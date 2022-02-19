CC=gcc

PROG= tests_suite
DIR_SRC= $(shell cd .. && pwd)
OBJS= tests_suite.o tests_utils.o tests_date.o
OBJS_SRC= ${DIR_SRC}/utils.o ${DIR_SRC}/date.o

CFLAGS= -Wall -O -g -lm -lcheck -lgcov

.PHONY: tests_suite
tests_suite: ${OBJS}
	$(CC) -o ${PROG} ${OBJS} ${OBJS_SRC} $(CFLAGS) && ./${PROG}

clean:
	rm -rf *.o

mrproper: clean
	rm -rf ${PROG}

