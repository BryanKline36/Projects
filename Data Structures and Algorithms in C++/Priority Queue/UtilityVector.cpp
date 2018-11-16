// Program Information ////////////////////////////////////////////////////////
/**
 * @file UtilityVector.cpp
 * 
 * @brief Implementation file for UtilityVector
 * 
 * @author Bryan Kline
 *
 * @details Implements all member methods of the UtilityVector
 *
 * @version 1.00 (08 February 2016)
 *
 * @Note Requires UtilityVector.h, SimpleVector.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef UTILITYCLASS_CPP
#define UTILITYCLASS_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "UtilityVector.h"
#include "SimpleVector.h"

//UtilityVector class structure member implementations ////////////////////////

/**
 * @brief Default/Initialization UtilityVector constructor
 *
 * @details Constructs UtilityVector with either default or given capacity
 *          
 * @pre Assumes Uninitialized UtilityVector object
 *
 * @post List of nodes is created for use as array
 *
 * @par Algorithm 
 *      Initializes class by calling parent constructor
 * 
 * @exception None
 *
 * @param [in] newCapacity
 *             Desired default or user-provided capacity (int)
 *
 * @return None
 *
 * @note None
 */
template <typename DataType>
UtilityVector<DataType>::UtilityVector
       (
        int newCapacity // in: initial capacity for vector
       )
     : SimpleVector<DataType>( newCapacity )
{
    // construct from parent
}

/**
 * @brief Initialization fill constructor
 *
 * @details Constructs object with all elements filled
 *          
 * @pre Assumes uninitialized UtilityVector object
 *
 * @post list of nodes is created for use as array
 *
 * @par Algorithm 
 *      Initializes class by calling parent constructor
 * 
 * @exception None
 *
 * @param [in] newCapacity 
 *             User-defined object capacity (int)
 *
 * @param [in] fillValue 
 *             DataType fill value (DataType)
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
UtilityVector<DataType>::UtilityVector
       ( 
        int newCapacity,          // in: new vector capacity
        const DataType &fillValue // in: fill value for all elements
       )
     : SimpleVector<DataType>( newCapacity, fillValue )
{
    // construct from parent
}

/**
 * @brief Copy constructor
 *
 * @details Creates local copy of all contents of parameter object
 *          
 * @pre Assumes uninitialized UtilityVector object
 *
 * @par Algorithm 
 *      Calls parent constructor for copy process
 * 
 * @exception None
 *
 * @param [in] copiedVector
 *             Incoming Vector object (UtilityVector<DataType>)
 *
 * @return None
 *
 * @note None
 */
template <typename DataType>
UtilityVector<DataType>::UtilityVector
       (
        const UtilityVector<DataType> &copiedVector // in: other UtilityVector
                                                    // object
       )
     : SimpleVector<DataType>( copiedVector )
{
    // construct parent
}

/**
 * @brief Object destructor
 *
 * @details Removes or verifies removal of all data in UtilityVector
 *          
 * @pre Assumes UtilityVector capacity >= 0
 *
 * @par Algorithm
 *      Calls parent destructor
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note None
 */
template <typename DataType>
UtilityVector<DataType>::~UtilityVector
       (
        // no parameters
       )
{
    // parent class (SimpleVector) destructs
}

/**
 * @brief Copies data between elements
 *
 * @details Copies DataType value from one vector element to another
 *        using indices
 *          
 * @pre Assumes data found in elements, and that vectorCapacity > indexFrom 
 *              and vectorCapacity > indexTo
 *
 * @post vector element at indexTo contains the data found
 *       at element at indexFrom
 *
 * @par Algorithm 
 *      Acquires data using getAtIndex,
 *      assigns data using setAtIndex
 * 
 * @exception Boundary
 *            Exception called if from or to indices are out of bounds
 *
 * @param [in] indexTo
 *             Index for element to which data is copied (int)
 *             
 * @param [in] indexFrom
 *             Index for element from which data is copied (int)
 *             
 * @return None
 *
 * @note None
 */
template <typename DataType>
void UtilityVector<DataType>::copyFromTo
     (
      int indexTo,   // in: index of to element
      int indexFrom  // in: index of from element
     )
{
    DataType temp = this->getAtIndex( indexFrom );

    this->setAtIndex( indexTo, temp );
}

/**
 * @brief Swaps data between elements
 *
 * @details Acquires DataType quantities from two elements, swaps between them
 *          
 * @pre Assumes data found in elements, and that vectorCapacity > oneIndex 
 *              and vectorCapacity > otherIndex
 *
 * @post Vector element at oneIndex contains the data found
 *       at element at otherIndex, and vector element at otherIndex
 *       contains data found at oneIndex
 *
 * @par Algorithm 
 *      Acquires data for both items using getAtIndex,
 *      assigns data to opposite indices using setAtIndex
 * 
 * @exception Boundary
 *            Exception called if one or other indices are out of bounds
 *
 * @param [in] oneIndex
 *             Index for element of one of two elements to be swapped (int)
 *             
 * @param [in] otherIndex
 *             Index for element of other of two elements to be swapped (int)
 *             
 * @return None
 *
 * @note None
 */
template <typename DataType>
void UtilityVector<DataType>::swapBetween
     (
      int oneIndex,   // in: index of to element
      int otherIndex  // in: index of from element
     )
{
    DataType oneTemp = this->getAtIndex( oneIndex ); 
    DataType otherTemp = this->getAtIndex( otherIndex );

    this->setAtIndex(oneIndex, otherTemp );
    this->setAtIndex(otherIndex, oneTemp );
}

/**
 * @brief Inserts DataItem at specified index
 *
 * @details Shifts all data above inserted location up
 *          
 * @pre Assumes vectorSize data is correct
 *
 * @pre Assumes data found in elements, 
 *              vectorCapacity > vectorSize
 *
 * @post All data is moved up from insertion location,
 *       given DataType item inserted at insertion location
 *
 * @par Algorithm 
 *      Copies data from each element up to next element using copyFromTo,
 *      inserts item using setAtIndex
 * 
 * @exception Boundary
 *            Exception called if one or other indices are out of bounds
 *
 * @param [in] insertIndex
 *             Index for element of element to acquire inserted data (int)
 *             
 * @param [in] itemToInsert
 *             Data item to be inserted into vector (int)
 *             
 * @return None
 *
 * @note None
 */
template <typename DataType>
void UtilityVector<DataType>::insertAtIndex
     (
      int insertIndex,              // in: index at which to insert data
      const DataType &itemToInsert  // in: DataType data to be inserted
     )
{
    int counter;
    int size = this->getSize();
    int capacity = this->getCapacity();

    // condition: insertIndex is valid and capacity is greater than size
    if( insertIndex >= 0 && insertIndex < capacity && capacity > size
                                                   && ( insertIndex <= size ) )
    {
        // condition: the UtilityVector object is not empty
        if( size > 0 )
        {
            for( counter = ( size - 1 ); counter >= insertIndex; counter-- )
            {
                copyFromTo( ( counter + 1 ), counter );
            }
        }

        this->setAtIndex( insertIndex, itemToInsert ); 
        this->incrementSize();
    }
}

/**
 * @brief Removes DataItem at specified index
 *
 * @details Shifts all data above removed location down
 *          
 * @pre Assumes vectorSize data is correct
 *
 * @pre Assumes data found in elements
 *
 * @post All data is moved down by one element to the removal location,
 *       given DataType item removed at removal location,
 *       and passed back to calling function
 *
 * @par Algorithm
 *      Acquired data item from element 
 *      Copies data from each element down by one element to the removed index
 *      using copyFromTo, passes item back to calling function
 * 
 * @exception Boundary
 *            Exception called if one or other indices are out of bounds
 *
 * @param [in] removalIndex
 *             Index of element to be removed from vector (int)
 *             
 * @param [out] removedItem
 *              Data removed from vector and passed back to calling function
 *              (DataType)
 *             
 * @return None
 *
 * @note None
 */template <typename DataType>
void UtilityVector<DataType>::removeAtIndex
     (
      int removalIndex,              // in: index at which to remove data
      DataType &removedItem          // out: DataType data to be removed
     )
{
    int counter;
    int size = this->getSize();
    int capacity = this->getCapacity();

    // condition: removalIndex is valid
    if( removalIndex >= 0 && removalIndex < capacity 
                                                   && ( removalIndex < size ) )
    {
        removedItem = this->getAtIndex( removalIndex );

        if( size > 1 )
        {  
            for( counter = removalIndex; counter < ( size - 1 ); counter++ )
            {
                copyFromTo( counter, ( counter + 1 ) );
            } 
            
            this->decrementSize();
        }
        else
        {
            this->zeroSize();
        }
    }    
}

// Terminating precompiler directives  ////////////////////////////////////////

#endif // ifndef UTILITYCLASS_CPP

