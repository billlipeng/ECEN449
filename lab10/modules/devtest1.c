//devtest.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sound.h"
#include "audio_samples.h"

/*
A simple print function to print out what the command is
doing so the user knows what to expect from the entered
command. 
*/ 

static unsigned short* sample_ptr = &audio_samples[0];
void print(char c, int cmd) {
	if(c == 's')
		switch(cmd) {
			case AC97_VOL_MUTE:
				printf("Command: Mute Volume\n");
				break;
			case AC97_VOL_MIN:
				printf("Command: Minimum Volume\n");
				break;
			case AC97_VOL_MID:
				printf("Command: Medium Volume\n");
				break;
			case AC97_VOL_MAX:
				printf("Command: Maximum Volume\n");
				break;
			default:
				printf("Command: Unknown\n");
				break;
		}
	else if(c == 'p')
		switch(cmd) {
			case AC97_PCM_RATE_8000_HZ:
				printf("Command: Play rate 8000Hz (Slow) \n");
				break;
			case AC97_PCM_RATE_11025_HZ:
				printf("Command: Play rate 11025Hz (Normal) \n");
				break;
			case AC97_PCM_RATE_16000_HZ:
				printf("Command: Play rate 16000Hz (Fast) \n");
				break;
			case AC97_PCM_RATE_22050_HZ:
				printf("Command: Play rate 22050Hz (Faster) \n");
				break;
			case AC97_PCM_RATE_44100_HZ:
				printf("Command: Play rate 44100Hz (Fasterer) \n");
				break;
			case AC97_PCM_RATE_48000_HZ:
				printf("Command: Play rate 48000Hz (Fastest) \n");
				break;
		}
	else if(c == 'm')
		switch(cmd) {
			case AC97_PCM_RATE_8000_HZ:
				printf("Command: Momo Ture \n");
				break;
			case AC97_PCM_RATE_11025_HZ:
				printf("Command: Momo False \n");
				break;
		}
}

int main()
{
  int fd;
  char input = 0;
  char buffer[NUM_SAMPLES];

  int i;
  static int num;
  //Array of sound controls
  int sound[4] = {AC97_VOL_MUTE, AC97_VOL_MIN, AC97_VOL_MID, AC97_VOL_MAX};
  //Pointer to sound array for the ioctl function
  int* sound_ptr = sound;

  //Array of playback controls
  int playback[6] = {AC97_PCM_RATE_8000_HZ, AC97_PCM_RATE_11025_HZ, AC97_PCM_RATE_16000_HZ, AC97_PCM_RATE_22050_HZ, AC97_PCM_RATE_44100_HZ, AC97_PCM_RATE_48000_HZ};
  //Pointer to playback array for the ioctl function
  int* pb_ptr = playback;

  //Array of mono controls
  int mono[2] = {1,0};

  //Pointer to mono array for the ioctl function
  int* mono_ptr = mono;

  /* open device file for reading and writing */
  /* use "open" to open '/dev/xac97' */
  fd = open("/dev/xac97", O_RDWR);

  /* handle error opening file */
  if(fd == -1)
  {
    printf("Failed to open device file!\n");
    return -1;
  }

  /*
	We will iterate through the arrays depending on which
	option was selected (s or p) and execute each command
	in the array.
  */
  printf("Enter a command (s - volume control, p - playback control, m - mono control): ");
	input = getchar();
  while( input != 'q')
  {
	  if(input == 's') 
	  { //Sound commands
			  ioctl(fd, ADJUST_AUX_VOL, sound_ptr);
			  print('s', *sound_ptr); //Print out the command
			  sound_ptr++;
			  if(sound_ptr == (sound+4)) //If the pointer hit the end of the array, reset it to the first cell
			  	sound_ptr = sound;
	  }
	  if(input == 'p') 
	  { //Playback commands
			  ioctl(fd, ADJUST_PLAYBACK_RATE, pb_ptr);
			  print('p', *pb_ptr); //Print out the command
			  pb_ptr++;
			  if(pb_ptr == (playback+6)) //Same pointer logic as before, reset if it hit the end
		          	pb_ptr = playback; 
	  }
	  if(input == 'm') 
	  { //Mono commands
			  ioctl(fd, ENABLE_DISABLE_MONO, mono_ptr);
			  print('m', *mono_ptr); //Print out the command
			  mono_ptr++;
			  if(mono_ptr == (mono+1)) //Same pointer logic as before, reset if it hit the end
		          	mono_ptr = mono; 
	  }

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
	  printf("Enter command: ");
	  input = getchar();
  }
  close(fd);
  return 0;

}

