#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#define private public
#include "../../Templates.h"
using namespace Templates;

int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
Array<int>::Iterator iter;

TEST_CASE("Array should push one value"){
    Array<int> instance(OriginalArray, 15);
    REQUIRE(instance.Push(31)==1);
    REQUIRE(instance.Size()==16);
    iter = instance.Begin();
    for(int a=0;a<15;a++,iter.Next())
        REQUIRE(*iter.GetValue()==OriginalArray[a]);
    REQUIRE(*iter.GetValue()==31);
}

TEST_CASE("Array should push one different value"){
    Array<int> instance(OriginalArray, 15);
    REQUIRE(instance.Push(35)==1);
    REQUIRE(instance.Size()==16);
    iter = instance.Begin();
    for(int a=0;a<15;a++,iter.Next())
        REQUIRE(*iter.GetValue()==OriginalArray[a]);
    REQUIRE(*iter.GetValue()==35);
}

TEST_CASE("Array should push values from array"){
    Array<int> instance(OriginalArray, 15);
    REQUIRE(instance.Push(OriginalArray, 10)==10);
    REQUIRE(instance.Size()==25);
    iter = instance.Begin();
    for(int a=0;a<15;a++,iter.Next())
        REQUIRE(*iter.GetValue()==OriginalArray[a]);
    for(int a=0;a<10;a++,iter.Next())
        REQUIRE(*iter.GetValue()==OriginalArray[a]);
}

TEST_CASE("Array should push whole second array"){
    Array<int> instance(OriginalArray, 15);
    REQUIRE(instance.Push(OriginalArray, 15)==15);
    REQUIRE(instance.Size()==30);
    iter = instance.Begin();
    for(int a=0;a<15;a++,iter.Next())
        REQUIRE(*iter.GetValue()==OriginalArray[a]);
    for(int a=0;a<15;a++,iter.Next())
        REQUIRE(*iter.GetValue()==OriginalArray[a]);
}
