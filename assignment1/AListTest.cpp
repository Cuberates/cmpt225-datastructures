#include <iostream> 

#include "AList.h"

using namespace std;

#define MAX_CAPACITY 12

int main(void) {
   // Intializing the deque
   for(int t = 0; t < 2; t++) {
      AList<int> testList; 
      assert(testList.empty()); 
      assert(testList.size() == 0);
      if(!t) testList.display(); 
      else testList.ddisplay(); 
      int i = 1; 
      // Adding elements to the front
      for(i; i <= 6; i++) testList.addLeft(i);
      assert(testList.size() == 6);
      if(!t) testList.display(); 
      else testList.ddisplay(); 
      // Adding elements to the back
      for(i; i <= 12; i++) testList.addRight(i);
      assert(testList.size() == 12);
      if(!t) testList.display(); 
      else testList.ddisplay();  
      // Remove elements from the front
      for(int i = 6; i >= 1; i--) { 
         int front = testList.removeLeft();
         assert(front == i);
      }
      if(!t) testList.display(); 
      else testList.ddisplay(); 
      assert(testList.size() == 6);
      // Remove elements from the back
      for(int i = 12; i >= 7; i--) { 
         int back = testList.removeRight();
         assert(back == i);
      }
      if(!t) testList.display(); 
      else testList.ddisplay(); 
      assert(testList.size() == 0); 
      assert(testList.empty());  
   }

   // AList<int> testList; 
   // testList.ddisplay();


}