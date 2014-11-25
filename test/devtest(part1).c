#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sound.h"

int main()
{
  int fd;
  char input = 0;

  /* open device file for reading and writing */
  /* use "open" to open '/dev/xac97' */
  fd = open("/dev/xac97", O_RDWR);

  /* handle error opening file */
  if(fd == -1)
  {
    printf("Failed to open device file!\n");
    return -1;
  }

  while( input != 'q'){

   input = getchar();

  }
  close(fd);
  return 0;

}
