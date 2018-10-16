#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

TEST_CASE("Int should not be lvalue reference","[Meta][is_lvalue_reference]"){
    REQUIRE(!is_lvalue_reference<int>::value);
}

TEST_CASE("Int pointer should not be lvalue reference","[Meta][is_lvalue_reference]"){
    REQUIRE(!is_lvalue_reference<int*>::value);
}

TEST_CASE("Int reference should be lvalue reference","[Meta][is_lvalue_reference]"){
    REQUIRE(is_lvalue_reference<int&>::value);
}

TEST_CASE("Int rreference should not be lvalue reference","[Meta][is_lvalue_reference]"){
    REQUIRE(!is_lvalue_reference<int&&>::value);
}


TEST_CASE("Const int should not be lvalue reference","[Meta][is_lvalue_reference]"){
    REQUIRE(!is_lvalue_reference<const int>::value);
}

TEST_CASE("Const int pointer should not be lvalue reference","[Meta][is_lvalue_reference]"){
    REQUIRE(!is_lvalue_reference<const int*>::value);
}

TEST_CASE("Const int reference should be lvalue reference","[Meta][is_lvalue_reference]"){
    REQUIRE(is_lvalue_reference<const int&>::value);
}

TEST_CASE("Const int rreference should not be lvalue reference","[Meta][is_lvalue_reference]"){
    REQUIRE(!is_lvalue_reference<const int&&>::value);
}


TEST_CASE("int pointer reference should be lvalue reference","[Meta][is_lvalue_reference]"){
    REQUIRE(is_lvalue_reference<const int* &>::value);
}
