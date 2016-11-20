cmake_minimum_required(VERSION 3.3)
project(Templates)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -O0 -g")

set(SOURCE_FILES
        main.cpp
        Algorithms.h
        BinaryHeap.h
        BinarySearchTree.h
        CondQueue.h
        Exceptions.h
        IteratorsDefinitions.h
        List.h
        PriorityQueue.h
        Queue.h
        Stack.h
        Templates.h
        Vector.h
        Array.h
        Interval.h
        Tests/AlgorithmsTests.h
        Tests/BinaryHeapTests.h
        Tests/BinarySearchTreeTests.h
        Tests/CondQueueTests.h
        Tests/ListTests.h
        Tests/PriorityQueueTests.h
        Tests/QueueTests.h
        Tests/StackTests.h
        Tests/VectorTests.h
        Tests/ArrayTests.h
        Tests/IntervalTests.h BinomialTree.h Tests/BinomialTreeTests.h BinomialHeap.h Tests/BinomialHeapTests.h BinomialHeapLite.h)
add_executable(Templates ${SOURCE_FILES})