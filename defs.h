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

//#define mylog(...)
#define mylog(...)	fprintf (stderr, __VA_ARGS__)

#endif
