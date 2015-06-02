MYCC	= clang
MYCC	= gcc

CC	= $(MYCC) -c -Wall
#-O9
LINK	= $(MYCC) -o
LIBS	= -lm
#-lquadmath

TARGETS = buddhabrot


all: $(TARGETS)


clean:
	rm -f *.o $(TARGETS)


buddhabrot.o:	buddhabrot.c
	$(CC)		buddhabrot.c

buddhabrot:			buddhabrot.o
	$(LINK) buddhabrot	buddhabrot.o	$(LIBS)
