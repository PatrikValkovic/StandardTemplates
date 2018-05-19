cmake_minimum_required(VERSION 3.3)
project(Templates)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -O0 -g")


set(LIB_FILES
        libs/catch.h)
set(SOURCE_FILES
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
        src/BinomialTree.h
        src/BinomialHeap.h
        src/BinomialHeapLite.h)
set(TEST_FILES
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
        test/IntervalTests.h
        test/BinomialTreeTests.h
        test/BinomialHeapTests.h
        test/BinomialHeapLiteTests.h)
set(TEST_SOURCES
        test/TravisTests.cpp
        test/ArrayTests.cpp)

enable_testing()
foreach (name ${TEST_SOURCES})
    get_filename_component(basename "${name}" NAME_WE)
    add_executable(${basename} ${name} ${SOURCE_FILES} ${LIB_FILES})
    ADD_TEST(NAME ${basename} COMMAND $<TARGET_FILE:${basename}>)
endforeach ()