#ifndef COLOR_SQRT_H
#define COLOR_SQRT_H

#include "IColor.h"

class ColorSQRT : public IColor{
public:
	ColorSQRT();
	
	virtual RGB *colorize(myint color, RGB *rgb, myint max);
private:
	float _currentMaxSq;
	myint _currentMax;
	
	inline void _setCurrentMax(myint max);
};

#endif
