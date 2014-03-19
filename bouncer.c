/* written by Nicolas Metz and James Bradshaw. Spring 2014

   Bouncer application used to overlay gradient ball to image files in conjunction with ffmpeg

*/


//#include <ffmpeg/avutil.h>
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
  AVFormatContext *pFormatCtx;
  int             i, videoStream;
  AVCodecContext  *pCodecCtx;
  AVCodec         *pCodec;
  AVFrame         *pFrame; 
  AVFrame         *pFrameRGB;
  AVPacket        packet;
  int             frameFinished;
  int             numBytes;
  uint8_t         *buffer;
  
  if(argc < 2) {
    printf("Please provide an image file as an arguement\n");
    return -1;
  }
  // Register all formats and codecs
  av_register_all();
  
  
 




  printf("TESTIING IS DOING SOMETHING?\n");
  return 0;
}

