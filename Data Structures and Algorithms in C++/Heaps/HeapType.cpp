// Program Information ////////////////////////////////////////////////////////
/**
 * @file HeapType.cpp
 *
 * @brief HeapType class implementation 
 * 
 * @details Implementation of HeapType class methods
 *
 * @version 1.00 
 *          Bryan Kline (10 April 2016)
 *          Oringial code
 *          
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef HEAPTYPE_CPP
#define HEAPTYPE_CPP

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "HeapType.h"

using namespace std;

// Global constants ///////////////////////////////////////////////////////////

const int BASE_TWO = 2;
const int TWO = 2;
const int THREE = 3;
const int TWO_DIGIT = 10;
const int THREE_DIGIT = 100;
const float RESIZE = 1.25;

// HeapType class method implementation ///////////////////////////////////////

/**
 *@brief Implementation of HeapType class default constructor 
 *
 *@details Sets data members to default values and allocates memory for heap
 *
 *@pre Assumes an uninitialized HeapType object
 *
 *@post An initialized HeapType object with data members set to default values
 *
 *@par Algorithm  
 *     Initializers are used to set data members to default values and memory
 *     is allocated for the heap
 *
 *@exception None
 *
 *@param None
 *
 *@return None
 *
 *@note Initializers used
 */
template <class DataType>
HeapType<DataType>:: HeapType
       (
        // no parameters
       )
    : heapCapacity( DEFAULT_CAPACITY ),
      heapSize( 0 ), 
      heapVector( NULL )
{
    heapVector = new DataType[DEFAULT_CAPACITY];
}

/**
 *@brief Implementation of HeapType class copy constructor 
 *
 *@details Copies the data members and values from the heap passed in as a
 *         parameter into the calling heap
 *
 *@pre Assumes an uninitialized HeapType object
 *
 *@post The heap is created with all values as the heap passed in as a 
 *      parameter
 *
 *@par Algorithm  
 *     Initializers are used to set data members to default values and then
 *     the overloaded assignment operator is called on the local object
 *
 *@exception None
 *
 *@param[in] copiedVector
 *           A reference parameter of type HeapType which corresponds to the
 *           heap to be copied into the local object (HeapType<DataType>)
 *
 *@return None
 *
 *@note Initializers used
 */
template <class DataType>
HeapType<DataType>:: HeapType
       ( 
        const HeapType<DataType> &copiedVector // in: the heap to be copied
       )
    : heapCapacity( copiedVector.heapCapacity ),
      heapSize( copiedVector.heapSize ), 
      heapVector( NULL )    
{
    *this = copiedVector;
}

/**
 *@brief Implementation of HeapType class destructor
 *
 *@details Deletes heap and sets data members to default values
 *
 *@pre Assumes initialized HeapType object
 *
 *@post All memory allocated to the head freed and data members set to default
 *      values
 *
 *@par Algorithm  
 *     Data members are set to default values and if the heap pointer is not
 *     NULL then the heap is deleted
 *
 *@exception None
 *
 *@param None 
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
HeapType<DataType>:: ~HeapType
       ( 
        // no parameters
       )
{
    heapSize = 0;
    heapCapacity = 0;

    // condition: the heap pointer is not NULL
    if( heapVector != NULL )
    {
        delete heapVector;
        heapVector = NULL;
    }
}

/**
 *@brief Implementation of HeapType class overloaded assignment operator 
 *
 *@details Copies the data members and values from the heap passed in as a
 *         parameter into the calling heap
 *
 *@pre Assumes an uninitialized HeapType object
 *
 *@post The calling heap has the values of the heap passed in as a parameter
 *      copied into it
 *
 *@par Algorithm  
 *     An if statement checks that the calling object and the parameter are not
 *     the same object and if not then a call to copyHeapVector copies the 
 *     vector and then the local data members are assigned to those of the 
 *     parameter and then the local object is returned 
 *
 *@exception None
 *
 *@param[in] rhVector
 *           A reference parameter of type HeapType which corresponds to the
 *           heap to be copied into the local object (HeapType<DataType>)
 *
 *@return A the local object of type HeapType is returned (HeapType<DataType>)
 *
 *@note None
 */
template <class DataType>
const HeapType<DataType>& HeapType<DataType>:: operator = 
       ( 
        const HeapType<DataType> &rhVector // in: the heap to be copied
       )
{
    // condition: if the parameter is not the same as the local object
    if( this != &rhVector )
    {
        copyHeapVector( heapVector, rhVector.heapVector, 
                                                       rhVector.heapCapacity );
        heapCapacity = rhVector.heapCapacity;
        heapSize = rhVector.heapSize;           
    }     

    return *this;
}

/**
 *@brief Implementation of HeapType class method to print the heap to the
 *       screen in the form of a tree
 *
 *@details The heapVector is printed out in such a way so as to resemble a tree
 *
 *@pre Assumes an initialized HeapType object
 *
 *@post The heap is printed out in the form of a tree and the heap is unchanged
 *
 *@par Algorithm 
 *     A nested counter controlled loop calls getSpacing to determine the
 *     proper spacing, prints out leading spaces with a call to displayChars, 
 *     both in the outter loop, then the inner loop prints out items in the
 *     tree and dividing spaces with calls to displayChars and displayInt
 *     
 *@exception None
 *
 *@param[in] IDChar
 *           A char which acts as an identifier of the heap (char)
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void HeapType<DataType>:: showHPStructure
       ( 
        char IDChar // in: a char corresponding to the identity of the heap
       )
{

    int height = getHeight();
    int level = height;
    int heapIndex = 0;
    int rowCounter, rowItem, index, leadSpaces, divSpaces;  

    cout << "Heap " << IDChar << " Data:" << endl;

    for( rowCounter = 0; rowCounter < height; rowCounter++ )
    {
        getSpacing( level, leadSpaces, divSpaces );
        displayChars( leadSpaces, SPACE );
        rowItem = ( toPower( BASE_TWO, rowCounter ) );    

        for( index = 0; ( index < rowItem && heapIndex < heapSize ); 
                                                                      index++ )
        {
            // condition: it's not the first item in the row of the tree
            if( index != 0 )
            {
                displayChars( divSpaces, SPACE );
            }
            displayInt( ( heapVector[heapIndex] ).toInt() );
            heapIndex++;
        }
        level--;
        cout << endl;
    }
    cout << endl;
}

/**
 *@brief Implementation of HeapType class method to return the size of the heap
 *
 *@details Returns the size of the heap
 *
 *@pre Assumes an initialized HeapType object
 *
 *@post The size of the heap is returned and the heap is unchanged
 *
 *@par Algorithm  
 *     The int heapSize is returned
 *
 *@exception None
 *
 *@param None 
 *
 *@return An int corresponding to the size of the heap (ine)
 *
 *@note None
 */
template <class DataType>
int HeapType<DataType>:: getSize
       (
        // no parameters
       ) const
{
    return heapSize;
}

/**
 *@brief Implementation of HeapType class method to check if the heap is empty
 *
 *@details Returns a bool corresponding to whether or not the heap is empty
 *
 *@pre Assumes an initialized HeapType object
 *
 *@post A bool is returned and the heap is unchanged
 *
 *@par Algorithm 
 *     An if statement checks whether or no the heap pointer is NULL or if the  
 *     size of the heap is zero, if so then true is returned, otherwise false
 *
 *@exception None
 *
 *@param None
 *
 *@return A bool corresponding to whether or not the heap is empty (bool)
 *
 *@note None
 */
template <class DataType>
bool HeapType<DataType>:: isEmpty
       (
        // no parameters
       ) const
{
    if( heapVector == NULL || heapSize == 0 )
    {
        return true;
    }

    return false;
}

/**
 *@brief Implementation of HeapType class method to add an item to the heap
 *
 *@details The item is added to the last place in the heap and then is
 *         recursively shifted up with a call to shiftUp if necessary
 *
 *@pre Assumes an initialized HeapType object holding items of a type that has
 *     an assignment operator
 *
 *@post The item is added to the heap and is shifted up if necessary, possibly
 *      changing the order of the heap
 *
 *@par Algorithm  
 *     A call to checkForResize increases the size of the heap if it's full,
 *     the item is added to the last position in the heap, shiftUp is called
 *     on that index to shift it up if necessary and the size of the heap is
 *     incremented
 *
 *@exception None
 *
 *@param[in] inData
 *           A reference parameter of type DataType which corresponds to the
 *           item to be added to the heap (DataType) 
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void HeapType<DataType>:: add
       ( 
        const DataType &inData  // in: the item to be added to the heap
       )
{
    checkForResize();
    heapVector[heapSize] = inData;
    shiftUp( heapSize );
    heapSize++;        
}

/**
 *@brief Implementation of HeapType class method to remove an item from the
 *       heap
 *
 *@details The top item of the heap is removed, then the last is placed on top
 *         and shifted down if necessary and a bool is returned corresponding
 *         to whether it was successful
 *
 *@pre Assumes an initialized HeapType object holding items of a type that has
 *     an assignment operator
 *
 *@post The largest item is removed from the top of the heap and then the 
 *      last item is placed on the top and shifted down with a call to 
 *      shiftDown if necessary
 *
 *@par Algorithm  
 *     An if statement checks that the heap is not empty and if not then the
 *     item at the top of the heap is assigned to the parameter removeData,
 *     the item at the last position in the heap is placed on the top, the size
 *     of the heap is decremented and then shiftDown is called to shift it down
 *     if necessary and true is returned if that was successful, otherwise 
 *     false is returned
 *
 *@exception None
 *
 *@param[out] removeData 
 *            A reference parameter of type DataType which accepts the item 
 *            removed if it's there (DataType)       
 *
 *@return A bool is returned corresponding to whether or not an item could be
 *        removed from the heap (bool)
 *
 *@note None
 */
template <class DataType>
bool HeapType<DataType>:: remove
       ( 
        DataType &removeData // out: an item to accept the value of the item 
                             //      removed from the heap
       )
{
    // condition: the heap is not empty
    if( !isEmpty() )
    {
        removeData = heapVector[0];
        heapVector[0] = heapVector[( heapSize - 1 )];
        heapSize--;
        shiftDown( 0 );

        return true;
    }

    return false;
}

/**
 *@brief Implementation of HeapType class method to set the size of the heap to
 *       zero
 *
 *@details The data member heapSize is set to zero
 *
 *@pre Assumes an initialized HeapType object
 *
 *@post The size of the heap is changed to zero and any items in the heap are
 *      lost
 *
 *@par Algorithm  
 *     The data member heapSize is set to zero
 *
 *@exception None
 *
 *@param None
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void HeapType<DataType>:: clear
       (
        // no parameters
       )
{
    heapSize = 0;
}

/**
 *@brief Implementation of HeapType class method to shift an item up in the 
 *       heap if necessary
 *
 *@details Recursively shifts the item at the specified index up the heap if it 
 *         is larger than its parent
 *
 *@pre Assumes an initialized HeapType object
 *
 *@post The item at the specified index is swapped with its parent if it's
 *      larger
 *
 *@par Algorithm  
 *     An if statement checks that currentIndex isn't at the top of the heap,
 *     if so then it's the base case, and if not it enters the recursive case
 *     which checks if the item at the index is greater than its parent and if 
 *     so a call to swap swaps them and then the method is called recursively
 *     on the parent of the currentIndex 
 *     
 *@exception None
 *
 *@param[in] currentIndex
 *           An int corresponding to the index of the item to be shifted up
 *           if necessary (int)
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void HeapType<DataType>:: shiftUp
       ( 
        int currentIndex // in: the index of the item to be shifted up
       )
{
    // condition: the currentIndex is not the top of the heap
    if( currentIndex != 0 )
    {
        // condition: the item at currentIndex is greater than its parent 
        if( ( heapVector[currentIndex] ).compareKey
                             ( heapVector[( ( currentIndex - 1 )/TWO )] ) > 0 )
        {
            swap( currentIndex, ( ( currentIndex - 1 )/TWO ) );
        }
        shiftUp( ( ( currentIndex - 1 )/TWO ) );
    }
}

/**
 *@brief Implementation of HeapType class method to shift an item down in the 
 *       heap if necessary
 *
 *@details Recursively shifts the item at the specified index down the heap if 
 *         it is smaller than either of its children
 *
 *@pre Assumes an initialized HeapType object
 *
 *@post The item at the specified index is swapped with the larger of its
 *      children if it's smaller
 *
 *@par Algorithm  
 *     An if statement checks that the left child of currentIndex is within the
 *     size of the vector, if not it's the base case, if so then another if
 *     checks that the right child is also within the size of the vector, if so
 *     then both right and left are compared to the parent, and then to each 
 *     other, if statements swap the item at currentIndex with either the left
 *     or right child depending on which is larger if the parent is smaller,
 *     and if the right child is not within the size of the vector then the
 *     parent is swapped with the left child if it's smaller, lastly the
 *     function is called recursively on the child it was swapped with in
 *     either case
 *
 *@exception None
 *
 *@param[in] currentIndex
 *           An int corresponding to the index of the item to be shifted down
 *           if necessary (int)
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void HeapType<DataType>:: shiftDown
       ( 
        int currentIndex // in: the index of the item to be shifted down
       )
{
    int left, right;

    // condition: the left child is within the size of the heap
    if( ( ( TWO * currentIndex ) + 1 ) < heapSize )
    { 
        // condition: the right child is also within the size of the heap
        if( ( ( TWO * currentIndex ) + TWO ) < heapSize )
        {
            left = ( heapVector[currentIndex] ).compareKey
                                ( heapVector[( ( TWO * currentIndex ) + 1 )] );
            right = ( heapVector[currentIndex] ).compareKey
                              ( heapVector[( ( TWO * currentIndex ) + TWO )] );

            // condition: the left child is greater than the right and the 
            //            parent
            if( left < right && left < 0 )   
            {
                swap( currentIndex, ( TWO * currentIndex ) + 1 );
                shiftDown( ( TWO * currentIndex ) + 1 );
            }    
            // condition: the right child is greater than or equal to the left 
            //            and greater than the parent
            else if( right <= left && right < 0 )
            {
                swap( currentIndex, ( ( TWO * currentIndex ) + TWO ) );
                shiftDown( ( TWO * currentIndex ) + TWO );
            }
        }
        else
        {
            // condition: if the left child is greater than the parent
            if( ( heapVector[currentIndex] ).compareKey
                           ( heapVector[( ( TWO * currentIndex ) + 1 )] ) < 0 )
            {
                swap( currentIndex, ( ( TWO * currentIndex ) + 1 ) );
                shiftDown( ( TWO * currentIndex ) + 1 );
            }
        
        }
    }
}

/**
 *@brief Implementation of HeapType class method to resize the heap if it
 *       becomes full
 *
 *@details The vector is dynamically resized to 1.25 the size if it becomes
 *         full
 *
 *@pre Assumes an initialized HeapType object holding items of a type that has
 *     an assignment operator
 *
 *@post The capacity of the heapVector is increased by 1.25 times 
 *
 *@par Algorithm  
 *     An if statement checks that heapVector is not NULL and that the heap
 *     is full and if those conditions are met then an array of type DataType
 *     is created with a new capacity 1.25 times larger and then a counter
 *     controlled loop copies the items from the old vector into the new and 
 *     then deletes the old vector and points heapVector to the new one  
 *
 *@exception None
 *
 *@param None 
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void HeapType<DataType>:: checkForResize
       (
        // no parameters
       )
{
    int index;
    int newSize = ( ( float ) heapCapacity * RESIZE );
    DataType* tempVector;

    // condition: the heapVector is not NULL and the vector is full
    if( heapVector != NULL && ( heapSize == heapCapacity ) )
    {
        tempVector = new DataType[newSize];

        for( index = 0; index < heapSize; index++ )
        {
            tempVector[index] = heapVector[index];
        }

        delete[] heapVector;
        heapVector = tempVector;
        tempVector = NULL;
        heapCapacity = newSize;
    }
}

/**
 *@brief Implementation of HeapType class method to copy one vector into
 *       another
 *
 *@details Takes in two vectors and copies one into the other 
 *
 *@pre Assumes an positive int for the capacity of the source vector
 *
 *@post The destination pointer points to a vector of the same size, holding
 *      the same values, as that of the source pointer and the heapVector
 *      data member points to destination
 *
 *@par Algorithm  
 *     An if statement checks whether destination points to a vector, if so its
 *     deleted, then memory is allocated to of size count, and then a counter
 *     controlled loop copies in the items from the source vector into the 
 *     destination vector and then the data member heapVector points to
 *     the destination vector
 *
 *@exception None 
 *
 *@param[in] destination
 *           A DataType pointer which points to the vector which will have the
 *           values of the other vector copied into it (DataType*) 
 *
 *@param[in] source
 *           A DataType pointer which points to the vector which will have its
 *           values copied into the other vector (DataType*)                 
 *
 *@param[in] count
 *           An int corresponding to the capacity of the source vector (int)
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void HeapType<DataType>:: copyHeapVector
       ( 
        DataType* destination, 
        const DataType* source, 
        int count 
       )
{
    int index;

    if( destination != NULL )
    {
        delete[] destination;
        destination = NULL;
    }

    if( count > 0 )
    {
        destination = new DataType[count];

        for( index = 0; index < count; index++ )
        {
            destination[index] = source[index];
        }
        heapVector = destination;
    }
}

/**
 *@brief Implementation of HeapType class method to swap two items in the heap
 *
 *@details Swaps two items in the heap at the indices indicated by the input
 *         parameters
 *
 *@pre Assumes an initialized HeapType object holding items of a type that has
 *     an assignment operator
 *
 *@post Two items in the heapVector at the specified indices are swapped
 *
 *@par Algorithm  
 *     An if statement checks that the heap contains items and if so then it 
 *     uses one a temporary position to swap the items at the specified
 *     indices
 *
 *@exception None
 *
 *@param[in] one
 *           An int corresponding to an item in the heap at the first index 
 *           (int)           
 *
 *@param[in] other
 *           An int corresponding to an item in the heap at the next index 
 *           (int)
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void HeapType<DataType>:: swap
       ( 
        int one, // in: the index of one item in the heap
        int other // in: the index of the other item in the heap
       )
{
    DataType temp;      

    // condition: heapVector is not NULL
    if( heapVector != NULL )
    {
        temp = heapVector[one];
        heapVector[one]  = heapVector[other];
        heapVector[other] = temp;
    }
}

/**
 *@brief Implementation of HeapType class method to determine the height of the
 *       tree representation of the heap
 *
 *@details Returns an int corresponding to the height of the tree form of the 
 *         heap based on indices
 *
 *@pre Assumes an initialized HeapType object with a size greater than zero
 *
 *@post Returns the height of the tree form of the heap and the heap is 
 *      unchanged
 *
 *@par Algorithm  
 *     An if statement checks that the heap is not empty and if it's not then
 *     an event controlled loop considers the final index in the heap and while
 *     an int, result, is not greater than the final index it's assigned the
 *     value of 2^(height) - 1 as height starts at zero and then is incremented
 *     and once result is greater than last index height is decremented and
 *     it's returned
 *
 *@exception None
 *
 *@param None
 *
 *@return An int corresponding to the height of the tree representation of the
 *        heap (int)
 *
 *@note None
 */
template <class DataType>
int HeapType<DataType>:: getHeight
       (
        // no parameters
       ) const
{
    int lastIndex = ( heapSize - 1 );
    int height = 0;
    int result = 0;

    // condition: heapVector points to an array
    if( !isEmpty() )
    {
        while( result <= lastIndex )    
        {
            result = ( toPower( BASE_TWO, height ) - 1 );
            height++;
        }

        height--;
    }

    return height;
}

/**
 *@brief Implementation of HeapType class method to calculate the proper 
 *       spacing for the showHPStructure
 *
 *@details The parameters hold values corresponding to the leading and diving
 *         spaces in the tree representation of the heap
 *
 *@pre Assumes that the parameter row is a positive int
 *
 *@post The parameters hold the values of the calculation and the heap is
 *      unchanged
 *
 *@par Algorithm  
 *     Both parameters are assigned the value of the calculations 2^(row) - 1
 *     for leading spaces and 2^(row + 1) - 3 for dividing spaces
 *
 *@exception None
 *
 *@param[out] firstSpaces
 *            An int corresponding to the number of leading spaces (int)  
 *
 *@param[out] dividerSpaces
 *            An int corresponding to the number of dividing spaces (int)
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void HeapType<DataType>:: getSpacing
       ( 
        int row, // in: the current row in the tree representation of the heap
        int &firstSpaces, // out: leading spaces
        int &dividerSpaces // out: dividing spaces
       ) const
{
    firstSpaces = ( toPower( BASE_TWO, row ) - 1 );
    dividerSpaces = ( toPower( BASE_TWO, ( row + 1 ) ) - THREE );
}

/**
 *@brief Implementation of HeapType class method to calculate the result of 
 *       raising a number to a power
 *
 *@details An int is returned corresponding to the result of taking one 
 *         parameter to the power of the other
 *
 *@pre Assumes an initialized HeapType object and positive int parameters
 *
 *@post The result of the calculation is returned and the heap is unchanged
 *
 *@par Algorithm  
 *     An if statement checks that the exponent is greater than zero and if
 *     so then a counter controlled loop multiplies the base by itself that 
 *     many times and returns the result, otherwise one is returned 
 *
 *@exception None
 *
 *@param[in] base
 *           An int corresponding to the base in the calculation (int) 
 *
 *@param[in] exponent
 *           An int corresponding to the exponent in the calculation (int) 
 *
 *@return An int corresponding to the result of the power calculation (int)
 *
 *@note None
 */
template <class DataType>
int HeapType<DataType>:: toPower
       ( 
        int base, // in: the base of the calculation
        int exponent // in: the exponent of the calculation
       ) const
{
    int index;    
    int result = 1;

    // condition: the exponent is greater than zero
    if( exponent > 0 )
    {
        for( index = 0; index < exponent; index++ )
        {
            result = result * base;
        }
    }
    else
    {
        result = 1;
    }

    return result;
}

/**
 *@brief Implementation of HeapType class method to printed out an item in the
 *       heap to the screen
 *
 *@details The value specified by the input parameter is formatted and printed
 *         to the screen
 *
 *@pre Assumes an initialized HeapType object that holds items of a type that
 *     can be compared to an int using the less than and greater than operators
 *
 *@post The value passed in as a parameter is printed to the screen and the
 *      heap is unchanged
 *
 *@par Algorithm  
 *     If statements check how many digits are in the parameter passed in to be
 *     printed to the screen, if one digit it's centered between spaces, if two
 *     digits then a leading zero is added, if three then it's simply printed
 *     to the screen
 *
 *@exception None
 *
 *@param[in] valueIndex
 *           An int corresponding to the value in the heap at which is to be
 *           printed to the screen (int)
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void HeapType<DataType>:: displayInt
       ( 
        int valueIndex // in: the value to be printed to the screen
       ) const
{
    DataType value;
    

    // condition: the value in the heap is a one digit int 
    if( valueIndex >= 0 && valueIndex < TWO_DIGIT )
    {
        cout << " " << valueIndex << " ";
    }
    // condition: the value in the heap is a two digit int 
    else if( valueIndex >= TWO_DIGIT && valueIndex < THREE_DIGIT )
    {
        cout << "0" << valueIndex;
    }  
    // condition: the value in the heap is a three digit int 
    else if( valueIndex >= THREE_DIGIT )
    {
        cout << valueIndex;
    }    
}

/**
 *@brief Implementation of HeapType class method to print a char to the screen
 *       in an amount specificied by an input parameter
 *
 *@details A char parameter is printed to the screen in the amount specified by
 *         a parameter
 *
 *@pre Assumes an initialized HeapType object
 *
 *@post A char is printed to the screen some number of times and the heap is
 *      unchanged
 *
 *@par Algorithm  
 *     A counter controlled loop prints to the screen the char input to the 
 *     method as a parameter 
 *
 *@exception None
 *
 *@param[in] numChars
 *           An int corresponding to the number of a particular char that is to
 *           be printed to the screen (int)
 *
 *@param[in] outChar
 *           A char that is to be printed to the screen (char)
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void HeapType<DataType>:: displayChars
       ( 
        int numChars, // in: the number of times the char is to be printed
        char outChar // in: the char to be printed to the screen
       ) const
{
    int counter;

    for( counter = 0; counter < numChars; counter++ )
    {
        cout << outChar;
    }
} 


// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef HEAPTYPE_CPP
