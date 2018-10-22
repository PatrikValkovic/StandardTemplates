#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#define private public
#include "../../Templates.h"
using namespace Templates;

int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

TEST_CASE("Vector should push one value", "[Vector][Push]"){
    Vector<int> instance(OriginalArray, 15);
    instance.Push(31);
    REQUIRE(instance.Size()==16);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    REQUIRE(instance[15] == 31);
}

TEST_CASE("Vector should resize based on the input size if big array is pushed", "[Vector][Push]"){
    Vector<int> instance(OriginalArray, 2);
    instance.Push(OriginalArray+2, 13);
    REQUIRE(instance.Size()==15);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
}


static int COUNTER = 0;
static int SHOULD_THROW = ~0;
class T1
{
    int* value;
public:
    T1() : value(new int(COUNTER++)) {}
    T1(const T1& s) {
        if(--SHOULD_THROW == 0)
            throw 0;
        value = new int(*s.value);
    }
    ~T1(){
        delete value;
    }
    bool operator==(const T1& s) const {
        return *value == *(s.value);
    }
};
TEST_CASE("Vector should be valid after inserting one element with exception", "[Vector][Push]"){
    SHOULD_THROW = ~0;
    T1* arr = new T1[15];
    Vector<T1> instance(arr, 15);
    SHOULD_THROW = 1;
    try
    {
        instance.Push(arr[0]);
        REQUIRE(false);
    }
    catch(...)
    {}
    SHOULD_THROW = ~0;

    REQUIRE(instance.Size()==15);

    delete [] arr;
}


TEST_CASE("Vector should push values from array", "[Vector][Push]"){
    Vector<int> instance(OriginalArray, 15);
    instance.Push(OriginalArray, 10);
    REQUIRE(instance.Size()==25);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for(int i=0;i<10;i++)
        REQUIRE(instance[i+15] == OriginalArray[i]);
}

TEST_CASE("Vector should push whole second array", "[Vector][Push]"){
    Vector<int> instance(OriginalArray, 15);
    instance.Push(OriginalArray, 15);
    REQUIRE(instance.Size()==30);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i+15] == OriginalArray[i]);
}

TEST_CASE("Vector should not push values from array if exception occurs", "[Vector][Push]"){
    SHOULD_THROW = ~0;
    T1* arr = new T1[15];
    Vector<T1> instance(arr, 15);
    SHOULD_THROW = 5;
    try
    {
        instance.Push(arr, 10);
        REQUIRE(false);
    }
    catch(...)
    {}
    SHOULD_THROW = ~0;
    REQUIRE(instance.Size() >= 15);
    for(int i=0;i<15;i++)
        REQUIRE((instance[i] == arr[i]));

    delete [] arr;
}

TEST_CASE("Vector should not push values from array if exception occurs in the last insertion", "[Vector][Push]"){
    SHOULD_THROW = ~0;
    T1* arr = new T1[15];
    Vector<T1> instance(arr, 15);
    SHOULD_THROW = 15;
    try
    {
        instance.Push(arr, 15);
        REQUIRE(false);
    }
    catch(...)
    {}
    SHOULD_THROW = ~0;
    REQUIRE(instance.Size() >= 15);
    for(int i=0;i<15;i++)
        REQUIRE((instance[i] == arr[i]));

    delete [] arr;
}
