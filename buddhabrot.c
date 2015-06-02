// thank you Melinda Green :o)

#include <stdint.h>
#include <stdio.h>
#include <string.h>	// memset
#include <stdlib.h>	// exit
#include <math.h>

#define ITERATIONS		2000
#define HALF_SCREEN_SIZE	(600 / 2)

#define colorize		colorizeLine

#define RGBMAX			0xFF

#define float	double
#define uint	unsigned int

#define mylog(...)
//#define mylog(...)	fprintf (stderr, __VA_ARGS__)

#define M_WIDTH2	+2.0	/* -2 to +2 */
#define M_WIDTH		+4.0	/* -2 to +2 */
#define M_CORR		-2.0	/* M_WIDTH / 2 */
#define M_ESCAPE2	+4.0	/* 2^2 */

typedef struct _Point{
	float	x;
	float	y;
} Point;

typedef struct _Budabrot{
	uint	iterations;
	uint	size;
	uint	size2;
	float	res;
	float	resBack;
	uint	*bmp;
	Point	*points;
	uint	pointsMax;
} Budabrot;

// =====================================

static uint *bb_initBMP(uint sizex, uint sizey){
	size_t size = sizex * sizey * sizeof(uint);

	uint *bmp = malloc(size);

	if (bmp == NULL){
		fprintf(stderr, "No memory for bitmap !!! :)");
		exit(1);
	}

	// no need to initialize them to zero here.
	memset(bmp, 0, size);

	return bmp;
}

static Point *bb_initPoints(uint size){
	Point *px = malloc(size * sizeof(Point));

	if (px == NULL){
		fprintf(stderr, "No memory for points vector !!! :)");
		exit(1);
	}

	// no need to initialize them to zero.

	return px;
}

static Budabrot *bb_init(Budabrot *bb, uint iterations, uint halfScreenSize){
	uint screenSize	= halfScreenSize * 2;

	++halfScreenSize;
	++screenSize;

	bb->iterations	= iterations;

	bb->size	= screenSize;
	bb->size2	= halfScreenSize;

	bb->res		= M_WIDTH / screenSize;
	bb->resBack	= screenSize / M_WIDTH;

	// increase to make it even - for center point (0,0)
	bb->bmp		= bb_initBMP(bb->size, bb->size);
	bb->points	= bb_initPoints(bb->iterations);

	bb->pointsMax	= 0;

	return bb;
}

inline static float convertFw(const Budabrot *bb, uint a){
	return bb->res * a + M_CORR;
}

inline static uint convertBw(const Budabrot *bb, float a){
	return (int) ((a - M_CORR) * bb->resBack);
}

inline static uint bb_getPixel(const Budabrot *bb, uint x, uint y){
	uint pos = y * bb->size + x;

	return bb->bmp[pos];
}

static void bb_putPixel(Budabrot *bb, uint index){
	// skip point (0, 0)
	if (index == 0)
		return;

	if (bb->points[index].x == 0.00 && bb->points[index].y == 0)
		return;

	uint x = convertBw(bb, bb->points[index].x);
	uint y = convertBw(bb, bb->points[index].y);

	uint pos = y * bb->size + x;

	//fprintf(stderr, "\t\t%5u x %5u = %5u (size = %5u x %5u = %5u)\n", x, y, pos,  bb->size, bb->size2, bb->size * bb->size2);

	uint val = ++(bb->bmp[pos]);

	mylog("\t\t%5u x %5u = %5u of %5u\n", x, y, val, bb->pointsMax);

	if (val > bb->pointsMax)
		bb->pointsMax = val;
}

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

static uint Z(Budabrot *bb, float x, float y){
	if (Z_MTest(x, y))
		return bb->iterations;

	float zr = 0;
	float zi = 0;

	uint i;
	for(i = 0; i < bb->iterations; ++i){
		float zr2 = zr * zr;
		float zi2 = zi * zi;

		if (zr2 + zi2 > M_ESCAPE2)
			return i;

		bb->points[i].x = zr;
		bb->points[i].y = zi;

		// z = z*z + c

		zi = 2 * zr * zi + y;
		zr = zr2 - zi2 + x;
	}

	return i;
}

static int bb_loop(Budabrot *bb, float xf, float yf){
	uint it = Z(bb, xf, yf);

	if (it == bb->iterations)
		return 0;

	mylog("escapes after %5u\n", it);

	// begin plot points
	uint i;
	for (i = 0; i < it; ++i){
		mylog("\tplot %5u -> %8.5f x %8.5f\n", i, bb->points[i].x, bb->points[i].y);
		bb_putPixel(bb, i);
	}

	return 1;
}

static void bb_generate(Budabrot *bb){
	//bb->pointsMax = 0;
	//memset(bb->bmp, 0, size);

	static const float step = 0.0005;

	float xf, yf;
	for(xf = - M_WIDTH2; xf < M_WIDTH2; xf += step){
		for(yf = - M_WIDTH2; yf < 0; yf += step)
			bb_loop(bb, xf, yf);

		fprintf(stderr, "x = %8.4f\r", xf);
	}

	fprintf(stderr, "\n");
}

/*
inline static int colorizeComp(uint color, float pMin, float pMax){
	if (color < pMin || color > pMax)
		return 0;

	uint a = color / pMax * RGBMAX;

	return a > RGBMAX ? RGBMAX : a;
}
*/

inline static void colorizeLine(FILE *F, uint color, uint max){
	uint a = color / (float) max * RGBMAX;

	fprintf(F, "%5u %5u %5u ", a, a, a);
}

inline static void colorizeSqr(FILE *F, uint color, uint max){
	static int mem_max = 0;
	static float mem_sqr = 0;

	if (mem_max != max){
		mem_max = max;
		mem_sqr = sqrt(max);

		mylog(stderr, "sqrt updated...\n");
	}

	uint a = sqrt(color) / mem_sqr  * RGBMAX;

	fprintf(F, "%5u %5u %5u ", a, a, a);
}

static void bb_output(const Budabrot *bb){
	FILE *F = stdout;

	fprintf(F, "P3\n");
	fprintf(F, "%u %u\n", bb->size, bb->size);
	fprintf(F, "%u\n", RGBMAX);

	uint x, y;
	for(x = 0; x < bb->size; ++x){
		for(y = 0; y < bb->size2; ++y){
			colorize(F, bb_getPixel(bb, x, y), bb->pointsMax);
		}

		for(y = bb->size2 - 1; y > 0; --y){
			colorize(F, bb_getPixel(bb, x, y - 1), bb->pointsMax);
		}

		printf("\n");
	}
}

int main(){
	Budabrot bb_pl;
	Budabrot *bb = bb_init(& bb_pl, ITERATIONS, HALF_SCREEN_SIZE);

	bb_generate(bb);
	bb_output(bb);

	free(bb->bmp);
	free(bb->points);

	return 0;
}

