// Program Information ////////////////////////////////////////////////////////
/**
 * @file SimpleVector.cpp
 * 
 * @brief Implementation file for SimpleVector class
 * 
 * @author Michael Leverington
 *
 * @details Implements all member methods of the SimpleVector class
 *
 * @version 1.10
 *          Michael Leverington (19 January 2016)
 *          Updated for use with linked list
 * 
 *          1.00 
 *          Michael Leverington (30 August 2015)
 *          Original code
 *
 * @Note Requires SimpleVector.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef SIMPLEVECTOR_CPP
#define SIMPLEVECTOR_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "SimpleVector.h"

/**
 * @brief Default node constructor
 *
 * @details Constructs node with given data
 *          
 * @pre assumes DataType has default constructor & assignment operator
 *
 * @post member values dataItem, previous, and next are initialized
 *
 * @par Algorithm 
 *      initialization constructor operation
 * 
 * @exception None
 *
 * @param [in] inData 
 *             DataType data passed into constructor
 * 
 *        [in] inPrevPtr
 *             previous pointer for node, defaults to NULL
 *
 *        [in] inNextPtr
 *             next pointer for node, defaults to NULL
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
DataNode<DataType>::DataNode
       (
        const DataType &inData,          // new data for node
        DataNode<DataType> *inPrevPtr,   // previous node pointer
        DataNode<DataType> *inNextPtr    // next node pointer
       )
    : dataItem( inData ), 
      previous( inPrevPtr ), 
      next( inNextPtr )
   {
    // data loaded via initializers
   }

/**
 * @brief Default/Initialization SimpleVector constructor
 *
 * @details Constructs SimpleVector with either default or given capacity
 *          
 * @pre assumes uninitialized SimpleVector object
 *
 * @post list of nodes is created for use as array
 *
 * @post member values vectorCapacity and vectorSize are first initialized
 *       in the constructor
 *
 * @post member values vectorCapacity, vectorSize, currentIndex,
 *       currentPtr, and listHead are initialized in resize
 *
 * @par Algorithm 
 *      sets initial values to start resize,
 *      then calls resize
 * 
 * @exception None
 *
 * @param [in] newCapacity
 *             desired default or user-provided capacity
 *
 * @return None
 *
 * @note None
 */
template <class DataType> 
SimpleVector<DataType>::SimpleVector
       (
        int newCapacity
       )
    : vectorCapacity( 0 ), vectorSize( 0 )
   {
    resize( newCapacity );
   }

/**
 * @brief Initialization fill constructor
 *
 * @details Constructs object with all elements filled
 *          
 * @pre assumes uninitialized SimpleVector object
 *
 * @post list of nodes is created for use as array
 *
 * @post member values vectorCapacity 
 *       and vectorSize are first initialized in the constructor
 *
 * @post member values vectorCapacity, vectorSize, currentIndex,
 *       currentPtr, and listHead are initialized in resize
 *
 * @par Algorithm 
 *      sets initial values to start resize,
 *      then calls resize,
 *      then fills all nodes with data,
 *      sets vectorSize to vectorCapacity
 * 
 * @exception None
 *
 * @param [in] newCapacity 
 *             user-defined object capacity
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
SimpleVector<DataType>::SimpleVector
       ( 
        int newCapacity,          // in: new vector capacity
        const DataType &fillValue // in: fill value for all elements
       )
     : vectorCapacity( 0 ), vectorSize( 0 )
   {
    int index;
    DataNode<DataType> *currentPtr;

    resize( newCapacity );

    currentPtr = listHead;

    for( index = 0; index < vectorCapacity; 
                                      currentPtr = currentPtr->next, index++ )
       {
        currentPtr->dataItem = fillValue;
       }

    vectorSize = index;
   }

/**
 * @brief Copy constructor
 *
 * @details Creates local copy of all contents of parameter object
 *          
 * @pre Assumes uninitialized SimpleVector object
 *
 * @post member values vectorCapacity and vectorSize are first initialized
 *       in the constructor
 *
 * @post member values vectorCapacity, vectorSize, currentIndex,
 *       currentPtr, and listHead are set in copyVectorObject
 *
 * @par Algorithm 
 *      sets initial values to start copyVectorObject,
 *      then calls copyVectorObject,
 *      which sets vectorCapacity, vectorSize, currentIndex, currentPtr
 * 
 * @exception None
 *
 * @param [in] copiedVector
 *             incoming Vector object
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
SimpleVector<DataType>::SimpleVector
       ( 
        const SimpleVector<DataType> &copiedVector // in: vector to copy
       )
     : vectorCapacity( 0 ), vectorSize( 0 )
   {
    copyVectorObject( copiedVector );
   }

/**
 * @brief object destructor
 *
 * @details removes or verifies removal of all data in SimpleVector
 *          
 * @pre assumes SimpleVector capacity >= 0
 *
 * @post all linked list nodes are removed, using resize
 *
 * @par Algorithm
 *      calls resize function, which handles all conditions
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
SimpleVector<DataType>::~SimpleVector
       (
        // no parameters
       )
   {
    resize( 0 );
   }

/**
 * @brief Overloaded assignment operation
 *
 * @details Assigns data from right-hand object to this object
 *          
 * @pre no assumptions made about this object prior to assignment
 *
 * @post object contains a complete data copy of assigned right-hand object
 *
 * @par Algorithm 
 *      checks for not assigning to self,
 *      then calls copyVectorObject, which handles all condtions
 * 
 * @exception None
 *
 * @param [in] rhVector
 *             SimpleVector object to be assigned
 *
 * @return Reference to this object
 *
 * @note None
 */
template <class DataType>
const SimpleVector<DataType> &SimpleVector<DataType>::operator = 
       (
        const SimpleVector<DataType> & rhVector // in: assigned right side
       )
   {
    if( this != &rhVector )
       {
        copyVectorObject( rhVector );
       }

    return *this; 
   }

/**
 * @brief SimpleVector capacity accessor
 *
 * @details None
 *          
 * @pre SimpleVector has some capacity >= 0
 *
 * @post No change in data, capacity returned
 *
 * @par Algorithm 
 *      returns vectorCapacity as value
 * 
 * @exception None
 *
 * @param None
 *
 * @return SimpleVector capacity
 *
 * @note None
 */
template <class DataType>
int SimpleVector<DataType>::getCapacity
       (
        // no parameters
       ) const
   {
    return vectorCapacity;
   }

/**
 * @brief SimpleVector size accessor
 *
 * @details None
 *          
 * @pre SimpleVector has some size >= 0
 *
 * @post No change in data, size returned
 *
 * @par Algorithm 
 *      returns vectorSize as value
 * 
 * @exception None
 *
 * @param None
 *
 * @return SimpleVector size
 *
 * @note None
 */
template <class DataType>
int SimpleVector<DataType>::getSize
       (
        // no parameters
       ) const
   {
    return vectorSize;
   }

/**
 * @brief SimpleVector set element data method
 *
 * @details allows assignment of data to element in this SimpleVector
 *          
 * @pre Assumes initialized SimpleVector
 *
 * @post Assigns new value to element and/or returns value
 *
 * @par Algorithm 
 *      Finds node related to index, assigns data to node
 * 
 * @exception throws logic error if index is out of bounds
 *
 * @param [in] index 
 *             index of element to be assigned
 *
 * @param [in] inData
 *             new data to be set at index
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
void SimpleVector<DataType>::setAtIndex
       ( 
        int index,              // in: index for array element
        const DataType &inData  // in: data value to be set
       ) 
     throw ( logic_error )
   {
    DataNode<DataType> *assignPtr;

    if ( index >= 0 && index < vectorCapacity )
       {       
        assignPtr = getPointerToIndex( index );

        assignPtr->dataItem = inData;
       }

    else
       {
        throw logic_error( "ERROR: Array index out of bounds" );
       }
   }

/**
 * @brief SimpleVector get element data method
 *
 * @details allows assignment of data to element in this SimpleVector
 *          
 * @pre Assumes initialized SimpleVector
 *
 * @post Returns value at index as const quantity
 *
 * @par Algorithm 
 *      Finds node related to index, returns value
 * 
 * @exception throws logic error if index is out of bounds
 *
 * @param [in] index of element to be retrieved
 *
 * @return Copy of data value at index
 *
 * @note None
 */
template <class DataType>
const DataType &SimpleVector<DataType>::getAtIndex
       ( 
        int index // in: index for array element
       )
         throw ( logic_error )
   {
    DataNode<DataType> *result;

    if ( index >= 0 && index < vectorCapacity )
       {       
        result = getPointerToIndex( index );

        return result->dataItem;
       }

    else
       {
        throw logic_error( "ERROR: Array index out of bounds" );
       }
   }

/**
 * @brief SimpleVector resize (i.e., change capacity) operation
 *
 * @details Changes SimpleVector capacity to amount given in parameter
 *          
 * @pre Assumes SimpleVector initialized to capacity >= 0
 *
 * @post SimpleVector capacity is changed to requested amount
 *
 * @par Algorithm 
 *      For condition: empty SimpleVector and newCapacity > 0,
 *      starts by creating head node
 * 
 * @par Algorithm 
 *      For condition: newCapacity > vectorCapacity,
 *      adds nodes as needed, updates vectorCapacity
 *
 * @par Algorithm 
 *      For condition: newCapacity < vectorCapacity and vectorCapacity > 1,
 *      removes nodes previous to head, updates vectorCapacity
 *
 * @par Algorithm 
 *      For condition: newCapacity == 0,
 *      removes last node, sets head to NULL, vectorCapacity to 0
 *  
 * @par Algorithm 
 *      For all conditions:
 *      resets index to zero and related node pointer to head
 *  
 * @par Algorithm 
 *      For condition: empty SimpleVector and newCapacity == 0,
 *      does nothing
 * 
 * @exception None
 *
 * @param [in] new capacity requested
 *
 * @return None
 *
 * @note Makes no distinction about stored data;
 *       if capacity is reduced, data may be lost
 */
template <class DataType>
void SimpleVector<DataType>::resize
       ( 
        int newCapacity      // in: new capacity value
       )
   {
    DataType newData;
    DataNode<DataType> *current, *toBeDeleted;
    int smallestCircListSize = 2;

    if( newCapacity != vectorCapacity )
       {
        if( vectorCapacity == 0 )
           {
            listHead = new DataNode<DataType>( newData );

            listHead->next = listHead->previous = listHead;

            vectorCapacity = 1;
           }

        current = listHead->previous;

        while( vectorCapacity < newCapacity )
           {
            current->next 
                       = new DataNode<DataType>( newData, current, listHead );

            current = current->next;

            listHead->previous = current;

            vectorCapacity++;
           }

        while( newCapacity < vectorCapacity 
                                   && vectorCapacity >= smallestCircListSize )
           {
            toBeDeleted = listHead->previous;

            listHead->previous = listHead->previous->previous;
    
            listHead->previous->next = listHead;

            delete toBeDeleted;

            vectorCapacity--;
           }

        if( newCapacity == 0 && vectorCapacity > 0 )
           {
            delete listHead;

            listHead = NULL;

            vectorCapacity = 0;
           }

        if( vectorCapacity < vectorSize )
           {
            vectorSize = vectorCapacity;
           }

        currentPtr = listHead;

        currentIndex = 0;
       }
   }

/**
 * @brief SimpleVector size mutator - increase
 *
 * @details increases SimpleVector size count; has no impact on data
 *          
 * @pre Assumes SimpleVector initialize to capacity >= 0
 *
 * @post SimpleVector size value is incremented
 *
 * @par Algorithm 
 *      Increment size value
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note Provided as convenience for user; has no impact on SimpleVector data
 */
template <class DataType>
void SimpleVector<DataType>::incrementSize
       (
        // no parameters
       )
   {
    vectorSize++;
   }

/**
 * @brief SimpleVector size mutator - decrease
 *
 * @details decreases SimpleVector size count; has no impact on data
 *          
 * @pre Assumes SimpleVector initialize to capacity >= 0
 *
 * @post SimpleVector size value is decremented
 *
 * @par Algorithm 
 *      Decrement size value
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note Provided as convenience for user; has no impact on SimpleVector data
 */
template <class DataType>
void SimpleVector<DataType>::decrementSize
       (
        // no parameters
       )
   {
    vectorSize--;
   }

/**
 * @brief SimpleVector size mutator - zero
 *
 * @details Sets SimpleVector size count to zero; has no impact on data
 *          
 * @pre Assumes SimpleVector initialize to capacity >= 0
 *
 * @post SimpleVector size value is set to zero
 *
 * @par Algorithm 
 *      Set size value to zero
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note Provided as convenience for user; has no impact on SimpleVector data
 */
template <class DataType>
void SimpleVector<DataType>::zeroSize
       (
        // no parameters
       )
   {
    vectorSize = 0;
   }

/**
 * @brief SimpleVector copy utility
 *
 * @details Copies the data from a complete object into this object
 *          
 * @pre No assumption of initialization
 *
 * @post Object contains copy of data and states from copied object
 *
 * @par Algorithm 
 *      this object is resized to copied object capacity
 *      if copied object's capacity > 0,
 *      copies head data, then copies subsequent elements as needed,
 *      updates current index and pointer during copy
 *      copies copied object size to this object,
 *      copies copied object index and related pointer to this object
 * 
 * @exception None
 *
 * @param [in] copied SimpleVector object
 *
 * @return None
 *
 * @note Overwrites any data previously in this object
 */
template <class DataType>
void SimpleVector<DataType>::copyVectorObject
       ( 
        const SimpleVector<DataType> &inData // in: incoming vector, complete
       )
   {
    int index = 0;
    DataType dataVal;
    DataNode<DataType> *thisPtr, *inPtr = inData.listHead;

    resize( inData.vectorCapacity );

    thisPtr = listHead;

    if( inData.vectorCapacity > 0 )
       {
        while( index < inData.vectorCapacity )
           {
            thisPtr->dataItem = inPtr->dataItem;

            thisPtr = thisPtr->next;

            inPtr = inPtr->next;

            index++;
           }
       }

    vectorSize = inData.vectorSize;

    currentIndex = 0;

    currentPtr = listHead;
   }

/**
 * @brief SimpleVector array element access utility
 *
 * @details Specified element data accessed by index and returned
 *          
 * @pre Assumes initialized SimpleVector where 0 <= index < vectorCapacity
 *
 * @post Returns object at index
 *
 * @par Algorithm 
 *      Identifies requested index position closest to current index position,
 *      moves index and node pointer to that position
 *
 * @par Algorithm
 *      If new index > current index and distance 
 *      to new index < vectorCapacity /2, increments upward
 * 
 * @par Algorithm
 *      If new index < current index and distance 
 *      to new index > vectorCapacity /2, increments upward
 * 
 * @par Algorithm
 *      If new index < current index and distance 
 *      to new index < vectorCapacity /2, increments downward
 * 
 * @par Algorithm
 *      If new index > current index and distance 
 *      to new index > vectorCapacity /2, increments upward
 * 
 * @exception None
 *
 * @param [in] index
 *             index of element to be accessed
 *
 * @return pointer to data item, or NULL, as specified
 *
 * @note None
 */
template <class DataType>
DataNode<DataType> *SimpleVector<DataType>::getPointerToIndex
       ( 
        int index    // in: index to find node
       )
   {
    bool lowToHigh= index > currentIndex;
    bool highToLow = !lowToHigh;
    bool closeToIndex = ( abs( index - currentIndex ) < ( vectorCapacity / 2 ) );
    bool farFromIndex = !closeToIndex;

    while( currentIndex != index )
       {
        if( ( lowToHigh && closeToIndex ) || ( highToLow && farFromIndex ) )
           {
            currentPtr = currentPtr->next;

            currentIndex++;  

            if( currentIndex == vectorCapacity )
               {
                currentIndex = 0;
               }              
           }
        else
           {
            currentPtr = currentPtr->previous;
    
            if( currentIndex == 0 )
               {
                currentIndex = vectorCapacity;
               }              

            currentIndex--;
           }
       }

    return currentPtr;
   }

/**
 * @brief Shows structure of list as array
 *
 * @details None
 *          
 * @pre Assumes initialized SimpleVector where 0 <= index < vectorCapacity
 *
 * @post Provides display as specified
 *
 * @par Algorithm 
 *      Iterates across linked list, showing data items as elements
 *
 * @exception None
 *
 * @param [in] IDChar
 *             character ID letter to indicate object displayed
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
void SimpleVector<DataType>::showSVStructure
       ( 
        char IDChar     // in: object identifier for display
       )
   {
    DataType dataItem;
    int indexVal = 0;
    char dataStr[ LARGE_STR_LEN ];

    cout << " Vector ID " << IDChar;

    if( listHead == NULL || vectorSize == 0 )
       {
         cout << " : Empty List." << endl;
       }

    else
       {
        cout << endl;

        dataItem = getAtIndex( indexVal );
        dataItem.toString( dataStr );

        cout << " data item, index: " << indexVal << ": " 
             << dataStr << endl;

        indexVal++;

        while( indexVal < getSize() )
           {
            dataItem = getAtIndex( indexVal );
            dataItem.toString( dataStr );

            cout << " data item, index: " << indexVal << ": " 
                 << dataStr << endl;

            indexVal++;
           }

        cout << endl;
       }
   }


// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef SIMPLEVECTOR_CPP







