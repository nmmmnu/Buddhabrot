#include "ColorLinear.h"

class ColorLinear : public IColor{
public:
	virtual RGB *colorize(myint color, RGB *rgb, myint max);
};

IColor *FColorLinear(){
	return new ColorLinear();
}

// =======================

RGB *ColorLinear::colorize(myint color, RGB *rgb, myint max){
	return RGBManipulator::make(color, max, rgb);
}

