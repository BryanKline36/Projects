// Program Information ////////////////////////////////////////////////////////
/**
 * @file LinkedList.h
 *
 * @brief Definition file for LinkedList class
 * 
 * @details Specifies all member methods of the LinkedList class
 *
 * @version 1.00 
 *          Michael Leverington (06 February 2016)
 *          Original code
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>
#include <cstdlib>

using namespace std;

// Class constants /////////////////////////////////////////////////////////////

template <class DataType>
class DataNode
   {
    public:

       // DataType must have default constructor and assignment operator
       DataType dataItem;

       DataNode( const DataType &inData, 
                             DataNode<DataType> *inPrevPtr = NULL, 
                                       DataNode<DataType> *inNextPtr = NULL);

       DataNode<DataType> *previous;
       DataNode<DataType> *next;
   };

template <class DataType>
class LinkedList
   {
    public:

       // class constants
       static const int LARGE_STR_LEN = 100;

       // constructors
       LinkedList();
       LinkedList( const LinkedList<DataType> &copiedList ); 

       // destructor
       ~LinkedList( );

       // assignment
       const LinkedList<DataType> &operator = 
                                   ( const LinkedList<DataType> &rhList );

       // modifiers
       void clearList();
       void insertAtCurrent( const DataType &inData );
       bool removeAtCurrent( DataType &removedItem );
       bool nextNode();
       bool prevNode();
       void toEnd();
       void toBeginning();

       // accessors
       bool atEnd() const;
       bool atBeginning() const;
       const DataType &getAtCurrent() const;
       void showLLStructure( char IDChar ) const;

    private:

       DataNode<DataType> *listHead;
       DataNode<DataType> *currentPtr;

       void copyList( const LinkedList<DataType> &copiedList );
       void clearListHelper( DataNode<DataType> *workingPtr );
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef LINKEDLIST_H

