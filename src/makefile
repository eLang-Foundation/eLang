compile: elang.c
	make lib
	gcc -L. -Wall -o elang elang.c libGet.so

lib:
	g++ -c -Wall -Werror -fPIC get.cpp
	g++ -shared -o libGet.so get.o

test:
	make
	./elang test.elang

clean:
	rm elang
	rm *.so
	rm *.o

memcheck:
	make
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./elang test.elang

debug:
	make lib
	gcc -g -L. -Wall -o elang elang.c libGet.so
