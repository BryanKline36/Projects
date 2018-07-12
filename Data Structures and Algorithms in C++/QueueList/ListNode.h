// Program Information ////////////////////////////////////////////////////////
/**
 * @file ListNode.h
 *
 * @brief Header file for list node
 * 
 * @details Basic list node header file incorporates struct 
 *          with integer data item and pointer to next node
 *
 * @version 1.00 
 *          Michael Leverington (30 August 2015)
 *          Original development of class
 *
 * @note Materials loosely base on Linked List exercise in Brandl, et. al.
 *       in C++ Data Structures: A Laboratory Course, (c) 2009.
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef STRUCT_LISTNODE_H
#define STRUCT_LISTNODE_H

// Header files ///////////////////////////////////////////////////////////////

   // none

// Class implementations //////////////////////////////////////////////////////

struct ListNode
   {
    ListNode( int nodeData, ListNode* nextPtr);

    int dataItem;

    ListNode* next;
   };

// Terminating precompiler directives /////////////////////////////////////////

#endif  // STRUCT_LISTNODE_H


