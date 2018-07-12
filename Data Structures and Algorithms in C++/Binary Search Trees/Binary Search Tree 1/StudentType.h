// Program Information ////////////////////////////////////////////////////////
/**
 * @file DataType.h
 *
 * @brief Definition file for DataType class
 * 
 * @details Specifies all data of the DataType class,
 *          along with the constructor
 *
 * @version 1.10
 *          Michael Leverington (30 January 2016)
 *          Updated for use with UtilityVector
 * 
 *          1.00 
 *          Michael Leverington (07 September 2015)
 *          Original code
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_STUDENTTYPE_H
#define CLASS_STUDENTTYPE_H

// Header files ///////////////////////////////////////////////////////////////

   // None

// Class constants ////////////////////////////////////////////////////////////

   // None

// Class definition ///////////////////////////////////////////////////////////

class StudentType
   {
    public:

       static const int STD_STR_LEN = 50;
       static const int DATA_SET_STR_LEN = 100;
       static const char COMMA = ',';
       static const char SPACE = ' ';
       static const char NULL_CHAR = '\0';

       // default constructor - required by Simple/UtilityVector
       StudentType();

       // initialization constructor
       StudentType( char *initStudentName, int initUnivIDNum, char initGender );

       // assignment operator - required by Simple/UtilityVector
       const StudentType &operator = ( const StudentType &rhStudent );

       // data setting operation
       void setStudentData( char *inStudentName, 
                                          int inStudentID, char inGender );

       // comparison test - required by Simple/UtilityVector
       int compareTo( const StudentType &otherStudent ) const;

       // to string - required by Simple/UtilityVector
       void toString( char *outString ) const;

    private:

       // student full name
       char name[ STD_STR_LEN ];

       // University ID
       int universityID;

       // Gender
       char gender;

       void copyString( char *destination, const char *source ) const;
       void parseNames( char *lastName, char *firstName, 
                                                 const char *fullName ) const;
       int compareStrings( const char *oneStr, const char *otherStr ) const;
       char toLower( char testChar ) const;
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_STUDENTTYPE_H



