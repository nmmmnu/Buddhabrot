#include <stdint.h>
#include <stdio.h>
#include <string.h>	// memset
#include <stdlib.h>	// exit
#include <time.h>	// time for srand()

#define ITERATIONS	1024
#define LOOPS		(10 * 1000 * 1000)
#define SCREEN_SIZE	500

#define float	double
#define uint	unsigned int

#define mylog(...)

#define M_WIDTH		+4.0	/* -2 to +2 */
#define M_CORR		-2.0	/* M_WIDTH / 2 */
#define M_ESCAPE2	+4.0	/* 2^2 */

typedef struct _Point{
	float	x;
	float	y;
} Point;

typedef struct _Budabrot{
	uint	iterations;
	uint	loops;
//	uint	size2;
	uint	size;
	float	res;
	float	resBack;
	uint	*bmp;
	Point	*points;
	uint	pointsMax;
} Budabrot;

// =====================================

inline static uint _myrand(uint max);

// =====================================

static uint *bb_initBMP(uint sizex, uint sizey){
	size_t size = sizex * sizey  * sizeof(uint);

	uint *bmp = malloc(size);

	if (bmp == NULL){
		fprintf(stderr, "No memory for bitmap !!! :)");
		exit(1);
	}

	// no need to initialize them to zero here.
	memset(bmp, 0, size);

	return bmp;
}

static Point *bb_initPoints(uint sizex){
	size_t size = sizex * sizeof(Point);

	Point *px = malloc(size);

	if (px == NULL){
		fprintf(stderr, "No memory for points vector !!! :)");
		exit(1);
	}

	// no need to initialize them to zero.

	return px;
}

static Budabrot *bb_init(Budabrot *bb, uint loops, uint iterations, uint screenSize){
//	screenSize	= (screenSize >> 1) << 1;

	bb->iterations	= iterations;
	bb->loops	= loops;

	bb->size	= screenSize;
//	bb->size2	= (screenSize >> 1) + 1; // +1 is for zero "row"

	bb->res		= M_WIDTH / screenSize;
	bb->resBack	= screenSize / M_WIDTH;

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
	if (bb->points[index].x == 0 && bb->points[index].y == 0)
		return;

	uint x = convertBw(bb, bb->points[index].x);
	uint y = convertBw(bb, bb->points[index].y);

	// for speed we are calculating half y size,
	// so we bring it on the simetrical point.
	//if (y > bb->size2)
	//	y = bb->size - y;

	uint pos = y * bb->size + x;

	uint val = ++(bb->bmp[pos]);

	mylog("\t\t%5u x %5u = %5u of %5u\n", x, y, val, bb->pointsMax);

	if (val > bb->pointsMax)
		bb->pointsMax = val;
}

static uint Z(Budabrot *bb, float x, float y){
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

static int bb_loop(Budabrot *bb){
	uint x = _myrand(bb->size);
	uint y = _myrand(bb->size);

	float xf = convertFw(bb, x);
	float yf = convertFw(bb, y);

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

	uint loops;
	for(loops = 0; loops < bb->loops;)
		loops = loops + bb_loop(bb);
}

static void bb_output(const Budabrot *bb){
	FILE *F = stdout;

	fprintf(F, "P2\n");
	fprintf(F, "%u %u\n", bb->size, bb->size);
	fprintf(F, "%u\n", bb->pointsMax);

	uint x, y;
	for(x = 0; x < bb->size; ++x){
		for(y = 0; y < bb->size; ++y){
			fprintf(F, "%5u ", bb_getPixel(bb, x, y));
		}

		printf("\n");
	}
}

int main(){
	srand(time(NULL));

	Budabrot bb_pl;
	Budabrot *bb = bb_init(& bb_pl, LOOPS, ITERATIONS, SCREEN_SIZE);

	bb_generate(bb);
	bb_output(bb);

	free(bb->bmp);
	free(bb->points);

	return 0;
}

// =====================================

inline static uint _myrand(uint max){
	return rand() / (float) RAND_MAX * (max - 1);
}

