#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;

int OriginalArray[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

TEST_CASE("Array swap should should swap two items", "[Array][Swap]")
{
    Array<int> instance(OriginalArray, 10);
    instance.Swap(0,9);
    REQUIRE(instance[0] == 19);
    REQUIRE(instance[9] == 1);
}

TEST_CASE("Array swap should should swap items if first is negative", "[Array][Swap]")
{
    Array<int> instance(OriginalArray, 10);
    try
    {
        instance.Swap(-1, 9);
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
    catch(...)
    {
        REQUIRE(false);
    }
}

TEST_CASE("Array swap should should swap items if second is negative", "[Array][Swap]")
{
    Array<int> instance(OriginalArray, 10);
    try
    {
        instance.Swap(0, -1);
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
    catch(...)
    {
        REQUIRE(false);
    }
}

TEST_CASE("Array swap should should swap items if first is too big", "[Array][Swap]"){
    Array<int> instance(OriginalArray, 10);
    try
    {
        instance.Swap(15, 2);
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
    catch(...)
    {
        REQUIRE(false);
    }
}

TEST_CASE("Array swap should should swap items if second is too big", "[Array][Swap]"){
    Array<int> instance(OriginalArray, 10);
    try
    {
        instance.Swap(2, 15);
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
    catch(...)
    {
        REQUIRE(false);
    }
}

TEST_CASE("Array swap should should swap items if indexes are same", "[Array][Swap]"){
    Array<int> instance(OriginalArray, 10);
    instance.Swap(5, 5);
}
