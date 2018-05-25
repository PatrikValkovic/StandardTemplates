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