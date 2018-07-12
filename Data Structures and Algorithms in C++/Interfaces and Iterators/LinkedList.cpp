// Program Information ////////////////////////////////////////////////////////
/**
 * @file LinkedList.cpp
 *
 * @brief Implementation for LinkedList class
 *
 * @author Bryan Kline
 *
 * @details Implements all member methods for the LinkedList class 
 *
 * @version 1.00
 *          Bryan Kline (15 February 2016)
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "LinkedList.h"

// DataNode implementation ////////////////////////////////////////////////////

/**
 * @brief Implementation of parameterized constructor for DataNode class
 *
 * @details Initializers used to set data members 
 *
 * @pre Assumes an uninitialized DataNode object
 *
 * @post Initialized DataNode object
 *
 * @par Algorithm 
 *      Initializers are used to assign data members the values passed in as
 *      parameters
 *
 * @exception None
 *
 * @param[in] dataItem
 *            Reference parameter of type DataType which will be the item the
 *            node holds (DataType)    
 *
 * @param[in] previous
 *            DataNode pointer that points to the previous node in the list  
 *            (DataNode<DataType>*)
 *
 * @param[in] next
 *            DataNode pointer that points to the next node in the list  
 *            (DataNode<DataType>*)    
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
DataNode<DataType>:: DataNode
       ( 
        const DataType &inData, // in: the item the node will hold          
        DataNode<DataType> *inPrevPtr, // in: pointer to the previous node
        DataNode<DataType> *inNextPtr // in: pointer to the next node
       )
    : dataItem ( inData ),
      previous ( inPrevPtr ),
      next ( inNextPtr )
{
    // initializers used
}

// LinkedList class member implementations ////////////////////////////////////

/**
 * @brief Implementation of LinkedList default constructor
 *
 * @details Initializers used to set data members to NULL
 *
 * @pre Assumes an uninitialized LinkedList object
 *
 * @post Initialized LinkedList object with data members set to default values
 *
 * @par Algorithm 
 *      Initializers used to set data members of type DataNode pointer to NULL
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
LinkedList<DataType>:: LinkedList
       (
        // no parameters   
       )
    : listHead ( NULL ),
      currentPtr( NULL )    
{
    // initializers used    
}

/**
 * @brief Implementation of LinkedList copy constructor
 *
 * @details The private method copyList is called to copy the list passed
 *          in as a parameter into the calling list
 *
 * @pre Assumes an uninitialized LinkedList object
 *
 * @post LinkedList object with the same nodes and data members as the list
 *       passed in as a parameter 
 *
 * @par Algorithm 
 *      Initializers are used to set default values to data members and then
 *      the private method copyList is called on the list passed in as a 
 *      parameter
 *
 * @exception None
 *
 * @param[in] copiedList
 *            A const LinkedList reference parameter which will be copied into
 *            the calling list (LinkedList<DataType>)
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
LinkedList<DataType>:: LinkedList
       ( 
        const LinkedList<DataType> &copiedList // in: the LinkedList object to
                                               //     be copied
       )
    : listHead ( NULL ),
      currentPtr( NULL )     
{
    *this = copiedList;
}

/**
 * @brief Implementation of LinkedList destructor
 *
 * @details The member method clearList is called to delete all nodes in the
 *          list
 *
 * @pre Assumes an initialized LinkedList object
 *
 * @post All nodes contained in the LinkedList object deleted and data members
 *       set to default values
 *
 * @par Algorithm 
 *      The member method clearList is called to remove all nodes from the list
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
LinkedList<DataType>:: ~LinkedList
       (
        // no parameters
       )
{
    clearList();
}

/**
 * @brief Implementation of LinkedList overloaded assignment operator 
 *
 * @details The private method copyList is called to copy the list passed
 *          in as a parameter into the calling list
 *
 * @pre Assumes a LinkedList object
 *
 * @post LinkedList object with the same nodes and data members as the list
 *       passed in as a parameter
 *
 * @par Algorithm 
 *      A call to the private method copyList by the calling object copies
 *      the nodes and data members from the list passed in as a parameter
 *      into the local object
 *
 * @exception None
 *
 * @param[in] rhList
 *            A const LinkedList reference parameter which will be copied into
 *            the calling list (LinkedList<DataType>)
 *
 * @return The local LinkedList object (LinkedList<DataType>)
 *
 * @note None
 */
template <class DataType>
const LinkedList<DataType>& LinkedList<DataType>:: operator = 
       ( 
        const LinkedList<DataType> &rhList // in: the LinkedList object to be 
                                           //     copied
       )
{
    copyList( rhList );

    return *this;
}

/**
 * @brief Implementation of LinkedList method to clear the list of all nodes
 * 
 * @details Memory for all nodes is freed and data members are set to default
 *          values
 *
 * @pre Assumes an initialized LinkedList object
 *
 * @post All nodes are deleted and data members are set to default values
 *
 * @par Algorithm 
 *      An if statement checks whether of not listHead is NULL and if not then
 *      the nodes are cleared recursively by checking whether there is more
 *      one node, the recursive case in which the method clearListHelper is
 *      on currentPtr and clearList is called again, or there is only one node,
 *      the base case in which listHead is deleted and data members are set to
 *      default values
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
void LinkedList<DataType>:: clearList
       (
        // no parameters
       )
{
    // condition: there are nodes 
    if( listHead != NULL )
    {
        toEnd();
        clearListHelper( currentPtr );
        listHead = currentPtr = NULL;
    }
}

/**
 * @brief Implementation of LinkedList method to insert an item of type
 *        DataType into the list
 *
 * @details The item passed in as a parameter is added to the list at the 
 *          node pointed to by currentPtr
 *
 * @pre Assumes an initialized LinkedList object
 *
 * @post The LinkedList object has the item of type DataType passed in as a
 *       parameter inserted into the list at currentPtr
 *
 * @par Algorithm 
 *      An if statement checks whether there are nodes in the list and if there
 *      aren't then the first one is made at listHead, otherwise a new one is
 *      made and then linked up with currentPtr and the node before it
 *
 * @exception None
 *
 * @param[in] inData
 *            A const reference parameter of type DataType that is to be
 *            inserted into the list (DataType)
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
void LinkedList<DataType>:: insertAtCurrent
       ( 
        const DataType &inData // in: the item to be inserted into the list
       )
{
    DataNode<DataType>* temp;    

    // condition: there are no nodes yet
    if( listHead == NULL )
    {
        listHead = new DataNode<DataType>( inData, NULL, NULL );
        listHead->previous = listHead->next = currentPtr = listHead;
    }   
    else 
    {
        temp = new DataNode<DataType>( inData, currentPtr->previous, currentPtr );

        // condition: if currentPtr is at listHead
        if( currentPtr == listHead )
        {
            listHead = temp;
        }
        ( currentPtr->previous )->next = temp;
        currentPtr->previous = temp;
        currentPtr = temp;    
    }
    
    temp = NULL;
}

/**
 * @brief Implementation of LinkedList method to remove an item of type
 *        DataType from the list
 *
 * @details The item at the node pointed to by currentPtr is removed and stored
 *          in parameter of type DataTye passed into the method
 *
 * @pre Assumes an initialized LinkedList object
 *
 * @post The LinkedList object has the item of type DataType at currentPtr 
 *       removed and stored in the parameter passed into the method
 *
 * @par Algorithm 
 *      An if statement checks whether there are nodes in the list and if there
 *      are then a function call to the getAtCurrent gets the item and assigns
 *      it to the reference parameter passed in and then if that was the only
 *      node the clearList is called, otherwise the node at currentPtr is
 *      deleted and adjacent nodes are linked together
 *
 * @exception None
 *
 * @param[out] removedItem
 *             A reference parameter of type DataType that accepts the item
 *             at the node pointed to by currentPtr (DataType)
 *
 * @return A bool corresponding to whether or not the removal was successful
 *         (bool)
 *
 * @note None
 */
template <class DataType>
bool LinkedList<DataType>:: removeAtCurrent
       ( 
        DataType &removedItem // out: to receive the item removed
       )
{
    DataNode<DataType>* temp;    

    // condition: the list isn't empty
    if( listHead != NULL )
    {
        removedItem = getAtCurrent();        

        // condition: there is only one node in the list
        if( listHead->next == listHead )
        {
            clearList();
        }
        else
        {
            temp = currentPtr;
            ( currentPtr->previous )->next = currentPtr->next;
            ( currentPtr->next )->previous = currentPtr->previous;
    
            // condition: currentPtr is at listHead
            if( currentPtr == listHead )
            {
                listHead = listHead->next;    
            }
            currentPtr = currentPtr->next;
            delete temp;              
        }
        temp = NULL;

        return true;
    }
    temp = NULL; 
   
    return false;
}

/**
 * @brief Implementation of LinkedList method to move the DataNode pointer
 *        currentPtr to the next node 
 *
 * @details If the list is not empty and there is more than one node, the 
 *          DataNode pointer next is moved to the next node
 *
 * @pre Assumes an initialized LinkedList object
 *
 * @post The LinkedList data member currentPtr points to the next node in
 *       the list
 *
 * @par Algorithm 
 *      An if statement checks whether or not the list is empty and if there
 *      is more than one node in the list, if so then currentPtr is moved to
 *      next node
 *
 * @exception None
 *
 * @param None
 *
 * @return A bool corresponding to whether or not the DataNode pointer was
 *         successfully moved (bool)
 *
 * @note None
 */
template <class DataType>
bool LinkedList<DataType>:: nextNode
       (
        // no parameters
       )
{
    // condition: currentPtr isn't NULL and there is more than one node in the
    //            list
    if( currentPtr != NULL && listHead != listHead->next )
    {
        currentPtr = currentPtr->next;
        return true;
    }

    return false;
}

/**
 * @brief Implementation of LinkedList method to move the DataNode pointer
 *        currentPtr to the previous node 
 *
 * @details If the list is not empty and there is more than one node, the 
 *          DataNode pointer previous is moved to the previous node
 *
 * @pre Assumes an initialized LinkedList object
 *
 * @post The LinkedList data member currentPtr points to the previous node in
 *       the list
 *
 * @par Algorithm 
 *      An if statement checks whether or not the list is empty and if there
 *      is more than one node in the list, if so then currentPtr is moved to
 *      previous node
 *
 * @exception None
 *
 * @param None
 *
 * @return A bool corresponding to whether or not the DataNode pointer was
 *         successfully moved (bool)
 *
 * @note None
 */
template <class DataType>
bool LinkedList<DataType>:: prevNode
       (
        // no parameters
       )
{
    // condition: currentPtr isn't NULL and there is more than one node in the
    //            list
    if( currentPtr != NULL && listHead != listHead->previous )
    {
        currentPtr = currentPtr->previous;
        return true;
    }

    return false;
}

/**
 * @brief Implementation of LinkedList method to move the DataNode pointer
 *        currentPtr to the end of the list
 *
 * @details If the DataNode pointer currentPtr isn't already at the end of the
 *          list then it is moved to the last node
 *
 * @pre Assumes an initialized LinkedList object
 *
 * @post The LinkedList data member currentPtr points to the last node in
 *       the list
 *
 * @par Algorithm 
 *      An if statement checks whether or not currentPtr is already at the end
 *      of the list and if not then the method nextNode is called in an event 
 *      controlled loop until it reaches the end
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
void LinkedList<DataType>:: toEnd
       (
        // no parameters
       )
{
    // condition: currentPtr isn't at the end of the list and not NULL
    if( !atEnd() && currentPtr != NULL )
    {
        while( currentPtr->next != listHead)
        {
            nextNode();
        }
    }
}

/**
 * @brief Implementation of LinkedList method to move the DataNode pointer
 *        currentPtr to the beginning of the list
 *
 * @details If the DataNode pointer currentPtr isn't already at the beginning
 *          of the list then it is moved to the first node
 *
 * @pre Assumes an initialized LinkedList object
 *
 * @post The LinkedList data member currentPtr points to the first node in
 *       the list
 *
 * @par Algorithm 
 *      An if statement checks whether or not currentPtr is already at the
 *      beginning of the list and if not then the method prevNode is called in 
 *      and event controlled loop until it reaches the beginning
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
void LinkedList<DataType>:: toBeginning
       (
        // no parameters
       )
{
    // condition: currentPtr isn't at the beginning of the list and not NULL
    if( !atBeginning() && currentPtr != NULL )
    {
        while( currentPtr != listHead )
        {
            prevNode();
        }        
    }
}

/**
 * @brief Implementation of LinkedList method that determines whether or
 *        not the DataNode pointer currentPtr is at the end of the list
 *
 * @details If the DataNode pointer currentPtr is at the end of the list
 *          then a corresponding bool is returned
 *
 * @pre Assumes an initialized LinkedList object
 *
 * @post A bool corresponding to the position of currentPtr is returned and 
 *       the LinkedList object is unchanged
 *
 * @par Algorithm 
 *      An if statement checks whether or not the next node is listHead and
 *      if so then true is returned, otherwise false is returned
 *
 * @exception None
 *
 * @param None
 *
 * @return A bool corresponding to whether or not currentPtr is at the end of
 *         the list (bool)
 *
 * @note None
 */
template <class DataType>
bool LinkedList<DataType>:: atEnd
       (
        // no parameters
       ) const
{
    // condition: currentPtr isn't NULL and not already at the end of the list
    if( currentPtr != NULL && currentPtr->next == listHead )
    {
        return true;
    }

    return false;
}

/**
 * @brief Implementation of LinkedList method that determines whether or
 *        not the DataNode pointer currentPtr is at the beginning of the list
 *
 * @details If the DataNode pointer currentPtr is at the beginning of the list
 *          then a corresponding bool is returned
 *
 * @pre Assumes an initialized LinkedList object
 *
 * @post A bool corresponding to the position of currentPtr is returned and 
 *       the LinkedList object is unchanged
 *
 * @par Algorithm 
 *      An if statement checks whether or not the current node is listHead and
 *      if so then true is returned, otherwise false is returned
 *
 * @exception None
 *
 * @param None
 *
 * @return A bool corresponding to whether or not currentPtr is at the
 *         beginning of the list (bool)
 *
 * @note None
 */
template <class DataType>
bool LinkedList<DataType>:: atBeginning
       (
        // no parameters
       ) const
{
    // condition: currentPtr isn't NULL and not already at the beginning of the
    //            list
    if( currentPtr != NULL && currentPtr == listHead )
    {
        return true;
    }
    
    return false;
}

/**
 * @brief Implementation of LinkedList method to retrieve the item held in
 *        the node at the DataNode pointer currentPtr
 *
 * @details If there are nodes in the list then the item at currentPtr is
 *          returned
 *
 * @pre Assumes an initialized LinkedList object and that currentPtr isn't NULL
 *
 * @post The item at currentPtr is returned and the LinkedList object is
 *       unchanged
 *
 * @par Algorithm 
 *      An if statement checks whether or not currentPtr is NULL and if
 *      not then the item at currentPtr is returned
 *
 * @exception None
 *
 * @param None
 *
 * @return The item of type DataType at the currentPtr is returned (DataType)
 *
 * @note None
 */
template <class DataType>
const DataType& LinkedList<DataType>:: getAtCurrent
       (
        // no parameters
       ) const
{
    return currentPtr->dataItem;
}

/**
 * @brief Implementation of LinkedList method to print the list to the screen
 *
 * @details The items in the list are printed to the screen along with a char
 *          that identifies the list 
 *
 * @pre Assumes an initialized LinkedList object
 *
 * @post The structure of the LinkedList object is printed to the screen
 *       and the list is unchanged
 *
 * @par Algorithm
 *      An if statement checks whether there are nodes in the list, if not then
 *      an indication that the list is empty is printed to the screen, 
 *      otherwise the list identifier is printed out and an event controlled
 *      moves through the list and prints each item to the screen    
 *
 * @exception None
 *
 * @param[in] IDChar
 *            A char which acts as an identifier for the list to be printed to
 *            the screen (char)
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
void LinkedList<DataType>:: showLLStructure
       ( 
        char IDChar 
       ) const
{
    char* buffer = new char[LARGE_STR_LEN];
    DataNode<DataType>* temp = listHead;

    // condition: the list is empty
    if( listHead == NULL )
    {
        cout << " List ID " << IDChar << " : Empty List." <<  endl;
    }
    else
    {
        cout << " List ID " << IDChar << endl;

        ( temp->dataItem ).toString( buffer );
        cout << "-Data: " << buffer << endl;
        temp = temp->next;

        while( temp != listHead )
        {
            ( temp->dataItem ).toString( buffer );
            cout << "-Data: " << buffer << endl;
            temp = temp->next;
        }
        cout << endl;
    }
}

/**
 * @brief Implementation of LinkedList private method to copy on LinkedList
 *        object into another
 *
 * @details The calling LinkedList object has the nodes and data members of
 *          the list passed in as parameter
 *
 * @pre Assumes a LinkedList object
 *
 * @post LinkedList object with the same nodes and data members as the list
 *       passed in as a parameter
 *
 * @par Algorithm
 *      An if statement checks that the local object and the LinkedList object
 *      passed in as a parameter are not the same, if they're not then a call
 *      to the method clearList clears the calling object's nodes and if the 
 *      object passed in as a parameter is not empty then an event controlled
 *      loop goes through it and new nodes are created for the calling object 
 *       
 *
 * @exception None
 *
 * @param[in] copiedList
 *            A const LinkedList reference parameter which will be copied into
 *            the calling list (LinkedList<DataType>)  
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
void LinkedList<DataType>:: copyList
       ( 
        const LinkedList<DataType> &copiedList 
       )
{
    DataNode<DataType> *source, *destination;    

    // condition: the local object and the list passed in as a parameter aren't
    //            the same object
    if( this != &copiedList )
    {
        clearList();

        // condition: the list passed in as a parameter isn't empty
        if( copiedList.listHead != NULL )
        {
            source = copiedList.listHead;           
            listHead = new DataNode<DataType>( source->dataItem, NULL, NULL );
            listHead->previous = listHead->next = destination = 
                                                         currentPtr = listHead;
            
            while( source->next != copiedList.listHead )
            {
                source = source->next;
                destination->next = new DataNode<DataType>
                                   ( source->dataItem, destination, listHead );
                destination = destination->next; 

                // condition: source is at the position of the currentPtr of
                //            the list passed in as a parameter
                if( source == copiedList.currentPtr )
                {
                    currentPtr = destination;    
                } 
            }
            listHead->previous = destination;   
        }
    }
}

/**
 * @brief Implementation of LinkedList private method to delete a node in the
 *        list
 *  
 * @details Takes in a pointer to a node as a parameter, deletes it and links
 *          up adjacent nodes
 *
 * @pre Assumes an initialized LinkedList object
 *
 * @post The node to which the DataNode pointer passed in as a parameter points
 *       to is deleted and adjacent nodes are linked
 *
 * @par Algorithm 
 *      An if statement checks that the parameter is not NULL and that it's not
 *      listHead, if not then, after an if statement checks whether the
 *      parameter pointing at currentPtr and if so then prevNode is called,
 *      the nodes adjacent to the one the parameter points to are linked
 *      and the node is deleted
 *
 * @exception None
 *
 * @param[in] workingPtr
 *            DataNode pointer which corresponds to the node to be deleted
 *            (DataNode<DataType>)  
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
void LinkedList<DataType>:: clearListHelper( DataNode<DataType> *workingPtr )
{
    // condition: workingPtr is not at listHead
    if( workingPtr->next != listHead )
    {   
        clearListHelper( workingPtr->next );
    }
    delete workingPtr;

}

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef LINKEDLIST_CPP
