CC = gcc
CFLAGS = -g -Wall
XLFLAGS = -L/usr/X11R6/lib -lX11

demo: demo.c ezgfx.o
	$(CC) $(CFLAGS) -o demo demo.c ezgfx.o $(XLFLAGS)

ezgfx.o: ezgfx.c ezgfx.h
	$(CC) $(CFLAGS) -c ezgfx.c -o ezgfx.o
clean:
	rm *dat -f

execut:
	$(CC) -DDEBUG -DUSEGFX -g -Wall -O3 -I ~/bolsa2/include/ "dil_mhv_visual.c" ~/bolsa2/include/ezgfx.o -lm -lgsl -lgslcblas -o "dil_mhv_visual" -IGL -IGLU -lX11

