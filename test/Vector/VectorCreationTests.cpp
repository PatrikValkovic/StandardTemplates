#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


const int array[] = {1, 3, 5, 7, 9};

TEST_CASE("Should create empty Vector", "[Vector][Creation]") {
    Vector<int> instance;
    REQUIRE(instance.Empty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create Vector with capacity", "[Vector][Creation]"){
    Vector<int> instance(4);
    REQUIRE(instance.Empty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create Vector with more capacity", "[Vector][Creation]"){
    Vector<int> instance(25);
    REQUIRE(instance.Empty());
    REQUIRE(instance.Size() == 0);
}


TEST_CASE("Should create Vector with no capacity if zero capacity passed", "[Vector][Creation]"){
    Vector<int> instance(0);
    REQUIRE(instance.Empty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create Vector with huge capacity", "[Vector][Creation]"){
    Vector<int> instance(1584);
    REQUIRE(instance.Empty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create Vector with default values", "[Vector][Creation]"){
    Vector<int> instance(array, 5);
    REQUIRE(!instance.Empty());
    REQUIRE(instance.Size() == 5);
    for (int a = 0; a < 5; a++)
        REQUIRE(instance[a] == array[a]);
    Vector<int>::Iterator b = instance.Begin();
    Vector<int>::Iterator e = instance.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
}

TEST_CASE("Should create Vector from another Vector by copy", "[Vector][Creation]"){
    Vector<int> instance(array, 5);
    Vector<int> second(instance);
    REQUIRE(instance.Size() == 5);
    REQUIRE(second.Size() == 5);

    for (int a = 0; a < 5; a++)
        REQUIRE(instance[a] == array[a]);
    for (int a = 0; a < 5; a++)
        REQUIRE(second[a] == array[a]);

    Vector<int>::Iterator b = instance.Begin();
    Vector<int>::Iterator e = instance.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
    b = second.Begin();
    e = second.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
}

TEST_CASE("Should create Vector from another Vector by move", "[Vector][Creation]"){
    Vector<int> instance(array, 5);
    Vector<int> second(move(instance));
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.Empty());
    REQUIRE(second.Size() == 5);
    REQUIRE(!second.Empty());

    for (int a = 0; a < 5; a++)
        REQUIRE(second[a] == array[a]);

    Vector<int>::Iterator b = second.Begin();
    Vector<int>::Iterator e = second.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
}



