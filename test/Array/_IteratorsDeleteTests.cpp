#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;

/*
int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
Array<int>::Iterator iter;

TEST_CASE("Array iterator should delete item at the beginning"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(iter.DeleteThis() == 1);
    REQUIRE(*iter.GetPointer() == 3);
    REQUIRE(instance.Size() == 14);
    REQUIRE(instance.Capacity() >= 14);
}

TEST_CASE("Array iterator should not delete item at the end"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.DeleteThis() == 0);
    REQUIRE(iter.GetPointer() == nullptr);
    REQUIRE(instance.Size() == 15);
    REQUIRE(instance.Capacity() >= 15);
}

TEST_CASE("Array iterator should delete item at position"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    REQUIRE(iter.DeleteThis() == 1);
    REQUIRE(*iter.GetPointer() == 13);
    REQUIRE(instance.Size() == 14);
    REQUIRE(instance.Capacity() >= 15);
}

TEST_CASE("Array iterator should not delete items before if at beginning"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(iter.DeleteBefore(5) == 0);
    REQUIRE(*iter.GetPointer() == 1);
    REQUIRE(instance.Size() == 15);
}

TEST_CASE("Array iterator should delete some items before from the end"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.DeleteBefore(5) == 5);
    REQUIRE(instance.Size() == 10);
    iter = instance.Begin();
    for (int a = 0; a < 10; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
}

TEST_CASE("Array iterator should delete all items before"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    REQUIRE(iter.DeleteBefore(5) == 5);
    REQUIRE(instance.Size() == 10);
    iter = instance.Begin();
    for (int a = 5; a < 15; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
}

TEST_CASE("Array iterator should delete all items before with overlap"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    REQUIRE(iter.DeleteBefore(55) == 5);
    REQUIRE(instance.Size() == 10);
    iter = instance.Begin();
    for (int a = 5; a < 15; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
}

TEST_CASE("Array iterator should delete all items from the end with overlap"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.DeleteBefore(55) == 15);
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Array iterator should delete some items after beginning"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(iter.DeleteAfter(5) == 5);
    REQUIRE(instance.Size() == 10);
    iter = instance.Begin();
    for (int a = 0; a < 1; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
    for (int a = 6; a < 15; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
}

TEST_CASE("Array iterator should delete some items after beginning and access with same iterator"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(iter.DeleteAfter(5) == 5);
    REQUIRE(instance.Size() == 10);
    for (int a = 0; a < 1; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
    for (int a = 6; a < 15; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
}

TEST_CASE("Array iterator should delete one items after beginning"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(iter.DeleteAfter() == 1);
    REQUIRE(instance.Size() == 14);
    for (int a = 0; a < 1; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
    for (int a = 2; a < 15; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
}

TEST_CASE("Array iterator should delete all items after beginning"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(iter.DeleteAfter(15) == 0);
    REQUIRE(instance.Size() == 15);
}

TEST_CASE("Array iterator should delete all items after beginning with overlap"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.Begin();
    REQUIRE(iter.DeleteAfter(55) == 14);
    REQUIRE(instance.Size() == 1);
    REQUIRE(instance[0] == 1);
}

TEST_CASE("Array iterator should not delete one item after end"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.DeleteAfter() == 0);
    REQUIRE(instance.Size() == 15);
    iter = instance.End();
    for (int a = 14; a >= 0; a--)
    {
        REQUIRE(iter.Back());
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
    }
}

TEST_CASE("Array iterator should not delete one item after end with same iterator"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.DeleteAfter() == 0);
    REQUIRE(instance.Size() == 15);
    for (int a = 14; a >= 0; a--)
    {
        REQUIRE(iter.Back());
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
    }
}

TEST_CASE("Array iterator should not delete some item after end"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.DeleteAfter(5) == 0);
    REQUIRE(instance.Size() == 15);
    iter = instance.End();
    for (int a = 14; a >= 0; a--)
    {
        REQUIRE(iter.Back());
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
    }
}

TEST_CASE("Array iterator should not delete all items after end"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.DeleteAfter(15) == 0);
    REQUIRE(instance.Size() == 15);
    iter = instance.End();
    for (int a = 14; a >= 0; a--)
    {
        REQUIRE(iter.Back());
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
    }
}

TEST_CASE("Array iterator should not delete all items after end with overlap"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.End();
    REQUIRE(iter.DeleteAfter(55) == 0);
    REQUIRE(instance.Size() == 15);
    iter = instance.End();
    for (int a = 14; a >= 0; a--)
    {
        REQUIRE(iter.Back());
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
    }
}

TEST_CASE("Array iterator should delete one item after specific position"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    REQUIRE(iter.DeleteAfter() == 1);
    REQUIRE(instance.Size() == 14);
    iter = instance.Begin();
    for (int a = 0; a < 6; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
    for (int a = 7; a < 15; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
}

TEST_CASE("Array iterator should delete one item after specific position with same iterator"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    REQUIRE(iter.DeleteAfter() == 1);
    REQUIRE(instance.Size() == 14);
    REQUIRE(*iter.GetPointer() == OriginalArray[5]);
    REQUIRE(iter.Next());
    for (int a = 7; a < 15; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
    iter.ToBegin();
    for (int a = 0; a < 5; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
}

TEST_CASE("Array iterator should delete some item after specific position"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    REQUIRE(iter.DeleteAfter(5) == 5);
    REQUIRE(instance.Size() == 10);
    iter = instance.Begin();
    for (int a = 0; a < 6; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
    for (int a = 11; a < 15; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
}

TEST_CASE("Array iterator should not delete all items after specific position"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    REQUIRE(iter.DeleteAfter(10) == 0); //todo bug
    REQUIRE(instance.Size() == 15);
    iter = instance.Begin();
    for (int a = 0; a < 15; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
}

TEST_CASE("Array iterator should not delete all items after specific position with overlap"){
    Array<int> instance(OriginalArray, 15);
    iter = instance.At(5);
    REQUIRE(iter.DeleteAfter(55) == 9);
    REQUIRE(instance.Size() == 6);
    iter = instance.Begin();
    for (int a = 0; a < 6; a++)
    {
        REQUIRE(*iter.GetPointer() == OriginalArray[a]);
        REQUIRE(iter.Next());
    }
}

*/