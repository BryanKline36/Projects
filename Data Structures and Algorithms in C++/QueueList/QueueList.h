// Program Information ////////////////////////////////////////////////////////
/**
 * @file QueueList.h
 *
 * @brief Header file for queue implementation using linked list
 * 
 * @details Definitions of all members 
 *          to be used in the QueueList class
 *
 * @version 1.00 
 *          Michael Leverington(13 January 2016)
 *
 * @note None
 *
 * @note Depends on ListNode header file
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_QUEUELIST_H
#define CLASS_QUEUELIST_H

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>         // for list display
#include <cstdio>           // for string management in list display
#include <cstring>          // for string management in list display
#include "ListNode.h"

using namespace std;

// Class definitions  /////////////////////////////////////////////////////////

class QueueList 
   {
    public:
       // constants
       static const int DISPLAY_WIDTH = 5;
       static const int SMALL_STR_LEN = 50;
       static const char SPACE = ' ';

       // constructors
       QueueList( int maxCapacity = 10 );
       QueueList( const QueueList& other );
       ~QueueList();

       // modifiers
       bool enqueue( int newDataItem );
       bool dequeue( int &newDataItem );

       bool resetCapacity( int newCapacity );

       void clear();
       
       QueueList& isAssigned( const QueueList& other );
       QueueList& operator = ( const QueueList& other );

       // accessors
       bool peekHead( int &dataVal ) const;

       void showStructure( char listID ) const;

       bool queueIsEmpty() const;
       bool queueIsFull() const;
       bool listIsEmpty() const;

    private:

       void displayChars( int numChars ) const;
       ListNode* head;
       ListNode* tail;

       int capacityLimit;
       int listCapacity;
       int queueSize;
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif // ifndef CLASS_QUEUELIST


