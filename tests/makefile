compile:
	gcc count_test.c ../src/count.c ../src/insideQuotes.c Unity/src/unity.c -o count_test
	gcc getContents_test.c ../src/getContents.c Unity/src/unity.c -o getContents_test
	gcc getIndex_test.c ../src/getIndex.c Unity/src/unity.c -o getIndex_test
	gcc insideQuotes_test.c ../src/insideQuotes.c Unity/src/unity.c -o insideQuotes_test
	gcc trim_test.c ../src/trim.c Unity/src/unity.c -o trim_test
	g++ -L../src/ -Wall re_test.c ../src/re.cpp Unity/src/unity.c ../src/libRe.so -o re_test

tests:
	./count_test
	./getContents_test
	./getIndex_test
	./insideQuotes_test
	./trim_test
	./re_test
