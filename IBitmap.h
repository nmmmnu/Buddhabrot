#ifndef IBITMAP_H
#define IBITMAP_H

#include "defs.h"

typedef uint32_t hitcount;

class IBitmap{
public:
	virtual ~IBitmap(){};

	virtual void setVSize(float vsize, float vcorrection = 0) = 0;

	virtual void  clear() = 0;

	virtual myint getPixel(myint x, myint y) const = 0;
	virtual void  putPixel(myint x, myint y, myint value) = 0;
	virtual void  putVPixel(float fx, float fy, myint value) = 0;

	virtual hitcount getMaxHitcount() const = 0;
	virtual myint getSize() const = 0;
};

#endif
