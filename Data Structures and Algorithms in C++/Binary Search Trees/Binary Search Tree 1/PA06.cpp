// Program Information ////////////////////////////////////////////////////////
/**
 * @file PA07.cpp
 *
 * @brief Driver program to exercise the BST class, with account information
 * 
 * @details Allows for testing the BST class,
 *          along with a timer class that will be used for evaluation
 *
 * @version 1.10
 *          Michael Leverington (28 February 2016)
 *          Updated for new assignment
 * 
 *          1.00 
 *          Michael Leverington (09 October 2015)
 *          Original code
 *
 * @Note Requires iostream.h, cstring, StudentType.h, BSTClass.cpp
 */

// Precompiler directives /////////////////////////////////////////////////////

   // None

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include "StudentType.h"
#include "BSTClass.cpp"

using namespace std;

// Global constant definitioans  //////////////////////////////////////////////

const char ENDLINE_CHAR = '\n';
const char CARRIAGE_RETURN_CHAR = '\r';
const char NULL_CHAR = '\0';
const char SEMI_COLON = ';';
const int MAX_NAME_LEN = 50;
const int MAX_DATA_LEN = 100;

const bool INPUT_TEST = false;    // shows raw input data
const bool MANUAL_ENTRY = false;  // for manual entry/not redirected entry

enum cCodes { DUMMY, BC_1_IOT, BC_1_ASSGND, BC_1_PSTOT, BC_1_PREOT, 
                                    BC_1_RI, BC_1_FI, BC_1_CLRD, BC_1_CPYD };

// Free function prototypes  //////////////////////////////////////////////////

int getControlCode( istream &consoleIn );
bool getALine( istream &consoleIn, StudentType &inputData );
void displayCodeChoices();

// Main function implementation  //////////////////////////////////////////////

int  main()
   {
    StudentType ST_1, removeStudent, retrieveStudent;
    BSTClass<StudentType> BC_1, BC_2;
    char studentInfoStr[ MAX_DATA_LEN ];
    int controlCode, inputCtr = 0;

    displayCodeChoices();

    controlCode = getControlCode( cin );

    cout << controlCode << endl;

    if( MANUAL_ENTRY )
       {
        cout << "Data Entry:" << endl;
       }

    if( INPUT_TEST )
       {
        cout << endl << "Input Data:" << endl;
       }

    while( getALine( cin, ST_1 ) )
       {
        if( INPUT_TEST )
           {
            ST_1.toString( studentInfoStr );

            cout << studentInfoStr << endl;
           }

        BC_1.insert( ST_1 );

        inputCtr++;

        if( inputCtr == 3 )
           {
            removeStudent = ST_1;
           }

        else if( inputCtr == 6 )
           {
            retrieveStudent = ST_1;
           }
       }

    switch( controlCode )
       {
        case BC_1_IOT:

           cout << endl << "BC_1 In Order Traversal: " << endl;

           BC_1.inOrderTraversal();

           break;

        case BC_1_RI:

           cout << endl << "Test of removal operation" << endl;

           cout << endl << "BC_1 Traversal before removal: " << endl;

           BC_1.inOrderTraversal();

           BC_1.remove( removeStudent );

           removeStudent.toString( studentInfoStr );

           cout << endl 
                << "BC_1 Traversal after removal of " << studentInfoStr 
                << endl;

           BC_1.inOrderTraversal();

           break;

        case BC_1_FI:

           cout << endl << "Test of find operation" << endl;

           cout << endl << "BC_1 Traversal before search: " << endl;

           BC_1.inOrderTraversal();

           if( BC_1.find( retrieveStudent ) )
              {
               retrieveStudent.toString( studentInfoStr );

               cout << endl 
                    << "Retrieve Account Information: "
                    << studentInfoStr << endl;
              }

           else
              {
               cout << "ERROR: Name not found." << endl;
              }

           break;

        case BC_1_ASSGND:

           cout << endl << "Test of tree assignment operation" << endl;

           cout << endl << "BC_1 In Order Traversal: " << endl;

           BC_1.inOrderTraversal();
 
           BC_2 = BC_1;

           cout << endl << "BC_2 In Order Traversal: " << endl;

           BC_2.inOrderTraversal();

           break;

        case BC_1_PSTOT:

           cout << endl << "BC_1 Post Order Traversal: " << endl;

           BC_1.postOrderTraversal();

           break;

        case BC_1_PREOT:
           cout << endl << "BC_1 Pre Order Traversal: " << endl;
           BC_1.preOrderTraversal();
           break;

        case BC_1_CLRD:

           cout << endl << "Test of tree clearing operation" << endl;

           cout << endl << "BC_1 Traversal before cleared: " << endl;

           BC_1.inOrderTraversal();

           BC_1.clear();

           cout << endl << "BC_1 Traversal after removal: " << endl;

           BC_1.inOrderTraversal();

           break;

        case BC_1_CPYD:

           cout << endl << "Test of tree object copy operation" << endl;

           cout << endl << "BC_1 In Order Traversal: " << endl;

           BC_1.inOrderTraversal();

           // Non-standard action: Object instantiated in a location
           //   not at the beginning of the function
           BSTClass<StudentType> BC_3( BC_1 );
      
           cout << endl << "BC_3 In Order Traversal: " << endl;

           BC_3.inOrderTraversal();

           break;
       } 
       
    return 0;
   }

void displayCodeChoices()
   {
    cout << "Here is the list of codes for the various tests:" << endl;

    cout << "Show in order traversal           : " << BC_1_IOT << endl;
    cout << "Show object assignment operation  : " << BC_1_ASSGND << endl;
    cout << "Show post order traversal         : " << BC_1_PSTOT << endl;
    cout << "Show pre order traversal          : " << BC_1_PREOT << endl;
    cout << "Show remove item action           : " << BC_1_RI << endl;
    cout << "Show retrieved data               : " << BC_1_FI << endl;
    cout << "Show tree cleared action          : " << BC_1_CLRD << endl;
    cout << "Show tree copied action           : " << BC_1_CPYD << endl;
    cout << endl << "Enter code number: ";
   }

int getControlCode( istream &consoleIn )
   {
    char inChar;
    int codeNum;

    consoleIn >> codeNum;

    while( inChar != ENDLINE_CHAR )
       {
        consoleIn.get( inChar );
       }

    return codeNum;
   }

bool getALine( istream &consoleIn, StudentType &inputData )
   {
    const int QUIT_LENGTH = 4;
    char inChar;
    int index = 0;
    char inName[ MAX_DATA_LEN ];
    int inIDNum;
    char inGender;

    // get name
    consoleIn.get( inChar );

    while( index < MAX_NAME_LEN - 1 && inChar != SEMI_COLON )
       {
        if( inChar != CARRIAGE_RETURN_CHAR && inChar != ENDLINE_CHAR )
           {
            inName[ index ] = inChar;

            index++;
 
            inName[ index ] = NULL_CHAR;
           }

        if( strlen( inName ) == QUIT_LENGTH 
                                          && strcmp( inName, "QUIT" ) == 0 )
           {
            return false;
           }

        consoleIn.get( inChar );
       }

    // get ID number
    consoleIn >> inIDNum;

    // get next semicolon
    consoleIn.get( inChar ); 

    // get gender
    consoleIn.get( inGender ); 

    inputData.setStudentData( inName, inIDNum, inGender );
            
    return true;
   }






