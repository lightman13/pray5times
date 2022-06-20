CC=gcc
LIB=libpray5times.so
LIB_DLL=libpray5times.dll

#Cppcheck
CPPCHECK := cppcheck
cppcheck_flags := --enable=all --inconclusive --inline-suppr    \
		  --suppress=missingIncludeSystem --library=gnu \
		  --quiet --suppress=unusedFunction
#Swig
SWIG=swig
SWIG_FILE=libpray5times.i
SWIG_OUTPUT=libpray5times_wrap
PYTHON_PATH=/usr/include/python3.9/
JAVA_PATH=/usr/lib/jvm/java/include
JAVA_PATH_LINUX=/usr/lib/jvm/java/include/linux/

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
	install -m 755 ${LIB_DLL} ${DIR_INSTALL}
	install -m 755 prayer_time.h /usr/include/

.PHONY: uninstall
uninstall:
	rm -rf ${DIR_INSTALL}/${LIB}
	rm -f /usr/include/prayer_time.h

clean:
	rm -f *.o
	rm -f *.so
	rm -rf report-html
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.py
	rm -rf __pycache__
	rm -f *.java
	rm -f *.class
	rm -f libpray5times_wrap.c

mrproper: clean
	rm -f ${LIB}

cppcheck:
	${CPPCHECK} ${cppcheck_flags} *.[ch]

check: ${OBJS}
	${CC} -c ${CFLAGS} ${SRC} && make -C tests

coverage: ${OBJS}
	${CC} -c ${CFLAGS} -fprofile-arcs -ftest-coverage -lgcov ${SRC} && make -C tests

coverage_report: coverage-report.html
.PHONY: coverage-report.html
coverage-report.html:
	mkdir report-html && ${GCOVR} ${gcovr_flags} report-html/$@

# Language bindings
python:
	${SWIG} -python ${SWIG_FILE}
	${CC} -c ${SRC} ${CFLAGS}
	${CC} -c ${SWIG_OUTPUT}.c ${CFLAGS} -I${PYTHON_PATH}
	${CC} -shared -o _${LIB} ${OBJS} ${SWIG_OUTPUT}.o

java:
	${SWIG} -java ${SWIG_FILE}
	${CC} -c ${SRC} ${CFLAGS}
	${CC} -c ${SWIG_OUTPUT}.c ${CFLAGS} -I${JAVA_PATH} -I${JAVA_PATH_LINUX}
	${CC} -shared -o ${LIB} ${OBJS} ${SWIG_OUTPUT}.o

csharp:
	${SWIG} -csharp ${SWIG_FILE}
	${CC} -c ${SRC} ${CFLAGS}
	${CC} -c ${SWIG_OUTPUT}.c ${CFLAGS}
	${CC} -shared -o ${LIB_DLL} ${OBJS} ${SWIG_OUTPUT}.o
