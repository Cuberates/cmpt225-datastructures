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

        array[ currentPos ].element = x;
        array[ currentPos ].image = y;
        array[ currentPos ].info = ACTIVE;

        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }
    
    bool insert( KeyType && x )
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

    ValType getVal(const KeyType x) const { 
        assert(isActive(x));
        int pos = findPos(x); 
        return array[pos].image; 
    }

    void display() {
        cout << "--------------------------\n";
        for(auto &pair : array) { 
            // if(pair.info == DELETED) {
            //     cout << pair.element << " " << pair.image << " DELETED\n";
            //     continue; 
            // }
            if(pair.info == ACTIVE) {
                cout << pair.element << " " << pair.image << " ACTIVE\n";
                continue;
            }
            // cout << ". . EMPTY\n";
        }  
        cout << "--------------------------\n";
    }
    void ddisplay() { 
        // cout << getSize() << "\n";
        cout << "--------------------------\n";
        for(auto &pair : array) { 
            if(pair.info == DELETED) {
                cout << pair.element << " " << pair.image << " DELETED\n";
                continue; 
            }
            if(pair.info == ACTIVE) {
                cout << pair.element << " " << pair.image << " ACTIVE\n";
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
        KeyType element;
        ValType image;
        EntryType info;

        HashEntry( const KeyType & e = KeyType{ }, EntryType i = EMPTY )
        : element{ e }, info{ i } { }
        
        HashEntry( KeyType && e, EntryType i = EMPTY )
        : element{ std::move( e ) }, info{ i } { }    
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
            array[ currentPos ].element != x )
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
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ) );
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
    const ValType& getVal( const KeyType & x ) const;
    const KeyType& getKey( const ValType & x ) const;
    void ddisplay() {hashTable1.ddisplay(); hashTable2.ddisplay();}

    private:

    HashTable<KeyType, ValType> hashTable1; 
    HashTable<ValType, KeyType> hashTable2; 
};