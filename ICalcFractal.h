#ifndef CALC_FRACTAL_H
#define CALC_FRACTAL_H

#include "defs.h"

class ICalcFractal{
public:
	virtual ~ICalcFractal(){};

	virtual myint Z(float x, float y, myint iterations, Point *points = NULL) = 0;
};

#endif

