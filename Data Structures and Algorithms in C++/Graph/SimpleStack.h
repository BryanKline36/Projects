// Program Information ////////////////////////////////////////////////////////
/**
 * @file SimpleStack.h
 *
 * @brief Definition file for SimpleStack class
 * 
 * @author Michael Leverington
 * 
 * @details Specifies all member methods of the SimpleStack class
 *
 * @version 1.00
 *          Michael Leverington (13 April 2016)
 *          Original Code
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_SIMPLESTACK_H
#define CLASS_SIMPLESTACK_H

// Header files ///////////////////////////////////////////////////////////////

#include "SimpleList.cpp"

#include <iostream>
using namespace std;

// Class definition  //////////////////////////////////////////////////////////


template <class DataType>
class SimpleStack : private SimpleList<DataType>
   {
    public:

       static const int INITIAL_CAPACITY = 10;

       // constructors
       SimpleStack();
       SimpleStack( const SimpleStack &copiedStack ); 

       // destructor
       ~SimpleStack( );

       // assignment
       const SimpleStack &operator = ( const SimpleStack &rhStack );

       // accessors

          // reports stack empty
          bool isEmpty() const;

       // modifiers

          // pushes item onto stack
          void push( const DataType &newData );

          // removes item from stack
          bool pop( DataType &poppedData);
   
          // allows access to top without removing
          bool peekTop( DataType &peekData );

    public:

       int stackSize;
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_simpleStack_H

