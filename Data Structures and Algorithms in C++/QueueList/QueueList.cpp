// Class Implementation Information ///////////////////////////////////////////
/**
  * @file QueueList.cpp
  *
  * @brief Implementation file for QueueList class
  * 
  * @details Implements member methods of QueueList class 
  *
  * @version 1.00 
  *          Bryan Kline (25 January 2016)
  *
  * @note Requires QueueList.h
  */

// Precompiler directives /////////////////////////////////////////////////////

   // none

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>           // for queue display
#include <cstdio>             // for string management
#include <cstring>            // for string management
#include "QueueList.h"        // header file

using namespace std;

// Global constant definitions  ///////////////////////////////////////////////

static const int ONE = 1;
static const int ZERO = 0;

// Class/Data Structure member implementations ////////////////////////////////

/**
  * @brief Implementation of QueueList default constructor
  *
  * @details Default constructor for QueueList class
  *
  * @pre Uninitialized QueueList 
  *
  * @post QueueList object initialized with default values
  *
  * @par Algorithm 
  *      Data members are assigned default values     
  *
  * @exception None
  *
  * @param[in] maxCapacity
  *            Data member capacityLimit initialized to maxCapacity which
  *            sets the maximum possible size of the QueueList (int)
  *
  * @return None
  *
  * @note ListNode pointers are set to NULL, capacityLimit set to 
  *       the parameter maxCapacity, and remaining data members
  *       set to zero
  *       
  */
QueueList:: QueueList( int maxCapacity )
{
    head = NULL;
    tail = NULL;			
    capacityLimit = maxCapacity;  
    listCapacity = ZERO;	
    queueSize = ZERO;
}

/**
  * @brief Implementation of QueueList copy constructor
  *
  * @details Copy constructor for QueueList class
  *
  * @pre Uninitialized QueueList
  *
  * @post QueueList with same nodes and values as the QueueList
  *       passed in as a parameter
  *
  * @par Algorithm     
  *      Data members of type ListNode pointer are initialized to NULL
  *      and the overloaded assignment operator is called on this 
  *  
  * @exception None
  *
  * @param[in] other
  *            A const QueueList object passed in by reference to be 
  *            copied by the calling object (QueueList)
  *
  * @return None
  *
  * @note Data members of type ListNode pointer are initialized to NULL
  *       so that the QueueList will be empty when checked by other
  *       methods
  *       
  */
QueueList:: QueueList( const QueueList& other )
{
    head = NULL;
    tail = NULL;    

    *this = other;    
}

/**
  * @brief Implementation of QueueList destructor
  *
  * @details Destructor for QueueList class
  *
  * @pre QueueList object with or without nodes and data
  *
  * @post All memory allocated to the QueueList object freed
  *       and data members set back to default values
  *
  * @par Algorithm     
  *      The member method clear called to delete all nodes
  *      in the QueueList object
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
QueueList:: ~QueueList()
{
    clear();  
}

/**
  * @brief Implementation of method to add items to the QueueList
  *
  * @details The int parameter passed into the method is added
  *          to the queue after tail if there is space on the list
  *
  * @pre A QueueList object which has been initialized
  *
  * @post If there is in room in the QueueList then the int parameter
  *       passed into the method is added to the queue, another node
  *       having been created for the item if necessary and tail is moved
  *    
  *
  * @par Algorithm     
  *      An if statement checks that the queue is not full and whether
  *      capacityLimit is greater than zero, if not false is returned, if so
  *      if else statements check 1) whether or not there are any nodes and
  *      if not one is created for the item and assigned to head and tail, 
  *      2) whether queueSize and listCapacity are equal in which case a new
  *      node is created for the item and linked with tail, and 3) if queueSize
  *      is less than listCapacity in which case if queueSize is zero then the
  *      item is assigned to the node at head and if not then tail is moved to
  *      the next node and the item is added to that node
  *
  * @exception None
  *
  * @param[in] newDataItem
  *            An int which, if there is space in the queue, is added to
  *            to the dataItem portion of the node following tail (int)
  *
  * @return A bool is returned corresponding to whether or not the item
  *         was successfully added to the queue (bool)
  *
  * @note Data members correponding the size of the queue and the list are
  *       incremented
  *       
  */
bool QueueList:: enqueue( int newDataItem )
{
    // condition: queue is not full and the capacity is greater than zero
    if( ( !queueIsFull() ) && ( capacityLimit > ZERO )  )
    {
        // condition: adding the first data item
        if( listIsEmpty() )   
        {
            head = new ListNode( newDataItem, NULL );  
            head->next = tail = head;	
            listCapacity++;	 
        }
        // condition: there are no unused nodes
        else if( queueSize == listCapacity )        
        {
	        tail->next = new ListNode( newDataItem, head ); 
            tail = tail->next;   
            listCapacity++;
        }
        // condition: there are unused nodes to add to
        else if( queueSize < listCapacity )  
        {
            // condition: all nodes are unused
            if( queueSize == ZERO ) 
            {
                head->dataItem = newDataItem;
                tail = head;
            }
            else
            {
                tail = tail->next;
                tail->dataItem = newDataItem;    
            }
        }
        queueSize++;

        return true;
    }

    return false;
}

/**
  * @brief Implementation of method to remove items from the QueueList
  *
  * @details If there are items to remove from the queue then the
  *          item at head is removed and the parameter passed into the
  *          method is assigned the value of the item being removed
  *
  * @pre A QueueList object which has been initialized
  *
  * @post If the QueueList contained at least one item then it is removed
  *       from the head of the queue and head is moved
  *
  * @par Algorithm 
  *      An if statement checks whether or not the queue is empty and if
  *      so then false is returned, otherwise the parameter passed in is
  *      assigned the value of the data member dataItem at the head node
  *      and head is moved to the next node and queueSize is decremented
  *
  * @exception None
  *
  * @param[out] newDataItem
  *             An int passed in by reference which will accept the value of
  *             the item removed from the head of the queue (int)
  *
  * @return A bool is returned corresponding to whether or not the item
  *         was successfully removed from the queue (bool)
  *
  * @note None
  *       
  */
bool QueueList:: dequeue( int &newDataItem )
{
   // condition: queue is not empty
   if( !queueIsEmpty() )
   {
       newDataItem = head->dataItem; 
       head = head->next; 
       queueSize--;
 
       return true;
   }
            	
   return false;
}

/**
  * @brief Implementation of method to change the capacity of the QueueList
  *
  * @details The maximum number of allowed nodes, capacityLimit, is changed
  *          to the parameter passed in if it's greater than the size of 
  *          the queue
  *
  * @pre An initialized QueueList object
  *
  * @post The QueueList object has the number of possible nodes, limitCapacity,
  *       changed and unused nodes are deleted if necessary
  *
  * @par Algorithm     
  *      An int counter is set equal to listCapacity minus the parameter passed
  *      in, newCapacity, which will be the number of nodes to be deleted if 
  *      necessary, then if statements check that 1) newCapacity is greater
  *      than capacityLimit in which case capacityLimit is assigned the value 
  *      of newCapacity and true is returned, 2) newCapacity is less than 
  *      listCapacity and greater than or equal to queueSize in which case
  *      if newCapacity is zero then clear is called, otherwise tail and/or
  *      head are moved depending on whether or not newCapacity is equal to one
  *      and a counter controlled loop moves a node pointer through the list 
  *      after tail and deletes nodes and true is returned, otherwise if neither 
  *      of those main branches are entered then false is returned
  *
  *
  * @exception None
  *
  * @param[in] newCapacity
  *            An int that specifies what the capacityLimit, or the maximum
  *            total number of allowed nodes, will be changed to (int)
  *
  * @return A bool is returned corresponding to whether or not the resize
  *         was successful (bool)
  *
  * @note None
  *       
  */
bool QueueList:: resetCapacity( int newCapacity )
{
    int index, counter = ( listCapacity - newCapacity ); 
    ListNode* tempNode;

    // condition: newCapacity is greater than the current maximum capacity
    //            of the list 
    if( newCapacity > capacityLimit )
    {
        capacityLimit = newCapacity;
        return true;
    }
    // condition: newCapacity is less than the number of nodes and greater 
    //            than or equal to the size of the queue 
    else if ( ( newCapacity < listCapacity ) && ( newCapacity >= queueSize ) )
    {
        // condition: newCapacity is zero
        if( newCapacity == ZERO)
        {
            clear();
        }
        else
        {
            // condition: the list has no unsed nodes and newCapacity is one
            if( ( queueIsEmpty() ) && ( newCapacity == ONE ) )
            {
                head = tail = head->next;
            }
            // condition: the list has no unsed nodes and newCapacity is not
            //            one
            else if( ( queueIsEmpty() ) && ( newCapacity != ONE ) )
            {
                tail = head->next;
            }

            tempNode = tail->next;
            for( index = ZERO; index < counter; index++ )
            {
                tail->next = tempNode->next;
                delete tempNode;
                tempNode = tail->next;  
            }

            capacityLimit = listCapacity = newCapacity;
            tempNode = NULL;
        }

        return true;
    }

    return false;
}

/**
  * @brief Implementation of method to clear all nodes in QueueList
  *
  * @details If the QueueList has nodes then they are deleted and
  *          data members are set to default values
  *
  * @pre An initialized QueueList object
  *
  * @post The QueueList has all memory allocated to nodes freed and
  *       data members are set to default values
  *
  * @par Algorithm    
  *      An if statement checks that there are nodes in the queue, then
  *      an event controlled loop goes through the queue with a temporary
  *      ListNode pointer and tail, moving from node to node and deleting
  *      all nodes and then data members are assigned default values
  *
  * @exception If there are no nodes in the QueueList then the method
  *            exits
  *
  * @param None 
  *
  * @return None
  *
  * @note The data member capacityLimit is not set to default its default
  *       value as this value should persist for subsequent usage of the
  *       data structure
  *       
  */
void QueueList:: clear()
{
    ListNode* tempNode;

    // condition: the list is not empty
    if( !listIsEmpty() )
    {
        tempNode = tail = head->next;
        while( tempNode != head )  
        {    
            tempNode = tempNode->next; 
            delete tail;
            tail = tempNode;
        }
        delete head;
         
        head = NULL;
        tail = NULL;
        tempNode = NULL;

        capacityLimit = ZERO;
        listCapacity = ZERO;		
        queueSize = ZERO;
    }
}

/**
  * @brief Implementation of method to copy the structure and data members
  *        of one QueueList to another
  *
  * @details The structure and data members of the QueueList object passed
  *          in by reference is copied to the calling QueueList object
  *
  * @pre A QueueList object
  *
  * @post A QueueList object containing all nodes and data members copied
  *       from the QueueList object passed in as a parameter 
  *
  * @par Algorithm     
  *      The method clear is called to delete all nodes and reset default
  *      values, then the values of the data members from the QueueList
  *      object passed in as a parameter are assigned to those of the
  *      calling object, and an event controlled loop moves a temporary node
  *      pointer through the queue to be copied while another creates nodes
  *      for the calling object and the data items are copied into them 
  *      
  *
  * @exception If the calling QueueList object and the QueueList object
  *            passed in as a parameter are the same object then the method
  *            exits
  *
  * @param[in] other
  *            A QueueList object passed in by reference which will have
  *            its structure and data members copied to the calling obejct
  *            (QueueList) 
  *
  * @return The calling QueueList object is returned by this dereferenced
  *         (QueueList)
  *
  * @note None
  *       
  */
QueueList& QueueList:: isAssigned( const QueueList& other )
{
    ListNode* thisTemp;
    ListNode* otherTemp = other.head;

    // condition: the two QueueList objects are not the same object
    if( this != &other)
    {
        clear();

        // condition: the QueueList object passed in as a parameter is
        //            is not empty
        if( !other.listIsEmpty() )
        {
            capacityLimit = other.capacityLimit;       
            listCapacity = other.listCapacity;
            queueSize = other.queueSize;

            thisTemp = new ListNode( otherTemp->dataItem, NULL );
            thisTemp->next = head = tail = thisTemp;
            
            while( otherTemp->next != other.head )
            {
                otherTemp = otherTemp->next;
                thisTemp->next = new ListNode( otherTemp->dataItem, head );
                thisTemp = thisTemp->next;
                // condition: the temporary node pointer moving through
                //            the list other is at the tail
                if( otherTemp == other.tail )
                {
                    tail = thisTemp;
                }
                //thisTemp = thisTemp->next;
            }
            otherTemp = NULL;
            thisTemp = NULL;
        }
    }

    return *this;
}

/**
  * @brief Implementation of overloaded assignment operator
  *
  * @details The method isAssigned is called to copy the QueueList
  *          passed in as a parameter into the calling QueueList object
  *
  * @pre A QueueList object
  *
  * @post A QueueList object containing all nodes and data members copied
  *       from the QueueList object passed in as a parameter
  *
  * @par Algorithm   
  *      The method isAssigned is called on the parameter passed in
  *      and its result is returned   
  *
  * @exception None
  *
  * @param[in] other
  *            A QueueList object passed in by reference which will have
  *            its structure and data members copied to the calling obejct
  *            (QueueList)
  *
  * @return The result of the call to the method isAssigned is returned
  *         (QueueList)
  *
  * @note None
  *       
  */
QueueList& QueueList:: operator = ( const QueueList& other )
{
    return isAssigned( other );
}

/**
  * @brief Implementation of method to view the data item at the
  *        head of the QueueList object
  *
  * @details The data item at the head of the queue is assigned the
  *          parameter passed in by reference and a bool corresponding
  *          to whether or not it was successful is returned
  *
  * @pre A initialized QueueList
  *
  * @post True is returned if the queue is not empty and the parameter
  *       passed in will contain the value of the data member in the
  *       node at head, false is returned if there are no used nodes
  *
  * @par Algorithm  
  *      An if statement checks if the queue is empty and if it's not then 
  *      the value of the data member dataItem at the head node is assigned
  *      to the parameter passed into the method   
  *
  * @exception None
  *
  * @param[out] dataVal
  *             An int passed in by reference which will accept the 
  *             value of the data member of the node at head (int)
  *
  * @return A bool corresponding to whether or not the method was
  *         successful (bool)
  *
  * @note None
  *       
  */
bool QueueList:: peekHead( int &dataVal ) const
{
    // condition: the queue is not empty
    if( !queueIsEmpty() )
    {
        dataVal = head->dataItem; 
        return true;
    }

    return false;
}

/**
  * @brief Implementation of method to print out the structure of a 
  *        QueueList object to the screen
  *
  * @details QueueList data members are printed to the screen along with
  *          the data items of the nodes in the list in rows of five
  *
  * @pre A QueueList object
  *
  * @post The QueueList nodes printed to the screen
  *
  * @par Algorithm     
  *      The cstdlib function sprintf creates a string, buffer, containing
  *      identifying information, then an if statement checks if the list
  *      is empty, if so an indication of that is printed to the screen,
  *      if not then a counter controlled loop goes through the list with
  *      a node pointer and prints each node's data item to the screen
  *      preceded by a char which indicates if it's the head, tail, in
  *      in the queue otherwise or unused, and surrounded by brackets
  *
  * @exception None
  *
  * @param[in] listID
  *            A char which represents an identifier of the QueueList
  *            to be printed to the screen
  *
  * @return None
  *
  * @note None
  *       
  */
void QueueList:: showStructure( char listID ) const
{
    int index, shiftRight;
    string label;
    char* buffer = new char[SMALL_STR_LEN];
    ListNode* tempNode = head;
    
    shiftRight = sprintf( buffer, " List %c (%d/%d/%d): ", 
        listID, queueSize, listCapacity, capacityLimit );
  
    // condition: there are no nodes in the QueueList
    if( listIsEmpty() )
    {
        cout << " Empty list";
    }
    else
    {
        cout << buffer;  
        
        for(index = ZERO; index < listCapacity; index++)
        {    
            // condition: index is not zero and a multiple of five
            if( ( index != ZERO ) && ( index % DISPLAY_WIDTH == ZERO ) )        
            {
                cout << endl;
                displayChars(shiftRight);
            }
            // condition: tempNode is either at head or tail and there are
            //            used nodes
            if( ( ( tempNode == head ) || ( tempNode == tail ) ) 
                && ( queueSize > ZERO ) )
            {
               // condition: there is only one used node in the list
               if( head == tail )
               {
                   label = "H/T: [";
               }
               //condition: tempNode is at head
               else if( tempNode == head )
               {
                   label = "H: [";      
               }  
               // condition: tempNode is at tail
               else if( tempNode == tail )
               {
                   label = "T: [";      
               }
            }
            else
            {
                // condition: if the current node to be printed is in the queue
                if(index < queueSize)
                {   
                    label = "Q: [";
                }
                else
                {
                    label = "U: ["; 
                }
            }
            cout << label << tempNode->dataItem << "] ";

            tempNode = tempNode->next;
        }
        tempNode = NULL;
    }
    cout << endl;

    delete buffer;
    buffer = NULL;
}

/**
  * @brief Implementation of method to check if the queue portion
  *        of a QueueList object is empty
  *
  * @details The QueueList object is checked for any used nodes
  *          and returns a corresponding bool value
  *
  * @pre An initialized QueueList object
  *
  * @post True is returned if there are no used nodes in the
  *       QueueList, otherwise false is returned
  *
  * @par Algorithm    
  *      With a call to the member method listIsEmpty, an if statement checks 
  *      if the list is empty or if the data member queueSize is zero
  *
  * @exception None
  *
  * @param None
  *
  * @return A bool is returned corresponding to whether or not there
  *         are any used nodes in the QueueList (bool)
  *
  * @note None
  *       
  */
bool QueueList:: queueIsEmpty() const
{
    // condition: there are no nodes, used or unused
    if( ( listIsEmpty() ) || ( queueSize == ZERO ) )
    {
        return true; 
    }

    return false;
}

/**
  * @brief Implementation of method to check whether the queue portion
  *        of a QueueList object is full
  *
  * @details The current size of the queue, the used nodes, is checked
  *          against the total capacity of the QueueList and a corresponding
  *          bool is returned
  *
  * @pre An initialized QueueList object
  *
  * @post True is returned if the queue is full, otherwise false
  *       is returned
  *
  * @par Algorithm   
  *      An if statement checks if the data member queueSize is
  *      equal to capacityLimit   
  *
  * @exception None
  *
  * @param None
  *
  * @return A bool is returned corresponding to whether or not the
  *         queue portion of the QueueList is full (bool)
  *
  * @note None
  *       
  */
bool QueueList:: queueIsFull() const
{
    // condition: number of used nodes is equal to the capacity of the list
    if( queueSize == capacityLimit )
    {
        return true; 
    }

    return false;
}
           
/**
  * @brief Implementation of method to check for any nodes 
  *        in the QueueList
  *
  * @details The QueueList object is checked for any nodes, used
  *          or unused, and returns a corresponding bool value
  *
  * @pre An initialized QueueList object
  *
  * @post True is returned if the QueueList is empty, otherwise
  *       false is returned
  *
  * @par Algorithm  
  *      An if statement checks whether the data members of type ListNode
  *      pointer are NULL    
  *
  * @exception None
  *
  * @param None
  *
  * @return A bool is returned corresponding to whether or not the
  *         QueueList is empty (bool)
  *
  * @note None
  *       
  */
bool QueueList:: listIsEmpty() const
{
    // condition: neither head nor tail are pointing at nodes
    if( ( head == NULL ) && ( tail == NULL ) )
    {
        return true; 
    }

    return false;
}

/**
  * @brief Implementation of char output method
  *
  * @details An int is taken in as a parameter which corresponds
  *          to the number of the char SPACE to be output to the
  *          screen 
  *
  * @pre A positive, non-zero int is entered as a parameter
  *
  * @post The method will output spaces to the screen in the amount
  *       of the int passed in as a parameter
  *
  * @par Algorithm 
  *      An if statement checks if numChars is greater than zero
  *      and a counter controlled loop with numChars as the controlling
  *      value outputs SPACE, a global constant corresponding to a
  *      space, to the screen    
  *
  * @exception If numChars is zero or a negative number then the method
  *            exits
  *
  * @param[in] numChars
  *            An int greater than zero which corresponds to the number
  *            of spaces output to the screen (int)
  *
  * @return None
  *
  * @note SPACE is a global constant char which is assigned the value of
  *       a single space
  *       
  */
void QueueList:: displayChars( int numChars ) const
{
    int index;

    // condition: the parameter passed in is greater than zero
    if( numChars > ZERO )
    {
        for(index = ZERO; index < numChars; index++)
        {
            cout << SPACE;       
        }
    }
}
