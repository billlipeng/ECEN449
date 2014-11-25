// devtest.c
// This is an application for the device driver
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
  int fd;                  /* file descriptor */
  int message;  /*message from the buffer*/
  int byte;

  /* open device file for read and write */
  /* use "open" to open '/dev/irq_test' */
  fd = open("/dev/irq_test", O_RDWR);  // read-only

  /* handle error opening file */
  if(fd == -1)
  {
    printf("Failed to open device file!\n");
    return -1;
  }
  
  while(1) 
  {
        /* use "read" to read from buffer */
        byte = read(fd, &message, 4);
        /* print unsigned ints to screen */
   		if( byte != 0 )
			printf("Decoded IR signal  = 0x%x\n", message);
        sleep(1);		//delay    
  }
  close(fd);
  return 0;
}
