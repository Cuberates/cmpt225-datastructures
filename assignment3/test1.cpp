#include <iostream>
// #include "QuadraticProbing.h"
#include "IndPQ.h"

void testHeap() {
    std::cout << "=== Testing Heap ===\n";

    Heap heap;
    
    // Insert unique elements
    std::cout << "Inserting: 10, 20, 5, 30, 3\n";
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(30);
    heap.insert(3);
    
    heap.display();

    // Get min element
    std::cout << "Min Element: " << heap.getMin() << "\n";

    // Delete min element
    std::cout << "Deleting min...\n";
    heap.deleteMin();
    heap.display();

    // Increase priority of 20 by 5 (should percolate down)
    std::cout << "Increasing priority of 20 by 5...\n";
    heap.updatePriority(20, 5);
    heap.display();

    // Decrease priority of 30 by 15 (should percolate up)
    std::cout << "Decreasing priority of 30 by 15...\n";
    heap.updatePriority(30, -15);
    heap.display();

    // Remove an element (removes 5)
    std::cout << "Removing element 5...\n";
    heap.remove(5);
    heap.display();

    // Clear the heap
    std::cout << "Clearing the heap...\n";
    heap.clear();
    heap.display();
}

void testIndPQ() {
    std::cout << "\n=== Testing Indexed Priority Queue (IndPQ) ===\n";
    IndPQ pq;
    // Insert elements with unique priorities
    std::cout << "Inserting: (Task1, 5), (Task2, 3), (Task3, 8), (Task4, 1), (Task5, 7)\n";
    pq.insert("Task1", 5);
    pq.insert("Task2", 3);
    pq.insert("Task3", 8);
    pq.insert("Task4", 1);
    pq.insert("Task5", 7);
    
    pq.display();
    
    // Get min element
    std::cout << "Min Task: " << pq.getMin() << "\n";

    // Delete min element
    std::cout << "Deleting min task...\n";
    pq.deleteMin();
    pq.display();

    // Increase priority of Task3 by 2 (should move down)
    std::cout << "Increasing priority of Task3 by 2...\n";
    pq.updatePriority("Task3", 2);
    pq.display();

    // Decrease priority of Task1 by 3 (should move up)
    std::cout << "Decreasing priority of Task1 by 3...\n";
    pq.updatePriority("Task1", -3);
    pq.display();

    // Remove Task2
    std::cout << "Removing Task2...\n";
    pq.remove("Task2");
    pq.display();

    // Clear the queue
    std::cout << "Clearing the priority queue...\n";
    pq.clear();
    pq.display();
}

int main() {
    testHeap();
    testIndPQ();
    return 0;
}
