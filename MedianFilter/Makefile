INCLUDE_DIRS = 
LIB_DIRS = 
CC = gcc

CDEFS=
CFLAGS= -O0 $(INCLUDE_DIRS) $(CDEFS)
CFLAGS= -O0 -msse3 -malign-double $(INCLUDE_DIRS) $(CDEFS)
CFLAGS= -O2 -msse3 -malign-double $(INCLUDE_DIRS) $(CDEFS)
CFLAGS= -O3 $(INCLUDE_DIRS) $(CDEFS)
CFLAGS= -O3 -mssse3 $(INCLUDE_DIRS) $(CDEFS)
LIBS=-lpthread

PRODUCT=median

HFILES=
CFILES= median.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

${PRODUCT}:	${OBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
