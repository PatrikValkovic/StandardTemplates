#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;


TEST_CASE("Remove reference from integer", "[Meta][remove_reference]")
{
    REQUIRE(are_same<int,remove_reference<int>::type>::value);
}

TEST_CASE("Remove reference from integer reference", "[Meta][remove_reference]")
{
    REQUIRE(are_same<int,remove_reference<int &>::type>::value);
}

TEST_CASE("Remove reference from integer rreference", "[Meta][remove_reference]")
{
    REQUIRE(are_same<int,remove_reference<int&&>::type>::value);
}

TEST_CASE("Remove reference from integer pointer", "[Meta][remove_reference]")
{
    REQUIRE(are_same<int *,remove_reference<int * >::type>::value);
}

TEST_CASE("Remove reference from integer pointer reference", "[Meta][remove_reference]")
{
    REQUIRE(are_same<int *,remove_reference<int* &>::type>::value);
}
