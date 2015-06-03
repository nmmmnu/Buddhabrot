#include "CalcMandelbrot.h"

myint CalcMandelbrot::Z(float x, float y, myint iterations, Point *points){
	if (_testZ(x, y))
		return iterations;

	float zr = 0;
	float zi = 0;

	myint i;
	for(i = 0; i < iterations; ++i){
		float zr2 = zr * zr;
		float zi2 = zi * zi;

		if (zr2 + zi2 > M_ESCAPE2)
			return i;

		// save current points for later use...
		if (points){
			points[i].x = zr;
			points[i].y = zi;
		}
		
		// calc next Z

		// z = z*z + c

		zi = 2 * zr * zi + y;
		zr = zr2 - zi2 + x;
	}

	return i;
}

bool CalcMandelbrot::_testZ(float x, float y){
	if (_speedup == false)
		return false;

	/*
	Bulb + Cardioid	= 10 sec
	Cardioid only	= 18 sec
	Bulb only	= 60 sec
	no tests	= 66 sec
	*/

	// Bulb test
	float y2 = y * y;

	float bt = (x + 1) * (x + 1) + y2;

	if (bt < 0.0625)	// 0.0625 = 1/16
		return true;


	// Cardioid test, without SQRT
	float x4 = x - 0.25;	// 0.25 = 1/4

	//float y2 = y * y;

	float q = x4 * x4 + y2;

	if (q * (q + x4) < 0.25 * y2)
		return true;


	// Ok...
	return false;
}


