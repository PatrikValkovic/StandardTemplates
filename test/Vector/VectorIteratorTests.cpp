#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9};

TEST_CASE("Vector's Iterator should iterate thought all elements", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator it = instance.Begin();
    for(int i=0;i<5;i++, it++)
        REQUIRE(*it == array[i]);
}

TEST_CASE("Vector's ConstIterator should iterate thought all elements", "[Vector][Iterator]") {
    const Vector<int> instance(array, 5);
    Vector<int>::ConstIterator it = instance.Begin();
    for(int i=0;i<5;i++, it++)
        REQUIRE(*it == array[i]);
}

TEST_CASE("Vector's Iterator should iterate thought all elements, even the deleted", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    instance.Delete(2);
    Vector<int>::Iterator it = instance.Begin();
    for(int i=0;i<20;i++, it++);
}

TEST_CASE("Vector's ConstIterator should iterate thought all elements, even the deleted", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    instance.Delete(2);
    Vector<int>::ConstIterator it = instance.Begin();
    for(int i=0;i<20;i++, it++);
}


TEST_CASE("Vector's Iterator should iterate thought all elements using pre-increment", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator it = instance.Begin();
    for(int i=0;i<5;i++, ++it)
        REQUIRE(*it == array[i]);
}

TEST_CASE("Vector's ConstIterator should iterate thought all elements using pre-increment", "[Vector][Iterator]") {
    const Vector<int> instance(array, 5);
    Vector<int>::ConstIterator it = instance.Begin();
    for(int i=0;i<5;i++, ++it)
        REQUIRE(*it == array[i]);
}

TEST_CASE("Vector's Iterator should iterate thought all elements, even the deleted using pre-increment", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    instance.Delete(2);
    Vector<int>::Iterator it = instance.Begin();
    for(int i=0;i<20;i++, ++it);
}

TEST_CASE("Vector's ConstIterator should iterate thought all elements, even the deleted using pre-increment", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    instance.Delete(2);
    Vector<int>::ConstIterator it = instance.Begin();
    for(int i=0;i<20;i++, ++it);
}



TEST_CASE("Vector's Iterator should iterate thought all elements, even the deleted, by Next", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    instance.Delete(2);
    Vector<int>::Iterator it = instance.Begin();
    for(int i=0;i<20 && it.Next();i++);
}

TEST_CASE("Vector's ConstIterator should iterate thought all elements, even the deleted, by Next", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    instance.Delete(2);
    Vector<int>::ConstIterator it = instance.Begin();
    for(int i=0;i<20 && it.Next();i++);
}

TEST_CASE("Vector's Iterator comparsion operators", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator b = instance.Begin();
    Vector<int>::Iterator e = instance.End();
    REQUIRE(b != e);
    b = instance.End();
    REQUIRE(b == e);
}

TEST_CASE("Vector's ConstIterator comparsion operators", "[Vector][Iterator]") {
    const Vector<int> instance(array, 5);
    Vector<int>::ConstIterator b = instance.Begin();
    Vector<int>::ConstIterator e = instance.End();
    REQUIRE(b != e);
    b = instance.End();
    REQUIRE(b == e);
}

class MyClass
{
public:
    int variable;
};

TEST_CASE("Vector's Iterator structured dereference should work", "[Vector][Iterator]") {
    Vector<MyClass> instance(10);
    MyClass x;
    x.variable = 5;
    instance.Push(x);
    Vector<MyClass>::Iterator b = instance.Begin();
    REQUIRE(b->variable == 5);
}

TEST_CASE("Vector's ConstIterator structured dereference should work", "[Vector][Iterator]") {
    Vector<MyClass> instance(10);
    MyClass x;
    x.variable = 5;
    instance.Push(x);
    Vector<MyClass>::ConstIterator b = instance.Begin();
    REQUIRE(b->variable == 5);
}

TEST_CASE("Vector's Iterator should jump over multiple elements", "[Vector][Iterator]") {
    Vector<int> instance(25);
    instance.Push(array, 5);
    Vector<int>::Iterator b = instance.Begin();
    REQUIRE(b.Next(1));
    b = instance.Begin();
    REQUIRE(b.Next(5));
    b = instance.Begin();
    REQUIRE(b.Next(10));
    b = instance.Begin();
    REQUIRE(b.Next(25));
    b = instance.Begin();
    REQUIRE(b.Next(26)); //because of the end node
    b = instance.Begin();
    REQUIRE(!b.Next(27));
    b = instance.Begin();
    REQUIRE(!b.Next(30));
}

TEST_CASE("Vector's ConstIterator should jump over multiple elements", "[Vector][Iterator]") {
    Vector<int> instance(25);
    instance.Push(array, 5);
    Vector<int>::ConstIterator b = instance.Begin();
    REQUIRE(b.Next(1));
    b = instance.Begin();
    REQUIRE(b.Next(5));
    b = instance.Begin();
    REQUIRE(b.Next(10));
    b = instance.Begin();
    REQUIRE(b.Next(25));
    b = instance.Begin();
    REQUIRE(b.Next(26)); //because of the end node
    b = instance.Begin();
    REQUIRE(!b.Next(27));
    b = instance.Begin();
    REQUIRE(!b.Next(30));
}

TEST_CASE("Vector's Iterator should jump over multiple elements using plus operator", "[Vector][Iterator]") {
    Vector<int> instance(25);
    instance.Push(array, 5);
    Vector<int>::Iterator b = instance.Begin();
    Vector<int>::Iterator t = b + 1;
    REQUIRE(b.Next());
    REQUIRE(b == t);

    b = instance.Begin();
    t = b + 5;
    REQUIRE(b.Next(5));
    REQUIRE(b == t);
    REQUIRE(t == instance.End());

    b = instance.Begin();
    t = b + 10;
    REQUIRE(b.Next(10));
    REQUIRE(b == t);

    b = instance.Begin();
    t = b + 25;
    REQUIRE(b.Next(25));
    REQUIRE(b == t);

    b = instance.Begin();
    t = b + 26;
    REQUIRE(b.Next(26)); //because of the end node
    REQUIRE(b == t);

    b = instance.Begin();
    t = b + 27;
    REQUIRE(b == t);

    b = instance.Begin();
    t = b + 30;
    REQUIRE(b == t);
}

TEST_CASE("Vector's ConstIterator should jump over multiple elements using plus operator", "[Vector][Iterator]") {
    Vector<int> instance(25);
    instance.Push(array, 5);
    Vector<int>::ConstIterator b = instance.Begin();
    Vector<int>::ConstIterator t = b + 1;
    REQUIRE(b.Next());
    REQUIRE(b == t);

    b = instance.Begin();
    t = b + 5;
    REQUIRE(b.Next(5));
    REQUIRE(b == t);
    REQUIRE(t == instance.End());

    b = instance.Begin();
    t = b + 10;
    REQUIRE(b.Next(10));
    REQUIRE(b == t);

    b = instance.Begin();
    t = b + 25;
    REQUIRE(b.Next(25));
    REQUIRE(b == t);

    b = instance.Begin();
    t = b + 26;
    REQUIRE(b.Next(26)); //because of the end node
    REQUIRE(b == t);

    b = instance.Begin();
    t = b + 27;
    REQUIRE(b == t);

    b = instance.Begin();
    t = b + 30;
    REQUIRE(b == t);
}

TEST_CASE("Vector's Iterator should jump the the end", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator b = instance.Begin();
    Vector<int>::Iterator e = instance.End();
    b.JumpToEnd();
    REQUIRE(b == e);
}

TEST_CASE("Vector's ConstIterator should jump the the end", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    Vector<int>::ConstIterator b = instance.Begin();
    Vector<int>::ConstIterator e = instance.End();
    b.JumpToEnd();
    REQUIRE(b == e);
}

TEST_CASE("Vector's Iterator should jump the the beginning", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator b = instance.Begin();
    Vector<int>::Iterator e = instance.End();
    e.JumpToBegin();
    REQUIRE(b == e);
}

TEST_CASE("Vector's ConstIterator should jump the the beginning", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    Vector<int>::ConstIterator b = instance.Begin();
    Vector<int>::ConstIterator e = instance.End();
    e.JumpToBegin();
    REQUIRE(b == e);
}
