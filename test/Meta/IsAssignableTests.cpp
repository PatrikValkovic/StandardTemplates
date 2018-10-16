#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

TEST_CASE("is assignable int and int","[Meta][is_assignable]"){
    REQUIRE(is_assignable<int&, int>::value);
}

TEST_CASE("is assignable long and int","[Meta][is_assignable]"){
    REQUIRE(is_assignable<long&, int>::value);
}

TEST_CASE("is assignable int and int ref","[Meta][is_assignable]"){
    REQUIRE(is_assignable<int&, int&>::value);
}

//TODO more tests
