#include <stdlib.h>	// malloc, free
#include <string.h>	// memset

#include "Bitmap.h"

class Bitmap : public IBitmap{
public:
	Bitmap(myint size);
	virtual ~Bitmap();

	virtual void setVSize(float vsize, float vcorrection = 0);

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

IBitmap * FBitmap(myint size){
	return new Bitmap(size);
}

// ==============================

Bitmap::Bitmap(myint size){
	myint size2;
	size2 = size / 2;
	size  = size2 * 2;

	// increase once, because Y-values are from -2 to  0 inclusive
	++size2;
	// increase once, because X-values are from -2 to +2 inclusive
	++size;

	this->_size2		= size2;
	this->_size		= size;

	setVSize(100);

	_bmpAlloc();
}

void Bitmap::setVSize(float vsize, float vcorrection){
	this->_res		= vsize / this->_size;
	this->_resBack		= this->_size / vsize;

	this->_vcorrection	= vcorrection;
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

