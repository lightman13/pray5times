CC=gcc
LIB=libpray5times.so

CFLAGS+=-Wall -Werror -O0 -g -lm -fpic
SRC := sun_position.c utils.c cal_prayer.c date.c
OBJS := sun_position.o utils.o cal_prayer.o date.o
DIR_INSTALL := /usr/lib64

#gcovr
GCOVR := gcovr
gcovr_flags := -r . --html --html-details -o

all: pray5times

pray5times:
	${CC} -c ${SRC} ${CFLAGS}
	${CC} -shared -o ${LIB} ${OBJS}

.PHONY: install
install:
	install -m 755 ${LIB} ${DIR_INSTALL}

.PHONY: uninstall
uninstall:
	rm -rf ${DIR_INSTALL}/${LIB}

clean:
	rm -f *.o
	rm -f *.so
	rm -rf report-html
	rm -f *.gcda
	rm -f *.gcno

check: ${OBJS}
	${CC} -c ${CFLAGS} ${SRC} && make -C tests

coverage: ${OBJS}
	${CC} -c ${CFLAGS} -fprofile-arcs -ftest-coverage -lgcov ${SRC} && make -C tests

coverage_report: coverage-report.html
.PHONY: coverage-report.html
coverage-report.html:
	mkdir report-html && ${GCOVR} ${gcovr_flags} report-html/$@
