C:
	make -C wrapper
	make -C src
	make -C lib

java:
	make -C wrapper
	make -C src
	make java -C lib

python:
	make -C wrapper
	make -C src
	make python -C lib

csharp:
	make -C wrapper
	make -C src
	make csharp -C lib

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
