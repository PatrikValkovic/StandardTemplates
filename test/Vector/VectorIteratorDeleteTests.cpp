#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

TEST_CASE("Vector's Iterator should delete element after the first element", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin();
    it.Delete();
    REQUIRE(instance.Size() == 9);
    REQUIRE(instance[0] == array[0]);
    for(int i=1;i<9;i++)
        REQUIRE(instance[i] == array[i+1]);
}

TEST_CASE("Vector's Iterator should delete two elements after the first element", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin();
    it.Delete(2);
    REQUIRE(instance.Size() == 8);
    REQUIRE(instance[0] == array[0]);
    for(int i=1;i<8;i++)
        REQUIRE(instance[i] == array[i+2]);
}

TEST_CASE("Vector's Iterator should delete all elements after the first element", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin();
    it.Delete(9);
    REQUIRE(instance.Size() == 1);
    REQUIRE(instance[0] == array[0]);
}

TEST_CASE("Vector's Iterator should delete maximum of all elements after the first element", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin();
    it.Delete(19);
    REQUIRE(instance.Size() == 1);
    REQUIRE(instance[0] == array[0]);
}

TEST_CASE("Vector's Iterator should delete element in the middle", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin()+3;
    it.Delete();
    REQUIRE(instance.Size() == 9);
    for(int i=0;i<4;i++)
        REQUIRE(instance[i] == array[i]);
    for(int i=4;i<9;i++)
        REQUIRE(instance[i] == array[i+1]);
}

TEST_CASE("Vector's Iterator should delete two elements in the middle", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin() + 3;
    it.Delete(2);
    REQUIRE(instance.Size() == 8);
    for(int i=0;i<4;i++)
        REQUIRE(instance[i] == array[i]);
    for(int i=4;i<8;i++)
        REQUIRE(instance[i] == array[i+2]);
}

TEST_CASE("Vector's Iterator should delete all elements after the middle position", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin()+3;
    it.Delete(6);
    REQUIRE(instance.Size() == 4);
    for(int i=0;i<4;i++)
        REQUIRE(instance[i] == array[i]);
}

TEST_CASE("Vector's Iterator should delete maximum of all elements from the middle", "[Vector][Iterator][Delete]") {
    Vector<int> instance(array, 10);
    Vector<int>::Iterator it = instance.Begin() + 3;
    it.Delete(19);
    REQUIRE(instance.Size() == 4);
    for(int i=0;i<4;i++)
        REQUIRE(instance[i] == array[i]);
}

static bool SHOULD_THROW = false;
class MyClass
{
public:
    ~MyClass() noexcept(false) {
        if(SHOULD_THROW)
            throw 0;
    }
};
TEST_CASE("Vector's Iterator should delete element even in the case of exception", "[Vector][Iterator][Delete]") {
    SHOULD_THROW = false;
    MyClass arr[10];
    Vector<MyClass> instance(arr, 10);
    Vector<MyClass>::Iterator it = instance.Begin() + 3;
    SHOULD_THROW = true;
    try
    {
        it.Delete();
        REQUIRE(false);
    }
    catch(...)
    {}
    SHOULD_THROW = false;
    REQUIRE(instance.Size() == 9);
}
