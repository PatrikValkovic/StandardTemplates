#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;


TEST_CASE("Add rref for integer", "[Meta][as_rref]")
{
    REQUIRE(are_same<int&&,as_rref<int>::type>::value);
}

TEST_CASE("Add rref for ref integer", "[Meta][as_rref]")
{
    REQUIRE(are_same<int&&,as_rref<int&>::type>::value);
}

TEST_CASE("Should not add rref for movable integer", "[Meta][as_rref]")
{
    REQUIRE(are_same<int&&,as_rref<int&&>::type>::value);
}


TEST_CASE("Add rref for const integer", "[Meta][as_rref]")
{
    REQUIRE(are_same<const int&&,as_rref<const int>::type>::value);
}

TEST_CASE("Add rref for const ref integer", "[Meta][as_rref]")
{
    REQUIRE(are_same<const int&&,as_rref<const int&>::type>::value);
}

TEST_CASE("Should not add rref for const movable integer", "[Meta][as_rref]")
{
    REQUIRE(are_same<const int&&,as_rref<const int&&>::type>::value);
}


TEST_CASE("Add rref for integer pointer", "[Meta][as_rref]")
{
    REQUIRE(are_same<int* &&,as_rref<int*>::type>::value);
}

TEST_CASE("Add rref for ref integer pointer", "[Meta][as_rref]")
{
    REQUIRE(are_same<int* &&,as_rref<int* & >::type>::value);
}

TEST_CASE("Should not add rref for movable integer pointer", "[Meta][as_rref]")
{
    REQUIRE(are_same<int* &&,as_rref<int* &&>::type>::value);
}
