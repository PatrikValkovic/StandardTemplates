#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

class T1{
public:
    T1(T1&&) noexcept
    {}
    T1(const T1&) = delete;
};

TEST_CASE("Should have movable noexcept constructor","[Meta][is_constructible_movable_noexcept]"){
    REQUIRE(is_constructible_movable_noexcept<T1>::value);
}

class T2{
public:
    T2() = delete;
    T2(const T2&) = delete;
    T2(T2&&) noexcept(false)
    {}
};

TEST_CASE("Should not have movable noexcept constructor if marked","[Meta][is_constructible_movable_noexcept]"){
    REQUIRE(!is_constructible_movable_noexcept<T2>::value);
}

class T3{
public:
    T3() = delete;
    T3(const T3&) = delete;
    T3(T2&&)
    {}
};

TEST_CASE("Should not have movable noexcept constructor if not marked","[Meta][is_constructible_movable_noexcept]"){
    REQUIRE(!is_constructible_movable_noexcept<T3>::value);
}

class T4{
public:
    T4() = delete;
    T4(const T4&) = default;
    T4(T4&&) = delete;
};

TEST_CASE("Should not have movable noexcept constructor if deleted","[Meta][is_constructible_movable_noexcept]"){
    REQUIRE(!is_constructible_movable_noexcept<T4>::value);
}

class T5{
private:
    T5() = delete;
    T5(const T5&) = default;
    T5(T5&&) noexcept {};
};

TEST_CASE("Should not have movable noexcept constructor if private","[Meta][is_constructible_movable_noexcept]"){
    REQUIRE(!is_constructible_movable_noexcept<T5>::value);
}


//buildin types

TEST_CASE("Is movable noexcept constructible","[Meta][is_constructible_movable_noexcept]"){
    REQUIRE(is_constructible_movable_noexcept<int>::value);
}

TEST_CASE("Is pointer movable noexcept constructible","[Meta][is_constructible_movable_noexcept]"){
    REQUIRE(is_constructible_movable_noexcept<int*>::value);
}

TEST_CASE("Is reference movable noexcept constructible","[Meta][is_constructible_movable_noexcept]"){
    REQUIRE(is_constructible_movable_noexcept<int&>::value);
}

TEST_CASE("Is rreference movable noexcept constructible","[Meta][is_constructible_movable_noexcept]"){
    REQUIRE(is_constructible_movable_noexcept<int&&>::value);
}

