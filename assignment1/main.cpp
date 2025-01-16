#include <iostream> 
#include "AList.h"

using namespace std;

int main(void) {
    int option, data; 
    AList<int> myList;  
    while(true) {
        cout << "Welcome to AList testing program! ------ \n";
        cout << "1. Insert left" << "\n";
        cout << "2. Insert right" << "\n";
        cout << "3. Remove left" << "\n";
        cout << "4. Remove right" << "\n";
        cout << "5. Clear" << "\n";
        cout << "Choose: "; 
        cin >> option;
        switch(option) { 
            case 1: 
                assert()
                cin >> data;
                myList.addLeft(data);
                break; 
            case 2: 
                cin >> data; 
                myList.addRight(data);
                break; 
            case 3: 
                myList.removeLeft();
                break;  
            case 4: 
                myList.removeRight(); 
                break;
            case 5: 
                myList.clear();
                break; 
        }
        myList.ddisplay();
    } 
}