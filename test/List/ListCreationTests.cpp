#define CATCH_CONFIG_MAIN
#define ___OUT_OF_MEMORY_TESTING
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9};

TEST_CASE("Should create empty List", "[List][Creation]") {
    List<int>::_SetAllocationLimit(~0U);
    List<int> instance;
    REQUIRE(instance.IsEmpty());
    REQUIRE(instance.Size() == 0);
}

TEST_CASE("Should create List with some values", "[List][Creation]") {
    List<int>::_SetAllocationLimit(~0U);
    List<int> instance(array, 5);
    REQUIRE(!instance.IsEmpty());
    REQUIRE(instance.Size() == 5);
}


TEST_CASE("Should create List with default values", "[List][Creation]"){
    List<int>::_SetAllocationLimit(~0U);
    List<int> instance(array, 5);
    REQUIRE(!instance.IsEmpty());
    REQUIRE(instance.Size() == 5);
    for (int a = 0; a < 5; a++)
        REQUIRE(instance[a] == array[a]);
    List<int>::Iterator b = instance.Begin();
    List<int>::Iterator e = instance.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
}

TEST_CASE("Should create List from another List by copy", "[List][Creation]"){
    List<int>::_SetAllocationLimit(~0U);
    List<int> instance(array, 5);
    List<int> second(instance);
    REQUIRE(instance.Size() == 5);
    REQUIRE(second.Size() == 5);

    for (int a = 0; a < 5; a++)
        REQUIRE(instance[a] == array[a]);
    for (int a = 0; a < 5; a++)
        REQUIRE(second[a] == array[a]);

    List<int>::Iterator b = instance.Begin();
    List<int>::Iterator e = instance.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
    b = second.Begin();
    e = second.End();
    for (int a = 0; b != e; a++, b++)
        REQUIRE(*b == array[a]);
}

TEST_CASE("Should create List from another List by move", "[List][Creation]"){
    List<int>::_SetAllocationLimit(~0U);
    List<int> instance(array, 5);
    List<int> second(move(instance));
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.IsEmpty());
    REQUIRE(second.Size() == 5);
    REQUIRE(!second.IsEmpty());

    for (int a = 0; a < 5; a++)
        REQUIRE(second[a] == array[a]);

    List<int>::Iterator b = second.Begin();
    List<int>::Iterator e = second.End();
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
TEST_CASE("List should stay valid even after exception", "[List][Creation]"){
    List<int>::_SetAllocationLimit(~0U);
    T1 array[5];
    T1CallsToException=8;

    List<T1> instance(array, 5);
    try
    {
        List<T1> second(instance);
        REQUIRE(false);
    }
    catch(...)
    {
        REQUIRE(true);
    }
    REQUIRE(instance.Size() == 5);
}

TEST_CASE("List no memory leaks if exception occurs in the constructor", "[List][Creation]"){
    List<int>::_SetAllocationLimit(~0U);
    T1 array[5];
    T1CallsToException=3;

    try
    {
        List<T1> instance(array, 5);
        REQUIRE(false);
    }
    catch(...)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Creation of List with out of memory fails without memory leaks", "[List][Creation]"){
    List<int>::_SetAllocationLimit(4);
    try
    {
        List<int> instance(array, 5);
        REQUIRE(false);
    }
    catch(...)
    {
        REQUIRE(true);
    }
}
