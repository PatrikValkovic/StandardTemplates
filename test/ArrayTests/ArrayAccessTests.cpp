#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9};

TEST_CASE("Call of bracket operator at empty array should throw OutOfRangeException", "[Array][Access]") {
    Array<int> instance;
    try
    {
        instance[0];
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Call of bracket operator at array with capacity should throw OutOfRangeException", "[Array][Access]") {
    Array<int> instance(4);
    try
    {
        instance[0];
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Call of bracket operator at empty const array should throw OutOfRangeException", "[Array][Access]") {
    const Array<int> instance;
    try
    {
        instance[0];
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Call of bracket operator at const array with capacity should throw OutOfRangeException", "[Array][Access]") {
    const Array<int> instance(4);
    try
    {
        instance[0];
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Call of bracket operator at empty array with value 0 should throw OutOfRangeException", "[Array][Access]") {
    Array<int> instance;
    try
    {
        instance[0];
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Call of bracket operator at filled array should work", "[Array][Access]") {
    Array<int> instance(array, 5);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == array[i]);
}

TEST_CASE("Call of bracket operator at filled const array should work", "[Array][Access]") {
    const Array<int> instance(array, 5);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == array[i]);
}

TEST_CASE("Call of bracket operator with height value at filled array should throw OutOfRangeException", "[Array][Access]") {
    Array<int> instance(array, 5);
    try
    {
        instance[8];
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Call of bracket operator with value=size at filled array should throw OutOfRangeException", "[Array][Access]") {
    Array<int> instance(array, 5);
    try
    {
        instance[5];
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Call of bracket operator with height value at filled const array should throw OutOfRangeException", "[Array][Access]") {
    const Array<int> instance(array, 5);
    try
    {
        instance[8];
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Call of bracket operator with value=size at filled const array should throw OutOfRangeException", "[Array][Access]") {
    const Array<int> instance(array, 5);
    try
    {
        instance[5];
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Call of bracket operator with negative value at filled array should throw OutOfRangeException", "[Array][Access]") {
    Array<int> instance(array, 5);
    try
    {
        instance[-1];
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Call of bracket operator with negative value at filled const array should throw OutOfRangeException", "[Array][Access]") {
    const Array<int> instance(array, 5);
    try
    {
        instance[-1];
        REQUIRE(false);
    }
    catch(OutOfRangeException&)
    {
        REQUIRE(true);
    }
}


