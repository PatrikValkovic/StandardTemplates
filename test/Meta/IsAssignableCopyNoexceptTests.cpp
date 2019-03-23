#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

class T1{
public:
    T1& operator=(const T1&) noexcept {return *this;};
    T1& operator=(T1&&) = delete;
};

TEST_CASE("Should have assignment copy noexcept operator","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(is_assignable_copy_noexcept<T1>::value);
}

class T2{
public:
    T2& operator=(const T2&) noexcept(false) {return *this;};
    T2& operator=(T2&&) = delete;
};

TEST_CASE("Should not have assignment copy noexcept operator if marked","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(!is_assignable_copy_noexcept<T2>::value);
}

class T3{
public:
    T3& operator=(const T3&) {return *this;};
    T3& operator=(T3&&) = delete;
};

TEST_CASE("Should not have assignment copy noexcept operator if not marked","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(!is_assignable_copy_noexcept<T3>::value);
}

class T4{
private:
    T4& operator=(const T4&) noexcept {return *this;};
    T4& operator=(T4&&) = delete;
};

TEST_CASE("Should not have assignment copy noexcept operator if private","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(!is_assignable_copy_noexcept<T4>::value);
}

class T5{
public:
    T5& operator=(const T5&) = delete;
    T5& operator=(T5&&) = default;
};

TEST_CASE("Should not have assignment copy noexcept operator if deleted","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(!is_assignable_copy_noexcept<T5>::value);
}






TEST_CASE("Int is assignable copy noexcept","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(is_assignable_copy_noexcept<int>::value);
}

TEST_CASE("Int pointer is assignable copy noexcept","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(is_assignable_copy_noexcept<int*>::value);
}


TEST_CASE("Int reference is assignable copy noexcept","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(is_assignable_copy_noexcept<int&>::value);
}

TEST_CASE("Int rreference is assignable copy noexcept","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(is_assignable_copy_noexcept<int&&>::value);
}




TEST_CASE("T2 is not assignable copy noexcept","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(!is_assignable_copy_noexcept<T2>::value);
}

TEST_CASE("T2 pointer is assignable copy noexcept","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(is_assignable_copy_noexcept<T2*>::value);
}

TEST_CASE("T2 reference is assignable copy noexcept","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(!is_assignable_copy_noexcept<T2&>::value);
}

TEST_CASE("T2 rreference is assignable copy noexcept","[Meta][is_assignable_copy_noexcept]"){
    REQUIRE(!is_assignable_copy_noexcept<T2&&>::value);
}

