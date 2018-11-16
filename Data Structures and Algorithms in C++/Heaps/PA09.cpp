// Program Information ////////////////////////////////////////////////////////
/**
 * @file PA09.cpp
 *
 * @brief Driver program to implement the recursive backtracking operation
 * 
 * @details None
 *
 * @version 1.10
 *          Bryan Kline (13 April 2016)
 *          Modified to include fitClassRooms function
 *
 *          1.00 
 *          Michael Leverington (02 April 2016)
 *          Original code
 *
 * @Note Requires Heaptype.cpp, SimpleVector, SimpleTimer.h, ClassType.h, 
 *                RoomType.h, iostream, cstring
 */

// Precompiler directives /////////////////////////////////////////////////////

   // none

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include "SimpleTimer.h"
#include "ClassType.h"
#include "RoomType.h"
#include "HeapType.cpp"
#include "SimpleVector.cpp"

using namespace std;

// Global constant definitioans  //////////////////////////////////////////////

enum FILE_DATA_CODES { STRING_CAPTURED, START_CLASSROOMS, END_CLASSROOMS, 
                                    START_CLASS_REQUESTS, END_CLASS_REQUESTS };

const int MAX_STR_LEN = 100;
const int STD_STR_LEN = 50;
const int MAX_NUM_ROOMS = 25;

const bool SHOW_INPUT = false;
const bool SHOW_TIMER = false;

const char ENDLINE_CHAR = '\n';
const char CARRIAGE_RETURN_CHAR = '\r';
const char NULL_CHAR = '\0';
const char SPACE = ' ';
const char COMMA = ',';
const char SEMI_COLON = ';';

// Free function prototypes  //////////////////////////////////////////////////

int getALine( istream &consoleIn, char *inString, 
                                        char delimiterChar = SEMI_COLON );

bool getANumber( istream &consoleIn, int &number );

void displayList( const HeapType<RoomType> &roomList, 
                                   const SimpleVector<ClassType> &classList );

bool fitClassRooms( const HeapType<RoomType> &roomHeap,
                            const HeapType<ClassType> &classHeap,
                                        SimpleVector<ClassType> &classList );

void printSpaces( int numSpaces );

// Main function implementation  //////////////////////////////////////////////

int main()
   {
    // initialize main
    HeapType<RoomType> RoomTypeHeap;
    HeapType<ClassType> ClassTypeHeap;
    SimpleVector<ClassType> classList;
    SimpleTimer timer;
    RoomType roomTypeData;
    ClassType classTypeData;
    char dummy[ MAX_STR_LEN ];
    char name[ STD_STR_LEN ];
    int roomNum, roomCap, classSize;

    // load classrooms

       // capture start line for room data
       getALine( cin, dummy );

       // loop through room data - capture name data
       while( getALine( cin, name, COMMA ) != END_CLASSROOMS )
          {
           // input room number
           getANumber( cin, roomNum );

           // input room capacity
           getANumber( cin, roomCap );

           if( SHOW_INPUT )
              {
               cout << "Room Data: " << name << ", " << roomNum 
                    << ", " << roomCap << endl;
              }
           // set room data
           roomTypeData.setRoomData( name, roomNum, roomCap );

           // add room data to heap
           RoomTypeHeap.add( roomTypeData );
          }
       // end loop

    // load class requests

       // capture start line for class data
       getALine( cin, dummy );

       // loop through class request data
       while( getALine( cin, name, COMMA ) != END_CLASS_REQUESTS )
          {
           // get class size request
           getANumber( cin, classSize );

           if( SHOW_INPUT )
              {
               cout << "Class Data: " << name << ", " << classSize << endl;
              }

           // set class request data
           classTypeData.setClassData( name, classSize );

           // add room to vector
           ClassTypeHeap.add( classTypeData );
          }           
       // end loop

    // show heaps
    RoomTypeHeap.showHPStructure( 'R' );
    ClassTypeHeap.showHPStructure( 'C' );

    // check for equal numbers of data sets
    if( RoomTypeHeap.getSize() == ClassTypeHeap.getSize() )
       {
        // start timer
        timer.start();

        // search for solution - check for success
        if( fitClassRooms( RoomTypeHeap, ClassTypeHeap, classList ) )
           {
            // stop timer before display
            timer.stop();

            // display classrooms with classes
            displayList( RoomTypeHeap, classList );

            // show time, as needed
            if( SHOW_TIMER )
               {
                timer.getElapsedTime( dummy );

                cout << endl << "Elapsed Time: " << dummy << endl << endl;
               }
           }

        // otherwise, assume failure
        else
           {
            // stop, reset timer
            timer.stop();

            // display failed attempt
            cout << endl
                 << "Solution not found for classroom/class request fit."
                 << endl << endl;

            // show time, as needed
            if( SHOW_TIMER )
               {
                timer.getElapsedTime( dummy );

                cout << endl << "Elapsed Time: " << dummy << endl << endl;
               }
           }
       }

    // otherwise, assume incorrect data input
    else
       {
        cout << "Unequal number of room and class request sets"
             << " - Program Aborted." << endl;
       }

    return 0;
   }

// Free function implementation  //////////////////////////////////////////////

bool fitClassRooms
       ( 
        const HeapType<RoomType> &roomHeap,
        const HeapType<ClassType> &classHeap,
        SimpleVector<ClassType> &classList 
       )
   {
    int index = 0;
    HeapType<RoomType> roomHeapObject( roomHeap );
    HeapType<ClassType> classHeapObject( classHeap );
    ClassType classObject;
    RoomType roomObject;
    
    classList.resize( classHeap.getSize() );

    while( !classHeapObject.isEmpty() )
    {
        classHeapObject.remove( classObject );
        roomHeapObject.remove( roomObject );   

        if( classObject.getSizeRequest() > roomObject.getRoomCapacity() )
        {
            return false;
        }
    
        classList.setAtIndex( index, classObject );
        index++;
    }

    return true;
   }

void displayList( const HeapType<RoomType> &roomHeap, 
                                   const SimpleVector<ClassType> &classList )
   {
    HeapType<RoomType> workingRoomHeap( roomHeap );
    SimpleVector<ClassType> workingClassList( classList );
    RoomType roomData;
    ClassType classData;
    int classIndex = 0;
    char roomStr[ MAX_STR_LEN ], classStr[ MAX_STR_LEN ];

    cout << endl << "Classroom/Class Request Fit List" << endl;
    cout <<  "================================" << endl << endl;

    while( !workingRoomHeap.isEmpty() )
       {
        workingRoomHeap.remove( roomData );
        roomData.toString( roomStr );

        classData = workingClassList.getAtIndex( classIndex );
        classData.toString( classStr );

        cout << roomStr << " - " << classStr << endl;

        classIndex++;
       }
   }

int getALine( istream &consoleIn, char *inString, char delimiterChar )
   {
    char inChar;
    int index = 0;

    inString[ 0 ] = NULL_CHAR;

    consoleIn.get( inChar );

    while( index < MAX_STR_LEN - 1 && inChar != delimiterChar )
       {
        if( inChar != ENDLINE_CHAR && inChar != CARRIAGE_RETURN_CHAR )
           {
           inString[ index ] = inChar;

           index++;
 
           inString[ index ] = NULL_CHAR;

           if( strcmp( inString, "Start Room Data;" ) == 0 )
              {
               return START_CLASSROOMS;
              }

           else if( strcmp( inString, "End Room Data;" ) == 0 )
              {
               return END_CLASSROOMS;
              }

           else if( strcmp( inString, "Start Class Data;" ) == 0 )
              {
               return START_CLASS_REQUESTS;
              }

           else if( strcmp( inString, "End Class Data;" ) == 0 )
              {
               return END_CLASS_REQUESTS;
              }
           }
        
        consoleIn.get( inChar );
       }
       
    return STRING_CAPTURED;
   }

bool getANumber( istream &consoleIn, int &number )
   {
    char dummyChar;

    consoleIn >> number;
    consoleIn >> dummyChar;

    return ( dummyChar == SEMI_COLON );
   }

void printSpaces( int numSpaces )
   {
    while( numSpaces > 0 )
       {
        cout << SPACE;

        numSpaces--;
       }
   }












