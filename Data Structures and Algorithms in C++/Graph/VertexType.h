// Program Information ////////////////////////////////////////////////////////
/**
 * @file VertexType.h
 *
 * @brief Definition file for VertexType class
 * 
 * @details Specifies all data of the VertexType class,
 *          along with a default constructor, and public data
 *
 * @author Michael Leverington
 *
 * @version 1.00 (15 November 2015)
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef VERTEXTYPE_H
#define VERTEXTYPE_H

// Header files ///////////////////////////////////////////////////////////////

#include "PathType.h"

#include <ostream>
#include <cstdio>
#include <stdexcept>

using namespace std;

// Class constants ////////////////////////////////////////////////////////////

const int MAX_PATHS = 20;

// Class definition ///////////////////////////////////////////////////////////

struct VertexType
   {
    static const char DUMMY_VERTEX = '-';

    VertexType();
    VertexType( char letter, bool used );

    ~VertexType();

    const VertexType &operator = ( const VertexType &rhVertexType );

    void clear();

    void addPath( const PathType &newPath );

    bool getPath( int index, PathType &newPath );

    int compareTo( const VertexType &otherVertex );

    void toString( char *str );

    char toUpper( char testChar );

    char vertexLetter;
    bool usedState;
    int numPaths;
    PathType paths[ MAX_PATHS ];
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef VERTEXTYPE_H



