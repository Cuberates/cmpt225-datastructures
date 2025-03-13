#include <iostream>
#include <cassert>
#include <string> 
#include <vector> 
#include "QuadraticProbing.h"

class Heap { 
	public: 
	explicit Heap(int capacity = 100);
	bool isEmpty() const; 
	const int & getMin() const; 
	const int & getSize() const; 
	void insert(const int &p); 
	void deleteMin(); 
	void deleteMin(int &minItem);
	void display(); 
	void ddisplay(); 

	private: 
	int currentSize; 
	std::vector<int> array;
	void percolateDown(int hole); 	
	void preOrder(int root = 1); 
	void inOrder(int root = 1);
	void postOrder(int root = 1); 
};

Heap::Heap(int capacity) { currentSize = 0; array = std::vector<int>(capacity); }
bool Heap::isEmpty() const { return currentSize == 0; }
const int & Heap::getMin() const { return array[1]; } 
const int & Heap::getSize() const { return currentSize; }

void Heap::insert(const int &p) {
	if(currentSize == array.size() - 1) {
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
void Heap::deleteMin() { 
	assert(isEmpty() == 0 && "Calling deleteMin() on an empty structure!"); 
	array[1] = std::move(array[currentSize--]);
	percolateDown(1);
}
void Heap::deleteMin(int &minItem) {
	assert(isEmpty() == 0 && "Calling deleteMin() on an empty structure!"); 
	minItem = std::move(array[1]); 
	array[1] = std::move(array[currentSize--]);
	percolateDown(1);
}
void Heap::percolateDown(int hole) { 
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
void Heap::display() {
	std::cout << "Pre-Order Traversal: "; preOrder(); cout << "\n"; 
	std::cout << "In-Order Traversal: "; inOrder(); cout << "\n";
	std::cout << "Post-Order Traversal: "; postOrder(); cout << "\n";
}
void Heap::ddisplay() { 
	std::cout << "Current size: " << currentSize << "\n";
	std::cout << "Current representation of Heap: \n";
	for(int i = 1; i <= currentSize; i++) { 
		std::cout << array[i] << " "; 
	}
	cout << "\n";
	display(); 
}
void Heap::preOrder(int root) {
	if (root > currentSize) return; 
	int leftChild = 2 * root; 
	int rightChild = 2 * root + 1; 
	std::cout << array[root] << " "; 
	preOrder(leftChild);
	preOrder(rightChild);
}
void Heap::inOrder(int root) {
	if (root > currentSize) return; 
	int leftChild = 2 * root; 
	int rightChild = 2 * root + 1; 
	preOrder(leftChild);
	std::cout << array[root] << " "; 
	preOrder(rightChild);
}
void Heap::postOrder(int root) {
	if (root > currentSize) return; 
	int leftChild = 2 * root; 
	int rightChild = 2 * root + 1; 
	preOrder(leftChild);
	preOrder(rightChild);
	std::cout << array[root] << " "; 
}

class IndPQ { 
	public: 
	explicit IndPQ(); 
	bool isEmpty() const; 
	
	const std::string & getMin() const; 
	const int & getSize() const; 
	
	void insert(const std::string &taskid, int p); 
	void updatePriority(const std::string &taskid, int p); 

	std::string & deleteMin(); 

	void remove(const std::string &tid); 
	void clear(); 

	void display();
	void ddisplay(); 

	private: 
	Heap priorities; 
	HashTable<int, std::string> hash; 
};

IndPQ::IndPQ() {};

bool IndPQ::isEmpty() const { return priorities.isEmpty(); }

const std::string & IndPQ::getMin() { 
	int minP = priorities.getMin(); 
	std::string & minTask = hash.getVal(minP); 
	return minTask; 
}




