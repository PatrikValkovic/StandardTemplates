#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

class T1{
public:
    T1() = delete;
    T1(const T1&) noexcept {}
    T1(T1&&) = delete;
};

TEST_CASE("Should have copyable noexcept constructor","[Meta][is_constructible_copyable_noexcept]"){
    REQUIRE(is_constructible_copyable_noexcept<T1>::value);
}

class T2{
public:
    T2() = delete;
    T2(const T2&) noexcept(false) {}
    T2(T2&&) = delete;
};

TEST_CASE("Should not have copyable noexcept constructor if marked","[Meta][is_constructible_copyable_noexcept]"){
    REQUIRE(!is_constructible_copyable_noexcept<T2>::value);
}

class T3{
public:
    T3() = delete;
    T3(const T3&) {}
    T3(T3&&) = delete;
};

TEST_CASE("Should not have copyable noexcept constructor if not marked","[Meta][is_constructible_copyable_noexcept]"){
    REQUIRE(!is_constructible_copyable_noexcept<T3>::value);
}

class T4{
public:
    T4() = delete;
    T4(const T4&) = delete;
    T4(T4&&) = default;
};

TEST_CASE("Should assert false when deleted copyable noexcept constructor","[Meta][is_constructible_copyable_noexcept]"){
    REQUIRE(!is_constructible_copyable_noexcept<T4>::value);
}


class T5{
private:
    T5() = delete;
    T5(const T5&) noexcept(true) {}
    T5(T5&&) = default;
};

TEST_CASE("Should assert false when deleted copyable noexcept constructor is private","[Meta][is_constructible_copyable_noexcept]"){
    REQUIRE(!is_constructible_copyable_noexcept<T5>::value);
}

//buildin types

TEST_CASE("Is int copyable noexcept constructible","[Meta][is_constructible_copyable_noexcept]"){
    REQUIRE(is_constructible_copyable_noexcept<int>::value);
}

TEST_CASE("Is pointer copyable noexcept constructible","[Meta][is_constructible_copyable_noexcept]"){
    REQUIRE(is_constructible_copyable_noexcept<int*>::value);
}

TEST_CASE("Is reference copyable noexcept constructible","[Meta][is_constructible_copyable_noexcept]"){
    REQUIRE(is_constructible_copyable_noexcept<int&>::value);
}

TEST_CASE("Is rreference copyable noexcept constructible","[Meta][is_constructible_copyable_noexcept]"){
    REQUIRE(!is_constructible_copyable_noexcept<int&&>::value);
}
