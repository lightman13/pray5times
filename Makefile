all:
	make -C wrapper
	make -C src

clean:
	make clean -C wrapper
	make clean -C src

install:
	make install -C wrapper
	make install -C src

uninstall:
	make uninstall -C wrapper
	make uninstall -C src
