#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9};

TEST_CASE("Should copy array", "[Array][Assignment]") {
    Array<int> instance(array, 5);
    Array<int> second(10);
    second = instance;
    REQUIRE(instance.Size() == 5);
    REQUIRE(second.Size() == 5);
    REQUIRE(instance.Capacity() >= 5);
    REQUIRE(second.Capacity() >= 5);

    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == array[i]);
    for(int i=0;i<5;i++)
        REQUIRE(second[i] == array[i]);

    for(int i=0;i<5;i++)
        second[i]=i;

    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == array[i]);
    for(int i=0;i<5;i++)
        REQUIRE(second[i] == i);
}

TEST_CASE("Should move array by assignment operator", "[Array][Assignment]") {
    Array<int> instance(array, 5);
    Array<int> second(10);
    second = move(instance);
    REQUIRE(instance.Size() == 0);
    REQUIRE(second.Size() == 5);
    REQUIRE(instance.Capacity() >= 0);
    REQUIRE(second.Capacity() >= 5);

    for(int i=0;i<5;i++)
        REQUIRE(second[i] == array[i]);
}

TEST_CASE("Should copy even empty array", "[Array][Assignment]"){
    Array<int> instance1;
    Array<int> instance2;
    instance2 = instance1;

    REQUIRE(instance1.Capacity() >= 0);
    REQUIRE(instance2.Capacity() >= 0);
}

TEST_CASE("Should move even empty array", "[Array][Assignment]"){
    Array<int> instance1;
    Array<int> instance2;
    instance2 = move(instance1);

    REQUIRE(instance1.Capacity() >= 0);
    REQUIRE(instance2.Capacity() >= 0);
}

TEST_CASE("Array calling copy on self have not affect", "[Array][Assignment]"){
    Array<int> instance1;
    instance1 = instance1;
    REQUIRE(instance1.Capacity() >= 0);
}

TEST_CASE("Array calling move assignment on self have not affect", "[Array][Assignment]"){
    Array<int> instance1;
    instance1 = move(instance1);
    REQUIRE(instance1.Capacity() >= 0);
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
TEST_CASE("Array should stay valid even after exception in copy assignment", "[Array][Assignment]"){
    T1 array[5];
    T1CallsToException=8;

    Array<T1> instance1(array, 5);
    Array<T1> instance2(10);
    try
    {
        instance2 = instance1;
    }
    catch(...)
    {}
    REQUIRE(instance1.Size() == 5);
    REQUIRE(instance1.Capacity() >= 5);
    REQUIRE(instance2.Size() == 0);
    REQUIRE(instance2.Capacity() >= 0);
}

