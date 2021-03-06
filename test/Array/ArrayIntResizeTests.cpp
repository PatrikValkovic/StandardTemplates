#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;

int OriginalArray[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

TEST_CASE("Array of ints should resize to bigger value", "[Array][Resize]")
{
    Array<int> instance(OriginalArray, 10);
    int capacity = instance.Capacity();
    instance.Resize(capacity + 10);
    REQUIRE(instance.Capacity() == capacity + 10);
}

TEST_CASE("Array of ints should resize to the same value", "[Array][Resize]")
{
    Array<int> instance(OriginalArray, 10);
    int capacity = instance.Capacity();
    instance.Resize(capacity);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of ints should resize to the size", "[Array][Resize]")
{
    Array<int> instance(OriginalArray, 10);
    int size = instance.Size();
    instance.Resize(size);
    REQUIRE(instance.Capacity() == size);
}

TEST_CASE("Array of ints should resize to the value lower then the size", "[Array][Resize]")
{
    Array<int> instance(OriginalArray, 10);
    instance.Resize(5);
    REQUIRE(instance.Capacity() == 5);
}



TEST_CASE("Array of ints should resize by positive value", "[Array][Resize]")
{
    Array<int> instance(OriginalArray, 10);
    int capacity = instance.Capacity();
    instance.ResizeBy(10);
    REQUIRE(instance.Capacity() == capacity + 10);
}

TEST_CASE("Array of ints should resize by zero", "[Array][Resize]")
{
    Array<int> instance(OriginalArray, 10);
    int capacity = instance.Capacity();
    instance.ResizeBy(0);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of ints should resize by negative value still in the place where are no elements", "[Array][Resize]")
{
    Array<int> instance(OriginalArray, 10);
    int capacity = instance.Capacity();
    instance.ResizeBy(10);
    instance.ResizeBy(-9);
    REQUIRE(instance.Capacity() == capacity + 1);
}

TEST_CASE("Array of ints should resize by negative value to match the array size", "[Array][Resize]")
{
    Array<int> instance(OriginalArray, 10);
    int size = instance.Size();
    instance.ResizeBy(10);
    instance.ResizeBy(instance.Size() - instance.Capacity());
    REQUIRE(instance.Capacity() == size);
}

TEST_CASE("Array of ints should resize by negative value and delete some of elements", "[Array][Resize]")
{
    Array<int> instance(OriginalArray, 10);
    int size = instance.Size();
    instance.ResizeBy(10);
    instance.ResizeBy(instance.Size() - instance.Capacity() - 2);
    REQUIRE(instance.Capacity() == size - 2);
    REQUIRE(instance.Size() == size - 2);
}

TEST_CASE("Array of ints should shrink to fit", "[Array][Resize][ShrinkToFit]")
{
    Array<int> instance(OriginalArray, 10);
    int size = instance.Size();
    instance.ResizeBy(10);
    instance.ShrinkToFit();
    REQUIRE(instance.Capacity() == size);
    REQUIRE(instance.Size() == size);
}

TEST_CASE("Array of ints should not resize to negative value", "[Array][Resize]")
{
    Array<int> instance(OriginalArray, 10);
    try    {
       instance.Resize(-5);
       REQUIRE(false);
    }
    catch(OutOfRangeException&){
        REQUIRE(true);
    }
    catch(...){
        REQUIRE(false);
    }
}
