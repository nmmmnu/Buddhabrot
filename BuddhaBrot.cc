#include <stdio.h>	// printf, in C++ ?? :)
#include <stdlib.h>	// malloc, free
#include <string.h>	// memset

#include "BuddhaBrot.h"

BuddhaBrot::BuddhaBrot(ICalcFractal *calc, IBitmap *bitmap, IColor *color, myint iterations, float step){
	this->_calc		= calc;
	this->_bitmap		= bitmap;
	this->_color		= color;

	this->_iterations	= iterations;
	this->_step		= step;

	_pointsAlloc();

	this->_bitmap->setVSize(M_WIDTH, M_CORRECTION);
}

BuddhaBrot::~BuddhaBrot(){
	delete(this->_calc);

	delete(this->_bitmap);

	free(this->_points);
}

void BuddhaBrot::generate(){
	_bitmap->clear();

	float xf, yf;
	for(yf = - M_WIDTH2; yf <= 0; yf += _step)
		for(xf = - M_WIDTH2; xf <= M_WIDTH2; xf += _step){
			_calculateEscape(xf, yf);

		_printProgress(yf, 0.0);
	}

	_printProgress(100.0, 100.0, true);
}

bool BuddhaBrot::_calculateEscape(float xf, float yf){
	uint it = _calc->Z(xf, yf, _iterations, _points);

	// if it escapes equal to iterations,
	// then point is bounded
	if (it == _iterations)
		return false;

	// if it escapes on 0 iteration,
	// then point is escaped outside the circle
	if (it == 0)
		return true;

	// begin plot points
	uint i;
	for (i = 0; i < it; ++i){
		const Point p = _points[i];

		// skip point (0, 0)
		if (p.x > - _step && p.x < + _step && p.y > - _step && p.y < + _step)
			continue;

		_bitmap->putVPixel(p.x, p.y, it);
	}

	return true;
}

void BuddhaBrot::output() const{
	static FILE *F = stdout;

	RGB rgb2;

	myint size = _bitmap->getSize();

	fprintf(F, "P3\n");
	fprintf(F, "%u %u\n", size, size);
	fprintf(F, "%u\n", RGBManipulator::MAX_COLOR);

	myint x, y;
	for(x = 0; x < size; ++x){
		for(y = 0; y < size; ++y){
			myint c = _bitmap->getPixel(x, y);
			RGB *rgb = _color->colorize(c, & rgb2, _bitmap->getMaxHitcount());
			_outputRGB(rgb);
		}

		printf("\n");
	}

	printf("hitcount - %u\n", _bitmap->getMaxHitcount());
}

inline void BuddhaBrot::_outputRGB(RGB *rgb) const{
	static FILE *F = stdout;

	fprintf(F, "%5u %5u %5u ", rgb->r, rgb->g, rgb->b);
}

// =========================

void BuddhaBrot::_pointsAlloc(){
	size_t size = _iterations * sizeof(Point);

	_points = (Point *) malloc(size);

	if (_points == NULL){
		fprintf(stderr, "No memory for points vector !!! :)");
		exit(1);
	}

	// no need to initialize them to zero,
	// but lets do it for Valgring
	memset(_points, 0, size);
}

void BuddhaBrot::_printProgress(float p, float total, bool nl){
	static const char *PMASK = "Progressing: %8.4f of %8.4f %s";

	const char *t = nl ? "\n" : "\r";

	fprintf(stderr, PMASK, p, total, t);
}

