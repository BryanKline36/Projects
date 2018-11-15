// Program Information ////////////////////////////////////////////////////////
/**
 * @file RoomType.h
 *
 * @brief Definition file for RoomType class
 * 
 * @details Specifies all data of the RoomType class,
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

#ifndef CLASS_ROOMTYPE_H
#define CLASS_ROOMTYPE_H

// Header files ///////////////////////////////////////////////////////////////

#include <cstdio>
#include <iostream>

// Class constants ////////////////////////////////////////////////////////////

   // None

// Class definition ///////////////////////////////////////////////////////////

class RoomType
   {
    public:

       static const int NO_CLASS = -1;
       static const int STD_STR_LEN = 80;
       static const char NULL_CHAR = '\0';

       // default constructor - required by Simple/UtilityVector
       RoomType();

       // initialization constructor
       RoomType( char *bldgName, int roomNum, int roomCap );

       // assignment operator - required by Simple/UtilityVector
       const RoomType &operator = ( const RoomType &rhRoom );

       // data setting operation
       void setRoomData( char *inBldgName, 
                           int inRoomNumber, 
                             int inRoomCapacity, 
                               int inAssocClsIndex = NO_CLASS );

       // set index to associate class request data
       void setAssociatedIndex( int inAssocIndex );

       // get index of associated class request data
       int getAssociatedIndex() const;

       // get room capacity for testing
       int getRoomCapacity() const;

       // comparison test - required by Simple/UtilityVector
       int compareTo( const RoomType &otherRoom ) const;

       // to string - required by Simple/UtilityVector
       void toString( char *outString ) const;

    private:

       // building full name
       char buildingName[ STD_STR_LEN ];

       // room number
       int roomNumber;

       // room capacity
       int roomCapacity;

       // associated class index
       int associatedClassIndex;
 
       void copyString( char *destination, const char *source ) const;

       int compareStrings( const char *oneStr, const char *otherStr ) const;

       int getStrLen( const char *str ) const;

       char toLower( char testChar ) const;
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_ROOMTYPE_H



