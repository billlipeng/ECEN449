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
/*user defined header files*/
#include "parse_wav.h"
#include "sound.h"

#define BUFF_LEN 2048 //2k 16-bit samples


/*function prototypes*/
static int open_wav_file(char* filename);
static int wav_file_filter(const struct direct *entry); 

/*global variables shared by all functions in this source*/
static int fd_out, fd_in;//file designators for audio device and wav file
static struct stat file_info;//used for getting file length needed by mmap
static unsigned short val=0;//temp variable used for ioctl calls
static void *contents;//points to the beginning of the mmap region
static unsigned char *audio_ptr;//points to current audio sample
static unsigned char *samples;//points to the beginning of the audio data
static int num_samples;//number of samples in current wav file
static unsigned short  msg_buff[100];//used to hold read IR messages
/*audio playback mode settings*/
static unsigned short vol_setting, playback_rate, mono_setting; //hold current audio settings
static int play_audio = 0;//play flag
static int completion_mode = 1; //0=stop,1=repeat,2=forward,3=reverse
static int mute_audio = 0;//mute flag

int main(void) {

    int i; //loop variable
    int ir_read_bytes, audio_write_bytes;
    int quit = 0; //exit flag
    //counters which handle the multple message problem
    int wait_count = 0;
    struct dirent **namelist;//structure pointer for reading directory
    int num_files; //number of wav files contained in directory
    int cur_file=0; //index points to wav file currently open
    int nxt_file=0;


    /*scan current directory for wav files and provide them in alphabetical order*/
    num_files = scandir(".", &namelist, wav_file_filter, alphasort);
    if (num_files < 0) //handle errors
    {
        perror("scandir");
        return -1;
    }
    
    /*open hardware devices with proper error handling*/

    /*open ir device file*/
    //use open
    /*handle error opening file*/
    if( <0){
        printf("Failed to open ir device!\n");
        return -1;
    }
    
    
   /*clear message queue before starting*/
    read(fd_ir,msg_buff,200);
	
    /*open audio device file*/
    //use open
    /*handle error opening file*/
    if( <0){
        printf("Failed to open audio device!\n");
        return -1;
    }

    /*initially open first wav file*/
    /*open and mmap file, check for valid file, and adjust codec*/
    printf("Opening %s\n", namelist[cur_file]->d_name);
    if(open_wav_file(namelist[cur_file]->d_name)<0)
        return -1;//if error opening

    while(quit != 1) //continue until killed
    {
        /*if file selection changed load in a new file*/
        if(nxt_file != cur_file)
        {
            /*munmap current mapping*/
            //use munmap
            /*close currently opened file*/
            //use close
            printf("Opening %s\n", namelist[cur_file]->d_name);
            /*open and mmap file, check for valid file, and adjust codec*/
            //use open_wave_file
            /*clear contents already written to audio device*/
            //use ioctl
            /*update current file index*/
            cur_file = nxt_file;
        }

        /*copy BUFF_LEN worth of samples from wav file to 
          audio device in repeat mode*/
        if(play_audio == 1)
        {
        }
        else //if not writting audio data
            usleep(100000); //sleep for 100ms 

        /*read in all messages in queue*/
       //use read  
 
        /*handle messages read*/
        for(i=0; i<ir_read_bytes/2;i++) //ir_read_bytes is returned from read!
        {
            switch(msg_buff[i])
            {

                /*if vol up pressed*/
                case 0x  :
                //may need to use counter
                //do something with vol_setting
                //call ioctl
                break;

                /*if vol down pressed*/
                case 0x  :
                //may need to use counter
                //do something with vol_setting
                //call ioctl
                break;

                /*if pause is pressed*/
                case 0x  :
                //do something with playback flag
                break;

                /*if play is pressed*/
                case 0x :
                //do something with playback flag
                break;

                /*if stop is pressed*/
                case 0x  :
                //do something with playback flag
                //do something with audio_ptr
                break;

                /*if channel up pressed*/
                case 0x  :
                    if(wait_count == 0)
                    {
                        /*open next wav file in directory*/
                        nxt_file=cur_file+1;
                        if(nxt_file==num_files)
                            nxt_file=0;//circular nature
                        wait_count = 1;//trigger a wait
                    }
                    break;

                /*if channel up pressed*/
                case 0x  :
                    break;

                /*if power button pressed*/
                case 0x  :
                    quit = 1;
                    ir_read_bytes=0;//exit for loop
                    break;
                
                /*when mute pressed*/
                case 0x94: //ignore additional messages until wait count is cleared
                    if(mute_audio == 0 && wait_count == 0)
                    {
                        val = AC97_VOL_MUTE;
                        mute_audio = 1;
                    }
                    else if(wait_count == 0)
                    {
                        val = vol_setting;
                        mute_audio = 0;
                    }
                    /*update codec*/
                    ioctl(fd_out,ADJUST_AUX_VOL,&val);
                    wait_count = 1;//wait 
                    break;
    
                //map some buttons to set the completion mode
                //note that the completion mode determines how your application
                //handles audio_ptr when the end of file has been reached
               


                default: 
                    printf("message %d not defined!\n",msg_buff[i]);
            }
        }
            /*maintain wait scheme used to ignore multiple messages*/
            if(wait_count>4)
                wait_count = 0;
            else if(wait_count!=0)
                wait_count++;
    }
    sleep(1); //wait for audio to finish playing before exiting	
    /*un-map file from memory region*/
   //use munmap 
    /*close ir device*/
    close();
    /*close wave file*/
    close();
    /*close audio device*/
    close();

	return 0;
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
    //use file_info.st_size for file size
    /*ensure mmap worked properly*/
    if(contents == MAP_FAILED)
    {
        printf("Error with mmap!\n");
        return -1; 
    }

    /*advise the kernel to do read ahead*/
    madvise(contents,file_info.st_size,MADV_WILLNEED);
    
    /*get wave file info*/
    if(parse_wav((char*)contents,&wav_info)<0)
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
    if(wav_info.num_channels == 1)//if mono
        mono_setting=1;//set mono
    else //if stereo
        mono_setting=0;//reset mono
    //use ioctl to enable or disable mono 
    //hint use &mono_setting
    /*set playback rate accordingly*/
    playback_rate = wav_info.sample_rate;
    //use ioctl to set playback rate
    
    /*initialize audio buffer pointers*/
    samples = wav_info.audio_samples;//point to beginning of data section
    audio_ptr = wav_info.audio_samples;//points to current sample

    /*set play flag to start playing file*/
    play_audio = 1; 

    return 0; //success!
}


/*function used by scandir to filter out all files except
  those with the .wav extension*/
static int wav_file_filter(const struct direct *entry) 
{
    if (strstr(entry->d_name,".wav")) //if .wav in filename
        return 1;//true
    else 
        return 0;//false
}
