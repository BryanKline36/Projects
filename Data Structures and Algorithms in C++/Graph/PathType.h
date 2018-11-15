// Program Information ////////////////////////////////////////////////////////
/**
 * @file PathType.h
 *
 * @brief Definition file for PathType class
 * 
 * @details Specifies all data of the PathType class,
 *          along with a default constructor, and public data
 *
 * @author Michael Leverington
 *
 * @version 1.00 (15 November 2015)
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef PATHTYPE_H
#define PATHTYPE_H

// Header files ///////////////////////////////////////////////////////////////

#include <ostream>
#include <iostream>
#include <cstdio>
#include <stdexcept>

using namespace std;

// Class constants ////////////////////////////////////////////////////////////

   // None

// Class definition ///////////////////////////////////////////////////////////

struct PathType
   {
    static const char DUMMY_VERTEX = '-';

    PathType();
    PathType( char letter, int weight );

    const PathType &operator = ( const PathType &rhPathType );

    void clear();

    int compareTo( const PathType &otherPathType );

    char toUpper( char testChar );

    void toString( char *str );

    char vertexLetter;
    int pathWeight;
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef PATHTYPE_H



