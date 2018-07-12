// Program Information ////////////////////////////////////////////////////////
/**
 * @file SimpleVector.h
 *
 * @brief Definition file for SimpleVector class
 * 
 * @details Specifies all member methods of the SimpleVector class
 *
 * @version 1.10
 *          Michael Leverington (19 January 2016)
 *          Updated for use with linked list
 * 
 *          1.00 
 *          Michael Leverington (30 August 2015)
 *          Original code
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>
#include <cstdlib>

using namespace std;

// Class constants /////////////////////////////////////////////////////////////

template <class DataType>
class DataNode
   {
    public:

       // DataType must have default constructor and assignment operator
       DataType dataItem;

       DataNode( const DataType &inData, 
                 DataNode<DataType> *inPrevPtr = NULL, 
                 DataNode<DataType> *inNextPtr = NULL );

       DataNode<DataType> *previous;
       DataNode<DataType> *next;
   };

template <class DataType>
class SimpleVector
   {
    public:

       // constants local to class
       static const int LARGE_STR_LEN = 100;
       static const int DEFAULT_CAPACITY = 10;
       static const int DISPLAY_WIDTH = 5;
       static const char SPACE = ' ';
       static const char COLON = ':';
       static const char LEFT_BRACKET = '[';
       static const char RIGHT_BRACKET = ']';

       // constructors
       SimpleVector( int newCapacity = DEFAULT_CAPACITY );
       SimpleVector( int newCapacity, const DataType &fillValue );
       SimpleVector( const SimpleVector<DataType> &copiedVector ); 

       // destructor
       ~SimpleVector( );

       // assignment
       const SimpleVector<DataType> &operator = 
                                   ( const SimpleVector<DataType> &rhVector );

       // accessors
       int getCapacity() const;
       int getSize() const;
       void showSVStructure( char IDChar );

       // index access
       void setAtIndex( int index, const DataType &inData ) 
                                                        throw ( logic_error );
       const DataType &getAtIndex( int index ) throw ( logic_error );

    // modifiers

       // allows vector to be resized (i.e., capacity changed) 
       //   to specified quantity
       //   Note: data is not checked and may be lost for downward resize
       void resize( int newCapacity );

       // increment/decrement don't affect class
       //    but allows programmer to keep track of size inside vector
       void incrementSize();
       void decrementSize();
       void zeroSize();

    private:

       int vectorCapacity;
       int vectorSize;
       int currentIndex;
       DataNode<DataType> *currentPtr;
       DataNode<DataType> *listHead;

       void copyVectorObject( const SimpleVector<DataType> &inData );
       DataNode<DataType> *getPointerToIndex( int index );
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef SIMPLEVECTOR_H

