#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

class T1{
public:
    T1() = default;
    T1(const T1&) = delete;
    T1(T1&&) = delete;
};

TEST_CASE("Should have default constructor","[Meta][is_constructible_default]"){
    REQUIRE(is_constructible_default<T1>::value);
}

class T2{
public:
    T2() = delete;
    T2(const T2&) = delete;
    T2(T2&&) = delete;
};

TEST_CASE("Should not have default constructor","[Meta][is_constructible_default]"){
    REQUIRE(!is_constructible_default<T2>::value);
}

class T3{
private:
    T3() = default;
    T3(const T3&) = delete;
    T3(T3&&) = delete;
};

TEST_CASE("Should have default constructor but private","[Meta][is_constructible_default]"){
    REQUIRE(!is_constructible_default<T3>::value);
}