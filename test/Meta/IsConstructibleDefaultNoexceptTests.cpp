#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

class T1{
public:
    T1() noexcept {}
};

TEST_CASE("Should have default noexcept constructor","[Meta][is_constructible_default_noexcept]"){
    REQUIRE(is_constructible_default_noexcept<T1>::value);
}

class T2{
public:
    T2() noexcept(false) {}
};

TEST_CASE("Should not have default noexcept constructor if noted","[Meta][is_constructible_default_noexcept]"){
    REQUIRE(!is_constructible_default_noexcept<T2>::value);
}


class T3{
public:
    T3() {}
};

TEST_CASE("Should not have default noexcept constructor if not noted","[Meta][is_constructible_default_noexcept]"){
    REQUIRE(!is_constructible_default_noexcept<T3>::value);
}

class T4{
public:
    T4() = delete;
};

TEST_CASE("Should not have default noexcept constructor if deleted","[Meta][is_constructible_default_noexcept]"){
    REQUIRE(!is_constructible_default_noexcept<T4>::value);
}

class T5{
private:
    T5() noexcept {}
};

TEST_CASE("Should not have default noexcept constructor if private","[Meta][is_constructible_default_noexcept]"){
    REQUIRE(!is_constructible_default_noexcept<T5>::value);
}

//buildin types

TEST_CASE("Is int default noexcept constructible","[Meta][is_constructible_default_noexcept]"){
    REQUIRE(is_constructible_default_noexcept<int>::value);
}

TEST_CASE("Is pointer default noexcept constructible","[Meta][is_constructible_default_noexcept]"){
    REQUIRE(is_constructible_default_noexcept<int*>::value);
}

TEST_CASE("Is reference default noexcept constructible","[Meta][is_constructible_default_noexcept]"){
    REQUIRE(!is_constructible_default_noexcept<int&>::value);
}

TEST_CASE("Is rreference default noexcept constructible","[Meta][is_constructible_default_noexcept]"){
    REQUIRE(!is_constructible_default_noexcept<int&&>::value);
}