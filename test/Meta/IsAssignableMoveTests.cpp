#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

class T4{
public:
    T4& operator=(const T4&) = delete;
    T4& operator=(T4&&) = default;
};

TEST_CASE("Should have assignment move operator","[Meta][is_assignable_move]"){
    REQUIRE(is_assignable_move<T4>::value);
}

class T5{
public:
    T5& operator=(const T5&) = delete;
    T5& operator=(T5&&) = delete;
};

TEST_CASE("Should have not assignment move operator","[Meta][is_assignable_move]"){
    REQUIRE(!is_assignable_move<T5>::value);
}

class T6{
private:
    T6& operator=(const T6&) = delete;
    T6& operator=(T6&&) = default;
};

TEST_CASE("Should have assignment move operator but private","[Meta][is_assignable_move]"){
    REQUIRE(!is_assignable_move<T6>::value);
}




TEST_CASE("Int is assignable copy","[Meta][is_assignable_move]"){
    REQUIRE(is_assignable_move<int>::value);
}

TEST_CASE("Int pointer is assignable copy","[Meta][is_assignable_move]"){
    REQUIRE(is_assignable_move<int*>::value);
}


TEST_CASE("Int reference is assignable copy","[Meta][is_assignable_move]"){
    REQUIRE(is_assignable_move<int&>::value);
}

TEST_CASE("Int rreference is assignable copy","[Meta][is_assignable_move]"){
    REQUIRE(is_assignable_move<int&&>::value);
}




TEST_CASE("T2 is not assignable copy","[Meta][is_assignable_move]"){
    REQUIRE(!is_assignable_move<T5>::value);
}

TEST_CASE("T2 pointer is assignable copy","[Meta][is_assignable_move]"){
    REQUIRE(is_assignable_move<T5*>::value);
}

TEST_CASE("T2 reference is assignable copy","[Meta][is_assignable_move]"){
    REQUIRE(!is_assignable_move<T5&>::value);
}

TEST_CASE("T2 rreference is assignable copy","[Meta][is_assignable_move]"){
    REQUIRE(!is_assignable_move<T5&&>::value);
}