// Program Information ////////////////////////////////////////////////////////
/**
 * @file SimpleQueue.cpp
 *
 * @brief Implementation file for SimpleQueue class
 * 
 * @author Bryan Kline
 * 
 * @details Implements all member methods of the SimpleQueue class
 *
 * @version 1.00
 *          Bryan Kline (27 April 2016)
 *          Original Code
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_SIMPLEQUEUE_CPP
#define CLASS_SIMPLEQUEUE_CPP

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include "SimpleQueue.h"
#include "SimpleList.cpp"

using namespace std;

// Class implementation  //////////////////////////////////////////////////////

/**
 *@brief Implementation of SimpleQueue default constructor
 *
 *@details The parent class constructs the queue
 *
 *@pre Assumes an uninitialized SimpleQueue object
 *
 *@post Data members are set to default values and memory is allocated for the
 *      queue
 *
 *@par Algorithm  
 *     Initializers are used to set data members to default values and the 
 *     parent class constructs the queue
 *
 *@exception None
 *
 *@param None
 *
 *@return None
 *
 *@note Initializers used
 */
template <class DataType>
SimpleQueue<DataType>:: SimpleQueue
       (
        // no parameters
       )
    : SimpleList<DataType>( INITIAL_CAPACITY ),
      queueSize ( 0 )
{
    // parent class constructs the queue
}

/**
 *@brief Implementation of SimpleQueue copy constructor
 *
 *@details The parent class copy constuctor constructs the queue
 *
 *@pre Assumes an uninitialized SimpleQueue object
 *
 *@post The values of the data members and stack of the queue passed in as a
 *      parameter are copied into the local object 
 *
 *@par Algorithm  
 *     Initializers are used to copy data members from the parameter and the
 *     parent class' copy constructor constructs the queue
 *
 *@exception None
 *
 *@param[in] copiedQueue
 *           A reference parameter of type SimpleQueue which corresponds to the
 *           queue to be copied (SimpleQueue<DataType>)  
 *
 *@return None
 *
 *@note Initializers used
 */
template <class DataType>
SimpleQueue<DataType>:: SimpleQueue
       ( 
        const SimpleQueue<DataType> &copiedQueue // in: the queue to be copied
       ) 
    : SimpleList<DataType>( copiedQueue ),
      queueSize ( copiedQueue.queueSize )
{
    // parent class constructs the stack  
}

/**
 *@brief Implementation of SimpleQueue destructor
 *
 *@details The parent class' destructor destructs the queue
 *
 *@pre Assumes an initialized SimpleQueue object
 *
 *@post Memory allocated to the queue is freed and data memebers are set to
 *      default values
 *
 *@par Algorithm  
 *     Memory allocated to the queue is freed and data memebers are set to
 *     default values by the parent class' destructor
 *
 *@exception None
 *
 *@param None
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
SimpleQueue<DataType>:: ~SimpleQueue
       (
        // no parameters
       )
{
    // parent class destructs the queue     
}

/**
 *@brief Implementation of SimpleQueue overloaded assignment operator
 *
 *@details The overloaded assignment operator from the parent class assigns
 *         one queue to another
 *
 *@pre Assumes an initialized SimpleQueue object and that the parent class has
 *     an overloaded assignment operator
 *
 *@post The local queue has the same values as the parameter passed in
 *
 *@par Algorithm  
 *     An if statement checks that the local object and the parameter are not
 *     the same and if not then the parent class' overloaded assignment 
 *     operator is called on the local object and the parameter to copy in the
 *     values and queue into the local object
 *
 *@exception None
 *
 *@param rhStack
 *       A reference parameter of type SimpleQueue which corresponds to the
 *       queue to be copied (SimpleQueue<DataType>)
 *
 *@return A SimpleQueue which is the local object (SimpleQueue<DataType>)
 *
 *@note None
 */
template <class DataType>
const SimpleQueue<DataType>& SimpleQueue<DataType>:: operator = 
       ( 
        const SimpleQueue<DataType> &rhQueue // in: the queue to be copied
       )
{
    // condition: the local object and the parameter are different
    if( this != &rhQueue)
    {
        *this = rhQueue;
    }
    
    return *this;
}

/**
 *@brief Implementation of SimpleQueue method to determine whether it's empty
 *
 *@details A bool is returned which corresponds to whether or not the queue
 *         is empty
 *
 *@pre Assumes an initialized SimpleQueue object
 *
 *@post A bool is returned and the queue is unchanged
 *
 *@par Algorithm  
 *     An if statement checks whether or not the size of the queue is greater
 *     than zero, if so false is returned, otherwise true is returned
 *
 *@exception None
 *
 *@param None
 *
 *@return A bool is returned corresponding to whether or not the queue is empty
 *        (bool)
 *
 *@note None
 */
template <class DataType>
bool SimpleQueue<DataType>:: isEmpty
       (
        // no parameters
       ) const
{
    // condition: there are no items in the queue
    if( queueSize > 0 )
    {
        return false;
    }

    return true;
}

/**
 *@brief Implementation of SimpleQueue method to enqueue items to the queue
 *
 *@details The item passed in is added to the queue, the capacity of the
 *         queue is double if it's full
 *
 *@pre Assumes an initialized SimpleQueue object and that the item the queue
 *     holds has overloaded assignment and offset operators
 *
 *@post A new item is added to the queue if there is room, otherwise the
 *      capacity of the queue is doubled and then it's added
 *
 *@par Algorithm  
 *     An if statement checks whether or not the queue is full, if so then 
 *     the the parent method resize is called to double the capacity, then
 *     the item is added to the back of the queue
 *
 *@exception None
 *
 *@param[in] enqueueData
 *           A reference parameter of type DataType which corresponds to the
 *           item to be added to the queue (DataType)
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void SimpleQueue<DataType>:: enqueue
       ( 
        const DataType &enqueueData // in: the item to be enqueued
       )
{
    int queueCapacity = this->getCapacity();

    // condition: the queue is full
    if( queueSize == queueCapacity )
    {
        this->resize( 2 * queueCapacity );
    }

    ( *this )[queueSize] = enqueueData;
    queueSize++;
}

/**
 *@brief Implementation of SimpleQueue method to dequeue an item from the queue
 *
 *@details Dequeues items from the front of the queue 
 *
 *@pre Assumes an initialized SimpleQueue object and that the parent 
 *     class has overloaded assignment and offset operators
 *
 *@post The item at the front of the queue is removed and the parameter accepts
 *      the item
 *
 *@par Algorithm  
 *     An if statement checks whether or not the queue is empty, if so then
 *     false is returned, otherwise the parameter is assigned the item at the
 *     the front of the queue, a counter controlled loop shifts everything
 *     towards the front and true is returned
 *
 *@exception None
 *
 *@param[out] dequeueData
 *            A reference parameter of type DataType which will accept the item
 *            dequeued (DataType)
 *
 *@return A bool is returned corresponding to whether or not the item was
 *        sucessfully dequeued (bool)
 *
 *@note None
 */
template <class DataType>
bool SimpleQueue<DataType>:: dequeue
       (    
        DataType &dequeueData // out: parameter to accept the item dequeued
       )
{
    int index;

    // condition: queue is not empty
    if( !isEmpty() )
    {
        dequeueData = ( *this )[0];

        for( index = 0; index < queueSize; index++ )
        {
            ( *this )[index] = ( *this )[index + 1];
        }

        queueSize--;
    
        return true;
    }

    return false;
}

/**
 *@brief Implementation of SimpleQueue method to view the front of the queue
 *
 *@details Reports the item at the front of the queue
 *
 *@pre Assumes an initialized SimpleQueue object and that the item the queue
 *     holds has overloaded assignment and offset operators
 *
 *@post The parameter takes the item at the front of the queue and the queue is
 *      unchanged
 *
 *@par Algorithm  
 *     An if statement checks whether or not the queue is empty, if not then
 *     the parameter is assigned the item at the front of the queue and true
 *     is returned
 *
 *@exception None
 *
 *@param[out] peekFront
 *            A reference parameter of type DataType which will accept the
 *            item at the front of the queue (DataType) 
 *
 *@return A bool is returned corresponding to whether or not the action was
 *        successful (bool)
 *
 *@note None
 */
template <class DataType>
bool SimpleQueue<DataType>:: peekFront
       ( 
        DataType &peekData // out: the item at the front of the queue 
       )
{
    // condition: the queue is not empty
    if( !isEmpty() )
    {
        peekData = ( *this )[0];

        return true;
    }

    return false;
}

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_SIMPLEQUEUE_CPP
