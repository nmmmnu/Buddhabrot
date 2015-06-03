#ifndef FRACTAL_CALCULATOR_H
#define FRACTAL_CALCULATOR_H

#include <stdint.h>
#include <stdio.h>

#define float double

typedef uint32_t myint;

struct Point{
	float	x;
	float	y;
};

struct RGB{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
};

//#define mylog(...)
#define mylog(...)	fprintf (stderr, __VA_ARGS__)

#endif
