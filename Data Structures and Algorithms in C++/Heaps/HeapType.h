// Program Information ////////////////////////////////////////////////////////
/**
 * @file HeapType.h
 *
 * @brief Definition file for HeapType class
 * 
 * @details Specifies all member methods of the HeapType class
 *
 * @version 1.00 
 *          Michael Leverington (02 April 2016)
 *          Original code
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef HEAPTYPE_H
#define HEAPTYPE_H

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>
#include <cstdlib>

using namespace std;

// Class declarations /////////////////////////////////////////////////////////

template <class DataType>
class HeapType
   {
    public:

       // class static constants
       static const int DEFAULT_CAPACITY = 10;
       static const int BASE_TWO = 2;
       static const char SPACE = ' ';

       // constructors
       HeapType();
       HeapType( const HeapType<DataType> &copiedVector ); 

       // destructor
       ~HeapType( );

       // assignment
       const HeapType<DataType> &operator = 
                                   ( const HeapType<DataType> &rhVector );

       // accessors

          // shows heap structure in tree form
          void showHPStructure( char IDChar );

          // gets size of heap
          int getSize() const;

          // reports if heap empty
          bool isEmpty() const;

       // modifiers

          // adds (inserts) data in heap, uses recursive shift up
          void add( const DataType &inData );

          // removes data from heap, uses recursive shift down
          bool remove( DataType &removeData );

          // clears size of heap
          void clear();

    private:

       // recursively shifts element up heap after add operation
       void shiftUp( int currentIndex );

       // recursively shifts element down heap after remove operation
       void shiftDown( int currentIndex );

       // checks for need to resize during add operation
       // increases size by 125%
       void checkForResize();

       // utility to copy vector from one location to other
       void copyHeapVector( DataType *destination, 
                                          const DataType *source, int count );

       // swaps data element locations using given indices
       void swap( int one, int other );

       // gets height of heap
       int getHeight() const;

       // calculates display spacing depending on row
       // assumes bottom row is always #1
       void getSpacing( int row, int &firstSpaces, int &dividerSpaces ) const;

       // calculates simple integer power, as needed for tree calculations
       int toPower( int base, int exponent ) const;

       // displays integer as three digits, centers one digit,
       // adds leading zero to two digits, normally displays three digits
       void displayInt( int valueIndex ) const;

       // displays given number of characters
       void displayChars( int numChars, char outChar ) const;

       // local data
       int heapCapacity;
       int heapSize;
       DataType *heapVector;
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef HEAPTYPE_H

