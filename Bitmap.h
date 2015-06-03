#ifndef BITMAP_H
#define BITMAP_H

#include "IBitmap.h"

class Bitmap : public IBitmap{
public:
	Bitmap(myint size, float vsize, float vcorrection);
	virtual ~Bitmap();
	
	virtual void clear();

	virtual myint getPixel(myint x, myint y) const;
	virtual void  putPixel(myint x, myint y, myint _ignoreIt);
	virtual void  putVPixel(float fx, float fy, myint _ignoreIt);
	
	virtual hitcount getMaxHitcount() const{
		return _bmpHitcount;
	};
	
	virtual myint getSize() const{
		return _size;
	};

private:
	void _bmpAlloc();

	inline size_t _bmpSize() const;
	
	inline myint _bmpPos(myint x, myint y) const;
	
	inline myint _convertVirtual(float a) const;
	inline myint _convertVirtual2(float a) const;

private:
	myint _size;
	myint _size2;

	float _res;
	float _resBack;

	float _vcorrection;
	
private:
	hitcount *_bmp;
	hitcount  _bmpHitcount;
};


#endif

