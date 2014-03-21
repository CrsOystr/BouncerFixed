 /*
   written by Nicolas Metz and James Bradshaw. Spring 2014

   Bouncer application used to overlay gradient ball to image files in conjunction with ffmpeg
   
   Some annoted code used from dranger ffmpeg tutorial
 */

#include "libavutil/avutil.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include <stdio.h>


//FUNCTION TO RETRIEVE AVFRAME
AVFrame* load_frame(char* file_name)
{
  AVFormatContext *pFormatCtx = NULL;
  int i, videoStream, numBytes;
  AVCodecContext *pCodecCtx = NULL;
  AVCodec *pCodec = NULL;
  AVFrame *pFrameRGB = NULL;
  uint8_t *buffer = NULL;
  AVPacket packet;
  int frameFinished;

  AVDictionary *optionsDict = NULL;
  
  av_register_all();
  
  if(avformat_open_input(&pFormatCtx, file_name, NULL, NULL)!=0)
    {
      printf("Couldnt Open File");
      return NULL;
    }

  // Retrieve stream information
  if(avformat_find_stream_info(pFormatCtx, NULL)<0)
    {
      printf("couldnt find stream info");
      return NULL; 
    }

  // Find the first video stream
  videoStream=-1;
  for(i=0; i<pFormatCtx->nb_streams; i++)
    if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) {
      videoStream=i;
      break;
    }
  if(videoStream==-1)
    {
      printf("couldnt find video stream\n");
      return NULL; 
    }
  
  // Get a pointer to the codec context for the video stream
  pCodecCtx=pFormatCtx->streams[videoStream]->codec;
  
  // Find the decoder for the video stream
  pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
  if(pCodec==NULL)
 {
    printf("Unsupported codec!\n");
    return NULL; 
  }

  // Open codec
  if(avcodec_open2(pCodecCtx, pCodec, &optionsDict)<0)
    {
      printf("Couldnt open codec");
      return NULL;
    }
  
  // Allocate an AVFrame structure
  pFrameRGB=av_frame_alloc();
  if(pFrameRGB==NULL)
    {
      printf("couldnt allocate frame");
      return NULL;
    }
  // Determine required buffer size and allocate buffer
  numBytes=avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
pCodecCtx->height);
 
  buffer=(uint8_t *)av_malloc(numBytes*sizeof(uint8_t));

  pFrameRGB->width = pCodecCtx->width;
  pFrameRGB->height = pCodecCtx->height;
  pFrameRGB->format = pCodecCtx->pix_fmt;
 
  
  while(av_read_frame(pFormatCtx, &packet)>=0)
    {
      // Is this a packet from the video stream?
      if(packet.stream_index==videoStream)
	{
	  // Decode video frame
	  avcodec_decode_video2(pCodecCtx, pFrameRGB, &frameFinished,
				&packet);
	}
      av_free_packet(&packet);
    }





  return pFrameRGB;
}




/*





 */
AVFrame* convert(AVFrame *frame, int format)
{
  int                 numBytes;
  AVFrame            *outputFrame = NULL;
  struct SwsContext  *sws_ctx = NULL;
  uint8_t            *buffer = NULL;



  // Allocate an AVFrame structure
  outputFrame=av_frame_alloc();
  if(outputFrame==NULL)
    {
      printf("couldnt allocate frame");
      return NULL;
    }

  numBytes = avpicture_get_size(PIX_FMT_RGB24, frame->width, frame->height);

  buffer=(uint8_t *)av_malloc(numBytes*sizeof(uint8_t));   

  printf("lolololformat %i\n", frame->height);
  
  sws_ctx = sws_getContext
     (
      frame->width,
      frame->height,
      frame->format,
      frame->width,
      frame->height,
      PIX_FMT_RGB24,
      SWS_BILINEAR,
      NULL,
      NULL,
      NULL
     );

  //Fills Pic to Prepare
   avpicture_fill((AVPicture *)outputFrame, buffer, PIX_FMT_RGB24,
  frame->width, frame->height);

   sws_scale
     (
      sws_ctx,
      (uint8_t const * const *)frame->data,
      frame->linesize,
      0,
      frame->height,
      outputFrame->data,
      outputFrame->linesize
      );

  return outputFrame;
}

int writeFrame( AVFrame* input, int frameNumber)
{
  AVCodec        *codec;
  AVCodecContext *CodecCtx;
  FILE           *f;
  AVFrame        *frame;
  AVPacket        pkt;
  char          *fileName;

  
  codec = avcodec_find_encoder_by_name("xkcd");
  CodecCtx->pix_fmt = codec->pix_fmts[0];
  
  frame = convert(input, codec->pix_fmts[0]);

  fileName = "output%i", frameNumber;

  f = fopen(fileName, "wb");


}





/*MAIN ENTRY POINT TO APP



*/
int main(int argc, char *argv[])
{
  AVFrame *user_image;
  int i;

  //checks to confirm there is an arguement for us to accept
  if(argc < 2)
 {
    printf("Please provide a .jpg image file as an arguement\n");
    return -1;
  }

  //Loads frame using our function
  user_image = load_frame(argv[1]);
  
  
  for(i=0; i < 10; i++)
    {
      writeFrame(user_image, i);
    }

  //Ends program and confirms we did something
  printf("TESTIING IS DOING SOMETHING?\nand we havnt segfaulted\n");
  return 0;
}

