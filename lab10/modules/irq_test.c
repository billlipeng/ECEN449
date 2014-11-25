/*  irq_test.c - Simple character device module
 *  
 *  Demonstrates interrupt driven character device.  Note: Assumption
 *  here is some hardware will strobe a given hard coded IRQ number
 *  (200 in this case).  This hardware is not implemented, hence reads
 *  will block forever, consider this a non-working example.  Could be
 *  tied to some device to make it work as expected.
 *
 *  (Adapted from various example modules including those found in the
 *  Linux Kernel Programming Guide, Linux Device Drivers book and
 *  FSM's device driver tutorial)
 */


/* All of our linux kernel includes. */
/* Needed by all modules */
#include <linux/module.h>  
/* Needed for module parameters */
#include <linux/moduleparam.h>  
/* Needed for printk and KERN_* */
#include <linux/kernel.h>  
/* Need for __init macros  */
#include <linux/init.h>	   
/* Provides file ops structure */
#include <linux/fs.h>
#include <linux/slab.h>	   
// Provides access to the "current" process task structure
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/io.h>      
/* Needed for IO reads and writes */
#include "xparameters.h"   
/*Needed for physical address of multiplier */   
#include <linux/device.h>
#include <linux/semaphore.h>	/* Provides semaphore support */
#include <linux/wait.h>		/* For wait_event and wake_up */
#include <linux/interrupt.h>	/* Provide irq support functions (2.6 only) */

/* Some defines */
#define DEVICE_NAME "irq_test"
#define BUF_LEN 200
#define IRQ_NUM 3

/* From xparameters.h */
#define PHY_ADDR XPAR_IR_DEMOD_0_BASEADDR // IR_signal
#define MEMSIZE XPAR_IR_DEMOD_0_HIGHADDR - XPAR_IR_DEMOD_0_BASEADDR + 1



/* Function prototypes, so we can setup the function pointers for dev
   file access correctly. */
int my_init(void);
void my_cleanup(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static irqreturn_t irq_handler(int irq, void *dev_id);

/* 
 * Global variables are declared as static, so are global but only
 * accessible within the file.
 */
static int Major;		/* Major number assigned to our device driver */
static int Device_Open = 0;	/* Flag to signify open device */
static char msg[BUF_LEN];	/* The msg the device will give when asked */
static char *msg_Ptr;
static struct semaphore sem;  /* mutual exclusion semaphore for race
				 on file open  */
static wait_queue_head_t queue; /* wait queue used by driver for
				   blocking I/O, dynamiclly*/

static int* start;
static int* messages;
static int* end;


void* virt_addr; // virtual address pointing to IR_
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
  printk("Physical Address: %x\n", PHY_ADDR); //Print physical address
  printk("Virtual Address: %x\n", virt_addr); //Print virtual address
  
  init_waitqueue_head(&queue);	/* initialize the wait queue */

  /* Initialize the semaphor we will use to protect against multiple
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

  try_module_get(THIS_MODULE);	/* increment the module use count
				   (make sure this is accurate or you
				   won't be able to remove the module
				   later. */

  messages = (int*)kmalloc( (100*sizeof(int)), GFP_KERNEL);// dynamic allocation of memory
  start = messages;
  end = messages;
  msg_Ptr = (char*)messages; 
  return 0;
}

/* 
 * Called when a process closes the device file.
 */
static int device_release(struct inode *inode, struct file *file)
{
  Device_Open--;		/* We're now ready for our next caller */
  
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
  int bytes_read = 0;
  
  
  /* In this driver msg_Ptr is NULL until an interrupt occurs */
  wait_event_interruptible(queue, (msg_Ptr != NULL)); /* sleep until interrupted*/

  while ( length&& (msg_Ptr != end) ) {
    
    /* 
     * We have to use 
     * put_user which copies data from the kernel data segment to
     * the user data segment. 
     */
    put_user(*(msg_Ptr++), buffer++); /* one char at a time... */
    if( msg_Ptr == start + 100) msg_Ptr = start; // set msg_Ptr back to start if msg_Ptr reach ceiling
    length --;
    bytes_read++;
  }
  
  /* 
   * Most read functions return the number of bytes put into the buffer
   */
  return bytes_read;
}

/*  
 * Called when a process writes to dev file: echo "hi" > /dev/hello 
 * Next time we'll make this one do something interesting.
 */

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{

  /* not allowing writes for now, just printing a message in the
     kernel logs. */
  printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
  return -EINVAL;		/* Fail */


}

irqreturn_t irq_handler(int irq, void *dev_id) {
  
  static int counter = 0;	/* keep track of the number of
				   interrupts handled */

  printk(KERN_ALERT "IRQ Num %d called, interrupts processed %d times\n", irq, counter++);
  messages[counter-1] = ioread32(virt_addr);
  end++;
  if( end == start + 100) end = start; // set end back to start if end reach the ceiling 
  iowrite32(0x10000000, virt_addr + 8); // set slv_reg2 control bit to one
										// clean the interrupt
  
  wake_up_interruptible(&queue);   /* Just wake up anything waiting for the device */
  return IRQ_HANDLED;
}



/* These define info that can be displayed by modinfo */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peng Li, Sundaresan Adin");
MODULE_DESCRIPTION("Module which creates a character device and allows user interaction with it");

/* Here we define which functions we want to use for initialization
   and cleanup */
module_init(my_init);
module_exit(my_cleanup);
