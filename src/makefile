compile:
	gcc -L. -Wall -o elang elang.c helpers/libRe.so

compileAll:
	make lib
	make

lib:
	(cd helpers && g++ -c -Wall -Werror -fPIC re.cpp)
	g++ -shared -o helpers/libRe.so helpers/re.o

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
	gcc -g -L.-Wall -o elang elang.c helpers/libRe.so
