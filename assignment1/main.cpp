#include <iostream> 

#include "AList.h"

using namespace std;

#define MAX_CAPACITY 12

int main(void) {
    int option, data; 
    AList<int> myList;  
    while(true) {
        system("clear");
        myList.ddisplay();
        cout << "\n\n"; 
        cout << "Testing the AList class via operations! ------ \n";
        cout << "Assertion: theSize <= theCapacity \n"; 
        cout << "1. Insert left" << "\n";
        cout << "2. Insert right" << "\n";
        cout << "3. Remove left" << "\n";
        cout << "4. Remove right" << "\n";
        cout << "5. Clear" << "\n";
        cout << "Choose: "; 
        cin >> option;
        switch(option) { 
            case 1: 
                assert(myList.size() < MAX_CAPACITY);
                cin >> data;
                myList.addLeft(data);
                break; 
            case 2: 
                assert(myList.size() < MAX_CAPACITY);
                cin >> data; 
                myList.addRight(data);
                break; 
            case 3: 
                assert(myList.size() > 0);
                myList.removeLeft();
                break;  
            case 4: 
                assert(myList.size() > 0);  
                myList.removeRight(); 
                break;
            case 5: 
                myList.clear();
                break; 
        }
    } 
}