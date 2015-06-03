#include "defs.h"

#include "BuddhaBrot.h"
#include "CalcMandelbrot.h"
#include "ColorLinear.h"

#define ITERATIONS	1000
#define SCREEN_SIZE	500
#define POINT_STEP	0.01

BuddhaBrot *factory(){
	ICalcFractal *calc	= (ICalcFractal *)	new CalcMandelbrot();
	IColor *color		= (IColor *)		new ColorLinear();

	return new BuddhaBrot(calc, color, ITERATIONS, SCREEN_SIZE, POINT_STEP);
}

int main(){	
	BuddhaBrot *bb = factory();

	bb->generate();
	bb->output();

	delete(bb);
	
	return 0;
}
