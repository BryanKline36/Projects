// Program Information ////////////////////////////////////////////////////////
/**
 * @file PA03.cpp
 *
 * @brief Driver program to exercise the LinkedList class
 * 
 * @details Allows for testing all LinkedList methods 
 *          in an interactive environment
 *
 * @version 1.20
 *          Michael Leverington (06 February 2016)
 *          Updated for use with LinkedList
 *
 *          1.10
 *          Michael Leverington (30 January 2016)
 *          Updated for use with UtilityVector
 * 
 *          1.00 
 *          Michael Leverington (07 September 2015)
 *          Original code
 *
 * @Note Requires LinkedList.cpp, StudentType.h, LinkedList.cpp
 */

// Precompiler directives /////////////////////////////////////////////////////

   // none

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include "StudentType.h"
#include "LinkedList.cpp"
#include "InterfaceClass.cpp"

using namespace std;

// Global constant definitioans  //////////////////////////////////////////////

const int LARGE_STR_LEN = 100;
const int SMALL_STR_LEN = 25;

const bool VERBOSE = false;

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
    InterfaceClass<StudentType> testPQA;
    InterfaceClass<StudentType> testPQB;
    InterfaceClass<StudentType> testPQC;
    char cmdChar;
    char dataString[ LARGE_STR_LEN ];
    char name[ SMALL_STR_LEN ];
    char classLevel[ SMALL_STR_LEN ];
    int studentIdData;
    StudentType dataItem;
    bool dataChanged, responseFlag;

    ShowMenu();

    do
       {
        responseFlag = dataChanged = false;

        cout << endl << "Command: ";                  // Read command
        
        cmdChar = GetCommandInput( name, studentIdData, classLevel );

        switch ( cmdChar )
           {
            case 'A':  // assign to b PQ

               testPQB = testPQA;

               if( VERBOSE )
                  {
                   cout << "-Test PQ \'A\' has been assigned to test PQ \'B\'." 
                        << endl;
                  }

               dataChanged = true;

               break;

            case 'b':  // move backward in list

               responseFlag = --testPQA;

               if( VERBOSE )
                  {
                   if( responseFlag )
                      {
                       cout << "-Current location has been moved back in list"
                            << endl;
                      }
                   else
                      {
                       cout << "-Failed to move current location back in list"
                            << endl;
                      }
                  }

               break;

            case 'B':  // moved to beginning of list

               testPQA.toBeginning();

               if( VERBOSE )
                  {
                   cout << "-Current location has been moved to beginning of list "
                        << endl;
                  }

               break;

            case 'c':  // clear linked list

               testPQA.clearList();

               if( VERBOSE )
                  {
                   cout << "-Linked List has been cleared " << endl;
                  }

               dataChanged = true;

               break;

            case 'C':  // create copy constructor PQ

               // tempPQ constructed in code block to control scope
                  { 
                   InterfaceClass<StudentType> tempPQ( testPQA );

                   testPQC = tempPQ;
                  }

               if( VERBOSE )
                  {
                   cout << "-Test PQ \'C\' has been constructed with test PQ \'A\'." 
                        << endl;
                  }

               dataChanged = true;

               break;

            case 'E':  // moved to end of list

               testPQA.toEnd();

               if( VERBOSE )
                  {
                   cout << "-Current location has been moved to end of list "
                        << endl;
                  }

               break;

            case 'f':  // move forward in list

               responseFlag = ++testPQA;

               if( VERBOSE )
                  {
                   if( responseFlag )
                      {
                       cout << "-Current location has been moved forward in list"
                            << endl;
                      }
                   else
                      {
                       cout << "-Failed to move current location forward in list"
                            << endl;
                      }
                  }

               break;

            case 'h': case 'H':  // help request

               ShowMenu();

               break;

            case 'i':  // insert one data item

               dataItem.setStudentData( name, studentIdData, classLevel );
 
               testPQA.insertAtCurrent( dataItem );

               if( VERBOSE )
                  {
                   dataItem.toString( dataString );

                   cout << "-Data: " << dataString
                        << " has been inserted." << endl;
                  }

               dataChanged = true;

               break;

            case 'q': case 'Q':  // quit the test program

               if( VERBOSE )
                  {
                   cout << "-End Program Requested" << endl;
                  }

               cout << endl;

               break;

            case 'r':  // remove one data item

               testPQA.removeAtCurrent( dataItem );

               if( VERBOSE )
                  {
                   dataItem.toString( dataString );

                   cout << "-Data: " << dataString
                        << " has been removed." << endl;
                  }

               dataChanged = true;

               break;

            case 'v':  // view data item

               dataItem = *testPQA;

               if( VERBOSE )
                  {
                   dataItem.toString( dataString );

                   cout << "-Data: " << dataString
                        << " is at current location." << endl;
                  }

               dataChanged = true;

               break;

            default :            // Invalid command

               // clear to end of line in case further data input
               cin.ignore( SMALL_STR_LEN, ENDLINE_CHAR );

               if( VERBOSE )
                  {
                   cout << "-Inactive or invalid command" << endl;
                  }
           }

        if( dataChanged && VERBOSE )
           {
            testPQA.showLLStructure( 'A' );
            testPQB.showLLStructure( 'B' );
            testPQC.showLLStructure( 'C' );
           }
       }
    while ( cmdChar != 'q' && cmdChar != 'Q' );

    cout << "Final Data Set" << endl;
    testPQA.showLLStructure( 'A' );
    testPQB.showLLStructure( 'B' );
    testPQC.showLLStructure( 'C' );
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
    cout << endl << "Linked List program manages student data";
    cout << endl << "Commands:" << endl;
    cout << "  A       : Tests assignment operation" << endl;
    cout << "  b       : Move backward in the list" << endl;
    cout << "  B       : Move to beginning of the list" << endl;
    cout << "  c       : Clear Linked List" << endl;
    cout << "  C       : Tests copy constructor" << endl;
    cout << "  E       : Move to end of the list" << endl;
    cout << "  f       : Move forward in the list" << endl;
    cout << "  h       : Show this list of commands" << endl;
    cout << "  i x y z : Insert name x, student ID y, & class level z" 
         << endl;
    cout << "  q       : Quit the test program" << endl;
    cout << "  r       : Remove item" << endl;
    cout << "  v       : View data at current node" << endl;

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
    cin.ignore();

    if( inputChar == 'i' )
       {
        cin.getline( nameString, SMALL_STR_LEN, SEMICOLON );
        cin >> studentID >> dummyChar;
        cin >> gradeLevel;
       }

    cout << inputChar << endl;

    return inputChar;
   }













