#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates;

TEST_CASE("UniquePointer should be allocated with nullptr", "[UniquePointer]")
{
    UniquePointer<int> a;
    REQUIRE(a.Get() == nullptr);
}

TEST_CASE("UniquePointer should be allocated with pointer", "[UniquePointer]")
{
    UniquePointer<int> a(new int(10));
    REQUIRE(a.Get() != nullptr);
    REQUIRE(*a == 10);
}

TEST_CASE("UniquePointer should be allocated with second unique pointer with nullptr", "[UniquePointer]")
{
    UniquePointer<int> a;
    UniquePointer<int> b(move(a));
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() == nullptr);
}

TEST_CASE("UniquePointer should be allocated with second unique pointer with pointer", "[UniquePointer]")
{
    UniquePointer<int> a(new int(10));
    UniquePointer<int> b(move(a));
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() != nullptr);
    REQUIRE(*b == 10);
}

TEST_CASE("UniquePointer should perform assignment operator with second unique pointer with nullptr", "[UniquePointer]")
{
    UniquePointer<int> a;
    UniquePointer<int> b;
    b = move(a);
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() == nullptr);
}

TEST_CASE("UniquePointer should perform assignment operator with second unique pointer with pointer", "[UniquePointer]")
{
    UniquePointer<int> a(new int(10));
    UniquePointer<int> b;
    b = move(a);
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() != nullptr);
    REQUIRE(*b == 10);
}

TEST_CASE("UniquePointer asterisk operator should work", "[UniquePointer]")
{
    UniquePointer<int> a(new int(10));
    REQUIRE(*a == 10);
}

TEST_CASE("UniquePointer asterisk can set the value", "[UniquePointer]")
{
    UniquePointer<int> a(new int(10));
    REQUIRE(*a == 10);
    *a = 5;
    REQUIRE(*a == 5);
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


TEST_CASE("UniquePointer should release the value", "[UniquePointer]")
{
    UniquePointer<int> a(new int(5));
    REQUIRE(*a == 5);
    a.Release();
    REQUIRE(a.Get() == nullptr);
}

TEST_CASE("UniquePointer release should work even with nullptr", "[UniquePointer]")
{
    UniquePointer<int> a;
    REQUIRE(a.Get() == nullptr);
    a.Release();
    REQUIRE(a.Get() == nullptr);
}

TEST_CASE("UniquePointer Get and Raw are same", "[UniquePointer]")
{
    UniquePointer<int> a(new int(5));
    REQUIRE(a.Get() == a.Raw());
}

TEST_CASE("UniquePointer swap with nullptr pointers works", "[UniquePointer][swap]")
{
    UniquePointer<int> a;
    UniquePointer<int> b;
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() == nullptr);
    using Templates::swap;
    swap(a, b);
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() == nullptr);
}

TEST_CASE("UniquePointer swap with one nullptr pointer works", "[UniquePointer][swap]")
{
    UniquePointer<int> a(new int(10));
    UniquePointer<int> b;
    REQUIRE(a.Get() != nullptr);
    REQUIRE(*a == 10);
    REQUIRE(b.Get() == nullptr);
    using Templates::swap;
    swap(a, b);
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() != nullptr);
    REQUIRE(*b == 10);
}

TEST_CASE("UniquePointer swap with pointer works", "[UniquePointer][swap]")
{
    UniquePointer<int> a(new int(10));
    UniquePointer<int> b(new int(9));
    REQUIRE(a.Get() != nullptr);
    REQUIRE(*a == 10);
    REQUIRE(b.Get() != nullptr);
    REQUIRE(*b == 9);
    using Templates::swap;
    swap(a, b);
    REQUIRE(a.Get() != nullptr);
    REQUIRE(*a == 9);
    REQUIRE(b.Get() != nullptr);
    REQUIRE(*b == 10);
}

TEST_CASE("make_unique works for integer", "[UniquePointer][make_unique]")
{
    auto p = make_unique<int>(5);
    REQUIRE(*p == 5);
}

class MyClass{
public:
    MyClass(int a, int b){};
};

TEST_CASE("make_unique with more parameters", "[UniquePointer][make_unique]")
{
    auto p = make_unique<MyClass>(5,10);
}

TEST_CASE("make_unique with no parameter", "[UniquePointer][make_unique]")
{
    auto p = make_unique<int>();
    *p = 4;
    REQUIRE(*p == 4);
}



// Deleters
TEST_CASE("Should call just delete for pointer", "[UniquePointer][defaultDeleter]")
{
    __defaultDeleter<int>::perform(new int(10));
}

TEST_CASE("Should call delete[] for array pointer", "[UniquePointer][defaultDeleter]")
{
    __defaultDeleter<int[]>::perform(new int[10]);
}





TEST_CASE("Empty UniquePointer should work on array", "[UniquePointer]")
{
    UniquePointer<int[]> a;
    REQUIRE(a.Get() == nullptr);
    a.Release();
    REQUIRE(a.Get() == nullptr);
}

TEST_CASE("UniquePointer should work on array created in place", "[UniquePointer]")
{
    UniquePointer<int[]> a(new int[10]);
    a.Release();
    REQUIRE(a.Get() == nullptr);
}

TEST_CASE("UniquePointer should work on array", "[UniquePointer]")
{
    int* arr = new int[10];
    for(int i=0;i<10;i++)
        arr[i] = i;

    UniquePointer<int[]> a(arr);

    REQUIRE(a.Get() != nullptr);
    for(int i=0;i<10;i++)
        REQUIRE(a[i] == i);
    a.Release();
    REQUIRE(a.Get() == nullptr);
}

TEST_CASE("Calling assignment on same instance of UniquePointer should not be problem", "[UniquePointer]")
{
    UniquePointer<int> a = make_unique<int>(5);
    a = move(a);
    REQUIRE(*a == 5);
}

TEST_CASE("Should call asterisk operator on const UniquePointer", "[UniquePointer]")
{
    const UniquePointer<int> a = make_unique<int>(5);
    REQUIRE(*a == 5);
}

TEST_CASE("Should call bracket operator on const UniquePointer", "[UniquePointer]")
{
    int* arr = new int[10];
    for(int i=0;i<10;i++)
        arr[i] = i;
    const UniquePointer<int[]> a(arr);

    for(int i=0;i<10;i++)
        REQUIRE(a[i] == i);
}
