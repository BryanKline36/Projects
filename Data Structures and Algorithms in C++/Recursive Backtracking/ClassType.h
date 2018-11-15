// Program Information ////////////////////////////////////////////////////////
/**
 * @file ClassType.h
 *
 * @brief Definition file for ClassType class
 * 
 * @details Specifies all data of the ClassType class,
 *          along with the constructor
 *
 * @version 1.20
 *          Michael Leverington (11 March 2016)
 *          Updated for use with room information
 * 
 *          1.00 
 *          Michael Leverington (07 September 2015)
 *          Original code
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_CLASSTYPE_H
#define CLASS_CLASSTYPE_H

// Header files ///////////////////////////////////////////////////////////////

#include <cstdio>
#include <iostream>

// Class constants ////////////////////////////////////////////////////////////

   // None

// Class definition ///////////////////////////////////////////////////////////

class ClassType
   {
    public:

       static const int NO_CLASS = -1;
       static const int STD_STR_LEN = 80;
       static const char NULL_CHAR = '\0';

       // default constructor - required by Simple/UtilityVector
       ClassType();

       // initialization constructor
       ClassType( char *inClsName, int inClsSize );

       // assignment operator - required by Simple/UtilityVector
       const ClassType &operator = ( const ClassType &rhClass );

       // data setting operation
       void setClassData( char *inClsName, int inClsSize );

       // sets used class flag
       void setClassAvailable( bool flagState );

       // get class availability
       bool classIsAvailable();

       // get size request for room
       int getSizeRequest();

       // comparison test - required by Simple/UtilityVector
       int compareTo( const ClassType &otherClass ) const;

       // to string - required by Simple/UtilityVector
       void toString( char *outString ) const;

    private:

       // full class name
       char className[ STD_STR_LEN ];

       // class size
       int classSize;

       // used state flag
       bool classAvailable;

       void copyString( char *destination, const char *source ) const;

       int compareStrings( const char *oneStr, const char *otherStr ) const;

       int getStrLen( const char *str ) const;

       char toLower( char testChar ) const;
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_CLASSTYPE_H



