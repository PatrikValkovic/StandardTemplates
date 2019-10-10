#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9};

TEST_CASE("Should create empty Array", "[Array][Creation]") {
    Array<int> instance;
    REQUIRE(instance.Capacity() == 0);
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.Empty());
}

TEST_CASE("Should create Array with capacity", "[Array][Creation]"){
    Array<int> instance(4);
    REQUIRE(instance.Capacity() == 4);
    REQUIRE(instance.Empty());
}

TEST_CASE("Should create Array with more capacity", "[Array][Creation]"){
    Array<int> instance(25);
    REQUIRE(instance.Capacity() == 25);
}

TEST_CASE("Should create Array with default capacity if zero capacity passed", "[Array][Creation]"){
    Array<int> instance(0);
    REQUIRE(instance.Capacity() == 0);
}

TEST_CASE("Should create Array with huge capacity", "[Array][Creation]"){
    Array<int> instance(1584);
    REQUIRE(instance.Capacity() == 1584);
}

TEST_CASE("Should create Array with default values", "[Array][Creation]"){
    Array<int> instance(array, 5);
    REQUIRE(instance.Capacity() >= 5);
    REQUIRE(!instance.Empty());
    REQUIRE(instance.Size() == 5);
    for (int a = 0; a < 5; a++)
        REQUIRE(instance[a] == array[a]);
}

TEST_CASE("Should create Array from another Array by copy", "[Array][Creation]"){
    Array<int> instance(array, 5);
    Array<int> second(instance);
    REQUIRE(instance.Size() == 5);
    REQUIRE(second.Size() == 5);
    REQUIRE(instance.Capacity() >= 5);
    REQUIRE(second.Capacity() >= 5);
    for (int a = 0; a < 5; a++)
        REQUIRE(instance[a] == array[a]);
    for (int a = 0; a < 5; a++)
        REQUIRE(second[a] == array[a]);
}

TEST_CASE("Should create Array from another Array by move", "[Array][Creation]"){
    Array<int> instance(array, 5);
    Array<int> second(move(instance));
    REQUIRE(instance.Size() == 0);
    REQUIRE(second.Size() == 5);
    REQUIRE(instance.Capacity() >= 0);
    REQUIRE(second.Capacity() >= 5);
    for (int a = 0; a < 5; a++)
        REQUIRE(second[a] == array[a]);
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
TEST_CASE("Array should stay valid even after exception", "[Array][Creation]"){
    T1 array[5];
    T1CallsToException=8;

    Array<T1> instance(array, 5);
    try
    {
        Array<T1> second(instance);
    }
    catch(...)
    {}
    REQUIRE(instance.Size() == 5);
    REQUIRE(instance.Capacity() >= 5);
}

TEST_CASE("Array no memory leaks if exception occurs in the constructor", "[Array][Creation]"){
    T1 array[5];
    T1CallsToException=3;

    try
    {
        Array<T1> instance(array, 5);
    }
    catch(...)
    {}
}
