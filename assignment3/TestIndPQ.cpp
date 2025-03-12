#include <iostream>
#include "IndPQ.h"

int main(void) { 
	PQ myPQ;  
	myPQ.insert(2);
	myPQ.display(); 
	myPQ.insert(5);
	myPQ.display();
	myPQ.insert(1);
	myPQ.display(); 
	int min = myPQ.deleteMin();
	std::cout << "The minimum element removed from the heap is " << min << "\n";
	myPQ.display();
}