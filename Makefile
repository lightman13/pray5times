all:
	make -C wrapper
	make -C src
	make -C lib

clean:
	make clean -C wrapper
	make clean -C src
	make clean -C lib

install:
	make install -C wrapper
	make install -C src
	make install -C lib

uninstall:
	make uninstall -C wrapper
	make uninstall -C src
	make uninstall -C lib
