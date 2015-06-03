#include <stdlib.h>	// malloc, free
#include <string.h>	// memset

#include "Bitmap.h"

Bitmap::Bitmap(myint size, float vsize, float vcorrection){
	myint size2;
	size2 = size / 2;
	size  = size2 * 2;
	
	// increase once, because Y-values are from -2 to  0 inclusive
	++size2;
	// increase once, because X-values are from -2 to +2 inclusive
	++size;

	this->_size2		= size2;
	this->_size		= size;

	this->_res		= vsize / size;
	this->_resBack		= size / vsize;
	
	this->_vcorrection	= vcorrection;
	
	_bmpAlloc();
}

Bitmap::~Bitmap(){
	free(_bmp);
}

myint Bitmap::getPixel(myint x, myint y) const{
	if (y >= _size2)
		y = _size - y;
	
	if (x >= _size || y >= _size)
		return 0;

	myint pos = _bmpPos(x, y);

	return _bmp[pos];
}

void Bitmap::putPixel(myint x, myint y, myint _ignoreIt){
	if (y >= _size2)
		y = _size - y;

	if (x >= _size || y >= _size)
		return;

	myint pos = _bmpPos(x, y);

	myint val = ++(_bmp[pos]);

	if (val > _bmpHitcount)
		_bmpHitcount = val;
}

void Bitmap::putVPixel(float fx, float fy, myint value){
	myint x = _convertVirtual(fx);
	myint y = _convertVirtual(fy);
	
	putPixel(x, y, value);
}

// =====================

void Bitmap::_bmpAlloc(){
	size_t size = _bmpSize();

	_bmp = (hitcount *) malloc(size);

	if (_bmp == NULL){
		fprintf(stderr, "No memory for bitmap !!! :)");
		exit(1);
	}
}

inline size_t Bitmap::_bmpSize() const{
	return _size * _size2 * sizeof(hitcount);
}

void Bitmap::clear(){
	_bmpHitcount = 0;

	size_t size = _bmpSize();

	memset(_bmp, 0, size);
}

inline myint Bitmap::_bmpPos(myint x, myint y) const{
	return y * _size + x;
}

// =====================

inline myint Bitmap::_convertVirtual(float a) const{
	return (a - _vcorrection) * _resBack;
}

