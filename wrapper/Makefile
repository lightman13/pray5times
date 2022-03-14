PYINSTALLER := pyinstaller
src_files := pray5times-wrapper.py
DIR_INSTALL := /usr/bin
PROG := pray5times-wrapper
PROG_DIR := dist
PYLINT := pylint

all: pray5times-wrapper

pray5times-wrapper:
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
