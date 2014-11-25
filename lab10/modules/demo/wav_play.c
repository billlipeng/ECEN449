#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <dirent.h>
#include <string.h>
#include "parse_wav.c"
/*user defined header files*/

#include "sound.h"


#define SMAPLE_SIZE 4000
#define ENABLE_MONO 1
#define DISABLE_MONO 0 
#define AC97_VOL_ATTN_DELTA_DB 0x0101
#define ENABLE_PLAY 1
#define DISABLE_PLAY 0
/*function prototypes*/
static int open_wav_file(char* filename);
static int wav_file_filter(const struct direct *entry);

/*global variables shared by all functions in this source*/
static int fd_out, fd_in;//file designators for audio device and wav file
static int fd_ir; // file designator for ir device
static struct stat file_info;//used for getting file length needed by mmap
int val;//temp variable used for ioctl calls
unsigned int *val_ptr;
static void *contents;//points to the beginning of the mmap region
static unsigned char *audio_ptr;//points to current audio sample
static unsigned char *samples;//points to the beginning of the audio data
static int num_samples;//number of samples in current wav file
//static unsigned short  msg_buff[200];//used to hold read IR messages
char msg_buff[200];
/*audio playback mode settings*/
int vol_setting, playback_rate, mono_setting, pr_val; //hold current audio settings
unsigned int *setting_ptr1, *setting_ptr2;
static int play_audio = 0;//play flag
//static int stop_audio = 1;//stop flag
static int completion_mode = 1; //0=stop,1=repeat,2=forward,3=reverse
static int mute_audio = 0;//mute flag
static int channel_up = 0;//channel up flag
static int channel_down = 0;//channel down flag
static int volume_up = 0;//volume up flag
static int volume_down = 0;//volume down flag

static int num=0;
static int new_file = 0;

static unsigned short current_volume = AC97_VOL_ATTN_0_DB;


int main()
{
  int i; //loop variable
  unsigned short user_input;
  int ir_read_bytes, audio_write_bytes;
  int quit = 0; //exit flag
  //counters which handle the multple message problem
  int wait_count = 0;
  struct dirent **namelist;//structure pointer for reading directory
  int num_files; //number of wav files contained in directory
  int cur_file=0; //index points to wav file currently open
  int nxt_file=0;
  
  unsigned int cmd;
  char buffer[4000];
  //char buffer_ir[200]={0};//a 200 byte buffer in user space
  int result;

  /*scan current directory for wav files and provide them in alphabetical order*/
  num_files = scandir(".", &namelist, wav_file_filter, alphasort);
  if(num_files < 0) //handle errors
  {
    perror("scandir");
      return -1;
  }

  /*open ir device file*/ 
  fd_ir = open("/dev/irq_test", O_RDWR);
  /*handle error opening file*/
  if(fd_ir<0)
  {
    printf("Failed to open ir device!\n");
    return -1;
  }

  /*open audio device file */
  fd_out = open("/dev/xac97", O_RDWR);  
  /* handle error opening file */
  if (fd_out < 0)
  {
    printf("Failed to open ac97 device file!\n");
    return -1;
  }



  // for test
  //printf("Before opening\n");

  /*initially open first wav file*/
  /*open and mmap file, check for valid file, and adjust codec*/
  printf("Opening %s\n", namelist[cur_file]->d_name);
  if(open_wav_file(namelist[cur_file]->d_name)<0)
    return -1;//if error opening
  
  while(quit != 1) //continue until killed
  {   
    
    /*if file selection changed load in a new file*/
    if(nxt_file != cur_file && new_file==1)
    //if( nxt_file != cur_file)
    {
      new_file = 0;
      num = 0;
      //*munmap current mapping*/
      munmap(contents, file_info.st_size);
      /*close currently opened file*/
      close(fd_in);
      printf("Opening %s\n", namelist[nxt_file]->d_name);
      /*open and mmap file, check for valid file, and adjust codec*/
      if(open_wav_file(namelist[nxt_file]->d_name)<0)
        return -1;//if error opening
      /*clear contents already written to audio device*/
      /*update current file index*/
      cur_file = nxt_file;
      //printf("It's playing %s\n",namelist[nxt_file]->d_name);  
      printf("It's playing."); 
    }    

   

    /*copy num_samples worth of samples from wav file to 
      audio device in repeat mode*/
 
    if(play_audio == ENABLE_PLAY)
    {
      
      //printf("It's playing!\n");
      for(i=0; i< 4000; i++)
      { 
        buffer[i] = *audio_ptr;
        num++;
        audio_ptr++;
        if(num==num_samples)
        {
          num=0;
          audio_ptr = samples;
          break;
        }
      }
      //for testing
      
      write(fd_out, buffer, 4000);
    }
   
    //else // if not writting audio data
    //	usleep(100000); // sleep for 100ms

   
    /*read in all messages in queue*/
    read(fd_ir, msg_buff, 4);   
   
    //convert char to int type
    result = (unsigned int)((unsigned char)msg_buff[3])*256*256*256 + 
             (unsigned int)((unsigned char)msg_buff[2])*256*256 + 
             (unsigned int)((unsigned char)msg_buff[1])*256 + 
             (unsigned int)((unsigned char)msg_buff[0]);
    //printf("Decoded message : 0x%x\n", result);  

    
    switch(result)
    {

    
      /*change the volume*/
      //when volume up is pressed
      case 0x92000000:
        printf("volume up\n");
        if(volume_up==0)
        {
          if(current_volume==AC97_VOL_ATTN_0_DB)
            current_volume = AC97_VOL_ATTN_0_DB;
          else
            current_volume = current_volume - AC97_VOL_ATTN_DELTA_DB;
          volume_up = 1;
        }
        else if(wait_count == 0)
        {
          volume_up = 0;
        }
        val = current_volume;
        val_ptr = &val;
        ioctl(fd_out,ADJUST_AUX_VOL,val_ptr);
        break;

      //when volume down is pressed
      case 0x93000000:
	printf("volume down\n");
        if(volume_down==0)
        {
          if(current_volume==AC97_VOL_ATTN_46_0_DB)// the lowest sound
            current_volume = AC97_VOL_ATTN_46_0_DB ;
          else
            current_volume = current_volume + AC97_VOL_ATTN_DELTA_DB;
          volume_down = 1;
        }
        else if(wait_count == 0)
        {
          volume_down = 0;
        }
        val = current_volume;
        val_ptr = &val;
        ioctl(fd_out,ADJUST_AUX_VOL,val_ptr);
        break;

   
      
      /*change the channel to switch wav files*/
      //if channel up pressed
      case 0x90000000:
        printf("channel up\n");
        if(channel_up==0)
        {
          /*open next wav file in directory*/
         nxt_file=cur_file+1;
          new_file = 1;
          if(nxt_file==num_files)
            nxt_file=0;//circular nature
          channel_up = 1;
        }
        else if(wait_count == 0)
        {
          channel_up = 0;
        }
        break;
 
      //if channel down pressed
      case 0x91000000:
	printf("channel down\n");
        if(channel_down==0)
        {
         /*open next wav file in directory*/
          nxt_file=cur_file-1;
          new_file = 1;
          if(cur_file==0)
            nxt_file=num_files-1;//circular nature
          break;
          channel_down = 1;
        }
        else if(wait_count == 0)
        {
          channel_down = 0;
        }

      //when play is pressed
      case 0xdf000000:
	printf("play\n");
        play_audio = ENABLE_PLAY;
       // stop_audio = 0;
        break;

      //when pause is pressed
      case 0xdc000000:
	printf("pause\n");
        play_audio = DISABLE_PLAY;
        break;

      //when stop is pressed
      case 0xde000000:
       // stop_audio = 1;
	printf("stop\n");
        play_audio = DISABLE_PLAY;
        num=0;
        audio_ptr = samples;
        break;     
  
      /*when mute pressed*/
      case 0x94000000:
        /*update codec*/
	printf("muting\n");
        val = AC97_VOL_MUTE;
        val_ptr = &val;
        ioctl(fd_out,ADJUST_AUX_VOL,val_ptr);
        break;
      
      //when exit is pressed
      case 0xe3000000:
	printf("exit\n");
        quit = 1;
        break;

      default: 
        ;
    }

  
  /*maintain wait scheme used to ignore multiple messages*/
  if(wait_count>25)
    wait_count = 0;
  else if(wait_count!=0)
    wait_count++;

  for(i=0; i<4; i++)
    msg_buff[i] = 0;
  //result = 0;
  
  }
  

  close(fd_in);
  close(fd_out);
}

/*this function opens a wav file, 
  maps its contents to memory, parses
  the wav header, and adjusts the audio
  codec accordingly
*/
static int open_wav_file(char* filename)
{

    wav_properties_t wav_info;


    /*open wave file*/
    fd_in=open(filename,O_RDONLY);
    /*handle error opening file*/
    if(fd_in <0){
        printf("Failed to wave file!\n");
        return -1;
    }
    
    /*get file info*/
    fstat(fd_in,&file_info);

    /*use mmap to map file to region of memory*/
    //mmap file to contents use flags for read only and shared mapping
    //printf("Mapping wav files\n");
    contents = mmap(0, file_info.st_size, PROT_READ, MAP_SHARED, fd_in, 0);    

    //ensure mmap worked properly
    if(contents == MAP_FAILED)
    {
        printf("Error with mmap!\n");
        return -1; 
    }



    /*advise the kernel to do read ahead*/
    madvise(contents,file_info.st_size,MADV_WILLNEED);
    
    
    /*get wave file info*/
    if( parse_wav((char*)contents,&wav_info) <0 )
    {
        printf("Invalid file type!\n");
        return -1;
    }


    /*ensure we can play wav file*/
    if(wav_info.format != 1)
    {
        printf("Compressed wav files are not supported!\n");
        return -1;
    }
    if(wav_info.bits_per_sample != 8)
    {
        printf("Only 8-bit audio is currently supported!\n");
        return -1;
    }
    
    /*calculate the number of samples in file*/
    num_samples = wav_info.num_bytes;//only supporting 8-bit audio



    /*adjust audio properties based on wav file*/
    /*set play mode */
    if(wav_info.num_channels == 1)//if mono
        mono_setting=0;//set mono
    else //if stereo
        mono_setting=1;//reset mono
    //use ioctl to enable or disable mono 
    setting_ptr1 = &mono_setting;
    ioctl(fd_out, ENABLE_DISABLE_MONO, setting_ptr1);


    /*set playback rate accordingly*/
    playback_rate = wav_info.sample_rate;
    if(playback_rate==8000)
      pr_val = 0;
    if(playback_rate==11025)
      pr_val = 1;
    if(playback_rate==16000)
      pr_val = 2;
    if(playback_rate==22050)
      pr_val = 3;
    if(playback_rate==44100)
      pr_val = 4;
    if(playback_rate==48000)
      pr_val = 5;
    setting_ptr2 = &pr_val;
    //set playback rate
    ioctl(fd_out, ADJUST_PLAYBACK_RATE, setting_ptr2);
  

  
    /* part 2(i) initialize audio buffer pointers*/
    samples = wav_info.audio_samples;//point to beginning of data section
    audio_ptr = wav_info.audio_samples;//points to current sample

    /*set play flag to start playing file*/
    play_audio = ENABLE_PLAY; 
    printf("success!\n");
    return 0; //success!
}

/*function used by scandir to filter out all files except
  those with the .wav extension*/
static int wav_file_filter(const struct direct *entry) 
{
  if(strstr(entry->d_name,".wav")) //if .wav in filename
    return 1;//true
  else 
    return 0;//false
}
