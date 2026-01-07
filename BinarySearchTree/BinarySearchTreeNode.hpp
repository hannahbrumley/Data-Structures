#ifndef _BINARY_SEARCH_TREE_NODE_HPP
#define _BINARY_SEARCH_TREE_NODE_HPP

#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/NullptrException.hpp"

template <typename TK, typename TD>
//! A template node class, to be used in the BinarySearchTree class.
class BinarySearchTreeNode
{
public:
    //! Initializes left and right pointers to nullptr.
    BinarySearchTreeNode()
    {
        ptrLeft = nullptr;
        ptrRight = nullptr;
    }

    BinarySearchTreeNode( TK newKey, TD newData )
    {
        key = newKey;
        data = newData;
        ptrLeft = nullptr;
        ptrRight = nullptr;
    }

    //! Destroys left and right children, if they are not pointing to nullptr.
    ~BinarySearchTreeNode()
    {
        // destroy children
        if ( ptrLeft != nullptr  ) { delete ptrLeft; }
        if ( ptrRight != nullptr ) { delete ptrRight; }
    }

    //! Pointer to the left child of the node, which is lesser in value
    BinarySearchTreeNode<TK, TD>* ptrLeft;

    //! Pointer to the right chlid of the node, which is greater in value
    BinarySearchTreeNode<TK, TD>* ptrRight;

    //! The data stored by the node
    TD data;

    //! The key of this node
    TK key;

    //! The tester is our friend
    friend class BinarySearchTreeTester;
};

#endif
