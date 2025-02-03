all: 
	g++ -Wall -o AListTest AListTest.cpp
	g++ -Wall -o overflowLeft overflowLeft.cpp
	g++ -Wall -o overflowRight overflowRight.cpp
	g++ -Wall -o underflowLeft underflowLeft.cpp
	g++ -Wall -o underflowRight underflowRight.cpp

run: 
	-./overflowLeft
	-./overflowRight
	-./underflowLeft
	-./underflowLeft

clean: 
	rm -f overflowLeft overflowRight underflowLeft underflowRight AListTest