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

class T4{
public:
    T4() = delete;
    T4(const T4&) = default;
    T4(T4&&) = default;
};

TEST_CASE("Should result false even if all other constructors are defined","[Meta][is_constructible_default]"){
    REQUIRE(!is_constructible_default<T4>::value);
}

//buildin types

TEST_CASE("Is int default constructible","[Meta][is_constructible_default]"){
    REQUIRE(is_constructible_default<int>::value);
}

TEST_CASE("Is pointer default constructible","[Meta][is_constructible_default]"){
    REQUIRE(is_constructible_default<int*>::value);
}

TEST_CASE("Is reference default constructible","[Meta][is_constructible_default]"){
    REQUIRE(!is_constructible_default<int&>::value);
}

TEST_CASE("Is rreference default constructible","[Meta][is_constructible_default]"){
    REQUIRE(!is_constructible_default<int&&>::value);
}

// own types

class D
{
public:
    D() = delete;
    D(const D&) = delete;
    D(D&&) = delete;
};

TEST_CASE("Is default constructible if all deleted","[Meta][is_constructible_default]"){
    REQUIRE(!is_constructible_default<D>::value);
}

TEST_CASE("Is pointer for all deleted default constructible","[Meta][is_constructible_default]"){
    REQUIRE(is_constructible_default<D*>::value);
}

TEST_CASE("Is reference for all deleted default constructible","[Meta][is_constructible_default]"){
    REQUIRE(!is_constructible_default<D&>::value);
}

TEST_CASE("Is rreference for all deleted default constructible","[Meta][is_constructible_default]"){
    REQUIRE(!is_constructible_default<D&&>::value);
}
