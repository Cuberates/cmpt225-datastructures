#include <iostream>
#include <string> 
#include <vector> 
#include "QuadraticProbing.h"

class PQ { 
	public: 
	PQ(int capacity = 100);
	PQ(const std::vector<int> & items);
	void insert(const int &p);
	int & deleteMin(); 
	int & getMin(); 
	vector<int> & getAll() const;
	void remove(const int &p); 
	bool isEmpty(); 
	int size() const; 
	void clear(); 
	void display(); 
	void ddispplay(); 

	private: 
	int currentSize; 
	std::vector<int> array;
	
	void percolateDown(int hole); 	
};

PQ::PQ(int capacity) { currentSize = 0; array = std::vector<int>(capacity); }
PQ::PQ(const std::vector<int> &items) { array = items; }

void PQ::insert(const int &p) {
	if(currentSize > array.size()) {
		array.resize(array.size() * 2); 
	}
	int hole = ++currentSize; 
	int copy = p; 
	array[0] = std::move(copy); 
	for(hole; p < array[hole / 2]; hole /= 2) { 
		array[hole] = std::move(array[hole / 2]); 
	}
	array[hole] = std::move(array[0]);
}
int & PQ::deleteMin() { 
	int minElement = array[1];
	array[1] = std::move(array[currentSize--]); 
	percolateDown(1);
	return minElement; 
}

int & PQ::getMin() { 
	int minElement = array[1]; 
	return minElement;
}

void PQ::remove(const int &p) { 
	
}

bool PQ::isEmpty() { 
	return (currentSize <= 0); 
}

// Returning the current size of the structure NOT the capacity of the structure
int PQ::size() const { 
	return currentSize; 
}

void PQ::clear() { 
	currentSize = 0; 
	array.clear(); 
}

void PQ::display() {
	for(int hole = 1; hole <= currentSize; hole++) { 
		std::cout << "Child nodes of " << array[hole] << "\n";
		std::cout << "Left: "; 
		if(hole * 2 <= currentSize) std::cout << array[hole * 2]; std::cout << "\n"; 
		std::cout << "Right: ";
		if(hole * 2 + 1 <= currentSize) std::cout << array[hole * 2 + 1]; std::cout << "\n";
	}
}

void PQ::percolateDown(int hole) { 
	int child; 
	int tmp = std::move(array[hole]);

	for(hole; hole * 2 <= currentSize; hole = child) { 
		child = hole * 2; 
		if (child != currentSize && array[child + 1] < array[child])
			++child; 
		if (array[child] < tmp)
			array[hole] = std::move(array[child]);
		else 
			break; 
	}
	array[hole] = std::move(tmp);
}


class IndPQ { 
	public: 
	IndPQ(); 
	void insert(const std::string &taskid, int p); 
	std::string & deleteMin(); 
	std::string & getMin();
	void updatePriority(const std::string &taskid, int p); 
	void remove(const std::string &tid); 
	bool isEmpty(); 
	int size(); 
	void clear(); 
	void display();
	void ddisplay(); 

	private: 
	PQ priorities; 
	HashTable<int,string> map; 
};

IndPQ::IndPQ() {}

void IndPQ::insert(const std::string &taskid, int p) {
	priorities.insert(p); 
	map.insert(p, taskid);
}
std::string & IndPQ::deleteMin() { 
	int p = priorities.deleteMin();
	map.remove(p);
}


void IndPQ::ddisplay() { 
	
}