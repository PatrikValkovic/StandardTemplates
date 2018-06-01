#define CATCH_CONFIG_MAIN
#include "../libs/catch.h"
#include "../Templates.h"

using namespace Templates;

TEST_CASE("UniquePointer should be allocated with nullptr", "[UniquePointer]")
{
    UniquePointer<int> a;
}

TEST_CASE("UniquePointer should be allocated with pointer", "[UniquePointer]")
{
    UniquePointer<int> a(new int(10));
}

TEST_CASE("UniquePointer should be allocated with second unique pointer with nullptr", "[UniquePointer]")
{
    UniquePointer<int> a;
    UniquePointer<int> b(move(a));
}

TEST_CASE("UniquePointer should be allocated with second unique pointer with pointer", "[UniquePointer]")
{
    UniquePointer<int> a(new int(10));
    UniquePointer<int> b(move(a));
}

TEST_CASE("UniquePointer should perform assignment operator with second unique pointer with nullptr", "[UniquePointer]")
{
    UniquePointer<int> a;
    UniquePointer<int> b;
    b = move(a);
}

TEST_CASE("UniquePointer should perform assignment operator with second unique pointer with pointer", "[UniquePointer]")
{
    UniquePointer<int> a(new int(10));
    UniquePointer<int> b;
    b = move(a);
}

TEST_CASE("UniquePointer asterisk operator should work", "[UniquePointer]")
{
    UniquePointer<int> a(new int(10));
    REQUIRE(*a == 10);
}


class T1{
public:
    int _data;
    explicit T1(int data) : _data(data)
    {}
};
TEST_CASE("UniquePointer arrow operator should work", "[UniquePointer]")
{
    UniquePointer<T1> a(new T1(10));
    REQUIRE(a->_data == 10);
}

TEST_CASE("UniquePointer bool operator should return true for pointer", "[UniquePointer]")
{
    UniquePointer<int> a(new int(10));
    REQUIRE((bool)a);
}

TEST_CASE("UniquePointer bool operator should return false for nullptr", "[UniquePointer]")
{
    UniquePointer<int> a(nullptr);
    REQUIRE(!(bool)a);
}

