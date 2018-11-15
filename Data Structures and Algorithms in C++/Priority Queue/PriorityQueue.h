// Program Information ////////////////////////////////////////////////////////
/**
 * @file PriorityQueue.h
 *
 * @brief Definition file for PriorityQueue class
 * 
 * @details Specifies all member methods of the PriorityQueue class,
 *          which uses the UtilityVector class
 *
 * @version 1.10
 *          Michael Leverington (30 January 2016)
 *          Updated for use with UtilityVector
 * 
 *          1.00 
 *          Michael Leverington (07 September 2015)
 *          Original code
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_PRIORITYQUEUE_H
#define CLASS_PRIORITYQUEUE_H

// Header files ///////////////////////////////////////////////////////////////

#include <stdexcept>
#include <iostream>
#include "StudentType.h"
#include "UtilityVector.h"

using namespace std;

// Class constants ////////////////////////////////////////////////////////////

   // None

// Class definition ///////////////////////////////////////////////////////////

template <class DataType>
class PriorityQueue
   {
    public:

       // class constants
       static const int DEFAULT_CAPACITY = 10;
       static const int DEFAULT_NUM_PRIORITIES = 5;
       static const int DATA_SET_STR_LEN = 100;
       static const char TAB = '\t';
       static const char SPACE = ' ';

       // constructors
       PriorityQueue( int initialCapacity = DEFAULT_CAPACITY,
                                 int numPriorities = DEFAULT_NUM_PRIORITIES );
       PriorityQueue( const PriorityQueue &copiedQueue ); 

       // destructor
       ~PriorityQueue();

       // assignment
       const PriorityQueue &operator = 
                                   ( const PriorityQueue<DataType> &rhPQueue );

       // modifiers
       void enqueue( const DataType &dataItem ) throw ( logic_error );

       // accessors
       void dequeue( DataType &dQData ) throw ( logic_error );
       void peekAtFront( DataType &pkData ) throw ( logic_error );
       bool isEmpty() const;
       void showStructure( char ID );

    private:

       // max limit of priorities
       int maxPriorities;

       UtilityVector<DataType> qData;
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_PRIORITYQUEUE_H

