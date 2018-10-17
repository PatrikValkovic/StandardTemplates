#define CATCH_CONFIG_MAIN
#include "../libs/catch.h"
#include "../Templates.h"

using namespace Templates;

TEST_CASE("SharedPointer should be allocated with nullptr", "[SharedPointer]")
{
    SharedPointer<int> a;
    REQUIRE(a.Get() == nullptr);
}

TEST_CASE("SharedPointer should be allocated with pointer", "[SharedPointer]")
{
    SharedPointer<int> a(new int(10));
    REQUIRE(a.Get() != nullptr);
    REQUIRE(*a == 10);
}

TEST_CASE("SharedPointer should be allocated with second shared pointer with nullptr", "[SharedPointer]")
{
    SharedPointer<int> a;
    SharedPointer<int> b(move(a));
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() == nullptr);
}

TEST_CASE("SharedPointer should be allocated with second shared pointer with pointer", "[SharedPointer]")
{
    SharedPointer<int> a(new int(10));
    SharedPointer<int> b(move(a));
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() != nullptr);
    REQUIRE(*b == 10);
}

TEST_CASE("SharedPointer should perform assignment operator with second shared pointer with nullptr", "[SharedPointer]")
{
    SharedPointer<int> a;
    SharedPointer<int> b;
    b = move(a);
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() == nullptr);
}

TEST_CASE("SharedPointer should perform assignment operator with second shared pointer with pointer", "[SharedPointer]")
{
    SharedPointer<int> a(new int(10));
    SharedPointer<int> b;
    b = move(a);
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() != nullptr);
    REQUIRE(*b == 10);
}

TEST_CASE("SharedPointer asterisk operator should work", "[SharedPointer]")
{
    SharedPointer<int> a(new int(10));
    REQUIRE(*a == 10);
}

TEST_CASE("SharedPointer asterisk can set the value", "[SharedPointer]")
{
    SharedPointer<int> a(new int(10));
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
TEST_CASE("SharedPointer arrow operator should work", "[SharedPointer]")
{
    SharedPointer<T1> a(new T1(10));
    REQUIRE(a->_data == 10);
}

TEST_CASE("SharedPointer bool operator should return true for pointer", "[SharedPointer]")
{
    SharedPointer<int> a(new int(10));
    REQUIRE((bool)a);
}

TEST_CASE("SharedPointer bool operator should return false for nullptr", "[SharedPointer]")
{
    SharedPointer<int> a(nullptr);
    REQUIRE(!(bool)a);
}


TEST_CASE("SharedPointer should release the value", "[SharedPointer]")
{
    SharedPointer<int> a(new int(5));
    REQUIRE(*a == 5);
    a.Release();
    REQUIRE(a.Get() == nullptr);
}

TEST_CASE("SharedPointer release should work even with nullptr", "[SharedPointer]")
{
    SharedPointer<int> a;
    REQUIRE(a.Get() == nullptr);
    a.Release();
    REQUIRE(a.Get() == nullptr);
}

TEST_CASE("SharedPointer Get and Raw are same", "[SharedPointer]")
{
    SharedPointer<int> a(new int(5));
    REQUIRE(a.Get() == a.Raw());
}

TEST_CASE("SharedPointer swap with nullptr pointers works", "[SharedPointer][swap]")
{
    SharedPointer<int> a;
    SharedPointer<int> b;
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() == nullptr);
    using Templates::swap;
    swap(a, b);
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() == nullptr);
}

TEST_CASE("SharedPointer swap with one nullptr pointer works", "[SharedPointer][swap]")
{
    SharedPointer<int> a(new int(10));
    SharedPointer<int> b;
    REQUIRE(a.Get() != nullptr);
    REQUIRE(*a == 10);
    REQUIRE(b.Get() == nullptr);
    using Templates::swap;
    swap(a, b);
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() != nullptr);
    REQUIRE(*b == 10);
}

TEST_CASE("SharedPointer swap with pointer works", "[SharedPointer][swap]")
{
    SharedPointer<int> a(new int(10));
    SharedPointer<int> b(new int(9));
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

TEST_CASE("make_shared works for integer", "[SharedPointer][make_shared]")
{
    auto p = make_shared<int>(5);
    REQUIRE(*p == 5);
}

class MyClass{
public:
    MyClass(int a, int b){};
};

TEST_CASE("make_shared with more parameters", "[SharedPointer][make_shared]")
{
    auto p = make_shared<MyClass>(5,10);
}

TEST_CASE("make_shared with no parameter", "[SharedPointer][make_shared]")
{
    auto p = make_shared<int>();
    *p = 4;
    REQUIRE(*p == 4);
}






TEST_CASE("Empty SharedPointer should work on array", "[SharedPointer]")
{
    SharedPointer<int[]> a;
    REQUIRE(a.Get() == nullptr);
    a.Release();
    REQUIRE(a.Get() == nullptr);
}

TEST_CASE("SharedPointer should work on array created in place", "[SharedPointer]")
{
    SharedPointer<int[]> a(new int[10]);
    a.Release();
    REQUIRE(a.Get() == nullptr);
}

TEST_CASE("SharedPointer should work on array", "[SharedPointer]")
{
    int* arr = new int[10];
    for(int i=0;i<10;i++)
        arr[i] = i;

    SharedPointer<int[]> a(arr);

    REQUIRE(a.Get() != nullptr);
    for(int i=0;i<10;i++)
        REQUIRE(a[i] == i);
    a.Release();
    REQUIRE(a.Get() == nullptr);
}


TEST_CASE("SharedPointer assignment work", "[SharedPointer]")
{
    SharedPointer<int> a(new int(5));
    SharedPointer<int> b(nullptr);

    REQUIRE(*a == 5);
    REQUIRE(b.Raw() == nullptr);

    b = a;

    REQUIRE(*b == 5);
    REQUIRE(*a == 5);
}

static bool SHOULD_BE_DELETED;
class T2{
public:
    ~T2()
    { REQUIRE(SHOULD_BE_DELETED); }
};
TEST_CASE("SharedPointer entity not deleted after assignment", "[SharedPointer]")
{
    SHOULD_BE_DELETED = false;
    T2* t2 = new T2();
    SharedPointer<T2> a(t2);
    SharedPointer<T2> b(nullptr);

    REQUIRE(b.Raw() == nullptr);
    b = a;
    REQUIRE(b.Raw() != nullptr);

    a.Release();
    SHOULD_BE_DELETED = true;
    b.Release();
    SHOULD_BE_DELETED = false;
}

TEST_CASE("SharedPointer copy constructor work", "[SharedPointer]")
{
    SharedPointer<int> a(new int(5));
    SharedPointer<int> b(a);

    REQUIRE(*a == 5);
    REQUIRE(*b == 5);
}

TEST_CASE("SharedPointer entity not deleted after copy constructor", "[SharedPointer]")
{
    SHOULD_BE_DELETED = false;
    T2* t2 = new T2();
    SharedPointer<T2> a(t2);
    SharedPointer<T2> b(a);

    REQUIRE(b.Raw() != nullptr);
    REQUIRE(b.Raw() != nullptr);

    a.Release();
    SHOULD_BE_DELETED= true;
    b.Release();
    SHOULD_BE_DELETED = false;
}
