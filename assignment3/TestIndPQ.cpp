#include <iostream>
#include "IndPQ.h"

int main() {
    IndPQ pq;

    // Insert some tasks
    pq.insert("Task A", 5);
    pq.insert("Task B", 2);
    pq.insert("Task C", 8);
    pq.insert("Task D", 1); // Lowest priority (highest importance)

    std::cout << "\nInitial Priority Queue:\n";
    pq.display();

    // Get the minimum task
    std::cout << "\nTask with the highest priority: " << pq.getMin() << "\n";

    // Delete the minimum priority task
    std::cout << "\nDeleting minimum priority task: " << pq.deleteMin() << "\n";

    std::cout << "\nPriority Queue after deleting min:\n";
    pq.display();

    // Update priority of "Task C" from 8 to 0
    std::cout << "\nUpdating priority of 'Task C' to 0 (highest priority)\n";
    pq.updatePriority("Task C", 0);

    std::cout << "\nPriority Queue after update:\n";
    pq.display();

    // Remove "Task B"
    std::cout << "\nRemoving 'Task B'\n";
    pq.remove("Task B");

    std::cout << "\nPriority Queue after removing 'Task B':\n";
    pq.display();

    // Clear all tasks
    std::cout << "\nClearing the queue...\n";
    pq.clear();

    std::cout << "\nFinal Priority Queue:\n";
    pq.display();

    return 0;
}