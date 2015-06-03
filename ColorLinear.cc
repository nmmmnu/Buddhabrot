#include "ColorLinear.h"
#include "RGBManipulator.h"

RGB *ColorLinear::colorize(myint color, RGB *rgb, myint max){
	return RGBManipulator::make(color, max, rgb);
}

