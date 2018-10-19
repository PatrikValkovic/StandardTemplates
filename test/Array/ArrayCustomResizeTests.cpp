#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;

static int T1CallsToException = ~0;
class T1
{
public:
    int* _var;
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

TEST_CASE("Array of custom type should resize to bigger value", "[Array][Resize]")
{
    T1* arr = new T1[10];
    T1CallsToException = ~0;

    Array<T1> instance(arr, 10);
    int capacity = instance.Capacity();

    instance.Resize(capacity + 10);
    REQUIRE(instance.Capacity() == capacity + 10);

    delete [] arr;
}

TEST_CASE("Array of custom type should resize to the same value", "[Array][Resize]")
{
    T1* arr = new T1[10];
    T1CallsToException = ~0;

    Array<T1> instance(arr, 10);
    int capacity = instance.Capacity();

    instance.Resize(capacity);
    REQUIRE(instance.Capacity() == capacity);

    delete [] arr;
}

TEST_CASE("Array of custom type should resize to the size", "[Array][Resize]")
{
    T1* arr = new T1[10];
    T1CallsToException = ~0;

    Array<T1> instance(arr, 10);
    int size = instance.Size();

    instance.Resize(size);
    REQUIRE(instance.Capacity() == size);

    delete [] arr;
}

TEST_CASE("Array of custom type should resize to the value lower then the size", "[Array][Resize]")
{
    T1* arr = new T1[10];
    T1CallsToException = ~0;

    Array<T1> instance(arr, 10);

    instance.Resize(5);
    REQUIRE(instance.Capacity() == 5);

    delete [] arr;
}

TEST_CASE("Array of custom type should resize to the value lower then the size and should be thread safe", "[Array][Resize]")
{
    T1* arr = new T1[10];
    T1CallsToException = ~0;

    Array<T1> instance(arr, 10);
    int capacity = instance.Capacity();
    int size = instance.Size();

    T1CallsToException = 3;
    try{
        instance.Resize(5);
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    REQUIRE(instance.Capacity() == capacity);
    REQUIRE(instance.Size() == size);

    for(int i=0;i<10;i++)
        REQUIRE(*(instance[i]._var) == *(arr[i]._var));

    delete [] arr;
}


TEST_CASE("Array of custom type should resize by positive value", "[Array][Resize]")
{
    T1* arr = new T1[10];
    T1CallsToException = ~0;

    Array<T1> instance(arr, 10);
    int capacity = instance.Capacity();

    instance.ResizeBy(10);
    REQUIRE(instance.Capacity() == capacity + 10);

    delete [] arr;
}

TEST_CASE("Array of custom type should resize by zero", "[Array][Resize]")
{
    T1* arr = new T1[10];
    T1CallsToException = ~0;

    Array<T1> instance(arr, 10);
    int capacity = instance.Capacity();

    instance.ResizeBy(0);
    REQUIRE(instance.Capacity() == capacity);

    delete [] arr;
}

TEST_CASE("Array of custom type should resize by negative value still in the place where are no elements", "[Array][Resize]")
{
    T1* arr = new T1[10];
    T1CallsToException = ~0;

    Array<T1> instance(arr, 10);
    int capacity = instance.Capacity();

    instance.ResizeBy(10);
    instance.ResizeBy(-9);
    REQUIRE(instance.Capacity() == capacity + 1);

    delete [] arr;
}

TEST_CASE("Array of custom type should resize by negative value to match the array size", "[Array][Resize]")
{
    T1* arr = new T1[10];
    T1CallsToException = ~0;

    Array<T1> instance(arr, 10);
    int size = instance.Size();

    instance.ResizeBy(10);
    instance.ResizeBy(instance.Size() - instance.Capacity());
    REQUIRE(instance.Capacity() == size);

    delete [] arr;
}

TEST_CASE("Array of custom type should resize by negative value and delete some of elements", "[Array][Resize]")
{
    T1* arr = new T1[10];
    T1CallsToException = ~0;

    Array<T1> instance(arr, 10);
    int size = instance.Size();

    instance.ResizeBy(10);
    instance.ResizeBy(instance.Size() - instance.Capacity() - 2);
    REQUIRE(instance.Capacity() == size - 2);
    REQUIRE(instance.Size() == size - 2);

    delete [] arr;
}

TEST_CASE("Array of custom type should resize by negative and is thread safe", "[Array][Resize]")
{
    T1* arr = new T1[10];
    T1CallsToException = ~0;

    Array<T1> instance(arr, 10);
    instance.ResizeBy(10);
    int size = instance.Size();
    int capacity = instance.Capacity();

    T1CallsToException = 2;
    try{
        instance.ResizeBy(instance.Size() - instance.Capacity() - 2);
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    REQUIRE(instance.Capacity() == capacity);
    REQUIRE(instance.Size() == size);

    for(int i=0;i<10;i++)
        REQUIRE(*(instance[i]._var) == *(arr[i]._var));

    delete [] arr;
}

TEST_CASE("Array of ints should shrink to fit", "[Array][Resize][ShrinkToFit]")
{
    T1* arr = new T1[10];
    T1CallsToException = ~0;

    Array<T1> instance(arr, 10);
    int size = instance.Size();

    instance.ShrinkToFit();
    instance.ResizeBy(instance.Size() - instance.Capacity());
    REQUIRE(instance.Capacity() == size);
    REQUIRE(instance.Size() == size);

    delete [] arr;
}
