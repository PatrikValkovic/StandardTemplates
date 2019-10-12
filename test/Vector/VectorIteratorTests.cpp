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

TEST_CASE("Vector's Iterator should iterate thought all elements, even the allocated", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    instance.Delete(2);
    Vector<int>::Iterator it = instance.Begin();
    for(int i=0;i<5;i++, it++);
}

TEST_CASE("Vector's ConstIterator should iterate thought all elements, even the allocated", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    instance.Delete(2);
    Vector<int>::ConstIterator it = instance.Begin();
    for(int i=0;i<5;i++, it++);
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
    for(int i=0;i<5;i++, ++it);
}

TEST_CASE("Vector's ConstIterator should iterate thought all elements, even the deleted using pre-increment", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    instance.Delete(2);
    Vector<int>::ConstIterator it = instance.Begin();
    for(int i=0;i<5;i++, ++it);
}



TEST_CASE("Vector's Iterator should iterate thought all elements, even the allocated, by plusplus", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    instance.Delete(2);
    Vector<int>::Iterator it = instance.Begin();
    for(int i=0;i<5;i++, it++);
}

TEST_CASE("Vector's ConstIterator should iterate thought all elements, even the allocated, by plusplus", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    instance.Delete(2);
    Vector<int>::ConstIterator it = instance.Begin();
    for(int i=0;i<5;i++, it++);
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

TEST_CASE("Vector's Iterator should jump the the end", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator b = instance.Begin();
    Vector<int>::Iterator e = instance.End();
    b.End();
    REQUIRE(b == e);
}

TEST_CASE("Vector's ConstIterator should jump the the end", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    Vector<int>::ConstIterator b = instance.Begin();
    Vector<int>::ConstIterator e = instance.End();
    b.End();
    REQUIRE(b == e);
}

TEST_CASE("Vector's Iterator should jump the the beginning", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator b = instance.Begin();
    Vector<int>::Iterator e = instance.End();
    e.Begin();
    REQUIRE(b == e);
}

TEST_CASE("Vector's ConstIterator should jump the the beginning", "[Vector][Iterator]") {
    Vector<int> instance(array, 5);
    Vector<int>::ConstIterator b = instance.Begin();
    Vector<int>::ConstIterator e = instance.End();
    e.Begin();
    REQUIRE(b == e);
}
