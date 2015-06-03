#include "RGBManipulator.h"

RGB *RGBManipulator::make(myint a,			myint max, RGB *rgb){
	myint aa = _calcMax(a, max);
	
	rgb->r = aa;
	rgb->g = aa;
	rgb->b = aa;
	
	return rgb;
}

RGB *RGBManipulator::make(myint r, myint g, myint b,	myint max, RGB *rgb){
	rgb->r = _calcMax(r, max);
	rgb->g = _calcMax(g, max);
	rgb->b = _calcMax(b, max);
	
	return rgb;
}

inline myint RGBManipulator::_calcMax(myint a, myint max){
	if (a > max)
		a = max;
	
	// over optimization ?
	if (max == MAX_COLOR)
		return a;
	
	return a / (float) max * MAX_COLOR;
}
