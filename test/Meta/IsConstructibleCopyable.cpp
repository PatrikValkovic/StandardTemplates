#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

class T1{
public:
    T1() = delete;
    T1(const T1&) = default;
    T1(T1&&) = delete;
};

TEST_CASE("Should have copyable constructor","[Meta][is_constructible_copyable]"){
    REQUIRE(is_constructible_copyable<T1>::value);
}

class T2{
public:
    T2() = delete;
    T2(const T2&) = delete;
    T2(T2&&) = delete;
};

TEST_CASE("Should not have copyable constructor","[Meta][is_constructible_copyable]"){
    REQUIRE(!is_constructible_copyable<T2>::value);
}

class T3{
private:
    T3() = delete;
    T3(const T3&) = default;
    T3(T3&&) = delete;
};

TEST_CASE("Should have copyable constructor but private","[Meta][is_constructible_copyable]"){
    REQUIRE(!is_constructible_copyable<T3>::value);
}

class T4{
public:
    T4() = delete;
    T4(const T4&) = delete;
    T4(T4&&) = default;
};

TEST_CASE("Should assert false even with movable constructor","[Meta][is_constructible_copyable]"){
    REQUIRE(!is_constructible_copyable<T4>::value);
}
