#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
int SecondArray[5] = {90, 91, 92, 93, 94};

TEST_CASE("Vector should insert one element", "[Vector][Insert]")
{
    Vector<int> instance(OriginalArray, 15);
    instance.Insert(100);
    REQUIRE(instance.Size() == 16);
    REQUIRE(instance[0] == 100);
    for (int i = 1; i < 16; i++)
        REQUIRE(instance[i] == OriginalArray[i-1]);
}

TEST_CASE("Vector should insert five elements", "[Vector][Insert]")
{
    Vector<int> instance(OriginalArray, 15);
    instance.Insert(SecondArray, 5);
    REQUIRE(instance.Size() == 20);
    for (int i = 0; i < 5; i++)
        REQUIRE(instance[i] == SecondArray[i]);
    for (int i = 5; i < 20; i++)
        REQUIRE(instance[i] == OriginalArray[i - 5]);
}

