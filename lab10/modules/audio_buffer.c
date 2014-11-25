// audio_buffer.c

/* Moved all prototypes and includes into the headerfile */
#include "audio_buffer.h"

/* This structure defines the function pointers to our functions for
   opening, closing, reading and writing the device file.  There are
   lots of other pointers in this structure which we are not using,
   see the whole definition in linux/fs.h */
// file operations structure
static struct file_operations fops = {
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_release,
  .ioctl = device_ioctl
};

/*
 * This function is called when the module is loaded and registers a
 * device for the driver to use.
 */
int my_init(void)
{
  /* Linux kernel's version of printf */
  printk(KERN_INFO "Mapping virtual address....\n");
  /* Map virtual address to multiplier physical address */
  //use ioremap
  virt_addr = ioremap(PHY_ADDR, MEMSIZE);
  baseaddr = (u32)virt_addr; // baseaddr is the virtual address of the audio controller
  printk("Physical Address: %x\n", PHY_ADDR); //Print physical address
  printk("Virtual Address: %x\n", baseaddr); //Print virtual address

  init_waitqueue_head(&queue);	/* initialize the wait queue */

  /* Initialize the semaphore we will use to protect against multiple
     users opening the device  */
  sema_init(&sem, 1);

  Major = register_chrdev(0, DEVICE_NAME, &fops);
  if (Major < 0) {
    printk(KERN_ALERT "Registering char device failed with %d\n", Major);
    return Major;
  }
  printk(KERN_INFO "Registered a device with dynamic Major number of %d\n", Major);
  printk(KERN_INFO "Create a device file for this device with this command:\n'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);

  return 0;		/* success */
}

/*
 * This function is called when the module is unloaded, it releases
 * the device file.
 */
void my_cleanup(void)
{
  /*
   * Unregister the device
   */
  unregister_chrdev(Major, DEVICE_NAME);
  /*
   * Unmapping virtual address space
   */
  printk(KERN_ALERT "unmapping virtual address space....\n");
  iounmap((void*)virt_addr);
}

/*
 * Called when a process tries to open the device file, like "cat
 * /dev/irq_test".  Link to this function placed in file operations
 * structure for our device file.
 */
static int device_open(struct inode *inode, struct file *file)
{

  int irq_ret;

  if (down_interruptible (&sem))
	return -ERESTARTSYS;

  /* We are only allowing one process to hold the device file open at
     a time. */
  if (Device_Open){
    up(&sem);
    return -EBUSY;
  }
  Device_Open++;

  /* OK we are now past the critical section, we can release the
     semaphore and all will be well */
  up(&sem);

  /* request a fast IRQ and set handler */
  irq_ret = request_irq(IRQ_NUM, irq_handler, 0 /*flags*/ , DEVICE_NAME, NULL);
  if (irq_ret < 0) {		/* handle errors */
    printk(KERN_ALERT "Registering IRQ failed with %d\n", irq_ret);
    return irq_ret;
  }

  //initialize AC97
  /*Initialize the codec with or without loopback,*/
  XAC97_InitAudio(baseaddr, 0);
  /*Write to an AC97 control register using peripheral keyhole registers.*/
  //enables variable rate audio mode (enables sample rate registers and SLOTREQ signaling
  XAC97_WriteReg(baseaddr, AC97_ExtendedAudioStat, 1);
  //set AUX volume to max
  XAC97_WriteReg(baseaddr, AC97_AuxOutVol, AC97_VOL_MAX);
  //set the PCM playback rate at 11025Hz
  XAC97_WriteReg(baseaddr, AC97_PCM_DAC_Rate, AC97_PCM_RATE_11025_HZ);
  //XAC97_WriteReg(baseaddr, AC97_PCM_ADC_Rate, AC97_PCM_RATE_11025_HZ);
  
  // Initialize mono
  mono = 0;

  try_module_get(THIS_MODULE);	/* increment the module use count
				   (make sure this is accurate or you
				   won't be able to remove the module
				   later. */

  //sample_ptr = &audio_samples[0];

  printk(KERN_ALERT "Device opened\n");
  printk(KERN_ALERT"IRQ Num %d called\n", IRQ_NUM);
  return 0;
}

/*
 * Called when a process closes the device file.
 */
static int device_release(struct inode *inode, struct file *file)
{
  Device_Open--;		/* We're now ready for our next caller */

  // Clear the playback FIFO
  XAC97_ClearFifos(baseaddr);
  // Perform a 'soft' reset on the audio codec
  XAC97_SoftReset(baseaddr);

  // Unregister the interrupt handler
  free_irq(IRQ_NUM, NULL);

  /*
   * Decrement the usage count, or else once you opened the file,
   * you'll never get get rid of the module.
   */
  module_put(THIS_MODULE);
  printk(KERN_ALERT "Device Released\n");

  return 0;
}

/*
 * Called when a process, which already opened the dev file, attempts to
 * read from it.
 */
static ssize_t device_read(struct file *filp,	/* see include/linux/fs.h   */
			   char *buffer,	/* buffer to fill with data */
			   size_t length,	/* length of the buffer     */
			   loff_t * offset)
{
  /* Not allow writes for now, just print a message in the
     kernel logs. */
  printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
  return -EINVAL;		/* Fail */
}

/*
 * Called when a process writes to dev file: echo "hi" > /dev/hello
 * Next time we'll make this one do something interesting.
 */
static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{


   u32 sample_data;
   char sample_in;
 
   while(len)
   {
       /*
  	* The buffer is in user data segment, not the kernel segment.
    	* We use get_user which gets data from the user data segment
   	* to the kernel data segment.
    	*/
   	get_user(sample_in, buff);
   	sample_data = 10*(u32)((unsigned char)sample_in);
   	buff++;
   
   	/* sleep when the audio FIFO is full  */
   	wait_event_interruptible(queue,XAC97_isInFIFOFull(baseaddr));
 	
	// When mono is set to true, duplicate samples are written to the playback FIFO
     if(mono)
     		XAC97_WriteFifo(baseaddr, sample_data);
   	else
	{
     		XAC97_WriteFifo(baseaddr, sample_data);
     		XAC97_WriteFifo(baseaddr, sample_data);
   	}
	len--;
   }
   return 0;

}


// the interrupt triggers when the buffer is half empty

irqreturn_t irq_handler(int irq, void *dev_id)
{
  static int counter = 0;	/* keep track of the number of
				   interrupts handled */
  printk(KERN_ALERT "IRQ Num %d called, interrupts processed %d times\n", irq, counter++);
  wake_up_interruptible(&queue);   /* Just wake up anything waiting for the device */
  return 0;
}


/* This function allows the user process to provide control
   command to our device driver and read status from the device */


static int device_ioctl(struct inode *inode,
                        struct file *file,
                        unsigned int cmd,
                        unsigned int *val_ptr)
{
  u16 val; //temportary value
  get_user(val, val_ptr); //grab value from user space
	/* switch statement to execute commands */
	switch(cmd) {
		/*aux volume*/
		case ADJUST_AUX_VOL:
			XAC97_WriteReg(virt_addr, AC97_AuxOutVol, val);
			break;

		/*playback rate*/
		case ADJUST_PLAYBACK_RATE:
			XAC97_WriteReg(virt_addr, AC97_PCM_DAC_Rate, val);
			break;

		/*mono*/
		case ENABLE_DISABLE_MONO:
			if(val) mono = 1;
			else 	mono = 0;
			break;


		/*handle error*/
		default:
			printk(KERN_INFO "Unsupported control command!\n");
			return -EINVAL;
	}

  return 0;
}


/* These define info that can be displayed by modinfo */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peng Li & Sundaresan Adin");
MODULE_DESCRIPTION("xac97 driver");

/* Here we define which functions we want to use for initialization
   and cleanup */
module_init(my_init);
module_exit(my_cleanup);
