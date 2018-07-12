// Program Information ////////////////////////////////////////////////////////
/**
 * @file ClassType.cpp
 *
 * @brief Implementation file for ClassType class
 * 
 * @details Implements the methods of the ClassType class
 *
 * @version 1.10
 *          Michael Leverington (11 March 2016)
 *          Update for use with room information
 *
 *          1.00 
 *          Michael Leverington (30 January 2016)
 *          Initial development
 *
 * @Note Requires ClassType.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_CLASSTYPE_CPP
#define CLASS_CLASSTYPE_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "ClassType.h"

using namespace std;

ClassType::ClassType
       ( 
        // no parameters
       )
     : classSize( 0 ), classAvailable( true )
   {
    copyString( className, "---" );
   }

ClassType::ClassType
     ( 
      char *inClsName, 
      int inClsSize 
     )
     : classSize( inClsSize ), classAvailable( true ) 
   {
    copyString( className, inClsName );
   }

const ClassType &ClassType:: operator = 
     ( 
      const ClassType &rhClass
     )
   {
    copyString( className, rhClass.className );

    classSize = rhClass.classSize;

    classAvailable = rhClass.classAvailable;

    return *this;
   }

void ClassType::setClassData
     ( 
      char *inClsName, 
      int inClsSize 
     )
   {
    copyString( className, inClsName );
    classSize = inClsSize;
    classAvailable = true;
   }

void ClassType::setClassAvailable
     (
      bool flagState
     )
   {
    classAvailable = flagState;
   }

bool ClassType::classIsAvailable
     (
      // no parameters
     )
   {
    return classAvailable;
   }

int ClassType::getSizeRequest
     (
      // no parameters
     )
   {
    return classSize;
   }

int ClassType::compareTo
     (
      const ClassType &otherRoom
     ) const
   {
    return compareStrings( className, otherRoom.className );
   }

void ClassType::toString
     (
      char *outString
     ) const
   {
    sprintf( outString, "Class Name: %s, Class Size: %d", 
                                                      className, classSize );
   }

void ClassType::copyString
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

int ClassType::compareStrings
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

    return getStrLen( oneStr ) - getStrLen( otherStr );
   }

int ClassType::getStrLen
       ( 
        const char *str 
       ) const
   {
    int length = 0;

    while( str[ length ] != NULL_CHAR )
       {
        length++;
       }

    return length;
   }

char ClassType::toLower
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

#endif		// #ifndef CLASSTYPE_CPP



