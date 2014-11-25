#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_* and printk */
#include <linux/init.h> /* Needed for __init and __exit macros */
#include <asm/io.h> /* Needed for IO reads and writes */

#include "xparameters.h" /* Needed for physical address of multiplier */

/*from xparameters.h*/
#define PHY_ADDR XPAR_MULTIPLY_0_BASEADDR //physical address of multiplier
/*size of physical address range for multiple */
#define MEMSIZE XPAR_MULTIPLY_0_HIGHADDR - XPAR_MULTIPLY_0_BASEADDR+1
#define DEVICE_NAME "multiplier"

/* Function prototypes, so we can setup the function pointers for dev
   file access correctly. */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

void* virt_addr; //virtual address pointing to multiplier
static int Major; /* Major number assigned to our device driver */

/* This structure defines the function pointers to our functions for
   opening, closing, reading and writing the device file.  There are
   lots of other pointers in this structure which we are not using,
   see the whole definition in linux/fs.h */
static struct file_operations fops = {
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_release
};

/* This function is run upon module load. This is where you setup data structures and reserve resources used by the module. */

static int __init my_init(void) {
	/* Linux kernel's version of printf */
	printk(KERN_INFO "Mapping virtual address...\n");
	
	/*map virtual address to multiplier physical address*/
	//use ioremap
	virt_addr = ioremap(PHY_ADDR, MEMSIZE);
	printk("Physical Address: %x\n", PHY_ADDR); //Print physical address
	printk("Virtual Address: %x\n", virt_addr); //Print virtual address

	/* This function call registers a device and returns a major number
	associated with it.  Be wary, the device file could be accessed
	as soon as you register it, make sure anything you need (ie
	buffers ect) are setup _BEFORE_ you register the device.*/
	Major = register_chrdev(0, DEVICE_NAME, &fops);

	/* Negative values indicate a problem */
	if (Major < 0) {		
		/* Make sure you release any other resources you've already
		grabbed if you get here so you don't leave the kernel in a
		broken state. */
		printk(KERN_ALERT "Registering char device failed with %d\n", Major);
		iounmap((void*)virt_addr);
		return Major;
	} else {
		printk(KERN_INFO "Registered a device with dynamic Major number of %d\n", Major);
		printk(KERN_INFO "Create a device file for this device with this command:\n'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
	}

	//a non 0 return means init_module failed; module can't be loaded.
	return 0;
}
/* This function is run just prior to the module's removal from the system. You should release _ALL_ resources used by your module here (otherwise be prepared for a reboot). */
static void __exit my_exit(void) {
	printk(KERN_ALERT "unmapping virtual address space...\n");	
	unregister_chrdev(Major, DEVICE_NAME);
	iounmap((void*)virt_addr);
}

/* 
 * Called when a process tries to open the device file, like "cat
 * /dev/my_chardev".  Link to this function placed in file operations
 * structure for our device file.
 */
static int device_open(struct inode *inode, struct file *file)
{
  printk(KERN_ALERT "This device is opened\n");  
  return 0;
}

/* 
 * Called when a process closes the device file.
 */
static int device_release(struct inode *inode, struct file *file)
{
  printk(KERN_ALERT "This device is closed\n");  
  return 0;
}

/* 
 * Called when a process, which already opened the dev file, attempts
 * to read from it.
 */
static ssize_t device_read(struct file *filp, /* see include/linux/fs.h*/
			   char *buffer,      /* buffer to fill with
						 data */
			   size_t length,     /* length of the
						 buffer  */
			   loff_t * offset)
{
  /*
   * Number of bytes actually written to the buffer
   */
  int bytes_read = 0;
  
  while (length && *msg_Ptr) {
    
    /* 
     * The buffer is in the user data segment, not the kernel segment
     * so "*" assignment won't work.  We have to use put_user which
     * copies data from the kernel data segment to the user data
     * segment.
     */
    put_user(*(msg_Ptr++), buffer++); /* one char at a time... */
    
    length--;
    bytes_read++;
  }
  
  /* 
   * Most read functions return the number of bytes put into the
   * buffer
   */
  return bytes_read;
}

/* 
 * This function is called when somebody tries to write into our
 * device file.
 */
static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset)
{
	int i, j;
	unsigned int mult1, mult2;
	
	int value1[4];
	/* printk(KERN_INFO "device_write(%p,%s,%d)", file, buffer, (int)length); */

	/* get_user pulls message from userspace into kernel space */
	for (i = 0; i < length; i++) {
		if(i < (length/3)) //Mult1
			for(j = 0; j < (length/3); j++) {
				value1[j] = ioread8(virt_addr+i);			
				put_user(value1[j], buffer++);
			}
	
	}

	/* 
	* Again, return the number of input characters used 
	*/
	return i;
}

/* These define info that can be displayed by modinfo */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ECEN449 SANKAR M S & BILL PENG");
MODULE_DESCRIPTION("Simple multiplier module");

/* Here we define which functions we want to use for initialization and cleanup */
module_init(my_init);
module_exit(my_exit);
