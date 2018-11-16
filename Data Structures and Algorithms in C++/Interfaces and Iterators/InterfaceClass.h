// Program Information ////////////////////////////////////////////////////////
/**
 * @file InterfaceClass.h
 *
 * @brief Definition file for InterfaceClass class
 * 
 * @details Specifies all member methods of the InterfaceClass class
 *
 * @version 1.00 
 *          Michael Leverington (06 February 2016)
 *          Original code
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef INTERFACE_H
#define INTERFACE_H

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "LinkedList.h"

using namespace std;

// Class constants /////////////////////////////////////////////////////////////

template <class DataType>
class InterfaceClass : public LinkedList<DataType>
   {
    public:

       // constructors
       InterfaceClass();
       InterfaceClass( const InterfaceClass<DataType> &copiedList ); 

       // destructor
       virtual ~InterfaceClass( );

       // modifiers

          // move current node location forward in the list
          // but may not move if at end of list
          virtual bool operator ++ ();

          // move current node location backward in the list
          // but may not move if at beginning of list
          virtual bool operator -- ();

          // accessors

             // acquires data at current node
             virtual const DataType &operator * ();
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef INTERFACE_H

