#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <stdio.h>

#define uint		unsigned int
#define float		double

//#define mylog(...)
#define mylog(...)	fprintf (stderr, __VA_ARGS__)


typedef struct _Point{
	float	x;
	float	y;
} Point;

uint Z(float x, float y, uint iterations, Point *points);

#endif

