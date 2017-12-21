CC=gcc
CFLAGS=-m64

ASM=nasm
AFLAGS=-f elf64

LFLAGS=-L/usr/lib -lallegro -lallegro_color

all: mandelbrot

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

mandelbrot.o: mandelbrot.s
	$(ASM) $(AFLAGS) mandelbrot.s
	
paint.o:paint.c
	$(CC) $(CFLAGS) -c paint.c

mandelbrot: main.o mandelbrot.o paint.o paint.h
	$(CC) $(CFLAGS) main.o mandelbrot.o paint.o -o mandelbrot $(LFLAGS)

clean:
	rm *.o
	rm mandelbrot
