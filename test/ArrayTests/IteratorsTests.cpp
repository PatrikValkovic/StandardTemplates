#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#define private public
#include "../../Templates.h"
using namespace Templates;

int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
Array<int>::Iterator iter;

TEST_CASE("Should traverse Array by iterator forward"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(!iter.Back());
    for (int a = 0; a < 15; a++)
    {
        REQUIRE(*iter.GetValue() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
    REQUIRE(!iter.Next());
}

TEST_CASE("Should traverse Array by iterator backward"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(!iter.Next());
    for (int a = 14; a >= 0; a--)
    {
        REQUIRE(iter.Back());
        REQUIRE(*iter.GetValue() == OriginalArray[a]);
    }
    REQUIRE(!iter.Back());
}

TEST_CASE("Should create Array iterator at specific position"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    for (int a = 5; a < 15; a++)
    {
        REQUIRE(*iter.GetValue() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
}

TEST_CASE("Array iterator should jump to beginning"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    iter.JumpToBegin();
    REQUIRE(!iter.Back());
    for (int a = 0; a < 15; a++)
    {
        REQUIRE(*iter.GetValue() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
    REQUIRE(!iter.Next());
}

TEST_CASE("Array iterator should move forward more positions"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(iter.Next(5));
    for (int a = 5; a < 15; a++)
    {
        REQUIRE(*iter.GetValue() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
    REQUIRE(!iter.Next());
}

TEST_CASE("Array iterator should move backward more positions"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.Back(4));
    for (int a = 10; a >= 0; a--)
    {
        REQUIRE(*iter.GetValue() == OriginalArray[a]);
        REQUIRE(iter.Back());
    }
    REQUIRE(!iter.Back());
}

TEST_CASE("Array iterator should not move backward more than size"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(!iter.Back(24));
}

TEST_CASE("Array iterator should not move forward more that size"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(!iter.Next(25));
}
