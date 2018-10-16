#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

TEST_CASE("Int should not be rvalue reference","[Meta][is_rvalue_reference]"){
    REQUIRE(!is_rvalue_reference<int>::value);
}

TEST_CASE("Int pointer should not be rvalue reference","[Meta][is_rvalue_reference]"){
    REQUIRE(!is_rvalue_reference<int*>::value);
}

TEST_CASE("Int reference should not be rvalue reference","[Meta][is_rvalue_reference]"){
    REQUIRE(!is_rvalue_reference<int&>::value);
}

TEST_CASE("Int rreference should be rvalue reference","[Meta][is_rvalue_reference]"){
    REQUIRE(is_rvalue_reference<int&&>::value);
}


TEST_CASE("Const int should not be rvalue reference","[Meta][is_rvalue_reference]"){
    REQUIRE(!is_rvalue_reference<const int>::value);
}

TEST_CASE("Const int pointer should not be rvalue reference","[Meta][is_rvalue_reference]"){
    REQUIRE(!is_rvalue_reference<const int*>::value);
}

TEST_CASE("Const int reference should not be rvalue reference","[Meta][is_rvalue_reference]"){
    REQUIRE(!is_rvalue_reference<const int&>::value);
}

TEST_CASE("Const int rreference should be rvalue reference","[Meta][is_rvalue_reference]"){
    REQUIRE(is_rvalue_reference<const int&&>::value);
}


TEST_CASE("int pointer rreference should be rvalue reference","[Meta][is_rvalue_reference]"){
    REQUIRE(is_rvalue_reference<const int* &&>::value);
}
