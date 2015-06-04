#ifndef RGB_MANIPULATOR_H
#define RGB_MANIPULATOR_H

#include "defs.h"

struct RGB{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
};

class RGBManipulator{
public:
	static const myint MAX_COLOR = 0xFF;

public:
	static RGB *make(myint a,			myint max, RGB *rgb);
	static RGB *make(myint r, myint g, myint b,	myint max, RGB *rgb);

private:
	inline static myint _calcMax(myint a, myint max);
};

#endif
