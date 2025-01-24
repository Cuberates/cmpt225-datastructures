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

template <typename Object>
int testRemove(AList<Object>& L, const int MAX_CAP = CAP) { 
    for(int i = 1; i <= MAX_CAP; i++) { 
        int r = rand() % 2 + 1; 
        if(r % 2 == 0) { 
            cout << "removeLeft() => "; 
            L.removeLeft();
            L.display();  
            cout << "\t Size: " << L.size() << "\n";
            assert(L.size() == CAP-i);
            continue; 
        } 
        cout << "removeRight() => "; 
        L.removeRight(); 
        L.display(); 
        cout << "\t Size: " << L.size() << "\n";
        assert(L.size() == CAP-i); 
    }
    return 1; 
}

int main(void) {
    srand(time(0));
    cout << "---- Testing on listInt ---- \n";
    AList<int> listInt; 
    int s1[CAP]; 
    for(int i = 0; i < CAP; i++) { 
        int r = rand() % CAP + 1; 
        s1[i] = r; 
    }
    testAdd(listInt, s1); 
    testRemove(listInt); 
    listInt.ddisplay();
    cout << "\n";

    cout << "---- Testing on listFloat ---- \n";
    AList<float> listFloat;
    float s2[CAP]; 
    for(int i = 0; i < CAP; i++) { 
        float r1 = rand() % CAP + 1;
        float r2 = rand() % CAP + 1;  
        s2[i] = r1 / r2; 
    }
    testAdd(listFloat, s2); 
    testRemove(listFloat); 
    listFloat.ddisplay();
    cout << "\n";

    cout << "---- Testing on listChar ---- \n";
    AList<char> listChar; 
    char s3[CAP];
    for(int i = 0; i < CAP; i++) { 
        int r = rand() % 26; 
        s3[i] = r + 'A'; 
    }
    testAdd(listChar, s3); 
    testRemove(listChar); 
    listChar.ddisplay();
    cout << "\n";
    

}