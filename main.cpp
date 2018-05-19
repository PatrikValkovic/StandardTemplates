#ifndef _STALIB_
#include <stdlib.h>
#endif

#define ADDITIONAL_TESTS

#include "Templates.h"
#include "test/VectorTests.h"
#include "test/QueueTests.h"
#include "test/CondQueueTests.h"
#include "test/AlgorithmsTests.h"
#include "test/ListTests.h"
#include "test/PriorityQueueTests.h"
#include "test/StackTests.h"
#include "test/BinaryHeapTests.h"
#include "test/BinarySearchTreeTests.h"
#include "test/ArrayTests.h"
#include "test/IntervalTests.h"
#include "test/BinomialTreeTests.h"
#include "test/BinomialHeapTests.h"
#include "test/BinomialHeapLiteTests.h"

int main()
{
    IntervalTests::tests();
    VectorTest::test();
    QueueTests::test();
    CondQueueTests::test();
    AlgorithmsTests::test();
    ListTests::test();
    PriorityQueueTests::test();
    StackTests::test();
    ArrayTests::tests();
    BinaryHeapTests::tests();
    BinarySearchTreeTests::tests();
    BinomialTreeTest::tests();
    BinomialHeapTests::tests();
    BinomialHeapLiteTests::tests();

    std::cout << "No errors" << std::endl;

    exit(0);
}