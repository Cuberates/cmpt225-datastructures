/******************************************************************
**   AList Class, Assignment 1 Part B
**   File: underflowLeft.cpp
**   Description: Performing left-end underflows 
**   Copyright © 2025, Xuan Viet Duc Nguyen.  All rights reserved.
**   Student ID: 301626893
**   Login ID: xvn@sfu.ca
*******************************************************************
******************************************************************/

#include <iostream> 
#include <cassert>
#include <random> 
#include <ctime> 
#include "AList.h"

using namespace std;

#define CAP 12

template <typename Object>
int testAdd(AList<Object>& L, const Object sample[], const int MAX_CAP = CAP) { 
    for(int i = 1; i <= MAX_CAP; i++) { 
        int r = rand() % 2 + 1; 
        if(r % 2 == 0) { 
            cout << "addLeft(" << sample[i-1] << ") => "; 
            L.addLeft(sample[i-1]);
            L.display();  
            cout << "\t Size: " << L.size() << "\n";
            assert(L.size() == i);
            continue; 
        } 
        cout << "addRight(" << sample[i-1] <<") => "; 
        L.addRight(sample[i-1]); 
        L.display(); 
        cout << "\t Size: " << L.size() << "\n";
        assert(L.size() == i);
    }
    return 1; 
}

// Vulnerable function
template <typename Object>
int testRemove(AList<Object>& L, const int MAX_CAP = CAP) { 
    for(int i = 1; i <= MAX_CAP + 1; i++) { 
        cout << "removeLeft() => "; 
        L.removeLeft();
        L.display();  
        cout << "\t Size: " << L.size() << "\n";
    }
    return 1; 
}


int main(void) {
	srand(time(0));
    AList<int> listInt; 
    int s1[CAP]; 
    for(int i = 0; i < CAP; i++) { 
        int r = rand() % CAP + 1; 
        s1[i] = r; 
    }
    testAdd(listInt, s1); 
	testRemove(listInt); // Calling a vulnerable function
}