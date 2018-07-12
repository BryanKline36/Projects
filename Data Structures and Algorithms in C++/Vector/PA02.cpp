// Program Information ////////////////////////////////////////////////////////
/**
  * @file PA02.cpp
  *
  * @brief Driver program to exercise linked-list based Vector classes
  * 
  * @details Allows for testing all SimpleVector methods 
  *          in an interactive operation
  *
  * @version 1.00 
  *          Original development (23 January 2016)
  *
  * @note Requires SimpleVector.h, SimpleVector.cpp
  */

// Precompiler directives /////////////////////////////////////////////////////

   // none

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include "SimpleVector.cpp"

using namespace std;

// Global constant definitions  ///////////////////////////////////////////////

const int SMALL_STR_LEN = 25;

const bool VERBOSE = true;

const char ENDLINE_CHAR = '\n';
const char DASH = '-';

// Free function prototypes  //////////////////////////////////////////////////

void ShowMenu();

// Main function implementation  //////////////////////////////////////////////

int  main()
   {
    SimpleVector<char> testListA( 5, DASH ), testListB, testListC;    // Test lists
    char commandChar;                             
    bool testListB_Assigned = false, testListC_Constructed = false;
    int indexVal, newCapacity, currentCapacity, currentSize, oldCapacity = 5;
    char dataVal;

    ShowMenu();

    do
       {
        cout << "Command: ";                  // Read command
        
        cin >> commandChar;

        if( !VERBOSE )
           {
            cout << commandChar << ": ";
           }

        switch ( commandChar )
           {
            case 'a':  // object assignment

               testListB = testListA;

               if( VERBOSE )
                  {
                   cout << 
                     " Test list \'B\' has been assigned to test list \'A\'." 
                        << endl;
                  }

               testListB_Assigned = true;

               break;

            case 'c':  // construct c test list

               // tempTestList constructed in code block to control scope
               // Note: Declaration of object outside of declaration area
               //       (i.e., not declared at the beginning of the function)
               //       is not accepted practice but is conducted here
               //       to demonstrate specified action
                  { 
                   SimpleVector<char> tempTestList( testListA );

                   testListC = tempTestList;

                   testListC_Constructed = true;
                  }

               if( VERBOSE )
                  {
                   cout << 
                " Test list \'C\' has been constructed with test list \'A\'." 
                        << endl;
                  }

               break;

            case 'g':  // get value

               cin >> indexVal;

               cout << indexVal << endl;

               dataVal = testListA.getAtIndex( indexVal );

               if( VERBOSE )
                  {
                    cout << " Value: " << dataVal 
                         << " acquired." << endl;
                  }

               break;

            case 'r':  // resize vector

               cin >> newCapacity;

               cout << newCapacity << endl;

               testListA.resize( newCapacity );

               if( oldCapacity > newCapacity )
                  {
                   oldCapacity = newCapacity;
                  }

               while( oldCapacity < newCapacity )
                  {
                   testListA.setAtIndex( oldCapacity, DASH );

                   oldCapacity++;
                  }

               if( VERBOSE )
                  {
                   cout << " Vector capacity reset to: " 
                        << newCapacity << endl;
                  }

               break;

            case 's':  // set value

               cin >> indexVal;

               cin >> dataVal;

               cout << indexVal << " - " << dataVal << endl;

               testListA.setAtIndex( indexVal, dataVal );

               if( VERBOSE )
                  {
                    cout << " Value: " << dataVal 
                         << " set." << endl;
                  }


               break;

            case 'S':  // show list of commands

               ShowMenu();

               break;

            case 't':  // check two tests for empty or full

               currentCapacity = testListA.getCapacity();

               currentSize = testListA.getSize();

               cout << " Current capacity: " << currentCapacity << endl;

               cout << " Current Size: " << currentSize <<endl;

               break;

            default :            // Invalid or non-control command

               // clear to end of line in case further data input
               cin.ignore( SMALL_STR_LEN, ENDLINE_CHAR );

               if( commandChar == 'E' )
                  {
                   cout << " End program requested." << endl;
                  }

               else if( VERBOSE )
                  {
                   cout << " Inactive or invalid command." << endl;
                  }

               break;
           }

        testListA.showStructure( 'A' );

        if( testListB_Assigned )
           {
            testListB.showStructure( 'B' );
           }

        if( testListC_Constructed )
           {
            testListC.showStructure( 'C' );
           }

        cout << endl;
       }
    while ( commandChar != 'E' );

    return 0;
   }

// Free function implementation  //////////////////////////////////////////////

/**
  * @brief Displays choice of commands for exercising linked list
  *
  * @details Command letters displayed are unique characters
  *          specified as shown
  *
  * @pre None
  *
  * @post Choice of commands is displayed as specified
  *
  * @par Algorithm
  *      Standard output operations for each command line available
  *
  * @exception None
  *
  * @param None
  *
  * @return None
  *
  * @note Five spaces for parameter parentheses,
  *       three spaces for curly braces
  */
void ShowMenu
     (
      // no parameters
     )
   {
    cout << endl << "Commands:" << endl << endl;

    cout << "  a     : Assign \'A\' test list to \'B\' test list" << endl;

    cout << "  c     : Construct \'C\' test list with test list \'A\'" << endl;

    cout << "  E     : End the test program" << endl;
 
    cout << "  g x   : Get value from vector at index x" << endl;

    cout << "  s x y : Set value in vector at index x to value y" << endl;

    cout << "  r x   : Reset vector capacity to x" << endl;

    cout << "  S     : Show this list of commands" << endl;

    cout << "  t     : Conduct Vector size & capacity tests" << endl << endl;
   }






