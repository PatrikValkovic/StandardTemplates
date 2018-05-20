#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#define private public
#include "../../Templates.h"
using namespace Templates;


const int alloc = 10;
int array[] = {1, 3, 5, 7, 9};

TEST_CASE("Should create empty Array", "[Array][Creation]") {
    Array<int,alloc> instance;
    REQUIRE(instance.Allocated == alloc);
    for (int a = 0; a < alloc; a++)
        REQUIRE(instance.Containing[a] == NULL);
}

TEST_CASE("Should create Array with capacity", "[Array][Creation]"){
    Array<int,alloc> instance(4);
    REQUIRE(instance.Capacity() == alloc);
    for (int a = 0; a < 4; a++)
        REQUIRE(instance.Containing[a] == NULL);
}

TEST_CASE("Should create Array with more capacity", "[Array][Creation]"){
    Array<int,alloc> instance(25);
    REQUIRE(instance.Capacity() == 25);
    for (int a = 0; a < 25; a++)
        REQUIRE(instance.Containing[a] == NULL);
}

TEST_CASE("Should create Array with negative capacity", "[Array][Creation]"){
    Array<int,alloc> instance(-5);
    REQUIRE(instance.Capacity() == alloc);
    for (int a = 0; a < alloc; a++)
        REQUIRE(instance.Containing[a] == NULL);
}

TEST_CASE("Should create Array with huge capacity", "[Array][Creation]"){
    Array<int,alloc> instance(1584);
    REQUIRE(instance.Capacity() == 1584);
    for (int a = 0; a < 1584; a++)
        REQUIRE(instance.Containing[a] == NULL);
}

TEST_CASE("Should create Array with default values", "[Array][Creation]"){
    Array<int,alloc> instance(array, 5);
    REQUIRE(instance.Capacity() >= 5);
    REQUIRE(instance.Size() == 5);
    for (int a = 0; a < 5; a++)
        REQUIRE(*instance.Containing[a] == array[a]);
}
