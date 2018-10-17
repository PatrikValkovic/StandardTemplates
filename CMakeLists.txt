cmake_minimum_required(VERSION 3.3)
project(Templates)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -O0 -g")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage --coverage")
endif()

set(LIB_FILES
        libs/catch.h)
set(SOURCE_FILES
        Templates.h
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
        src/Vector.h
        src/Array.h
        src/Interval.h
        src/BinomialTree.h
        src/BinomialHeap.h
        src/BinomialHeapLite.h
        src/Basis.h
		src/Meta.h
        src/UniquePointer.h
        src/SharedPointer.h)
set(TEST_FILES
        test/AlgorithmsTests.cpp
        test/BinaryHeapTests.cpp
        test/BinarySearchTreeTests.cpp
        test/CondQueueTests.cpp
        test/ListTests.cpp
        test/PriorityQueueTests.cpp
        test/QueueTests.cpp
        test/StackTests.cpp
        test/VectorTests.cpp
        test/IntervalTests.cpp
        test/BinomialTreeTests.cpp
        test/BinomialHeapTests.cpp
        test/BinomialHeapLiteTests.cpp)
set(TEST_SOURCES ${TEST_FILES}
        test/TravisTests.cpp
        test/ArrayTests/CreationTests.cpp
        test/ArrayTests/DeleteTests.cpp
        test/ArrayTests/ShiftingTests.cpp
        test/ArrayTests/ToArrayTests.cpp
        test/ArrayTests/IteratorsTests.cpp
        test/ArrayTests/IteratorsDeleteTests.cpp
        test/ArrayTests/ArraySwapTests.cpp
        test/ArrayTests/PushTests.cpp
        test/ArrayTests/IteratorInsertTests.cpp
        test/SwapTests.cpp
        test/Meta/AreSameTests.cpp
        test/Meta/TrueFalseTests.cpp
        test/Meta/AddConstTests.cpp
        test/Meta/AsConstRefTests.cpp
        test/Meta/AsRefTests.cpp
        test/Meta/AsRRefTests.cpp
        test/Meta/RemoveReferenceTests.cpp
        test/Meta/EnableIfTests.cpp
        test/Meta/IsConstructibleDefault.cpp
        test/Meta/DeclvalTests.cpp
        test/Meta/AndTests.cpp
        test/Meta/OrTests.cpp
        test/Meta/IsLValueReferenceTests.cpp
        test/Meta/IsRValueReferenceTests.cpp
        test/Meta/IsReferenceTests.cpp
        test/Meta/IsAssignableTests.cpp
        test/Meta/IsConstructibleMovable.cpp
        test/Meta/IsConstructibleCopyable.cpp
        test/Meta/IsAssignableCopyTests.cpp
        test/Meta/IsAssignableMoveTests.cpp
        test/MallocFreeTests.cpp
        test/Pointers/UniquePointerTests.cpp
        test/Pointers/SharedPointerTests.cpp)

find_program( VALGRIND_PROGRAM valgrind )
set( CTEST_MEMORYCHECK_COMMAND ${VALGRIND_PROGRAM})
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --log-fd=1")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} -q")
unset(CTEST_MEMORYCHECK_SUPPRESSIONS_FILE)

include (CTest)
enable_testing()
foreach (name ${TEST_SOURCES})
    get_filename_component(basename "${name}" NAME_WE)
    add_executable(${basename} ${name} ${SOURCE_FILES} ${LIB_FILES})
    ADD_TEST(NAME ${basename} COMMAND $<TARGET_FILE:${basename}>)
endforeach ()