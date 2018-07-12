// Program Information ////////////////////////////////////////////////////////
/**
 * @file PA11.cpp
 *
 * @brief Program demonstrates BFS and DFS with graph data
 * 
 * @details Uses three different data managing tools
 *
 * @version 1.10 (27 April 2016)
 *          Bryan Kline
 *          Addition of depth first and breadth first traversals
 *
 *          1.00 (15 November 2015)
 *
 * @Note Requires iostream, cstring, SimpleList.cpp, SimpleQueue.cpp,
 *                SimpleStack.cpp, VertexClass.h, and PathClass.h
 */

// Precompiler directives /////////////////////////////////////////////////////

   // None

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include "VertexType.h"
#include "PathType.h"
#include "SimpleList.cpp"
#include "SimpleQueue.cpp"
#include "SimpleStack.cpp"

using namespace std;

// Global constant definitioans  //////////////////////////////////////////////

const char DATA_END_CHAR = '#';
const char NULL_CHAR = '\0';
const int MAX_STR_LEN = 80;
const char COLON = ':';
const char TAB = '\t';
const int MAX_VERTICES = 50;

// Free function prototypes  //////////////////////////////////////////////////

bool getALine( istream &consoleIn, char &vert_1, int &wt, char &vert_2 );
bool getLine( istream &consoleIn, char *str, int length, char stopChar );
void dumpList( const SimpleList<VertexType> &list );
void BreadthFirstTraversal( const SimpleList<VertexType> &list );
void DepthFirstTraversal( const SimpleList<VertexType> &list );
int returnIndex( char letter, const SimpleList<VertexType> &list );
int findAdjacencies( const VertexType &vertex, 
                                          const SimpleList<VertexType> &list );

// Main function implementation  //////////////////////////////////////////////

int  main()
   {
    SimpleList<VertexType> vertexList( MAX_VERTICES );
    VertexType workingVertex;
    PathType workingPath;
    char vertex_1, vertex_2;
    int weight;

    cout << endl << "Loading Data" << endl << endl;

    while( getALine( cin, vertex_1, weight, vertex_2 ) )
       {
        // set first vertex to second vertex information
        workingVertex.vertexLetter = vertex_1;
        
        workingPath.vertexLetter = vertex_2;

        workingPath.pathWeight = weight;

        vertexList.findData( workingVertex, REMOVE_ITEM );

        workingVertex.addPath( workingPath );

        vertexList.addItem( workingVertex );

        // set second vertex to first vertex information
        workingVertex.clear();

        workingVertex.vertexLetter = vertex_2;

        workingPath.vertexLetter = vertex_1;

        workingPath.pathWeight = weight;

        vertexList.findData( workingVertex, REMOVE_ITEM );

        workingVertex.addPath( workingPath );

        vertexList.addItem( workingVertex );

        workingVertex.clear();
       }

    dumpList( vertexList );

    DepthFirstTraversal( vertexList );

    BreadthFirstTraversal( vertexList );

    return 0;
   }

// Free function implementation  //////////////////////////////////////////////

//Function that traverses a graph in a depth first manner
void DepthFirstTraversal( const SimpleList<VertexType> &list )
{
    int index = 0;
    SimpleList<VertexType> tempList( list );
    SimpleStack<VertexType> stack; 
    VertexType tempItem;   

    cout << "Implementing Depth First Traversal" << endl;
    cout << "Visiting vertices: ";

    tempList[index].usedState = true;
    stack.push( tempList[index] );
    cout << tempList[index].vertexLetter; 

    while( !stack.isEmpty() )
    {
        stack.peekTop( tempItem );
        // condition: an unused adjacency was not found
        if( ( findAdjacencies( tempItem, tempList ) ) == -1 )
        {
            stack.pop( tempItem );
        }
        else
        {
            index = findAdjacencies( tempItem, tempList );
            tempList[index].usedState = true;
            stack.push( tempList[index] );    
            cout << ", " << tempList[index].vertexLetter;
        }
    }
    cout << endl << endl;
      
}

//Function that traverses a graph in a breadth first manner
void BreadthFirstTraversal( const SimpleList<VertexType> &list )
{
    int index = 0;
    SimpleList<VertexType> tempList( list );
    SimpleQueue<VertexType> queue; 
    VertexType tempItem;       

    cout << "Implementing Breadth First Traversal" << endl;
    cout << "Visiting vertex: ";

    tempList[index].usedState = true;
    queue.enqueue( tempList[index] );
    cout << tempList[index].vertexLetter;

    while( !queue.isEmpty() )
    {
        queue.dequeue( tempItem );
        index = 0;        

        while( index != -1 )  
        {
            index = findAdjacencies( tempItem, tempList );
            // condition: an unused adjacency was found
            if( index != -1 )
            {
                tempList[index].usedState = true;
                queue.enqueue( tempList[index] );
                cout << ", " << tempList[index].vertexLetter;
            }
        }
    }
    cout << endl << endl; 
}

// Function that returns the index of a vertex in a SimpleList given its 
// vertex letter
int returnIndex( char letter, const SimpleList<VertexType> &list )
{
    int index;

    for( index = 0; index < list.getSize(); index++ )
    {
        // condition: the letter of the vertex in the list is the same as that
        //            passed in as a parameter
        if( ( list[index] ).vertexLetter == letter )
        {
            return index;
        }
    }        

    return -1;
}

// Function that finds the first adjacency of a vertex and returns the index in
// the SimpleList 
int findAdjacencies( const VertexType &vertex, 
                                           const SimpleList<VertexType> &list )
{
    int index, check;

    for( index = 0; index < vertex.numPaths; index++ )
    {
        check = returnIndex( ( vertex.paths[index] ).vertexLetter, list );
        // condition: the vertex is in the list and it's not been visited
        if( check >= 0 && !list[check].usedState )
        {
            return returnIndex( list[check].vertexLetter, list );
        }
    }  
    
    return -1;
}

void dumpList( const SimpleList<VertexType> &list )
   {
    SimpleList<VertexType> testList( list );
    VertexType workingVertex;
    PathType workingPath;
    int vertIndex = 0, pathIndex;

    cout << "Starting Vertex List Dump: " << endl;

    while( vertIndex < testList.getSize() )
       {
        workingVertex = testList[ vertIndex ];

        cout << "Vertex: " << workingVertex.vertexLetter << endl;

        for( pathIndex = 0; pathIndex < workingVertex.numPaths; pathIndex++ )
           {
            workingPath = workingVertex.paths[ pathIndex ];

            cout << TAB << "Path: " << workingPath.pathWeight
                 << " to: " << workingPath.vertexLetter << endl;
           }

        cout << endl;

        vertIndex++;
       }
   }

bool getALine( istream &consoleIn, char &vert_1, int &wt, char &vert_2 )
   {
    char inChar;

    // get first vertex
    consoleIn >> vert_1;

    if( vert_1 == DATA_END_CHAR )
       {
        return false;
       }
   
    // get divider comma
    consoleIn >> inChar;

    // get path weight
    consoleIn >> wt;

    // get divider comma
    consoleIn >> inChar;

    // get second vertex
    consoleIn >> vert_2;

    return true;
   }

bool getLine( istream &consoleIn, char *str, int length, char stopChar )
   {
    const char LOWEST_PRINTABLE_CHAR = 32;  // space
    const char HIGHEST_PRINTABLE_CHAR = 126;  // tilde 
    int index = 0;
    int inVal;
    bool istreamState = consoleIn.good();

    inVal = consoleIn.get();

    while( char( inVal ) != stopChar && index < length - 1  )
       {
        if( inVal >= LOWEST_PRINTABLE_CHAR 
                                    && inVal <= HIGHEST_PRINTABLE_CHAR )
           {
            str[ index ] = char( inVal );

            index++;

            str[ index ] = NULL_CHAR;
           }

        inVal = consoleIn.get();
       }

    return istreamState;
   }

