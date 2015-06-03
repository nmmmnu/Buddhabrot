#ifndef CALC_MANDELBROT_H
#define CALC_MANDELBROT_H

#include "ICalcFractal.h"

class CalcMandelbrot : public ICalcFractal{
private:
	static const float M_ESCAPE2 = 4;	// 2 ^ 2

public:
	CalcMandelbrot(bool speedup = true){
		this->_speedup = speedup;
	}
	
	virtual myint Z(float x, float y, myint iterations, Point *points = NULL);

private:
	bool _speedup;				// Whatever to use bulb checking or not
	
	bool _testZ(float x, float y);
};

#endif

