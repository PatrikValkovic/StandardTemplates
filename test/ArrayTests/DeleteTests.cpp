#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

TEST_CASE("Array should delete all elements by default") {
    Array<int> Instance(OriginalArray, 15);
    Instance.Delete();
    REQUIRE(Instance.Size() == 0);
}

TEST_CASE("Array should delete all elements") {
    Array<int> Instance(OriginalArray, 15);
    Instance.Delete(15);
    REQUIRE(Instance.Size() == 0);
}

TEST_CASE("Array should delete less elements") {
    Array<int> Instance(OriginalArray, 15);
    Instance.Delete(5);
    REQUIRE(Instance.Size() == 10);
    for (int a = 0; a < Instance.Size(); a++)
        REQUIRE(Instance[a] == OriginalArray[a + 5]);
}

TEST_CASE("Array should delete few elements") {
    Array<int> Instance(OriginalArray, 15);
    Instance.Delete(3);
    REQUIRE(Instance.Size() == 12);
    for (int a = 0; a < Instance.Size(); a++)
        REQUIRE(Instance[a] == OriginalArray[a + 3]);
}

TEST_CASE("Array should delete maximum of size elements") {
    Array<int> Instance(OriginalArray, 15);
    Instance.Delete(25);
    REQUIRE(Instance.Size() == 0);
}

TEST_CASE("Array should delete all elements from the end") {
    Array<int> Instance(OriginalArray, 15);
    Instance.DeleteFromEnd(15);
    REQUIRE(Instance.Size() == 0);
}

TEST_CASE("Array should delete some elements from the end") {
    Array<int> Instance(OriginalArray, 15);
    Instance.DeleteFromEnd(3);
    REQUIRE(Instance.Size() == 12);
    for (int a = 0; a < Instance.Size(); a++)
        REQUIRE(Instance[a] == OriginalArray[a]);
}

TEST_CASE("Array should delete maximum of size elements from the end") {
    Array<int> Instance(OriginalArray, 15);
    Instance.DeleteFromEnd(25);
    REQUIRE(Instance.Size() == 0);
}
