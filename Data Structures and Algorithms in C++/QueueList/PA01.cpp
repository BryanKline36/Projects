// Program Information ////////////////////////////////////////////////////////
/**
  * @file PA01.cpp
  *
  * @brief Driver program to exercise QueueList and ListNode classes
  * 
  * @details Allows for testing all QueueList methods 
  *          in an interactive operation
  *
  * @version 1.00 
  *          Original development (13 January 2016)
  *
  * @note Requires ListNode.h, ListNode.cpp, QueueList.h, QueueList.cpp
  */

// Precompiler directives /////////////////////////////////////////////////////

   // none

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include "QueueList.h"

using namespace std;

// Global constant definitions  ///////////////////////////////////////////////

const int SMALL_STR_LEN = 25;

const bool VERBOSE = true;

const char ENDLINE_CHAR = '\n';

// Free function prototypes  //////////////////////////////////////////////////

void ShowMenu();
char GetCommandInput();
int GetDataInput( char inputChar );

// Main function implementation  //////////////////////////////////////////////

int  main()
   {
    QueueList testListA, testListB, testListC;    // Test lists
    int testData;
    char commandChar;                             // List data item
    bool tempBool, testListC_Constructed = false;

    ShowMenu();

    do
       {
        cout << endl << "Command: ";                  // Read command
        
        commandChar = GetCommandInput();

        testData = GetDataInput( commandChar );

        if( !VERBOSE )
           {
            cout << commandChar << ": " << testData << endl;
           }

        switch ( commandChar )
           {
            case 'a':  // object assignment

               testListB = testListA;

               if( VERBOSE )
                  {
                   cout << 
                     "  Test list \'A\' has been assigned to test list \'B\'." 
                        << endl;
                  }

               break;

            case 'c':  // construct c test list

               // tempTestList constructed in code block to control scope
               // Note: Declaration of object outside of declaration area
               //       (i.e., not declared at the beginning of the function)
               //       is not accepted practice but is conducted here
               //       to demonstrate specified action
                  { 
                   QueueList tempTestList( testListA );
                 
                   testListC = tempTestList;

                   testListC_Constructed = true;
                  }

               if( VERBOSE )
                  {
                   cout << 
                "  Test list \'C\' has been constructed with test list \'A\'." 
                        << endl;
                  }

               break;

            case 'C':  // clear queue, all data destroyed

               testListA.clear();

               if( VERBOSE )
                  {
                   cout << "  Test list \'A\' cleared" << endl;
                  }

               break;

            case 'd':  // dequeue value

               tempBool = testListA.dequeue( testData );

               if( VERBOSE )
                  {
                   if( tempBool )
                      {
                       cout << "  Value: " << testData 
                            << " dequeued." << endl;
                      }
                   else
                      {
                       cout << "  Dequeue process failed." << endl;
                      }
                  }

               break;

            case 'e':  // enqueue value

               tempBool = testListA.enqueue( testData );

               if( VERBOSE )
                  {
                   if( tempBool )
                      {
                       cout << "  Value: " << testData 
                            << " enqueued." << endl;
                      }
                   else
                      {
                       cout << "  Enqueue process failed." << endl;
                      }
                  }

               break;

            case 'p':  // peek at head of queue

               tempBool = testListA.peekHead( testData );

               if( VERBOSE )
                  {
                   if( tempBool )
                      {
                       cout << "  Value: " << testData 
                            << " found at queue head." << endl;
                      }
                   else
                      {
                       cout << "  Peek at head process failed." << endl;
                      }
                  }

               break;

            case 'r':  // reset capacity of queue, if possible

               tempBool = testListA.resetCapacity( testData );

               if( VERBOSE )
                  {
                   if( tempBool )
                      {
                       cout << "  Queue capacity reset to: " << testData 
                            << '.' << endl;
                      }
                   else
                      {
                       cout << "  Queue capacity reset process failed." << endl;
                      }
                  }

               break;

            case 's':  // show list of commands

               ShowMenu();

               break;

            case 't':  // check all three tests for empty or full

               cout << "  Boolean test requested." << endl;

               tempBool = testListA.queueIsEmpty();

               if( VERBOSE )
                  {
                   if( tempBool )
                      {
                       cout << "  Queue is empty." << endl;
                      }
                   else
                      {
                       cout << "  Queue is not empty." << endl;
                      }
                  }

               tempBool = testListA.queueIsFull();

               if( VERBOSE )
                  {
                   if( tempBool )
                      {
                       cout << "  Queue is full." << endl;
                      }
                   else
                      {
                       cout << "  Queue is not full." << endl;
                      }
                  }

               tempBool = testListA.listIsEmpty();

               if( VERBOSE )
                  {
                   if( tempBool )
                      {
                       cout << "  List is empty." << endl;
                      }
                   else
                      {
                       cout << "  List is not empty." << endl;
                      }
                  }

               break;

            default :            // Invalid command

               // clear to end of line in case further data input
               cin.ignore( SMALL_STR_LEN, ENDLINE_CHAR );

               if( commandChar == 'E' )
                  {
                   cout << "  End program requested." << endl;
                  }

               else if( VERBOSE )
                  {
                   cout << "  Inactive or invalid command." << endl;
                  }

               break;
           }

        testListA.showStructure( 'A' );
        testListB.showStructure( 'B' );

        if( testListC_Constructed )
           {
            testListC.showStructure( 'C' );
           }
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

    cout << "  a    : Assign \'A\' test list to \'B\' test list" << endl;

    cout << "  c    : Construct \'C\' test list with test list \'A\'" << endl;

    cout << "  C    : Clear test list" << endl;

    cout << "  d    : Dequeue value" << endl << endl;

    cout << "  e x  : Enqueue value x" << endl;

    cout << "  E    : End the test program" << endl;

    cout << "  p    : Peek at queue head value" << endl;

    cout << "  r x  : Reset queue capacity to x, if possible" << endl;

    cout << "  s    : Show this list of commands" << endl << endl;

    cout << "  t    : Conduct list/queue empty/full tests" << endl << endl;

    cout << endl;
   }

/**
  * @brief Acquires command input from user
  *
  * @details Command letters are unique combinations of three letters
  *
  * @pre None
  *
  * @post Three characters are placed into a character array
  *
  * @par Algorithm
  *      Characters are input to array elements one at a time
  *
  * @exception None
  *
  * @param None
  *
  * @return Input character captured via iostream
  *
  * @note None
  */
char GetCommandInput
     ( 
      // no parameters
     )
   {
    char inChar;

    cin >> inChar;

    return inChar;
   }

/**
  * @brief Acquires data input if a specific command was input
  *
  * @details Accepts input for all operations starting with "e" or "r";
  *          does not input anything otherwise
  *
  * @pre None
  *
  * @post Value is input and returned if control requires it, 
  *       otherwise, zero is returned
  *
  * @par Algorithm
  *      Tests for character, 
  *      accepts input if appropriate,
  *      returns data value if input accepted,
  *      or zero if no input accepted
  *
  * @exception None
  *
  * @param[in] inputChar
  *            Character is used to check for input control
  *
  * @return Data value accepted or zero (int)
  *
  * @note None
  */
int GetDataInput
     ( 
      char inputChar // input: character used to decide to input
     )
   {
    int dataVal = 0;

    if( inputChar == 'e' || inputChar == 'r' )
       {
        cin >> dataVal;
       }

    return dataVal;
   }




