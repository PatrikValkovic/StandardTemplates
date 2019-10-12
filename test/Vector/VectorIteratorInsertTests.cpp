#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9};
int second[] = {90, 91, 92, 93, 94};

TEST_CASE("Vector's Iterator should insert element from beginning", "[Vector][Iterator][Insert]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator it = instance.Begin();
    it.Insert(10);
    REQUIRE(instance.Size() == 6);
    REQUIRE(instance[0] == 10);
    for(int i=1;i<6;i++)
        REQUIRE(instance[i] == array[i-1]);
}

TEST_CASE("Vector's Iterator should insert elements from beginning", "[Vector][Iterator][Insert]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator it = instance.Begin();
    it.Insert(second, 5);
    REQUIRE(instance.Size() == 10);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == second[i]);
    for(int i=5;i<10;i++)
        REQUIRE(instance[i] == array[i-5]);
}

TEST_CASE("Vector's Iterator should insert element in the middle", "[Vector][Iterator][Insert]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator it = instance.Begin() + 2;
    it.Insert(10);
    REQUIRE(instance.Size() == 6);
    for(int i=0;i<2;i++)
        REQUIRE(instance[i] == array[i]);
    REQUIRE(instance[2] == 10);
    for(int i=3;i<6;i++)
        REQUIRE(instance[i] == array[i-1]);
}

TEST_CASE("Vector's Iterator should insert elements in the middle", "[Vector][Iterator][Insert]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator it = instance.Begin() + 2;
    it.Insert(second, 5);
    REQUIRE(instance.Size() == 10);
    for(int i=0;i<2;i++)
        REQUIRE(instance[i] == array[i]);
    for(int i=2;i<7;i++)
        REQUIRE(instance[i] == second[i-2]);
    for(int i=7;i<10;i++)
        REQUIRE(instance[i] == array[i-5]);
}

TEST_CASE("Vector's Iterator should insert element at the end", "[Vector][Iterator][Insert]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator it = instance.End();
    it.Insert(10);
    REQUIRE(instance.Size() == 6);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == array[i]);
    REQUIRE(instance[5] == 10);
}

TEST_CASE("Vector's Iterator should insert elements at the end", "[Vector][Iterator][Insert]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator it = instance.End();
    it.Insert(second, 5);
    REQUIRE(instance.Size() == 10);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == array[i]);
    for(int i=5;i<10;i++)
        REQUIRE(instance[i] == second[i-5]);
}
