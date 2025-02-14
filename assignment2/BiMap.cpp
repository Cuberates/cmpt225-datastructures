#include "BiMap.h"

#include <iostream> 
#include <cassert>

using namespace std;

template<typename KeyType, typename ValType>
BiMap<KeyType, ValType>::BiMap() {

}
template<typename KeyType, typename ValType>
void BiMap<KeyType, ValType>::makeEmpty() {
	hashTable1.makeEmpty(); 
	hashTable2.makeEmpty(); 
}
template<typename KeyType, typename ValType>
int BiMap<KeyType, ValType>::getSize() const {
	int sizeHashTable1 = hashTable1.getSize(); 
	int sizeHashTable2 = hashTable2.getSize();
	assert(sizeHashTable1 == sizeHashTable2 && "Table sizes must be equal!");
	return sizeHashTable1;  
}
// insert pair <x,y>, provided x is not the 
// key of a current pair and y is not the value of 
// a current pair.  Return true iff <x,y> was inserted.
template<typename KeyType, typename ValType>
bool BiMap<KeyType, ValType>::insert( const KeyType &x, const ValType & y) {
	auto preCondition = !hashTable1.contains(x) && !hashTable2.contains(y);
	assert(preCondition && "Insertion of duplicated key!");	
	hashTable1.insert(x, y);
	hashTable2.insert(y, x);
	return 1; 	
}

template<typename KeyType, typename ValType>
bool BiMap<KeyType, ValType>::containsKey( const  KeyType& x ) const {
	return hashTable1.contains(x);
}
	// returns true if x is the key of a current pair.
template<typename KeyType, typename ValType>
bool BiMap<KeyType, ValType>::containsVal( const ValType&x ) const {
	return hashTable2.contains(x);
}
	// returns true if x is the value of a current pair.
template<typename KeyType, typename ValType>
bool BiMap<KeyType, ValType>::removeKey( const KeyType & x ) {
	// Do we have to remove the entire pair?
	auto preCondition = hashTable1.contains(x);
	assert(preCondition && "Removal of non-existent key!");
	if(preCondition) { 
		ValType val = hashTable1.getVal(x); 
		hashTable1.remove(x); 
		hashTable2.remove(val);
	}
	return 1;
}
	// removes the pair with key x if it exists.
template<typename KeyType, typename ValType>
bool BiMap<KeyType, ValType>::removeVal( const ValType & x ) {
	auto preCondition = hashTable2.contains(x);
	assert(preCondition && "Removal of non-existent value!");
	if(preCondition) { 
		ValType key = hashTable2.getVal(); 
		hashTable1.remove(key); 
		hashTable2.remove(x);
	}
	return 1;
}
	// removes the pair with values x if it exists.
template<typename KeyType, typename ValType>
const ValType & BiMap<KeyType, ValType>
::getVal( const KeyType & x ) const {
	assert(hashTable1.contains(x) && "Accessing a non-existent key!"); 
	ValType val = hashTable1.getVal(x);
	return val; 

}
	// returns the value associated with key x.
template<typename KeyType, typename ValType>
const KeyType& BiMap<KeyType, ValType>
::getKey( const ValType & x ) const {
	assert(hashTable2.contains(x) && "Accessing a non-existent value!");
	KeyType key = hashTable2.getVal(x);
	return key; 
}
