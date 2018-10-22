#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

TEST_CASE("Vector should covert to readable array", "[Vector][ToArray]") {
    Vector<int> instance(OriginalArray, 15);
    Array<int> array = instance.ToArray();
    REQUIRE(array.Size() == 15);
    for (int a = 0; a < array.Size(); a++)
        REQUIRE(OriginalArray[a] == array[a]);
}

TEST_CASE("Const array should covert to readable raw array", "[Vector][ToArray]") {
    const Vector<int> instance(OriginalArray, 15);
    Array<int> array = instance.ToArray();
    REQUIRE(array.Size() == 15);
    for (int a = 0; a < array.Size(); a++)
        REQUIRE(OriginalArray[a] == array[a]);
}
