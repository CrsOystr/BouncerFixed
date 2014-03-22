
all:
	gcc -I../ffmpeg/include -L../ffmpeg/lib bouncer.c -o bouncer `pkg-config --libs --cflags libavutil libavformat libavcodec libswscale`

cookies:
	echo lol

clean:
	$(RM) bouncer *.o *.mp4 *.xkcd



movie:
	ffmpeg -f image2 -r 10 -i output%03d.xkcd bouncer.mp4