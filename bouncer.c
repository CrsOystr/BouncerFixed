/* written by Nicolas Metz and James Bradshaw. Spring 2014

   Bouncer application used to overlay gradient ball to image files in conjunction with ffmpeg

*/

#include <stdio.h>
//#include <ffmpeg/avutil.h>
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libavcodec/avcodec.h"



int main(int argc, char *argv[])
{

  av_register_all();
  printf("lol\ntesting\n");

  AVFrame frame;
  int64_t res;

  return 0;
}

