// Program Information ////////////////////////////////////////////////////////
/**
 * @file UtilityVector.h
 *
 * @brief Definition file for UtilityVector class
 * 
 * @details Specifies all member methods of the UtilityVector class
 *
 * @version 1.00 
 *          Michael Leverington (29 January 2016)
 *          Original code
 *
 * @Note Requires SimpleVector.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef UTILITYVECTOR_H
#define UTILITYVECTOR_H

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "SimpleVector.h"

using namespace std;

// Class constants ////////////////////////////////////////////////////////////

template <class DataType>
class UtilityVector: public SimpleVector<DataType>
   {
    public:

       // constants
       static const int DEFAULT_CAPACITY = 10;

       // constructors
       UtilityVector( int newCapacity = DEFAULT_CAPACITY );
       UtilityVector( int newCapacity, const DataType &fillValue );
       UtilityVector( const UtilityVector<DataType> &copiedVector ); 

       // destructor
       ~UtilityVector();

       // modifiers

          // allows copying from one index location to another 
          void copyFromTo( int indexTo, int indexFrom );

          // allows swapping from one index location to another
          void swapBetween( int oneIndex, int otherIndex );

          // allows insertion at a given index
          void insertAtIndex( int insertIndex, const DataType &itemToInsert ); 

          // allows insertion at a given index
          void removeAtIndex( int removalIndex, DataType &removedItem ); 
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef UTILITYVECTOR_H

