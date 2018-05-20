#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#define private public
#include "../../Templates.h"
using namespace Templates;

int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
int SecondArray[5] = {100,101,102,103,104};
Array<int>::Iterator iter;

TEST_CASE("Array iterator should insert one item after beginning"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(iter.Insert(24) == 1);
    REQUIRE(instance.Size() == 16);
    for(int i=0;i<1;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    REQUIRE(instance[1] == 24);
    for(int i=2;i<16;i++)
        REQUIRE(instance[i] == OriginalArray[i - 1]);
}

TEST_CASE("Array iterator should insert one item after specific position"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    REQUIRE(iter.Insert(24) == 1);
    REQUIRE(instance.Size() == 16);
    for(int i=0;i<6;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    REQUIRE(instance[6] == 24);
    for(int i=7;i<16;i++)
        REQUIRE(instance[i] == OriginalArray[i - 1]);
}

TEST_CASE("Array iterator should insert one item after end"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.Insert(24) == 0); /* TODO should insert */
    REQUIRE(instance.Size() == 15);
}

TEST_CASE("Array iterator should insert more items after beginning"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(iter.Insert(SecondArray, 5) == 5);
    REQUIRE(instance.Size() == 20);
    for(int i=0;i<1;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for(int i=1;i<6;i++)
        REQUIRE(instance[i] == SecondArray[i - 1]);
    for(int i=6;i<20;i++)
        REQUIRE(instance[i] == OriginalArray[i - 5]);
}

TEST_CASE("Array iterator should insert more items after specific position"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    REQUIRE(iter.Insert(SecondArray, 5) == 5);
    REQUIRE(instance.Size() == 20);
    for(int i=0;i<6;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for(int i=6;i<11;i++)
        REQUIRE(instance[i] == SecondArray[i - 6]);
    for(int i=11;i<20;i++)
        REQUIRE(instance[i] == OriginalArray[i - 5]);
}

TEST_CASE("Array iterator should insert more items after end"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.Insert(SecondArray, 5) == 0); /* TODO should insert */
    REQUIRE(instance.Size() == 15);
}

TEST_CASE("Array iterator should insert one item before beginning"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(iter.InsertBefore(24) == 1);
    REQUIRE(instance.Size() == 16);
    REQUIRE(instance[0] == 24);
    for(int i=1;i<16;i++)
        REQUIRE(instance[i] == OriginalArray[i - 1]);
}

TEST_CASE("Array iterator should insert one item before specific position"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    REQUIRE(iter.InsertBefore(24) == 1);
    REQUIRE(instance.Size() == 16);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    REQUIRE(instance[5] == 24);
    for(int i=6;i<16;i++)
        REQUIRE(instance[i] == OriginalArray[i - 1]);
}

TEST_CASE("Array iterator should insert one item before end"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.InsertBefore(24) == 1);
    REQUIRE(instance.Size() == 16);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    REQUIRE(instance[15] == 24);
}

TEST_CASE("Array iterator should insert more items before beginning"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(iter.InsertBefore(SecondArray, 5) == 5);
    REQUIRE(instance.Size() == 20);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == SecondArray[i]);
    for(int i=5;i<20;i++)
        REQUIRE(instance[i] == OriginalArray[i - 5]);
}

TEST_CASE("Array iterator should insert more items before specific position"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    REQUIRE(iter.InsertBefore(SecondArray, 5) == 5);
    REQUIRE(instance.Size() == 20);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for(int i=5;i<10;i++)
        REQUIRE(instance[i] == SecondArray[i - 5]);
    for(int i=10;i<20;i++)
        REQUIRE(instance[i] == OriginalArray[i - 5]);
}

TEST_CASE("Array iterator should insert more items before end"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.InsertBefore(SecondArray, 5) == 5);
    REQUIRE(instance.Size() == 20);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for(int i=15;i<20;i++)
        REQUIRE(instance[i] == SecondArray[i - 15]);
}
