#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
 
  int fd;                  /* file descriptor */

  int buffer;

  int byte;

  /* open device file for reading and writing */
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
   	//sleep(1);
        /* read result using char dev */
        /* using read to read from peripheral */
        byte = read(fd, &buffer, 4);
        /* print unsigned ints to screen */
   	if( byte != 0 )
        printf("Decoded IR signal  = 0x%x\n", buffer);
        sleep(1);		//delay
	//delay();
    
  }
  close(fd);
  return 0;
}
