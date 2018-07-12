// Program Information ////////////////////////////////////////////////////////
/**
 * @file StudentType.cpp
 *
 * @brief Implementation file for StudentType class
 * 
 * @details Implements the constructor method of the StudentType class
 *
 * @version 1.10
 *          Michael Leverington (10 February 2016)
 *          Update for use with SorterClass
 *
 *          1.00 
 *          Michael Leverington (30 January 2016)
 *          Initial development
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
     : universityID( 0 ), gender( '-' ) 
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
 *      Initializes class by assigning name, Id number, and gender
 * 
 * @exception None
 *
 * @param [in] initStudentName
 *             Name of student as c-string
 *
 * @param [in] initUnivIDNum
 *             University ID number as integer
 *
 * @param [in] initGender
 *             gender
 *
 * @return None
 *
 * @note None
 */
StudentType::StudentType
     ( 
      char *initStudentName, 
      int initUnivIDNum, 
      char initGender
     )
     : universityID( initUnivIDNum ), gender( initGender )
   {
    copyString( name, initStudentName );
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

    gender = rhStudent.gender;

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
 * @param [in] gender
 *             Character identifier for gender
 *
 * @return Integer result of comparison process
 *
 * @note None
 */
void StudentType::setStudentData
     ( 
      char *inStudentName, 
      int inStudentID, 
      char inGender
     )
   {
    copyString( name, inStudentName );
    universityID = inStudentID;
    gender = inGender;
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
 *      Parses student name into last and first using parseName,
 *      then returns test for last name first,
 *      then first name
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
    int difference, index = 0;

    while( name[ index ] != NULL_CHAR 
                                  && otherStudent.name[ index ] != NULL_CHAR )
       {
        difference = toLower( name[ index ] ) 
                                      - toLower( otherStudent.name[ index ] );

        if( difference != 0 )
           {
            return difference;
           }

        index++;
       }

    return 0;
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
    char genderStr[ STD_STR_LEN ];

    switch( gender )
       {
        case 'F':
        case 'f':

           copyString( genderStr, "Female" );
           break;

        case 'M':
        case 'm':

           copyString( genderStr, "Male" );
           break;

        default:

           copyString( genderStr, "Not Reported" );
           break;
       }

    sprintf( outString, "%s, %d, %s", name, universityID, genderStr );
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
     ) const
   {
    int index = 0;

    while( source[ index ] != NULL_CHAR && index < STD_STR_LEN )
       {
        destination[ index ] = source[ index ];

        index++;

        destination[ index ] = NULL_CHAR;
       }
   }

/**
 * @brief Name parsing utility
 *
 * @details Takes full name and breaks into first and last names
 *          
 * @pre assumes standard string conditions, including NULL_CHAR end
 *
 * @post first name and last name strings hold correct components
 *       of original full name string
 *
 * @par Algorithm 
 *      Copies string character by character from source into last name
 *      string until a comma is found, then it copies the remainder
 *      into the first name string, assumes string max length < STD_STR_LEN
 * 
 * @exception None
 *
 * @param [out] lastName
 *              String containing last name of student
 *
 * @param [out] firstName
 *              String containing first name of student
 *
 * @param [in] fullName
 *             String containing full name of student,
 *             with first and last names delimited by a comma
 *
 * @return None
 *
 * @note None
 */
void StudentType::parseNames
     ( 
      char *lastName, 
      char *firstName, 
      const char *fullName 
     ) const
   {
    int workingIndex = 0, fullNameIndex = 0;

    // skip any leading spaces
    while( fullName[ fullNameIndex ] != SPACE && fullNameIndex < STD_STR_LEN )
       {
        fullNameIndex++;
       }

    // load last name
    while( fullName[ fullNameIndex ] != COMMA && fullNameIndex < STD_STR_LEN )
       {
        lastName[ workingIndex ] = fullName[ fullNameIndex ];

        workingIndex++; fullNameIndex++;

        lastName[ workingIndex ] = NULL_CHAR;
       }

    // increment past comma
    fullNameIndex++;

    // skip any dividing spaces
    while( fullName[ fullNameIndex ] != SPACE && fullNameIndex < STD_STR_LEN )
       {
        fullNameIndex++;
       }

    // restart first name index
    workingIndex = 0;

    // load first name
    while( fullName[ fullNameIndex ] != NULL_CHAR 
                                              && fullNameIndex < STD_STR_LEN )
       {
        firstName[ workingIndex ] = fullName[ fullNameIndex ];

        workingIndex++; fullNameIndex++;

        firstName[ workingIndex ] = NULL_CHAR;
       }
   }

/**
 * @brief String comparison facility
 *
 * @details Compares two strings ignoring case
 *          
 * @pre assumes standard string conditions, including NULL_CHAR end
 *
 * @post first name and last name strings hold correct components
 *       of original full name string
 *
 * @par Algorithm 
 *      Compares letters one by one with each letter set to lower case,
 *      if a difference in letter is found, it is returned,
 *      if the end of the shortest string is reached without a difference,
 *      strings are assumed to be the same
 *      Returns 0 if strings are equal,
 *      returns > 0 if one string > other string
 *      returns < 0 if one string < other string
 * 
 * @exception None
 *
 * @param [in] oneStr
 *             One of the two strings to be compared
 *
 * @param [in] otherStr
 *              The other of the two strings to be compared
 *
 * @return Difference between two strings (int)
 *
 * @note None
 */
int StudentType::compareStrings
     ( 
      const char *oneStr, 
      const char *otherStr 
     ) const
   {
    int difference, index = 0;

    while( oneStr[ index ] != NULL_CHAR && otherStr[ index ] != NULL_CHAR )
       {
        difference = toLower( oneStr[ index ] ) - toLower( otherStr[ index ] );
        if( difference != 0 )
           {
            return difference;
           }

        index++;
       }

    return 0;
   }

/**
 * @brief Letter to lower case facility
 *
 * @details None
 *          
 * @pre No assumptions are made related to the input data
 *
 * @post If the character is an upper case letter, it is converted
 *       to lower case and returned;
 *       otherwise the character is returned unchanged
 *
 * @par Algorithm 
 *      Tests for upper case letter;
 *      If upper case, letter is mathematically modifed to lower case
 *      otherwise no action is taken
 * 
 * @exception None
 *
 * @param [in] testChar
 *             Character to be tested for upper case and modified as needed
 *
 * @return None
 *
 * @note None
 */
char StudentType::toLower
     ( 
      char testChar 
     ) const
   {
    if( testChar >= 'A' && testChar <= 'Z' )
       {
        return testChar - 'A' + 'a';
       }

    return testChar;
   }

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_DATATYPE_CPP



