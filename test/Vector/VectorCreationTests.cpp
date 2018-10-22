#define CATCH_CONFIG_MAIN
#define ___OUT_OF_MEMORY_TESTING
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9};

TEST_CASE("Should create empty Vector", "[Vector][Creation]") {
    Vector<int>::_SetAllocationLimit(~0U);
    Vector<int> instance;
    REQUIRE(instance.IsEmpty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create Vector with capacity", "[Vector][Creation]"){
    Vector<int>::_SetAllocationLimit(~0U);
    Vector<int> instance(4);
    REQUIRE(instance.IsEmpty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create Vector with more capacity", "[Vector][Creation]"){
    Vector<int>::_SetAllocationLimit(~0U);
    Vector<int> instance(25);
    REQUIRE(instance.IsEmpty());
    REQUIRE(instance.Size() == 0);
}


TEST_CASE("Should create Vector with no capacity if zero capacity passed", "[Vector][Creation]"){
    Vector<int>::_SetAllocationLimit(~0U);
    Vector<int> instance(0);
    REQUIRE(instance.IsEmpty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create Vector with huge capacity", "[Vector][Creation]"){
    Vector<int>::_SetAllocationLimit(~0U);
    Vector<int> instance(1584);
    REQUIRE(instance.IsEmpty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create Vector with default values", "[Vector][Creation]"){
    Vector<int>::_SetAllocationLimit(~0U);
    Vector<int> instance(array, 5);
    REQUIRE(!instance.IsEmpty());
    REQUIRE(instance.Size() == 5);
    for (int a = 0; a < 5; a++)
        REQUIRE(instance[a] == array[a]);
    Vector<int>::Iterator b = instance.Begin();
    Vector<int>::Iterator e = instance.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
}

TEST_CASE("Should create Vector from another Vector by copy", "[Vector][Creation]"){
    Vector<int>::_SetAllocationLimit(~0U);
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
    Vector<int>::_SetAllocationLimit(~0U);
    Vector<int> instance(array, 5);
    Vector<int> second(move(instance));
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.IsEmpty());
    REQUIRE(second.Size() == 5);
    REQUIRE(!second.IsEmpty());

    for (int a = 0; a < 5; a++)
        REQUIRE(second[a] == array[a]);

    Vector<int>::Iterator b = second.Begin();
    Vector<int>::Iterator e = second.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
}

static int T1CallsToException;
class T1
{
private:
    int* _var;
public:
    T1() : _var(new int(0))
    {}
    T1(const T1 &x){
        T1CallsToException--;
        if(T1CallsToException==0)
            throw 0;
        _var = new int(0);
    }
    ~T1(){
        delete _var;
    }
};
TEST_CASE("Vector should stay valid even after exception", "[Vector][Creation]"){
    Vector<int>::_SetAllocationLimit(~0U);
    T1 array[5];
    T1CallsToException=8;

    Vector<T1> instance(array, 5);
    try
    {
        Vector<T1> second(instance);
        REQUIRE(false);
    }
    catch(...)
    {
        REQUIRE(true);
    }
    REQUIRE(instance.Size() == 5);
}

TEST_CASE("Vector no memory leaks if exception occurs in the constructor", "[Vector][Creation]"){
    Vector<int>::_SetAllocationLimit(~0U);
    T1 array[5];
    T1CallsToException=3;

    try
    {
        Vector<T1> instance(array, 5);
        REQUIRE(false);
    }
    catch(...)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Creation of Vector with out of memory faills without memory leaks", "[Vector][Creation]"){
    Vector<int>::_SetAllocationLimit(10);
    try
    {
        Vector<int> instance(20);
        REQUIRE(false);
    }
    catch(...)
    {
        REQUIRE(true);
    }
}
