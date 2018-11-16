// Program Information ////////////////////////////////////////////////////////
/**
 * @file VertexType.cpp
 *
 * @brief Implementation file for VertexType class
 * 
 * @details Implements member actions of the VertexType class
 *
 * @author Michael Leverington
 *
 * @version 1.00 (30 October 2015)
 *
 * @Note Requires VertexType.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef VERTEXTYPE_CPP
#define VERTEXTYPE_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "VertexType.h"

/**
 * @brief Default constructor
 *
 * @details Constructs empty VertexType
 *          
 * @param None
 *
 * @note None
 */
VertexType::VertexType
       ( 
        // no parameters
       )
     : vertexLetter( DUMMY_VERTEX ), usedState( false ),
       numPaths( 0 )
   {
    // assignment in initializers
   }

/**
 * @brief Initialization constructor
 *
 * @details Constructs VertexType with data
 *          
 * @param in: the vertex letter
 * @param in: The weight of the path to the vertex
 *
 * @note None
 */
VertexType::VertexType
       ( 
        char letter,   // in: vertex letter
        bool used     // in: the weight of the path to the vertex
       )
     : vertexLetter( letter ), usedState( false ),
       numPaths( 0 )
   {
    // assignment in initializers
   }

VertexType::~VertexType
       ( 
        // no parameters
       )
   {
    // no action here
   }

/**
 * @brief Assignment operator
 *
 * @details Assigns VertexType
 *          
 * @param in: right-hand assigned
 *
 * @note None
 */
const VertexType &VertexType::operator = 
       ( 
        const VertexType &rhVertexType  // in: incoming right-hand value
       )
   {
    int index;

    vertexLetter = rhVertexType.vertexLetter;
    usedState = rhVertexType.usedState;
    numPaths = rhVertexType.numPaths;

    for( index = 0; index < rhVertexType.numPaths; index++ )
       {
        paths[ index ] = rhVertexType.paths[ index ];
       }

    return *this;
   }

void VertexType::clear
       (
        // no parameters
       )
   {
    vertexLetter = DUMMY_VERTEX;

    usedState = false;

    numPaths = 0;
   }

void VertexType::addPath( const PathType &newPath )
   {
    paths[ numPaths ] = newPath;

    numPaths++;
   }

bool VertexType::getPath( int index, PathType &retrievedPath )
   {
    if( index < numPaths )
       {
        retrievedPath = paths[ index ];

        return true;
       }

    return false;
   }

int VertexType::compareTo( const VertexType &otherVertex )
   {
    return toUpper( vertexLetter ) - toUpper( otherVertex.vertexLetter );
   }

void VertexType::toString( char *str )
   {
    sprintf( str, "Vertex: %c, path count: %d \n", vertexLetter, numPaths );
   }

char VertexType::toUpper( char testChar )
   {
    if( testChar >= 'a' && testChar <= 'z' )
       {
        testChar = testChar - 'a' + 'A';
       }

    return testChar;
   }

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef VERTEXTYPE_CPP



