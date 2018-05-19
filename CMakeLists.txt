cmake_minimum_required(VERSION 3.3)
project(Templates)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -O0 -g")

set(SOURCE_FILES
        main.cpp
        src/Algorithms.h
        src/BinaryHeap.h
        src/BinarySearchTree.h
        src/CondQueue.h
        src/Exceptions.h
        src/IteratorsDefinitions.h
        src/List.h
        src/PriorityQueue.h
        src/Queue.h
        src/Stack.h
        Templates.h
        src/Vector.h
        src/Array.h
        src/Interval.h
        test/AlgorithmsTests.h
        test/BinaryHeapTests.h
        test/BinarySearchTreeTests.h
        test/CondQueueTests.h
        test/ListTests.h
        test/PriorityQueueTests.h
        test/QueueTests.h
        test/StackTests.h
        test/VectorTests.h
        test/ArrayTests.h
        test/IntervalTests.h src/BinomialTree.h test/BinomialTreeTests.h src/BinomialHeap.h test/BinomialHeapTests.h src/BinomialHeapLite.h test/BinomialHeapLiteTests.h)
add_executable(Templates ${SOURCE_FILES})