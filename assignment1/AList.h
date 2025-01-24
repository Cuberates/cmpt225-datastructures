#ifndef ALIST_H
#define ALIST_H

#include <iostream>
#include <cassert>
using namespace std;

template <typename Object>
class AList { 
	public: 
	AList() {
		theCapacity = 12; 
		objects = new Object[theCapacity];
		theSize = 0; 
		left = 0; // array index of location just before the left-most list element
		right = 1; // array index just past the right-most list element
	}
	~AList() { delete [] objects; }
	
	bool empty() const { return size() == 0; }
	int size() const { return theSize; }
	void clear() {  
		theSize = 0; 
		left = 0; 
		right = 1; 
	}

	// Operations
	void addLeft(const Object x) { 
		theSize++; 
		objects[left] = x; 
		left = left - 1; 
		if(left < 0) left = theCapacity - 1; 
	}

	void addRight(const Object x) { 
		theSize++; 	
		objects[right] = x; 
		right = (right + 1) % theCapacity; 
	}

	Object removeRight() { 
		Object rightElement = objects[(right - 1 + theCapacity) % theCapacity];
		theSize--; 
		right--; 
		if(right < 0) right = theCapacity - 1;
		return rightElement;  
	}

	Object removeLeft() { 
		Object leftElement = objects[(left + 1) % theCapacity];
		theSize--; 
		left = (left + 1) % theCapacity; 
		return leftElement;
	}

	void display() { 
		cout << "["; 
		int l = left; 
		for(int i = 0; i < theSize; i++) {
			l = (l + 1) % theCapacity; // We are incrementing left until it reaches right
			cout << objects[l]; 
			if(i < theSize - 1) cout << ", ";
		}
		cout << "]"; 
	}

	void ddisplay() { 
		cout << "[";
		for(int i = 0; i < theCapacity; i++) { 
			cout << objects[i];
			if(i < theCapacity - 1) cout << ", ";

		}
		cout << "]\n";
		cout << "Left: " << left << "\t"; 
		cout << "Right: " << right << "\t"; 
		cout << "Size: " << theSize; 
	}

	private:
	int theSize;
	int left; 
	int right; 
	int theCapacity; 
	Object * objects;
};

#endif