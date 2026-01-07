#ifndef _SMART_FIXED_ARRAY_TESTER_HPP
#define _SMART_FIXED_ARRAY_TESTER_HPP

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

#include "SmartFixedArray.hpp"

class SmartFixedArrayTester : public TesterBase
{
public:
    SmartFixedArrayTester()
        : TesterBase( "test_result_smart_fixed_array.html" )
    {
        AddTest(TestListItem("Constructor()",       bind(&SmartFixedArrayTester::Test_Constructor, this)));

        AddTest(TestListItem("ShiftLeft()",         bind(&SmartFixedArrayTester::Test_ShiftLeft, this)));
        AddTest(TestListItem("ShiftRight()",        bind(&SmartFixedArrayTester::Test_ShiftRight, this)));

        AddTest(TestListItem("PopBack()",           bind(&SmartFixedArrayTester::Test_PopBack, this)));
        AddTest(TestListItem("PopFront()",          bind(&SmartFixedArrayTester::Test_PopFront, this)));
        AddTest(TestListItem("PopAt()",             bind(&SmartFixedArrayTester::Test_PopAt, this)));

        AddTest(TestListItem("GetBack()",           bind(&SmartFixedArrayTester::Test_GetBack, this)));
        AddTest(TestListItem("GetFront()",          bind(&SmartFixedArrayTester::Test_GetFront, this)));
        AddTest(TestListItem("GetAt()",             bind(&SmartFixedArrayTester::Test_GetAt, this)));

        AddTest(TestListItem("IsFull()",            bind(&SmartFixedArrayTester::Test_IsFull, this)));
        AddTest(TestListItem("IsEmpty()",           bind(&SmartFixedArrayTester::Test_IsEmpty, this)));

        AddTest(TestListItem("PushBack()",          bind(&SmartFixedArrayTester::Test_PushBack, this)));
        AddTest(TestListItem("PushFront()",         bind(&SmartFixedArrayTester::Test_PushFront, this)));
        AddTest(TestListItem("PushAt()",            bind(&SmartFixedArrayTester::Test_PushAt, this)));

        AddTest(TestListItem("Search()",            bind(&SmartFixedArrayTester::Test_Search, this)));
    }

    virtual ~SmartFixedArrayTester() { }

private:
    int Test_Constructor();
    int Test_PushBack();
    int Test_PushFront();
    int Test_PushAt();
    int Test_PopBack();
    int Test_PopFront();
    int Test_PopAt();
    int Test_GetBack();
    int Test_GetFront();
    int Test_GetAt();
    int Test_IsFull();
    int Test_IsEmpty();
    int Test_ShiftLeft();
    int Test_ShiftRight();
    int Test_Search();
};

int SmartFixedArrayTester::Test_Constructor()
{
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_Constructor", 3 );
    StartTestSet( "Test_Constructor", { } );
    ostringstream oss;

    StartTest( "1. Check initial member variable values" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        Set_Comments( "When a new SmartFixedArray is created, m_itemCount and should be 0 and ARRAY_SIZE should be 100." );

        SmartFixedArray<int> arr;

        if      ( !Set_Outputs( "ARRAY_SIZE", 100, arr.ARRAY_SIZE ) )   { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 0, arr.m_itemCount ) )   { TestFail(); }
        else                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_PushBack()
{
    string functionName = "PushBack";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName, "Resize" } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     /**/ arr.PushBack( 5 ); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Add three items, check they're in the correct position" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        string values[] = { "a", "b", "c" };
        int expectedItemCount = 3;

        SmartFixedArray<string> arr;
        for ( int i = 0; i < 3; i++ )   { arr.PushBack( values[i] ); }

        Set_ExpectedOutput( "m_array", string( "not nullptr" ) );
        for ( int i = 0; i < 3; i++ )   { Set_ExpectedOutput( "m_array[" + StringUtil::ToString( i ) + "]", values[i] ); }

        ostringstream oss;
        oss << arr.m_array;
        Set_ActualOutput    ( "m_array", oss.str() );

        if      ( arr.m_array == nullptr )                                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", expectedItemCount, arr.m_itemCount ) )   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", values[0], arr.m_array[0] ) )             { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", values[1], arr.m_array[1] ) )             { TestFail(); }
        else if ( !Set_Outputs( "m_array[2]", values[2], arr.m_array[2] ) )             { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check if StructureFullException is thrown if array is full" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool exceptionThrown = false;

        try                                     {   SmartFixedArray<int> arr;     arr.m_itemCount = arr.ARRAY_SIZE;      arr.PushBack( 2 );       }
        catch( StructureFullException& ex )     {   exceptionThrown = true;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        Set_Outputs( string( "Exception is thrown" ), "true", exceptionThrown );
        if  ( exceptionThrown )     { TestPass(); }
        else                        { TestFail(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_PushFront()
{
    string functionName = "PushFront";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName, "AllocateMemory", "Resize" } );
    ostringstream oss;

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     /**/ arr.PushFront( 5 ); /**/             }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Add three items, check they're in the correct position" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.PushFront( "a" );
        arr.PushFront( "b" );
        arr.PushFront( "c" );

        ostringstream oss;
        oss << arr.m_array;
        Set_ExpectedOutput( "m_array", string( "not nullptr" ) );
        Set_ActualOutput    ( "m_array", oss.str() );

        if      ( arr.m_array == nullptr )                                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 3, arr.m_itemCount ) )                   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", string( "c" ), arr.m_array[0] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", string( "b" ), arr.m_array[1] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[2]", string( "a" ), arr.m_array[2] ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check if StructureFullException is thrown if array is full" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool exceptionThrown = false;

        try                                {   SmartFixedArray<int> arr;     arr.m_itemCount = arr.ARRAY_SIZE;      arr.PushFront( 2 );       }
        catch( StructureFullException& ex )    {   exceptionThrown = true;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        Set_Outputs( string( "Exception is thrown" ), "true", exceptionThrown );
        if  ( exceptionThrown )     { TestPass(); }
        else                        { TestFail(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_PushAt()
{
    string functionName = "PushAt";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     arr.PushAt( 5, 5 );            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, insert at some position" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_itemCount = 3;

        arr.PushAt( "z", 1 );

        if      ( arr.m_array == nullptr )                                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 4, arr.m_itemCount ) )                   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", string( "a" ), arr.m_array[0] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", string( "z" ), arr.m_array[1] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[2]", string( "b" ), arr.m_array[2] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[3]", string( "c" ), arr.m_array[3] ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check if StructureFullException is thrown if array is full" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool exceptionThrown = false;

        try                                {   SmartFixedArray<int> arr;     arr.m_itemCount = arr.ARRAY_SIZE;      arr.PushAt( 0, 2 );       }
        catch( StructureFullException& ex )    {   exceptionThrown = true;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        Set_Outputs( string( "Exception is thrown" ), "true", exceptionThrown );
        if  ( exceptionThrown )     { TestPass(); }
        else                        { TestFail(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "3. ERROR CHECK: Check for exception when inserting outside of range" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array itemCount is 5, trying to call InsertAt( \"z\", 50 )." );
        SmartFixedArray<string> arr;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_array[3] = "d";
        arr.m_array[4] = "e";
        arr.m_itemCount = 5;

        bool exceptionOccurred = false;

        try
        {
            arr.PushAt( "z", 50 );
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_PopBack()
{
    string functionName = "PopBack";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     arr.PopBack();            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, remove back" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_itemCount = 3;

        arr.PopBack();

        if      ( arr.m_array == nullptr )                                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 2, arr.m_itemCount ) )                   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", string( "a" ), arr.m_array[0] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", string( "b" ), arr.m_array[1] ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception with empty array" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty, calling PopBack()." );
        SmartFixedArray<string> arr;

        bool exceptionOccurred = false;

        try
        {
            arr.PopBack();
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_PopFront()
{
    string functionName = "PopFront";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     arr.PopFront();            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, remove front" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_itemCount = 3;

        arr.PopFront();

        if      ( arr.m_array == nullptr )                                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 2, arr.m_itemCount ) )                   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", string( "b" ), arr.m_array[0] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", string( "c" ), arr.m_array[1] ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception with empty array" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty, calling PopFront()." );
        SmartFixedArray<string> arr;

        bool exceptionOccurred = false;

        try
        {
            arr.PopFront();
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_PopAt()
{
    string functionName = "PopAt";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     arr.PopAt( 1 );            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;   Logger::Out( ex.what() );   }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, remove at position" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_itemCount = 3;

        arr.PopAt( 1 );

        if      ( arr.m_array == nullptr )                                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 2, arr.m_itemCount ) )                   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", string( "a" ), arr.m_array[0] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", string( "c" ), arr.m_array[1] ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception with invalid index" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "ARRAY_SIZE is 100. Calling PopAt( 150 )." );
        SmartFixedArray<string> arr;
        arr.m_itemCount = 3;

        bool exceptionOccurred = false;

        try
        {
            arr.PopAt( 150 );
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "3. ERROR CHECK: Check for exception with empty array" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty, calling PopAt( 0 )." );
        SmartFixedArray<string> arr;

        bool exceptionOccurred = false;

        try
        {
            arr.PopAt( 0 );
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_GetBack()
{
    string functionName = "GetBack";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     arr.GetBack();            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, get back" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_itemCount = 3;

        if      ( !Set_Outputs( "GetBack()", string( "c" ), arr.GetBack() ) )       { TestFail(); }
        else                                                                        { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception when array is empty" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty. Calling GetBack()." );
        SmartFixedArray<string> arr;

        bool exceptionOccurred = false;

        try
        {
            arr.GetBack();
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_GetFront()
{
    string functionName = "GetFront";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     arr.GetFront();            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;   Logger::Out( ex.what() );   }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, get front" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_itemCount = 3;

        if      ( !Set_Outputs( "GetFront()", string( "a" ), arr.GetFront() ) )      { TestFail(); }
        else                                                                         { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception when array is empty" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty. Calling GetFront()." );
        SmartFixedArray<string> arr;

        bool exceptionOccurred = false;

        try
        {
            arr.GetFront();
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_GetAt()
{
    string functionName = "GetAt";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     arr.GetAt( 5 );            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, get at 1" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_itemCount = 3;

        if      ( !Set_Outputs( "GetAt( 1 )", string( "b" ), arr.GetAt( 1 ) ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception with invalid index" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "ARRAY_SIZE is 100. Calling GetAt( 250 )." );
        SmartFixedArray<string> arr;
        arr.m_itemCount = 3;

        bool exceptionOccurred = false;

        try
        {
            arr.GetAt( 250 );
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "3. ERROR CHECK: Check for exception when array is empty" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty. Calling GetAt( 0 )." );
        SmartFixedArray<string> arr;

        bool exceptionOccurred = false;

        try
        {
            arr.GetAt( 0 );
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_IsFull()
{
    string functionName = "IsFull";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     arr.IsFull();            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Check if IsFull returns true when full" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.m_itemCount = 100;
        if      ( !Set_Outputs( "IsFull()", true, arr.IsFull() ) )         { TestFail(); }
        else                                                               { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. Check if IsFull returns false when not full" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.m_itemCount = 3;
        if      ( !Set_Outputs( "IsFull()", false, arr.IsFull() ) )         { TestFail(); }
        else                                                                { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_IsEmpty()
{
    string functionName = "IsEmpty";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     arr.IsEmpty();            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Check if IsFull returns false when an item is in the array" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.m_itemCount = 100;
        if      ( !Set_Outputs( functionName, false, arr.IsEmpty() ) )     { TestFail(); }
        else                                                               { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. Check if IsFull returns true when empty" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.m_itemCount = 0;
        if      ( !Set_Outputs( functionName, true, arr.IsEmpty() ) )       { TestFail(); }
        else                                                                { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_ShiftLeft()
{
    string functionName = "ShiftLeft";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        SmartFixedArray<int> arr;
        try
        {
            arr.ShiftLeft( 0 );
        }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Populate array, call ShiftLeft, check positions" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        string originalValues[] = { "a", "b", "c", "d", "-" };

        SmartFixedArray<string> arr;
        arr.m_itemCount = 4;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_array[3] = "d";
        arr.ShiftLeft( 1 );

        if      ( !Set_Outputs( "m_array[0]", string("a"), arr.m_array[0] ) )        { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", string("c"), arr.m_array[1] ) )        { TestFail(); }
        else if ( !Set_Outputs( "m_array[2]", string("d"), arr.m_array[2] ) )        { TestFail(); }
        else                                                                        { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Try to shift array out-of-bounds..." ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "ARRAY_SIZE is 100, calling ShiftLeft( 300 )." );
        SmartFixedArray<string> arr;
        arr.m_itemCount = 5;

        bool exceptionOccurred = false;

        try
        {
            arr.ShiftLeft( 300 );
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        Set_ExpectedOutput( "Exception occurred", true );
        Set_ActualOutput( "Exception occurred", exceptionOccurred );

        if      ( !exceptionOccurred )          { TestFail(); }
        else                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}


int SmartFixedArrayTester::Test_ShiftRight()
{
    string functionName = "ShiftRight";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        SmartFixedArray<int> arr;

        try                                     {
            arr.ShiftRight( 0 );
        }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Populate array, call ShiftRight, check positions" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        string originalValues[] = { "a", "b", "c", "d", "-" };

        SmartFixedArray<string> arr;
        arr.m_itemCount = 4;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_array[3] = "d";
        arr.ShiftRight( 1 );

        if      ( !Set_Outputs( "m_array[0]", string("a"), arr.m_array[0] ) )        { TestFail(); }
        else if ( !Set_Outputs( "m_array[2]", string("b"), arr.m_array[2] ) )        { TestFail(); }
        else if ( !Set_Outputs( "m_array[3]", string("c"), arr.m_array[3] ) )        { TestFail(); }
        else if ( !Set_Outputs( "m_array[4]", string("d"), arr.m_array[4] ) )        { TestFail(); }
        else                                                                        { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Try to shift array out-of-bounds..." ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "ARRAY_SIZE is 100, calling ShiftRight( 300 )." );
        SmartFixedArray<string> arr;
        arr.m_itemCount = 5;

        bool exceptionOccurred = false;

        try
        {
            arr.ShiftRight( 300 );
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        Set_ExpectedOutput( "Exception occurred", true );
        Set_ActualOutput( "Exception occurred", exceptionOccurred );

        if      ( !exceptionOccurred )          { TestFail(); }
        else                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_Search()
{
    string functionName = "Search";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartFixedArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     arr.Search( 10 );            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;  Logger::Out( ex.what() );    }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, search for an item." ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<string> arr;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_itemCount = 3;

        if      ( !Set_Outputs( "Search( \"b\" )", 1, arr.Search( "b" ) ) )             { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Search for an item that isn't in the array." ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Searching for \"z\" in the array." );
        SmartFixedArray<string> arr;
        arr.m_itemCount = 3;

        bool exceptionOccurred = false;

        try
        {
            arr.Search( "z" );
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}



#endif
