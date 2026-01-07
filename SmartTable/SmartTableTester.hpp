#ifndef _SMART_DYNAMIC_ARRAY_TESTER_HPP
#define _SMART_DYNAMIC_ARRAY_TESTER_HPP

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

#include "../SmartDynamicArray/SmartDynamicArray.hpp"

class SmartDynamicArrayTester : public TesterBase
{
public:
    SmartDynamicArrayTester()
        : TesterBase( "test_result_smart_dynamic_array.html" )
    {
        AddTest(TestListItem("Constructor()",       bind(&SmartDynamicArrayTester::Test_Constructor, this)));

        AddTest(TestListItem("ShiftLeft()",         bind(&SmartDynamicArrayTester::Test_ShiftLeft, this)));
        AddTest(TestListItem("ShiftRight()",        bind(&SmartDynamicArrayTester::Test_ShiftRight, this)));

        AddTest(TestListItem("RemoveBack()",        bind(&SmartDynamicArrayTester::Test_RemoveBack, this)));
        AddTest(TestListItem("RemoveFront()",       bind(&SmartDynamicArrayTester::Test_RemoveFront, this)));
        AddTest(TestListItem("RemoveAt()",          bind(&SmartDynamicArrayTester::Test_RemoveAt, this)));

        AddTest(TestListItem("GetBack()",           bind(&SmartDynamicArrayTester::Test_GetBack, this)));
        AddTest(TestListItem("GetFront()",          bind(&SmartDynamicArrayTester::Test_GetFront, this)));
        AddTest(TestListItem("GetAt()",             bind(&SmartDynamicArrayTester::Test_GetAt, this)));

        AddTest(TestListItem("AllocateMemory()",    bind(&SmartDynamicArrayTester::Test_AllocateMemory, this)));
        AddTest(TestListItem("Resize()",            bind(&SmartDynamicArrayTester::Test_Resize, this)));
        AddTest(TestListItem("IsFull()",            bind(&SmartDynamicArrayTester::Test_IsFull, this)));

        AddTest(TestListItem("InsertBack()",        bind(&SmartDynamicArrayTester::Test_InsertBack, this)));
        AddTest(TestListItem("InsertFront()",       bind(&SmartDynamicArrayTester::Test_InsertFront, this)));
        AddTest(TestListItem("InsertAt()",          bind(&SmartDynamicArrayTester::Test_InsertAt, this)));

        AddTest(TestListItem("Search()",            bind(&SmartDynamicArrayTester::Test_Search, this)));
    }

    virtual ~SmartDynamicArrayTester() { }

private:
    int Test_Constructor();
    int Test_InsertBack();
    int Test_InsertFront();
    int Test_InsertAt();
    int Test_RemoveBack();
    int Test_RemoveFront();
    int Test_RemoveAt();
    int Test_GetBack();
    int Test_GetFront();
    int Test_GetAt();
    int Test_AllocateMemory();
    int Test_Resize();
    int Test_IsFull();
    int Test_ShiftLeft();
    int Test_ShiftRight();
    int Test_Search();
};

int SmartDynamicArrayTester::Test_Constructor()
{
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_Constructor", 3 );
    StartTestSet( "Test_Constructor", { } );
    ostringstream oss;

    StartTest( "1. Check initial member variable values" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        Set_Comments( "When a new SmartDynamicArray is created, m_array should be nullptr and m_itemCount and m_arraySize should be 0." );

        SmartDynamicArray<int> arr;

        oss << arr.m_array;
        Set_ExpectedOutput  ( "m_array is nullptr" );
        Set_ActualOutput    ( "m_array", oss.str() );

        if      ( arr.m_array != nullptr )                              { TestFail(); }
        else if ( !Set_Outputs( "m_arraySize", 0, arr.m_arraySize ) )   { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 0, arr.m_itemCount ) )   { TestFail(); }
        else                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartDynamicArrayTester::Test_InsertBack()
{
    string functionName = "InsertBack";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName, "Resize" } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     /**/ arr.PushBack( 5 ); /**/   }
        catch( NotImplementedException& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "0b. Check if function AllocateMemory is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     /**/ arr.AllocateMemory( 5 ); /**/             }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Add three items, check they're in the correct position" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        string values[] = { "a", "b", "c" };
        int expectedItemCount = 3;

        SmartDynamicArray<string> arr;
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

    StartTest( "2. Check if prerequisite function Resize() is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     /**/ arr.Resize( 15 ); /**/             }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "3. Add maximum amount of items, check if resize triggers, and can add more" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.m_array = new string[3];
        arr.PushBack( "a" );
        arr.PushBack( "b" );
        arr.PushBack( "c" );
        // Resize should happen during this one:
        arr.PushBack( "d" );

        if      ( !Set_Outputs( "m_itemCount", 4, arr.m_itemCount ) )   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", string( "a" ), arr.m_array[0] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", string( "b" ), arr.m_array[1] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[2]", string( "c" ), arr.m_array[2] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[3]", string( "d" ), arr.m_array[3] ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartDynamicArrayTester::Test_InsertFront()
{
    string functionName = "InsertFront";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName, "AllocateMemory", "Resize" } );
    ostringstream oss;

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     /**/ arr.PushFront( 5 ); /**/             }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "0b. Check if function AllocateMemory is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     /**/ arr.AllocateMemory( 5 ); /**/             }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Add three items, check they're in the correct position" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
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

    StartTest( "2. Check if prerequisite function Resize() is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     /**/ arr.Resize( 15 ); /**/             }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "3. Add maximum amount of items, check if resize triggers, and can add more" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.m_array = new string[3];
        arr.PushFront( "a" );
        arr.PushFront( "b" );
        arr.PushFront( "c" );
        // Resize should happen during this one:
        arr.PushFront( "d" );

        if      ( !Set_Outputs( "m_itemCount", 4, arr.m_itemCount ) )                   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", string( "d" ), arr.m_array[0] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", string( "c" ), arr.m_array[1] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[2]", string( "b" ), arr.m_array[2] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[3]", string( "a" ), arr.m_array[3] ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    FinishTestSet();
    return TestResult();
}

int SmartDynamicArrayTester::Test_InsertAt()
{
    string functionName = "InsertAt";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     arr.PushAt( 5, 5 );            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "0b. Check if function AllocateMemory is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     /**/ arr.AllocateMemory( 5 ); /**/             }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, insert at some position" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.m_array = new string[ 5 ];
        arr.m_arraySize = 5;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_itemCount = 3;

        arr.PushAt( "z", 1 );

        ostringstream oss;
        oss << arr.m_array;
        Set_ExpectedOutput  ( "m_array", string( "not nullptr" ) );
        Set_ActualOutput    ( "m_array", oss.str() );

        if      ( arr.m_array == nullptr )                                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 4, arr.m_itemCount ) )                   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", string( "a" ), arr.m_array[0] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", string( "z" ), arr.m_array[1] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[2]", string( "b" ), arr.m_array[2] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[3]", string( "c" ), arr.m_array[3] ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception when inserting outside of range" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array itemCount is 5, trying to call InsertAt( \"z\", 50 )." );
        SmartDynamicArray<string> arr;
        arr.m_array = new string[ 5 ];
        arr.m_arraySize = 5;
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

int SmartDynamicArrayTester::Test_RemoveBack()
{
    string functionName = "RemoveBack";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     arr.PopBack();            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, remove back" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.m_array = new string[5];
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_arraySize = 5;
        arr.m_itemCount = 3;

        arr.PopBack();

        if      ( arr.m_array == nullptr )                                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 2, arr.m_itemCount ) )                   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", string( "a" ), arr.m_array[0] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", string( "b" ), arr.m_array[1] ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception with empty array" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty, calling RemoveBack()." );
        SmartDynamicArray<string> arr;

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

int SmartDynamicArrayTester::Test_RemoveFront()
{
    string functionName = "RemoveFront";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     arr.PopFront();            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, remove front" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.m_array = new string[5];
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_arraySize = 5;
        arr.m_itemCount = 3;

        arr.PopFront();

        if      ( arr.m_array == nullptr )                                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 2, arr.m_itemCount ) )                   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", string( "b" ), arr.m_array[0] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", string( "c" ), arr.m_array[1] ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception with empty array" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty, calling RemoveFront()." );
        SmartDynamicArray<string> arr;

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

int SmartDynamicArrayTester::Test_RemoveAt()
{
    string functionName = "RemoveAt";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     arr.PopAt( 1 );            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, remove at position" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.m_array = new string[5];
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_arraySize = 5;
        arr.m_itemCount = 3;

        arr.PopAt( 1 );

        if      ( arr.m_array == nullptr )                                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 2, arr.m_itemCount ) )                   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", string( "a" ), arr.m_array[0] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", string( "c" ), arr.m_array[1] ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception with invalid index" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array size is 5. Calling RemoveAt( 50 )." );
        SmartDynamicArray<string> arr;
        arr.m_arraySize = 5;
        arr.m_itemCount = 3;

        bool exceptionOccurred = false;

        try
        {
            arr.PopAt( 50 );
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "3. ERROR CHECK: Check for exception with empty array" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty, calling RemoveAt( 0 )." );
        SmartDynamicArray<string> arr;

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

int SmartDynamicArrayTester::Test_GetBack()
{
    string functionName = "GetBack";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     arr.GetBack();            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, get back" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.m_array = new string[5];
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_arraySize = 5;
        arr.m_itemCount = 3;

        if      ( !Set_Outputs( "GetBack()", string( "c" ), arr.GetBack() ) )       { TestFail(); }
        else                                                                        { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception when array is empty" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty. Calling GetBack()." );
        SmartDynamicArray<string> arr;

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

int SmartDynamicArrayTester::Test_GetFront()
{
    string functionName = "GetFront";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     arr.GetFront();            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, get front" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.m_array = new string[5];
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_arraySize = 5;
        arr.m_itemCount = 3;

        if      ( !Set_Outputs( "GetFront()", string( "a" ), arr.GetFront() ) )      { TestFail(); }
        else                                                                         { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception when array is empty" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty. Calling GetFront()." );
        SmartDynamicArray<string> arr;

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

int SmartDynamicArrayTester::Test_GetAt()
{
    string functionName = "GetAt";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     arr.GetAt( 5 );            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, get at 1" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.m_array = new string[5];
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_arraySize = 5;
        arr.m_itemCount = 3;

        if      ( !Set_Outputs( "GetAt( 1 )", string( "b" ), arr.GetAt( 1 ) ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception with invalid index" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array size is 5. Calling GetAt( 50 )." );
        SmartDynamicArray<string> arr;
        arr.m_arraySize = 5;
        arr.m_itemCount = 3;

        bool exceptionOccurred = false;

        try
        {
            arr.GetAt( 50 );
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
        SmartDynamicArray<string> arr;

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

int SmartDynamicArrayTester::Test_AllocateMemory()
{
    string functionName = "AllocateMemory";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     arr.AllocateMemory( 5 );            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Call AllocateMemory" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.AllocateMemory( 5 );

        ostringstream oss;
        oss << arr.m_array;
        Set_ExpectedOutput  ( "m_array", string( "not nullptr" ) );
        Set_ActualOutput    ( "m_array", oss.str() );

        if      ( arr.m_array == nullptr )                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 0, arr.m_itemCount ) )   { TestFail(); }
        else if ( !Set_Outputs( "m_arraySize", 5, arr.m_arraySize ) )   { TestFail(); }
        else                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception with negative size" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Calling AllocateMemory( -5 )." );
        SmartDynamicArray<string> arr;

        bool exceptionOccurred = false;

        try
        {
            arr.AllocateMemory( -5 );
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

int SmartDynamicArrayTester::Test_Resize()
{
    string functionName = "Resize";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     arr.Resize( 5 );            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Create array, call Resize, check that values are copied over, new size" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        string values[] = { "a", "b", "c", "d" };

        SmartDynamicArray<string> arr;
        arr.m_array = new string[4];
        arr.m_arraySize = 4;
        arr.m_itemCount = 4;

        for ( int i = 0; i < 4; i++ )
        {
            arr.m_array[i] = values[i];
        }

        arr.Resize( 8 );

        ostringstream oss;
        oss << arr.m_array;
        Set_ExpectedOutput  ( "m_array", string( "not nullptr" ) );
        Set_ActualOutput    ( "m_array", oss.str() );

        if      ( arr.m_array == nullptr )                                      { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 4, arr.m_itemCount ) )           { TestFail(); }
        else if ( !Set_Outputs( "m_arraySize", 8, arr.m_arraySize ) )           { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", values[0], arr.m_array[0] ) )     { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", values[1], arr.m_array[1] ) )     { TestFail(); }
        else if ( !Set_Outputs( "m_array[2]", values[2], arr.m_array[2] ) )     { TestFail(); }
        else if ( !Set_Outputs( "m_array[3]", values[3], arr.m_array[3] ) )     { TestFail(); }
        else                                                                    { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception when resize size is smaller than old size" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array size is 5, calling Resize( 2 )." );
        SmartDynamicArray<string> arr;
        arr.m_arraySize = 5;

        bool exceptionOccurred = false;

        try
        {
            arr.Resize( 2 );
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "3. ERROR CHECK: Check for exception when resize size is negative" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array size is 5, calling Resize( -50 )." );
        SmartDynamicArray<string> arr;
        arr.m_arraySize = 5;

        bool exceptionOccurred = false;

        try
        {
            arr.Resize( -50 );
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

int SmartDynamicArrayTester::Test_IsFull()
{
    string functionName = "IsFull";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     arr.IsFull();            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Check if IsFull returns true when full" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.m_arraySize = 5;
        arr.m_itemCount = 5;
        if      ( !Set_Outputs( "IsFull()", true, arr.IsFull() ) )         { TestFail(); }
        else                                                               { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. Check if IsFull returns false when not full" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.m_arraySize = 5;
        arr.m_itemCount = 3;
        if      ( !Set_Outputs( "IsFull()", false, arr.IsFull() ) )         { TestFail(); }
        else                                                                { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartDynamicArrayTester::Test_ShiftLeft()
{
    string functionName = "ShiftLeft";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        SmartDynamicArray<int> arr;
        arr.m_array = new int[5];
        try
        {
            arr.ShiftLeft( 0 );
        }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Populate array, call ShiftLeft, check positions" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        string originalValues[] = { "a", "b", "c", "d", "-" };

        SmartDynamicArray<string> arr;
        arr.m_array = new string[10];
        arr.m_arraySize = 10;
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
        Set_Comments( "Array size is 5, calling ShiftLeft( 10 )." );
        SmartDynamicArray<string> arr;
        arr.m_array = new string[5];
        arr.m_arraySize = 5;
        arr.m_itemCount = 5;

        bool exceptionOccurred = false;

        try
        {
            arr.ShiftLeft( 10 );
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


int SmartDynamicArrayTester::Test_ShiftRight()
{
    string functionName = "ShiftRight";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        SmartDynamicArray<int> arr;
        arr.m_array = new int[5];

        try                                     {
            arr.ShiftRight( 0 );
        }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Populate array, call ShiftRight, check positions" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        string originalValues[] = { "a", "b", "c", "d", "-" };

        SmartDynamicArray<string> arr;
        arr.m_array = new string[10];
        arr.m_arraySize = 10;
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
        Set_Comments( "Array size is 5, calling ShiftRight( 10 )." );
        SmartDynamicArray<string> arr;
        arr.m_array = new string[5];
        arr.m_arraySize = 5;
        arr.m_itemCount = 5;

        bool exceptionOccurred = false;

        try
        {
            arr.ShiftRight( 10 );
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

int SmartDynamicArrayTester::Test_Search()
{
    string functionName = "Search";
    Logger::OutHighlight( "TEST SET BEGIN", "SmartDynamicArrayTester::Test_" + functionName, 3 );
    StartTestSet( "Test_" + functionName, { functionName } );
    ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, string( "Implemented" ) );

        try                                     {   SmartDynamicArray<int> arr;     arr.Search( 10 );            }
        catch( NotImplementedException& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, search for an item." ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartDynamicArray<string> arr;
        arr.m_array = new string[5];
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_arraySize = 5;
        arr.m_itemCount = 3;

        if      ( !Set_Outputs( "Search( \"b\" )", 1, arr.Search( "b" ) ) )             { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Search for an item that isn't in the array." ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Searching for \"z\" in the array." );
        SmartDynamicArray<string> arr;
        arr.m_array = new string[5];
        arr.m_arraySize = 5;
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
