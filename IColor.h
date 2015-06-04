#ifndef ICOLOR_H
#define ICOLOR_H

#include "defs.h"

#include "RGB.h"

class IColor{
public:
	virtual ~IColor(){};

	virtual RGB *colorize(myint color, RGB *rgb, myint max) = 0;
};

#endif

