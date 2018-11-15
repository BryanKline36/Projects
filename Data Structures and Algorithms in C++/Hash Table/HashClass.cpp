// Program Information ////////////////////////////////////////////////////////
/**
 * @file HashClass.cpp
 *
 * @brief Implementation file for HashClass class
 * 
 * @details Implements the constructor method of the HashClass class
 *
 * @version 1.20
 *          Bryan Kine (20 April 2016)
 *          Implementation of remaining methods
 *        
 *          1.10 
 *          Michael Leverington (06 April 2016)
 *          Updated with probing
 *
 *          1.00 
 *          Michael Leverington (06 November 2015)
 *          Original code
 *
 * @Note Requires HashClass.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef HASH_CLASS_CPP
#define HASH_CLASS_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "HashClass.h"

using namespace std;

// Global constants ///////////////////////////////////////////////////////////

const int TWO_POWER = 2;

// Class Implementation ///////////////////////////////////////////////////////

/**
 *@brief Implementation of DataNode struct default constructor 
 *
 *@details An initializer is used to set one of the struct data members to its 
 *         default value 
 *
 *@pre Assumes a DataNode struct
 *
 *@post The data member usedState is set to its default value
 *
 *@par Algorithm  
 *     An initializer is used to set the data member usedState to its default
 *     value
 *
 *@exception None
 *
 *@param None
 *
 *@return None
 *
 *@note Initializer used
 */
template<typename DataType>
DataNode<DataType>::DataNode
       (
        // no parameters
       )
    : usedState( UNUSED )
{
    // initializer used
}

/**
 *@brief Implementation of HashClass default constructor
 *
 *@details Initializers are used to set data members to default values
 *
 *@pre Assumes an uninitialized HashClass object
 *
 *@post Data members are set to default values and memory is allocated for the
 *      hash table
 *
 *@par Algorithm  
 *     Initializers are used to set data members to default values and allocate
 *     memory for the hash table
 *
 *@exception None
 *
 *@param None
 *
 *@return None
 *
 *@note Initializers used
 */
template<typename DataType>
HashClass<DataType>::HashClass
       (
        // no parameters
       )
    : tableLength( DEFAULT_HASH_TABLE_LENGTH ), 
      maxProbeAttempts( DEFAULT_PROBE_ATTEMPT_LIMIT ),
      hashLetterCount( DEFAULT_HASH_LETTER_COUNT ),
      hashList( new DataNode<DataType>[ DEFAULT_HASH_TABLE_LENGTH ] )
{
    // initializers used
}

/**
 *@brief Implementation of HashClass copy constructor
 *
 *@details Initializers are used to set data members to default values and 
 *         allocate memory for the hash table and then the values of one
 *         HashClass object are copied into the other
 *
 *@pre Assumes an uninitialized HashClass object
 *
 *@post The local object has the values of the HashClass object passed in as a
 *      parameter copied into it
 *
 *@par Algorithm  
 *     Initializers are used to set data members to default values and allocate
 *     memory for the hash table and the method copyList copies over the values
 *     from the HashClass object passed in as a parameter into the local object
 *
 *@exception None
 *
 *@param[in] copied
 *           A reference parameter of type HashClass corresponding to the 
 *           hash table to be copied into the local object 
 *           (HashClass<DataType>)
 *
 *@return None
 *
 *@note Initializers used
 */           
template<typename DataType>
HashClass<DataType>::HashClass
       ( 
        const HashClass<DataType> &copied // in: the HashClass object to be 
                                          //     copied
       )
    : tableLength( copied.tableLength ), 
      maxProbeAttempts( copied.maxProbeAttempts ),
      hashLetterCount( copied.hashLetterCount ),
      hashList( new DataNode<DataType>[ copied.tableLength ] )
{
    copyList( copied.hashList );
}

/**
 *@brief Implementation of HashClass destructor
 *
 *@details The memory allocated to the hash table is freed
 *
 *@pre Assumes an initialized HashClass object
 *
 *@post The memory allocated to the hash table is freed
 *
 *@par Algorithm  
 *     An if statement checks whether hashList is NULL and if it isn't then
 *     the memory allocated to it is freed and then it's set to NULL
 *
 *@exception None
 *
 *@param None
 *
 *
 *@return None
 *
 *@note None
 */
template<typename DataType>
HashClass<DataType>::~HashClass
       (
        // no parameters
       )
{
    // condition: the hash table is not NULL
    if( hashList != NULL)
    {
        delete [] hashList;
        hashList = NULL;
    }
}

/**
 *@brief Implementation of HashClass overloaded assignment operator
 *
 *@details The data members and hash table from one HashClass object are copied
 *         into another
 *
 *@pre Assumes an initialized HashClass object
 *
 *@post The data members and hash table from one HashClass object are copied
 *      into the other
 *
 *@par Algorithm  
 *     An if statement checks whether the local object is the same as the 
 *     parameter and if not then the method resizeList is called, data members
 *     are assigned the values of the HashClass object passed in as a 
 *     parameter, the method copyList is called to copy the hash table, and
 *     then the local object is returned
 *
 *
 *@exception None
 *
 *@param[in] rhHashTable
 *           A reference parameter of type HashClass which corresponds to the
 *           HashClass object to be copied into the local object (HashClass)
 *
 *@return None
 *
 *@note None
 */
template <typename DataType>
const HashClass<DataType>& HashClass<DataType>:: operator = 
       ( 
        const HashClass &rhHashTable // in: the HashClass object to be copied
       )
{
    int dummyMaxProbes, dummyTotalProbes;

    // condition: the parameter is different than the local object
    if( this != &rhHashTable )
    {
        resizeList( rhHashTable.tableLength, CLEAR_LIST, 
                                            dummyMaxProbes, dummyTotalProbes );

        maxProbeAttempts = rhHashTable.maxProbeAttempts;

        hashLetterCount = rhHashTable.hashLetterCount;

        copyList( rhHashTable.hashList );
    }

    return *this;
}

/**
 *@brief Implementation of HashClass method to resize the hash table
 *
 *@details The result of a call to resizeList is returned
 *
 *@pre Assumes an initialized HashClass object
 *
 *@post The hash table is resized
 *
 *@par Algorithm  
 *     The parameters are passed into the method resizeList and its result
 *     is returned
 *
 *@exception None
 *
 *@param[in] newTableLength
 *           An int corresponding to the new length of the hash table (int)
 *           
 *
 *@param[in] clearListFlag
 *           A bool corresponding to whether or not the table will be cleared
 *           (bool)   
 *
 *@param[in] maxProbes
 *           An int corresponding to the maximum number of probes (int)    
 *
 *@param[in] totalProbes
 *           An int corresponding to the number of times probed (int)
 *
 *@return A bool is returned corresponding to whether or not the resize of the
 *        table was successful (bool)
 *
 *@note None
 */
template <typename DataType>
bool HashClass<DataType>::setTableLength
       ( 
        int newTableLength, // in: the new table length
        bool clearListFlag, // in: a bool to clear the table
        int &maxProbes, // in: the max probes
        int &totalProbes // in: the total probes used
       )
{
    return resizeList( newTableLength, clearListFlag, maxProbes, totalProbes );
}

/**
 *@brief Implementation of HashClass method to set the data member 
 *       hashLetterCount
 *
 *@details Assigns the data member hashLetterCount to the value parameter
 *
 *@pre Assumes an initialized HashClass object
 *
 *@post The data member hashLetterCount is reset
 *
 *@par Algorithm  
 *     The data member hashLetterCount assigned the value of the parameter 
 *     passed in
 *
 *@exception None
 *
 *@param[in] newHashLetterCount
 *           An int corresponding to the new value of the data member 
 *           hashLetterCount (int)
 *
 *@return None
 *
 *@note None
 */
template <typename DataType>
void HashClass<DataType>::setHashLetterCount
       ( 
        int newHashLetterCount // in: the new value for hashLetterCount
       )
{
    hashLetterCount = newHashLetterCount;
}

/**
 *@brief Implementation of HashClass method to set the data member 
 *       maxProbeAttempts
 *
 *@details Assigns the data member maxProbeAttempts to the value parameter
 *
 *@pre Assumes an initialized HashClass object
 *
 *@post The data member maxProbeAttempts is reset
 *
 *@par Algorithm  
 *     The data member maxProbeAttempts assigned the value of the parameter 
 *     passed in
 *
 *@exception None
 *
 *@param[in] maxProbeAttempts
 *           An int corresponding to the new value of the data member 
 *           maxProbeAttempts (int)
 *
 *@return None
 *
 *@note None
 */
template <typename DataType>
void HashClass<DataType>::setProbeAttempts
       ( 
        int newNumProbeAttempts // in: the new value for maxProbeAttempts
       )
{
    maxProbeAttempts = newNumProbeAttempts;
}

/**
 *@brief Implementation of HashClass to add and item to the table
 *
 *@details Calls addItemHelper to add an item to the list and then returns a
 *         corresponding to whether or not the item was used
 *
 *@pre Assumes an initialized HashClass object
 *
 *@post The item is added to the hash table if, after quadratic probing if
 *      necessary, it finds an available place in the table
 *
 *@par Algorithm  
 *     The method addItemHelper is called and the result is stored in 
 *     probeAttempts, if the value in probeAttempts is less than the max            
 *     maximum possible attempts then true is returned, otherwise false is
 *     returned
 *
 *@exception None
 *
 *@param[in] newData
 *           A reference parameter of type DataType which corresponds to the
 *           item to be added to the table (DataType)
 *
 *@param[in] probeAttempts
 *           An int corresponding to the number of times the table has been
 *           probed (int)
 *
 *@return A bool is returned corresponding to whether or not the item was added
 *        to the table
 *
 *@note None
 */
template <typename DataType>
bool HashClass<DataType>::addItem
       ( 
        const DataType &newData, // in: the item to be added to the table
        int &probeAttempts // in: the times the table has been probed
       )
{
    probeAttempts = addItemHelper( hashList, newData );
    
    // condition: the probes attempted is less than the maximum 
    if( probeAttempts < maxProbeAttempts )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *@brief Implementation of HashClass method to find and item in the table
 *
 *@details Returns the index of the table if the item is found, otherwise
 *         -1 is returned 
 *
 *@pre Assumes an initialized HashClass object
 *
 *@post The index of the item is returned if it's in the table and it's 
 *      unchanged
 *
 *@par Algorithm  
 *     An event controlled loop, while the number of rehash attempts is below 
 *     the maximum, goes through the table checking first the initial hash
 *     index and then the quadratically probed index after that if not found,
 *     an if statement returning the index if it's found at any point, 
 *     otherwise -1 is returned
 *
 *@exception None
 *
 *@param[in] dataItem
 *           A reference parameter of type DataType corresponding to the item
 *           to be searched for in the table (DataType)
 *
 *@param[in] probeAttempts
 *           An int corresponding to the number of probe attempts, needed for
 *           the hash method
 *
 *@return An int corresponding to the index at which an item was found in 
 *        the table (int)
 *
 *@note None
 */
template <typename DataType>
int HashClass<DataType>::findItem
       ( 
        const DataType &dataItem, // in: the item to be searched for
        int &probeAttempts // in: the number of probe attempts
       ) const
{
    DataType temp = dataItem;
    int counter = 0;    
    int probeCounter = probeAttempts;
    int hashValue = temp.hash( DEFAULT_HASH_LETTER_COUNT, tableLength );
    int index = hashValue;    

    while( probeCounter < DEFAULT_PROBE_ATTEMPT_LIMIT )
    {
        // condition: the item has been found in the table
        if( ( hashList[index] ).nodeData.compareTo( dataItem ) == 0 
                                     && ( hashList[index] ).usedState == USED )
        {
            return index;
        }

        index = ( hashValue + ( toPower( ( counter + 1 ), TWO_POWER ) ) 
                                                               % tableLength );
        counter++;
        probeCounter--;
    }

    return FAILED_PROBE_PROCESS;
}

/**
 *@brief Implementation of HashClass method to remove an item from the hash
 *       table
 *
 *@details The method findItem is called and if it's found then it is removed
 *         from the table
 *
 *@pre Assumes an initialized HashClass object
 *
 *@post If the item to be removed is in the table it is removed
 *
 *@par Algorithm  
 *     The method findItem is called and the result is stored in index, if
 *     that value is -1 then false is retuned as it's not in the list, 
 *     otherwise the struct node at that index is set to UNUSED and true is
 *     returned
 *
 *@exception None
 *
 *@param[in] dataItem
 *           A reference parameter of type DataType which corresponds to the 
 *           item to be removed from the table (DataType)
 *
 *@param[in] probeAttempts
 *           An int which corresponds to the number of times the item will
 *           be rehashed by the findItem method (int)
 *
 *@return A bool is returned corresponding to whether or not the item was 
 *        successfully removed from the hash table (bool)
 *
 *@note None
 */
template <typename DataType>
bool HashClass<DataType>::removeItem
       ( 
        const DataType &dataItem, // in: the item to be removed from the table
        int &probeAttempts // in: the number of times the method will rehash
       )
{   
    int index = findItem( dataItem, probeAttempts );
    
    // condition: the item is not in the table
    if( index == FAILED_PROBE_PROCESS )
    {
        return false;
    }
    else
    {
        ( hashList[index] ).usedState = UNUSED;
        probeAttempts = 0;    
    
        return true;
    }
}

/**
 *@brief Implementation of HashClass method to determine whether the hash table
 *       is empty
 *
 *@details Returns a bool based on whether or not the hash table is empty
 *
 *@pre Assumes an initialized HashClass object
 *
 *@post A bool is returned based on whether or not the table is empty and it's
 *      unchanged
 *
 *@par Algorithm  
 *     An if statement checks whether or not the pointer to the table is NULL, 
 *     if not then a counter controlled loop moves through the table and if
 *     at any point there is a node with its data member usedState set to 
 *     USED then false is returned, if not then true is returned
 *
 *@exception None
 *
 *@param None
 *
 *@return A bool is returned corresponding to whether or not the hash table is
 *        empty (bool)
 *
 *@note None
 */
template<typename DataType>
bool HashClass<DataType>::isEmpty
       ( 
        // no parameters
       ) const
{
    int index;

    // condition: the pointer to the table is not NULL
    if( hashList != NULL )
    {
        for( index = 0; index < tableLength; index++ )
        {
            // condition: there is an item in the table
            if( hashList[index].usedState == USED )
            {
                return false;
            }
        }
    }

    return true;
}

/**
 *@brief Implementation of HashClass method to clear the hash table
 *
 *@details All the nodes in the table have their usedState set to UNUSED
 *
 *@pre Assumes an initialized HashClass object
 *
 *@post All the items in the table are set to UNUSED thereby clearing the table
 *
 *@par Algorithm  
 *     An if statement checks whether or not the pointer to the table is NULL, 
 *     if not then a counter controlled loop moves through the table and sets
 *     all the nodes' usedState data members to UNUSED
 *
 *@exception None
 *
 *@param None
 *
 *@return None
 *
 *@note None
 */
template<typename DataType>
void HashClass<DataType>::clearList
       (  
        // no parameters     
       )
{
    int index;

    // condition: the pointer to the table is not NULL
    if( hashList != NULL )
    {
        for( index = 0; index < tableLength; index++ )
        {
            hashList[index].usedState = UNUSED;
        }
    }
}

/**
 *@brief Implementation of HashClass method to print out the hash table to 
 *       screen
 *
 *@details The items in the hash table are printed to the screen, UNUSED is
 *         displayed if there is no item at a position in the table
 *
 *@pre Assumes an initialized HashClass object and that the items in the 
 *     table have a toString method
 *
 *@post The hash table is printed to the screen and is unchanged
 *
 *@par Algorithm  
 *     A counter controlled loop moves through the table and if the node at
 *     a given index has its data member usedState set to USED then it's 
 *     printed to the screen with call to toString, otherwise UNUSED is 
 *     printed to the screen 
 *
 *@exception None
 *
 *@param None
 *
 *@return None
 *
 *@note None
 */
template<typename DataType>
void HashClass<DataType>::showStructure
       (
        // no parameters
       ) const
{
    int index;
    char buffer[LARGE_STR_LEN];

    for( index = 0; index < tableLength; index++ )
    {
        // condition: there is an item in the table at the current index
        if( ( hashList[index] ).usedState == USED )
        {
            cout << "Index " << index << ": ";
            ( ( hashList[index] ).nodeData ).toString( buffer ); 
            cout << buffer << endl;
        }
        else
        {
            cout << "Index " << index << ": UNUSED" << endl;
        }
    }
    cout << "- End of List -" << endl;

}

/**
 *@brief Implementation of HashClass method to calculate the hash value of an
 *       item to be added to the table 
 *
 *@details The method of one of the parameters is called to get the hash value
 *         of the item to be added to the table
 *
 *@pre Assumes an initialized HashClass object and that the parameter dataItem
 *     has a hashing method
 *
 *@post The hash value of the item to be added to the table is returned and 
 *      the hash table is unchanged
 *
 *@par Algorithm  
 *     The hashing method for the parameter dataItem is called with a default
 *     number of letters to be considered for the calculation the length of the 
 *     table passed in as parameters
 *
 *@exception None
 *
 *@param[in] dataItem
 *           A reference parameter of type DataType which corresponds to the
 *           item to be hashed and added to the table (DataType)
 *
 *@param[in] workingTableLength
 *           A int corresponding to the length of the hash table for the hash
 *           calculation (int)
 *
 *@return An int corresponding to the value returned from the call to the 
 *        parameter dataItem's hashing method (int)
 *
 *@note None
 */
template<typename DataType>
int HashClass<DataType>::hash
       (
        const DataType &dataItem, // in: item to be hashed
        int workingTableLength // in: the length of the table
       ) const
{
    DataType temp = dataItem;

    return temp.hash( hashLetterCount, workingTableLength );
}

/**
 *@brief Implementation of HashClass method to assist in adding an item to the
 *       table
 *
 *@details Called by addItem to assist in adding an item to the hash table and
 *         the number of probes is returned
 *
 *@pre Assumes an initialized HashClass object
 *
 *@post An item is added to the table if there is an available place for it
 *      after the maximum number of probe attempts
 *
 *@par Algorithm  
 *     The method has is called and assigned to hashValue, then a counter 
 *     controlled loop attempts to place the item at the index corresponding
 *     to hashValue, checking its usedState data member with an if statement,
 *     placing it there if possible and if not calculating the next index
 *     with call to toPower, in either case the number of probe attempts is
 *     returned
 *
 *@exception None
 *
 *@param[in] destHashHelper
 *           A pointer of type DataNode which points to the hash table
 *           (DataNode<DataType>)
 *
 *@param[in] newData
 *           A reference parameter of type DataType which corresponds to the 
 *           item to be added to the table (DataType)
 *
 *@return An int is returned corresponding to the number of probe attempts 
 *        (int)
 *
 *@note None
 */
template <typename DataType>
int HashClass<DataType>::addItemHelper
       ( 
        DataNode<DataType> *destHashTable, // in: the hash table
        const DataType &newData // in: the item to be added to the table
       )
{
    int hashValue = hash( newData, tableLength );
    int index = hashValue;
    int probeNumber;
    
    for( probeNumber = 0; probeNumber < maxProbeAttempts; probeNumber++ )
    {
        // condition: the current place in the table is not available
        if( destHashTable[index].usedState == USED )
        {
            index = ( ( hashValue + toPower( ( probeNumber + 1 ), TWO_POWER ) ) 
                                                               % tableLength );
        }
        else
        {
            ( destHashTable[index] ).nodeData = newData;        
            ( destHashTable[index] ).usedState = USED;
            return probeNumber;
        }
    }

    return probeNumber;
}

/**
 *@brief Implementation of HashClass method to resize the hash table
 *
 *@details Either clears the table and resizes it to any size or the items
 *         in the table remain but the size can only be increased
 *
 *@pre Assumes an initialized HashClass object
 *
 *@post Either clears the list and resizes it or simply resizes it if the new
 *      size is greater than the current size
 *
 *@par Algorithm  
 *     An if statement checks whether or not clearFlag is set, if so then 
 *     the table is deleted, a table with the new size is created and true is
 *     returned, otherwise an if statement checks if the new size is greater
 *     than the current, if not then false is returned otherwise a new table
 *     is created with the old size, the table is copied into it with a counter 
 *     conrolled loop, the old table is deleted then a new one is created with 
 *     the new size and then a counter controlled loop calls addItem on each
 *     one to place them into the new table if it's not used and true is 
 *     returned
 *
 *@exception None
 *
 *@param[in] newSize
 *           An int corresponding to the new size of the table (int)
 *
 *@param[in] clearFlag
 *           A bool corresponding to whether or not the list will be cleared
 *           (bool)   
 *
 *@param[in] maxProbes
 *           A reference parameter of type int corresponding to the maximum
 *           number of times the table can be probed (int)
 *
 *@param[in] totaProbes
 *           A reference parameter of type int corresponding to the number
 *           of probe attempts (int)   
 *
 *@return None
 *
 *@note None
 */
template<typename DataType>
bool HashClass<DataType>::resizeList
       (       
        int newSize, // in: the new size of the table
        bool clearFlag, // in: a bool to clear the table
        int &maxProbes, // in: the maximum number of allowed probes
        int &totaProbes // in: the amount of times the table has been probed
       )
{
    int index;
    int probeCount = 0;
    bool success;
    DataNode<DataType>* temp;

    // condition: the table is to be cleared
    if( clearFlag )
    {
        delete[] hashList;
        hashList = new DataNode<DataType>[newSize];
        tableLength = newSize;

        return true;
    }
    else
    {
        // condition: if the new table size is greater than the current size
        if( newSize > tableLength )
        {
            temp = new DataNode<DataType>[tableLength];
            
            for( index = 0; index < tableLength; index++ )
            {
                ( temp[index] ).nodeData = ( hashList[index] ).nodeData;
                ( temp[index] ).usedState = ( hashList[index] ).usedState;
            }

            delete[] hashList;
            hashList = new DataNode<DataType>[newSize];
            tableLength = newSize;           

            for( index = 0; index < tableLength; index++ )
            {
                // condition: there is an item in the temporary table
                if( ( temp[index] ).usedState == USED )
                {
                    success = addItem( ( temp[index] ).nodeData, totaProbes );
                    probeCount = ( probeCount + totaProbes );

                    // condition: adding to the table failed
                    if( !success )
                    {
                        return false;
                    }
                }
            }
            
            totaProbes = probeCount;            

            return true;
        } 
        else
        {
            return false;
        }
    }
}

/**
 *@brief Implementation of HashClass class method to copy a hash table into the
 *       local object
 *
 *@details The contents of one hash table are copied into the other
 *
 *@pre Assumes an initialized HashClass object, both tables are of the same
 *     size, and that the DataType that the node holds has an overloaded
 *     assignment operator
 *
 *@post The hash table holds the same nodes as those of the parameter passed in
 *
 *@par Algorithm  
 *     A counter controlled loop moves through both hash lists and copies the
 *     nodes from one to the other by accessing the struct node data members
 *     directly
 *
 *@exception None
 *
 *@param[in] copiedList
 *           A pointer to a DataNode object which points to the hash table to 
 *           be copied to the local object (DataNode<DataType>*) 
 *
 *@return None
 *
 *@note None
 */
template<typename DataType>
void HashClass<DataType>::copyList 
       ( 
        const DataNode<DataType> *copiedList // in: the hash table to be copied
       )
{
    int index;

    for( index = 0; index < tableLength; index++ )
    {
        hashList[index].usedState = copiedList[index].usedState;
        hashList[index].nodeData = copiedList[index].nodeData;
    }
}

/**
 *@brief Implementation of HashClass class method to calculate the result of 
 *       raising a number to a power
 *
 *@details An int is returned corresponding to the result of taking one 
 *         parameter to the power of the other
 *
 *@pre Assumes an initialized HashClass object and positive int parameters
 *
 *@post The result of the calculation is returned and the hash table is 
 *      unchanged
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
template<typename DataType>
int HashClass<DataType>::toPower
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

// Terminating precompiler directives  ////////////////////////////////////////

#endif	// define HASH_CLASS_CPP

