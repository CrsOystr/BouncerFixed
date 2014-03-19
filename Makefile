all:
	gcc -I../ffmpeg/include -L../ffmpeg/lib  bouncer.c -o bouncer `pkg-config --cflags --libs libavutil libavformat libavcodec libswscale`

cookies:
	echo lol

clean:
	$(RM) bouncer *.o *.mp4 *.xkcd



movie:
