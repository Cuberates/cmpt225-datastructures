#include <iostream>
#include "AList.h"

using namespace std;

int main(void) { 
	AList<int>* newList = new AList<int>(); 
	newList->addLeft(10);
	newList->addLeft(20);
	newList->addRight(30);
	newList->ddisplay();
}for(int i = left; i <= right; i++) { 	
			cout << i << " " << objects[i] << "\n";
		}