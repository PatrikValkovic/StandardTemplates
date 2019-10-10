#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#define private public
#include "../../Templates.h"
using namespace Templates;

int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

TEST_CASE("Array should push one value", "[Array][Push]"){
    Array<int> instance(OriginalArray, 15);
    instance.Push(31);
    REQUIRE(instance.Size()==16);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    REQUIRE(instance[15] == 31);
}

TEST_CASE("Array should resize based on the input size if big array is pushed", "[Array][Push]"){
    Array<int> instance(OriginalArray, 2);
    instance.Push(OriginalArray+2, 13);
    REQUIRE(instance.Size()==15);
    REQUIRE(instance.Capacity() >= 15);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
}


TEST_CASE("Array should push values from array", "[Array][Push]"){
    Array<int> instance(OriginalArray, 15);
    instance.Push(OriginalArray, 10);
    REQUIRE(instance.Size()==25);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for(int i=0;i<10;i++)
        REQUIRE(instance[i+15] == OriginalArray[i]);
}

TEST_CASE("Array should push whole second array", "[Array][Push]"){
    Array<int> instance(OriginalArray, 15);
    instance.Push(OriginalArray, 15);
    REQUIRE(instance.Size()==30);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i+15] == OriginalArray[i]);
}
