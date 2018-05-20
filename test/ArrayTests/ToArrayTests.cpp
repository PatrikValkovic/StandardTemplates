#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#define private public
#include "../../Templates.h"
using namespace Templates;


int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
int *array;
int **writablearray;
int count;

TEST_CASE("Array should covert to readable raw array") {
    Array<int> instance(OriginalArray, 15);
    array = instance.ToArray(count);
    REQUIRE(count == 15);
    for (int a = 0; a < count; a++)
        REQUIRE(OriginalArray[a] == array[a]);
    delete [] array;
}

TEST_CASE("Array should covert to writable raw array") {
    Array<int> instance(OriginalArray, 15);
    writablearray = instance.ToWriteArray(count);
    REQUIRE(count == 15);
    for (int a = 0; a < count; a++)
    {
        REQUIRE(*writablearray[a] == OriginalArray[a]);
        *writablearray[a] = a;
    }
    array = instance.ToArray(count);
    REQUIRE(count == 15);
    for (int a = 0; a < count; a++)
        REQUIRE(array[a] == a);
    delete [] array;
    delete [] writablearray;
}
