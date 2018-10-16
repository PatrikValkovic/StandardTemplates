#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

TEST_CASE("Int should not be reference","[Meta][is_reference]"){
    REQUIRE(!is_reference<int>::value);
}

TEST_CASE("Int pointer should not be reference","[Meta][is_reference]"){
    REQUIRE(!is_reference<int*>::value);
}

TEST_CASE("Int reference should be reference","[Meta][is_reference]"){
    REQUIRE(is_reference<int&>::value);
}

TEST_CASE("Int rreference should be reference","[Meta][is_reference]"){
    REQUIRE(is_reference<int&&>::value);
}


TEST_CASE("Const int should not be reference","[Meta][is_reference]"){
    REQUIRE(!is_reference<const int>::value);
}

TEST_CASE("Const int pointer should not be reference","[Meta][is_reference]"){
    REQUIRE(!is_reference<const int*>::value);
}

TEST_CASE("Const int reference should be reference","[Meta][is_reference]"){
    REQUIRE(is_reference<const int&>::value);
}

TEST_CASE("Const int rreference should be reference","[Meta][is_reference]"){
    REQUIRE(is_reference<const int&&>::value);
}


TEST_CASE("int pointer reference should be reference","[Meta][is_reference]"){
    REQUIRE(is_reference<const int* &>::value);
}


TEST_CASE("int pointer rreference should be reference","[Meta][is_reference]"){
    REQUIRE(is_reference<const int* &&>::value);
}