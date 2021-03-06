CC=gcc
CPPCHECK := cppcheck
cppcheck_flags := --enable=all --inconclusive --inline-suppr	\
		  --suppress=missingIncludeSystem --library=gnu \
		  --quiet
# Valgrind
valgrind_flags := --leak-check=full --show-leak-kinds=all	\
		  --track-origins=yes --verbose 		\
		  --log-file=valgrind-out.txt

PROG := pray5times
MAN := pray5times.1
EXEC := ./pray5times
OBJS := main.o
SRC := main.c
override CFLAGS+=-Wall -Werror -O2 -g -lm -lpray5times
DIR_INSTALL := /usr/bin
DIR_MAN := /usr/share/man/man1

all: pray5times

pray5times: ${OBJS}
	$(CC) -o ${PROG} ${OBJS} ${CFLAGS}

.PHONY: install
install:
	install -m 755 ${PROG} ${DIR_INSTALL}
	install -m 755 ${MAN} ${DIR_MAN}

.PHONY: uninstall
uninstall:
	rm -rf ${DIR_INSTALL}/${PROG}
	rm -rf ${DIR_MAN}/${MAN}
clean:
	rm -f *.o
	rm -f valgrind-out.txt
	rm -f *.gcno
	rm -f *.gcda
	rm -rf report-html

mrproper: clean
	rm -f ${PROG}

cppcheck:
	${CPPCHECK} ${cppcheck_flags} *.[ch] 

valgrind: pray5times
	valgrind ${valgrind_flags} ${EXEC} -l 1 -L 1 > /dev/null 2>&1
