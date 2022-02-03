PYINSTALLER := pyinstaller
src_files := prayer_time_wrapper.py
DIR_INSTALL := /usr/local/bin
PROG := prayer_time_wrapper
PROG_DIR := dist
PYLINT := pylint

all: prayer_time_wrapper

prayer_time_wrapper:
	${PYINSTALLER} --onefile ${src_files}

clean:
	rm -rf dist/
	rm -rf build/
	rm -rf __pycache__
	rm -rf *.spec

install:
	install -m 755 ${PROG_DIR}/${PROG} ${DIR_INSTALL}

uninstall:
	rm -rf ${DIR_INSTALL}/${PROG}

pylint:
	${PYLINT} *.py
