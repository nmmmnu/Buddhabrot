MYCC	= g++

CC	= $(MYCC) -c -Wall
#-O9
LINK	= $(MYCC) -o
LIBS	= -lm
#-lquadmath


TARGETS = buddhabrot


all: $(TARGETS)


clean:
	rm -f *.o $(TARGETS)


buddhabrot:			main.o BuddhaBrot.o CalcMandelbrot.o Bitmap.o RGB.o ColorLinear.o ColorSQRT.o
	$(LINK) buddhabrot	main.o BuddhaBrot.o CalcMandelbrot.o Bitmap.o RGB.o ColorLinear.o ColorSQRT.o

main.o: main.cc	BuddhaBrot.h Bitmap.h CalcMandelbrot.h ColorLinear.h defs.h
	$(CC) main.cc


BuddhaBrot.o: BuddhaBrot.cc BuddhaBrot.h ICalcFractal.h IBitmap.h RGB.h IColor.h defs.h
	$(CC) BuddhaBrot.cc

CalcMandelbrot.o: CalcMandelbrot.cc CalcMandelbrot.h ICalcFractal.h defs.h
	$(CC) CalcMandelbrot.cc

Bitmap.o: Bitmap.cc Bitmap.h IBitmap.h defs.h
	$(CC) Bitmap.cc

RGB.o: RGB.cc RGB.h defs.h
	$(CC) RGB.cc

ColorLinear.o: ColorLinear.cc ColorLinear.h IColor.h RGB.h defs.h
	$(CC) ColorLinear.cc

ColorSQRT.o: ColorSQRT.cc ColorSQRT.h IColor.h RGB.h defs.h
	$(CC) ColorSQRT.cc


