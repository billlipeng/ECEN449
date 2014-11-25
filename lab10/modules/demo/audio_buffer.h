/* All of our linux kernel includes. */
#include <linux/module.h>  /* Needed by all modules */
#include <linux/moduleparam.h>  /* Needed for module parameters */
#include <linux/kernel.h>  /* Needed for printk and KERN_* */
#include <linux/init.h>	   /* Need for __init macros  */
#include <linux/fs.h>	   /* Provides file ops structure */
#include <linux/sched.h>   /* Provides access to the "current" process
			      task structure */
#include <asm/uaccess.h>   /* Provides utilities to bring user space
			      data into kernel space.  Note, it is
			      processor arch specific. */
#include <linux/semaphore.h>	/* Provides semaphore support */
#include <linux/wait.h>		/* For wait_event and wake_up */
#include <linux/interrupt.h>	/* Provide irq support functions (2.6
				   only) */
#include "xparameters.h"   /* Needed for physical address of IR_demod */
#include <linux/io.h>      /* Needed for IO reads and writes */  
#include "xac97.h"
#include "audio_samples.h"

/* Some defines */
#define DEVICE_NAME "xac97"
#define IRQ_NUM 1
#define BUF_LEN 200
#define PHY_ADDR XPAR_OPB_AC97_CONTROLLER_REF_0_BASEADDR
#define MEMSIZE XPAR_OPB_AC97_CONTROLLER_REF_0_HIGHADDR - XPAR_OPB_AC97_CONTROLLER_REF_0_BASEADDR + 1

#define ENABLE_MONO 1
#define DISABLE_MONO 0 
/* Function prototypes, so we can setup the function pointers for dev
   file access correctly. */
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static irqreturn_t irq_handler(int irq, void *dev_id);
// the function prototype for ioctl()
static int device_ioctl(struct inode *, struct file *, unsigned int, unsigned int *);

/* 
 * Global variables are declared as static, so are global but only
 * accessible within the file.
 */
static int Major;		/* Major number assigned to our device driver */
static int Device_Open = 0;	/* Flag to signify open device */
static struct semaphore sem;  /* mutual exclusion semaphore for race
				 on file open  */
static wait_queue_head_t queue; /* wait queue used by driver for
				   blocking I/O */
static int num = 0;
//static u16* sample_ptr = &audio_samples[0];
void* virt_addr;  //virtual address pointing to AC97
u32 baseaddr;
static int mono;
