#ifndef _TESTER_HPP
#define _TESTER_HPP

#include <iostream>
#include <string>
using namespace std;

#include "LinkedList.hpp"
#include "../../cutest/TesterBase.hpp"
#include "../../Utilities/StringUtil.hpp"
#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/StructureFullException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/NullptrException.hpp"

class LinkedListTester : public TesterBase
{
public:
    LinkedListTester()
        : TesterBase( "test_result_linked_list.html" )
    {
        AddTest(TestListItem("Test_NodeConstructor",         bind(&LinkedListTester::Test_NodeConstructor, this)));
        AddTest(TestListItem("Test_Constructor",             bind(&LinkedListTester::Test_Constructor, this)));
        AddTest(TestListItem("Test_GetFront",                bind(&LinkedListTester::Test_GetFront, this)));
        AddTest(TestListItem("Test_GetBack",                 bind(&LinkedListTester::Test_GetBack, this)));
        AddTest(TestListItem("Test_GetAt",                   bind(&LinkedListTester::Test_GetAt, this)));
        AddTest(TestListItem("Test_SubscriptOperator",       bind(&LinkedListTester::Test_SubscriptOperator, this)));
        AddTest(TestListItem("Test_IsEmpty",                 bind(&LinkedListTester::Test_IsEmpty, this)));
        AddTest(TestListItem("Test_Size",                    bind(&LinkedListTester::Test_Size, this)));
        AddTest(TestListItem("Test_PushFront",               bind(&LinkedListTester::Test_PushFront, this)));
        AddTest(TestListItem("Test_PushBack",                bind(&LinkedListTester::Test_PushBack, this)));
        AddTest(TestListItem("Test_PushAt",                  bind(&LinkedListTester::Test_PushAt, this)));
        AddTest(TestListItem("Test_PopFront",                bind(&LinkedListTester::Test_PopFront, this)));
        AddTest(TestListItem("Test_PopBack",                 bind(&LinkedListTester::Test_PopBack, this)));
        AddTest(TestListItem("Test_PopAt",                   bind(&LinkedListTester::Test_PopAt, this)));
        AddTest(TestListItem("Test_Clear",                   bind(&LinkedListTester::Test_Clear, this)));
    }

    virtual ~LinkedListTester() { }

private:
    int Test_NodeConstructor();
    int Test_Constructor();
    int Test_Clear();
    int Test_PushFront();
    int Test_PushBack();
    int Test_PushAt();
    int Test_PopFront();
    int Test_PopBack();
    int Test_PopAt();
    int Test_GetFront();
    int Test_GetBack();
    int Test_GetAt();
    int Test_SubscriptOperator();
    int Test_IsEmpty();
    int Test_Size();
};

int LinkedListTester::Test_NodeConstructor()
{
    string functionName = "Node Constructor";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { } );
    ostringstream oss;

    StartTest( "1. Check initial member variable values" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        Set_Comments( "When a new Node is created, its m_ptrNext and m_ptrPrev pointers should point to nullptr." );

        DoublyLinkedListNode<int> myList;

        oss << myList.m_ptrNext;
        Set_ExpectedOutput  ( "m_ptrNext is nullptr" );
        Set_ActualOutput    ( "m_ptrNext", oss.str() );

        oss.str("");
        oss.clear();
        oss << myList.m_ptrPrev;
        Set_ExpectedOutput  ( "m_ptrPrev is nullptr" );
        Set_ActualOutput    ( "m_ptrPrev", oss.str() );

        if      ( myList.m_ptrNext != nullptr )                         { TestFail(); }
        else if ( myList.m_ptrPrev != nullptr )                         { TestFail(); }
        else                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_Constructor()
{
    string functionName = "LinkedList Constructor";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { "IsEmpty" } );
    ostringstream oss;

    StartTest( "0. Check if function/prereqs " + functionName + " are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    StartTest( "1. Check initial member variable values" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        Set_Comments( "When a new LinkedList is created, its pointers should be nullptr and m_itemCount should be 0." );

        LinkedList<int> myList;

        oss << myList.m_ptrFirst;
        Set_ExpectedOutput  ( "m_ptrFirst is nullptr" );
        Set_ActualOutput    ( "m_ptrFirst", oss.str() );

        oss.str("");
        oss.clear();
        oss << myList.m_ptrLast;
        Set_ExpectedOutput  ( "m_ptrLast is nullptr" );
        Set_ActualOutput    ( "m_ptrLast", oss.str() );

        if      ( myList.m_ptrFirst != nullptr )                            { TestFail(); }
        else if ( myList.m_ptrLast != nullptr )                             { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 0, myList.m_itemCount ) )    { TestFail(); }
        else                                                                { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_Clear()
{
    string functionName = "Clear";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ arr.Clear(); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "Does m_itemCount = 0 after Clear? Are the pointers reset?" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;
        ll.m_ptrFirst = new DoublyLinkedListNode<string>;
        ll.m_ptrLast = ll.m_ptrFirst;
        ll.m_ptrFirst->m_data = "A";
        ll.m_itemCount = 1;
        ostringstream oss;

        ll.Clear();

        oss << ll.m_ptrFirst;
        Set_ExpectedOutput  ( "m_ptrFirst is nullptr" );
        Set_ActualOutput    ( "m_ptrFirst", oss.str() );

        oss.str("");
        oss.clear();
        oss << ll.m_ptrLast;
        Set_ExpectedOutput  ( "m_ptrLast is nullptr" );
        Set_ActualOutput    ( "m_ptrLast", oss.str() );

        if      ( !Set_Outputs( "m_itemCount", 0, ll.m_itemCount ) )        { TestFail(); }
        else if ( ll.m_ptrFirst != nullptr )                                { TestFail(); }
        else if ( ll.m_ptrLast != nullptr )                                 { TestFail(); }
        else                                                                { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_PushFront()
{
    string functionName = "PushFront";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ arr.PushFront( 1 ); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "When item is added to empty list, m_ptrFirst and m_ptrLast should point at it." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;
        ll.PushFront( "cheeseburger" );

        ostringstream oss;

        oss << ll.m_ptrFirst;
        Set_ExpectedOutput  ( "m_ptrFirst is not nullptr" );
        Set_ActualOutput    ( "m_ptrFirst", oss.str() );

        oss.str("");
        oss.clear();
        oss << ll.m_ptrLast;
        Set_ExpectedOutput  ( "m_ptrLast is not nullptr" );
        Set_ActualOutput    ( "m_ptrLast", oss.str() );

        if      ( ll.m_ptrFirst == nullptr )                                                    { TestFail(); }
        else if ( ll.m_ptrLast == nullptr )                                                     { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 1, ll.m_itemCount ) )                            { TestFail(); }
        else if ( !Set_Outputs( "m_ptrFirst->data", "cheeseburger", ll.m_ptrFirst->m_data ) )   { TestFail(); }
        else                                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "When two items are added to an empty list, one should be pointed to by m_ptrFirst, and the other should be pointed to by m_ptrLast." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        Set_Comments( "Also, when two items are added to an empty list, the two items should point at each other." );
        LinkedList<string> ll;
        ll.PushFront( "one" );
        ll.PushFront( "two" );

        if ( !Set_Outputs( "m_itemCount", 2, ll.m_itemCount ) )                         { TestFail(); }
        else if ( !Set_Outputs( "m_ptrFirst->data", "two", ll.m_ptrFirst->m_data ) )    { TestFail(); }
        else if ( !Set_Outputs( "m_ptrLast->data", "one", ll.m_ptrLast->m_data ) )      { TestFail(); }
        else if ( ll.m_ptrFirst->m_ptrNext != ll.m_ptrLast )
        {
            ostringstream oss;
            oss << ll.m_ptrFirst->m_ptrNext;
            Set_ExpectedOutput( "m_ptrFirst->m_ptrNext is m_ptrLast" );
            Set_ActualOutput( "m_ptrFirst->m_ptrNext", oss.str() );
            TestFail();
        }
        else if ( ll.m_ptrLast->m_ptrPrev != ll.m_ptrFirst )
        {
            ostringstream oss;
            oss << ll.m_ptrLast->m_ptrPrev;
            Set_ExpectedOutput( "m_ptrLast->m_ptrPrev is m_ptrFirst" );
            Set_ActualOutput( "m_ptrLast->m_ptrPrev", oss.str() );
            TestFail();
        }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_PushBack()
{
    string functionName = "PushBack";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ arr.PushBack( 1 ); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    StartTest( "When item is added to empty list, m_ptrFirst and m_ptrLast should point at it." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;
        ll.PushBack( "cheeseburger" );

        ostringstream oss;

        oss << ll.m_ptrFirst;
        Set_ExpectedOutput  ( "m_ptrFirst is not nullptr" );
        Set_ActualOutput    ( "m_ptrFirst", oss.str() );

        oss.str("");
        oss.clear();
        oss << ll.m_ptrLast;
        Set_ExpectedOutput  ( "m_ptrLast is not nullptr" );
        Set_ActualOutput    ( "m_ptrLast", oss.str() );

        if      ( ll.m_ptrFirst == nullptr )                                                    { TestFail(); }
        else if ( ll.m_ptrLast == nullptr )                                                     { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 1, ll.m_itemCount ) )                            { TestFail(); }
        else if ( !Set_Outputs( "m_ptrFirst->data", "cheeseburger", ll.m_ptrFirst->m_data ) )   { TestFail(); }
        else                                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "When two items are added to an empty list, one should be pointed to by m_ptrFirst, and the other should be pointed to by m_ptrLast." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        Set_Comments( "Also, when two items are added to an empty list, the two items should point at each other." );
        LinkedList<string> ll;
        ll.PushBack( "one" );
        ll.PushBack( "two" );

        if ( !Set_Outputs( "m_itemCount", 2, ll.m_itemCount ) )                         { TestFail(); }
        else if ( !Set_Outputs( "m_ptrFirst->data", "one", ll.m_ptrFirst->m_data ) )    { TestFail(); }
        else if ( !Set_Outputs( "m_ptrLast->data", "two", ll.m_ptrLast->m_data ) )      { TestFail(); }
        else if ( ll.m_ptrFirst->m_ptrNext != ll.m_ptrLast )
        {
            ostringstream oss;
            oss << ll.m_ptrFirst->m_ptrNext;
            Set_ExpectedOutput( "m_ptrFirst->m_ptrNext is m_ptrLast" );
            Set_ActualOutput( "m_ptrFirst->m_ptrNext", oss.str() );
            TestFail();
        }
        else if ( ll.m_ptrLast->m_ptrPrev != ll.m_ptrFirst )
        {
            ostringstream oss;
            oss << ll.m_ptrLast->m_ptrPrev;
            Set_ExpectedOutput( "m_ptrLast->m_ptrPrev is m_ptrFirst" );
            Set_ActualOutput( "m_ptrLast->m_ptrPrev", oss.str() );
            TestFail();
        }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_PushAt()
{
    string functionName = "PushAt";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ arr.PushBack( 1 ); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "Added two items, use PushAt to insert into the middle. Check pointers." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;
        ll.m_ptrFirst = new DoublyLinkedListNode<string>;
        ll.m_ptrLast = new DoublyLinkedListNode<string>;

        ll.m_ptrFirst->m_data = "A";
        ll.m_ptrLast->m_data = "T";

        ll.m_ptrFirst->m_ptrNext = ll.m_ptrLast;
        ll.m_ptrLast->m_ptrPrev = ll.m_ptrFirst;

        ll.m_itemCount = 2;

        Set_Comments( "Order before PushAt" );
        Set_Comments( "First item: " + ll.m_ptrFirst->m_data );
        Set_Comments( "Last item:  " + ll.m_ptrLast->m_data );

        Set_Comments( "Expected order after PushAt( \"R\", 1 )" );
        Set_Comments( "First item:  A" );
        Set_Comments( "Second item: R" );
        Set_Comments( "Last item:   T" );

        ll.PushAt( "R", 1 );

        if ( !Set_Outputs( "m_itemCount", 3, ll.m_itemCount ) )                                             { TestFail(); }
        else if ( !Set_Outputs( "m_ptrFirst->data", "A", ll.m_ptrFirst->m_data ) )                          { TestFail(); }
        else if ( !Set_Outputs( "m_ptrLast->data", "T", ll.m_ptrLast->m_data ) )                            { TestFail(); }
        else if ( !Set_Outputs( "m_ptrFirst->m_ptrNext->data", "R", ll.m_ptrFirst->m_ptrNext->m_data ) )    { TestFail(); }
        else if ( !Set_Outputs( "m_ptrLast->m_ptrPrev->data",  "R", ll.m_ptrLast->m_ptrPrev->m_data ) )     { TestFail(); }
        else                                                                                                { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_PopFront()
{
    string functionName = "PopFront";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ arr.PopFront(); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "Popping the last item should reset m_ptrFirst and m_ptrLast to nullptr and set m_itemCount to 0." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;
        ll.m_itemCount = 1;
        ll.m_ptrFirst = new DoublyLinkedListNode<string>;
        ll.m_ptrLast = ll.m_ptrFirst;
        ll.PopFront();

        ostringstream oss;

        oss << ll.m_ptrFirst;
        Set_ExpectedOutput  ( "m_ptrFirst is nullptr" );
        Set_ActualOutput    ( "m_ptrFirst", oss.str() );

        oss.clear();
        oss << ll.m_ptrLast;
        Set_ExpectedOutput  ( "m_ptrLast is nullptr" );
        Set_ActualOutput    ( "m_ptrLast", oss.str() );

        if      ( ll.m_ptrFirst != nullptr )                                                    { TestFail(); }
        else if ( ll.m_ptrLast != nullptr )                                                     { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 0, ll.m_itemCount ) )                            { TestFail(); }
        else                                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "PopFront on a list with 2+ elements should adjust m_ptrFirst and m_itemCount. " ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;
        ll.m_ptrFirst = new DoublyLinkedListNode<string>;
        ll.m_ptrFirst->m_data = "A";

        ll.m_ptrLast = new DoublyLinkedListNode<string>;
        ll.m_ptrLast->m_data = "B";

        ll.m_ptrFirst->m_ptrNext = ll.m_ptrLast;
        ll.m_ptrLast->m_ptrPrev = ll.m_ptrFirst;

        ll.m_itemCount = 2;

        ll.PopFront();

        ostringstream oss;

        oss << ll.m_ptrFirst;
        Set_ExpectedOutput  ( "m_ptrFirst is m_ptrLast" );
        Set_ActualOutput    ( "m_ptrFirst", oss.str() );

        oss.clear();
        oss << ll.m_ptrLast;
        Set_ExpectedOutput  ( "m_ptrLast is m_ptrLast" );
        Set_ActualOutput    ( "m_ptrLast", oss.str() );

        if      ( ll.m_ptrFirst != ll.m_ptrLast )                                               { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 1, ll.m_itemCount ) )                            { TestFail(); }
        else                                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "Pushing Back cd1, cd2, cd3, a PopFront should leave cd2 and cd3." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;

        auto node1 = new DoublyLinkedListNode<string>;
        node1->m_data = "cd1";

        auto node2 = new DoublyLinkedListNode<string>;
        node2->m_data = "cd2";
        node1->m_ptrNext = node2;
        node2->m_ptrPrev = node1;

        auto node3 = new DoublyLinkedListNode<string>;
        node3->m_data = "cd3";
        node2->m_ptrNext = node3;
        node3->m_ptrPrev = node2;

        ll.m_ptrFirst = node1;
        ll.m_ptrLast = node3;
        ll.m_itemCount = 3;

        Set_Comments( "Item at position 0: " + node1->m_data );
        Set_Comments( "Item at position 1: " + node2->m_data );
        Set_Comments( "Item at position 2: " + node3->m_data );

        ll.PopFront();

        if      ( !Set_Outputs( "m_itemCount", 2, ll.m_itemCount ) )             { TestFail(); }
        else if ( ll.m_ptrFirst != node2 )
        {
            Set_ExpectedOutput( "m_ptrFirst points to " + string( node2->m_data ) );
            Set_ActualOutput( "m_ptrFirst points to " + string( ll.m_ptrFirst->m_data ) );
            TestFail();
        }
        else if ( ll.m_ptrLast != node3 )
        {
            Set_ExpectedOutput( "m_ptrLast points to " + string( node3->m_data ) );
            Set_ActualOutput( "m_ptrLast points to " + string( ll.m_ptrLast->m_data ) );
            TestFail();
        }
        else
        {
            Set_ExpectedOutput( "m_ptrFirst points to " + string( node2->m_data ) );
            Set_ActualOutput( "m_ptrFirst points to " + string( ll.m_ptrFirst->m_data ) );
            Set_ExpectedOutput( "m_ptrLast points to " + string( node3->m_data ) );
            Set_ActualOutput( "m_ptrLast points to " + string( ll.m_ptrLast->m_data ) );
          TestPass();
        }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_PopBack()
{
    string functionName = "PopBack";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ arr.PopBack(); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    StartTest( "Popping the last item should reset m_ptrFirst and m_ptrLast to nullptr and set m_itemCount to 0." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;
        ll.m_itemCount = 1;
        ll.m_ptrFirst = new DoublyLinkedListNode<string>;
        ll.m_ptrLast = ll.m_ptrFirst;
        ll.PopFront();

        ostringstream oss;

        oss << ll.m_ptrFirst;
        Set_ExpectedOutput  ( "m_ptrFirst is nullptr" );
        Set_ActualOutput    ( "m_ptrFirst", oss.str() );

        oss.clear();
        oss << ll.m_ptrLast;
        Set_ExpectedOutput  ( "m_ptrLast is nullptr" );
        Set_ActualOutput    ( "m_ptrLast", oss.str() );

        if      ( ll.m_ptrFirst != nullptr )                                                    { TestFail(); }
        else if ( ll.m_ptrLast != nullptr )                                                     { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 0, ll.m_itemCount ) )                            { TestFail(); }
        else                                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "PopBack on a list with 2+ elements should adjust m_ptrLast and m_itemCount. " ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;
        ll.m_ptrFirst = new DoublyLinkedListNode<string>;
        ll.m_ptrFirst->m_data = "A";

        ll.m_ptrLast = new DoublyLinkedListNode<string>;
        ll.m_ptrLast->m_data = "B";

        ll.m_ptrFirst->m_ptrNext = ll.m_ptrLast;
        ll.m_ptrLast->m_ptrPrev = ll.m_ptrFirst;

        ll.m_itemCount = 2;

        ll.PopFront();

        ostringstream oss;

        oss << ll.m_ptrFirst;
        Set_ExpectedOutput  ( "m_ptrLast is m_ptrFirst" );
        Set_ActualOutput    ( "m_ptrLast", oss.str() );

        oss.clear();
        oss << ll.m_ptrLast;
        Set_ExpectedOutput  ( "m_ptrFirst is m_ptrFirst" );
        Set_ActualOutput    ( "m_ptrFirst", oss.str() );

        if      ( ll.m_ptrFirst != ll.m_ptrLast )                                               { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 1, ll.m_itemCount ) )                            { TestFail(); }
        else                                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "Pushing Back cd1, cd2, cd3, a PopBack should leave cd1 and cd2." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;

        auto node1 = new DoublyLinkedListNode<string>;
        node1->m_data = "cd1";

        auto node2 = new DoublyLinkedListNode<string>;
        node2->m_data = "cd2";
        node1->m_ptrNext = node2;
        node2->m_ptrPrev = node1;

        auto node3 = new DoublyLinkedListNode<string>;
        node3->m_data = "cd3";
        node2->m_ptrNext = node3;
        node3->m_ptrPrev = node2;

        ll.m_ptrFirst = node1;
        ll.m_ptrLast = node3;
        ll.m_itemCount = 3;

        Set_Comments( "Item at position 0: " + node1->m_data );
        Set_Comments( "Item at position 1: " + node2->m_data );
        Set_Comments( "Item at position 2: " + node3->m_data );

        ll.PopBack();

        if      ( !Set_Outputs( "m_itemCount", 2, ll.m_itemCount ) )             { TestFail(); }
        else if ( ll.m_ptrFirst != node1 )
        {
            Set_ExpectedOutput( "m_ptrFirst points to " + string( node1->m_data ) );
            Set_ActualOutput( "m_ptrFirst points to " + string( ll.m_ptrFirst->m_data ) );
            TestFail();
        }
        else if ( ll.m_ptrLast != node2 )
        {
            Set_ExpectedOutput( "m_ptrLast points to " + string( node2->m_data ) );
            Set_ActualOutput( "m_ptrLast points to " + string( ll.m_ptrLast->m_data ) );
            TestFail();
        }
        else                                                                     { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_PopAt()
{
    string functionName = "PopAt";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName, "Size" } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ arr.PopAt( 1 ); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "Popping the last item should reset m_ptrFirst and m_ptrLast to nullptr and set m_itemCount to 0." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;
        ll.m_itemCount = 1;
        ll.m_ptrFirst = new DoublyLinkedListNode<string>;
        ll.m_ptrLast = ll.m_ptrFirst;
        ll.PopFront();

        ostringstream oss;

        oss << ll.m_ptrFirst;
        Set_ExpectedOutput  ( "m_ptrFirst is nullptr" );
        Set_ActualOutput    ( "m_ptrFirst", oss.str() );

        oss.str("");
        oss.clear();
        oss << ll.m_ptrLast;
        Set_ExpectedOutput  ( "m_ptrLast is nullptr" );
        Set_ActualOutput    ( "m_ptrLast", oss.str() );

        if      ( ll.m_ptrFirst != nullptr )                                                    { TestFail(); }
        else if ( ll.m_ptrLast != nullptr )                                                     { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 0, ll.m_itemCount ) )                            { TestFail(); }
        else                                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "PopAt on a list with 3 items and PopAt index 0 " ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;

        auto node1 = new DoublyLinkedListNode<string>;
        auto node2 = new DoublyLinkedListNode<string>;
        auto node3 = new DoublyLinkedListNode<string>;

        node1->m_data = "A";
        node2->m_data = "B";
        node3->m_data = "C";

        node1->m_ptrNext = node2;
        node2->m_ptrNext = node3;

        node3->m_ptrPrev = node2;
        node2->m_ptrPrev = node1;

        ll.m_ptrFirst = node1;
        ll.m_ptrLast = node3;

        ll.m_itemCount = 3;

        Set_Comments( "Item at position 0: " + node1->m_data );
        Set_Comments( "Item at position 1: " + node2->m_data );
        Set_Comments( "Item at position 2: " + node3->m_data );

        ll.PopAt( 0 );

        // Expect the same results as PopFront()
        // m_ptrFirst should now be node2

//        ostringstream oss;
//        oss << ll.m_ptrFirst;
//        Set_ExpectedOutput  ( "m_ptrLast is m_ptrFirst" );
//        Set_ActualOutput    ( "m_ptrLast", oss.str() );
//
//        oss.str("");
//        oss.clear();
//        oss << ll.m_ptrLast;

        if      ( !Set_Outputs( "m_ptrFirst value", node2->m_data, ll.m_ptrFirst->m_data ) )    { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 2, ll.m_itemCount ) )                            { TestFail(); }
        else                                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "PopAt on a list with 3 items and PopAt index 2 " ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;

        auto node1 = new DoublyLinkedListNode<string>;
        auto node2 = new DoublyLinkedListNode<string>;
        auto node3 = new DoublyLinkedListNode<string>;

        node1->m_data = "A";
        node2->m_data = "B";
        node3->m_data = "C";

        node1->m_ptrNext = node2;
        node2->m_ptrNext = node3;

        node3->m_ptrPrev = node2;
        node2->m_ptrPrev = node1;

        ll.m_ptrFirst = node1;
        ll.m_ptrLast = node3;

        ll.m_itemCount = 3;

        Set_Comments( "Item at position 0: " + node1->m_data );
        Set_Comments( "Item at position 1: " + node2->m_data );
        Set_Comments( "Item at position 2: " + node3->m_data );

        ll.PopAt( 2 );

        // Expect the same results as PopBack()
        // m_ptrLast should now be node2

//        ostringstream oss;
//        oss << ll.m_ptrFirst;
//        Set_ExpectedOutput  ( "m_ptrLast is m_ptrFirst" );
//        Set_ActualOutput    ( "m_ptrLast", oss.str() );
//
//        oss.str("");
//        oss.clear();
//        oss << ll.m_ptrLast;

        if      ( !Set_Outputs( "m_ptrLast value", node2->m_data, ll.m_ptrLast->m_data ) )      { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 2, ll.m_itemCount ) )                            { TestFail(); }
        else                                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "Pushing Back A, B, C, a PopAt should leave A and C." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;

        auto node1 = new DoublyLinkedListNode<string>;
        auto node2 = new DoublyLinkedListNode<string>;
        auto node3 = new DoublyLinkedListNode<string>;

        node1->m_data = "A";
        node2->m_data = "B";
        node3->m_data = "C";

        node1->m_ptrNext = node2;
        node2->m_ptrPrev = node1;
        node2->m_ptrNext = node3;
        node3->m_ptrPrev = node2;

        ll.m_ptrFirst = node1;
        ll.m_ptrLast = node3;

        ll.m_itemCount = 3;

        Set_Comments( "Before PopAt..." );
        Set_Comments( "Item at position 0: " + node1->m_data );
        Set_Comments( "Item at position 1: " + node2->m_data );
        Set_Comments( "Item at position 2: " + node3->m_data );

        Set_ExpectedOutput( "m_ptrFirst points to " + string( node1->m_data ) );
        Set_ActualOutput( "m_ptrFirst points to " + string( ll.m_ptrFirst->m_data ) );

        Set_ExpectedOutput( "m_ptrLast points to " + string( node3->m_data ) );
        Set_ActualOutput( "m_ptrLast points to " + string( ll.m_ptrLast->m_data ) );

        ll.PopAt( 1 );

        if      ( !Set_Outputs( "m_itemCount", 2, ll.m_itemCount ) )            { TestFail(); }
        else if ( ll.m_ptrFirst != node1 )                                      { TestFail(); }
        else if ( ll.m_ptrLast != node3 )                                       { TestFail(); }
        else                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    StartTest( "Pushing Back A, B, C, D, E. PopAt(2), check pointer updates." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;

        auto node1 = new DoublyLinkedListNode<string>;
        auto node2 = new DoublyLinkedListNode<string>;
        auto node3 = new DoublyLinkedListNode<string>;
        auto node4 = new DoublyLinkedListNode<string>;
        auto node5 = new DoublyLinkedListNode<string>;

        node1->m_data = "A";
        node2->m_data = "B";
        node3->m_data = "C";
        node4->m_data = "D";
        node5->m_data = "E";

        node1->m_ptrNext = node2;
        node2->m_ptrNext = node3;
        node3->m_ptrNext = node4;
        node4->m_ptrNext = node5;

        node5->m_ptrPrev = node4;
        node4->m_ptrPrev = node3;
        node3->m_ptrPrev = node2;
        node2->m_ptrPrev = node1;

        ll.m_ptrFirst = node1;
        ll.m_ptrLast = node5;

        ostringstream oss;
//        oss << ll.m_ptrFirst;
//        oss.str("");
//        oss.clear();
//        oss << ll.m_ptrLast;
//        Set_ActualOutput    ( "m_ptrLast", oss.str() );
        ll.m_itemCount = 5;

        Set_Comments( "Before PopAt(2)..." );
        oss.str(""); oss.clear(); oss << node1; Set_Comments( "Item at position 0: [" + oss.str() + "] value: " + node1->m_data );
        oss.str(""); oss.clear(); oss << node2; Set_Comments( "Item at position 1: [" + oss.str() + "] value: " + node2->m_data );
        oss.str(""); oss.clear(); oss << node3; Set_Comments( "Item at position 2: [" + oss.str() + "] value: " + node3->m_data );
        oss.str(""); oss.clear(); oss << node4; Set_Comments( "Item at position 3: [" + oss.str() + "] value: " + node4->m_data );
        oss.str(""); oss.clear(); oss << node5; Set_Comments( "Item at position 4: [" + oss.str() + "] value: " + node5->m_data );

        ll.PopAt( 2 );

        //Set_Comments("After PopAt(2)...");
        //oss.str(""); oss.clear(); oss << node1; Set_Comments("Item at position 0: [" + oss.str() + "] value: " + node1->m_data);
        //oss.str(""); oss.clear(); oss << node2; Set_Comments("Item at position 1: [" + oss.str() + "] value: " + node2->m_data);
        //oss.str(""); oss.clear(); oss << node3; Set_Comments("Item at position 2: [" + oss.str() + "] value: " + node3->m_data);
        //oss.str(""); oss.clear(); oss << node4; Set_Comments("Item at position 3: [" + oss.str() + "] value: " + node4->m_data);
        //oss.str(""); oss.clear(); oss << node5; Set_Comments("Item at position 4: [" + oss.str() + "] value: " + node5->m_data);


        // Check m_ptrNext for each
        oss.str(""); oss.clear(); oss << node1;
        Set_ExpectedOutput( "Item 0 is " + string( node1->m_data ) + " (" + oss.str() + ")" );
        oss.str(""); oss.clear(); oss << ll.m_ptrFirst;
        Set_ActualOutput( "Item 0 is " + string( ll.m_ptrFirst->m_data ) + " (" + oss.str() + ")" );

        oss.str(""); oss.clear(); oss << node2;
        Set_ExpectedOutput( "Item 1 is " + string( node2->m_data ) + " (" + oss.str() + ")" );
        oss.str(""); oss.clear(); oss << ll.m_ptrFirst->m_ptrNext;
        Set_ActualOutput( "Item 1 is " + string( ll.m_ptrFirst->m_ptrNext->m_data ) + " (" + oss.str() + ")" );

        oss.str(""); oss.clear(); oss << node4;
        Set_ExpectedOutput( "Item 2 is " + string( node4->m_data ) + " (" + oss.str() + ")" );
        oss.str(""); oss.clear(); oss << ll.m_ptrFirst->m_ptrNext->m_ptrNext;
        Set_ActualOutput( "Item 2 is " + string( ll.m_ptrFirst->m_ptrNext->m_ptrNext->m_data ) + " (" + oss.str() + ")" );

        oss.str(""); oss.clear(); oss << node5;
        Set_ExpectedOutput( "Item 3 is " + string( node5->m_data ) + " (" + oss.str() + ")" );
        oss.str(""); oss.clear(); oss << ll.m_ptrLast;
        Set_ActualOutput( "Item 3 is " + string( ll.m_ptrLast->m_data ) + " (" + oss.str() + ")" );

        // Check m_ptrPrev for each
        oss.str(""); oss.clear(); oss << node4;
        Set_ExpectedOutput( "m_ptrLast->m_ptrPrev is " + string( node4->m_data ) + " (" + oss.str() + ")" );
        oss.str(""); oss.clear(); oss << ll.m_ptrLast->m_ptrPrev;
        Set_ActualOutput( "m_ptrLast->m_ptrPrev is " + string( ll.m_ptrLast->m_ptrPrev->m_data ) + " (" + oss.str() + ")" );

        oss.str(""); oss.clear(); oss << node2;
        Set_ExpectedOutput( "m_ptrLast->m_ptrPrev->m_ptrPrev is " + string( node2->m_data ) + " (" + oss.str() + ")" );
        oss.str(""); oss.clear(); oss << ll.m_ptrLast->m_ptrPrev->m_ptrPrev;
        Set_ActualOutput( "m_ptrLast->m_ptrPrev->m_ptrPrev is " + string( ll.m_ptrLast->m_ptrPrev->m_ptrPrev->m_data ) + " (" + oss.str() + ")" );

        oss.str(""); oss.clear(); oss << node1;
        Set_ExpectedOutput( "m_ptrLast->m_ptrPrev->m_ptrPrev->m_ptrPrev is " + string( node1->m_data ) + " (" + oss.str() + ")" );
        oss.str(""); oss.clear(); oss << ll.m_ptrLast->m_ptrPrev->m_ptrPrev->m_ptrPrev;
        Set_ActualOutput( "m_ptrLast->m_ptrPrev->m_ptrPrev->m_ptrPrev is " + string( ll.m_ptrLast->m_ptrPrev->m_ptrPrev->m_ptrPrev->m_data ) + " (" + oss.str() + ")" );

        // Check m_ptrFirst and m_ptrLast
        oss.str(""); oss.clear(); oss << node1;
        Set_ExpectedOutput( "m_ptrFirst is " + string( oss.str() ) );
        oss.str(""); oss.clear(); oss << ll.m_ptrFirst;
        Set_ActualOutput( "m_ptrFirst is " + string( oss.str() ) );

        oss.str(""); oss.clear(); oss << node5;
        Set_ExpectedOutput( "m_ptrLast is " + string( oss.str() ) );
        oss.str(""); oss.clear(); oss << ll.m_ptrLast;
        Set_ActualOutput( "m_ptrLast is " + string( oss.str() ) );


        if      ( !Set_Outputs( "m_itemCount", 4, ll.m_itemCount ) )            { TestFail(); }
        else if ( ll.m_ptrFirst != node1 )                                      { TestFail(); }
        else if ( ll.m_ptrLast != node5 )                                       { TestFail(); }
        else if ( ll.m_ptrFirst->m_ptrNext != node2 )                           { TestFail(); }
        else if ( ll.m_ptrFirst->m_ptrNext->m_ptrNext != node4 )                { TestFail(); }
        else if ( ll.m_ptrFirst->m_ptrNext->m_ptrNext->m_ptrNext != node5 )     { TestFail(); }
        else if ( ll.m_ptrLast->m_ptrPrev != node4 )                            { TestFail(); }
        else if ( ll.m_ptrLast->m_ptrPrev->m_ptrPrev != node2 )                 { TestFail(); }
        else if ( ll.m_ptrLast->m_ptrPrev->m_ptrPrev->m_ptrPrev != node1 )      { TestFail(); }
        else                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_GetFront()
{
    string functionName = "GetFront";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ arr.GetFront(); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. GetFront should throw exception if list is empty" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<int> myList;

        bool exceptionThrown = false;
        try
        {
            cout << myList.GetFront();
        }
        catch( ... )
        {
            exceptionThrown = true;
        }

        if ( !Set_Outputs( "exception thrown", true, exceptionThrown ) )    { TestFail(); }
        else                                                                 { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. After inserting an item, GetFront should get the front." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<int> myList;
        myList.m_ptrFirst = new DoublyLinkedListNode<int>;
        myList.m_ptrFirst->m_data = 100;
        myList.m_itemCount = 1;
        myList.m_ptrLast = myList.m_ptrFirst;

        int value = -1;
        bool exceptionThrown = false;

        try
        {
            value = myList.GetFront();
        }
        catch( ... )
        {
            exceptionThrown = true;
        }

        if ( !Set_Outputs( "Exception thrown", false, exceptionThrown ) )   { TestFail(); }
        else if ( !Set_Outputs( "GetFront()", 100, value ) )                { TestFail(); }
        else                                                                { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "3. After inserting several items, GetFront should get the front." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;

        auto node1 = new DoublyLinkedListNode<string>;
        node1->m_data = "cd1";

        auto node2 = new DoublyLinkedListNode<string>;
        node2->m_data = "cd2";
        node1->m_ptrNext = node2;
        node2->m_ptrPrev = node1;

        auto node3 = new DoublyLinkedListNode<string>;
        node3->m_data = "cd3";
        node2->m_ptrNext = node3;
        node3->m_ptrPrev = node2;

        ll.m_ptrFirst = node1;
        ll.m_ptrLast = node3;
        ll.m_itemCount = 3;

        Set_Comments( "Item at position 0: " + node1->m_data );
        Set_Comments( "Item at position 1: " + node2->m_data );
        Set_Comments( "Item at position 2: " + node3->m_data );

        string value = "";
        bool exceptionThrown = false;

        try
        {
            value = ll.GetFront();
        }
        catch( ... )
        {
            exceptionThrown = true;
        }

        if      ( !Set_Outputs( "Exception thrown", false, exceptionThrown ) )   { TestFail(); }
        else if ( !Set_Outputs( "GetFront()", node1->m_data, value ) )           { TestFail(); }
        else                                                                     { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_GetBack()
{
    string functionName = "GetBack";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ arr.GetBack(); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. GetFront should throw exception if list is empty" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<int> myList;

        bool exceptionThrown = false;
        try
        {
            cout << myList.GetFront();
        }
        catch( ... )
        {
            exceptionThrown = true;
        }

        if ( !Set_Outputs( "exception thrown", true, exceptionThrown ) )    { TestFail(); }
        else                                                                 { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. After inserting an item, GetBack should get the front." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<int> myList;
        myList.m_ptrFirst = new DoublyLinkedListNode<int>;
        myList.m_ptrFirst->m_data = 100;
        myList.m_ptrLast = myList.m_ptrFirst;
        myList.m_itemCount = 1;

        int value = -1;
        bool exceptionThrown = false;

        try
        {
            value = myList.GetBack();
        }
        catch( ... )
        {
            exceptionThrown = true;
        }

        if      ( !Set_Outputs( "Exception thrown", false, exceptionThrown ) )  { TestFail(); }
        else if ( !Set_Outputs( "GetBack()", 100, value ) )                     { TestFail(); }
        else                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "3. After inserting several items, GetBack should get the back." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;

        auto node1 = new DoublyLinkedListNode<string>;
        node1->m_data = "cd1";

        auto node2 = new DoublyLinkedListNode<string>;
        node2->m_data = "cd2";
        node1->m_ptrNext = node2;
        node2->m_ptrPrev = node1;

        auto node3 = new DoublyLinkedListNode<string>;
        node3->m_data = "cd3";
        node2->m_ptrNext = node3;
        node3->m_ptrPrev = node2;

        ll.m_ptrFirst = node1;
        ll.m_ptrLast = node3;
        ll.m_itemCount = 3;

        Set_Comments( "Item at position 0: " + node1->m_data );
        Set_Comments( "Item at position 1: " + node2->m_data );
        Set_Comments( "Item at position 2: " + node3->m_data );

        string value = "";
        bool exceptionThrown = false;

        try
        {
            value = ll.GetBack();
        }
        catch( ... )
        {
            exceptionThrown = true;
        }

        if      ( !Set_Outputs( "Exception thrown", false, exceptionThrown ) )      { TestFail(); }
        else if ( !Set_Outputs( "GetBack()", node3->m_data, value ) )               { TestFail(); }
        else                                                                        { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_GetAt()
{
    string functionName = "GetAt";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ arr.GetAt( 1 ); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. GetAt should throw exception if list is empty" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<int> myList;

        bool exceptionThrown = false;
        try
        {
            cout << myList.GetAt( 1 );
        }
        catch( ... )
        {
            exceptionThrown = true;
        }

        if ( !Set_Outputs( "exception thrown", true, exceptionThrown ) )    { TestFail(); }
        else                                                                 { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. After inserting several items, GetAt should return the correct item." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> myList;

        DoublyLinkedListNode<string>* node1 = new DoublyLinkedListNode<string>;
        DoublyLinkedListNode<string>* node2 = new DoublyLinkedListNode<string>;
        DoublyLinkedListNode<string>* node3 = new DoublyLinkedListNode<string>;

        node1->m_data = "cat";
        node2->m_data = "dog";
        node3->m_data = "bunny";

        node1->m_ptrNext = node2;
        node2->m_ptrNext = node3;
        node3->m_ptrPrev = node2;
        node2->m_ptrPrev = node1;

        myList.m_ptrFirst = node1;
        myList.m_ptrLast = node3;

        myList.m_itemCount = 3;

        Set_Comments( "Item at position 0: " + node1->m_data );
        Set_Comments( "Item at position 1: " + node2->m_data );
        Set_Comments( "Item at position 2: " + node3->m_data );

        string value = "";
        bool exceptionThrown = false;

        try
        {
            value = myList.GetAt( 1 );
        }
        catch( ... )
        {
            exceptionThrown = true;
        }

        if      ( !Set_Outputs( "Exception thrown", false, exceptionThrown ) )  { TestFail(); }
        else if ( !Set_Outputs( "GetAt( 1 )", node2->m_data, value ) )          { TestFail(); }
        else                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_SubscriptOperator()
{
    string functionName = "SubscriptOperator";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ cout << arr.GetAt( 0 ); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    StartTest( "1. operator[] should throw exception if list is empty" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;

        bool threwException = false;

        try
        {
            string cd = ll.GetAt(10);
        }
        catch( ... )
        {
            threwException = true;
        }

        if ( !Set_Outputs( "Exception thrown", true, threwException ) )         { TestFail(); }
        else                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. After inserting several items, operator[] get the correct item." ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;

        auto node1 = new DoublyLinkedListNode<string>;
        node1->m_data = "cd1";

        auto node2 = new DoublyLinkedListNode<string>;
        node2->m_data = "cd2";
        node1->m_ptrNext = node2;
        node2->m_ptrPrev = node1;

        auto node3 = new DoublyLinkedListNode<string>;
        node3->m_data = "cd3";
        node2->m_ptrNext = node3;
        node3->m_ptrPrev = node2;

        ll.m_ptrFirst = node1;
        ll.m_ptrLast = node3;
        ll.m_itemCount = 3;

        Set_Comments( "Item at position 0: " + node1->m_data );
        Set_Comments( "Item at position 1: " + node2->m_data );
        Set_Comments( "Item at position 2: " + node3->m_data );

        if      ( !Set_Outputs( "list[0]", node1->m_data, ll.GetAt(0) ) )     { TestFail(); }
        else if ( !Set_Outputs( "list[1]", node2->m_data, ll.GetAt(1) ) )     { TestFail(); }
        else if ( !Set_Outputs( "list[2]", node3->m_data, ll.GetAt(2) ) )     { TestFail(); }
        else                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_IsEmpty()
{
    string functionName = "IsEmpty";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ arr.IsEmpty(); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }

        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. An empty list should return true" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<int> myList;

        if      ( !Set_Outputs( "IsEmpty()", true, myList.IsEmpty() ) )    { TestFail(); }
        else                                                               { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. An non-empty list should return false" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<int> myList;
        myList.m_ptrFirst = new DoublyLinkedListNode<int>;
        myList.m_ptrLast = myList.m_ptrFirst;
        myList.m_itemCount = 1;

        if      ( !Set_Outputs( "IsEmpty()", false, myList.IsEmpty() ) )    { TestFail(); }
        else                                                                { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int LinkedListTester::Test_Size()
{
    string functionName = "Size";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "Test_" + functionName, { } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   LinkedList<int> arr;     /**/ arr.Size(); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. The Size() of an empty list should be 0" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<int> myList;

        if      ( !Set_Outputs( "Size()", 0, myList.Size() ) )      { TestFail(); }
        else                                                        { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. The Size() of a list with 3 items should be 3" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        LinkedList<string> ll;

        auto node1 = new DoublyLinkedListNode<string>;
        node1->m_data = "cd1";

        auto node2 = new DoublyLinkedListNode<string>;
        node2->m_data = "cd2";
        node1->m_ptrNext = node2;
        node2->m_ptrPrev = node1;

        auto node3 = new DoublyLinkedListNode<string>;
        node3->m_data = "cd3";
        node2->m_ptrNext = node3;
        node3->m_ptrPrev = node2;

        ll.m_ptrFirst = node1;
        ll.m_ptrLast = node3;
        ll.m_itemCount = 3;

        if      ( !Set_Outputs( "Size()", 3, ll.Size() ) )          { TestFail(); }
        else                                                        { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

#endif
