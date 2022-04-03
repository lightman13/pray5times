CC=gcc
LIB=libpray5times.so

CFLAGS+=-Wall -Werror -O0 -g -lm -fpic
SRC := sun_position.c utils.c cal_prayer.c date.c
OBJS := sun_position.o utils.o cal_prayer.o date.o
DIR_INSTALL := /usr/lib64

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
