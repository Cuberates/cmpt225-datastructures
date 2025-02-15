/******************************************************************
**   BiMap Class, Assignment 2 Part A
**   File: BiMap.h
**   Description: Class implementation for BiMap
**   Copyright © 2025, Xuan Viet Duc Nguyen.  All rights reserved.
**   Student ID: 301626893
**   Login ID: xvn@sfu.ca
*******************************************************************
******************************************************************/

#include "QuadraticProbing.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <cassert>

using namespace std;

template <typename KeyType, typename ValType>
class HashTable {
public:
    explicit HashTable( int size = 11 ) :   array( nextPrime( size ) ) { makeEmpty( ); }
    bool contains( const KeyType & x ) const {
        return isActive( findPos( x ) );
    }
    void makeEmpty( ) {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }
    bool insert( const KeyType &x, const ValType &y ) {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].first = x;
        array[ currentPos ].second = y;
        array[ currentPos ].info = ACTIVE;

        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }
    
    bool insert( KeyType && x)
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ] = std::move( x );
        array[ currentPos ].info = ACTIVE;

        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool remove( const KeyType & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }
    // Added a method for "safely" retrieving the size of the HashTable.
    // Added a ddisplay() for debugging purposes. 

    int getSize() const { return currentSize; }

    ValType getVal(const KeyType& x) const { 
        // assert(isActive(x));
        assert(contains(x)); 
        auto pos = findPos(x); 
        return array[pos].second; 
    }

    void display() {
        cout << "--------------------------\n";
        for(auto &pair : array) { 
            if(pair.info == ACTIVE) {
                cout << pair.first << " " << pair.second << "\n";
                continue;
            }
        }  
        cout << "--------------------------\n";
    }
    void ddisplay() { 
        cout << "--------------------------\n";
        for(auto &pair : array) { 
            if(pair.info == DELETED) {
                cout << pair.first << " " << pair.second << " DELETED\n";
                continue; 
            }
            if(pair.info == ACTIVE) {
                cout << pair.first << " " << pair.second << " ACTIVE\n";
                continue;
            }
            cout << ". . EMPTY\n";
        }  
        cout << "--------------------------\n";
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };
private:
    struct HashEntry
    {
        KeyType first;
        ValType second;
        EntryType info;

        HashEntry( const KeyType & e = KeyType{ }, EntryType i = EMPTY )
        : first{ e }, info{ i } { }
        
        HashEntry( KeyType && e, EntryType i = EMPTY )
        : first{ std::move( e ) }, info{ i } { }    
    };
    
    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
    { return array[ currentPos ].info == ACTIVE; }

    int findPos( const KeyType & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );

        while( array[ currentPos ].info != EMPTY &&
            array[ currentPos ].first != x )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return currentPos;
    }

    void rehash( ) // I absolutely do not know how this works but it works so I don't want to modify anything
    {
        vector<HashEntry> oldArray = array;

        // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;

        // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE ) {
                insert( std::move( entry.first ), std::move(entry.second));
            }
                
    }

    size_t myhash( const KeyType & x ) const
    {
        static hash<KeyType> hf;
        return hf( x ) % array.size( );
    }
};


// Bijective Map class 
// Implemented with two hash tables.
template <typename KeyType, typename ValType>  
class BiMap
{  
    public:
    BiMap ();
    void makeEmpty( ); 
    int  getSize() const;
    bool insert( const KeyType &x, const ValType & y );
    bool containsKey( const  KeyType& x ) const;
    bool containsVal( const ValType&x ) const;
    bool removeKey( const KeyType & x );
    bool removeVal( const ValType & x );
    const ValType getVal( const KeyType & x ) const;
    const KeyType getKey( const ValType & x ) const;
    void ddisplay() {hashTable1.ddisplay(); hashTable2.ddisplay();}
    void display() {hashTable1.display();}


    private:
    HashTable<KeyType, ValType> hashTable1; 
    HashTable<ValType, KeyType> hashTable2; 
};


template<typename KeyType, typename ValType>
BiMap<KeyType, ValType>::BiMap() {}

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
		KeyType key = hashTable2.getVal(x); 
		hashTable1.remove(key); 
		hashTable2.remove(x);
	}
	return 1;
}
	// removes the pair with values x if it exists.
template<typename KeyType, typename ValType>
const ValType BiMap<KeyType, ValType>
::getVal( const KeyType & x ) const {
	assert(hashTable1.contains(x) && "Accessing a non-existent key!"); 
	ValType val = hashTable1.getVal(x); 
	return val; 
}
	// returns the value associated with key x.
template<typename KeyType, typename ValType>
const KeyType BiMap<KeyType, ValType>
::getKey( const ValType & x ) const {
	assert(hashTable2.contains(x) && "Accessing a non-existent value!");
	KeyType key = hashTable2.getVal(x);
	return key; 
}
