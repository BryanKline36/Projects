// Program Information ////////////////////////////////////////////////////////
/**
 * @file BSTClass.h
 *
 * @brief Definition file for BSTClass
 * 
 * @details Specifies all member methods of the BSTClass
 *
 * @version 1.10
 *          Michael Leverington (27 February 2016)
 *          Updated for use with new assignment
 * 
 *          1.00 
 *          Michael Leverington (30 August 2015)
 *          Original code
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef BST_CLASS_H
#define BST_CLASS_H

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

// Class constants ////////////////////////////////////////////////////////////

   // None

// Class definition ///////////////////////////////////////////////////////////

template <typename DataType>
class BSTNode
   {
    public:

       BSTNode( const DataType &nodeData, BSTNode *leftPtr, BSTNode *rightPtr );

       DataType dataItem;

       BSTNode<DataType> *left;
       BSTNode<DataType> *right;
   };

template <typename DataType>
class BSTClass
   {
    public:

       // constants
       static const char TAB = '\t';
       static const int MAX_DATA_LEN = 80;
       static const int INITIALIZE = 101;
       static const int AT_BOTTOM = 102;
       static const int GET_RESULT = 103;

       // constructor
       BSTClass();
       BSTClass( const BSTClass<DataType> &copied );

       // destructor
       ~BSTClass();

       // assignment operator
       const BSTClass &operator = (const BSTClass<DataType> &rhData );

       // modifiers
       void clear();
       void insert( const DataType &newData );
       bool find( DataType &searchDataItem ) const;
       bool remove( const DataType &dataItem );

       // accessors
       bool isEmpty() const;
       void preOrderTraversal() const; 
       void inOrderTraversal() const;  
       void postOrderTraversal() const;
 
    private:

       void copyTree( BSTNode<DataType> *&workingPtr, 
                                       const BSTNode<DataType> *sourcePtr );

       void clearHelper( BSTNode<DataType> *workingPtr );

       void insertHelper( BSTNode<DataType> *&workingPtr, 
                                                  const DataType &newData );

       bool findHelper( BSTNode<DataType> *workingPtr, 
                                     DataType &searchDataItem ) const;

       bool removeHelper( BSTNode<DataType> *&workingPtr, 
                                           const DataType &removeDataItem );

       void preOrderTraversalHelper( BSTNode<DataType> *workingPtr) const;

       void inOrderTraversalHelper( BSTNode<DataType> *workingPtr) const;

       void postOrderTraversalHelper( BSTNode<DataType> *workingPtr) const;

       BSTNode<DataType> *rootNode;    
   };

#endif	// define BST_CLASS_H



