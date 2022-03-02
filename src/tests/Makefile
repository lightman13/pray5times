CC=gcc

PROG= tests_suite
DIR_SRC= $(shell cd .. && pwd)
OBJS= tests_suite.o tests_utils.o tests_date.o tests_sun_position.o \
      tests_cal_prayer.o
OBJS_SRC= ${DIR_SRC}/utils.o ${DIR_SRC}/date.o ${DIR_SRC}/sun_position.o \
	  ${DIR_SRC}/cal_prayer.o

CFLAGS= -Wall -O -g -lm -lcheck -lgcov

.PHONY: tests_suite
tests_suite: ${OBJS}
	$(CC) -o ${PROG} ${OBJS} ${OBJS_SRC} $(CFLAGS) && ./${PROG}

clean:
	rm -rf *.o
	rm -f *.tap

mrproper: clean
	rm -rf ${PROG}

