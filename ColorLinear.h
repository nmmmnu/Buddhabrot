#ifndef COLOR_LINEAR_H
#define COLOR_LINEAR_H

#include "IColor.h"

class ColorLinear : public IColor{
public:
	virtual RGB *colorize(myint color, RGB *rgb, myint max);
};

#endif
