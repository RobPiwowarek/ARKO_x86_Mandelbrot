#ifndef PAINT_H
#define PAINT_H

#include <stdio.h>
#include "allegro5/allegro.h"

void paint(ALLEGRO_BITMAP *bitmap, int width, int height, double x, double y, double delta);

void mandelbrot(unsigned* pPixelBuffer, int width, int height, double x, double y, double delta);


#endif
