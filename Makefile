MYCC	= g++
#MYCC	= clang
#MYCC	= gcc

CC	= $(MYCC) -c -Wall
#-O9
LINK	= $(MYCC) -o
LIBS	= -lm
#-lquadmath

TARGETS = buddhabrot


all: $(TARGETS)


clean:
	rm -f *.o $(TARGETS)


buddhabrot.o:	buddhabrot.c buddhabrot_params.h mandelbrot.h
	$(CC)		buddhabrot.c

mandelbrot.o:	mandelbrot.c mandelbrot.h
	$(CC)		mandelbrot.c


buddhabrot:			buddhabrot.o mandelbrot.o
	$(LINK) buddhabrot	buddhabrot.o mandelbrot.o	$(LIBS)
