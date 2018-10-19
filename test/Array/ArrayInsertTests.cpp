#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
int SecondArray[5] = {90, 91, 92, 93, 94};

TEST_CASE("Array should insert one element into middle", "[Array][Insert]")
{
    Array<int> instance(OriginalArray, 15);
    instance.Insert(10, 100);
    REQUIRE(instance.Size() == 16);
    for (int i = 0; i < 10; i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    REQUIRE(instance[10] == 100);
    for (int i = 11; i < 16; i++)
        REQUIRE(instance[i] == OriginalArray[i - 1]);
}

TEST_CASE("Array should insert five elements into middle", "[Array][Insert]")
{
    Array<int> instance(OriginalArray, 15);
    instance.Insert(10, SecondArray, 5);
    REQUIRE(instance.Size() == 20);
    for (int i = 0; i < 10; i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for (int i = 10; i < 15; i++)
        REQUIRE(instance[i] == SecondArray[i - 10]);
    for (int i = 15; i < 20; i++)
        REQUIRE(instance[i] == OriginalArray[i - 5]);
}

TEST_CASE("Array should insert one element in the beginning", "[Array][Insert]")
{
    Array<int> instance(OriginalArray, 15);
    instance.Insert(0, 100);
    REQUIRE(instance.Size() == 16);
    REQUIRE(instance[0] == 100);
    for (int i = 1; i < 16; i++)
        REQUIRE(instance[i] == OriginalArray[i - 1]);
}

TEST_CASE("Array should insert five elements in the beginning", "[Array][Insert]")
{
    Array<int> instance(OriginalArray, 15);
    instance.Insert(0, SecondArray, 5);
    REQUIRE(instance.Size() == 20);
    for (int i = 0; i < 5; i++)
        REQUIRE(instance[i] == SecondArray[i]);
    for (int i = 5; i < 20; i++)
        REQUIRE(instance[i] == OriginalArray[i - 5]);
}

TEST_CASE("Array should insert one element in the end", "[Array][Insert]")
{
    Array<int> instance(OriginalArray, 15);
    instance.Insert(15, 100);
    REQUIRE(instance.Size() == 16);
    for (int i = 0; i < 15; i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    REQUIRE(instance[15] == 100);
}

TEST_CASE("Array should insert five elements in the end", "[Array][Insert]")
{
    Array<int> instance(OriginalArray, 15);
    instance.Insert(15, SecondArray, 5);
    REQUIRE(instance.Size() == 20);
    for (int i = 0; i < 15; i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for (int i = 15; i < 20; i++)
        REQUIRE(instance[i] == SecondArray[i - 15]);
}

TEST_CASE("Array should insert one element before the end", "[Array][Insert]")
{
    Array<int> instance(OriginalArray, 15);
    instance.Insert(14, 100);
    REQUIRE(instance.Size() == 16);
    for (int i = 0; i < 14; i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    REQUIRE(instance[14] == 100);
    REQUIRE(instance[15] == OriginalArray[14]);
}

TEST_CASE("Array should insert five elements before the end", "[Array][Insert]")
{
    Array<int> instance(OriginalArray, 15);
    instance.Insert(14, SecondArray, 5);
    REQUIRE(instance.Size() == 20);
    for (int i = 0; i < 14; i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for (int i = 14; i < 19; i++)
        REQUIRE(instance[i] == SecondArray[i - 14]);
    REQUIRE(instance[19] == OriginalArray[14]);
}
