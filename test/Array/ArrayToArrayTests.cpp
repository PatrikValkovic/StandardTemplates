#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
int count;

TEST_CASE("Array should covert to readable raw array", "[Array][ToArray]") {
    Array<int> instance(OriginalArray, 15);
    int* array = instance.ToArray(count);
    REQUIRE(count == 15);
    for (int a = 0; a < count; a++)
        REQUIRE(OriginalArray[a] == array[a]);
}

TEST_CASE("Array should be writable", "[Array][ToArray]") {
    Array<int> instance(OriginalArray, 15);
    int* arr = instance.ToArray(count);
    REQUIRE(count == 15);
    for (int a = 0; a < count; a++)
    {
        REQUIRE(arr[a] == OriginalArray[a]);
        arr[a] = a;
    }
    arr = instance.ToArray(count);
    REQUIRE(count == 15);
    for (int a = 0; a < count; a++)
        REQUIRE(arr[a] == a);
    for (int a = 0; a < count; a++)
        REQUIRE(instance[a] == a);
}

TEST_CASE("Const array should covert to readable raw array", "[Array][ToArray]") {
    const Array<int> instance(OriginalArray, 15);
    const int* array = instance.ToArray(count);
    REQUIRE(count == 15);
    for (int a = 0; a < count; a++)
        REQUIRE(OriginalArray[a] == array[a]);
}
