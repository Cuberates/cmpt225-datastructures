all: AListTest

AListTest: AListTest.o 
	g++ -Wall -o AListTest AListTest.o
AListTest.o : AListTest.cpp AList.h
	g++ -Wall -o AListTest.o -c AListTest.cpp
clean: 
	rm -f AListTest *.o
