#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9};

TEST_CASE("Call of bracket operator at empty Vector should throw OutOfRangeException", "[Vector][Access]") {
    Vector<int> instance;
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

TEST_CASE("Call of bracket operator at Vector with capacity should throw OutOfRangeException", "[Vector][Access]") {
    Vector<int> instance(4);
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

TEST_CASE("Call of bracket operator at empty const Vector should throw OutOfRangeException", "[Vector][Access]") {
    const Vector<int> instance;
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

TEST_CASE("Call of bracket operator at const Vector with capacity should throw OutOfRangeException", "[Vector][Access]") {
    const Vector<int> instance(4);
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

TEST_CASE("Call of bracket operator at empty Vector with value 0 should throw OutOfRangeException", "[Vector][Access]") {
    Vector<int> instance;
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

TEST_CASE("Call of bracket operator at filled Vector should work", "[Vector][Access]") {
    Vector<int> instance(array, 5);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == array[i]);
}

TEST_CASE("Call of bracket operator at filled const Vector should work", "[Vector][Access]") {
    const Vector<int> instance(array, 5);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == array[i]);
}

TEST_CASE("Call of bracket operator with height value at filled Vector should throw OutOfRangeException", "[Vector][Access]") {
    Vector<int> instance(array, 5);
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

TEST_CASE("Call of bracket operator with value=size at filled Vector should throw OutOfRangeException", "[Vector][Access]") {
    Vector<int> instance(array, 5);
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

TEST_CASE("Call of bracket operator with height value at filled const Vector should throw OutOfRangeException", "[Vector][Access]") {
    const Vector<int> instance(array, 5);
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

TEST_CASE("Call of bracket operator with value=size at filled const Vector should throw OutOfRangeException", "[Vector][Access]") {
    const Vector<int> instance(array, 5);
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

TEST_CASE("Call of bracket operator with negative value at filled Vector should throw OutOfRangeException", "[Vector][Access]") {
    Vector<int> instance(array, 5);
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

TEST_CASE("Call of bracket operator with negative value at filled const Vector should throw OutOfRangeException", "[Vector][Access]") {
    const Vector<int> instance(array, 5);
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


