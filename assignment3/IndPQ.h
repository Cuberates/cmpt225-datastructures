#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <cassert>
#include "QuadraticProbing.cpp"



template <typename KeyType, typename ValType>
class HashTable {
   public:
      explicit HashTable(int size = 11) : array(nextPrime(size)) { makeEmpty(); }

      bool contains(const KeyType &x) const {
         return isActive(findPos(x));
      }

      void makeEmpty() {
         currentSize = 0;
         for (auto &entry : array)
            entry.info = EMPTY;
      }

      bool insert(const KeyType &x, const ValType &y) {
         int currentPos = findPos(x);
         if (isActive(currentPos)) return false;
         if (array[currentPos].info != DELETED) ++currentSize;
         
         array[currentPos].first = x;
         array[currentPos].second = y;
         array[currentPos].info = ACTIVE;
         
         if (currentSize > array.size() / 2) rehash();
         return true;
      }
      
      bool insert(KeyType &&x, ValType &&y) {
         int currentPos = findPos(x);
         if (isActive(currentPos)) return false;
         if (array[currentPos].info != DELETED) ++currentSize;
         
         array[currentPos].first = std::move(x);
			array[currentPos].second = std::move(y); 
         array[currentPos].info = ACTIVE;
         
         if (currentSize > array.size() / 2) rehash();
         return true;
      }

      bool remove(const KeyType &x) {
         int currentPos = findPos(x);
         if (!isActive(currentPos)) return false;
         
         array[currentPos].info = DELETED;
         return true;
      }
      
      int getSize() const { return currentSize; }

      ValType getVal(const KeyType &x) const {
         assert(contains(x));
         auto pos = findPos(x);
         return array[pos].second;
      }

      void display() {
         std::cout << "--------------------------\n";
         for (auto &pair : array) {
            if (pair.info == ACTIVE)
               std::cout << pair.first << " " << pair.second << "\n";
         }
         std::cout << "--------------------------\n";
      }
      
      void ddisplay() {
         std::cout << "--------------------------\n";
         for (auto &pair : array) {
            if (pair.info == DELETED)
               std::cout << pair.first << " " << pair.second << " DELETED\n";
            else if (pair.info == ACTIVE)
               std::cout << pair.first << " " << pair.second << " ACTIVE\n";
            else
               std::cout << ". . EMPTY\n";
         }
         std::cout << "--------------------------\n";
      }

      enum EntryType { ACTIVE, EMPTY, DELETED };

   private:
      struct HashEntry {
         KeyType first;
         ValType second;
         EntryType info;

         HashEntry(const KeyType &e = KeyType{}, EntryType i = EMPTY)
            : first{e}, info{i} {}

         HashEntry(KeyType &&e, EntryType i = EMPTY)
            : first{std::move(e)}, info{i} {}
      };

      std::vector<HashEntry> array;
      int currentSize;

      bool isActive(int currentPos) const {
         return array[currentPos].info == ACTIVE;
      }

      int findPos(const KeyType &x) const {
         int offset = 1;
         int currentPos = myhash(x);
         
         while (array[currentPos].info != EMPTY && array[currentPos].first != x) {
            currentPos += offset;
            offset += 2;
            if (currentPos >= array.size())
               currentPos -= array.size();
         }
         return currentPos;
      }

      void rehash() {
         std::vector<HashEntry> oldArray = array;
         
         array.resize(nextPrime(2 * oldArray.size()));
         for (auto &entry : array)
            entry.info = EMPTY;
         
         currentSize = 0;
         for (auto &entry : oldArray)
            if (entry.info == ACTIVE)
               insert(std::move(entry.first), std::move(entry.second));
      }

      size_t myhash(const KeyType &x) const {
         static std::hash<KeyType> hf;
         return hf(x) % array.size();
      }
};


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

	const std::string & getID() const { return this->taskID; }
	const int getpriority() const { return this->priority; }

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

	void percolateUp(int hole);
	void percolateDown(int hole); 

	// private: 
	int currentSize;
	std::vector<Object> array;
	void preOrder(int root);
	    // Overload the operator[] for direct index access
	Object & operator[](int index) {
		if (index <= 0 || index > currentSize) {
			throw std::out_of_range("Index out of range!");
		}
		return array[index];
	}

	const Object & operator[](int index) const {
		if (index <= 0 || index > currentSize) {
			throw std::out_of_range("Index out of range!");
		}
		return array[index];
	}

};

template<typename Object>
Heap<Object>::Heap(int capacity) { currentSize = 0; array = std::vector<Object>(capacity + 1); }

template<typename Object> 
const bool Heap<Object>::isEmpty() { return currentSize == 0; }

template<typename Object>
const Object & Heap<Object>::getMin() { 
	assert(isEmpty() == false && "Calling getMin() on empty structure!");
	return array[1]; 
}

template<typename Object> 
const int & Heap<Object>::getSize() { 
	return currentSize; 
}

template<typename Object>
void Heap<Object>::insert(const Object & obj) { 
	if (currentSize == array.size() - 1) 
		array.resize(array.size() * 2);

	int hole = ++currentSize; 
	Object copy = obj; 
	array[hole] = std::move(copy);
	percolateUp(hole);
}

template<typename Object> 
void Heap<Object>::percolateUp(int hole) { 
	for(; array[hole] < array[hole / 2]; hole /= 2)
		std::swap(array[hole], array[hole/2]);
}

template<typename Object>
void Heap<Object>::percolateDown(int hole) {
	int child; 
	Object tmp = std::move(array[hole]);
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
// Insert with the new priority.
class IndPQ {
   private:
      Heap<Node> heap;
      HashTable<std::string, int> indexMap;

   public:
      IndPQ() : heap(100), indexMap(100) {}

      void insert(const std::string &taskID, int priority) {
         Node newNode(taskID, priority);
         heap.insert(newNode);
         indexMap.insert(taskID, heap.getSize());
      }

      const std::string & deleteMin() {
         assert(!heap.isEmpty() && "Calling deleteMin() on empty structure!");
         const std::string & minTask = heap.getMin().getID();
         heap.deleteMin();
         indexMap.remove(minTask);
         return minTask;
      }

      std::string getMin() {
         assert(!heap.isEmpty() && "Calling getMin() on empty structure!");
         return heap.getMin().getID();
      }

      void updatePriority(const std::string &taskID, int newPriority) {
			// Ensure the task exists in the heap (check for presence in the index map)
			assert(indexMap.contains(taskID) && "TaskID not found!");

			// Step 1: Find the task index in the heap
			int index = indexMap.getVal(taskID);  // Get the index from the indexMap
			
			// Step 2: Access the task and update its priority
			// Assuming heap is a std::vector<Node> where Node has getPriority and setPriority methods
			Node &taskNode = heap[index];  // Directly access the task node in the heap


			// Update the priority of the task
			taskNode.setPriority(newPriority);

			// Step 3: Percolate up or down to restore heap property
			if (newPriority < taskNode.getpriority()) {
				// If the new priority is smaller, percolate up
				heap.percolateUp(index);
			} else {
				// If the new priority is larger, percolate down
				heap.percolateDown(index);
			}
}


      void remove(const std::string &taskID) {
         assert(indexMap.contains(taskID) && "TaskID not found!");
			int index = indexMap.getVal(taskID);
			heap.deleteMin(); 
			indexMap.remove(taskID);
      }

      bool isEmpty() { return heap.isEmpty(); }
      int size() { return heap.getSize(); }
      void clear() { while (!heap.isEmpty()) deleteMin(); }
      void display() { heap.display(); }
      void ddisplay() { heap.ddisplay(); }
};

