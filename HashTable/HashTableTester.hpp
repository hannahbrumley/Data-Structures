#ifndef _HASH_TABLE_TESTER_HPP
#define _HASH_TABLE_TESTER_HPP

#include <iostream>
#include <string>
using namespace std;

#include "HashTable.hpp"
#include "../../cutest/TesterBase.hpp"
#include "../../Utilities/Menu.hpp"
#include "../../Utilities/StringUtil.hpp"
#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/NullptrException.hpp"

class HashTableTester : public TesterBase
{
public:
    HashTableTester()
        : TesterBase( "test_result_hash_table.html" )
    {
        AddTest(TestListItem("Test_Constructor",                bind(&HashTableTester::Test_Constructor, this)));
        AddTest(TestListItem("Test_SetCollisionMethod",         bind(&HashTableTester::Test_SetCollisionMethod, this)));
        AddTest(TestListItem("Test_Size",                       bind(&HashTableTester::Test_Size, this)));
        AddTest(TestListItem("Test_Hash1",                      bind(&HashTableTester::Test_Hash1, this)));
        AddTest(TestListItem("Test_Hash2",                      bind(&HashTableTester::Test_Hash2, this)));
        AddTest(TestListItem("Test_LinearProbe",                bind(&HashTableTester::Test_LinearProbe, this)));
        AddTest(TestListItem("Test_QuadraticProbe",             bind(&HashTableTester::Test_QuadraticProbe, this)));
        AddTest(TestListItem("Test_Push",                       bind(&HashTableTester::Test_Push, this)));
        AddTest(TestListItem("Test_Get",                        bind(&HashTableTester::Test_Get, this)));
    }

    virtual ~HashTableTester() { }

private:
    int Test_Constructor();
    int Test_SetCollisionMethod();
    int Test_Size();
    int Test_Hash1();
    int Test_Hash2();
    int Test_LinearProbe();
    int Test_QuadraticProbe();
    int Test_Push();
    int Test_Get();

    void WriteTableValues( HashTable<int>& ht );
};

int HashTableTester::Test_Constructor()
{
    string functionName = "Constructor";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "HashTableTester::Test_" + functionName, {} );

    { /* TEST BEGIN ************************************************************/
        StartTest( "1. Default constructor sets array size to 5" );
        HashTable<string> ht;
        if ( !Set_Outputs( "ArraySize()", 5, ht.m_table.ArraySize() ) )     { TestFail(); }
        else /* ........................................................ */ { TestPass(); }
        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}


int HashTableTester::Test_SetCollisionMethod()
{
    string functionName = "SetCollisionMethod";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "HashTableTester::Test_" + functionName, {} );

    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /*P*/    StartTest( "0. Check if function " + functionName + " is implemented..." );
    /*R*/    bool prereqsImplemented = true;
    /*E*/    Set_ExpectedOutput( functionName, string( "Implemented" ) );
    /*R*/
    /*E*/    try                                     { HashTable<int> ht; ht.SetCollisionMethod( CollisionMethod::LINEAR ); }
    /*Q*/    catch ( NotImplementedException& ex )   { Set_Comments( ex.what() ); prereqsImplemented = false; }
    /* */    catch ( ... ) { }
    /* */
    /* */    if ( prereqsImplemented )   { PrereqTest_Success( functionName ); }
    /* */    else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "1. Check that SetCollisionMethod works for LINEAR." );
        HashTable<int> ht;
        ht.SetCollisionMethod( CollisionMethod::LINEAR );

        int expectedOutput = static_cast<int>( CollisionMethod::LINEAR );
        int actualOutput = static_cast<int>( ht.m_method );

        if      ( !Set_Outputs( "m_method", expectedOutput, actualOutput ) )    { TestFail(); }
        else /* .............................................................*/ { TestPass(); }

        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "2. Check that SetCollisionMethod works for QUADRATIC." );
        HashTable<int> ht;
        ht.SetCollisionMethod( CollisionMethod::QUADRATIC );

        int expectedOutput = static_cast<int>( CollisionMethod::QUADRATIC );
        int actualOutput = static_cast<int>( ht.m_method );

        if      ( !Set_Outputs( "m_method", expectedOutput, actualOutput ) )    { TestFail(); }
        else /* .............................................................*/ { TestPass(); }

        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "3. Check that SetCollisionMethod works for DOUBLE_HASH." );
        HashTable<int> ht;
        ht.SetCollisionMethod( CollisionMethod::DOUBLE_HASH );

        int expectedOutput = static_cast<int>( CollisionMethod::DOUBLE_HASH );
        int actualOutput = static_cast<int>( ht.m_method );

        if      ( !Set_Outputs( "m_method", expectedOutput, actualOutput ) )    { TestFail(); }
        else /* .............................................................*/ { TestPass(); }

        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}


int HashTableTester::Test_Size()
{
    string functionName = "Size";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "HashTableTester::Test_" + functionName, {} );

    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /*P*/    StartTest( "0. Check if function " + functionName + " is implemented..." );
    /*R*/    bool prereqsImplemented = true;
    /*E*/    Set_ExpectedOutput( functionName, string( "Implemented" ) );
    /*R*/
    /*E*/    try                                     { HashTable<int> ht; ht.Size(); }
    /*Q*/    catch ( NotImplementedException& ex )   { Set_Comments( ex.what() ); prereqsImplemented = false; }
    /* */    catch ( ... ) { }
    /* */
    /* */    if ( prereqsImplemented )   { PrereqTest_Success( functionName ); }
    /* */    else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "1. Check that Size returns the correct value when m_itemCount is 1." );
        HashTable<int> ht;
        ht.m_table.m_itemCount = 1;
        if      ( !Set_Outputs( "Size()", 1, ht.Size() ) )    { TestFail(); }
        else /* ...........................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "1. Check that Size returns the correct value when m_itemCount is 5." );
        HashTable<int> ht;
        ht.m_table.m_itemCount = 5;
        if      ( !Set_Outputs( "Size()", 5, ht.Size() ) )    { TestFail(); }
        else /* ...........................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}


int HashTableTester::Test_Hash1()
{
    string functionName = "Hash1";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "HashTableTester::Test_" + functionName, {} );

    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /*P*/    StartTest( "0. Check if function " + functionName + " is implemented..." );
    /*R*/    bool prereqsImplemented = true;
    /*E*/    Set_ExpectedOutput( functionName, string( "Implemented" ) );
    /*R*/
    /*E*/    try                                     { HashTable<int> ht; ht.Hash1( 0 ); }
    /*Q*/    catch ( NotImplementedException& ex )   { Set_Comments( ex.what() ); prereqsImplemented = false; }
    /* */    catch ( ... ) { }
    /* */
    /* */    if ( prereqsImplemented )   { PrereqTest_Success( functionName ); }
    /* */    else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    int counter = 1;

    // Check hash function for values < arraySize...
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        HashTable<int> ht;
        int arraySize = ht.m_table.ArraySize();

        for ( int key = 0; key < arraySize; key ++)
        {
            StartTest( StringUtil::ToString( counter ) + ". Check that Hash function works for a given key value." );
            counter++;
            Set_Comments( "Hash function is expected to be: key % m_table.ArraySize()" );
            Set_Comments( "Array size is " + StringUtil::ToString( arraySize ) );

            int expectedOutput = key;
            int actualOutput = ht.Hash1( key );
            string functionCall = "Hash1(" + StringUtil::ToString( key ) + ")";

            if      ( !Set_Outputs( functionCall, expectedOutput, actualOutput ) )    { TestFail(); }
            else /* ...............................................................*/ { TestPass(); }

            FinishTest();
        }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    // Check hash function for values >= arraySize...
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        HashTable<int> ht;
        int arraySize = ht.m_table.ArraySize();

        for ( int key = arraySize; key < arraySize*2; key ++)
        {
            StartTest( StringUtil::ToString( counter ) + ". Check that Hash function works for a given key value." );
            counter++;
            Set_Comments( "Hash function is expected to be: key % m_table.ArraySize()" );
            Set_Comments( "Array size is " + StringUtil::ToString( arraySize ) );

            int expectedOutput = key - arraySize;
            int actualOutput = ht.Hash1( key );
            string functionCall = "Hash1(" + StringUtil::ToString( key ) + ")";

            if      ( !Set_Outputs( functionCall, expectedOutput, actualOutput ) )    { TestFail(); }
            else /* ...............................................................*/ { TestPass(); }

            FinishTest();
        }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}


int HashTableTester::Test_Hash2()
{
    string functionName = "Hash2";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "HashTableTester::Test_" + functionName, { "Hash1" } );

    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /*P*/    StartTest( "0a. Check if function " + functionName + " is implemented..." );
    /*R*/    bool prereqsImplemented = true;
    /*E*/    Set_ExpectedOutput( functionName, string( "Implemented" ) );
    /*R*/
    /*E*/    try                                     { HashTable<int> ht; ht.Hash2( 0, 0 ); }
    /*Q*/    catch ( NotImplementedException& ex )   { Set_Comments( ex.what() ); prereqsImplemented = false; }
    /* */    catch ( ... ) { }
    /* */
    /* */    if ( prereqsImplemented )   { PrereqTest_Success( functionName ); }
    /* */    else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /*P*/    StartTest( "0b. Check if function Hash1 is implemented..." );
    /*R*/    bool prereqsImplemented = true;
    /*E*/    Set_ExpectedOutput( functionName, string( "Implemented" ) );
    /*R*/
    /*E*/    try                                     { HashTable<int> ht; ht.Hash1( 0 ); }
    /*Q*/    catch ( NotImplementedException& ex )   { Set_Comments( ex.what() ); prereqsImplemented = false; }
    /* */    catch ( ... ) { }
    /* */
    /* */    if ( prereqsImplemented )   { PrereqTest_Success( functionName ); }
    /* */    else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "1. Check that Hash2 returns correct index for key and collision amount." );
        Set_Comments( "Hash2 functionality expected to be..." );
        Set_Comments( "originalIndex = Hash1( key )" );
        Set_Comments( "stepForward = collisionCount * ( 3 - key % 3 )" );
        Set_Comments( "Return originalIndex + stepForward" );
        Set_Comments( "..." );
        Set_Comments( "Hash2( int key, int collisionCount )" );
        Set_Comments( "Hash2( 0, 1 ) expecting Hash1( 0 ) + 1 * ( 3 - 0 % 3 )" );

        HashTable<int> ht;
        int key = 0;
        int collisionCount = 1;
        int originalIndex = ht.Hash1( key );
        int newIndex = ht.Hash2( key, collisionCount );
        int expectedOutput = originalIndex + 1 * 3;

        if      ( !Set_Outputs( "Hash2( 0, 1 )", expectedOutput, newIndex ) )    { TestFail(); }
        else /* ..............................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "2. Check that Hash2 returns correct index for key and collision amount." );
        Set_Comments( "Hash2( int key, int collisionCount )" );
        Set_Comments( "Hash2( 0, 2 ) expecting Hash1( 0 ) + 2 * ( 3 - 0 % 3 )" );

        HashTable<int> ht;
        int key = 0;
        int collisionCount = 2;
        int originalIndex = ht.Hash1( key );
        int newIndex = ht.Hash2( key, collisionCount );
        int expectedOutput = originalIndex + 2 * 3;

        if      ( !Set_Outputs( "Hash2( 0, 2 )", expectedOutput, newIndex ) )    { TestFail(); }
        else /* ..............................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "3. Check that Hash2 returns correct index for key and collision amount." );
        Set_Comments( "Hash2( int key, int collisionCount )" );
        Set_Comments( "Hash2( 3, 2 ) expecting Hash1( 3 ) + 2 * ( 3 - 3 % 3 )" );

        HashTable<int> ht;
        int key = 3;
        int collisionCount = 2;
        int originalIndex = ht.Hash1( key );
        int newIndex = ht.Hash2( key, collisionCount );
        int expectedOutput = originalIndex + 2 * 3;

        if      ( !Set_Outputs( "Hash2( 3, 2 )", expectedOutput, newIndex ) )    { TestFail(); }
        else /* ..............................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "4. Check that Hash2 returns correct index for key and collision amount." );
        Set_Comments( "Hash2( int key, int collisionCount )" );
        Set_Comments( "Hash2( 2, 5 ) expecting Hash1( 2 ) + 5 * ( 3 - 2 % 3 )" );

        HashTable<int> ht;
        int key = 2;
        int collisionCount = 5;
        int originalIndex = ht.Hash1( key );
        int newIndex = ht.Hash2( key, collisionCount );
        int expectedOutput = originalIndex + 5 * 1;

        if      ( !Set_Outputs( "Hash2( 2, 5 )", expectedOutput, newIndex ) )    { TestFail(); }
        else /* ..............................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}


int HashTableTester::Test_LinearProbe()
{
    string functionName = "LinearProbe";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "HashTableTester::Test_" + functionName, {} );

    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /*P*/    StartTest( "0. Check if function " + functionName + " is implemented..." );
    /*R*/    bool prereqsImplemented = true;
    /*E*/    Set_ExpectedOutput( functionName, string( "Implemented" ) );
    /*R*/
    /*E*/    try                                     { HashTable<int> ht; ht.LinearProbe( 0, 0 ); }
    /*Q*/    catch ( NotImplementedException& ex )   { Set_Comments( ex.what() ); prereqsImplemented = false; }
    /* */    catch ( ... ) { }
    /* */
    /* */    if ( prereqsImplemented )   { PrereqTest_Success( functionName ); }
    /* */    else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "1. Check that LinearProbe returns correct index for key and collision amount." );
        Set_Comments( "Setting originalIndex to 0 and collisionCount to 1, expecting a new index of 1." );
        HashTable<int> ht;
        if      ( !Set_Outputs( "LinearProbe( 0, 1 )", 1, ht.LinearProbe( 0, 1 ) ) )    { TestFail(); }
        else /* .....................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "2. Check that LinearProbe returns correct index for key and collision amount." );
        Set_Comments( "Setting originalIndex to 0 and collisionCount to 2, expecting a new index of 2." );
        HashTable<int> ht;
        if      ( !Set_Outputs( "LinearProbe( 0, 2 )", 2, ht.LinearProbe( 0, 2 ) ) )    { TestFail(); }
        else /* .....................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "3. Check that LinearProbe returns correct index for key and collision amount." );
        Set_Comments( "Setting originalIndex to 3 and collisionCount to 2, expecting a new index of 5." );
        HashTable<int> ht;
        if      ( !Set_Outputs( "LinearProbe( 3, 2 )", 5, ht.LinearProbe( 3, 2 ) ) )    { TestFail(); }
        else /* .....................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}


int HashTableTester::Test_QuadraticProbe()
{
    string functionName = "QuadraticProbe";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "HashTableTester::Test_" + functionName, {} );

    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /*P*/    StartTest( "0. Check if function " + functionName + " is implemented..." );
    /*R*/    bool prereqsImplemented = true;
    /*E*/    Set_ExpectedOutput( functionName, string( "Implemented" ) );
    /*R*/
    /*E*/    try                                     { HashTable<int> ht; ht.QuadraticProbe( 0, 0 ); }
    /*Q*/    catch ( NotImplementedException& ex )   { Set_Comments( ex.what() ); prereqsImplemented = false; }
    /* */    catch ( ... ) { }
    /* */
    /* */    if ( prereqsImplemented )   { PrereqTest_Success( functionName ); }
    /* */    else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "1. Check that Quadratic returns correct index for key and collision amount." );
        Set_Comments( "Setting originalIndex to 0 and collisionCount to 1, expecting a new index of 0 + 1^2." );
        HashTable<int> ht;
        if      ( !Set_Outputs( "LinearProbe( 0, 1 )", 1, ht.QuadraticProbe( 0, 1 ) ) )    { TestFail(); }
        else /* ........................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "2. Check that Quadratic returns correct index for key and collision amount." );
        Set_Comments( "Setting originalIndex to 0 and collisionCount to 2, expecting a new index of 0 + 2^2." );
        HashTable<int> ht;
        if      ( !Set_Outputs( "LinearProbe( 0, 2 )", 4, ht.QuadraticProbe( 0, 2 ) ) )    { TestFail(); }
        else /* ........................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "3. Check that Quadratic returns correct index for key and collision amount." );
        Set_Comments( "Setting originalIndex to 0 and collisionCount to 2, expecting a new index of 0 + 3^2." );
        HashTable<int> ht;
        if      ( !Set_Outputs( "LinearProbe( 0, 3 )", 9, ht.QuadraticProbe( 0, 3 ) ) )    { TestFail(); }
        else /* ........................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "4. Check that Quadratic returns correct index for key and collision amount." );
        Set_Comments( "Setting originalIndex to 3 and collisionCount to 1, expecting a new index of 3 + 1^2." );
        HashTable<int> ht;
        if      ( !Set_Outputs( "LinearProbe( 3, 1 )", 4, ht.QuadraticProbe( 3, 1 ) ) )    { TestFail(); }
        else /* ........................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "5. Check that Quadratic returns correct index for key and collision amount." );
        Set_Comments( "Setting originalIndex to 3 and collisionCount to 2, expecting a new index of 3 + 2^2." );
        HashTable<int> ht;
        if      ( !Set_Outputs( "LinearProbe( 3, 2 )", 7, ht.QuadraticProbe( 3, 2 ) ) )    { TestFail(); }
        else /* ........................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "6. Check that Quadratic returns correct index for key and collision amount." );
        Set_Comments( "Setting originalIndex to 3 and collisionCount to 2, expecting a new index of 3 + 3^2." );
        HashTable<int> ht;
        if      ( !Set_Outputs( "LinearProbe( 3, 3 )", 12, ht.QuadraticProbe( 3, 3 ) ) )    { TestFail(); }
        else /* .........................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}


int HashTableTester::Test_Push()
{
    string functionName = "Push";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "HashTableTester::Test_" + functionName, { "Hash1", "LinearProbe", "QuadraticProbe", "Hash2" } );

    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /*P*/    StartTest( "0. Check if function " + functionName + " is implemented..." );
    /*R*/    bool prereqsImplemented = true;
    /*E*/    Set_ExpectedOutput( functionName, string( "Implemented" ) );
    /*R*/
    /*E*/    try                                     { HashTable<int> ht; ht.Push( 1, 123 ); }
    /*Q*/    catch ( NotImplementedException& ex )   { Set_Comments( ex.what() ); prereqsImplemented = false; }
    /* */    catch ( ... ) { }
    /* */
    /* */    if ( prereqsImplemented )   { PrereqTest_Success( functionName ); }
    /* */    else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "1. Push item into empty HashTable, check index." );
        Set_Comments( "Data is 100, Key is 0, expecting Index to be 0." );
        HashTable<int> ht;
        HashItem<int> item( 100, 0 );
        ht.Push( item.key, item.data );
        int index = 0;  // the key hashed should give us this
        HashItem<int>& returnItem = ht.m_table.GetAt( 0 );

        if          ( !Set_Outputs( "Size()", 1, ht.Size() ) )                                  { TestFail(); }
        else if     ( !Set_Outputs( "Keys match", item.key, returnItem.key ) )                  { TestFail(); }
        else if     ( !Set_Outputs( "Data matches", item.data, returnItem.data ) )              { TestFail(); }
        else /* .............................................................................*/ { TestPass(); }

        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "2. Push item into empty HashTable, check index." );
        Set_Comments( "Data is 333, Key is 3, expecting Index to be 3." );
        HashTable<int> ht;
        HashItem<int> item( 333, 3 );
        ht.Push( item.key, item.data );

        int index = 0;  // the key hashed should give us this

        try
        {
            if          ( !Set_Outputs( "Size()", 1, ht.Size() ) )                                  { TestFail(); }
            else if     ( !Set_Outputs( "Keys match", item.key, ht.m_table.GetAt( 3 ).key ) )       { TestFail(); }
            else if     ( !Set_Outputs( "Data matches", item.data, ht.m_table.GetAt( 3 ).data ) )   { TestFail(); }
            else /* .............................................................................*/ { TestPass(); }
        }
        catch( const ItemNotFoundException& ex )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (ItemNotFoundException): " + string( ex.what() ) );
            TestFail();
        }
        catch( ... )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (No info)" );
            TestFail();
        }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "3. Push two items into empty HashTable. Do checks." );
        Set_Comments( "Data is 333, Key is 3, expecting Index to be 3." );
        Set_Comments( "Data is 333, Key is 3, expecting Index to be 3." );
        HashTable<int> ht;
        HashItem<int> item1( 333, 3 );
        HashItem<int> item2( 111, 1 );
        ht.Push( item1.key, item1.data );
        ht.Push( item2.key, item2.data );

        int index = 0;  // the key hashed should give us this

        try
        {
            if          ( !Set_Outputs( "Size()", 2, ht.Size() ) )                                   { TestFail(); }
            else if     ( !Set_Outputs( "Index 1 key", item1.key, ht.m_table.GetAt( 3 ).key ) )      { TestFail(); }
            else if     ( !Set_Outputs( "Index 1 data", item1.data, ht.m_table.GetAt( 3 ).data ) )   { TestFail(); }
            else if     ( !Set_Outputs( "Index 3 key", item2.key, ht.m_table.GetAt( 1 ).key ) )      { TestFail(); }
            else if     ( !Set_Outputs( "Index 3 data", item2.data, ht.m_table.GetAt( 1 ).data ) )   { TestFail(); }
            else /* ..............................................................................*/ { TestPass(); }
        }
        catch( const ItemNotFoundException& ex )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (ItemNotFoundException): " + string( ex.what() ) );
            TestFail();
        }
        catch( ... )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (No info)" );
            TestFail();
        }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    // Checks with LINEAR collision method
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "L1. Push two items into empty HashTable. Check collision results." );
        Set_Comments( "Data is 111, Key is 0, expecting Index to be 0." );
        Set_Comments( "Data is 222, Key is 7, expecting Index to be 1." );
        HashTable<int> ht( 7 );
        ht.SetCollisionMethod( CollisionMethod::LINEAR );
        HashItem<int> item1( 111, 0 );
        HashItem<int> item2( 222, 7 );
        ht.Push( item1.key, item1.data );
        ht.Push( item2.key, item2.data );
        Set_Comments( "... ");
        WriteTableValues( ht );
        try
        {
            if          ( !Set_Outputs( "Size()", 2, ht.Size() ) )                                   { TestFail(); }
            else if     ( !Set_Outputs( "Index 0 key",  item1.key,  ht.m_table.GetAt( 0 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index 0 data", item1.data, ht.m_table.GetAt( 0 ).data ) )   { TestFail(); }
            else if     ( !Set_Outputs( "Index 1 key",  item2.key,  ht.m_table.GetAt( 1 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index 1 data", item2.data, ht.m_table.GetAt( 1 ).data ) )   { TestFail(); }
            else /* ..............................................................................*/ { TestPass(); }
        }
        catch( const ItemNotFoundException& ex )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (ItemNotFoundException): " + string( ex.what() ) );
            TestFail();
        }
        catch( ... )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (No info)" );
            TestFail();
        }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "L2. Push three items into empty HashTable. Check collision results." );
        Set_Comments( "Data is 111, Key is 1,   expecting Index to be 1." );
        Set_Comments( "Data is 222, Key is 8,   expecting Index to be 2." );
        Set_Comments( "Data is 333, Key is 15,  expecting Index to be 3." );
        HashTable<int> ht( 7 );
        ht.SetCollisionMethod( CollisionMethod::LINEAR );
        HashItem<int> item1( 111, 1 );
        HashItem<int> item2( 222, 8 );
        HashItem<int> item3( 333, 15 );
        ht.Push( item1.key, item1.data );
        ht.Push( item2.key, item2.data );
        ht.Push( item3.key, item3.data );
        Set_Comments( "... ");
        WriteTableValues( ht );
        try
        {
            if          ( !Set_Outputs( "Size()", 3, ht.Size() ) )                                   { TestFail(); }
            else if     ( !Set_Outputs( "Index 1 key",  item1.key,  ht.m_table.GetAt( 1 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index 1 data", item1.data, ht.m_table.GetAt( 1 ).data ) )   { TestFail(); }
            else if     ( !Set_Outputs( "Index 2 key",  item2.key,  ht.m_table.GetAt( 2 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index 2 data", item2.data, ht.m_table.GetAt( 2 ).data ) )   { TestFail(); }
            else if     ( !Set_Outputs( "Index 3 key",  item3.key,  ht.m_table.GetAt( 3 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index 3 data", item3.data, ht.m_table.GetAt( 3 ).data ) )   { TestFail(); }
            else /* ..............................................................................*/ { TestPass(); }
        }
        catch( const ItemNotFoundException& ex )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (ItemNotFoundException): " + string( ex.what() ) );
            TestFail();
        }
        catch( ... )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (No info)" );
            TestFail();
        }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    // Checks with QUADRATIC collision method
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "Q1. Push two items into empty HashTable. Check collision results." );
        Set_Comments( "Data is 111, Key is 0, expecting Index to be 0." );
        Set_Comments( "Data is 222, Key is 7, expecting Index to be 0 + 1^2." );
        HashTable<int> ht( 7 );
        ht.SetCollisionMethod( CollisionMethod::QUADRATIC );
        HashItem<int> item1( 111, 0 );
        HashItem<int> item2( 222, 7 );
        ht.Push( item1.key, item1.data );
        ht.Push( item2.key, item2.data );
        Set_Comments( "... ");
        WriteTableValues( ht );
        try
        {
            if          ( !Set_Outputs( "Size()", 2, ht.Size() ) )                                   { TestFail(); }
            else if     ( !Set_Outputs( "Index 0 key",  item1.key,  ht.m_table.GetAt( 0 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index 0 data", item1.data, ht.m_table.GetAt( 0 ).data ) )   { TestFail(); }
            else if     ( !Set_Outputs( "Index 1 key",  item2.key,  ht.m_table.GetAt( 1 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index 1 data", item2.data, ht.m_table.GetAt( 1 ).data ) )   { TestFail(); }
            else /* ..............................................................................*/ { TestPass(); }
        }
        catch( const ItemNotFoundException& ex )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (ItemNotFoundException): " + string( ex.what() ) );
            TestFail();
        }
        catch( ... )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (No info)" );
            TestFail();
        }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "Q2. Push items into empty HashTable. Check collision results." );
        HashTable<int> ht( 7 );
        ht.SetCollisionMethod( CollisionMethod::QUADRATIC );
        HashItem<int> item1( 111, (7*0)+1 );
        HashItem<int> item2( 222, (7*1)+1 );
        HashItem<int> item3( 333, (7*2)+1 );
        HashItem<int> item4( 444, (7*3)+1 );
        Set_Comments( "Data is 111, Key is " + StringUtil::ToString( item1.key ) + ",  expecting Index to be 1." );
        Set_Comments( "Data is 222, Key is " + StringUtil::ToString( item2.key ) + ",  expecting Index to be (1 + 1^2)%7." );
        Set_Comments( "Data is 333, Key is " + StringUtil::ToString( item3.key ) + ",  expecting Index to be (1 + 2^2)%7." );
        Set_Comments( "Data is 444, Key is " + StringUtil::ToString( item4.key ) + ",  expecting Index to be (1 + 3^2)%7." );
        ht.Push( item1.key, item1.data );
        ht.Push( item2.key, item2.data );
        ht.Push( item3.key, item3.data );
        ht.Push( item4.key, item4.data );
        Set_Comments( "... ");
        WriteTableValues( ht );

        try
        {
            if          ( !Set_Outputs( "Size()", 4, ht.Size() ) )                                       { TestFail(); }
            else if     ( !Set_Outputs( "Index 1 key",      item1.key,  ht.m_table.GetAt( 1 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index 1 data",     item1.data, ht.m_table.GetAt( 1 ).data ) )   { TestFail(); }
            else if     ( !Set_Outputs( "Index 2 key",      item2.key,  ht.m_table.GetAt( 2 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index 2 data",     item2.data, ht.m_table.GetAt( 2 ).data ) )   { TestFail(); }
            else if     ( !Set_Outputs( "Index 5 key",      item3.key,  ht.m_table.GetAt( 5 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index 5 data",     item3.data, ht.m_table.GetAt( 5 ).data ) )   { TestFail(); }
            else if     ( !Set_Outputs( "Index 3 key",      item4.key,  ht.m_table.GetAt( 3 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index 3 data",     item4.data, ht.m_table.GetAt( 3 ).data ) )   { TestFail(); }
            else /* ..................................................................................*/ { TestPass(); }
        }
        catch( const ItemNotFoundException& ex )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (ItemNotFoundException): " + string( ex.what() ) );
            TestFail();
        }
        catch( ... )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (No info)" );
            TestFail();
        }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    // Checks with DOUBLE_HASH collision method
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "D1. Push two items into empty HashTable. Check collision results." );
        Set_Comments( "Hash2 is expected to be:" );
        Set_Comments( "originalIndex = Hash1( key )" );
        Set_Comments( "stepForward = collisionCount * ( 3 - key % 3 )" );
        Set_Comments( "Return originalIndex + stepForward" );
        HashTable<int> ht( 7 );
        ht.SetCollisionMethod( CollisionMethod::DOUBLE_HASH );

        HashItem<int> item1( 111, 0 );
        HashItem<int> item2( 222, 7 );

        int expectedIndex1 = 0;
        int expectedIndex2 = 0 + 1 * ( 3 - 7 % 3 );
        string ei1 = StringUtil::ToString( expectedIndex1 );
        string ei2 = StringUtil::ToString( expectedIndex2 );

        Set_Comments( "..." );
        Set_Comments( "Data is 111, Key is 0, expecting Index to be 0 -- " + ei1 );
        Set_Comments( "Data is 222, Key is 7, expecting Index to be 0 + 1 * ( 3 - 7 % 3 ) -- " + ei2 );

        ht.Push( item1.key, item1.data );
        ht.Push( item2.key, item2.data );

        Set_Comments( "... ");
        WriteTableValues( ht );

        try
        {
            if          ( !Set_Outputs( "Size()", 2, ht.Size() ) )                                                          { TestFail(); }
            else if     ( !Set_Outputs( "Index " + ei1 + " key",  item1.key,  ht.m_table.GetAt( expectedIndex1 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index " + ei1 + " data", item1.data, ht.m_table.GetAt( expectedIndex1 ).data ) )   { TestFail(); }
            else if     ( !Set_Outputs( "Index " + ei2 + " key",  item2.key,  ht.m_table.GetAt( expectedIndex2 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index " + ei2 + " data", item2.data, ht.m_table.GetAt( expectedIndex2 ).data ) )   { TestFail(); }
            else /* .....................................................................................................*/ { TestPass(); }
        }
        catch( const ItemNotFoundException& ex )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (ItemNotFoundException): " + string( ex.what() ) );
            TestFail();
        }
        catch( ... )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (No info)" );
            TestFail();
        }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "D2. Push items into empty HashTable. Check collision results." );
        Set_Comments( "Hash2 is expected to be:" );
        Set_Comments( "originalIndex = Hash1( key )" );
        Set_Comments( "stepForward = collisionCount * ( 3 - key % 3 )" );
        Set_Comments( "Return originalIndex + stepForward" );
        HashTable<int> ht( 7 );
        ht.SetCollisionMethod( CollisionMethod::DOUBLE_HASH );
        HashItem<int> item1( 111, (7*0)+1 );    // key = 1
        HashItem<int> item2( 222, (7*1)+1 );    // key = 8
        HashItem<int> item3( 333, (7*2)+1 );    // key = 15
        HashItem<int> item4( 444, (7*3)+1 );    // key = 22

        int expectedIndex1 = 1;
        int expectedIndex2 = (1 + 1 * ( 3 - item2.key % 3 )) % 7;
        int expectedIndex3 = (1 + 1 * ( 3 - item3.key % 3 )) % 7;
        int expectedIndex4 = (1 + 1 * ( 3 - item4.key % 3 )) % 7;

        string ei1 = StringUtil::ToString( expectedIndex1 );
        string ei2 = StringUtil::ToString( expectedIndex2 );
        string ei3 = StringUtil::ToString( expectedIndex3 );
        string ei4 = StringUtil::ToString( expectedIndex4 );

        Set_Comments( "..." );
        Set_Comments( "Data is 111, Key is " + StringUtil::ToString( item1.key ) + ",  expecting Index to be 1 -- " + ei1 );
        Set_Comments( "Data is 222, Key is " + StringUtil::ToString( item2.key ) + ",  expecting Index to be (1 + 1 * (3 - 8 % 3))%7 -- " + ei2 );
        Set_Comments( "Data is 333, Key is " + StringUtil::ToString( item3.key ) + ",  expecting Index to be (1 + 1 * (3 - 15 % 3))%7 -- " + ei3 );
        Set_Comments( "Data is 444, Key is " + StringUtil::ToString( item4.key ) + ",  expecting Index to be (1 + 1 * (3 - 22 % 3))%7 -- " + ei4 );

        ht.Push( item1.key, item1.data );
        ht.Push( item2.key, item2.data );
        ht.Push( item3.key, item3.data );
        ht.Push( item4.key, item4.data );

        Set_Comments( "... ");
        WriteTableValues( ht );

        try
        {
            if          ( !Set_Outputs( "Size()", 4, ht.Size() ) )                                                              { TestFail(); }
            else if     ( !Set_Outputs( "Index " + ei1 + " key",      item1.key,  ht.m_table.GetAt( expectedIndex1 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index " + ei1 + " data",     item1.data, ht.m_table.GetAt( expectedIndex1 ).data ) )   { TestFail(); }
            else if     ( !Set_Outputs( "Index " + ei2 + " key",      item2.key,  ht.m_table.GetAt( expectedIndex2 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index " + ei2 + " data",     item2.data, ht.m_table.GetAt( expectedIndex2 ).data ) )   { TestFail(); }
            else if     ( !Set_Outputs( "Index " + ei3 + " key",      item3.key,  ht.m_table.GetAt( expectedIndex3 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index " + ei3 + " data",     item3.data, ht.m_table.GetAt( expectedIndex3 ).data ) )   { TestFail(); }
            else if     ( !Set_Outputs( "Index " + ei4 + " key",      item4.key,  ht.m_table.GetAt( expectedIndex4 ).key ) )    { TestFail(); }
            else if     ( !Set_Outputs( "Index " + ei4 + " data",     item4.data, ht.m_table.GetAt( expectedIndex4 ).data ) )   { TestFail(); }
            else /* .........................................................................................................*/ { TestPass(); }
        }
        catch( const ItemNotFoundException& ex )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (ItemNotFoundException): " + string( ex.what() ) );
            TestFail();
        }
        catch( ... )
        {
            Set_ExpectedOutput( "No exception thrown" );
            Set_ActualOutput( "EXCEPTION THROWN (No info)" );
            TestFail();
        }

        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int HashTableTester::Test_Get()
{
    string functionName = "Get";
    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
    StartTestSet( "HashTableTester::Test_" + functionName, {} );

    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /*P*/    StartTest( "0. Check if function " + functionName + " is implemented..." );
    /*R*/    bool prereqsImplemented = true;
    /*E*/    Set_ExpectedOutput( functionName, string( "Implemented" ) );
    /*R*/
    /*E*/    try                                     { HashTable<int> ht; ht.Get( 0 ); }
    /*Q*/    catch ( NotImplementedException& ex )   { Set_Comments( ex.what() ); prereqsImplemented = false; }
    /* */    catch ( ... ) { }
    /* */
    /* */    if ( prereqsImplemented )   { PrereqTest_Success( functionName ); }
    /* */    else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "1. Check that Get throws an exception when a key isn't stored in the table." );
        HashTable<int> ht;
        // Gotta put something in the table
        HashItem<int> item( 111, 0 );
        ht.m_table.PushAt( item, 0 );

        bool exceptionHappened = false;
        Set_ExpectedOutput( "Exception occurs", string( "true" ) );

        try
        {
            ht.Get( 1 );
        }
        catch( ItemNotFoundException& ex )
        {
            exceptionHappened = true;
            Set_Comments( ex.what() );
        }
        catch( runtime_error& ex )
        {
            Set_ActualOutput( "An exception was thrown, but it was a runtime_error: " );
            Set_Comments( ex.what() );
        }
        catch( ... )
        {
            Set_ActualOutput( "An exception was thrown, but not an ItemNotFoundException" );
        }

        if      ( !exceptionHappened )    { TestFail(); }
        else /* .......................*/ { TestPass(); }

        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "2. Add item to table, check that Get will return it." );
        Set_Comments( "Key: 0, Index: 0" );
        // SmartTable<HashItem<T>> m_table;
        // PushAt( T newItem, int index )
        HashTable<int> ht;
        HashItem<int> item( 100, 0 );
        ht.m_table.PushAt( item, 0 );

        WriteTableValues( ht );

        int expectedOutput = 100;
        int actualOutput = -1;
        try
        {
            actualOutput = ht.Get( 0 );
        }
        catch ( ... )
        {
            Set_ActualOutput( "Exception was thrown" );
        }
        if      ( !Set_Outputs( "Get( 0 )", expectedOutput, actualOutput ) )    { TestFail(); }
        else /* .............................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "2. Add one item to table, check that Get will return it." );
        HashTable<int> ht;
        int arraySize = ht.m_table.Size();

        HashItem<int> item( 100, arraySize + 1 );
        int index = 1;  // the key hashed should give us this
        ht.m_table.PushAt( item, index );

        Set_Comments( "Key: " + StringUtil::ToString( item.key ) + ", Index: " + StringUtil::ToString( index ) );
        WriteTableValues( ht );

        int actualOutput = -1;
        try             { actualOutput = ht.Get( item.key ); }
        catch ( ... )   { Set_ActualOutput( "Exception was thrown" ); }
        string keyStr = StringUtil::ToString( item.key );

        if      ( !Set_Outputs( "Get(" + keyStr + ") data", item.data, actualOutput ) )    { TestFail(); }
        else /* ........................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "3. Add some items to the table. Check that the right data will be returned even with collisions (LINEAR)." );
        HashTable<int> ht(5);
        ht.SetCollisionMethod( CollisionMethod::LINEAR );
        int arraySize = ht.m_table.ArraySize();

        HashItem<int> items[] = {
            HashItem<int>( 111, (0 * arraySize) + 1 ),
            HashItem<int>( 222, (1 * arraySize) + 1 ),
            HashItem<int>( 333, (2 * arraySize) + 1 )
        };

        for ( int i = 0; i < 3; i++ )
        {
            ht.m_table.PushAt( items[i], i+1 );
        }

        WriteTableValues( ht );

        int actualOutput = -1;
        try             { actualOutput = ht.Get( items[2].key ); }
        catch ( ... )   { Set_ActualOutput( "Exception was thrown" ); }
        string keyStr = StringUtil::ToString( items[2].key );

        if      ( !Set_Outputs( "Get(" + keyStr + ") data", items[2].data, actualOutput ) )    { TestFail(); }
        else /* ............................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "3. Add some items to the table. Check that the right data will be returned even with collisions (QUADRATIC)." );
        HashTable<int> ht(7);
        ht.SetCollisionMethod( CollisionMethod::QUADRATIC );
        int arraySize = ht.m_table.ArraySize();

        HashItem<int> items[] = {
            HashItem<int>( 111, (0 * arraySize) + 1 ),      // Key = 1, Index 1                     (OK)

            HashItem<int>( 222, (1 * arraySize) + 1 ),      // Key = 8, Index 1                     (Collision = 1)
                                                            //              -> Index 1 + 1^2 = 2    (OK)

            HashItem<int>( 333, (2 * arraySize) + 1 )       // Key = 15, Index 1                    (Collision = 1)
                                                            //              -> Index 1 + 1^2 = 2    (Collision = 2)
                                                            //              -> Index 1 + 2^2 = 5    (OK)
        };
        int indices[] = { 1, 2, 5 };

        for ( int i = 0; i < 3; i++ )
        {
            ht.m_table.PushAt( items[i], indices[i] );
        }

        WriteTableValues( ht );

        int actualOutput = -1;
        try             { actualOutput = ht.Get( items[2].key ); }
        catch ( StructureEmptyException& ex ) { Set_ActualOutput( "StructureEmptyException thrown" ); Set_Comments( ex.what() ); }
        catch ( ItemNotFoundException& ex ) { Set_ActualOutput( "ItemNotFoundException thrown" ); Set_Comments( ex.what() ); }
        catch ( runtime_error& ex ) { Set_ActualOutput( "runtime_error thrown" ); Set_Comments( ex.what() ); }
        catch ( ... )   { Set_ActualOutput( "Exception was thrown" ); }
        string keyStr = StringUtil::ToString( items[2].key );

        if      ( !Set_Outputs( "Get(" + keyStr + ") data", items[2].data, actualOutput ) )    { TestFail(); }
        else /* ............................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        StartTest( "3. Add some items to the table. Check that the right data will be returned even with collisions (DOUBLE_HASH)." );
        HashTable<int> ht(7);
        ht.SetCollisionMethod( CollisionMethod::DOUBLE_HASH );
        int arraySize = ht.m_table.ArraySize();

        HashItem<int> items[] = {
            HashItem<int>( 111, (0 * arraySize) + 1 ),      // Key = 1, Index 1                                 (OK)

            HashItem<int>( 222, (1 * arraySize) + 1 ),      // Key = 8, Index 1                                 (Collision = 1)
                                                            //              -> Index 1 + 1 * ( 3 - 8 % 3 ) = 2  (OK)

            HashItem<int>( 333, (2 * arraySize) + 1 )       // Key = 15, Index 1                                (Collision = 1)
                                                            //              -> Index 1 + 1 * ( 3 - 15 % 3 ) = 4 (OK)
        };
        int indices[] = { 1, 2, 4 };

        for ( int i = 0; i < 3; i++ )
        {
            ht.m_table.PushAt( items[i], indices[i] );
        }

        WriteTableValues( ht );

        int actualOutput = -1;
        try             { actualOutput = ht.Get( items[2].key ); }
        catch ( StructureEmptyException& ex ) { Set_ActualOutput( "StructureEmptyException thrown" ); Set_Comments( ex.what() ); }
        catch ( ItemNotFoundException& ex ) { Set_ActualOutput( "ItemNotFoundException thrown" ); Set_Comments( ex.what() ); }
        catch ( runtime_error& ex ) { Set_ActualOutput( "runtime_error thrown" ); Set_Comments( ex.what() ); }
        catch ( ... )   { Set_ActualOutput( "Exception was thrown" ); }
        string keyStr = StringUtil::ToString( items[2].key );

        if      ( !Set_Outputs( "Get(" + keyStr + ") data", items[2].data, actualOutput ) )    { TestFail(); }
        else /* ............................................................................*/ { TestPass(); }
        FinishTest();
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}


//int HashTableTester::Test_Template()
//{
//    string functionName = "Template";
//    Logger::OutHighlight( "TEST SET BEGIN", functionName, 3 );
//    StartTestSet( "HashTableTester::Test_" + functionName, {} );
//
//    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
//    /*P*/    StartTest( "0. Check if function " + functionName + " is implemented..." );
//    /*R*/    bool prereqsImplemented = true;
//    /*E*/    Set_ExpectedOutput( functionName, string( "Implemented" ) );
//    /*R*/
//    /*E*/    try                                     { HashTable<int> ht; ht.SetCollisionMethod( CollisionMethod::LINEAR ); }
//    /*Q*/    catch ( NotImplementedException& ex )   { Set_Comments( ex.what() ); prereqsImplemented = false; }
//    /* */    catch ( ... ) { }
//    /* */
//    /* */    if ( prereqsImplemented )   { PrereqTest_Success( functionName ); }
//    /* */    else                        { return PrereqTest_Abort( functionName ); }
//    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
//
//    { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
//        StartTest( "3. Check that SetCollisionMethod works for DOUBLE_HASH." );
//        HashTable<int> ht;
//        ht.SetCollisionMethod( CollisionMethod::DOUBLE_HASH );
//
//        int expectedOutput = static_cast<int>( CollisionMethod::DOUBLE_HASH );
//        int actualOutput = static_cast<int>( ht.m_method );
//
//        if      ( !Set_Outputs( "m_method", expectedOutput, actualOutput ) )    { TestFail(); }
//        else /* .............................................................*/ { TestPass(); }
//
//        FinishTest();
//    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
//
//    FinishTestSet();
//    return TestResult();
//}

void HashTableTester::WriteTableValues( HashTable<int>& ht )
{
    Set_Comments( "Table layout:" );
    for ( int i = 0; i < ht.m_table.ArraySize(); i++ )
    {
        try                                         { Set_Comments( "Index = " + StringUtil::ToString( i ) + ", Key = " + StringUtil::ToString( ht.m_table.GetAt( i ).key ) ); }
        catch( const ItemNotFoundException& ex )    { Set_Comments( "Index = " + StringUtil::ToString( i ) + ", not used" ); Logger::Out( ex.what() ); }
    }
}

#endif

