// Class Implementation Information ///////////////////////////////////////////
/**
  * @file SimpleVector.cpp
  *
  * @brief Implementation file for SimpleVector and DataNode classes
  * 
  * @details Implements member methods of SimpleVector and DataNode classes 
  *
  * @version 2.00 
  *          Bryan Kline (02 February 2016)
  *
  * @note Requires SimpleVector.h
  */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef SIMPLEVECTOR_CPP
#define SIMPLEVECTOR_CPP

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>           // for vector display
#include <cstdio>             // for string management
#include <cstring>            // for string management
#include "SimpleVector.h"     // header file

using namespace std;

// Global constant definitions  ///////////////////////////////////////////////

static const int ONE = 1;
static const int ZERO = 0;

//DataNode Class Structure member implementations /////////////////////////////

/**      
  * @brief Implementation of templated DataNode parameterized constructor
  *
  * @details The parameters passed into the constructor are assigned to the
  *          data members of the DataNode object 
  *
  * @pre An uninitialized DataNode object
  *
  * @post A DataNode object with data members initialized to the values passed
  *       passed in as parameters
  *
  * @par Algorithm 
  *      Initializers are used to set data members to the values passed in as
  *      parameters    
  *
  * @exception None
  *
  * @param[in] inData
  *            Parameter of type DataType passed by reference into the
  *            template which will be the data value that the node holds
  *            inPrevPtr (<DataType>)
  *            Parameter of type DataNode pointer which points to the previous
  *            node in the vector (DataNode<DataType>)
  *            inNextPtr
  *            Parameter of type DataNode pointer which points to the next node
  *            in the vector (DataNode<DataType>)
  *
  * @return None
  *
  * @note Initializers used
  *       
  */
template <typename DataType>
DataNode<DataType>:: DataNode
     ( 
      DataType &inData, // the value or object the node will hold
      DataNode<DataType> *inPrevPtr, // a pointer to the previous node
      DataNode<DataType> *inNextPtr // a pointer to the next node
     )
    : dataItem ( inData ), previous ( inPrevPtr ), next ( inNextPtr )
{
    // initializers used 
}

//SimpleVector Class Structure member implementations /////////////////////////

/**
  * @brief Implementation of templated SimpleVector default constructor
  *
  * @details Initializers set default values to the data members in the vector
  *          and the vector is resized to the capacity passed in as a parameter
  *
  * @pre An uninitialized SimpleVector object
  *
  * @post An initialized SimpleVector object with default values and nodes
  *       created in the amount of the parameter newCapacity
  *
  * @par Algorithm 
  *      Initializers are used to set data members to default values and the 
  *      method resize is called with newCapacity as an argument to create
  *      nodes for the vector
  *          
  * @exception None
  *
  * @param[in] newCapacity
  *            An int which initializes vector capacity, or the maximum number
  *            of nodes the vector can contain (int)
  *
  * @return None
  *   
  * @note Initializers used
  *       
  */
template <typename DataType>
SimpleVector<DataType>:: SimpleVector
     ( 
      int newCapacity // the capacity of the vector
     )
    : vectorCapacity ( ZERO ), vectorSize ( ZERO ), 
      currentIndex ( ZERO ), currentPtr ( NULL ), listHead ( NULL )
{
    resize( newCapacity );

    // initializers used
}

/**
  * @brief Implementation of templated SimpleVector parameterized constructor 
  *
  * @details A SimpleVector is created and filled with the value or object
  *          of type DataType passed in as a parameter 
  *
  * @pre An uninitialized SimpleVector object
  *
  * @post A SimpleVector object with newCapacity number of nodes, all of
  *       which filled with fillValue of type DataType
  *
  * @par Algorithm 
  *      Initializers are used to set data members to default values, the
  *      method resize is called with newCapacity as an argument to change
  *      the capacity of the vector, and then a counter controlled loop moves
  *      through the vector and the method setAtIndex is called with the
  *      parameter fillValue passed into it as the value to fill the vector
  *
  * @exception None
  *
  * @param[in] newCapacity
  *            An int which initializes vector capacity, or the maximum number
  *            of nodes the vector can contain (int)
  *            fillValue
  *            A reference parameter of type DataType which will be the value
  *            or object which is used to fill all the nodes in the vector
  *            (<DataType>)
  *
  * @return None
  *
  * @note Initializers used
  *       
  */
template <typename DataType>
SimpleVector<DataType>:: SimpleVector
     ( 
      int newCapacity, // the capacity of the vector
      const DataType &fillValue // the value or object that will fill all nodes 
     )
    : vectorCapacity ( ZERO ), vectorSize ( ZERO ), 
      currentIndex ( ZERO ), currentPtr ( NULL ), listHead ( NULL )
{
    int counter;

    resize ( newCapacity );
    
    for( counter = ZERO; counter < newCapacity; counter++ )
    {
        setAtIndex( counter, fillValue );
    }

    vectorSize = vectorCapacity;

    // initializers used
}

/**
  * @brief Implementation of templated SimpleVector copy constructor
  *
  * @details The SimpleVector object passed into the constructor as a parameter
  *          is copied into the SimpleVector object to be constructed 
  *
  * @pre An uninitialized SimpleVector object 
  *
  * @post A SimpleVector object with the same nodes and data member values
  *       as the object passed in as a parameter
  *
  * @par Algorithm 
  *      The method copyVectorObject is called with the parameter copiedVector 
  *      passed in as an argument    
  *
  * @exception None
  *
  * @param[in] copiedVector
  *            A const SimpleVector object reference parameter which has its
  *            nodes and data values copied into the constructing SimpleVector
  *            object (SimpleVector<DataType>)
  *
  * @return None
  *
  * @note None
  *       
  */
template <typename DataType>
SimpleVector<DataType>:: SimpleVector
     ( 
      const SimpleVector<DataType> &copiedVector // the vector to be copied
     )
    : vectorCapacity ( ZERO ), vectorSize ( ZERO ), 
      currentIndex ( ZERO ), currentPtr ( NULL ), listHead ( NULL )
{
    copyVectorObject( copiedVector );

    // initializers used
}

/**
  * @brief Implementation of templated SimpleVector destructor
  *
  * @details The nodes contained in the vector are deleted and data members
  *          are set to default values
  *
  * @pre An initialized SimpleVector object
  *
  * @post All memory allocated for nodes in the vector freed and data members
  *       set to defaul values
  *
  * @par Algorithm 
  *      The method resize is called with zero passed in to clear out the 
  *      vector and the method zeroSize is called to set vectorSize to zero    
  *
  * @exception None 
  *
  * @param None
  *
  * @return None
  *
  * @note None
  *       
  */
template <typename DataType>
SimpleVector<DataType>:: ~SimpleVector
     ( 
      // no parameters
     )
{
    resize( ZERO );
    zeroSize();
}

/**
  * @brief Implementation of templated SimpleVector overloaded assignment
  *        operator
  *
  * @details The SimpleVector object passed into the method as a parameter is
  *          copied into the calling SimpleVector object 
  *
  * @pre An SimpleVector object 
  *
  * @post The calling SimpleVector object has the same nodes and data member
  *       values as the SimpleVector object passed in as a parameter
  *
  * @par Algorithm 
  *      An if statement checks whether both objects are the same, if they're
  *      not then the calling object is resized with vectorCapacity of rhVector
  *      passed in as an argument, a counter controlled loop moves through
  *      rhVector with a temporary DataNode pointer and the calling object
  *      copies in the values or objects from rhVector with a call to 
  *      setAtIndex, data members are assigned the values from rhVector and
  *      and this dereferenced is returned    
  *
  * @exception None
  *
  * @param[in] rhVector
  *            A const SimpleVector object reference parameter which will be
  *            copied into the calling vector (SimpleVector<DataType>) 
  *
  * @return The calling SimpleVector object is returned with this dereferenced
  *         (SimpleVector<DataType>)
  *
  * @note None
  *       
  */
template <typename DataType>
const SimpleVector<DataType>& SimpleVector<DataType>:: operator =
     ( 
      const SimpleVector<DataType> &rhVector // the vector to be copied
     )
{
    int counter;
    DataNode<DataType>* temp = rhVector.listHead;

    // condition: the calling object is different than the parameter
    if( this != &rhVector )
    {
        resize( rhVector.vectorCapacity );

        for( counter = ZERO; counter < rhVector.vectorCapacity; counter++ )
        {
            // condition: the temporary pointer is at rhVector's currentPtr
            if( temp == rhVector.currentPtr )
            {
                currentPtr = getPointerToIndex( counter );
            }
        
            setAtIndex( counter, temp->dataItem );
            temp = temp->next;
        }
        
        vectorSize = rhVector.vectorSize;
        currentIndex = rhVector.currentIndex;
    }    

    temp = NULL;

    return *this;
}

/**
  * @brief Implementation of templated SimpleVector method which returns the
  *        capacity of the vector
  *
  * @details The data member vectorCapacity is returned
  *
  * @pre An initialized SimpleVector object
  *
  * @post The SimpleVector object is unchanged and vectorCapacity is
  *       returned
  *
  * @par Algorithm 
  *      A return statement returns the data member vectorCapacity    
  *
  * @exception None
  *
  * @param None
  *
  * @return An int is returned which corresponds to the capacity of the vector
  *         (int) 
  *
  * @note None
  *       
  */
template <typename DataType>
int SimpleVector<DataType>:: getCapacity
     (
      // no parameters   
     ) const
{
    return vectorCapacity;
}

/**
  * @brief Implementation of templated SimpleVector method which returns the
  *        size of the vector
  *
  * @details The data member vectorSize is returned
  *
  * @pre An initialized SimpleVector object
  *
  * @post The SimpleVector object is unchanged and the vector size is returned
  *
  * @par Algorithm 
  *      A return statement returns the data member vectorSize    
  *
  * @exception None
  *
  * @param None 
  *
  * @return An int is returned which corresponds to the size of the vector 
  *         (int) 
  *
  * @note None
  *       
  */
template <typename DataType>
int SimpleVector<DataType>:: getSize
     (
      // no parameters
     ) const
{
    return vectorSize;
}

/**
  * @brief Implementation of templated SimpleVector method which prints the
  *        vector list nodes to the screen
  *
  * @details If the vector contains any nodes then they, along with the list
  *          identifier IDChar, are printed to the screen in rows of five,
  *          otherwise it is indicated that the vector is empty
  *
  * @pre A SimpleVector object
  *
  * @post The SimpleVector object is unchanged and its contents printed to the
  *       screen
  *
  * @par Algorithm 
  *      An if statement checks whether the vector is empty, if it is then an
  *      indication of that is printed to the screen, otherwise a counter
  *      controlled loop moves a temporary DataNode pointer through the vector,
  *      printing each one to the screen as it goes, printing a new line and
  *      spaces out every five nodes for proper formatting    
  *
  * @exception None
  *
  * @param[in] IDChar
  *            A char which acts as an identifier for the vector being printed
  *            to the screen (char)  
  *
  * @return None
  *
  * @note None
  *       
  */
template <typename DataType>
void SimpleVector<DataType>:: showStructure
     ( 
      char IDChar // the identifying char of the vector
     ) const
{   
    int nodeCount;
    int spaceCount;
    int shiftRight;
    char* buffer = new char[DISPLAY_WIDTH + DEFAULT_CAPACITY];
    DataNode<DataType>* pointer = listHead;

    shiftRight = sprintf(buffer, " Vector ID %c", IDChar );

    cout << buffer << COLON;

    // condition: the vector contains no nodes
    if( ( vectorCapacity == ZERO ) || ( listHead == NULL ) )
    {
        cout << " Empty List." << endl;
    } 
    else
    {
        for( nodeCount = ZERO; nodeCount < vectorCapacity; nodeCount++ )
        {
            // condition: a multiple of five nodes have been printed out
            if( ( nodeCount % DISPLAY_WIDTH == ZERO ) && (nodeCount != ZERO ) )
            {
                cout << SPACE;
                cout << endl;
                for(spaceCount = ZERO; spaceCount < shiftRight; spaceCount++ )
                {
                    cout << SPACE;
                }
                cout << COLON;
            }

        cout << SPACE << nodeCount << LEFT_BRACKET << pointer->dataItem 
             << RIGHT_BRACKET; 
        pointer = pointer->next;

        } 

        cout << endl; 
        pointer = NULL;      
    }
}

/**
  * @brief Implementation of templated SimpleVector method which sets an item
  *        at a given index in the vector 
  *
  * @details The data portion of the DataNode at the location in the vector as
  *          specified by the parameter index is assigned a value or object
  *          corresponding to the parameter inData
  *
  * @pre An initialized SimpleVector object containing at least one node
  *
  * @post The value at the node at the index in the SimpleVector object
  *       specified by the parameter index is set to the parameter inData
  *
  * @par Algorithm 
  *      An if statement checks if index is valid, if not then an exception 
  *      is thrown, if so then the method getPointerToIndex is called with
  *      index as a parameter and that is assigned to currentPtr, then
  *      currentPtr has the data item of the node it points to set to
  *      inData, and currentIndex is updated        
  *
  * @exception If the parameter index is less than zero or greater than
  *            vectorCapacity, meaning past the end of the vector, then
  *            a logic_error is thrown returning the string "Error/: 
  *            invalid index"
  *
  * @param[in] index
  *            An int corresponding to the index at which an item should
  *            be added to the vector (int)
  *            inData
  *            A const reference parameter of type DataType which will be
  *            added to the vector at the specified index (<DataType>)
  *
  * @return None
  *
  * @note None
  *       
  */
template <typename DataType>
void SimpleVector<DataType>:: setAtIndex
     ( 
      int index, // index in the vector at which inData will be placed
      const DataType &inData // the value or object to be placed at index
     ) throw ( logic_error )
{
    // condition: index is out of the bounds of the vector
    if( ( index < ZERO ) || ( index >= vectorCapacity ) )
    {
        throw logic_error( "Error: invalid index" );
    }
    else
    {
        currentPtr = getPointerToIndex( index );
        currentPtr->dataItem = inData;
        currentIndex = index;
    }
}

/**
  * @brief Implementation of templated SimpleVector method which gets an item
  *        at a given index from the vector 
  *
  * @details The data portion of the node at the location in the vector as
  *          specified by the parameter index is returned from the method
  *
  * @pre An initialized SimpleVector object containing at least one node
  *
  * @post The value or object in the data portion of the node at the index in
  *       the SimpleVector object specified by the parameter index is returned
  *       and the vector is unchanged
  *
  * @par Algorithm 
  *      An if statement checks if index is valid, if not then an exception 
  *      is thrown, if so then the method getPointerToIndex is called with
  *      index as a parameter and that is assigned to currentPtr, then
  *      currentIndex is updated and the value or object in the node is
  *      returned    
  *
  * @exception If the parameter index is less than zero or greater than
  *            vectorCapacity, meaning past the end of the vector, then
  *            a logic_error is thrown returning the string "Error/: 
  *            invalid index"
  *
  * @param[in] index
  *            An int corresponding to the index from which an item should
  *            be returned from the vector (int)
  *
  * @return The value or object in the data portion of the DataNode is
  *         returned (DataType)
  *
  * @note None
  *       
  */
template <typename DataType>
const DataType& SimpleVector<DataType>:: getAtIndex
     ( 
      int index // place in the vector from which a value or object is returned
     ) throw ( logic_error )
{
    // condition: index is out of bounds of the vector
    if( ( index < ZERO ) || ( index >= vectorCapacity ) )
    {
        throw logic_error( "Error: invalid index" ); 
    }
    else
    {
        currentPtr = getPointerToIndex( index );
        currentIndex = index;
        return currentPtr->dataItem;
    }
}

/**
  * @brief Implementation of templated SimpleVector method which changes the
  *        capacity of the vector
  *
  * @details The nodes in the vector are either created or destroyed depending
  *          on the parameter newCapacity so that the total capacity of the
  *          vector is changed 
  *
  * @pre An initialized SimpleVector object
  *
  * @post A SimpleVector object with its capacity changed
  *
  * @par Algorithm 
  *      An if statement checks whether newCapacity is greater than zero and
  *      not equal to vectorCapacity, if so then if newCapacity is less than
  *      vectorCapacity then a temporary node pointer goes to the end of the
  *      vector and then deletes back through the vector, moving currentIndex
  *      if necessary, and if newCapacity is not less than vectorCapacity then
  *      if listHead is NULL then it is created, otherwise the appropriate
  *      number of nodes is created starting at the end of the vector, and
  *      finally vectorCapacity is updated   
  *
  * @exception None 
  *
  * @param[in] newCapacity
  *            An int which specifies the new capacity of the vector (int) 
  *
  * @return None
  *
  * @note None
  *       
  */
template <typename DataType>
void SimpleVector<DataType>:: resize
     ( 
      int newCapacity  // the capacity of the vector
     )
{
    int counter, condition, start;
    DataType garbage;
    DataNode<DataType>* temp;
    DataNode<DataType>* hold;
 
    // condition: newCapacity is greater than zero and not the same as
    //            vectorCapacity
    if( ( newCapacity >= ZERO ) && ( newCapacity != vectorCapacity ) )
    {
        if( newCapacity < vectorCapacity )
        {
            temp = hold = listHead->previous;
            condition = ( vectorCapacity - newCapacity );
            for( counter = ZERO; counter < condition; counter++ )
            {
                // condition: hold is at currentPtr
                if( hold == currentPtr )
                {
                    currentPtr = currentPtr->previous;
                    currentIndex--;
                }
                listHead->previous = temp;
                hold = hold->previous;
                delete temp;
                temp = hold; 
            } 
            // condition: the new capacity is zero, the vector is being cleared
            if( newCapacity == ZERO )
            {
                listHead = currentPtr = NULL;
                currentIndex = ZERO;
            }
            else
            {
                listHead->previous = temp;
            }
        }
        else
        {
            condition = ( newCapacity - vectorCapacity );
            // condition: the vector isn't empty
            if( ( vectorCapacity != ZERO ) )
            {
                start = ZERO;
                temp = listHead->previous;
            }
            // condition: the vector is empty 
            if( ( listHead == NULL ) && ( vectorCapacity == ZERO ) )
            {
                start = ONE;
                listHead = new DataNode<DataType>( garbage, NULL, NULL);
                listHead->previous = listHead->next = listHead;
                temp = currentPtr = listHead;
            }

            for( counter = start; counter < condition; counter++ )
            {
                temp->next = new DataNode<DataType>( garbage, temp, listHead );
                temp = temp->next;
            }
            listHead->previous = temp;
        }
        vectorCapacity = newCapacity;
    }

    temp = hold = NULL;
}

/**
  * @brief Implementation of templated SimpleVector method to increment the
  *        size of the vector 
  *
  * @details The vector data member vectorSize is increased by one
  *
  * @pre An initialized SimpleVector object
  *
  * @post The data member vectorSize is changed
  *
  * @par Algorithm 
  *      An if statement checks whether the data member vectorSize is less
  *      than vectorCapacity and if so it's incremented    
  *
  * @exception None 
  *
  * @param None
  *
  * @return None 
  *
  * @note Method intended for programmer convenience
  *       
  */
template <typename DataType>
void SimpleVector<DataType>:: incrementSize
     (
      // no parameters
     )
{
    // condition: vectorSize is less than the capacity of the vector
    if( vectorSize < vectorCapacity )
    {
        vectorSize++;
    }
}

/**
  * @brief Implementation of templated SimpleVector method to decrement vector
  *        size
  *
  * @details The vector data member vectorSize is decreased by one
  *
  * @pre An initialized SimpleVector object
  *
  * @post The data member vectorSize is changed
  *
  * @par Algorithm 
  *      An if statement checks whether the data member vectorSize is greater
  *      than zero and if so it's decremented    
  *
  * @exception None
  *
  * @param None 
  *
  * @return None
  *
  * @note Method intended for programmer convenience
  *       
  */
template <typename DataType>
void SimpleVector<DataType>:: decrementSize
     (
      // no parameters  
     )
{
    // condition: vectorSize is greater than zero
    if( vectorSize > ZERO )
    {
        vectorSize--;
    }
}

/**
  * @brief Implementation of templated SimpleVector method to set vector size
  *        to zero
  *
  * @details The vector data member vectorSize is set to zero
  *
  * @pre An initialized SimpleVector object
  *
  * @post The data member vectorSize is changed
  *
  * @par Algorithm 
  *      The data member vectorSize is set to zero    
  *
  * @exception None
  *
  * @param None
  *
  * @return None
  *
  * @note Method intended for programmer convenience
  *       
  */
template <typename DataType>
void SimpleVector<DataType>:: zeroSize
     (
      // no parameters
     )
{
    vectorSize = ZERO;
}

/**
  * @brief Implementation of private templated SimpleVector method which
  *        copies a SimpleVector object into the calling SimpleVector object
  *
  * @details The SimpleVector object passed into the method as a parameter is
  *          copied into the calling SimpleVector object 
  *
  * @pre An SimpleVector object 
  *
  * @post The calling SimpleVector object has the same nodes and data member
  *       values as the object passed in as a parameter
  *
  * @par Algorithm 
  *      The overloaded assignment operator is called on the parameter inData
  *      and this dereferenced    
  *
  * @exception None
  *
  * @param[in] inData
  *            A const SimpleVector object reference parameter which will be
  *            copied into the calling vector (SimpleVector<DataType>)
  *            
  *
  * @return None
  *
  * @note Method is private
  *       
  */
template <typename DataType>
void SimpleVector<DataType>:: copyVectorObject
     ( 
      const SimpleVector<DataType> &inData // the vector to be copied
     )
{
    *this = inData;
}

/**
  * @brief Implementation of private templated SimpleVector method to return a
  *        pointer to a node in the vector
  *
  * @details Private method which, if the parameter index is valid, moves
  *          through the vector and when it reaches that index it returns a
  *          pointer to the node at that index 
  *
  * @pre An initialized SimpleVector object
  *
  * @post A pointer to the node at the index specified by the parameter index
  *       if it exists, otherwise a pointer set to NULL, is returned and the
  *       vector is unchanged
  *
  * @par Algorithm 
  *      If statements check that the parameter index is valid, if it is then
  *      a pointer is moved to that index with a counter controlled loop,
  *      otherwise the pointer set to NULL, and the pointer is returned     
  *
  * @exception None
  *
  * @param[in] index
  *            An int which corresponds to the index in the vector to which a
  *            pointer should be returned if a node there exists (int)
  *
  * @return A pointer to the node at index in the vector
  *
  * @note Method is private, and it returns a pointer set to NULL if conditions
  *       are not met (DataNode<DataType>*)
  *       
  */
template <typename DataType>
DataNode<DataType>* SimpleVector<DataType>:: getPointerToIndex
     ( 
      int index // the index at which a node pointer is be returned 
     )
{
    int counter;
    DataNode<DataType>* pointer = NULL;

    // condition: index is within the bounds of the vector
    if( ( index >= ZERO ) && ( index < vectorCapacity ) 
                                                 && ( vectorCapacity > ZERO ) )
    {
        pointer = listHead;

        for( counter = ZERO; counter < index; counter++ )    
        {
            pointer = pointer->next;                        
        } 
    }

    return pointer;
}

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef SIMPLEVECTOR_CPP
