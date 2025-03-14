#include <iostream>
#include <cassert>
// #include <pair>
#include <string> 
#include <vector> 
#include <limits.h> 
#include "QuadraticProbing.h"

#define INF INT_MAX
typedef std::pair<int, std::string> Node; 


class Heap { 
	public: 
	explicit Heap(int capacity = 100);
	bool isEmpty() const; 
	const int & getMin() const; 
	const int & getSize() const; 
	void insert(const int &p); 
	void remove (const int &p);
	void deleteMin(); 
	void deleteMin(int &minItem);
	void updatePriority(const int &p, const int &newP);
	void clear(); 
	const std::vector<int> & traverse(); 
	
	void display(); 
	void ddisplay(); 

	private: 
	int currentSize; 
	std::vector<Node> array;
	std::vector<int> traversal;
	void decreaseKey(const int &p, const int &delta);
	void increaseKey(const int &p, const int &delta);
	void percolateDown(int hole); 	
	void percolateUp(int hole); 

	// For traversals
	void preOrder(const int & root, bool called); 
	void inOrder(const int & root, bool called);
	void postOrder(const int & root, bool called);
};

Heap::Heap(int capacity) { currentSize = 0; array = std::vector<int>(capacity); }
bool Heap::isEmpty() const { return currentSize == 0; }
const int & Heap::getMin() const { return array[1]; } 
const int & Heap::getSize() const { return currentSize; }

void Heap::insert(const int &p,const std::string &taskid) {
	if(currentSize == array.size() - 1) {
		array.resize(array.size() * 2); 
	}
	int hole = ++currentSize; 
	array[0] = std::move(std::make_pair(p, taskid));
	percolateUp(hole);
}

void Heap::remove(const int &p) {
	// Performing decrease(P, INF) and then deleteMin()
	decreaseKey(p, INF);
	deleteMin(); 
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

void Heap::increaseKey(const int &p, const int &delta) { // nlog(n) which is pretty bad
	int pos = -1; 
	for(pos; pos <= currentSize; pos++) {
		if(pos >= 1 && array[pos] == p) break;
	}
	assert(pos != -1 && "Priority does not exist in the heap!");
	array[pos] = array[pos] + delta; 
	percolateDown(pos);
}		

void Heap::decreaseKey(const int &p, const int &delta) {
	int pos = -1; 
	for(pos; pos <= currentSize; pos++) {
		if(array[pos] == p) break;
	}
	assert(pos != -1 && "Priority does not exist in the heap!");
	array[pos] = array[pos] - delta; 
	percolateUp(pos);
}

void Heap::updatePriority(const int &p, const int &delta) {
	assert(abs(delta) <= INF && "Delta exceeds INF");
	if(delta <= 0) decreaseKey(p, -delta);
	else increaseKey(p, delta);
}

void Heap::percolateDown(int hole) { 
	int child; 
	int tmp = std::move(array[hole]);
	for(; hole * 2 <= currentSize; hole = child) { 
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

const std::vector<int> & Heap::traverse() { 
	preOrder(1, 0);
	std::vector<int> & trav = traversal;
	return trav; 
}

void Heap::percolateUp(int hole) { 
	for(hole; array[0] < array[hole / 2]; hole /= 2) { 
		array[hole] = std::move(array[hole / 2]); 
	}
	array[hole] = std::move(array[0]);
}

void Heap::display() {
	std::cout << "In-Order Traversal: ";
	preOrder(1, 0); 
	for(int i = 0; i < traversal.size(); i++) { 
		std::cout << traversal[i] << " ";
	}
	std::cout << "\n";
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

void Heap::preOrder(const int &root = 1, bool called = false) {
	if(called == 0) traversal.clear(); 
	if(root > currentSize) return; 
	int leftChild = root * 2; 
	int rightChild = root * 2 + 1; 
	traversal.push_back(array[root]);
	preOrder(leftChild, 1);
	preOrder(rightChild, 1);
}

void Heap::inOrder(const int &root = 1, bool called = false) { 
	if(called == 0) traversal.clear(); 
	if(root > currentSize) return; 
	int leftChild = root * 2; 
	int rightChild = root * 2 + 1; 
	inOrder(leftChild);
	traversal.push_back(array[root]);
	inOrder(rightChild);
}

void Heap::postOrder(const int &root = 1, bool called = false) {
	if(called == 0) traversal.clear(); 
	if(root > currentSize) return; 
	int leftChild = root * 2; 
	int rightChild = root * 2 + 1; 
	postOrder(leftChild);
	postOrder(rightChild);
	traversal.push_back(array[root]);
}

void Heap::clear() { 
	array.clear(); 
	traversal.clear(); 
	currentSize = 0; 
}

// class IndPQ { 
// 	public: 
// 	explicit IndPQ(); 
// 	bool isEmpty() const; 
// 	std::string & getMin(); 
// 	const int & getSize() const; 
// 	void insert(const std::string &taskid, int p); 
// 	void updatePriority(const std::string &taskid, int p); 
// 	std::string & deleteMin(); 
// 	void remove(const std::string &tid); 
// 	void clear(); 
// 	void display();
// 	void ddisplay(); 
// 	private: 
// 	Heap priorities; 
// 	HashTable<int, std::string> hash; // This does not allow duplication
// 	// HashTable<int, std::string> hash;
// };

// IndPQ::IndPQ() {};

// bool IndPQ::isEmpty() const { return priorities.isEmpty(); }

// std::string & IndPQ::getMin() { 
// 	int minP = priorities.getMin(); 
// 	std::string & minTask = hash.getVal(minP);
// 	return minTask; 
// }

// const int & IndPQ::getSize() const { 
// 	return priorities.getSize(); 
// }

// void IndPQ::insert(const std::string &taskid, int p) {
// 	assert(hash.contains(p) == 0 && "Insertion of duplication!");
// 	priorities.insert(p); 
// 	hash.insert(p, taskid);
// }

// void IndPQ::updatePriority(const std::string &taskid, int p) {
// 	remove(taskid);
// 	insert(taskid, p);
// }

// std::string & IndPQ::deleteMin() {
// 	int minP = priorities.getMin(); 
// 	std::string & minTask = hash.getVal(minP);
// 	priorities.deleteMin(); 
// 	hash.remove(minP);
// 	return minTask; 
// }

// void IndPQ::remove(const std::string &tid) { 
// 	const std::vector<int> & allPriorities = priorities.traverse(); 
// 	bool found = 0; 
// 	for (const auto & cp : allPriorities) { 
// 		const std::string & currentTask = hash.getVal(cp);
// 		if (currentTask == tid) {
// 			found = 1; 
// 			priorities.remove(cp); 
// 			hash.remove(cp);
// 		}
// 	}	
// 	assert(found == 1 && "Non-existent priority!"); 
// }

// void IndPQ::clear() { 
// 	priorities.clear(); 
// 	hash.makeEmpty(); 
// }

// void IndPQ::display() { 
// 	const std::vector<int> & allPriorities = priorities.traverse(); 
// 	for (const auto & p : allPriorities) {
// 		std::cout << "TaskID: " << hash.getVal(p) << "\t Prioritiy: " << p << "\n"; 
// 	}
// }




