#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <cassert>

/**
 * Design structure:
 * - A heap which stores <TASK, PRIORITY> which is good enough but inefficient
 * due to updatePriority(TASK, NEW_PRIORITY)
 *  */ 

class Node {
	private:
	std::string taskID; 
	int priority; 

	public:
	Node() {}
	Node (const std::string & taskID, const int & priority) {
		this->taskID = taskID; 
		this->priority = priority; 
	}

	const std::string & getID() { return this->taskID; }
	const int & getpriority() { return this->priority; }

	void setID(const std::string & taskID) { this->taskID = taskID; }
	void setPriority(const int & priority) { this->priority = priority; }

	friend bool operator<(const Node& n1, const Node& n2) {
		return n1.priority < n2.priority; 
	}
	friend std::ostream & operator<<(std::ostream &cout, Node & n) {
		cout << "Task ID=" << n.getID() << " | " << "Priority=" << n.getpriority();
		return cout; 
	}
};

template<typename Object> 
class Heap {
	public: 
	explicit Heap(int capacity = 100);
	const bool isEmpty(); 
	const Object & getMin(); 
	const int & getSize(); 

	void insert(const Object & obj); 
	void deleteMin(); 
	void display(); 
	void ddisplay(); 

	private: 
	int currentSize;
	std::vector<Object> array; 
	void percolateUp(int hole);
	void percolateDown(int hole); 
	void preOrder(int root);
};

template<typename Object>
Heap<Object>::Heap(int capacity) { currentSize = 0; array = std::vector<Object>(capacity + 1); }

template<typename Object> 
const bool Heap<Object>::isEmpty() { return currentSize == 0; }

template<typename Object>
const Object & Heap<Object>::getMin() { 
	assert(isEmpty() == false && "Calling getMin() on empty structure!");
	return array[0]; 
}

template<typename Object> 
const int & Heap<Object>::getSize() { 
	return currentSize; 
}

template<typename Object>
void Heap<Object>::insert(const Object & obj) { 
	if (currentSize == array.size() - 1) { 
		array.resize(array.size() * 2);
	}
	int hole = ++currentSize; 
	Object copy = obj; 
	array[hole] = std::move(copy);
	percolateUp(hole);
}

template<typename Object> 
void Heap<Object>::percolateUp(int hole) { 
	for(; array[hole] < array[hole / 2]; hole /= 2)
		// array[hole] = std::move(array[hole / 2]);
		std::swap(array[hole], array[hole/2]);
	// array[hole] = std::move(array[0]);
}

template<typename Object> 
void Heap<Object>::deleteMin() { 
	assert(isEmpty() == false && "Calling deleteMin() on empty structure!"); 
	array[1] = std::move(array[currentSize--]);
	percolateDown(1);
}
template<typename Object> 
void Heap<Object>::display() {
	assert(isEmpty() == false && "Calling preOrder() on empty structure!");
	for(int i = 1; i <= currentSize; i++) {
		std::cout << array[i] << "\n";
	}
}

template<typename Object> 
void Heap<Object>::preOrder(int root) { 
	if(root > currentSize) return; 
	int leftChild = root * 2; 
	int rightChild = root * 2 + 1; 
	std::cout << array[root] << " ";
	preOrder(leftChild);
	preOrder(rightChild);
}