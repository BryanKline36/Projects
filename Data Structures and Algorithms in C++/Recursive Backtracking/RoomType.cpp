// Program Information ////////////////////////////////////////////////////////
/**
 * @file RoomType.cpp
 *
 * @brief Implementation file for RoomType class
 * 
 * @details Implements the methods of the RoomType class
 *
 * @version 1.10
 *          Michael Leverington (11 March 2016)
 *          Update for use with room information
 *
 *          1.00 
 *          Michael Leverington (30 January 2016)
 *          Initial development
 *
 * @Note Requires RoomType.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_ROOMTYPE_CPP
#define CLASS_ROOMTYPE_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "RoomType.h"

using namespace std;

RoomType::RoomType
       ( 
        // no parameters
       )
     : roomNumber( 0 ), 
       roomCapacity( 0 ), associatedClassIndex( 0 )
   {
    copyString( buildingName, "---" );
   }

RoomType::RoomType
     ( 
      char *bldgName, 
      int roomNum, 
      int roomCap
     )
     : roomNumber( roomNum ), roomCapacity( roomCap ), 
       associatedClassIndex( 0 )
   {
    copyString( buildingName, bldgName );
   }

const RoomType &RoomType:: operator = 
     ( 
      const RoomType &rhRoom 
     )
   {
    copyString( buildingName, rhRoom.buildingName );

    roomNumber = rhRoom.roomNumber;

    roomCapacity = rhRoom.roomCapacity;

    associatedClassIndex = rhRoom.associatedClassIndex;

    return *this;
   }

void RoomType::setRoomData
     ( 
      char *inBldgName, 
      int inRoomNumber, 
      int inRoomCapacity,
      int inAssocClsIndex
     )
   {
    copyString( buildingName, inBldgName );
    roomNumber = inRoomNumber;
    roomCapacity = inRoomCapacity;
    associatedClassIndex = inAssocClsIndex;
   }

void RoomType::setAssociatedIndex
       ( 
        int inAssocIndex 
       )
   {
    associatedClassIndex = inAssocIndex;
   }

int RoomType::getAssociatedIndex
       ( 
        // no parameters
       ) const
   {
    return associatedClassIndex;
   }

int RoomType::getRoomCapacity
       ( 
        // no parameters
       ) const
   {
    return roomCapacity;
   }

int RoomType::compareTo
     (
      const RoomType &otherRoom
     ) const
   {
    int difference;

    difference = compareStrings( buildingName, otherRoom.buildingName );

    if( difference != 0 )
       {
        return difference;
       }

    return roomNumber - otherRoom.roomNumber;
   }

void RoomType::toString
     (
      char *outString
     ) const
   {
    sprintf( outString, 
               "Building Name: %s, Room Number: %d, Room Capacity: %d", 
                                     buildingName, roomNumber, roomCapacity );
   }

void RoomType::copyString
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

int RoomType::compareStrings
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

int RoomType::getStrLen
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

char RoomType::toLower
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

#endif		// #ifndef CLASS_ROOMTYPE_CPP



