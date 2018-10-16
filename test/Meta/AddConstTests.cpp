#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

TEST_CASE("Add const to integer", "[Meta][add_const]")
{
    REQUIRE(are_same<const int,add_const<int>::type>::value);
}

TEST_CASE("Should not add const to const integer", "[Meta][add_const]")
{
    REQUIRE(are_same<const int,add_const<const int>::type>::value);
}

TEST_CASE("Add const to integer pointer", "[Meta][add_const]")
{
    REQUIRE(are_same<int * const,add_const<int *>::type>::value);
}

TEST_CASE("Should not add const to const integer pointer", "[Meta][add_const]")
{
    REQUIRE(are_same<int * const,add_const<int * const>::type>::value);
}

TEST_CASE("Add const to integer const pointer", "[Meta][add_const]")
{
    REQUIRE(are_same<const int * const,add_const<const int *>::type>::value);
}

TEST_CASE("Should not add const to const integer const pointer", "[Meta][add_const]")
{
    REQUIRE(are_same<const int * const,add_const<const int * const>::type>::value);
}

TEST_CASE("Add const to integer reference", "[Meta][add_const]")
{
    REQUIRE(are_same<const int&,add_const<int&>::type>::value);
}

TEST_CASE("Should not add const to integer const reference", "[Meta][add_const]")
{
    REQUIRE(are_same<const int&,add_const<const int&>::type>::value);
}

TEST_CASE("Add const to integer rreference", "[Meta][add_const]")
{
    REQUIRE(are_same<const int&&,add_const<int&&>::type>::value);
}

TEST_CASE("Should not add const to integer const rreference", "[Meta][add_const]")
{
    REQUIRE(are_same<const int&&,add_const<const int&&>::type>::value);
}