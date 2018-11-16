// Program Information ////////////////////////////////////////////////////////
/**
 * @file ListNode.cpp
 *
 * @brief Implementation file for ListNode class (struct)
 * 
 * @details Implements constructor for ListNode class
 *
 * @version 1.00 
 *          Michael Leverington (30 August 2015)
 *          Original development of class
 *
 * @note Depends on ListNode.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef STRUCT_LISTNODE_CPP
#define STRUCT_LISTNODE_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "ListNode.h"

// Class/Data Structure member implementations ////////////////////////////////
/**
  * @brief ListNode constructor
  *
  * @details Creates and initializes one list node with data
  *          and a next pointer
  *
  * @pre ListNode uninitialized
  *
  * @post ListNode initialized with data and next pointer
  *
  * @par Algorithm
  *      Initializes node with data via method initializers
  *
  * @exception None
  *    No exceptional or error conditions handled in this method
  *
  * @param[in] nodeData provides the data to be stored in the node
  *
  * @param[in] nextPtr provides the pointer address to be stored
  *            in the node
  *
  * @note Five spaces used before parameter parenthesis,
  *       seven spaces used before the initializer colon,
  *       three spaces used before the opening/closing curly braces
  */
ListNode::ListNode
     ( 
      int nodeData,     // input: data value for node
      ListNode* nextPtr // input: pointer to next node
     )
       : dataItem ( nodeData ), next ( nextPtr )
   {
    // initializers used
   }

// Terminating precompiler directives /////////////////////////////////////////

#endif  // STRUCT_LISTNODE_CPP


