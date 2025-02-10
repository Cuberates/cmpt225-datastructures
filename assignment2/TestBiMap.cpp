#include <iostream>
// #include "BiMap.h"
#include "BiMap.cpp"

using namespace std;

// Simple main
int main( )
{
    BiMap<int, int> b1;
    b1.insert(2, 3);
    b1.insert(3, 4);
    b1.ddisplay(); 
    return 0;
}
