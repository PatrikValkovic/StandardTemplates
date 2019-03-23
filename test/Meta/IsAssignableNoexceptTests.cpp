#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

TEST_CASE("is assignable noexcept int and int","[Meta][is_assignable_noexcept]"){
    REQUIRE(is_assignable_noexcept<int&, int>::value);
}

TEST_CASE("is assignable noexcept long and int","[Meta][is_assignable_noexcept]"){
    REQUIRE(is_assignable_noexcept<long&, int>::value);
}

TEST_CASE("is assignable noexcept int and int ref","[Meta][is_assignable_noexcept]"){
    REQUIRE(is_assignable_noexcept<int&, int&>::value);
}

//TODO more tests
