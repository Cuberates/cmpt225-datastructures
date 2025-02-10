#include "QuadraticProbing.h"
#include "BiMap.h"

#include <iostream> 

using namespace std;

template<typename KeyType, typename ValType>
BiMap<KeyType, ValType>::BiMap() {
	// HashTable<KeyType> domain; 
	// HashTable<ValType> coDomain; 
}
template<typename KeyType, typename ValType>
void BiMap<KeyType, ValType>::makeEmpty() {
	domain.makeEmpty(); 
	coDomain.makeEmpty(); 
}
template<typename KeyType, typename ValType>
int BiMap<KeyType, ValType>::getSize() const {
	// Since our map is bijective, size of domain == size of codomain
	int sizeDomain = domain.getSize(); 
	int sizeCoDomain = coDomain.getSize(); 
	// assert(sizeDomain == sizeCoDomain); 
	return sizeDomain; 
}
// insert pair <x,y>, provided x is not the 
// key of a current pair and y is not the value of 
// a current pair.  Return true iff <x,y> was inserted.
template<typename KeyType, typename ValType>
bool BiMap<KeyType, ValType>::insert( const KeyType &x, const ValType & y) {
	if(coDomain.contains(x) || domain.contains(y)) return 0; 
	domain.insert(x);
	coDomain.insert(y);
	return 1;
}

template<typename KeyType, typename ValType>
bool BiMap<KeyType, ValType>::containsKey( const  KeyType& x ) const {
	return domain.contains(x);
}
	// returns true if x is the key of a current pair.
template<typename KeyType, typename ValType>
bool BiMap<KeyType, ValType>::containsVal( const ValType&x ) const {
	return coDomain.contains(x);
}
	// returns true if x is the value of a current pair.
template<typename KeyType, typename ValType>
bool BiMap<KeyType, ValType>::removeKey( const KeyType & x ) {
	// Do we have to remove the entire pair?
	if(domain.contains(x)) {
		domain.remove(x);
		coDomain.remove(y);
		return 1;
	}
	return 0; 
}
	// removes the pair with key x if it exists.
template<typename KeyType, typename ValType>
bool BiMap<KeyType, ValType>::removeVal( const ValType & x ) {
	domain.remove(x);
}
	// removes the pair with values x if it exists.
template<typename KeyType, typename ValType>
const ValType & BiMap<KeyType, ValType>
::getVal( const KeyType & x ) const {
	return 1; 
}
	// returns the value associated with key x.
template<typename KeyType, typename ValType>
const KeyType& BiMap<KeyType, ValType>
::getKey( const ValType & x ) const {
	// stuff
	return 1;
}
