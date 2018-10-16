#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

class T1{
public:
    T1& operator=(const T1&) = default;
    T1& operator=(T1&&) = delete;
};

TEST_CASE("Should have assignment copy operator","[Meta][is_assignable_copy]"){
    REQUIRE(is_assignable_copy<T1>::value);
}

class T2{
public:
    T2& operator=(const T2&) = delete;
    T2& operator=(T2&&) = delete;
};

TEST_CASE("Should have not assignment copy operator","[Meta][is_assignable_copy]"){
    REQUIRE(!is_assignable_copy<T2>::value);
}

class T3{
private:
    T3& operator=(const T3&) = default;
    T3& operator=(T3&&) = delete;
};

TEST_CASE("Should have assignment copy operator but private","[Meta][is_assignable_copy]"){
    REQUIRE(!is_assignable_copy<T3>::value);
}




TEST_CASE("Int is assignable copy","[Meta][is_assignable_copy]"){
    REQUIRE(is_assignable_copy<int>::value);
}

TEST_CASE("Int pointer is assignable copy","[Meta][is_assignable_copy]"){
    REQUIRE(is_assignable_copy<int*>::value);
}


TEST_CASE("Int reference is assignable copy","[Meta][is_assignable_copy]"){
    REQUIRE(is_assignable_copy<int&>::value);
}

TEST_CASE("Int rreference is assignable copy","[Meta][is_assignable_copy]"){
    REQUIRE(is_assignable_copy<int&&>::value);
}




TEST_CASE("T2 is not assignable copy","[Meta][is_assignable_copy]"){
    REQUIRE(!is_assignable_copy<T2>::value);
}

TEST_CASE("T2 pointer is assignable copy","[Meta][is_assignable_copy]"){
    REQUIRE(is_assignable_copy<T2*>::value);
}

TEST_CASE("T2 reference is assignable copy","[Meta][is_assignable_copy]"){
    REQUIRE(!is_assignable_copy<T2&>::value);
}

TEST_CASE("T2 rreference is assignable copy","[Meta][is_assignable_copy]"){
    REQUIRE(!is_assignable_copy<T2&&>::value);
}

