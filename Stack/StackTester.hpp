#ifndef _STACK_TESTER_HPP
#define _STACK_TESTER_HPP

#include <iostream>
#include <string>
using namespace std;

#include "ArrayStack.hpp"
#include "LinkedStack.hpp"
#include "../../cutest/TesterBase.hpp"
#include "../../Utilities/Menu.hpp"
#include "../../Utilities/StringUtil.hpp"
#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/NullptrException.hpp"

class StackTester : public TesterBase
{
public:
    StackTester()
        : TesterBase( "test_result_stack.html" )
    {
        AddTest(TestListItem("Test_ArrayStack",              bind(&StackTester::Test_ArrayStack, this)));
        AddTest(TestListItem("Test_LinkedStack",             bind(&StackTester::Test_LinkedStack, this)));
    }

    virtual ~StackTester() { }

private:
    int Test_ArrayStack();
    int Test_LinkedStack();
};

int StackTester::Test_ArrayStack()
{
    StartTestSet( "StackTester::Test_ArrayStack", { "Push", "Get", "Pop", "Size", "IsEmpty" } );
    Logger::Out( "Beginning test", "StackTester::ArrayStack" );

    bool exceptOccur = false;
    {
        /* TEST BEGIN ************************************************************/
        StartTest( "ArrayStack - Check if Push, Get, Pop, Size, and IsEmpty is implemented" );
        try
        {
            ArrayStack<string> q;
            q.Push( "hi" );
            q.Top();
            q.Pop();
            q.Size();
            q.IsEmpty();
        }
        catch( runtime_error& ex )
        {
            exceptOccur = true;
            TestFail();
            Logger::Out( "EX: " + string(ex.what()) + " -- ArrayStack not fully implemented. Skipping the rest of this test set.", "VectorTester::Test_LinkedStack" );
        }

        if ( !exceptOccur )
        {
            TestPass();
        }
        FinishTest();
    } /* TEST END **************************************************************/

    if ( exceptOccur )
    {
        FinishTestSet();
        return TestResult();
    }

    { /* TEST BEGIN ************************************************************/
        StartTest( "ArrayStack - Empty Stack, check if IsEmpty returns true." );

        ArrayStack<string> q;

        bool expectedResult = true;
        bool actualResult = q.IsEmpty();

        if ( actualResult != expectedResult )   { TestFail(); }
        else                                    { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    { /* TEST BEGIN ************************************************************/
        StartTest( "ArrayStack - Add to Stack, check if IsEmpty is false" );

        ArrayStack<string> q;
        q.Push( "A" );

        bool expectedResult = false;
        bool actualResult = q.IsEmpty();

        if ( actualResult != expectedResult )   { TestFail(); }
        else                                    { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    { /* TEST BEGIN ************************************************************/
        StartTest( "ArrayStack - Push items, check Size." );

        ArrayStack<string> q;
        q.Push( "A" );
        q.Push( "B" );
        q.Push( "C" );

        int expectedResult = 3;
        int actualResult = q.Size();

        if ( actualResult != expectedResult )   { TestFail(); }
        else                                    { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    { /* TEST BEGIN ************************************************************/
        StartTest( "ArrayStack - Push items, use Get and Pop to validate." );

        ArrayStack<string> q;
        q.Push( "A" );
        q.Push( "B" );
        q.Push( "C" );

        string expectedResult[] = { "C", "B", "A" };

        bool allMatch = true;
        for ( int i = 0; i < 3; i++ )
        {
            string frontValue = q.Top();
            q.Pop();

            Set_ExpectedOutput  ( "Element " + StringUtil::ToString( i ), expectedResult[i] );
            Set_ActualOutput    ( "Element " + StringUtil::ToString( i ), frontValue );

            if ( frontValue != expectedResult[i] )
            {
                allMatch = false;
            }
        }

        if ( !allMatch )    { TestFail(); }
        else                { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}

int StackTester::Test_LinkedStack()
{
    StartTestSet( "StackTester::Test_LinkedStack", { "Push", "Get", "Pop", "Size", "IsEmpty" } );
    Logger::Out( "Beginning test", "StackTester::LinkedStack" );

    bool exceptOccur = false;
    {
        /* TEST BEGIN ************************************************************/
        StartTest( "LinkedStack - Check if Push, Get, Pop, Size, and IsEmpty is implemented" );
        try
        {
            LinkedStack<string> q;
            q.Push( "hi" );
            q.Top();
            q.Pop();
            q.Size();
            q.IsEmpty();
        }
        catch( runtime_error& ex )
        {
            exceptOccur = true;
            TestFail();
            Logger::Out( "EX: " + string(ex.what()) + " -- LinkedStack not fully implemented. Skipping the rest of this test set.", "VectorTester::Test_LinkedStack" );
        }

        if ( !exceptOccur )
        {
            TestPass();
        }
        FinishTest();
    } /* TEST END **************************************************************/

    if ( exceptOccur )
    {
        FinishTestSet();
        return TestResult();
    }

    { /* TEST BEGIN ************************************************************/
        StartTest( "LinkedStack - Empty Stack, check if IsEmpty returns true." );

        LinkedStack<string> q;

        bool expectedResult = true;
        bool actualResult = q.IsEmpty();

        if ( actualResult != expectedResult )   { TestFail(); }
        else                                    { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    { /* TEST BEGIN ************************************************************/
        StartTest( "LinkedStack - Add to Stack, check if IsEmpty is false" );

        LinkedStack<string> q;
        q.Push( "A" );

        bool expectedResult = false;
        bool actualResult = q.IsEmpty();

        if ( actualResult != expectedResult )   { TestFail(); }
        else                                    { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    { /* TEST BEGIN ************************************************************/
        StartTest( "LinkedStack - Push items, check Size." );

        LinkedStack<string> q;
        q.Push( "A" );
        q.Push( "B" );
        q.Push( "C" );

        int expectedResult = 3;
        int actualResult = q.Size();

        if ( actualResult != expectedResult )   { TestFail(); }
        else                                    { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    { /* TEST BEGIN ************************************************************/
        StartTest( "LinkedStack - Push items, use Get and Pop to validate." );

        LinkedStack<string> q;
        q.Push( "A" );
        q.Push( "B" );
        q.Push( "C" );

        string expectedResult[] = { "C", "B", "A" };

        bool allMatch = true;
        for ( int i = 0; i < 3; i++ )
        {
            string frontValue = q.Top();
            q.Pop();

            Set_ExpectedOutput  ( "Element " + StringUtil::ToString( i ), expectedResult[i] );
            Set_ActualOutput    ( "Element " + StringUtil::ToString( i ), frontValue );

            if ( frontValue != expectedResult[i] )
            {
                allMatch = false;
            }
        }

        if ( !allMatch )    { TestFail(); }
        else                { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    FinishTestSet();
    return TestResult();
}



#endif
