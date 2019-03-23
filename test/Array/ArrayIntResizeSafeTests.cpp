#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;

int OriginalArray[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

TEST_CASE("Array of ints should resize to bigger value", "[Array][ResizeSafe]")
{
    Array<int> instance(OriginalArray, 10);
    int capacity = instance.Capacity();
    instance.ResizeSafe(capacity + 10);
    REQUIRE(instance.Capacity() == capacity + 10);
}

TEST_CASE("Array of ints should resize to the same value", "[Array][ResizeSafe]")
{
    Array<int> instance(OriginalArray, 10);
    int capacity = instance.Capacity();
    instance.ResizeSafe(capacity);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of ints should resize to the size", "[Array][ResizeSafe]")
{
    Array<int> instance(OriginalArray, 10);
    int size = instance.Size();
    instance.ResizeSafe(size);
    REQUIRE(instance.Capacity() == size);
}

TEST_CASE("Array of ints should resize to the value lower then the size", "[Array][ResizeSafe]")
{
    Array<int> instance(OriginalArray, 10);
    instance.Resize(5);
    REQUIRE(instance.Capacity() == 5);
}



TEST_CASE("Array of ints should resize by positive value", "[Array][ResizeSafe]")
{
    Array<int> instance(OriginalArray, 10);
    int capacity = instance.Capacity();
    instance.ResizeBySafe(10);
    REQUIRE(instance.Capacity() == capacity + 10);
}

TEST_CASE("Array of ints should resize by zero", "[Array][ResizeSafe]")
{
    Array<int> instance(OriginalArray, 10);
    int capacity = instance.Capacity();
    instance.ResizeBySafe(0);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array of ints should resize by negative value still in the place where are no elements", "[Array][ResizeSafe]")
{
    Array<int> instance(OriginalArray, 10);
    int capacity = instance.Capacity();
    instance.ResizeBySafe(10);
    instance.ResizeBySafe(-9);
    REQUIRE(instance.Capacity() == capacity + 1);
}

TEST_CASE("Array of ints should resize by negative value to match the array size", "[Array][ResizeSafe]")
{
    Array<int> instance(OriginalArray, 10);
    int size = instance.Size();
    instance.ResizeBySafe(10);
    instance.ResizeBySafe(instance.Size() - instance.Capacity());
    REQUIRE(instance.Capacity() == size);
}

TEST_CASE("Array of ints should resize by negative value and delete some of elements", "[Array][ResizeSafe]")
{
    Array<int> instance(OriginalArray, 10);
    int size = instance.Size();
    instance.ResizeBySafe(10);
    instance.ResizeBySafe(instance.Size() - instance.Capacity() - 2);
    REQUIRE(instance.Capacity() == size - 2);
    REQUIRE(instance.Size() == size - 2);
}

TEST_CASE("Array of ints should shrink to fit", "[Array][ResizeSafe][ShrinkToFitSafe]")
{
    Array<int> instance(OriginalArray, 10);
    int size = instance.Size();
    instance.ResizeBySafe(10);
    instance.ShrinkToFitSafe();
    REQUIRE(instance.Capacity() == size);
    REQUIRE(instance.Size() == size);
}

TEST_CASE("Array of ints should not resize to negative value", "[Array][ResizeSafe]")
{
    Array<int> instance(OriginalArray, 10);
    try    {
       instance.ResizeSafe(-5);
       REQUIRE(false);
    }
    catch(OutOfRangeException&){
        REQUIRE(true);
    }
    catch(...){
        REQUIRE(false);
    }
}
