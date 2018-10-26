#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9};
int second[] = {90, 91, 92, 93, 94};

TEST_CASE("Vector's Iterator should insert element after the first element", "[Vector][Iterator][Insert]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator it = instance.Begin();
    it.Insert(10);
    REQUIRE(instance.Size() == 6);
    REQUIRE(instance[0] == array[0]);
    REQUIRE(instance[1] == 10);
    for(int i=2;i<6;i++)
        REQUIRE(instance[i] == array[i-1]);
}

TEST_CASE("Vector's Iterator should insert elements after the first element", "[Vector][Iterator][Insert]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator it = instance.Begin();
    it.Insert(second, 5);
    REQUIRE(instance.Size() == 10);
    REQUIRE(instance[0] == array[0]);
    for(int i=1;i<6;i++)
        REQUIRE(instance[i] == second[i-1]);
    for(int i=6;i<10;i++)
        REQUIRE(instance[i] == array[i-5]);
}

TEST_CASE("Vector's Iterator should insert element in the middle", "[Vector][Iterator][Insert]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator it = instance.Begin() + 2;
    it.Insert(10);
    REQUIRE(instance.Size() == 6);
    for(int i=0;i<3;i++)
        REQUIRE(instance[i] == array[i]);
    REQUIRE(instance[3] == 10);
    for(int i=4;i<6;i++)
        REQUIRE(instance[i] == array[i-1]);
}

TEST_CASE("Vector's Iterator should insert elements in the middle", "[Vector][Iterator][Insert]") {
    Vector<int> instance(array, 5);
    Vector<int>::Iterator it = instance.Begin() + 2;
    it.Insert(second, 5);
    REQUIRE(instance.Size() == 10);
    for(int i=0;i<3;i++)
        REQUIRE(instance[i] == array[i]);
    for(int i=3;i<8;i++)
        REQUIRE(instance[i] == second[i-3]);
    for(int i=8;i<10;i++)
        REQUIRE(instance[i] == array[i-5]);
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
TEST_CASE("Vector's Iterator should not insert element if exception occurs", "[Vector][Iterator][Insert]") {
    SHOULD_THROW = ~0;
    T1 arr[5];
    Vector<T1> instance(arr, 5);
    Vector<T1>::Iterator it = instance.Begin();
    SHOULD_THROW = 1;
    try
    {
        it.Insert(arr[0]);
        REQUIRE(false);
    }
    catch(...)
    {}
    REQUIRE(instance.Size() == 5);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == arr[i]);
}

TEST_CASE("Vector's Iterator should not insert element in the middle if exception occurs", "[Vector][Iterator][Insert]") {
    SHOULD_THROW = ~0;
    T1 arr[5];
    Vector<T1> instance(arr, 5);
    Vector<T1>::Iterator it = instance.Begin() + 2;
    SHOULD_THROW = 1;
    try
    {
        it.Insert(arr[0]);
        REQUIRE(false);
    }
    catch(...)
    {}
    REQUIRE(instance.Size() == 5);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == arr[i]);
}
