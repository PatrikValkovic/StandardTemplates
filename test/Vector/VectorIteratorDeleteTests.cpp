#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

TEST_CASE("Vector's Iterator should delete element from beginning", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin();
    it.Delete();
    REQUIRE(instance.Size() == 9);
    for(int i=0;i<9;i++)
        REQUIRE(instance[i] == array[i+1]);
}

TEST_CASE("Vector's Iterator should delete two elements from beginning", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin();
    it.Delete(2);
    REQUIRE(instance.Size() == 8);
    for(int i=0;i<8;i++)
        REQUIRE(instance[i] == array[i+2]);
}

TEST_CASE("Vector's Iterator should delete all elements from beginning", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin();
    it.Delete(10);
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Vector's Iterator should delete maximum of all elements from beginning", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin();
    it.Delete(19);
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Vector's Iterator should delete element in the middle", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin()+3;
    it.Delete();
    REQUIRE(instance.Size() == 9);
    for(int i=0;i<3;i++)
        REQUIRE(instance[i] == array[i]);
    for(int i=3;i<9;i++)
        REQUIRE(instance[i] == array[i+1]);
}

TEST_CASE("Vector's Iterator should delete two elements in the middle", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin() + 3;
    it.Delete(2);
    REQUIRE(instance.Size() == 8);
    for(int i=0;i<3;i++)
        REQUIRE(instance[i] == array[i]);
    for(int i=3;i<8;i++)
        REQUIRE(instance[i] == array[i+2]);
}

TEST_CASE("Vector's Iterator should delete all elements after the middle position", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin()+4;
    it.Delete(6);
    REQUIRE(instance.Size() == 4);
    for(int i=0;i<4;i++)
        REQUIRE(instance[i] == array[i]);
}

TEST_CASE("Vector's Iterator should delete maximum of all elements from the middle", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin() + 3;
    it.Delete(19);
    REQUIRE(instance.Size() == 3);
    for(int i=0;i<3;i++)
        REQUIRE(instance[i] == array[i]);
}

TEST_CASE("Vector's Iterator shouldnt delete element in the end", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.End();
    it.Delete();
    REQUIRE(instance.Size() == 10);
    for(int i=0;i<10;i++)
        REQUIRE(instance[i] == array[i]);
}
