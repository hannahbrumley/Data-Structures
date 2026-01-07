#ifndef _QUEUE_TESTER_HPP
#define _QUEUE_TESTER_HPP

#include <iostream>
#include <string>
using namespace std;

#include "ArrayQueue.hpp"
#include "LinkedQueue.hpp"
#include "../../cutest/TesterBase.hpp"
#include "../../Utilities/Menu.hpp"
#include "../../Utilities/StringUtil.hpp"
#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/NullptrException.hpp"

class QueueTester : public TesterBase
{
public:
    QueueTester()
        : TesterBase( "test_result_queue.html" )
    {
        AddTest(TestListItem("Test_ArrayQueue",              bind(&QueueTester::Test_ArrayQueue, this)));
        AddTest(TestListItem("Test_LinkedQueue",             bind(&QueueTester::Test_LinkedQueue, this)));
    }

    virtual ~QueueTester() { }

private:
    int Test_ArrayQueue();
    int Test_LinkedQueue();
};

int QueueTester::Test_ArrayQueue()
{
    StartTestSet( "QueueTester::Test_ArrayQueue", { "Push", "Get", "Pop", "Size", "IsEmpty" } );
    Logger::Out( "Beginning test", "QueueTester::ArrayQueue" );

    bool exceptOccur = false;
    {
        /* TEST BEGIN ************************************************************/
        StartTest( "ArrayQueue - Check if Push, Get, Pop, Size, and IsEmpty is implemented" );
        try
        {
            ArrayQueue<string> q;
            q.Push( "hi" );
            q.Front();
            q.Pop();
            q.Size();
            q.IsEmpty();
        }
        catch( runtime_error& ex )
        {
            exceptOccur = true;
            TestFail();
            Logger::Out( "EX: " + string(ex.what()) + " -- ArrayQueue not fully implemented. Skipping the rest of this test set.", "VectorTester::Test_LinkedQueue" );
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
        StartTest( "ArrayQueue - Empty queue, check if IsEmpty returns true." );

        ArrayQueue<string> q;

        bool expectedResult = true;
        bool actualResult = q.IsEmpty();

        if ( actualResult != expectedResult )   { TestFail(); }
        else                                    { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    { /* TEST BEGIN ************************************************************/
        StartTest( "ArrayQueue - Add to queue, check if IsEmpty is false" );

        ArrayQueue<string> q;
        q.Push( "A" );

        bool expectedResult = false;
        bool actualResult = q.IsEmpty();

        if ( actualResult != expectedResult )   { TestFail(); }
        else                                    { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    { /* TEST BEGIN ************************************************************/
        StartTest( "ArrayQueue - Push items, check Size." );

        ArrayQueue<string> q;
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
        StartTest( "ArrayQueue - Push items, use Get and Pop to validate." );

        ArrayQueue<string> q;
        q.Push( "A" );
        q.Push( "B" );
        q.Push( "C" );

        string expectedResult[] = { "A", "B", "C" };

        bool allMatch = true;
        for ( int i = 0; i < 3; i++ )
        {
            string frontValue = q.Front();
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

int QueueTester::Test_LinkedQueue()
{
    StartTestSet( "QueueTester::Test_LinkedQueue", { "Push", "Get", "Pop", "Size", "IsEmpty" } );
    Logger::Out( "Beginning test", "QueueTester::LinkedQueue" );

    bool exceptOccur = false;
    {
        /* TEST BEGIN ************************************************************/
        StartTest( "LinkedQueue - Check if Push, Get, Pop, Size, and IsEmpty is implemented" );
        try
        {
            LinkedQueue<string> q;
            q.Push( "hi" );
            q.Front();
            q.Pop();
            q.Size();
            q.IsEmpty();
        }
        catch( const runtime_error& ex )
        {
            exceptOccur = true;
            TestFail();
            Logger::Out( "EX: " + string( ex.what() ) + " -- LinkedQueue not fully implemented. Skipping the rest of this test set.", "VectorTester::Test_LinkedQueue" );
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
        StartTest( "LinkedQueue - Empty queue, check if IsEmpty returns true." );

        LinkedQueue<string> q;

        bool expectedResult = true;
        bool actualResult = q.IsEmpty();

        if ( actualResult != expectedResult )   { TestFail(); }
        else                                    { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    { /* TEST BEGIN ************************************************************/
        StartTest( "LinkedQueue - Add to queue, check if IsEmpty is false" );

        LinkedQueue<string> q;
        q.Push( "A" );

        bool expectedResult = false;
        bool actualResult = q.IsEmpty();

        if ( actualResult != expectedResult )   { TestFail(); }
        else                                    { TestPass(); }

        FinishTest();
    } /* TEST END **************************************************************/

    { /* TEST BEGIN ************************************************************/
        StartTest( "LinkedQueue - Push items, check Size." );

        LinkedQueue<string> q;
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
        StartTest( "LinkedQueue - Push items, use Get and Pop to validate." );

        LinkedQueue<string> q;
        q.Push( "A" );
        q.Push( "B" );
        q.Push( "C" );

        string expectedResult[] = { "A", "B", "C" };

        bool allMatch = true;
        for ( int i = 0; i < 3; i++ )
        {
            string frontValue = q.Front();
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
