CC=gcc
CPPCHECK := cppcheck
cppcheck_flags := --enable=all --inconclusive --inline-suppr	\
		  --suppress=missingIncludeSystem --library=gnu \
		  --quiet
# Valgrind
valgrind_flags := --leak-check=full --show-leak-kinds=all	\
		  --track-origins=yes --verbose 		\
		  --log-file=valgrind-out.txt

PROG := prayer_time
EXEC := ./prayer_time
OBJS := main.o utils.o sun_position.o cal_prayer.o
CFLAGS=-Wall -O -g -lm

all: prayer_time

prayer_time: ${OBJS}
	$(CC) -o ${PROG} ${OBJS} $(CFLAGS)
	
clean:
	rm -f *.o
	rm -f valgrind-out.txt

mrproper: clean
	rm -f ${PROG}

cppcheck:
	${CPPCHECK} ${cppcheck_flags} *.[ch] 

valgrind: prayer_time
	valgrind ${valgrind_flags} ${EXEC} -l 1 -L 1 > /dev/null 2>&1
