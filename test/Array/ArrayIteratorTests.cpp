#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
int SecondArray[5] = {90,91,92,93,94};

TEST_CASE("Array iterator should iterate thought all the elements", "[Array][Iterator]") {
    Array<int> instance(OriginalArray, 15);
    Array<int>::Iterator bi = instance.Begin();
    Array<int>::Iterator ei = instance.End();
    int* bo = OriginalArray;
    for(;bi != ei;bi++,bo++)
        REQUIRE(*bi == *bo);
}

TEST_CASE("Const array iterator should iterate thought all the elements", "[Array][Iterator]") {
    const Array<int> instance(OriginalArray, 15);
    Array<int>::ConstantIterator bi = instance.Begin();
    Array<int>::ConstantIterator ei = instance.End();
    int* bo = OriginalArray;
    for(;bi != ei;bi++,bo++)
        REQUIRE(*bi == *bo);
}

TEST_CASE("Array iterator can set the values", "[Array][Iterator]") {
    Array<int> instance(OriginalArray, 15);
    Array<int>::Iterator bi = instance.Begin();
    for(int i=0;i<5;i++, bi++)
        *bi = SecondArray[i];
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == SecondArray[i]);
    for(int i=5;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
}

TEST_CASE("Array iterator can swap the values", "[Array][Iterator]") {
    Array<int> instance(OriginalArray, 15);
    Array<int>::Iterator p1 = instance.Begin();
    Array<int>::Iterator p2 = instance.Begin() + 10;
    for(int i=0;i<5;i++, p1++, p2++)
        swap(*p1, *p2);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == OriginalArray[i+10]);
    for(int i=5;i<10;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for(int i=10;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i-10]);
}
