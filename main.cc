#include "defs.h"

#include "BuddhaBrot.h"
#include "CalcMandelbrot.h"
#include "ColorLinear.h"
#include "Bitmap.h"

#define ITERATIONS	2000
#define SCREEN_SIZE	760
#define POINT_STEP	0.001

static BuddhaBrot *factory(){
	ICalcFractal *calc	= FCalcMandelbrot();
	IBitmap *bitmap		= FBitmap(SCREEN_SIZE);
	IColor *color		= FColorLinear();

	return new BuddhaBrot(calc, bitmap, color, ITERATIONS, POINT_STEP);
}

int main(){
	BuddhaBrot *bb = factory();

	bb->generate();
	bb->output();

	delete(bb);

	return 0;
}
