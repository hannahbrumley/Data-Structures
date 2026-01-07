#ifndef _BINARY_SEARCH_TREE_HPP
#define _BINARY_SEARCH_TREE_HPP

#include "BinarySearchTreeNode.hpp"

#include "../../Utilities/Logger.hpp"
#include "../../Utilities/StringUtil.hpp"

template <typename TK, typename TD>
//! A template binary search tree class that takes a KEY and a DATA
class BinarySearchTree
{
private:
    //! A pointer to the root node of the tree; TK = data type of the key, TD = data type of the data.
    BinarySearchTreeNode<TK, TD>* m_ptrRoot;

    //! The amount of nodes in the tree
    int m_nodeCount;

    //! The tester is our friend
    friend class BinarySearchTreeTester;

public:
    //! BinarySearchTree Constructor
    BinarySearchTree();
    //! BinarySearchTree Destructor
    ~BinarySearchTree();

    // Basic functionality
    //! Function that begins the recursive push function. Add new item to tree.
    void Push( const TK& newKey, const TD& newData );
    //! Function that begins the recursive contains function. Check if key is contained within the tree.
    bool Contains( const TK& key );
    //! Function that begins the recursive find node function. Get data relayed to some key stored in the tree.
    TD& GetData( const TK& key );

    // Traversal functions
    //! Function that begins the recursive in-order traversal.
    string GetInOrder();
    //! Function that begins the recursive pre-order traversal.
    string GetPreOrder();
    //! Function that begins the recursive post-order traversal.
    string GetPostOrder();

    // Additional functionality
    //! Function that begins the recursive get min key, returns key with smallest value.
    TK& GetMinKey();
    //! Function that begins the recursive get max key, returns key with largest value.
    TK& GetMaxKey();
    //! Function that beginst he recursive get height, returns the height of the tree.
    int GetHeight();
    //! Get amount of nodes in tree.
    int GetCount();

    //    void Delete( const TK& key );


     
private:
    //! Function that begins the recursive find node process based on node's key.
    BinarySearchTreeNode<TK, TD>* FindNode( const TK& key );

    // Recursive traversal functions
    //! Recursive in-order traversal function
    void RecursiveGetInOrder  ( BinarySearchTreeNode<TK, TD>* ptrCurrent, stringstream& stream );
    //! Recursive pre-order traversal function
    void RecursiveGetPreOrder ( BinarySearchTreeNode<TK, TD>* ptrCurrent, stringstream& stream );
    //! Recursive post-order traversal function
    void RecursiveGetPostOrder( BinarySearchTreeNode<TK, TD>* ptrCurrent, stringstream& stream );

    // Recursive additional functionality
    //! Recurses through nodes in tree looking for node with given key.
    BinarySearchTreeNode<TK, TD>* RecursiveFindNode( const TK& key, BinarySearchTreeNode<TK, TD>* ptrCurrent );
    //! Recurses through tree looking for the node with the maximum key value.
    TK& RecursiveGetMax( BinarySearchTreeNode<TK, TD>* ptrCurrent );
    //! Recurses through tree looking for the node with the minimum key value.
    TK& RecursiveGetMin( BinarySearchTreeNode<TK, TD>* ptrCurrent );
    //! Recurses through the tree comparing heights of left and right sub-trees to get the overall height.
    int RecursiveGetHeight( BinarySearchTreeNode<TK, TD>* ptrCurrent );
    //! Recurses through the tree searching for a node with a matching key.
    bool RecursiveContains( const TK& key, BinarySearchTreeNode<TK, TD>* ptrCurrent );
    //! Recurses through the tree searching for a position to insert the new data based on its key.
    void RecursivePush( const TK& newKey, const TD& newData, BinarySearchTreeNode<TK, TD>* ptrCurrent );

//    public:
//    void Delete( const TK& key );
//    private:
//    Node<TK, TD>* FindParentOfNode( const TK& key );
//    void DeleteNode_NoChildren( Node<TK, TD>* deleteMe, Node<TK, TD>* parent, bool isLeftNode );
//    void DeleteNode_LeftChild( Node<TK, TD>* deleteMe, Node<TK, TD>* parent, bool isLeftNode );
//    void DeleteNode_RightChild( Node<TK, TD>* deleteMe, Node<TK, TD>* parent, bool isLeftNode );
//    void DeleteNode_TwoChildren( Node<TK, TD>* deleteMe, Node<TK, TD>* parent, bool isLeftNode );
};

/* **************************************************************************************** */
/* ******************************************************************* Function definitions */
/* **************************************************************************************** */

/**
Initialize the root node pointer to nullptr and the node count to 0.
*/
template <typename TK, typename TD>
BinarySearchTree<TK,TD>::BinarySearchTree()
{
    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD> Constructor" );
    m_ptrRoot = nullptr;
    m_nodeCount = 0;
}


/**
If the root node pointer is not nullptr, then delete it.
*/
template <typename TK, typename TD>
BinarySearchTree<TK,TD>::~BinarySearchTree()
{
    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD> Destructor" );
    if ( m_ptrRoot != nullptr )
    {
        delete m_ptrRoot;
    }
}


/**
Error check: If the key is already in the tree, then throw a runtime_error with an error message. (Use teh Contains method)

Scenario 1: If m_ptrRoot is nullptr, create the new node here.

Scenario 2: Otherwise, start the push by calling the RecursivePush function, passing in the key, data, and the root node pointer.

@param  newKey      The key of the new item to be added.
@param  newData     The data of the new item to be added.
*/
template <typename TK, typename TD>
void BinarySearchTree<TK,TD>::Push( const TK& newKey, const TD& newData )
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::Push" );
//    Logger::Out( "New key: " + StringUtil::ToString( newKey ), "BinarySearchTree<TK,TD>::Push" );
//    Logger::Out( "New data: " + StringUtil::ToString( newData ), "BinarySearchTree<TK,TD>::Push" );

    if (Contains(newKey))
    {
        throw runtime_error("Key is not unique! "); 

    }
    if (m_ptrRoot == nullptr)
    {
        m_ptrRoot = new BinarySearchTreeNode<TK, TD>(newKey, newData); 
        m_nodeCount++; 
    }
    else
    {
        RecursivePush(newKey, newData, m_ptrRoot); 
    }
    
}


/**
Return the result of the RecursiveContains function, passing in the key and the root node pointer.

@param  key     The key to search for in the tree.
@return         True if the key is in the tree, or false otherwise.
*/
template <typename TK, typename TD>
bool BinarySearchTree<TK,TD>::Contains( const TK& key )
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::Contains" );
    return RecursiveContains(key, m_ptrRoot); 
}


/**
Begin the recursive in-order traversal by calling RecursiveGetInOrder and passing in the root node pointer and the string stream.

@return     The list of keys in the tree, in-order.
*/
template <typename TK, typename TD>
string BinarySearchTree<TK,TD>::GetInOrder()
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::GetInOrder" );
    stringstream stream;
    RecursiveGetInOrder( m_ptrRoot, stream );
    return stream.str();
}


/**
Begin the recursive pre-order traversal by calling RecursiveGetPreOrder and passing in the root node pointer and the string stream.

@return     The list of keys in the tree, pre-order.
*/
template <typename TK, typename TD>
string BinarySearchTree<TK,TD>::GetPreOrder()
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::GetPreOrder" );
    stringstream stream;
    RecursiveGetPreOrder( m_ptrRoot, stream );
    return stream.str();
}


/**
Begin the recursive post-order traversal by calling RecursiveGetPostOrder and passing in the root node pointer and the string stream.

@return     The list of keys in the tree, post-order.
*/
template <typename TK, typename TD>
string BinarySearchTree<TK,TD>::GetPostOrder()
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::GetPostOrder" );
    stringstream stream;
    RecursiveGetPostOrder( m_ptrRoot, stream );
    return stream.str();
}


/**
Begin the recursive search for the max key by calling the RecursiveGetMax function, passing in the root node pointer.

@return     A reference to the max key in the tree.
*/
template <typename TK, typename TD>
TK& BinarySearchTree<TK,TD>::GetMaxKey()
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::GetMaxKey" );
    return RecursiveGetMax(m_ptrRoot); 
}


/**
Begin the recursive search for the min key by calling the RecursiveGetMin function, passing in the root node pointer.

@return     A reference to the min key in the tree.
*/
template <typename TK, typename TD>
TK& BinarySearchTree<TK,TD>::GetMinKey()
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::GetMinKey" );
    return RecursiveGetMin(m_ptrRoot); 
}


/**
Return the count of nodes.

@return     The amonut of nodes in the tree.
*/
template <typename TK, typename TD>
int BinarySearchTree<TK,TD>::GetCount()     // done
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::GetCount" );
    return m_nodeCount; 
}


/**
Begin the recursive search for a node with a key by calling the RecursiveFindNode, passing in the key and root node pointer.

@param  key     The key to search for in the tree.
@return         The node found with the key given (possibly nullptr).
*/
template <typename TK, typename TD>
BinarySearchTreeNode<TK, TD>* BinarySearchTree<TK,TD>::FindNode( const TK& key )
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::FindNode" );
    return RecursiveFindNode(key, m_ptrRoot);
}


/**
If the root node pointer is set to nullptr, return 0. Otherwise, begin the recursive get height process
by calling RecursiveGetHeight and passing in the root node pointer.

@return     The height of the tree.
*/
template <typename TK, typename TD>
int BinarySearchTree<TK,TD>::GetHeight()
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::GetHeight" );
    if (m_ptrRoot == nullptr)
    {
        return 0; 
    }
    else
    {
        return RecursiveGetHeight(m_ptrRoot);
    }
}


/**
Use the FindNode function to find the node that has the key given.
If FindNode returns nullptr, then throw a runtime_error exception.
Otherwise, return the node's data.

@param  key     The key to search for in the tree.
@return         A reference to the data of the node.
*/
template <typename TK, typename TD>
TD& BinarySearchTree<TK, TD>::GetData(const TK& key)
{
    //Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::GetData" );
    BinarySearchTreeNode <TK, TD>* node = FindNode(key);
    if (node == nullptr)
    {
        throw runtime_error("Key not Found! ");
       

    }

    else
    {
        return (node->data);
    }
   

    
}
/* **************************************************************************************** */
/* ******************************************************************** Recursive functions */
/* **************************************************************************************** */


/**
Recurses through the tree, looking to see if a node with the key given exists.

#### TERMINATING CASES:

1. False if ptrCurrent is nullptr.
2. True if ptrCurrent's key matches the key.
3. False if there are no more child nodes to traverse (no left child / right child of ptrCurrent).

#### RECURSIVE CASES:

1. Recurse left if the key is less than ptrCurrent->key, returning that value.
2. Recurse right if the key is greater than ptrCurrent->key, returning that value.

@param  key             The key we're searching for.
@param  ptrCurrent      The current node we're investigating.
@return                 True if the key is found, or false otherwise.
*/
template <typename TK, typename TD>
bool BinarySearchTree<TK,TD>::RecursiveContains( const TK& key, BinarySearchTreeNode<TK, TD>* ptrCurrent )
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::RecursiveContains", 2 );
    if (ptrCurrent == nullptr)
    {
        return false; 
    }
    
    if (ptrCurrent->key == key)
    {
        return true; 
    }

    if (key < ptrCurrent->key)
    {
        return RecursiveContains(key, ptrCurrent->ptrLeft); 
    }
    else if (key > ptrCurrent->key)
    {
        return RecursiveContains(key, ptrCurrent->ptrRight); 
    }
    
    
}


/**
Recurses through the tree, looking to see if a node with the key given exists.

#### TERMINATING CASES:

1. nullptr if ptrCurrent is nullptr.
2. ptrCurrent if ptrCurrent's key matches the key.

#### RECURSIVE CASES:

1. Recurse left if the key is less than ptrCurrent->key, returning that value.
2. Recurse right if the key is greater than ptrCurrent->key, returning that value.

@param  key             The key we're searching for.
@param  ptrCurrent      The current node we're investigating.
@return                 The node with the matching key if found, nullptr otherwise.
*/
template <typename TK, typename TD>
BinarySearchTreeNode<TK, TD>* BinarySearchTree<TK,TD>::RecursiveFindNode( const TK& key, BinarySearchTreeNode<TK, TD>* ptrCurrent )
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::RecursiveFindNode", 2 );
    if (ptrCurrent == nullptr)
    {
        return nullptr; 

    }
    if (ptrCurrent->key == key)
    {
        return ptrCurrent; 
    }
    else
    {
        if (key < ptrCurrent->key)
        {
            return RecursiveFindNode(key, ptrCurrent->ptrLeft);
        }
        else if (key > ptrCurrent->key)
        {
            return RecursiveFindNode(key, ptrCurrent->ptrRight);
        }
    }
}


/**
Recurses through the tree, finding the proper place to put a new node.

#### Creating a node at ptrCurrent:

- Initialize the new node at the pointer. You can set its key and data via the Node constructor.
    - `ptrCurrent = new Node<TK,TD>( newKey, newData );` OR
    - `ptrCurrent->ptrLeft = new Node<TK,TD>( newKey, newData );` OR
    - `ptrCurrent->ptrRight = new Node<TK,TD>( newKey, newData );`
- Increment the node count by 1.
    - `m_nodeCount++;`

#### TERMINATING CASES:

1. If ptrCurrent is nullptr, throw a runtime error stating that the node is nullptr.
2. Otherwise if the newKey is less than the ptrCurrent's key AND there is no node to the left, then create the node to the left.
3. Otherwise if the newKey is greater than the ptrCurrent's key AND there is no node to the right, then create the node to the right.

#### RECURSIVE CASES:

1. If the newKey is less than the ptrCurrent's key AND there IS a node to the left, recurse left.
2. Otherwise if the newKey is greater than the ptrCurrent's key AND there IS a node to the right, recurse right.
*/
template <typename TK, typename TD>
void BinarySearchTree<TK,TD>::RecursivePush( const TK& newKey, const TD& newData, BinarySearchTreeNode<TK, TD>* ptrCurrent )
{

    if (ptrCurrent == nullptr)
    {
        throw runtime_error("Key is not unique! ");
    }
    if (newKey < ptrCurrent->key)
    {
        if(ptrCurrent->ptrLeft == nullptr)
        {
            ptrCurrent->ptrLeft =  new BinarySearchTreeNode<TK, TD>(newKey, newData); 
            m_nodeCount++; 
        }
        else
        {
            RecursivePush(newKey, newData, ptrCurrent->ptrLeft);
        }
    }

    else if (newKey > ptrCurrent->key)
    {
        if(ptrCurrent->ptrRight == nullptr)
        {
            ptrCurrent->ptrRight = new BinarySearchTreeNode<TK, TD>(newKey, newData); 
            m_nodeCount++; 
        }
        else
        {
            RecursivePush(newKey, newData, ptrCurrent->ptrRight); 
        }
    }
}


/**
Recurse in-order, building the stream.

1. Recurse to the left child.
2. Stream out the current node's key (`stream << ptrCurrent->key;`)
3. Recurse to the right child.
*/
template <typename TK, typename TD>
void BinarySearchTree<TK,TD>::RecursiveGetInOrder( BinarySearchTreeNode<TK, TD>* ptrCurrent, stringstream& stream )
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::RecursiveGetInOrder", 2 );
//    stream << "Output data this way." << endl;
    if (ptrCurrent == nullptr)
    {
        return; 
    }
    else
    {
        RecursiveGetInOrder(ptrCurrent->ptrLeft, stream); 
        stream << ptrCurrent->key; 
        RecursiveGetInOrder(ptrCurrent->ptrRight, stream); 
    }
}


/**
Recurse pre-order, building the stream.

1. Stream out the current node's key (`stream << ptrCurrent->key;`)s
2. Recurse to the left child.
3. Recurse to the right child.
*/
template <typename TK, typename TD>
void BinarySearchTree<TK,TD>::RecursiveGetPreOrder( BinarySearchTreeNode<TK, TD>* ptrCurrent, stringstream& stream )
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::RecursiveGetPreOrder", 2 );
//    stream << "Output data this way." << endl;
    if (ptrCurrent == nullptr)
    {
        return; 
    }
    else
    {
        stream << ptrCurrent->key; 
        RecursiveGetPreOrder(ptrCurrent->ptrLeft, stream); 
        RecursiveGetPreOrder(ptrCurrent->ptrRight, stream); 
    }
}


/**
Recurse post-order, building the stream.

1. Recurse to the left child.
3. Recurse to the right child.
2. Stream out the current node's key (`stream << ptrCurrent->key;`)
*/
template <typename TK, typename TD>
void BinarySearchTree<TK,TD>::RecursiveGetPostOrder( BinarySearchTreeNode<TK, TD>* ptrCurrent, stringstream& stream )
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::RecursiveGetPostOrder", 2 );
//    stream << "Output data this way." << endl;
    if (ptrCurrent == nullptr)
    {
        return; 
    }
    else
    {
        RecursiveGetPostOrder(ptrCurrent->ptrLeft, stream); 
        RecursiveGetPostOrder(ptrCurrent->ptrRight, stream); 
        stream << ptrCurrent->key; 
    }
}


/**
Recurse to find the node with the max key in the tree.

#### TERMINATING CASE:

1. If ptrCurrent is nullptr, throw a runtime_error.
2. Otherwise, if ptrCurrent does not have a right child, we are at the max node: return ptrCurrent's key.

#### RECURSIVE CASE:

1. Recurse to the right, returning the result.
*/
template <typename TK, typename TD>
TK& BinarySearchTree<TK,TD>::RecursiveGetMax( BinarySearchTreeNode<TK, TD>* ptrCurrent )
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::RecursiveGetMax", 2 );
    if (ptrCurrent == nullptr)
    {
        throw runtime_error("Error");
    }
    if (ptrCurrent->ptrRight == nullptr)
    {
        return ptrCurrent->key;
    }
    else
    {
        return RecursiveGetMax(ptrCurrent->ptrRight);
    }
}


/**
Recurse to find the node with the min key in the tree.

#### TERMINATING CASES:

1. If ptrCurrent is nullptr, throw a runtime_error.
2. Otherwise, if ptrCurrent does not have a left child, we are at the min node: return ptrCurrent's key.

#### RECURSIVE CASE:

1. Recurse to the left, returning the result.
*/
template <typename TK, typename TD>
TK& BinarySearchTree<TK,TD>::RecursiveGetMin( BinarySearchTreeNode<TK, TD>* ptrCurrent )
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::RecursiveGetMin", 2 );
    if (ptrCurrent == nullptr)
    {
        throw runtime_error("Error");
    }
    if (ptrCurrent->ptrLeft == nullptr)
    {
        return ptrCurrent->key; 
    }
    else
    {
        return RecursiveGetMin(ptrCurrent->ptrLeft); 
    }
}


/**
Recurse to get the max height of the left and right subtree in order to find this tree's height.

1. If ptrCurrent is nullptr, return 0.
2. Create two int variables to store the leftHeight and the rightHeight. Initialize both to 0.
3. If ptrCurrent has a left child, recurse left and store the result into leftHeight, + 1 to count the current node.
4. If ptrCurrent has a right child, recurse right and store the result into rightHeight, +1 to count the current node.
5. If leftHeight is greater than rightHeight, return leftHeight.
6. Otherwise, return rightHeight.
*/
template <typename TK, typename TD>
int BinarySearchTree<TK,TD>::RecursiveGetHeight( BinarySearchTreeNode<TK, TD>* ptrCurrent )
{
//    Logger::OutHighlight( "FUNCTION BEGIN", "BinarySearchTree<TK,TD>::RecursiveGetHeight", 2 );
    if (ptrCurrent == nullptr)
    {
        return 0; 
    }
    int leftHeight = 0; 
    int rightHeight = 0; 

    if (ptrCurrent->ptrLeft != nullptr)
    {
        leftHeight = RecursiveGetHeight(ptrCurrent->ptrLeft) + 1; 
    }
    if (ptrCurrent->ptrRight != nullptr)
    {
        rightHeight = RecursiveGetHeight(ptrCurrent->ptrRight) + 1; 
    }
    
    else
    {
        if (leftHeight > rightHeight)
        {
            return leftHeight;
        }
        else
        {
            return rightHeight;
        }

    }
  
        
   
}


#endif
