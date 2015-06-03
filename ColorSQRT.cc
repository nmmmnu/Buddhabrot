#include <math.h>

#include "ColorSQRT.h"
#include "RGBManipulator.h"

ColorSQRT::ColorSQRT(){
	_currentMax = 0;
}

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
