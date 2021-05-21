compile: elang.c
	g++ -c -Wall -Werror -fPIC get.cpp
	g++ -shared -o libGet.so get.o
	gcc -L. -Wall -o elang elang.c libGet.so

test:
	make
	./elang test.elang

clean:
	rm elang
	rm *.so
	rm *.o

memcheck:
	make
	valgrind --track-origins=yes --leak-check=full ./elang test.elang
