
all: bouncer.c
	gcc -I../ffmpeg/include -L../ffmpeg/lib bouncer.c -o bouncer `pkg-config --libs --cflags libavutil libavformat libavcodec libswscale`

clean:
	$(RM) bouncer *.o *.mp4 *.xkcd

movie: output000.xkcd
	ffmpeg -f image2 -r 30 -i output%03d.xkcd movie.mp4