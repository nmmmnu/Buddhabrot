// thank you Melinda Green :o)

#include <stdint.h>
#include <stdio.h>
#include <string.h>	// memset
#include <stdlib.h>	// exit
#include <math.h>	// sqrt

#include "mandelbrot.h"
#include "buddhabrot_params.h"

#define colorize	colorizeLine

#define RGBMAX		0xFF

typedef uint32_t	hitcount;

#define M_WIDTH		+4.0	/* -2 to +2 */
#define M_WIDTH2	+2.0	/* -2 to 0 */
#define M_CORRECTION	-2.0	/* M_WIDTH / 2 */

typedef struct _Budabrot{
	uint		iterations;
	uint		size;
	uint		size2;
	float		res;
	float		resBack;
	hitcount	*bmp;
	hitcount	bmpMaxHits;
	Point		*points;
} Budabrot;

// =====================================

inline static size_t bb_bmpsize(Budabrot *bb);
inline static void bb_clr(Budabrot *bb);

static Budabrot *bb_init(Budabrot *bb, uint iterations, uint halfScreenSize);

// =====================================

inline static void colorizeLine(FILE *F, uint color, uint max);
inline static void colorizeSqrt(FILE *F, uint color, uint max);

// =====================================

inline static uint bb_m2scr(const Budabrot *bb, float a){
	return (int) ((a - M_CORRECTION) * bb->resBack);
}

inline static uint bb_m2scr2(const Budabrot *bb, float a){
	uint result = bb_m2scr(bb, a);

	return (result >= bb->size2) ? bb->size - result : result;
}

inline static uint bb_getpx(const Budabrot *bb, uint x, uint y){
	uint pos = y * bb->size + x;

	return bb->bmp[pos];
}

static void bb_putpx(Budabrot *bb, uint index){
	// skip central point
	if (bb->points[index].x == 0 && bb->points[index].y == 0)
		return;

	uint x = bb_m2scr(bb, bb->points[index].x);
	uint y = bb_m2scr2(bb, bb->points[index].y);

	if (y >= bb->size2)
		return;

	uint pos = y * bb->size + x;

	//mylog("Converted coordinates: %5u x %5u\n", x, y);

	uint val = ++(bb->bmp[pos]);

	if (val > bb->bmpMaxHits)
		bb->bmpMaxHits = val;
}

static int bb_escape(Budabrot *bb, float xf, float yf){
	uint it = Z(xf, yf, bb->iterations, bb->points);

	if (it == bb->iterations)
		return 0;

	// if it escapes on 0 iteration,
	// then point is outside the circle
	if (it > 0){
		//mylog("Point Plot Start...\n");

		// begin plot points
		uint i;
		for (i = 0; i < it; ++i){
		//	mylog("Iterations: %5u, Coordinates: %8.4f x %8.4f\n", i, bb->points[i].x, bb->points[i].y);
			bb_putpx(bb, i);
		}

		//mylog("Point Plot End...\n");
	}

	return 1;
}

static void bb_generate(Budabrot *bb){
	static const char *PMASK = "Progressing: %8.4f of %8.4f %s";

	bb_clr(bb);

	float xf, yf;
	for(yf = - M_WIDTH2; yf <= 0; yf += POINT_STEP)
		for(xf = - M_WIDTH2; xf <= M_WIDTH2; xf += POINT_STEP){
			bb_escape(bb, xf, yf);

		fprintf(stderr, PMASK, yf, 0.0, "\r");
	}

	fprintf(stderr, PMASK, 100.0, 100.0, "\n");
}

static void bb_output(const Budabrot *bb){
	FILE *F = stdout;

	fprintf(F, "P3\n");
	fprintf(F, "%u %u\n", bb->size, bb->size);
	fprintf(F, "%u\n", RGBMAX);

	uint x, y;
	for(x = 0; x < bb->size; ++x){
		for(y = 0; y < bb->size2; ++y){
			colorize(F, bb_getpx(bb, x, y - 0), bb->bmpMaxHits);
		}

		for(y = bb->size2 - 1; y > 0; --y){
			colorize(F, bb_getpx(bb, x, y - 1), bb->bmpMaxHits);
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

// ==================================

inline static size_t bb_bmpsize(Budabrot *bb){
	return bb->size * bb->size2 * sizeof(hitcount);
}

inline static void bb_clr(Budabrot *bb){
	bb->bmpMaxHits = 0;

	size_t size = bb_bmpsize(bb);

	memset(bb->bmp, 0, size);
}

static void bb_allocbmp(Budabrot *bb){
	size_t size = bb_bmpsize(bb);

	hitcount *bmp = (hitcount *) malloc(size);

	if (bmp == NULL){
		fprintf(stderr, "No memory for bitmap !!! :)");
		exit(1);
	}

	bb->bmp = bmp;
}

static void bb_allocpoints(Budabrot *bb){
	size_t size = bb->iterations * sizeof(Point);

	Point *points = (Point *) malloc(size);

	if (points == NULL){
		fprintf(stderr, "No memory for points vector !!! :)");
		exit(1);
	}

	// no need to initialize them to zero.
	memset(points, 0, size);

	bb->points = points;
}

static Budabrot *bb_init(Budabrot *bb, uint iterations, uint halfScreenSize){
	uint screenSize	= halfScreenSize * 2;

	// increase once, because of -2 to  0 inclusive
	++halfScreenSize;
	// increase once, because of -2 to +2 inclusive
	++screenSize;

	bb->iterations	= iterations;

	bb->size	= screenSize;
	bb->size2	= halfScreenSize;

	bb->res		= M_WIDTH / screenSize;
	bb->resBack	= screenSize / M_WIDTH;

	bb_allocbmp(bb);
	bb_allocpoints(bb);

	bb->bmpMaxHits	= 0;

	return bb;
}

// =============================

inline static void colorizeLine(FILE *F, uint color, uint max){
	uint a = color / (float) max * RGBMAX;

	fprintf(F, "%5u %5u %5u ", a, a, a);
//	fprintf(F, "%5u ", a);
}

inline static void colorizeSqrt(FILE *F, uint color, uint max){
	static uint mem_max = 0;
	static float mem_sqr = 0;

	if (mem_max != max){
		mem_max = max;
		mem_sqr = sqrt(max);

		mylog("sqrt updated...\n");
	}

	uint a = sqrt(color) / mem_sqr  * RGBMAX;

	fprintf(F, "%5u %5u %5u ", a, a, a);
//	fprintf(F, "%5u ", a);
}
