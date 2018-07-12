// Program Information ////////////////////////////////////////////////////////
/**
 * @file StudentType.cpp
 *
 * @brief Implementation file for StudentType class
 * 
 * @details Implements the constructor method of the StudentType class
 *
 * @version 1.00 (07 September 2015)
 *
 * @Note Requires StudentType.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_DATATYPE_CPP
#define CLASS_DATATYPE_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "StudentType.h"
#include <cstdio>
#include <iostream>

using namespace std;

/**
 * @brief Default/Initialization constructor
 *
 * @details Constructs StudentType with default data
 *          
 * @pre assumes uninitialized StudentType object
 *
 * @post Initializes all data quantities
 *
 * @par Algorithm 
 *      Initializes class by assigning name, Id number, and class level
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note None
 */
StudentType::StudentType
       ( 
        // no parameters
       )
     : universityID( 0 ), priority( 0 ) 
   {
    copyString( name, "---" );
   }

/**
 * @brief Initialization constructor
 *
 * @details Constructs StudentType with provided data
 *          
 * @pre assumes uninitialized StudentType object,
 *      assumes string max length < STD_STR_LEN
 *
 * @post Initializes all data quantities
 *
 * @par Algorithm 
 *      Initializes class by assigning name, Id number, and class level
 * 
 * @exception None
 *
 * @param [in] studentName
 *             Name of student as c-string
 *
 * @param [in] univIDNum
 *             University ID number as integer
 *
 * @param [in] univClassLevel
 *             University class/grade level
 *
 * @return None
 *
 * @note None
 */
StudentType::StudentType
     ( 
      char *studentName, 
      int univIDNum, 
      char *univClassLevel
     )
     : universityID( univIDNum )
   {
    priority = setPriority( univClassLevel );

    copyString( name, studentName );
   }

/**
 * @brief Assignment operation
 *
 * @details Class overloaded assignment operator
 *          
 * @pre assumes initialized other object
 *
 * @post desination object holds copy of local this object
 *
 * @par Algorithm 
 *      Copies each data item separately
 * 
 * @exception None
 *
 * @param [in] rhStudent
 *             other StudentType object to be assigned
 *
 * @return Reference to local this StudentType object
 *
 * @note None
 */
const StudentType &StudentType:: operator = 
     ( 
      const StudentType &rhStudent 
     )
   {
    copyString( name, rhStudent.name );

    universityID = rhStudent.universityID;

    priority = rhStudent.priority;

    return *this;
   }

/**
 * @brief Data setting utility
 *
 * @details Allows resetting data in StudentType
 *          
 * @pre Makes no assumption about StudentType data
 *
 * @post Data values are correctly assigned in StudentType
 *
 * @par Algorithm 
 *      Assigns data values to class members
 * 
 * @exception None
 *
 * @param [in] studentName
 *             String name of student
 *
 * @param [in] studentID
 *             Integer value of student ID
 *
 * @param [in] studentLevel
 *             String name of student
 *
 * @return Integer result of comparison process
 *
 * @note None
 */
void StudentType::setStudentData
     ( 
      char *studentName, 
      int studentID, 
      char *classLevel 
     )
   {
    copyString( name, studentName );
    universityID = studentID;
    priority = setPriority( classLevel );
   }

/**
 * @brief Data comparison utility
 *
 * @details Provides public comparison operation for use in other classes
 *          
 * @pre Makes no assumption about StudentType data
 *
 * @post Provides integer result of comparison such that:
 *       - result < 0 indicates this < other
 *       - result == 0 indicates this == other
 *       - result > 0 indicates this > other
 *
 * @par Algorithm 
 *      Sets priorities of this and other class level item,
 *      then provides mathematic difference
 * 
 * @exception None
 *
 * @param [in] otherStudent
 *             Other student data to be compared to this object
 *
 * @return Integer result of comparison process
 *
 * @note None
 */
int StudentType::compareTo
     (
      const StudentType &otherStudent
     ) const
   {
    return priority - otherStudent.priority;
   }

/**
 * @brief Data serialization
 *
 * @details Converts data set to string for output by other data types
 *          
 * @pre Assumes data is initialized
 *
 * @post Provides all data as string
 *
 * @par Algorithm 
 *      Places data into formatted string
 * 
 * @exception None
 *
 * @param [out] outString
 *              string containing class data
 *
 * @return None
 *
 * @note None
 */
void StudentType::toString
     (
      char *outString
     ) const
   {
    sprintf( outString, "%d: %s, %d", priority, name, universityID );
   }

/**
 * @brief Gets numerical priority related to priority letter (char)
 *
 * @details None
 *          
 * @pre makes no assumptions about priority data
 *
 * @post provides priority value related to letter/char parameter
 *
 * @par Algorithm 
 *      Uses lookup table to set priorities
 * 
 * @exception None
 *
 * @param [in] student level in string form
 *
 * @return Integer result of priority letter lookup
 *
 * @note None
 */
int StudentType::getPriority
     ( 
      // no parameters
     ) const
   {
    return priority;
   }

/**
 * @brief Sets numerical priority related to priority letter (char)
 *
 * @details None
 *          
 * @pre makes no assumptions about priority data
 *
 * @post provides priority value related to letter/char parameter
 *
 * @par Algorithm 
 *      Uses lookup table to set priorities
 * 
 * @exception None
 *
 * @param [in] student level in string form
 *
 * @return Integer result of priority letter lookup
 *
 * @note None
 */
int StudentType::setPriority
     ( 
      char *priorityString
     )  
   {
    int priorityVal = 0; // default case - no priority

    switch( priorityString[ 0 ] )
       {
        // Freshman case - priority level 1
        case 'F':
        case 'f':

           priorityVal = 1;
           break;

        // Sophomore or Senior case
        case 'S':
        case 's':

           // Sophomore case - priority level 2
           if( priorityString [ 1 ] == 'O' || priorityString[ 1 ] == 'o' )
              {
               priorityVal = 2;
              }

           // Senior case - priority level 4
            else if( priorityString [ 1 ] == 'E' || priorityString[ 1 ] == 'e' )
              {
               priorityVal = 4;
              }
            break;

        // Senior case - priority level 3
        case 'J':
        case 'j':

           priorityVal = 3;
           break;

        // Graduate case - priority level 5
        case 'G':
        case 'g':

           priorityVal = 5;
           break;
       }

    return priorityVal;
   }

/**
 * @brief String copy utility
 *
 * @details Copies source string into destination string
 *          
 * @pre assumes standard string conditions, including NULL_CHAR end
 *
 * @post desination string holds copy of source string
 *
 * @par Algorithm 
 *      Copies string character by character until end of string
 *      character is found, assumes string max length < STD_STR_LEN
 * 
 * @exception None
 *
 * @param [out] Destination string
 *
 * @param [in] Source string
 *
 * @return None
 *
 * @note None
 */
void StudentType::copyString
     (
      char *destination, 
      const char *source
     )
   {
    int index = 0;

    while( source[ index ] != NULL_CHAR && index < STD_STR_LEN )
       {
        destination[ index ] = source[ index ];

        index++;

        destination[ index ] = NULL_CHAR;
       }
   }

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_DATATYPE_CPP



