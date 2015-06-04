#ifndef BUDDHABROT_H
#define BUDDHABROT_H

#include "defs.h"

#include "ICalcFractal.h"
#include "IColor.h"
#include "IBitmap.h"

class BuddhaBrot{
public:
	BuddhaBrot(ICalcFractal *calc, IBitmap *bitmap, IColor *color, myint iterations, float step);
	virtual ~BuddhaBrot();

	void generate();
	void output() const;

private:
	void _pointsAlloc();

	bool _calculateEscape(float xf, float yf);

	void _printProgress(float p, float total, bool nl = false);

	inline void _outputRGB(RGB *rgb) const;

protected:
	static const float M_WIDTH	= 4;
	static const float M_WIDTH2	= 2;
	static const float M_CORRECTION	= -2;

private:
	ICalcFractal	*_calc;
	IColor		*_color;

	myint		_iterations;
	float		_step;

	IBitmap		*_bitmap;
	Point		*_points;
};

#endif

