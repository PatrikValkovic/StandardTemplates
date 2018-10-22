#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
int SecondArray[5] = {90, 91, 92, 93, 94};

TEST_CASE("Vector should insert one element", "[Vector][Insert]")
{
    Vector<int> instance(OriginalArray, 15);
    instance.Insert(100);
    REQUIRE(instance.Size() == 16);
    REQUIRE(instance[0] == 100);
    for (int i = 1; i < 16; i++)
        REQUIRE(instance[i] == OriginalArray[i-1]);
}

TEST_CASE("Vector should insert five elements", "[Vector][Insert]")
{
    Vector<int> instance(OriginalArray, 15);
    instance.Insert(SecondArray, 5);
    REQUIRE(instance.Size() == 20);
    for (int i = 0; i < 5; i++)
        REQUIRE(instance[i] == SecondArray[i]);
    for (int i = 5; i < 20; i++)
        REQUIRE(instance[i] == OriginalArray[i - 5]);
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

TEST_CASE("Vector should not insert values from array if exception occurs", "[Vector][Insert]"){
    SHOULD_THROW = ~0;
    T1* arr = new T1[15];
    T1* arr2 = new T1[10];
    Vector<T1> instance(arr, 15);
    SHOULD_THROW = 7;
    try
    {
        instance.Insert(arr2, 10);
        REQUIRE(false);
    }
    catch(...)
    {}
    SHOULD_THROW = ~0;
    REQUIRE(instance.Size() == 15);
    for(int i=0;i<15;i++)
        REQUIRE((instance[i] == arr[i]));
    instance.Push(arr, 10);
    REQUIRE(instance.Size() == 25);

    delete [] arr;
    delete [] arr2;
}

