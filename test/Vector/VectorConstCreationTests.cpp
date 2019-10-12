#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9};

TEST_CASE("Should create empty const Vector", "[Vector][Creation]") {
    const Vector<int> instance;
    REQUIRE(instance.Empty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create const Vector with capacity", "[Vector][Creation]"){
    const Vector<int> instance(4);
    REQUIRE(instance.Empty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create const Vector with more capacity", "[Vector][Creation]"){
    const Vector<int> instance(25);
    REQUIRE(instance.Empty());
    REQUIRE(instance.Size() == 0);
}


TEST_CASE("Should create const Vector with no capacity if zero capacity passed", "[Vector][Creation]"){
    const Vector<int> instance(0);
    REQUIRE(instance.Empty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create const Vector with huge capacity", "[Vector][Creation]"){
    const Vector<int> instance(1584);
    REQUIRE(instance.Empty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create const Vector with default values", "[Vector][Creation]"){
    const Vector<int> instance(array, 5);
    REQUIRE(!instance.Empty());
    REQUIRE(instance.Size() == 5);
    for (int a = 0; a < 5; a++)
        REQUIRE(instance[a] == array[a]);
    Vector<int>::ConstIterator b = instance.Begin();
    Vector<int>::ConstIterator e = instance.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
}

TEST_CASE("Should create const Vector from another Vector by copy", "[Vector][Creation]"){
    const Vector<int> instance(array, 5);
    const Vector<int> second(instance);
    REQUIRE(instance.Size() == 5);
    REQUIRE(second.Size() == 5);

    for (int a = 0; a < 5; a++)
        REQUIRE(instance[a] == array[a]);
    for (int a = 0; a < 5; a++)
        REQUIRE(second[a] == array[a]);

    Vector<int>::ConstIterator b = instance.Begin();
    Vector<int>::ConstIterator e = instance.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
    b = second.Begin();
    e = second.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
}

TEST_CASE("Should create const Vector from another Vector by move", "[Vector][Creation]")
{
    Vector<int> instance(array, 5);
    const Vector<int> second(move(instance));
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.Empty());
    REQUIRE(second.Size() == 5);
    REQUIRE(!second.Empty());

    for (int a = 0; a < 5; a++)
        REQUIRE(second[a] == array[a]);

    Vector<int>::ConstIterator b = second.Begin();
    Vector<int>::ConstIterator e = second.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
}
