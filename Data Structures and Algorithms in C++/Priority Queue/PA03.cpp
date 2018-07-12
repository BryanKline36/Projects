// Program Information ////////////////////////////////////////////////////////
/**
 * @file PA03.cpp
 *
 * @brief Driver program to exercise the PriorityQueue class
 * 
 * @details Allows for testing all PriorityQueue methods 
 *          in an interactive environment
 *
 * @version 1.10
 *          Michael Leverington (30 January 2016)
 *          Updated for use with UtilityVector
 * 
 *          1.00 
 *          Michael Leverington (07 September 2015)
 *          Original code
 *
 * @Note Requires SimpleVector.cpp, UtilityVector.cpp,
 *                StudentType.h, PriorityQueue.cpp
 */

// Precompiler directives /////////////////////////////////////////////////////

   // none

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include "StudentType.h"
#include "SimpleVector.cpp"
#include "UtilityVector.cpp"
#include "PriorityQueue.cpp"

using namespace std;

// Global constant definitioans  //////////////////////////////////////////////

const int LARGE_STR_LEN = 100;
const int SMALL_STR_LEN = 25;

const bool VERBOSE = true;

const char SEMICOLON = ';';
const char ENDLINE_CHAR = '\n';
const char PERIOD = '.';

const int TEST_PQ_NUM_PRIORITIES = 12;

// Free function prototypes  //////////////////////////////////////////////////

void ShowMenu();
char GetCommandInput( char *nameString, int &studentID, char *gradeLevel );

// Main function implementation  //////////////////////////////////////////////

int main()
   {
    PriorityQueue<StudentType> testPQA;
    PriorityQueue<StudentType> testPQB;
    PriorityQueue<StudentType> testPQC;
    char cmdChar;
    char dataString[ LARGE_STR_LEN ];
    char name[ SMALL_STR_LEN ];
    char classLevel[ SMALL_STR_LEN ];
    int studentIdData;
    StudentType dataItem;
    bool dataChanged;

    ShowMenu();

    do
       {
        dataChanged = false;

        cout << endl << "Command: ";                  // Read command
        
        cmdChar = GetCommandInput( name, studentIdData, classLevel );

        switch ( cmdChar )
           {
            case 'A':  // assign to b PQ

               testPQB = testPQA;

               if( VERBOSE )
                  {
                   cout << "  Test PQ \'A\' has been assigned to test PQ \'B\'." 
                        << endl;
                  }

               dataChanged = true;

               break;

            case 'c':  // clear priority queue

               while( !testPQA.isEmpty() )
                  {
                   testPQA.dequeue( dataItem );
                  }

               if( VERBOSE )
                  {
                   cout << "  Priority Queue has been cleared " << endl;
                  }

               dataChanged = true;

               break;

            case 'C':  // create copy constructor PQ

               // tempPQ constructed in code block to control scope
                  { 
                   PriorityQueue<StudentType> tempPQ( testPQA );

                   testPQC = tempPQ;
                  }

               if( VERBOSE )
                  {
                   cout << "  Test PQ \'C\' has been constructed with test PQ \'A\'." 
                        << endl;
                  }

               dataChanged = true;

               break;

            case 'd': case 'D':  // dequeue one data item

               testPQA.dequeue( dataItem );

               if( VERBOSE )
                  {
                   dataItem.toString( dataString );

                   cout << "  Data: " << dataString
                        << " has been dequeued." << endl;
                  }

               dataChanged = true;

               break;

            case 'e': case 'E':  // enqueue

               dataItem.setStudentData( name, studentIdData, classLevel );
 
               testPQA.enqueue( dataItem );

               if( VERBOSE )
                  {
                   dataItem.toString( dataString );

                   cout << "  Data: " << dataString
                        << " has been enqueued." << endl;
                  }

               dataChanged = true;

               break;

            case 'h': case 'H':  // help request

               ShowMenu();

               break;

            case 'p': case 'P':  // peek at next item

               testPQA.peekAtFront( dataItem );

               if( VERBOSE )
                  {
                   dataItem.toString( dataString );

                   cout << "  Data: " << dataString
                        << " is at front of queue." << endl;
                  }
               break;

            case 'q': case 'Q':  // quit the test program

               if( VERBOSE )
                  {
                   cout << "  End Program Requested" << endl;
                  }

               cout << endl;

               break;

            default :            // Invalid command

               // clear to end of line in case further data input
               cin.ignore( SMALL_STR_LEN, ENDLINE_CHAR );

               if( VERBOSE )
                  {
                   cout << "  Inactive or invalid command" << endl;
                  }
           }

        if( dataChanged && VERBOSE )
           {
            testPQA.showStructure( 'A' );
            testPQB.showStructure( 'B' );
            testPQC.showStructure( 'C' );
           }
       }
    while ( cmdChar != 'q' && cmdChar != 'Q' );

    cout << "Final Data Set" << endl;
    testPQA.showStructure( 'A' );
    testPQB.showStructure( 'B' );
    testPQC.showStructure( 'C' );
    cout << endl;

    return 0;
   }

// Free function implementation  //////////////////////////////////////////////

/**
 * @brief ShowMenu: Displays choice of commands for exercising priority queue
 *
 * @details Command letters displayed indicate operations to be conducted
 *
 * @param None
 *
 * @note None
 */
void ShowMenu()
   {
    cout << endl << "Priority queue enqueues program process statements";
    cout << endl << "  with a priority of 1 being highest and succeeding";
    cout << endl << "  numbers are lower priority" << endl;
    cout << endl << "Commands:" << endl;
    cout << "  A       : Tests assignment operation" << endl;
    cout << "  c       : Clear priority queue" << endl;
    cout << "  C       : Tests copy constructor" << endl;
    cout << "  d       : Dequeue prioritized process" << endl;
    cout << "  e x y z : Enqueue name x, student ID y, & class level z" 
         << endl;
    cout << "  h       : Show this list of commands" << endl;
    cout << "  p       : Peek at prioritized process" << endl;
    cout << "  q       : Quit the test program" << endl;
    cout << endl;
   }

/**
 * @brief GetCommandInput: Acquires command input from user
 *
 * @details Command letters are unique combinations of three letters
 *
 * @param None
 *
 * @note Clears input string, loads command letters individually
 *       using extraction operation; adds input character for display
 *       and output line for display clearance
 */
char GetCommandInput
       ( 
        char *nameString,     // out: process string if input
        int &studentID,        // out: university student ID
        char *gradeLevel      // out : student grade level
       ) 
   {
    char inputChar, dummyChar;

    strcpy( nameString, "-" );
    studentID = 0;
    strcpy( gradeLevel, "None" );

    cin >> inputChar;

    if( inputChar == 'e' || inputChar == 'E' )
       {
        cin.getline( nameString, SMALL_STR_LEN, SEMICOLON );
        cin >> studentID >> dummyChar;
        cin >> gradeLevel;
       }

    cout << inputChar << endl;

    return inputChar;
   }













