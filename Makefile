C:
	make -C wrapper
	make -C lib
	make -C src

java:
	make -C wrapper
	make java -C lib
	make -C src

python:
	make -C wrapper
	make python -C lib
	make -C src

csharp:
	make -C wrapper
	make csharp -C lib
	make -C src

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
