#include <math.h>

#include "ColorSQRT.h"

class ColorSQRT : public IColor{
public:
	ColorSQRT(){
		_currentMax = 0;
	}

	virtual RGB *colorize(myint color, RGB *rgb, myint max);
private:
	float _currentMaxSq;
	myint _currentMax;

	inline void _setCurrentMax(myint max);
};

IColor *FColorSQRT(){
	return new ColorSQRT();
}

// =================

RGB *ColorSQRT::colorize(myint color, RGB *rgb, myint max){
	if (_currentMax != max)
		_setCurrentMax(max);

	float colorSq = sqrt(color);

	return RGBManipulator::make(colorSq, _currentMaxSq, rgb);
}

inline void ColorSQRT::_setCurrentMax(myint max){
	_currentMax   = max;
	_currentMaxSq = sqrt(max);
}
