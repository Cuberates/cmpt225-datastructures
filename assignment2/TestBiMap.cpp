/******************************************************************
**   BiMap Class, Assignment 2 Part A
**   File: TestBiMap.cpp
**   Description: Test program for BiMap
**   Copyright © 2025, Xuan Viet Duc Nguyen.  All rights reserved.
**   Student ID: 301626893
**   Login ID: xvn@sfu.ca
*******************************************************************
******************************************************************/

#include "BiMap.h"
#include <iostream> 
#include <vector>
#include <string>
#include <random>
#include <utility>

using namespace std;

#define ll long long // Learned this in sfu icpc training camp

vector<pair<int, string>> generateBijectivePair(int numPairs) { 
	vector<pair<int, string>> result(numPairs);
	// Define a function that is known to be bijective, let's pick f(x) = x^2
	auto bijection = [](ll x) { return (x*x); }; 
	for(int i = 0; i < numPairs; i++) { 
		string prefix = "HASHED-";
		prefix += to_string(bijection(i)); 
		result[i].first = i; 
		result[i].second = prefix; 
	}
	return result; 
}

int main() {
	vector<pair<int, string>> bijectivePairs = generateBijectivePair(100); 
	// Test insertion under constraint
	cout << "Testing Insertion -------- \n";
	BiMap<int, string> myMap; 
	for(const auto &p : bijectivePairs) { 
		cout << "Inserting <" << p.first << ", " << p.second << ">\n";
		assert(myMap.insert(p.first, p.second) == 1);
	}
	cout << "\n";
	// Test retrival under constraint 
	cout << "Testing Retrieval -------- \n";
	for(auto p : bijectivePairs) { 
		int r = rand() % 2; 
		if(r == 0) {
			cout << "Retrieving " << p.second << myMap.getKey(p.second) << "\n";
			assert(myMap.getKey(p.second) == p.first);
			assert(myMap.containsVal(p.second)); 
			continue; 
		}
		cout << "Retrieving " << p.first << ": " << myMap.getVal(p.first) << "\n";
		assert(myMap.getVal(p.first) == p.second);
		assert(myMap.containsKey(p.first)); 
	}

	// Test removal under constraint 
	cout << "\n";
	cout << "Testing Removal -------- \n";
	for(auto p : bijectivePairs) { 
		int r = rand() % 2; 
		if(r == 0) {
			cout << "Removing by value: " << p.second << "\n";
			assert(myMap.removeVal(p.second));
			continue;
		}
		cout << "Removing by key: " << p.first << "\n";
		assert(myMap.removeKey(p.first)); 
	}
}