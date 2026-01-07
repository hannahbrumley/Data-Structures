#ifndef _BINARY_SEARCH_TREE_TESTER_HPP
#define _BINARY_SEARCH_TREE_TESTER_HPP

#include <iostream>
#include <string>
using namespace std;

#include "../../cutest/TesterBase.hpp"
#include "../../Utilities/Menu.hpp"
#include "../../Utilities/StringUtil.hpp"
#include "../../Utilities/Logger.hpp"
#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/StructureFullException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/NullptrException.hpp"

#include "BinarySearchTreeNode.hpp"
#include "BinarySearchTree.hpp"

class BinarySearchTreeTester : public TesterBase
{
public:
    BinarySearchTreeTester()
        : TesterBase( "test_result_binary_search_tree.html" )
    {
        AddTest(TestListItem("NodeConsructor()",    bind(&BinarySearchTreeTester::Test_NodeConstructor, this)));

        AddTest(TestListItem("TreeConstructor()",   bind(&BinarySearchTreeTester::Test_TreeConstructor, this)));

        AddTest(TestListItem("Push()",              bind(&BinarySearchTreeTester::Test_Push, this)));
        AddTest(TestListItem("Contains()",          bind(&BinarySearchTreeTester::Test_Contains, this)));
        AddTest(TestListItem("FindNode()",          bind(&BinarySearchTreeTester::Test_FindNode, this)));
//        AddTest(TestListItem("FindParentOfNode()",  bind(&BinarySearchTreeTester::Test_FindParentOfNode, this)));
        AddTest(TestListItem("GetInOrder()",        bind(&BinarySearchTreeTester::Test_GetInOrder, this)));
        AddTest(TestListItem("GetPreOrder()",       bind(&BinarySearchTreeTester::Test_GetPreOrder, this)));
        AddTest(TestListItem("GetPostOrder()",      bind(&BinarySearchTreeTester::Test_GetPostOrder, this)));
        AddTest(TestListItem("GetMinKey()",         bind(&BinarySearchTreeTester::Test_GetMinKey, this)));
        AddTest(TestListItem("GetMaxKey()",         bind(&BinarySearchTreeTester::Test_GetMaxKey, this)));
        AddTest(TestListItem("GetCount()",          bind(&BinarySearchTreeTester::Test_GetCount, this)));
        AddTest(TestListItem("GetHeight()",         bind(&BinarySearchTreeTester::Test_GetHeight, this)));
//        AddTest(TestListItem("Delete()",            bind(&BinarySearchTreeTester::Test_Delete, this)));
    }

    virtual ~BinarySearchTreeTester() { }

private:
    int Test_NodeConstructor();
    int Test_TreeConstructor();
    int Test_Push();
    int Test_Contains();
    int Test_FindNode();
//    int Test_FindParentOfNode();
    int Test_GetInOrder();
    int Test_GetPreOrder();
    int Test_GetPostOrder();
    int Test_GetMinKey();
    int Test_GetMaxKey();
    int Test_GetCount();
    int Test_GetHeight();
//    int Test_Delete();
};

int BinarySearchTreeTester::Test_NodeConstructor()
{
    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_NodeConstructor", 3 );
    StartTestSet( "Test_NodeConstructor", { } );
    ostringstream oss;

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "1. Check if Node Constructor has been implemented yet..." );

        bool prereqsImplemented = true;
        string functionName = "Node Constructor";
        Set_ExpectedOutput( functionName, string( "Implemented" ) );
        try
        {
            BinarySearchTreeNode<char, string> testNode;
        }
        catch ( NotImplementedException& ex )
        {
            Set_Comments( ex.what() );
            prereqsImplemented = false;
        }

        if ( prereqsImplemented )
        {
            Set_ActualOutput( functionName, string( "Implemented" ) );
            TestPass();
            FinishTest();
        }
        else
        {
            Set_ActualOutput( functionName, string( "Not implemented" ) );
            TestFail();
            FinishTest();
            FinishTestSet();
            return TestResult();
        }
    } /* TEST END **************************************************************/

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "2. Create new node, ptrLeft/ptrRight should be nullptr." );
    {
        Set_Comments( "Make sure you're initializing pointers to nullptr from within constructors!" );

        BinarySearchTreeNode<char, string> node;

        Set_ExpectedOutput  ( "Node's ptrLeft is nullptr" );
        Set_ExpectedOutput  ( "Node's ptrRight is nullptr" );

        oss << node.ptrLeft;
        Set_ActualOutput    ( "Node's ptrLeft", oss.str() );

        oss.str("");
        oss.clear();
        oss << node.ptrRight;
        Set_ActualOutput    ( "Node's ptrRight", oss.str() );

        if ( node.ptrLeft != nullptr )
        {
            TestFail();
        }
        else if ( node.ptrRight != nullptr )
        {
            TestFail();
        }
        else
        {
            TestPass();
        }
    }
    FinishTest();

    FinishTestSet();
    return TestResult();
}

int BinarySearchTreeTester::Test_TreeConstructor()
{
    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_TreeConstructor", 3 );
    StartTestSet( "Test_TreeConstructor", { } );
    ostringstream oss;

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "1. Create new tree, check that m_ptrRoot is nullptr and m_nodeCount is 0." );

        Set_Comments( "Make sure you're initializing pointers to nullptr from within constructors!" );

        BinarySearchTree<char, string> tree;

        int expectedResult = 0;
        int actualResult = tree.m_nodeCount;

        Set_ExpectedOutput  ( "m_nodeCount", expectedResult );
        Set_ActualOutput    ( "m_nodeCount", actualResult );

        oss << tree.m_ptrRoot;
        Set_ExpectedOutput  ( "Trees's m_ptrRoot", string( "nullptr" ) );
        Set_ActualOutput    ( "Trees's m_ptrRoot", oss.str() );

        if ( actualResult != expectedResult )
        {
            TestFail();
        }
        else if ( tree.m_ptrRoot != nullptr )
        {
            TestFail();
        }
        else
        {
            TestPass();
        }

        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}

int BinarySearchTreeTester::Test_Push()
{
    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_Push", 3 );
    StartTestSet( "Test_Push", { "RecursivePush", "Contains" } );
    ostringstream oss;

    string functionName = "BinarySearchTree::RecursivePush";
    StartTest( "0a. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; tree.RecursivePush( 'a', "A", tree.m_ptrRoot ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    functionName = "BinarySearchTree::Push";
    StartTest( "0b. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; tree.Push( 'a', "A" ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "2. Push one item to a tree. Make sure it becomes the root. Validate key/data." );

        Set_Comments( "Push( 'a', \"apple\" )" );

        BinarySearchTree<char, string> tree;
        tree.Push( 'a', "apple" );

        if ( !Set_Outputs( "m_nodeCount",       1,          tree.m_nodeCount ) )        { TestFail(); }

        // Check ROOT
        else if ( tree.m_ptrRoot == nullptr )
        {
            Set_Comments( "m_ptrRoot was nullptr" );
            TestFail();
        }
        else if ( !Set_Outputs( "m_ptrRoot's key",   'a',        tree.m_ptrRoot->key ) )     { TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot's data",  "apple",    tree.m_ptrRoot->data ) )    { TestFail(); }

        else                                                                                 { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "3. Push 3 items to a tree. Check positions." );

        Set_Comments( "Push( 'b', \"banana\" )" );
        Set_Comments( "Push( 'a', \"apple\" )" );
        Set_Comments( "Push( 'c', \"cranberry\" )" );

        BinarySearchTree<char, string> tree;
        tree.Push( 'b', "banana" );
        tree.Push( 'a', "apple" );
        tree.Push( 'c', "cranberry" );

        string txtTree = "<pre>";
        txtTree += "  b     \n";
        txtTree += " / \\   \n";
        txtTree += "a   c   \n";
        txtTree += "</pre>";
        Set_Comments( txtTree );

        if ( !Set_Outputs( "m_nodeCount",       3,          tree.m_nodeCount ) )        { TestFail(); }

        // Check ROOT
        else if ( tree.m_ptrRoot == nullptr )
        {
            Set_Comments( "m_ptrRoot was nullptr" );
            TestFail();
        }
        else if ( !Set_Outputs( "m_ptrRoot's key",   'b',         tree.m_ptrRoot->key ) )     { TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot's data",  "banana",    tree.m_ptrRoot->data ) )    { TestFail(); }

        // Check ROOT- > LEFT
        else if ( tree.m_ptrRoot->ptrLeft == nullptr )
        {
            Set_Comments( "m_ptrRoot->ptrLeft was nullptr" );
            TestFail();
        }
        else if ( !Set_Outputs( "m_ptrRoot->ptrLeft's key",   'a',         tree.m_ptrRoot->ptrLeft->key ) )     { TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrLeft's data",  "apple",     tree.m_ptrRoot->ptrLeft->data ) )    { TestFail(); }

        // Check ROOT -> RIGHT
        else if ( tree.m_ptrRoot->ptrRight == nullptr )
        {
            Set_Comments( "m_ptrRoot->ptrRight was nullptr" );
            TestFail();
        }
        else if ( !Set_Outputs( "m_ptrRoot->ptrRight's key",   'c',             tree.m_ptrRoot->ptrRight->key ) )     { TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrRight's data",  "cranberry",     tree.m_ptrRoot->ptrRight->data ) )    { TestFail(); }

        else                                                                                 { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "5. Push 7 items to a tree. Check positions." );

        Set_Comments( "Push( 'd', \"dates\" )" );
        Set_Comments( "Push( 'b', \"banana\" )" );
        Set_Comments( "Push( 'f', \"figs\" )" );
        Set_Comments( "Push( 'a', \"apple\" )" );
        Set_Comments( "Push( 'c', \"cranberry\" )" );
        Set_Comments( "Push( 'e', \"elderberry\" )" );
        Set_Comments( "Push( 'g', \"grapefruit\" )" );

        string txtTree = "<pre>";
        txtTree += "       d                \n";
        txtTree += "    /     \\            \n";
        txtTree += "  b         f           \n";
        txtTree += " / \\       / \\        \n";
        txtTree += "a   c     e   g         \n";
        txtTree += "</pre>";
        Set_Comments( txtTree );

        BinarySearchTree<char, string> tree;
        tree.Push( 'd', "dates" );
        tree.Push( 'b', "banana" );
        tree.Push( 'f', "figs" );
        tree.Push( 'a', "apple" );
        tree.Push( 'c', "cranberry" );
        tree.Push( 'e', "elderberry" );
        tree.Push( 'g', "grapefruit" );

        if ( !Set_Outputs( "m_nodeCount",       7,          tree.m_nodeCount ) )        { TestFail(); }

        // Check ROOT (d)
        else if ( tree.m_ptrRoot == nullptr ) { Set_Comments( "m_ptrRoot was nullptr" );      TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot's key",   'd',                   tree.m_ptrRoot->key ) )                       { TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot's data",  "dates",               tree.m_ptrRoot->data ) )                      { TestFail(); }

        // Check ROOT- > LEFT (b)
        else if ( tree.m_ptrRoot->ptrLeft == nullptr ) { Set_Comments( "m_ptrRoot->ptrLeft was nullptr" );     TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrLeft's key",   'b',          tree.m_ptrRoot->ptrLeft->key ) )              { TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrLeft's data",  "banana",     tree.m_ptrRoot->ptrLeft->data ) )             { TestFail(); }

        // Check ROOT- > LEFT -> LEFT (a)
        else if ( tree.m_ptrRoot->ptrLeft->ptrLeft == nullptr ) { Set_Comments( "m_ptrRoot->ptrLeft->ptrLeft was nullptr" );     TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrLeft->ptrLeft's key",   'a',          tree.m_ptrRoot->ptrLeft->ptrLeft->key ) )              { TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrLeft->ptrLeft's data",  "apple",      tree.m_ptrRoot->ptrLeft->ptrLeft->data ) )             { TestFail(); }

        // Check ROOT -> RIGHT (f)
        else if ( tree.m_ptrRoot->ptrRight == nullptr ) { Set_Comments( "m_ptrRoot->ptrRight was nullptr" );    TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrRight's key",   'f',         tree.m_ptrRoot->ptrRight->key ) )             { TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrRight's data",  "figs",      tree.m_ptrRoot->ptrRight->data ) )            { TestFail(); }

        // Check ROOT -> RIGHT -> RIGHT (g)
        else if ( tree.m_ptrRoot->ptrRight->ptrRight == nullptr ) { Set_Comments( "m_ptrRoot->ptrRight->ptrRight was nullptr" );    TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrRight->ptrRight's key",   'g',         tree.m_ptrRoot->ptrRight->ptrRight->key ) )           { TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrRight->ptrRight's data",  "grapefruit",      tree.m_ptrRoot->ptrRight->ptrRight->data ) )    { TestFail(); }

        // Check ROOT- > LEFT -> RIGHT (c)
        else if ( tree.m_ptrRoot->ptrLeft->ptrRight == nullptr ) { Set_Comments( "m_ptrRoot->ptrLeft->ptrRight was nullptr" );     TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrLeft->ptrRight's key",   'c',          tree.m_ptrRoot->ptrLeft->ptrRight->key ) )              { TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrLeft->ptrRight's data",  "cranberry",      tree.m_ptrRoot->ptrLeft->ptrRight->data ) )             { TestFail(); }

        // Check ROOT -> RIGHT -> LEFT (e)
        else if ( tree.m_ptrRoot->ptrRight->ptrLeft == nullptr ) { Set_Comments( "m_ptrRoot->ptrRight->ptrLeft was nullptr" );    TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrRight->ptrLeft's key",   'e',         tree.m_ptrRoot->ptrRight->ptrLeft->key ) )           { TestFail(); }
        else if ( !Set_Outputs( "m_ptrRoot->ptrRight->ptrLeft's data",  "elderberry",      tree.m_ptrRoot->ptrRight->ptrLeft->data ) )    { TestFail(); }

        else                                                                                 { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    functionName = "BinarySearchTree::Contains";
    StartTest( "6. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; tree.Contains( 'a' ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "7. Don't allow the same key to be entered more than once. Throw runtime_error if this happens." );

        Set_Comments( "Push( 'a', \"apple\" )" );
        Set_Comments( "Push( 'a', \"apple\" )" );

        BinarySearchTree<char, string> tree;

        tree.Push( 'a', "apple" );

        bool exceptionHappened = false;
        try
        {
            tree.Push( 'a', "aardvark" );
        }
        catch( const runtime_error& ex )
        {
            exceptionHappened = true;
            Logger::Out(ex.what());
        }

        Set_ExpectedOutput  ( "Exception thrown", bool( true ) );
        Set_ActualOutput    ( "Exception thrown", bool( exceptionHappened ) );

        if ( !exceptionHappened )
        {
            Set_Comments( "Expected a runtime_error to be thrown but it didn't happen!" );
            TestFail();
        }
        else
        {
            TestPass();
        }

        FinishTest();
    } /* TEST END **************************************************************/



    FinishTestSet();
    return TestResult();
}

int BinarySearchTreeTester::Test_Contains()
{
    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_Contains", 3 );
    StartTestSet( "Test_Contains", { "RecursiveContains" } );
    ostringstream oss;

    string functionName = "BinarySearchTree::RecursiveContains";
    StartTest( "0a. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; tree.RecursiveContains( 'a', tree.m_ptrRoot ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    functionName = "BinarySearchTree::Contains";
    StartTest( "0b. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; tree.Contains( 'a' ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "2. Add some items to a tree; Check if Contains() locates an item." );

        string txtTree = "<pre>";
        txtTree += "  b     \n";
        txtTree += " / \\   \n";
        txtTree += "a   c   \n";
        txtTree += "</pre>";
        Set_Comments( txtTree );

        BinarySearchTree<char, string> tree;
        tree.m_ptrRoot = new BinarySearchTreeNode<char,string>( 'b', "banana" );
        tree.m_ptrRoot->ptrLeft = new BinarySearchTreeNode<char,string>( 'a', "apple" );
        tree.m_ptrRoot->ptrRight = new BinarySearchTreeNode<char,string>( 'c', "cantalope" );

        if ( !Set_Outputs( "tree.Contains( 'c' )", true, tree.Contains( 'c' ) ) )           { TestFail(); }
        else                                                                                { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "3. Add some items to a tree; Check if Contains() returns false for item not in tree." );

        string txtTree = "<pre>";
        txtTree += "  b     \n";
        txtTree += " / \\   \n";
        txtTree += "a   c   \n";
        txtTree += "</pre>";
        Set_Comments( txtTree );

        BinarySearchTree<char, string> tree;
        tree.m_ptrRoot = new BinarySearchTreeNode<char,string>( 'b', "banana" );
        tree.m_ptrRoot->ptrLeft = new BinarySearchTreeNode<char,string>( 'a', "apple" );
        tree.m_ptrRoot->ptrRight = new BinarySearchTreeNode<char,string>( 'c', "cantalope" );

        if ( !Set_Outputs( "tree.Contains( 'z' )", false, tree.Contains( 'z' ) ) )      { TestFail(); }
        else                                                                            { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}

int BinarySearchTreeTester::Test_FindNode()
{
    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_FindNode", 3 );
    StartTestSet( "Test_FindNode", { "RecursiveFindNode" } );
    ostringstream oss;

    string functionName = "BinarySearchTree::RecursiveFindNode";
    StartTest( "0a. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; tree.RecursiveFindNode( 'a', tree.m_ptrRoot ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    functionName = "BinarySearchTree::FindNode";
    StartTest( "0b. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; tree.FindNode( 'a' ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "Fill a tree, use FindNode() to find node 'g' in the tree." );

        string txtTree = "<pre>";
        txtTree += "       d                \n";
        txtTree += "    /     \\            \n";
        txtTree += "  b         f           \n";
        txtTree += " / \\       / \\        \n";
        txtTree += "a   c     e   g         \n";
        txtTree += "</pre>";
        Set_Comments( txtTree );
        Set_Comments( "FindNode( 'g' )" );

        BinarySearchTree<char, string> tree;
        tree.m_ptrRoot = new BinarySearchTreeNode<char,string>( 'd', "dates" );

        tree.m_ptrRoot->ptrLeft = new BinarySearchTreeNode<char,string>( 'b', "banana" );
        tree.m_ptrRoot->ptrLeft->ptrLeft = new BinarySearchTreeNode<char,string>( 'a', "apple" );
        tree.m_ptrRoot->ptrLeft->ptrRight = new BinarySearchTreeNode<char,string>( 'c', "carrot" );

        tree.m_ptrRoot->ptrRight = new BinarySearchTreeNode<char,string>( 'f', "figs" );
        tree.m_ptrRoot->ptrRight->ptrLeft = new BinarySearchTreeNode<char,string>( 'e', "eggplant" );
        tree.m_ptrRoot->ptrRight->ptrRight = new BinarySearchTreeNode<char,string>( 'g', "grapefruit" );

        BinarySearchTreeNode<char, string>* findNode = tree.FindNode( 'g' );

        if ( findNode == nullptr ) { Set_Comments( "findNode was nullptr" );      TestFail(); }
        else if ( !Set_Outputs( "findNode's key",   'g',     findNode->key ) )           { TestFail(); }
        else if ( !Set_Outputs( "findNode's data",  "grapefruit", findNode->data ) )     { TestFail(); }
        else                                                                             { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "Fill a tree, use FindNode() for item not in tree ('z'). Result should be nullptr." );

        string txtTree = "<pre>";
        txtTree += "       d                \n";
        txtTree += "    /     \\            \n";
        txtTree += "  b         f           \n";
        txtTree += " / \\       / \\        \n";
        txtTree += "a   c     e   g         \n";
        txtTree += "</pre>";
        Set_Comments( txtTree );
        Set_Comments( "FindNode( 'z' )" );

        BinarySearchTree<char, string> tree;
        tree.m_ptrRoot = new BinarySearchTreeNode<char,string>( 'd', "dates" );

        tree.m_ptrRoot->ptrLeft = new BinarySearchTreeNode<char,string>( 'b', "banana" );
        tree.m_ptrRoot->ptrLeft->ptrLeft = new BinarySearchTreeNode<char,string>( 'a', "apple" );
        tree.m_ptrRoot->ptrLeft->ptrRight = new BinarySearchTreeNode<char,string>( 'c', "carrot" );

        tree.m_ptrRoot->ptrRight = new BinarySearchTreeNode<char,string>( 'f', "figs" );
        tree.m_ptrRoot->ptrRight->ptrLeft = new BinarySearchTreeNode<char,string>( 'e', "eggplant" );
        tree.m_ptrRoot->ptrRight->ptrRight = new BinarySearchTreeNode<char,string>( 'g', "grapefruit" );

        BinarySearchTreeNode<char, string>* findNode = tree.FindNode( 'z' );


        if ( findNode != nullptr ) { Set_Comments( "findNode was NOT nullptr; should return nullptr for item not in tree!" );      TestFail(); }
        else                                                                        { TestPass(); }


        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}

int BinarySearchTreeTester::Test_GetInOrder()
{
    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_GetInOrder", 3 );
    StartTestSet( "Test_GetInOrder", { "RecursiveGetInOrder" } );
    ostringstream oss;

    string functionName = "BinarySearchTree::RecursiveGetInOrder";
    StartTest( "0a. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; stringstream stream; /* FUNCTION: */ tree.RecursiveGetInOrder( tree.m_ptrRoot, stream ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    functionName = "BinarySearchTree::GetInOrder";
    StartTest( "0b. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; /* FUNCTION: */ tree.GetInOrder(); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "Add things to a tree and then check the InOrder traversal." );

        string txtTree = "<pre>";
        txtTree += "       d                \n";
        txtTree += "    /     \\            \n";
        txtTree += "  b         f           \n";
        txtTree += " / \\       / \\        \n";
        txtTree += "a   c     e   g         \n";
        txtTree += "</pre>";
        Set_Comments( txtTree );
        Set_Comments( "InOrder traversal: LEFT, SELF, RIGHT" );

        BinarySearchTree<char, string> tree;
        tree.m_ptrRoot = new BinarySearchTreeNode<char,string>( 'd', "dates" );
        tree.m_ptrRoot->ptrLeft = new BinarySearchTreeNode<char,string>( 'b', "banana" );
        tree.m_ptrRoot->ptrLeft->ptrLeft = new BinarySearchTreeNode<char,string>( 'a', "apple" );
        tree.m_ptrRoot->ptrLeft->ptrRight = new BinarySearchTreeNode<char,string>( 'c', "carrot" );
        tree.m_ptrRoot->ptrRight = new BinarySearchTreeNode<char,string>( 'f', "figs" );
        tree.m_ptrRoot->ptrRight->ptrLeft = new BinarySearchTreeNode<char,string>( 'e', "eggplant" );
        tree.m_ptrRoot->ptrRight->ptrRight = new BinarySearchTreeNode<char,string>( 'g', "grapefruit" );

        if ( !Set_Outputs( "GetInOrder()", "abcdefg", tree.GetInOrder() ) )     { TestFail(); }
        else                                                                    { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}

int BinarySearchTreeTester::Test_GetPreOrder()
{
    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_GetPreOrder", 3 );
    StartTestSet( "Test_GetPreOrder", { "RecursiveGetPreOrder" } );
    ostringstream oss;

    string functionName = "BinarySearchTree::RecursivePush";
    StartTest( "0a. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; stringstream stream; /* FUNCTION: */ tree.RecursiveGetPreOrder( tree.m_ptrRoot, stream ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    functionName = "BinarySearchTree::GetPreOrder";
    StartTest( "0b. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; /* FUNCTION: */ tree.GetPreOrder(); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "Add things to a tree and then check the PreOrder traversal." );

        string txtTree = "<pre>";
        txtTree += "       d                \n";
        txtTree += "    /     \\            \n";
        txtTree += "  b         f           \n";
        txtTree += " / \\       / \\        \n";
        txtTree += "a   c     e   g         \n";
        txtTree += "</pre>";
        Set_Comments( txtTree );
        Set_Comments( "PreOrder traversal: SELF, LEFT, RIGHT" );

        BinarySearchTree<char, string> tree;
        tree.m_ptrRoot = new BinarySearchTreeNode<char,string>( 'd', "dates" );
        tree.m_ptrRoot->ptrLeft = new BinarySearchTreeNode<char,string>( 'b', "banana" );
        tree.m_ptrRoot->ptrLeft->ptrLeft = new BinarySearchTreeNode<char,string>( 'a', "apple" );
        tree.m_ptrRoot->ptrLeft->ptrRight = new BinarySearchTreeNode<char,string>( 'c', "carrot" );
        tree.m_ptrRoot->ptrRight = new BinarySearchTreeNode<char,string>( 'f', "figs" );
        tree.m_ptrRoot->ptrRight->ptrLeft = new BinarySearchTreeNode<char,string>( 'e', "eggplant" );
        tree.m_ptrRoot->ptrRight->ptrRight = new BinarySearchTreeNode<char,string>( 'g', "grapefruit" );

        if ( !Set_Outputs( "GetPreOrder()", "dbacfeg", tree.GetPreOrder() ) )     { TestFail(); }
        else                                                                      { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}

int BinarySearchTreeTester::Test_GetPostOrder()
{
    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_GetPostOrder", 3 );
    StartTestSet( "Test_GetPostOrder", { "RecursiveGetPostOrder" } );
    ostringstream oss;

    string functionName = "BinarySearchTree::RecursiveGetPostOrder";
    StartTest( "0a. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; stringstream stream; /* FUNCTION: */ tree.RecursiveGetPostOrder( tree.m_ptrRoot, stream ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    functionName = "BinarySearchTree::GetPostOrder";
    StartTest( "0b. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; /* FUNCTION: */ tree.GetPostOrder(); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "Add things to a tree and then check the PostOrder traversal." );

        string txtTree = "<pre>";
        txtTree += "       d                \n";
        txtTree += "    /     \\            \n";
        txtTree += "  b         f           \n";
        txtTree += " / \\       / \\        \n";
        txtTree += "a   c     e   g         \n";
        txtTree += "</pre>";
        Set_Comments( txtTree );
        Set_Comments( "PostOrder traversal: LEFT, RIGHT, SELF" );

        BinarySearchTree<char, string> tree;
        tree.m_ptrRoot = new BinarySearchTreeNode<char,string>( 'd', "dates" );
        tree.m_ptrRoot->ptrLeft = new BinarySearchTreeNode<char,string>( 'b', "banana" );
        tree.m_ptrRoot->ptrLeft->ptrLeft = new BinarySearchTreeNode<char,string>( 'a', "apple" );
        tree.m_ptrRoot->ptrLeft->ptrRight = new BinarySearchTreeNode<char,string>( 'c', "carrot" );
        tree.m_ptrRoot->ptrRight = new BinarySearchTreeNode<char,string>( 'f', "figs" );
        tree.m_ptrRoot->ptrRight->ptrLeft = new BinarySearchTreeNode<char,string>( 'e', "eggplant" );
        tree.m_ptrRoot->ptrRight->ptrRight = new BinarySearchTreeNode<char,string>( 'g', "grapefruit" );

        if ( !Set_Outputs( "GetPostOrder()", "acbegfd", tree.GetPostOrder() ) )     { TestFail(); }
        else                                                                        { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}

int BinarySearchTreeTester::Test_GetMaxKey()
{
    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_GetMaxKey", 3 );
    StartTestSet( "Test_GetMaxKey", { "RecursiveGetMax" } );
    ostringstream oss;

    string functionName = "BinarySearchTree::RecursiveGetMax";
    StartTest( "0a. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; /* FUNCTION: */ tree.RecursiveGetMax( tree.m_ptrRoot ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    functionName = "BinarySearchTree::GetMaxKey";
    StartTest( "0b. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; /* FUNCTION: */ tree.GetMaxKey(); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "Create a tree and then get the max key." );

        string txtTree = "<pre>";
        txtTree += "       d                \n";
        txtTree += "    /     \\            \n";
        txtTree += "  b         f           \n";
        txtTree += " / \\       / \\        \n";
        txtTree += "a   c     e   g         \n";
        txtTree += "</pre>";
        Set_Comments( txtTree );
        Set_Comments( "Max key: Keep traversing RIGHT until there are no more nodes." );

        BinarySearchTree<char, string> tree;
        tree.m_ptrRoot = new BinarySearchTreeNode<char,string>( 'd', "dates" );
        tree.m_ptrRoot->ptrLeft = new BinarySearchTreeNode<char,string>( 'b', "banana" );
        tree.m_ptrRoot->ptrLeft->ptrLeft = new BinarySearchTreeNode<char,string>( 'a', "apple" );
        tree.m_ptrRoot->ptrLeft->ptrRight = new BinarySearchTreeNode<char,string>( 'c', "carrot" );
        tree.m_ptrRoot->ptrRight = new BinarySearchTreeNode<char,string>( 'f', "figs" );
        tree.m_ptrRoot->ptrRight->ptrLeft = new BinarySearchTreeNode<char,string>( 'e', "eggplant" );
        tree.m_ptrRoot->ptrRight->ptrRight = new BinarySearchTreeNode<char,string>( 'g', "grapefruit" );

        if ( !Set_Outputs( "GetMaxKey()", 'g', tree.GetMaxKey() ) )     { TestFail(); }
        else                                                            { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}

int BinarySearchTreeTester::Test_GetMinKey()
{
    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_GetMinKey", 3 );
    StartTestSet( "Test_GetMinKey", { "RecursiveGetMin" } );
    ostringstream oss;

    string functionName = "BinarySearchTree::RecursiveGetMin";
    StartTest( "0a. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; /* FUNCTION: */ tree.RecursiveGetMin( tree.m_ptrRoot ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    functionName = "BinarySearchTree::GetMinKey";
    StartTest( "0b. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; /* FUNCTION: */ tree.GetMinKey(); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "Create a tree and then get the min key." );

        string txtTree = "<pre>";
        txtTree += "       d                \n";
        txtTree += "    /     \\            \n";
        txtTree += "  b         f           \n";
        txtTree += " / \\       / \\        \n";
        txtTree += "a   c     e   g         \n";
        txtTree += "</pre>";
        Set_Comments( txtTree );
        Set_Comments( "Max key: Keep traversing LEFT until there are no more nodes." );

        BinarySearchTree<char, string> tree;
        tree.m_ptrRoot = new BinarySearchTreeNode<char,string>( 'd', "dates" );
        tree.m_ptrRoot->ptrLeft = new BinarySearchTreeNode<char,string>( 'b', "banana" );
        tree.m_ptrRoot->ptrLeft->ptrLeft = new BinarySearchTreeNode<char,string>( 'a', "apple" );
        tree.m_ptrRoot->ptrLeft->ptrRight = new BinarySearchTreeNode<char,string>( 'c', "carrot" );
        tree.m_ptrRoot->ptrRight = new BinarySearchTreeNode<char,string>( 'f', "figs" );
        tree.m_ptrRoot->ptrRight->ptrLeft = new BinarySearchTreeNode<char,string>( 'e', "eggplant" );
        tree.m_ptrRoot->ptrRight->ptrRight = new BinarySearchTreeNode<char,string>( 'g', "grapefruit" );

        if ( !Set_Outputs( "GetMinKey()", 'a', tree.GetMinKey() ) )     { TestFail(); }
        else                                                            { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}

int BinarySearchTreeTester::Test_GetCount()
{
    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_GetCount", 3 );
    StartTestSet( "Test_GetCount", {} ); //{ "Push" } );
    ostringstream oss;

    string functionName = "BinarySearchTree::GetCount";
    StartTest( "0a. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; /* FUNCTION: */ tree.GetCount(); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "Create an empty tree and get the node count." );
        BinarySearchTree<char, string> tree;
        if ( !Set_Outputs( "GetCount()", 0, tree.GetCount() ) )             { TestFail(); }
        else                                                                { TestPass(); }
        FinishTest();
    } /* TEST END **************************************************************/

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "Create a tree, set node count to 1, get the node count." );

        BinarySearchTree<char, string> tree;
        tree.m_nodeCount = 1;

        if ( !Set_Outputs( "GetCount()", 1, tree.GetCount() ) )             { TestFail(); }
        else                                                                { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}

int BinarySearchTreeTester::Test_GetHeight()
{
    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_GetHeight", 3 );
    StartTestSet( "Test_GetHeight", { "RecursiveGetHeight" } );
    ostringstream oss;

    string functionName = "BinarySearchTree::RecursiveGetHeight";
    StartTest( "0a. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; /* FUNCTION: */ tree.RecursiveGetHeight( tree.m_ptrRoot ); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    functionName = "BinarySearchTree::GetHeight";
    StartTest( "0b. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   BinarySearchTree<char, string> tree; /* FUNCTION: */ tree.GetHeight(); }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "Create tree with one node (root), check height." );
        BinarySearchTree<char, string> tree;
        tree.m_ptrRoot = new BinarySearchTreeNode<char,string>( 'a', "apple" );
        Set_Comments( "Height of a node is the # of EDGES from the node to the deepest leaf." );

        if ( !Set_Outputs( "GetHeight()", 0, tree.GetHeight() ) )     { TestFail(); }
        else                                                          { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    {
        /* TEST BEGIN ************************************************************/
        StartTest( "Create tree with several nodes, check height." );

        BinarySearchTree<char, string> tree;
        tree.m_ptrRoot = new BinarySearchTreeNode<char,string>( 'd', "dates" );
        tree.m_ptrRoot->ptrLeft = new BinarySearchTreeNode<char,string>( 'b', "banana" );
        tree.m_ptrRoot->ptrRight = new BinarySearchTreeNode<char,string>( 'g', "grapefruit" );
        tree.m_ptrRoot->ptrRight->ptrLeft = new BinarySearchTreeNode<char,string>( 'e', "elderberry" );
        tree.m_ptrRoot->ptrRight->ptrLeft->ptrRight = new BinarySearchTreeNode<char,string>( 'f', "elderberry" );

        string txtTree = "<pre>";
        txtTree += "       d                \n";
        txtTree += "    /     \\            \n";
        txtTree += "  b         g           \n";
        txtTree += "           /            \n";
        txtTree += "          e             \n";
        txtTree += "           \\           \n";
        txtTree += "            f           \n";
        txtTree += "</pre>";
        Set_Comments( txtTree );
        Set_Comments( "Height of a node is the # of EDGES from the node to the deepest leaf." );

        if ( !Set_Outputs( "GetHeight()", 3, tree.GetHeight() ) )     { TestFail(); }
        else                                                          { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}


//int BinarySearchTreeTester::Test_FindParentOfNode()
//{
//    Logger::OutHighlight( "TEST SET BEGIN", "BinarySearchTreeTester::Test_FindParentOfNode", 3 );
//    StartTestSet( "Test_FindParentOfNode", { "RecursiveFindNode", "Push" } );
//    ostringstream oss;
//
//    { /* TEST BEGIN ************************************************************/
//        string functionName = "BinarySearchTree::FindParentOfNode";
//        StartTest( "1. Check if " + functionName + " has been implemented yet..." );
//
//        bool prereqsImplemented = true;
//        Set_ExpectedOutput( functionName, string( "Implemented" ) );
//        try
//        {
//            BinarySearchTree<char, string> tree;
//            tree.FindParentOfNode( 'a' );
//        }
//        catch ( NotImplementedException& ex )
//        {
//            Set_Comments( ex.what() );
//            prereqsImplemented = false;
//        }
//
//        if ( prereqsImplemented )
//        {
//            Set_ActualOutput( functionName, string( "Implemented" ) );
//            TestPass();
//            FinishTest();
//        }
//        else
//        {
//            Set_ActualOutput( functionName, string( "Not implemented" ) );
//            TestFail();
//            FinishTest();
//            FinishTestSet();
//            return TestResult();
//        }
//    } /* TEST END **************************************************************/
//
//    { /* TEST BEGIN ************************************************************/
//        StartTest( "Fill a tree, use FindNode() to find node in the tree." );
//
//        Set_Comments( "Push( 'd', \"dates\" )" );
//        Set_Comments( "Push( 'b', \"banana\" )" );
//        Set_Comments( "Push( 'f', \"figs\" )" );
//        Set_Comments( "Push( 'a', \"apple\" )" );
//        Set_Comments( "Push( 'c', \"cranberry\" )" );
//        Set_Comments( "Push( 'e', \"elderberry\" )" );
//        Set_Comments( "Push( 'g', \"grapefruit\" )" );
//
//        string txtTree = "<pre>";
//        txtTree += "       d                \n";
//        txtTree += "    /     \\            \n";
//        txtTree += "  b         f           \n";
//        txtTree += " / \\       / \\        \n";
//        txtTree += "a   c     e   g         \n";
//        txtTree += "</pre>";
//        Set_Comments( txtTree );
//        Set_Comments( "FindNode( 'g' )" );
//
//        BinarySearchTree<char, string> tree;
//        tree.Push( 'd', "dates" );
//        tree.Push( 'b', "banana" );
//        tree.Push( 'f', "figs" );
//        tree.Push( 'a', "apple" );
//        tree.Push( 'c', "cranberry" );
//        tree.Push( 'e', "elderberry" );
//        tree.Push( 'g', "grapefruit" );
//
//        char expectedKey = 'g';
//        string expectedData = "grapefruit";
//
//        Set_ExpectedOutput  ( "found node address",  string("NOT nullptr") );
//        Set_ExpectedOutput  ( "found node key",  char(expectedKey) );
//        Set_ExpectedOutput  ( "found node data", string(expectedData) );
//
//        char actualKey = '-';
//        string actualData = "-";
//
//        Node<char, string>* findNode = tree.FindNode( 'g' );
//
//        if ( findNode == nullptr )
//        {
//            Set_ActualOutput  ( "found node address",  string("nullptr") );
//        }
//        else
//        {
//            actualKey = findNode->key;
//            actualData = findNode->data;
//
//            Set_ActualOutput    ( "found node key", actualKey );
//            Set_ActualOutput    ( "found node data", actualData );
//        }
//
//        if ( findNode == nullptr )
//        {
//            TestFail();
//            Set_Comments( "FindNode returned nullptr!" );
//        }
//        else if ( actualKey != expectedKey )
//        {
//            TestFail();
//            Set_Comments( "FindNode key was wrong!" );
//        }
//        else if ( actualData != expectedData )
//        {
//            TestFail();
//            Set_Comments( "FindNode data was wrong!" );
//        }
//        else
//        {
//            TestPass();
//        }
//
//        FinishTest();
//    } /* TEST END **************************************************************/
//
//    { /* TEST BEGIN ************************************************************/
//        StartTest( "Fill a tree, use FindNode() for item not in tree. Result should be nullptr." );
//
//        Set_Comments( "Push( 'd', \"dates\" )" );
//        Set_Comments( "Push( 'b', \"banana\" )" );
//        Set_Comments( "Push( 'f', \"figs\" )" );
//        Set_Comments( "Push( 'a', \"apple\" )" );
//        Set_Comments( "Push( 'c', \"cranberry\" )" );
//        Set_Comments( "Push( 'e', \"elderberry\" )" );
//        Set_Comments( "Push( 'g', \"grapefruit\" )" );
//
//        string txtTree = "<pre>";
//        txtTree += "       d                \n";
//        txtTree += "    /     \\            \n";
//        txtTree += "  b         f           \n";
//        txtTree += " / \\       / \\        \n";
//        txtTree += "a   c     e   g         \n";
//        txtTree += "</pre>";
//        Set_Comments( txtTree );
//        Set_Comments( "FindNode( 'z' )" );
//
//        BinarySearchTree<char, string> tree;
//        tree.Push( 'd', "dates" );
//        tree.Push( 'b', "banana" );
//        tree.Push( 'f', "figs" );
//        tree.Push( 'a', "apple" );
//        tree.Push( 'c', "cranberry" );
//        tree.Push( 'e', "elderberry" );
//        tree.Push( 'g', "grapefruit" );
//
//        Set_ExpectedOutput  ( "found node address",  string("nullptr") );
//
//        Node<char, string>* findNode = tree.FindNode( 'z' );
//
//        if ( findNode == nullptr )
//        {
//            Set_ActualOutput  ( "found node address",  string("nullptr") );
//        }
//        else
//        {
//            oss << findNode;
//            Set_ActualOutput    ( "found node address", oss.str() );
//        }
//
//        if ( findNode != nullptr )
//        {
//            TestFail();
//            Set_Comments( "FindNode was supposd to return nullptr!" );
//        }
//        else
//        {
//            TestPass();
//        }
//
//        FinishTest();
//    } /* TEST END **************************************************************/
//
//    FinishTestSet();
//    return TestResult();
//}



//int BinarySearchTreeTester::Test_Delete()
//{
//    StartTestSet( "Test_Delete", { } );
//    ostringstream oss;
//
//    { /* TEST BEGIN ************************************************************/
//        StartTest( "DESCRIPTION" );
//
//        int expectedResult = 0;
//        int actualResult = 0;
//
//        Set_ExpectedOutput  ( "ITEM", expectedResult );
//        Set_ActualOutput    ( "ITEM", actualResult );
//
//        if ( actualResult != expectedResult )
//        {
//            TestFail();
//        }
//        else
//        {
//            TestPass();
//        }
//
//        FinishTest();
//    } /* TEST END **************************************************************/
//
//    FinishTestSet();
//    return TestResult();
//}

#endif
