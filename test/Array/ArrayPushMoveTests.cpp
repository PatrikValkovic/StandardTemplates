#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#define private public
#include "../../Templates.h"
using namespace Templates;

int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

TEST_CASE("Array should push move one value", "[Array][Push]"){
    Array<UniquePointer<int>> instance;
    instance.Push(make_unique<int>(5));
    REQUIRE(instance.Size()==1);
}

TEST_CASE("Array should push move array of 10 values", "[Array][Push]"){
    UniquePointer<int> pointers[10];
    for(int i=0;i < 10; i++)
        pointers[i] = make_unique<int>(i);
    Array<UniquePointer<int>> instance;
    instance.Push(move(pointers), 10);
    REQUIRE(instance.Size()==10);
}

TEST_CASE("Array should push move array of 100 values", "[Array][Push]"){
    UniquePointer<int> pointers[100];
    for(int i=0;i < 100; i++)
        pointers[i] = make_unique<int>(i);
    Array<UniquePointer<int>> instance;
    instance.Push(move(pointers), 100);
    REQUIRE(instance.Size()==100);
}

TEST_CASE("Array should push dynamic move array of 100 values", "[Array][Push]"){
    UniquePointer<int>* pointers = new UniquePointer<int>[100];
    for(int i=0;i < 100; i++)
        pointers[i] = make_unique<int>(i);
    Array<UniquePointer<int>> instance;
    instance.Push(move(pointers), 100);
    REQUIRE(instance.Size()==100);
}
