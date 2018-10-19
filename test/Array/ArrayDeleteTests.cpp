#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

TEST_CASE("Array should delete all elements by default", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.Delete();
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.IsEmpty());
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array should not delete elements if negative value passed", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.Delete(-1);
    REQUIRE(instance.Size() == 15);
    REQUIRE(!instance.IsEmpty());
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array should delete all elements if number=size", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.Delete(15);
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.IsEmpty());
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array should delete 5 elements", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.Delete(5);
    REQUIRE(instance.Size() == 10);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array should delete all elements if higher value passed", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.Delete(25);
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.Capacity() == capacity);
}



TEST_CASE("Array should not delete elements if negative value passed to DeleteFromBegin", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.DeleteFromBegin(-1);
    REQUIRE(instance.Size() == 15);
    REQUIRE(!instance.IsEmpty());
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array should delete all elements from the beginning if number=size", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.DeleteFromBegin(15);
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.IsEmpty());
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array should delete 5 elements from begin", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.DeleteFromBegin(5);
    REQUIRE(instance.Size() == 10);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array should delete all elements if higher value passed to DeleteFromBegin", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.DeleteFromBegin(25);
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.Capacity() == capacity);
}





TEST_CASE("Array should not delete elements if negative value passed to DeleteFromEnd", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.DeleteFromEnd(-1);
    REQUIRE(instance.Size() == 15);
    REQUIRE(!instance.IsEmpty());
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array should delete all elements from the end if number=size", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.DeleteFromEnd(15);
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.IsEmpty());
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array should delete 5 elements from end", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.DeleteFromEnd(5);
    REQUIRE(instance.Size() == 10);
    REQUIRE(instance.Capacity() == capacity);
}

TEST_CASE("Array should delete all elements if higher value passed to DeleteFromEnd", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.DeleteFromEnd(25);
    REQUIRE(instance.Size() == 0);
    REQUIRE(instance.Capacity() == capacity);
}




TEST_CASE("Array should delete some elements in the middle", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.Delete(5, 5);
    REQUIRE(instance.Size() == 10);
    REQUIRE(instance.Capacity() == capacity);
    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
    for(int i=5;i<10;i++)
        REQUIRE(instance[i] == OriginalArray[i+5]);
}

TEST_CASE("Array should not delete some elements in the middle if negative count passed", "[Array][Delete]") {
    Array<int> instance(OriginalArray, 15);
    int capacity = instance.Capacity();
    instance.Delete(5, -5);
    REQUIRE(instance.Size() == 15);
    REQUIRE(instance.Capacity() == capacity);
    for(int i=0;i<15;i++)
        REQUIRE(instance[i] == OriginalArray[i]);
}


