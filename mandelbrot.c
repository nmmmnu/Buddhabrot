#include "mandelbrot.h"

#define M_ESCAPE2	4	/* 2^2 */

static int Z_MTest(float x, float y);

// ====================================

uint Z(float x, float y, uint iterations, Point *points){
	if (Z_MTest(x, y))
		return iterations;

	float zr = 0;
	float zi = 0;

	uint i;
	for(i = 0; i < iterations; ++i){
		float zr2 = zr * zr;
		float zi2 = zi * zi;

		if (zr2 + zi2 > M_ESCAPE2)
			return i;

		// save current points for later use...
		points[i].x = zr;
		points[i].y = zi;

		// calc next Z

		// z = z*z + c

		zi = 2 * zr * zi + y;
		zr = zr2 - zi2 + x;

	}

	return i;
}

// ====================================

/*
Bulb + Cardioid	= 10 sec
Cardioid only	= 18 sec
Bulb only	= 60 sec
no tests	= 66 sec
*/
static int Z_MTest(float x, float y){
	// Bulb test
	float y2 = y * y;

	float bt = (x + 1) * (x + 1) + y2;

	if (bt < 0.0625) // 0.0625 = 1/16
		return 1;

	// Cardioid test, without SQRT
	float x4 = x - 0.25; // 0.25 = 1/4

	//float y2 = y * y;

	float q = x4 * x4 + y2;

	if (q * (q + x4) < 0.25 * y2)
		return 2;


	// Ok...
	return 0;
}

