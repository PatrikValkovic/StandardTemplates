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

const T1 OriginalArray[15];
const T1 SecondArray[3];


TEST_CASE("Array of custom type should remain same if inserted in the middle with safe", "[Array][SpliceSafe]") {
    T1CallsToException = ~0;
    Array<T1> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    int size = instance.Size();

    try{
        T1CallsToException = 1;
        instance.SpliceSafe(10, 0, SecondArray, 1);
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    REQUIRE(instance.Size() == size);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of custom type should remain same if inserted in the end with safe", "[Array][SpliceSafe]") {
    T1CallsToException = ~0;
    Array<T1> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    int size = instance.Size();

    try{
        T1CallsToException = 1;
        instance.SpliceSafe(size, 0, SecondArray, 1);
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    REQUIRE(instance.Size() == size);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of custom type should remain same if inserted in the beginning with safe", "[Array][SpliceSafe]") {
    T1CallsToException = ~0;
    Array<T1> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    int size = instance.Size();

    try{
        T1CallsToException = 1;
        instance.SpliceSafe(0, 0, SecondArray, 1);
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    REQUIRE(instance.Size() == size);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of custom type should remain same if inserted multiple in the middle with safe", "[Array][SpliceSafe]") {
    T1CallsToException = ~0;
    Array<T1> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    int size = instance.Size();

    try{
        T1CallsToException = 2;
        instance.SpliceSafe(10, 0, SecondArray, 3);
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    REQUIRE(instance.Size() == size);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of custom type should remain same if inserted multiple in the end with safe", "[Array][SpliceSafe]") {
    T1CallsToException = ~0;
    Array<T1> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    int size = instance.Size();

    try{
        T1CallsToException = 2;
        instance.SpliceSafe(size, 0, SecondArray, 3);
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    REQUIRE(instance.Size() == size);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of custom type should remain same if inserted multiple in the beginning with safe", "[Array][SpliceSafe]") {
    T1CallsToException = ~0;
    Array<T1> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    int size = instance.Size();

    try{
        T1CallsToException = 2;
        instance.SpliceSafe(0, 0, SecondArray, 3);
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    REQUIRE(instance.Size() == size);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of custom type should remain same if deleted and inserted multiple in the middle with safe", "[Array][SpliceSafe]") {
    T1CallsToException = ~0;
    Array<T1> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    int size = instance.Size();

    try{
        T1CallsToException = 2;
        instance.SpliceSafe(10, 2, SecondArray, 3);
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    REQUIRE(instance.Size() == size);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of custom type should remain same if deleted and inserted multiple in the end with safe", "[Array][SpliceSafe]") {
    T1CallsToException = ~0;
    Array<T1> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    int size = instance.Size();

    try{
        T1CallsToException = 2;
        instance.SpliceSafe(size, 2, SecondArray, 3);
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    REQUIRE(instance.Size() == size);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of custom type should remain same if deleted and inserted multiple before end with safe", "[Array][SpliceSafe]") {
    T1CallsToException = ~0;
    Array<T1> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    int size = instance.Size();

    try{
        T1CallsToException = 2;
        instance.SpliceSafe(size-2, 2, SecondArray, 3);
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    REQUIRE(instance.Size() == size);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of custom type should remain same if deleted and inserted multiple in the beginning with safe", "[Array][SpliceSafe]") {
    T1CallsToException = ~0;
    Array<T1> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    int size = instance.Size();

    try{
        T1CallsToException = 2;
        instance.SpliceSafe(0, 2, SecondArray, 3);
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    REQUIRE(instance.Size() == size);
    REQUIRE(instance.Capacity() == capacity);
}
