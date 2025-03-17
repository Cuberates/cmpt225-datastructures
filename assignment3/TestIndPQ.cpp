#include <iostream> 
#include <vector>
#include <string>
#include <random>
#include <utility>
#include <algorithm>
#include "IndPQ.h"

std::vector<std::pair<int, std::string>> generateBijectivePair(int numPairs) { 
   std::vector<std::pair<int, std::string>> result(numPairs);
   auto bijection = [](long long x) { return (x*x); }; 
   for(int i = 0; i < numPairs; i++) { 
      std::string prefix = "ID-";
      prefix += std::to_string(bijection(i)); 
      result[i].first = i; 
      result[i].second = prefix; 
   }
   return result; 
}

int main(void) {
   // Create bijective pairs of task ID and priority
   auto bijectivePair = generateBijectivePair(10);

   // Shuffle the pairs randomly
   auto rng = std::default_random_engine {};
   std::shuffle(std::begin(bijectivePair), std::end(bijectivePair), rng);

   // Create the IndPQ object
   IndPQ nodeHeap; 

   // Insert elements into the priority queue
   for(int i = 0; i < bijectivePair.size(); i++) {
      auto pairInfo = bijectivePair[i];
      nodeHeap.insert(pairInfo.second, pairInfo.first); 
   }
   std::cout << "After insertions: \n";
   nodeHeap.display(); 
   
   // Test getMin function
   std::cout << "Minimum task ID: " << nodeHeap.getMin() << "\n";

   // Test deleteMin function and remove the min task
   std::cout << "Removing min task: " << nodeHeap.deleteMin() << "\n";
   nodeHeap.display();
   
   // Test updatePriority function
   std::cout << "Updating priority of 'ID-9' to 100: \n";
   nodeHeap.updatePriority("ID-9", 100);
   nodeHeap.display();

   // Test remove function
   std::cout << "Removing task 'ID-9' from the queue: \n";
   nodeHeap.remove("ID-9");
   nodeHeap.display();
   
   // Check if the heap is empty
   std::cout << "Is heap empty? " << (nodeHeap.isEmpty() ? "Yes" : "No") << "\n";

   // Print the size of the heap
   std::cout << "Heap size: " << nodeHeap.size() << "\n";
   
   // Clear the heap and check if it's empty
   nodeHeap.clear();
   std::cout << "After clearing the heap, is empty? " << (nodeHeap.isEmpty() ? "Yes" : "No") << "\n";
   
   // Final display of the heap (it should be empty)
   nodeHeap.display();
}
