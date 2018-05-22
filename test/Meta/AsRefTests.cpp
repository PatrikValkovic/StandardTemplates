#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;


TEST_CASE("Add ref for integer", "[Meta][as_ref]")
{
    REQUIRE(are_same<int&,as_ref<int>::type>::value);
}

TEST_CASE("Should not add ref for ref integer", "[Meta][as_ref]")
{
    REQUIRE(are_same<int&,as_ref<int&>::type>::value);
}

TEST_CASE("Should not add ref for movable integer", "[Meta][as_ref]")
{
    REQUIRE(are_same<int&,as_ref<int&&>::type>::value);
}


TEST_CASE("Add ref for const integer", "[Meta][as_ref]")
{
    REQUIRE(are_same<const int&,as_ref<const int>::type>::value);
}

TEST_CASE("Should not add ref for const ref integer", "[Meta][as_ref]")
{
    REQUIRE(are_same<const int&,as_ref<const int&>::type>::value);
}

TEST_CASE("Should not add ref for const movable integer", "[Meta][as_ref]")
{
    REQUIRE(are_same<const int&,as_ref<const int&&>::type>::value);
}


TEST_CASE("Add ref for integer pointer", "[Meta][as_ref]")
{
    REQUIRE(are_same<int* &,as_ref<int*>::type>::value);
}

TEST_CASE("Should not add ref for ref integer pointer", "[Meta][as_ref]")
{
    REQUIRE(are_same<int* &,as_ref<int* & >::type>::value);
}

TEST_CASE("Should not add ref for movable integer pointer", "[Meta][as_ref]")
{
    REQUIRE(are_same<int* &,as_ref<int* &&>::type>::value);
}
