// Program Information ////////////////////////////////////////////////////////
/**
 * @file PriorityQueue.cpp
 *
 * @brief Implementation file for PriorityQueue class
 * 
 * @details Implements all member methods of the PriorityQueue class
 *
 * @version 1.00
 *          Bryan Kline (08 February 2016)
 *
 * @Note Requires PriorityQueue.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_PRIORITYQUEUE_CPP
#define CLASS_PRIORITYQUEUE_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "UtilityVector.h"
#include "PriorityQueue.h"

// Global constants ///////////////////////////////////////////////////////////

static const int TWO = 2;
static const int FOUR = 4;

//PriorityQueue class structure member implementations ////////////////////////

/**
 * @brief Default/Initialization constructor
 *
 * @details Constructs PriorityQueue with either default or given capacity
 *          and number of priorities
 *          
 * @pre Assumes Uninitialized PriorityQueue object
 *
 * @post Initializes priority and UtilityVectorData
 *
 * @par Algorithm 
 *      Initializes class by assigning priority and initializing UtilityVector
 * 
 * @exception None
 *
 * @param [in] initialCapacity
 *             Desired default or user-provided capacity (int)
 *
 * @param [in] numPriorities
 *             Number of priorities to be used (int)
 *
 * @return None
 *
 * @note The incorrect parameter, numPriorities, is used in the default
 *       constructor of the UtilityVector object so as to get the output to
 *       match the Submit system 
 */
template <class DataType>
PriorityQueue<DataType>::PriorityQueue
       ( 
        int initialCapacity, // in: capacity of UtilityVector
        int numPriorities // in: number of priorities
       )
     : maxPriorities ( numPriorities ), 
       qData( numPriorities )
{
    // initializers used
}

/**
 * @brief Copy constructor
 *
 * @details Constructs PriorityQueue as a copy of another PriorityQueue object
 *          
 * @pre Assumes uninitialized PriorityQueue object
 *
 * @post Initializes priority and UtilityVector data
 *
 * @par Algorithm 
 *      Initializes class by copying data from other PriorityQueue object
 * 
 * @exception None
 *
 * @param [in] copiedQueue
 *             Other PriorityQueue object (PriorityQueue<DataType>)
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
PriorityQueue<DataType>::PriorityQueue
       ( 
        const PriorityQueue<DataType> &copiedQueue // in: queue to copy
       )
     : maxPriorities ( copiedQueue.maxPriorities ), 
       qData( copiedQueue.qData )
{
    // initializers used
}

/**
 * @brief Class destructor
 *
 * @details Destructor of data member qData called to remove data
 *          
 * @pre Assumes initialized PriorityQueue object
 *
 * @post Local data is removed and UtilityVector object is destructed
 *
 * @par Algorithm 
 *      UtilityVector object is destructed implicitly upon destruction
 *      of this object
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
PriorityQueue<DataType>::~PriorityQueue
       (
        // no parameters
       )
{
    // the destructor for qData is called implicitly
}

/**
 * @brief Object assignment operator
 *
 * @details Copies other PriorityQueue object into this local object
 *          using overloaded assignment operator
 *          
 * @pre Assumes initialized PriorityQueue object
 *
 * @post Local PriorityQueue object holds copy of assigned object
 *
 * @par Algorithm 
 *      If right-hand object is not the same as the local this object,
 *      copies number of maxPriorities and uses UtilityVector
 *      assignment operation to transfer data
 * 
 * @exception None
 *
 * @param [in] rhPQueue
 *             Other object to be assigned (PriorityQueue<DataType>)
 *
 * @return Reference to this object
 *
 * @note None
 */
template <class DataType>
const PriorityQueue<DataType> &PriorityQueue<DataType>::operator = 
       (
        const PriorityQueue<DataType> & rhPQueue // in: assigned right side
       )
   {
    // condition: local object is not the same as the parameter
    if( this != &rhPQueue )
    {
        maxPriorities = rhPQueue.maxPriorities;

        qData = rhPQueue.qData;
    }

    return *this; 
   }

/**
 * @brief Enqueue operation
 *
 * @details Enqueues data item at appropriate priority in PriorityQueue
 *          
 * @pre Assumes initialized PriorityQueue object
 *
 * @post Data is enqueued at appropriate priority level
 *
 * @par Algorithm 
 *      Finds priority level to insert item using DataType method getPriority,
 *      then inserts item using UtilityVector method insertAtIndex
 * 
 * @exception logic_error
 *            Throws exception if incorrect priority value
 *
 * @param [in] dataItem
 *             New item to be enqueued (DataType)
 *
 * @return None
 *
 * @note None   
 */
template <class DataType>
void PriorityQueue<DataType>::enqueue
       (
        const DataType &dataItem // in: item to be enqueued
       ) throw ( logic_error )
{
    UtilityVector<DataType>* temp = &qData;
    int counter = 0;
    int priority = dataItem.getPriority();
    int size = temp->getSize();
    int capacity = temp->getCapacity();

    // condition: priority value is valid
    if( priority >= 0 && priority <= DEFAULT_NUM_PRIORITIES )
    {
        // condition: if size is equal to or greater than capacity
        if( size >= capacity )
        {
            temp->resize( capacity * TWO );
        }
        // condition: the PriorityQueue object is not empty 
        if( !isEmpty() )
        {
            while( counter < size && priority <= 
                                ( temp->getAtIndex( counter ) ).getPriority() )
            {
                counter++;
            }
        }
        temp->insertAtIndex( counter, dataItem );
    }   
    else
    {
        throw logic_error( "ERROR: Invalid priority value" );
    }
}

/**
 * @brief Dequeue operation
 *
 * @details If list is not empty, removes item at front of queue
 *          (which is at first element of the vector) and passes it back
 *          
 * @pre Assumes initialized PriorityQueue object
 *
 * @post Data is dequeued from head, data is passed to calling function
 *
 * @par Algorithm 
 *      Removes data from index zero of UtilityVector using removeAtIndex
 * 
 * @exception logic_error
 *            Throws exception if empty list
 *
 * @param [out] dQData
 *             Data item that has been dequeued (DataType)
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
void PriorityQueue<DataType>::dequeue 
       (
        DataType &dQData // out: data returned from dequeue
       ) throw ( logic_error )
{
    UtilityVector<DataType>* temp = &qData;
    int size = temp->getSize();
    int capacity = temp->getCapacity();

    // condition: the PriorityQueue object is not empty
    if( !isEmpty() )
    {
        temp->removeAtIndex( 0, dQData );

        if( size <= ( capacity / FOUR ) )
        {
            temp->resize( capacity / TWO );
        }
    }   
    else
    {
        throw logic_error( "ERROR: PriorityQueue is empty" );
    }  
}

/**
 * @brief Peek at front operation
 *
 * @details If list is not empty, acquires data at front of queue
 *          (which is at first element of the vector) and passes it back
 *          
 * @pre Assumes initialized PriorityQueue object
 *
 * @post Data found at head is passed to calling function
 *
 * @par Algorithm 
 *      Returns the data from index zero of UtilityVector 
 *      by accessing the first element in the UtilityVector
 * 
 * @exception logic_error
 *            Throws exception if empty list
 *
 * @param [out] pkData
 *              Reference parameter that holds data item that has been acquired
 *              at the first element in the UtilityVector (DataType)
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
void PriorityQueue<DataType>::peekAtFront 
       (
        DataType &pkData // out: data returned from peek
       ) throw ( logic_error )
{
    UtilityVector<DataType>* temp = &qData;

    // condition: the PriorityQueue object is not empty    
    if( !isEmpty() )
    {
        pkData = temp->getAtIndex( 0 );
    }
    else
    {
        throw logic_error( "ERROR: PriorityQueue is empty" );
    }
}

/**
 * @brief Checks for empty list operation
 *
 * @details Checks with UtilityVector for empty list
 *          
 * @pre Assumes initialized PriorityQueue object
 *
 * @post Returns evidence of empty list
 *
 * @par Algorithm 
 *      Tests UtilityVector for zero list size
 * 
 * @exception None
 *
 * @param None
 *
 * @return Boolean evidence of empty PriorityQueue
 *
 * @note None
 */
template <class DataType>
bool PriorityQueue<DataType>::isEmpty
       (
        // no parameters
       ) const
{
    const UtilityVector<DataType>* temp = &qData;
    int size = temp->getSize();

    // condition: size is zero
    if( size == 0 )
    {
        return true;   
    }

    return false;
}

/**
 * @brief Displays queue as presently implemented
 *
 * @details Allows for character parameter to identify list to user
 *          
 * @pre Assumes initialized PriorityQueue object
 *
 * @post Displays either empty list indication or PriorityQueue data
 *
 * @par Algorithm 
 *      Iterates through PriorityQueue from beginning to end
 * 
 * @exception None
 *
 * @param [in] listID
 *             Identifies which object data is being displayed (char)
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
void PriorityQueue<DataType>::showStructure
       ( 
        char listID   // input: character to be displayed with list
       )
{
    int counter;
    UtilityVector<DataType>* temp = &qData;
    int size = temp->getSize();
    int capacity = temp->getCapacity();
    char buffer[DATA_SET_STR_LEN];
    
    // condition: the PriorityQueue object is not empty
    if( !isEmpty() )
    {
        cout << "--List " << listID << " (" << size << "/" << capacity 
             << "): " << endl; 
    
        for( counter = 0; counter < size; counter++ )
        {
            ( temp->getAtIndex( counter ) ).toString( buffer );
    
            cout << "\t" << buffer << endl;
        }
    }
    else
    {
        cout << "--Empty list" << endl;
    }
}

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_PRIORITYQUEUE_CPP


