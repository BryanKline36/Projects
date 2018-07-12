// Program Information ////////////////////////////////////////////////////////
/**
 * @file SimpleStack.cpp
 *
 * @brief Implementation file for SimpleStack class
 * 
 * @author Bryan Kline
 * 
 * @details Implements all member methods of the SimpleStack class
 *
 * @version 1.00
 *          Bryan Kline (27 April 2016)
 *          Original Code
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_SIMPLESTACK_CPP
#define CLASS_SIMPLESTACK_CPP

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include "SimpleStack.h"
#include "SimpleList.cpp"

using namespace std;

// Class implementation  //////////////////////////////////////////////////////

/**
 *@brief Implementation of SimpleStack default constructor
 *
 *@details The parent class constructs the stack
 *
 *@pre Assumes an uninitialized SimpleStack object
 *
 *@post Data members are set to default values and memory is allocated for the
 *      stack
 *
 *@par Algorithm  
 *     Initializers are used to set data members to default values and the 
 *     parent class constructs the stack
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
SimpleStack<DataType>:: SimpleStack
       (
        // no parameters
       )
    : SimpleList<DataType>( INITIAL_CAPACITY ),
      stackSize ( 0 )
{
    // parent class constructs the stack
}

/**
 *@brief Implementation of SimpleStack copy constructor
 *
 *@details The parent class copy constuctor constructs the stack
 *
 *@pre Assumes an uninitialized SimpleStack object
 *
 *@post The values of the data members and stack of the stack passed in as a
 *      parameter are copied into the local object 
 *
 *@par Algorithm  
 *     Initializers are used to copy data members from the parameter and the
 *     parent class' copy constructor constructs the stack
 *
 *@exception None
 *
 *@param[in] copiedStack
 *           A reference parameter of type SimpleStack which corresponds to the
 *           stack to be copied (SimpleStack<DataType>)  
 *
 *@return None
 *
 *@note Initializers used
 */
template <class DataType>
SimpleStack<DataType>:: SimpleStack
       ( 
        const SimpleStack &copiedStack // in: the stack to be copied 
       )
    : SimpleList<DataType>( copiedStack ),
      stackSize ( copiedStack.stackSize )
{
    // parent class constructs the stack
}

/**
 *@brief Implementation of SimpleStack destructor
 *
 *@details The parent class' destructor destructs the stack
 *
 *@pre Assumes an initialized SimpleStack object
 *
 *@post Memory allocated to the stack is freed and data memebers are set to
 *      default values
 *
 *@par Algorithm  
 *     Memory allocated to the stack is freed and data memebers are set to
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
SimpleStack<DataType>:: ~SimpleStack
       (
        // no parameters
       )
{
    // parent class destructs the stack
}

/**
 *@brief Implementation of SimpleStack overloaded assignment operator
 *
 *@details The overloaded assignment operator from the parent class assigns
 *         one stack to another
 *
 *@pre Assumes an initialized SimpleStack object and that the parent class has
 *     an overloaded assignment operator
 *
 *@post The local stack has the same values as the parameter passed in
 *
 *@par Algorithm  
 *     An if statement checks that the local object and the parameter are not
 *     the same and if not then the parent class' overloaded assignment 
 *     operator is called on the local object and the parameter to copy in the
 *     values and stack into the local object
 *
 *@exception None
 *
 *@param rhStack
 *       A reference parameter of type SimpleStack which corresponds to the
 *       stack to be copied (SimpleStack<DataType>)
 *
 *@return A SimpleStack which is the local object (SimpleStack<DataType>)
 *
 *@note None
 */
template <class DataType>
const SimpleStack<DataType>& SimpleStack<DataType>:: operator =   
       ( 
        const SimpleStack &rhStack // in: the stack to be copied
       )
{
    // condition: the local object and the parameter are different
    if( this != &rhStack )
    {
        *this = rhStack;
    }
    
    return *this;
}

/**
 *@brief Implementation of SimpleStack method to determine whether it's empty
 *
 *@details A bool is returned which corresponds to whether or not the stack
 *         is empty
 *
 *@pre Assumes an initialized SimpleStack object
 *
 *@post A bool is returned and the stack is unchanged
 *
 *@par Algorithm  
 *     An if statement checks whether or not the size of the stack is greater
 *     than zero, if so false is returned, otherwise true is returned
 *
 *@exception None
 *
 *@param None
 *
 *@return A bool is returned corresponding to whether or not the stack is empty
 *        (bool)
 *
 *@note None
 */
template <class DataType>
bool SimpleStack<DataType>:: isEmpty
       (
        // no parameters
       ) const
{
    // condition: there are no items in the stack
    if( stackSize > 0 )
    {
        return false;
    }

    return true;
}

/**
 *@brief Implementation of SimpleStack method to push items onto the stack
 *
 *@details The item passed in is added to the stack, the capacity of the
 *         stack is double if it's full
 *
 *@pre Assumes an initialized SimpleStack object and that the item the stack
 *     holds has overloaded assignment and offset operators
 *
 *@post A new item is added to the stack if there is room, otherwise the
 *      capacity of the stack is doubled and then it's added
 *
 *@par Algorithm  
 *     An if statement checks whether or not the stack is full, if so then 
 *     the the parent method resize is called to double the capacity, then
 *     a counter controlled loop shifts everything in the stack down one
 *     index and then adds the item to the top of the stack
 *
 *@exception None
 *
 *@param[in] newData
 *           A reference parameter of type DataType which corresponds to the
 *           item to be added to the stack (DataType)
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void SimpleStack<DataType>:: push
       ( 
        const DataType &newData // in: the item to be pushed onto the stack
       )
{
    int index;
    int stackCapacity = this->getCapacity();
    
    // condition: the stack is full
    if( stackSize == stackCapacity )
    {
        this->resize( 2 * stackCapacity );
    }

    if( stackSize > 0 )
    {
        for( index = ( stackSize - 1 ); index >= 0; index-- )
        {
            ( *this )[index + 1] = ( *this )[index];
        }
    }

    ( *this )[0] = newData; 
    stackSize++;
}

/**
 *@brief Implementation of SimpleStack method to pop items off the stack
 *
 *@details Pops items off of the top of the stack 
 *
 *@pre Assumes an initialized SimpleStack object and that the parent 
 *     class has overloaded assignment and offset operators
 *
 *@post The item on the top of the stack is popped off and the parameter 
 *      accepts the item
 *
 *@par Algorithm  
 *     An if statement checks whether or not the queue is empty, if so then
 *     false is returned, otherwise the parameter is assigned the item on the
 *     the top of the stack, a counter controlled loop shifts everything
 *     towards the top and true is returned
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
bool SimpleStack<DataType>:: pop
       ( 
        DataType &poppedData
       )
{
    int index;

    if( !isEmpty() )
    {
        poppedData = ( *this )[0];

        for( index = 0; index < stackSize; index++ )
        {
            ( *this )[index] = ( *this )[index + 1];
        }

        stackSize--;
    
        return true;
    }

    return false;
}

/**
 *@brief Implementation of SimpleStack method to view the top of the stack
 *
 *@details Reports the item at the top of the stack
 *
 *@pre Assumes an initialized SimpleStack object and that the item the stack
 *     holds has overloaded assignment and offset operators
 *
 *@post The parameter takes the item at the top of the stack and the stack is
 *      unchanged
 *
 *@par Algorithm  
 *     An if statement checks whether or not the stack is empty, if not then
 *     the parameter is assigned the item at the top of the stack and true
 *     is returned
 *
 *@exception None
 *
 *@param[out] peekTop
 *            A reference parameter of type DataType which will accept the
 *            item at the top of the stack (DataType) 
 *
 *@return A bool is returned corresponding to whether or not the action was
 *        successful (bool)
 *
 *@note None
 */
template <class DataType>
bool SimpleStack<DataType>:: peekTop
       ( 
        DataType &peekData // out: the item at the top of the stack
       )
{
    // condition: the stack is not empty
    if( !isEmpty() )
    {
        peekData = ( *this )[0];
        
        return true;
    }

    return false;
}

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_simpleStack_CPP

