#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

class T1{
public:
    T1() = delete;
    T1(const T1&) = delete;
    T1(T1&&) = default;
};

TEST_CASE("Should have movable constructor","[Meta][is_constructible_movable]"){
    REQUIRE(is_constructible_movable<T1>::value);
}

class T2{
public:
    T2() = delete;
    T2(const T2&) = delete;
    T2(T2&&) = delete;
};

TEST_CASE("Should not have movable constructor","[Meta][is_constructible_movable]"){
    REQUIRE(!is_constructible_movable<T2>::value);
}

class T3{
private:
    T3() = delete;
    T3(const T3&) = delete;
    T3(T3&&) = default;
};

TEST_CASE("Should have movable constructor but private","[Meta][is_constructible_movable]"){
    REQUIRE(!is_constructible_movable<T3>::value);
}

class T4{
public:
    T4() = delete;
    T4(const T4&) = default;
    T4(T4&&) = delete;
};

TEST_CASE("Should assert false even with copyable constructor","[Meta][is_constructible_movable]"){
    REQUIRE(!is_constructible_movable<T4>::value);
}
