// Program Information ////////////////////////////////////////////////////////
/**
 * @file BSTClass.cpp
 *
 * @brief Implementation file for BSTClass
 *
 * @author Bryan Kline
 * 
 * @details Implements all member methods of the BSTNode and BSTClass classes 
 *
 * @version 1.00 
 *          Bryan Kline (03/10/2016)
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef BST_CLASS_CPP
#define BST_CLASS_CPP

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include "BSTClass.h"

using namespace std;

// BSTNode class implementation ///////////////////////////////////////////////

/**
 *@brief Implementation of BSTNode class parameterized constructor
 *
 *@details Initializers used to assign data members to the parameters passed in
 *
 *@pre Assumes an uninitialized BSTNode object
 *
 *@post An initialized BSTNode object 
 *
 *@par Algorithm  
 *     Intializers used to set data members to the values passed in as 
 *     parameters
 *
 *@exception None
 *
 *@param[in] nodeData
 *           A const reference parameter of type DataType which the node will
 *           hold (DataType)
 *
 *@param[in] leftPtr
 *           A pointer of type BSTNode to the left child node (BSTNode*)
 *
 *@param[in] rightPtr
 *           A pointer of type BSTNode to the right child node (BSTNode*)
 *
 *@return None
 *
 *@note Initializers used
 */
template <class DataType>
BSTNode<DataType>:: BSTNode
       ( 
        const DataType &nodeData, // in: the value the node will hold
        BSTNode *leftPtr, // in: pointer to the left child node
        BSTNode *rightPtr // in: pointer to the right child node
       )
    : dataItem ( nodeData ),
      left ( leftPtr ),
      right ( rightPtr )  
{
    // initializers used
}

// BSTClass class implementation //////////////////////////////////////////////

/**
 *@brief Implementation of BSTClass class default constructor
 *
 *@details The data member has a default value assigned to it
 *
 *@pre Assumes an uninitialized BSTClass object
 *
 *@post The data member has a default value
 *
 *@par Algorithm  
 *     An initializer is used to set the root to NULL
 *
 *@exception None
 *
 *@param None
 *
 *@return None
 *
 *@note Intializer used
 */
template <class DataType>
BSTClass<DataType>:: BSTClass
       (
        // no parameters
       )
    : rootNode ( NULL )
{
    // intializer used
}

/**
 *@brief Implementation of BSTClass class copy constructor
 *
 *@details Creates a tree with the same structure as the object passed in as
 *         parameter
 *
 *@pre Assumes an uninitialized BSTClass object
 *
 *@post The local object has the same structure as the parameter passed in
 *
 *@par Algorithm  
 *     An initializer is used to set the root to NULL and then the method 
 *     copyTree is called to copy the structure of the parameter into the
 *     into the local object  
 *
 *@exception None
 *
 *@param[in] copied
 *           A const reference parameter of type BSTClass which will have its
 *           values copied into the local object (BSTClass<DataType>)  
 *
 *@return None
 *
 *@note Intializers used
 */
template <class DataType>
BSTClass<DataType>:: BSTClass
       ( 
        const BSTClass<DataType> &copied // in: the object to be copied
       )
    : rootNode ( NULL )
{
    copyTree( rootNode, copied.rootNode );
}

/**
 *@brief Implementation of BSTClass class destructor
 *
 *@details Deletes all nodes in the tree and sets the data member to its 
 *         default value
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post All nodes in the tree deleted and the data member set to NULL
 *
 *@par Algorithm  
 *     The method clear is called to delete all nodes and set the root to NULL
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
BSTClass<DataType>:: ~BSTClass
       (
        // no parameters
       )
{
    clear();
}

/**
 *@brief Implementation of BSTClass class overloaded assignment operator
 *
 *@details Assigns one BSTClass object to the local object
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post The local object has the same structure as the parameter passed in
 *
 *@par Algorithm  
 *     An if statement checks whether the local object and the parameter 
 *     passed in are the same, if not then the method copyTree copies
 *     the structure and values of the parameter into the local object
 *
 *@exception None
 *
 *@param[in] rhData
 *           A const reference parameter of type BSTClass which will be the
 *           object which has its structure and values copied into the local
 *           object (BSTClass<DataType>)
 *
 *@return The local object is returned with this deferenced 
 *        (BSTClass<DataType>)
 *
 *@note None
 */
template <class DataType>
const BSTClass<DataType>& BSTClass<DataType>:: operator = 
       (
        const BSTClass<DataType> &rhData  // in: the object to be copied
       )
{
    // condition: the parameter and the local object are not the same
    if( this != &rhData )
    {
        clear();
        copyTree( rootNode, rhData.rootNode );
    }

    return *this;
}

/**
 *@brief Implementation of BSTClass class method to clear the tree
 *
 *@details Deletes all nodes in the tree and sets the root to NULL
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post All nodes in the tree deleted and the data member set to NULL
 *
 *@par Algorithm  
 *     An if statement checks that the tree is not empty and if its not then
 *     the method clearHelper is called to delete all nodes and the root is set
 *     to NULL
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
void BSTClass<DataType>:: clear
       (
        // no parameters
       )
{
    // condition: there are nodes in the tree
    if( !isEmpty() )
    {
        clearHelper( rootNode );
        rootNode = NULL;
    }
}

/**
 *@brief Implementation of BSTClass class method to insert an item into the 
 *       tree
 *
 *@details Inserts an item into the appropriate location in the tree with a
 *         call to a recursive helper method
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post The tree has the item inserted into the appropriate location
 *
 *@par Algorithm  
 *     An if statement checks whether the tree is empty, if so then a new node
 *     is created at the root, otherwise the recursive helper method is called   
 *     
 *
 *@exception None
 *
 *@param[in] newData
 *           A reference parameter of type DataType corresponding to the item
 *           to be inserted (DataType)
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void BSTClass<DataType>:: insert
       ( 
        const DataType &newData // in: the item to be inserted
       )
{
    // condition: the tree is empty
    if( isEmpty() )
    {
        rootNode = new BSTNode<DataType>( newData, NULL, NULL );
    }
    else
    {
        insertHelper( rootNode, newData );
    }
}

/** 
 *@brief Implementation of BSTClass class to search for an item in the tree
 *
 *@details The item passed in as a parameter is searched for in the tree
 *         and true is returned if it is found
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post A bool corresponding to whether or not the item is found is returned
 *      and the tree is unchanged
 *
 *@par Algorithm  
 *     An if statement checks whether the tree is empty and if not then the
 *     method findHelper is called to recursively search for the item
 *
 *@exception None
 *
 *@param[in] searchDataItem
 *           A reference parameter of type DataType which corresponds to the
 *           item searched for in the tree (DataType)
 *
 *@return A bool corresponding to whether or not the item was found in the
 *        tree (bool)
 *
 *@note None
 */
template <class DataType>
bool BSTClass<DataType>:: find
       ( 
        DataType &searchDataItem // in: the item searched for in the tree
       ) const
{
    bool found = false;

    // condition: there are nodes in the tree
    if( !isEmpty() )
    {
        found = findHelper( rootNode, searchDataItem );        
    }

    return found;
}

/**
 *@brief Implementation of BSTClass class that removes a node in the tree
 *
 *@details If the item passed in as a parameter is found the in tree then it
 *         is removed
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post If the item to be removed is in the tree it is removed and the
 *      parameter holds the value of the item removed
 *
 *@par Algorithm  
 *     An if statement checks that the tree is not empty and then calls the
 *     method removeHelper with the root and the parameter as arguments
 *
 *@exception None
 *
 *@param[out] dataItem
 *            A const reference parameter of type DataType corresponding to the
 *            item to be removed from the tree (DataType)
 *
 *@return A bool is returned corresponding to whether or not the removal was
 *        successful (bool)
 *
 *@note None
 */
template <class DataType>
bool BSTClass<DataType>:: remove
       ( 
        const DataType &dataItem // out: the item to be removed
       )
{
    bool removed = false;

    // condition: the tree contains nodes
    if( !isEmpty() )
    {
        removed = removeHelper( rootNode, dataItem );        
    }

    return removed;
}

/**
 *@brief Implementation of BSTClass class method that determines whether or not
 *       the tree is empty
 *
 *@details If there are no nodes in the tree then true is returned
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post A bool is returned based on whether or not the tree is empty
 *
 *@par Algorithm  
 *     An if statement checks whether the root is NULL and if so true is
 *     returned
 *
 *@exception None
 *
 *@param None
 *
 *@return A bool corresponding to whether or not the tree is empty (bool)
 *
 *@note None
 */
template <class DataType>
bool BSTClass<DataType>:: isEmpty
       (
        // no parameters
       ) const
{
    // condition: there are no nodes
    if( rootNode ==  NULL )
    {
        return true;
    }
    
    return false;
}

/**
 *@brief Implementation of BSTClass class to print the values in the tree to
 *       the screen
 *
 *@details The tree is traversed in pre-order and the values in the nodes are
 *         printed to the screen
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post The values in the tree are printed and the tree is unchanged
 *
 *@par Algorithm  
 *     An if statement checks whether or not the tree is empty and if not then
 *     the method preOrderTraversalHelper is called with the root as a 
 *     parameter
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
void BSTClass<DataType>:: preOrderTraversal
       (
        // no parameters
       ) const
{
    // condition: the tree contains nodes
    if( !isEmpty() )
    {
        preOrderTraversalHelper( rootNode );
        cout << endl;
    }
    else
    {
        cout << "Tree is empty" << endl;
    }
}

/**
 *@brief Implementation of BSTClass class to print the values in the tree to
 *       the screen
 *
 *@details The tree is traversed in order and the values in the nodes are
 *         printed to the screen
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post The values in the tree are printed and the tree is unchanged
 *
 *@par Algorithm  
 *     An if statement checks whether or not the tree is empty and if not then
 *     the method inOrderTraversalHelper is called with the root as a 
 *     parameter
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
void BSTClass<DataType>:: inOrderTraversal
       (
        // no parameters
       ) const 
{
    // condition: the tree contains nodes
    if( !isEmpty() )
    {
        inOrderTraversalHelper( rootNode );
        cout << endl;
    }
    else
    {
        cout << "Tree is empty" << endl;
    }
}

/**
 *@brief Implementation of BSTClass class to print the values in the tree to
 *       the screen
 *
 *@details The tree is traversed in post-order and the values in the nodes are
 *         printed to the screen
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post The values in the tree are printed and the tree is unchanged
 *
 *@par Algorithm  
 *     An if statement checks whether or not the tree is empty and if not then
 *     the method postOrderTraversalHelper is called with the root as a 
 *     parameter
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
void BSTClass<DataType>:: postOrderTraversal
       (
        // no parameters
       ) const
{
    // condition: the tree contains nodes
    if( !isEmpty() )
    {
        postOrderTraversalHelper( rootNode );
        cout << endl;
    }
    else
    {
        cout << "Tree is empty" << endl;
    }
}

/**
 *@brief Implementation of BSTClass class method that copies the structure
 *       and values from one tree into another
 *
 *@details Recursive calls to the method copy the structure and values from
 *         the tree passed in as a parameter into the local object
 *
 *@pre Assumes an initialized BSTClass object with no nodes
 *
 *@post The local object has the same structure as the parameter passed in
 *
 *@par Algorithm  
 *     An if statement checks whether the pointer pointing to the parameter is
 *     NULL and if not then then pointer to the local object has a node created
 *     for it and then the method is called recursively on the left and right
 *     pointers of the tree passed in as a parameter
 *
 *@exception None
 *
 *@param[in] workingPtr
 *           A reference BSTNode pointer which points to the current node under 
 *           consideration in the local tree (BSTNode<DataType>*)  
 *
 *@param[in] sourcePtr
 *           A BSTNode pointer which points to the current node under 
 *           consideration in the tree passed in as a parameter  
 *           (BSTNode<DataType>*)   
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void BSTClass<DataType>:: copyTree
       ( 
        BSTNode<DataType> *&workingPtr, // in: pointer to the current node of
                                        //     the local tree
        const BSTNode<DataType> *sourcePtr // in: pointer to the current node
                                           //     of the tree passed in as a 
                                           //     parameter
       )
{
    // condition: the tree passed in as a parameter is not a leaf node 
    if( sourcePtr != NULL )
    {
        workingPtr = new BSTNode<DataType>( sourcePtr->dataItem, NULL, NULL );
        copyTree( workingPtr->left, sourcePtr->left );
        copyTree( workingPtr->right, sourcePtr->right );
    }
}

/**
 *@brief Implementation of BSTClass class method to clear the tree
 *
 *@details Deletes the nodes in the tree recursively
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post All nodes in the tree are deleted
 *
 *@par Algorithm  
 *     An if statement checks whether the left pointer is NULL, if not then
 *     the method is called recursively on the left, then another if statement
 *     checks if the right is NULL, and if not the method is called recursively
 *     on the right, and the node is deleted
 *
 *@exception None
 *
 *@param[in] workingPtr
 *           A pointer of type DataType corresponding to the current node
 *           under consideration (BSTNode<DataType>*)
 *
 *@return None
 *
 *@note None
 */
template <class DataType>
void BSTClass<DataType>:: clearHelper
       ( 
        BSTNode<DataType> *workingPtr 
       )
{
    // condition: the left pointer is not NULL
    if( workingPtr->left != NULL )
    {
        clearHelper( workingPtr->left );
    }
    // condition: the left pointer is not NULL
    if( workingPtr->right != NULL )
    {
        clearHelper( workingPtr->right );
    }
    delete workingPtr;
}

/**
 *@brief Implementation of BSTClass class method to insert a new item into the
 *       tree
 *
 *@details The item to be inserted is added to tree with recursive calls to the
 *         method
 *
 *@pre Assumes an initialized BSTClass object and that the item to be inserted
 *     has a compareTo method
 *
 *@post The tree has the item inserted into the appropriate location
 *
 *@par Algorithm  
 *     An if statement checks whether the current node pointer is NULL, if not
 *     then if statements check whether the item to be inserted is greater or
 *     less than the item at the current node, going right or left in either   
 *     respective case, and then if that node is a leaf then a new node is
 *     created, otherwise the method is called on the child node
 *
 *@exception None
 *
 *@param[in] workingPtr
 *           A pointer of type BSTNode pointer which corresponds to the current
 *           node under consideration (BSTNode<DataType>*)
 *
 *@param[in] newData
 *           A reference parameter of type DataType corresponding to the item
 *           to be inserted (DataType)
 *
 *@return None
 *
 *@note The inserted item must have a compareTo method
 */
template <class DataType>
void BSTClass<DataType>:: insertHelper
       ( 
        BSTNode<DataType> *&workingPtr, // in: a pointer to the current node
        const DataType &newData // in: the item to be inserted
       )
{
    // condition: the pointer has gone past a leaf node
    if( workingPtr != NULL )
    {
        // condition: the item to insert is less than the current node
        if( newData.compareTo( workingPtr->dataItem ) < 0 )
        {
            // condition: there is no left node, at a leaf node
            if( workingPtr->left == NULL )
            {
                workingPtr->left = new BSTNode<DataType>( newData, NULL, NULL);
            }
            else
            {
                insertHelper( workingPtr->left, newData );
            }
        }     
        // condition: the item to insert is greater than the current node   
        else
        {
            // condition: there is no right node, at a leaf node
            if( workingPtr->right == NULL )
            {
                workingPtr->right = new BSTNode<DataType>
                                                        ( newData, NULL, NULL);
            }
            else
            {
                insertHelper( workingPtr->right, newData );
            }
        }
    }
}

/**
 *@brief Implementation of BSTClass class to search for an item in the tree
 *
 *@details An item is searched for in the tree and if found true is returned
 *
 *@pre Assumes an initialized BSTClass object and that the item searched for
 *     has a compareTo method
 *
 *@post A bool corresponding to whether or not the item is found is returned
 *      and the tree is unchanged
 *
 *@par Algorithm  
 *     If statements check whether the item passed in is equal to, less than,
 *     or greater than the item at the node under consideration, if it's equal
 *     then true is returned, if it's either less than or greater than it then
 *     in either case an if statement checks whether there is a node to the
 *     left or right and if so the method is called on that node otherwise
 *     false is returned
 *
 *@exception None
 *
 *@param[in] workingPtr
 *           A parameter of type BSTNode pointer which points to the current
 *           node under consideration in the recursion (BSTNode<DataType>*)
 *
 *@param[in] searchDataItem
 *           A const reference parameter of type DataType corresponding to the
 *           item searched for in the tree (DataType)
 *
 *@return A bool corresponding to whether or not the item was found in the
 *        tree (bool)
 *
 *@note The item searched for must have a compareTo method
 */
template <class DataType>
bool BSTClass<DataType>:: findHelper
       ( 
        BSTNode<DataType> *workingPtr, // in: pointer to the current node
        DataType &searchDataItem // in: the item being searched for
       ) const
{
    bool found = false;

    // condition: the item at the current node is equal to the item searched
    //            for in the tree
    if( searchDataItem.compareTo( workingPtr->dataItem ) == 0 )
    {
        return true;
    }
    // condition: the item at the current node is less than the item searched
    //            for in the tree
    else if( searchDataItem.compareTo( workingPtr->dataItem ) < 0 )
    {
        // condition: there is no branch to the left
        if( workingPtr->left != NULL )
        {
            found = findHelper( workingPtr->left, searchDataItem );
        }
        else
        {
            return false;
        }       
    }
    else
    {
        // condition: there is no branch to the right
        if( workingPtr->right != NULL )
        {
            found = findHelper( workingPtr->right, searchDataItem );
        }
        else
        {
            return false;
        }       
    }

    return found;
}

/**
 *@brief Implementation of BSTClass class that removes a node in the tree
 *
 *@details The item passed in as a parameter is found and removed recursively
 *         if it's in the tree
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post If the item to be removed is in the tree then it is removed and the
 *      DataType parameter holds the value of the removed item
 *
 *@par Algorithm  
 *     If statements check whether the item passed in is equal to, less than, 
 *     or greater than the item at the node under consideration, if it's less
 *     or great then the method is called recursively and if it's equal then
 *     it is removed, if it has two children then the greatest item in the left 
 *     branch is put into its node, if it has only one child then it's linked
 *     with the child's child, and if it's a leaf then it is deleted
 *
 *@exception None
 *
 *@param[in] workingPtr
 *           A parameter of type BSTNode pointer which points to the current
 *           node under consideration in the recursion (BSTNode<DataType>*)
 *
 *@param[out] removeDataItem
 *            A const reference parameter of type DataType corresponding to the
 *            item to be removed from the tree (DataType)
 *
 *@return A bool is returned corresponding to whether or not the removal was
 *        successful (bool)
 *
 *@note None
 */
template <class DataType>
bool BSTClass<DataType>:: removeHelper
       ( 
        BSTNode<DataType> *&workingPtr, // in: pointer to the current node 
        const DataType &removeDataItem // out: the item to be removed
       )        
{
    bool removed = false;
    BSTNode<DataType> *temp = workingPtr;
    BSTNode<DataType> *hold;

    // condition: the item to be removed is found
    if( removeDataItem.compareTo( workingPtr->dataItem ) == 0 )
    {
        // condition: the node containing the item is a leaf
        if( workingPtr->left == NULL && workingPtr->right == NULL )      
        {
            delete workingPtr;
            workingPtr = NULL;
        }
        // condition: the node containing the item has one child to the left
        else if( workingPtr->left != NULL && workingPtr->right == NULL )
        {
            workingPtr = workingPtr->left;
            delete temp;
        }
        // condition: the node containing the item has one child to the right
        else if( workingPtr->right != NULL && workingPtr->left == NULL )
        {
            workingPtr = workingPtr->right;
            delete temp;
        }
        else
        {
            temp = temp->left;
            while( temp->right != NULL && ( temp->right )->right != NULL )
            {
                temp = temp->right;
            }
            // condition: the node to the left of the node containing the item
            //            has no right nodes
            if( temp->right == NULL )
            {
                workingPtr->dataItem = temp->dataItem;
                workingPtr->left = temp->left;
                delete temp;
            }
            // condition: the node to the left of the node containing the item
            //            has at least one right node
            else if( ( temp->right )->right == NULL )
            {
                workingPtr->dataItem = ( temp->right )->dataItem; 
                hold = temp->right;
                temp->right = ( temp->right )->left;
                delete hold;
            }
        }

        return true;
    }
    // condition: the item to be removed is less than the item at the current
    //            node
    else if( removeDataItem.compareTo( workingPtr->dataItem ) < 0 )
    {
        // condition: there are nodes to the left
        if( workingPtr->left != NULL )
        {
            removed = removeHelper( workingPtr->left, removeDataItem );
        }
        else
        {
            return false;
        }       
    }
    else
    {
        // condition: there are nodes to the right
        if( workingPtr->right != NULL )
        {
            removed = removeHelper( workingPtr->right, removeDataItem );
        }
        else
        {
            return false;
        }       
    }

    return removed;
}

/**
 *@brief Implementation of BSTClass class method to traverse the tree and 
 *       print its structure to the screen
 *
 *@details Recursively moves through the tree and prints the value at each
 *         node 
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post The values in the nodes of the tree are printed to the screen and
 *      the tree is unchanged
 *
 *@par Algorithm  
 *     An if statement checks whether the pointer is NULL and if not then the
 *     the value at the node is printed to the screen, the method is called
 *     on the left branch, and then on the right branch    
 *
 *@exception None
 *
 *@param[in] workingPtr
 *           A parameter of type BSTNode pointer which points to the current
 *           node under consideration in the recursion (BSTNode<DataType>*)
 *
 *@return None
 *
 *@note A helper method to inOrderTraversal
 */
template <class DataType>
void BSTClass<DataType>:: preOrderTraversalHelper
       ( 
        BSTNode<DataType> *workingPtr // in: the pointer to the current node
       ) const
{
    char string[MAX_DATA_LEN];

    // condition: the pointer is not NULL
    if( workingPtr != NULL )
    {
        ( workingPtr->dataItem ).toString( string );
        cout << string << endl;
        preOrderTraversalHelper( workingPtr->left );
        preOrderTraversalHelper( workingPtr->right );
    }
}

/**
 *@brief Implementation of BSTClass class method to traverse the tree and 
 *       print its structure to the screen
 *
 *@details Recursively moves through the tree and prints the value at each
 *         node 
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post The values in the nodes of the tree are printed to the screen and
 *      the tree is unchanged
 *
 *@par Algorithm  
 *     An if statement checks whether the pointer is NULL and if not then the
 *     method is called on the left branch, the value at the node is printed
 *     to the screen, and then the method is called on the right branch
 *
 *@exception None
 *
 *@param[in] workingPtr
 *           A parameter of type BSTNode pointer which points to the current
 *           node under consideration in the recursion (BSTNode<DataType>*)
 *
 *@return None
 *
 *@note A helper method to preOrderTraversal
 */
template <class DataType>
void BSTClass<DataType>:: inOrderTraversalHelper
       ( 
        BSTNode<DataType> *workingPtr // in: the pointer to the current node
       ) const
{
    char string[MAX_DATA_LEN];

    // condition: the pointer is not NULL
    if( workingPtr != NULL )
    {
        inOrderTraversalHelper( workingPtr->left );
        ( workingPtr->dataItem ).toString( string );
        cout << string << endl;
        inOrderTraversalHelper( workingPtr->right );
    }
}

/**
 *@brief Implementation of BSTClass class method to traverse the tree and 
 *       print its structure to the screen
 *
 *@details Recursively moves through the tree and prints the value at each
 *         node 
 *
 *@pre Assumes an initialized BSTClass object
 *
 *@post The values in the nodes of the tree are printed to the screen and
 *      the tree is unchanged
 *
 *@par Algorithm  
 *     An if statement checks whether the pointer is NULL and if not then the
 *     method is called on the left branch, then the right branch, and then
 *     the value at the node is printed to the screen
 *
 *@exception None
 *
 *@param[in] workingPtr
 *           A parameter of type BSTNode pointer which points to the current
 *           node under consideration in the recursion (BSTNode<DataType>*)
 *
 *@return None
 *
 *@note A helper method to postOrderTraversal
 */
template <class DataType>
void BSTClass<DataType>:: postOrderTraversalHelper
       ( 
        BSTNode<DataType> *workingPtr // in: the pointer to the current node
       ) const
{
    char string[MAX_DATA_LEN];    

    // condition: the pointer is not NULL
    if( workingPtr != NULL )
    {
        postOrderTraversalHelper( workingPtr->left );
        postOrderTraversalHelper( workingPtr->right );
        ( workingPtr->dataItem ).toString( string );
        cout << string << endl;
    }
}

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef BST_CLASS_CPP

