CC=gcc
CPPCHECK := cppcheck
cppcheck_flags := --enable=all --inconclusive --inline-suppr	\
		  --suppress=missingIncludeSystem --library=gnu \
		  --quiet

PROG := prayer_time
OBJS := main.o utils.o sun_position.o cal_prayer.o
CFLAGS=-Wall -O -g -lm

all: prayer_time

prayer_time: ${OBJS}
	$(CC) -o ${PROG} ${OBJS} $(CFLAGS)
	
clean:
	rm -f *.o

mrproper: clean
	rm -f ${PROG}

cppcheck:
	${CPPCHECK} ${cppcheck_flags} *.[ch] 
