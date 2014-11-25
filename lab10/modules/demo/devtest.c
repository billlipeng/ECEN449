#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sound.h"
#include "audio_samples.h"

static unsigned short* sample_ptr = &audio_samples[0];

int main()
{
  int fd;
  int i;
  int input;
  unsigned int cmd;
  unsigned int *val_ptr;
  static int num=0;
  char buffer[NUM_SAMPLES];
  sample_ptr = &audio_samples[0];
  
  /* open device file for reading and writing */
  /* use "open" to open '/dev/xac97' */
  fd = open("/dev/xac97", O_RDWR);  

  /* handle error opening file */
  if(fd == -1)
  {
    printf("Failed to open device file!\n");
    return -1;
  }

 /* //while(input != 'q'){
   while(1){
        for(i=0; i< NUM_SAMPLES; i++){ 
	        buffer[i] = (char) audio_samples[num];
	        num++;   
	        if(num==NUM_SAMPLES) {
			 num=0;
	 		 break;
		}       
        }

       write(fd, buffer, NUM_SAMPLES);
   
       if( num == 0) break;
       //input = getchar();

  }
   

  // close the device driver
  
  close(fd);
  return 0;*/ 
 

  
  printf("Enter 'v' for adjusting volume, 'f' for adjusting frequency and 'q' to exit.\n");

 while(input != 'q')
  {
    if( input == 'v'){
    	input = input;
	printf("Please select the voice level. 0-mute, 1-mid, 2-max.\n");
	scanf("%d",&num);
	val_ptr = &num;
	if(*val_ptr== 0 || *val_ptr==1 || *val_ptr==2)
		cmd = ADJUST_AUX_VOL;
	ioctl(fd, cmd, val_ptr);
    }
    else if( input == 'f'){
	printf("Please select the frequency. 0-5--> slow-fast.\n");
	scanf("%d",&num);
	val_ptr = &num;
	if(*val_ptr==0 || *val_ptr==1 || *val_ptr==2 || *val_ptr==3 || *val_ptr==4 || *val_ptr==5)
		cmd = ADJUST_PLAYBACK_RATE;
	ioctl(fd, cmd, val_ptr);
    }
   
    else if( input == 'm'){
	printf("Please select the track. 0-stereo, 1-mono.\n");
	scanf("%d",&num);
	val_ptr = &num;
	if(*val_ptr==0 || *val_ptr==1)
		cmd = ENABLE_DISABLE_MONO;
	ioctl(fd, cmd, val_ptr);
	
    }
    
   // while(1)
   // {
    	for(i=0; i< NUM_SAMPLES; i++)
	{ 
	        buffer[i] = (char) audio_samples[num];
	        num++;   
	        if(num==NUM_SAMPLES) 
		{
			 num=0;
	 		 break;
		}       
        }

        write(fd, buffer, NUM_SAMPLES);
   
        //if( num == 0) break;
        //input = getchar();

    //}
	
    input = getchar();

  }

  close(fd);
  return 0;
  
   
}
