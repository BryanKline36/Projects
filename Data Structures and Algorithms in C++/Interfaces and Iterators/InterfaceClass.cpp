// Program Information ////////////////////////////////////////////////////////
/**
 * @file InterfaceClass.cpp
 *
 * @brief Implementation for InterfaceClass class
 *
 * @author Bryan Kline
 *
 * @details Implements all member methods for the InterfaceClass class 
 *
 * @version 1.00
 *          Bryan Kline (15 February 2016)
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef INTERFACECLASS_CPP
#define INTERFACECLASS_CPP

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "InterfaceClass.h"

// InterfaceClass class member implementations ////////////////////////////////////

/**
 * @brief Implementation of InterfaceClass default constructor
 *
 * @details The base class default sets data members to default values
 *
 * @pre Assumes an uninitialized InterfaceClass object
 *
 * @post The InterfaceClass object's data members are set to default values
 *
 * @par Algorithm 
 *      The base class default constructor is called implicitly
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
InterfaceClass<DataType>:: InterfaceClass
       (
        // no parameters
       )
{
    // base class default constructor is called implicitly
}

/**
 * @brief Implementation of InterfaceClass copy constructor
 *
 * @details The nodes of the InterfaceClass object passed in as a parameter
 *          are copied into the calling object
 *
 * @pre Assumes an uninitialized InterfaceClass object
 *
 * @post The calling object has the same nodes as the object passed in as a
 *       parameter
 *
 * @par Algorithm 
 *      The overloaded assignment operator is called on the local object
 *      and the InterfaceClass object passed in as a parameter
 *
 * @exception None
 *
 * @param copiedList
 *        A const reference InterfaceClass object that is to be copied into
 *        the calling object (InterfaceClass<DataType>)
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
InterfaceClass<DataType>:: InterfaceClass
       ( 
        const InterfaceClass<DataType> &copiedList // in: the InterfaceClass
                                                   //     object to be copied
       )
{
    *this = copiedList;
}

/**
 * @brief Implementation of InterfaceClass destructor
 *
 * @details All nodes in the list are deleted and data members are set to 
 *          default values
 *
 * @pre Assumes an initialized InterfaceClass object
 *
 * @post All memory allocated to the list freed and data members set to
 *       default values
 *
 * @par Algorithm 
 *      The method clearList is called to delete all nodes in the list and
 *      set data members to default values
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
InterfaceClass<DataType>:: ~InterfaceClass
       (
        // no parameters
       )
{
    this->clearList();
}

/**
 * @brief Implementation of InterfaceClass overloaded increment operator
 *
 * @details Iterates forward through the list toward the end
 *
 * @pre Assumes an initialized InterfaceClass object
 *
 * @post The current location in the list is incremented if it's not currently
 *       already at the end of the list
 *
 * @par Algorithm 
 *      An if statement checks whether the current location in the list is at
 *      the end or not, if so false is returned, otherwise the method nextNode
 *      is called in a return statement which moves to the next location in the
 *      list 
 *
 * @exception None
 *
 * @param None
 *
 * @return A bool is returned corresponding to whether or not the incrementor
 *         operator was successful in iterating through the list (bool)
 *
 * @note None
 */
template <class DataType>
bool InterfaceClass<DataType>:: operator ++ 
       (
        // no parameters
       )
{
    // condition: if the current location is not the end of the list
    if( !( this->atEnd() ) )
    {
        return this->nextNode();
    }

    return false;
}

/**
 * @brief Implementation of InterfaceClass overloaded decrement operator
 *
 * @details Iterates back through the list toward the beginning
 *
 * @pre Assumes an initialized InterfaceClass object
 *
 * @post The current location in the list is decremented if it's not currently
 *       already at the beginning of the list
 *
 * @par Algorithm 
 *      An if statement checks whether the current location in the list is at
 *      the beginning or not, if so false is returned, otherwise the method
 *      prevNode is called in a return statement which moves to the previous
 *      location in the list 
 *
 * @exception None
 *
 * @param None
 *
 * @return A bool is returned corresponding to whether or not the decrementor
 *         operator was successful in iterating through the list (bool)
 *
 * @note None
 */
template <class DataType>
bool InterfaceClass<DataType>:: operator -- 
       (
        // no parameters
       )
{
    // condition: if the current location is not the beginning of the list
    if( !( this->atBeginning() ) )
    {
        return this->prevNode();
    }

    return false;
}

/**
 * @brief Implementation of InterfaceClass overloaded dereference operator
 *
 * @details Returns the item of type DataType at a particular place
 *          in the list
 *
 * @pre Assumes an initialized InterfaceClass object
 *
 * @post The item of type DataType that is at a particular place in the
 *       the list is returned and the InterfaceClass is unchanged
 *
 * @par Algorithm 
 *      The local object is dereferenced and its method getAtCurrent is called
 *      in a return statement to retrieve the item of type DataType at that
 *      place in the list
 *
 * @exception None
 *
 * @param None
 *
 * @return A value or object of type DataType that is in the list at a given
 *         place in the list (DataType) 
 *
 * @note None
 */
template <class DataType>
const DataType& InterfaceClass<DataType>:: operator * 
       (
        // no parameters
       )
{
    return this->getAtCurrent();
}

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef INTERFACECLASS_CPP

