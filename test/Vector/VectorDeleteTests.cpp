#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

TEST_CASE("Vector should delete all elements by default", "[Vector][Delete]") {
    Vector<int> instance(OriginalArray, 15);
    instance.Delete();
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.IsEmpty());
}

TEST_CASE("Vector should delete all elements if number=size", "[Vector][Delete]") {
    Vector<int> instance(OriginalArray, 15);
    instance.Delete(15);
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.IsEmpty());
}

TEST_CASE("Vector should delete 5 elements", "[Vector][Delete]") {
    Vector<int> instance(OriginalArray, 15);
    instance.Delete(5);
    REQUIRE(instance.Size() == 10);
    for(int i=0;i<10;i++)
        REQUIRE(instance[i] == OriginalArray[i+5]);
}

TEST_CASE("Vector should delete all elements if higher value passed", "[Vector][Delete]") {
    Vector<int> instance(OriginalArray, 15);
    instance.Delete(25);
    REQUIRE(instance.Size() == 0);
}
