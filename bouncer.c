 /* written by Nicolas Metz and James Bradshaw. Spring 2014

   Bouncer application used to overlay gradient ball to image files in conjunction with ffmpeg

*/


//#include <ffmpeg/avutil.h>
#include "libavutil/avutil.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
  AVFormatContext *pFormatCtx;
  int             i,j,videoStream;
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
  
  //set pointer to NULL
  pFormatCtx = NULL;

  //open the input picture and assign it a Format Context
  avformat_open_input(&pFormatCtx, argv[1], NULL, NULL);

  //find the video stream
  videoStream = avformat_find_stream_info(pFormatCtx, NULL);

  //get the codec context from the format at the given stream 
  pCodecCtx = pFormatCtx->streams[videoStream]->codec;

  //find the codec for the input image
  pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

  //open the found codec
  avcodec_open2(pCodecCtx, pCodec, NULL);

  //allocate memory for two frames one for orignal input one for conversion
  pFrame = av_frame_alloc();
  pFrameRGB = av_frame_alloc();

  //number of bytes contained in the image
  numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);

  //allocate memory for the image buffer
  buffer = (uint8_t *)av_malloc(numBytes*sizeof(uint8_t));

  // fill the picture from the buffer
  avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);

  //read packet from frame
  i=0;
  
  while(av_read_frame(pFormatCtx, &packet)>=0)
    {
      if(packet.stream_index == videoStream)
	{
	  avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
	  
	  if(frameFinished)
	    {
	      img_convert((AVPicture *)pFrameRGB, PIX_FMT_RGB24, (AVPicture *)pFrame, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);
	      
	      if(++i <= 5)
		{
		  //SaveFrame(pFrameRGB, pCodecCtx->width, pCodecCtx->height, i);
		}
	    }
	}
      
      av_free_packet(&packet);

    }




  printf("%s : %i \n" , pFormatCtx->filename, videoStream);

  printf("TESTIING IS DOING SOMETHING?\n");
  return 0;
}

