// #include "BiMap.h"
#include "BiMap.cpp"
#include <iostream> 
#include <vector> 


int main(void) {
	BiMap<char, int> b1;
	int test1 = b1.insert('a', 2);
	b1.ddisplay();
	int test2 = b1.removeKey('a');
	b1.ddisplay(); 
	cout << test1 << " " << test2 << "\n";

	 
}