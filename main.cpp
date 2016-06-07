#ifndef _STALIB_
#include <stdlib.h>
#endif

#define ADDITIONAL_TESTS

#include "Templates.h"
#include "Tests/VectorTests.h"
#include "Tests/QueueTests.h"
#include "Tests/CondQueueTests.h"
#include "Tests/AlgorithmsTests.h"
#include "Tests/ListTests.h"
#include "Tests/PriorityQueueTests.h"
#include "Tests/StackTests.h"
#include "Tests/BinaryHeapTests.h"
#include "Tests/BinarySearchTreeTests.h"
#include "Tests/ArrayTests.h"
#include "Tests/IntervalTests.h"

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

    std::cout << "No errors" << std::endl;

    exit(0);
}