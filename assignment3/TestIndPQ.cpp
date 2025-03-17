#include <iostream> 
#include <vector>
#include <string>
#include <random>
#include <utility>
#include <algorithm>
// #include "QuadraticProbing.h"
#include "IndPQ.h"

std::vector<std::pair<int, std::string>> generateBijectivePair(int numPairs) { 
	std::vector<std::pair<int, std::string>> result(numPairs);
	// Define a function that is known to be bijective, let's pick f(x) = x^2
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
	auto bijectivePair = generateBijectivePair(10);
	auto rng = std::default_random_engine {};
	
	std::shuffle(std::begin(bijectivePair), std::end(bijectivePair), rng);

	Heap<Node> nodeHeap; 
	for(int i = 0; i < bijectivePair.size(); i++) {
		auto pairInfo = bijectivePair[i];
		nodeHeap.insert(Node(pairInfo.second, pairInfo.first)); 
	}
	nodeHeap.display(); 
}