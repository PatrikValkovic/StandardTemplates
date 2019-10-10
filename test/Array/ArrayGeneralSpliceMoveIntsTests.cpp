#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;

class MyWrapper
{
public:
    int value;

    MyWrapper() : value(-1)
    {}

    MyWrapper(int x) : value(x)
    {}

    MyWrapper(const MyWrapper&) = delete;

    MyWrapper(MyWrapper&& w)
    {
        value = w.value;
        w.value = -1;
    }

    bool operator==(const MyWrapper& s)
    {
        return value == s.value;
    }
};

using MW = MyWrapper;

//region deleting

TEST_CASE("Array of ints should delete one value in the middle with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(10, 1, (MW*&&) nullptr, 0);

    REQUIRE(instance.Size() == 14);
    REQUIRE(instance.Capacity() == capacity);

    for (int a = 0; a < 10; a++)
        REQUIRE((CP[a] == instance[a]));
    for (int a = 11; a < 15; a++)
        REQUIRE((instance[a - 1] == CP[a]));
}

TEST_CASE("Array of ints should delete one value in the beginning with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(0, 1, (MW*&&) nullptr, 0);

    REQUIRE(instance.Size() == 14);
    REQUIRE(instance.Capacity() == capacity);

    for (int a = 1; a < 15; a++)
        REQUIRE((instance[a - 1] == CP[a]));
}

TEST_CASE("Array of ints should delete one value in the end with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(instance.Size() - 1, 1, (MW*&&) nullptr, 0);

    REQUIRE(instance.Size() == 14);
    REQUIRE(instance.Capacity() == capacity);

    for (int a = 0; a < 14; a++)
        REQUIRE((instance[a] == CP[a]));
}


TEST_CASE("Array of ints should delete three values in the middle with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(10, 3, (MW*&&) nullptr, 0);

    REQUIRE(instance.Size() == 12);
    REQUIRE(instance.Capacity() == capacity);

    for (int a = 0; a < 10; a++)
        REQUIRE((CP[a] == instance[a]));
    for (int a = 13; a < 15; a++)
        REQUIRE((instance[a - 3] == CP[a]));
}

TEST_CASE("Array of ints should delete three values in the beginning with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(0, 3, (MW*&&) nullptr, 0);

    REQUIRE(instance.Size() == 12);
    REQUIRE(instance.Capacity() == capacity);

    for (int a = 3; a < 15; a++)
        REQUIRE((instance[a - 3] == CP[a]));
}

TEST_CASE("Array of ints should delete three values in the end with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(instance.Size() - 3, 3, (MW*&&) nullptr, 0);

    REQUIRE(instance.Size() == 12);
    REQUIRE(instance.Capacity() == capacity);

    for (int a = 0; a < 12; a++)
        REQUIRE((instance[a] == CP[a]));
}

//endregion

//region inserting

TEST_CASE("Array of ints should insert one value in the middle with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW more[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};


    Array<MW> instance(OriginalArray, 15);

    instance.Splice(10, 0, move(more), 1);

    REQUIRE(instance.Size() == 16);
    REQUIRE(instance.Capacity() >= 16);

    for (int a = 0; a < 10; a++)
        REQUIRE((CP[a] == instance[a]));
    REQUIRE((instance[10] == CP[0]));
    for (int a = 11; a < 16; a++)
        REQUIRE((instance[a] == CP[a - 1]));
}

TEST_CASE("Array of ints should insert one value in the beginning with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW more[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(0, 0, move(more), 1);

    REQUIRE(instance.Size() == 16);
    REQUIRE(instance.Capacity() >= 16);

    REQUIRE((instance[0] == CP[0]));
    for (int a = 1; a < 16; a++)
        REQUIRE((instance[a] == CP[a - 1]));
}

TEST_CASE("Array of ints should insert one value in the end with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW more[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(instance.Size(), 0, move(more), 1);

    REQUIRE(instance.Size() == 16);
    REQUIRE(instance.Capacity() >= 16);

    for (int a = 0; a < 15; a++)
        REQUIRE((instance[a] == CP[a]));
    REQUIRE((instance[15] == CP[0]));
}

TEST_CASE("Array of ints should insert one value before the end with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW more[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(instance.Size() - 1, 0, move(more), 1);

    REQUIRE(instance.Size() == 16);
    REQUIRE(instance.Capacity() >= 16);

    for (int a = 0; a < 14; a++)
        REQUIRE((instance[a] == CP[a]));
    REQUIRE((instance[14] == CP[0]));
    REQUIRE((instance[15] == CP[14]));
}


TEST_CASE("Array of ints should insert three values in the middle with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(10, 0, move(SecondArray), 3);

    REQUIRE(instance.Size() == 18);
    REQUIRE(instance.Capacity() >= 18);

    for (int a = 0; a < 10; a++)
        REQUIRE((CP[a] == instance[a]));
    for (int a = 10; a < 13; a++)
        REQUIRE((CP2[a - 10] == instance[a]));
    for (int a = 13; a < 18; a++)
        REQUIRE((instance[a] == CP[a - 3]));
}

TEST_CASE("Array of ints should insert three values in the beginning with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(0, 0, move(SecondArray), 3);

    REQUIRE(instance.Size() == 18);
    REQUIRE(instance.Capacity() >= 18);

    for (int a = 0; a < 3; a++)
        REQUIRE((instance[a] == CP2[a]));
    for (int a = 3; a < 18; a++)
        REQUIRE((instance[a] == CP[a - 3]));
}

TEST_CASE("Array of ints should insert three values in the end with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(instance.Size(), 0, move(SecondArray), 3);

    REQUIRE(instance.Size() == 18);
    REQUIRE(instance.Capacity() >= 18);

    for (int a = 0; a < 15; a++)
        REQUIRE((instance[a] == CP[a]));
    for (int a = 15; a < 18; a++)
        REQUIRE((instance[a] == CP2[a - 15]));
}

TEST_CASE("Array of ints should insert three values before the end with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(instance.Size() - 1, 0, move(SecondArray), 3);

    REQUIRE(instance.Size() == 18);
    REQUIRE(instance.Capacity() >= 18);

    for (int a = 0; a < 14; a++)
        REQUIRE((instance[a] == CP[a]));
    for (int a = 14; a < 17; a++)
        REQUIRE((instance[a] == CP2[a - 14]));
    REQUIRE((instance[17] == CP[14]));
}

//endregion

//region delete one insert one
TEST_CASE("Array of ints should delete one value and insert one value in the middle with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW more[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};


    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(10, 1, move(more), 1);

    REQUIRE(instance.Size() == 15);
    REQUIRE(instance.Capacity() == capacity);

    for (int a = 0; a < 10; a++)
        REQUIRE((CP[a] == instance[a]));
    REQUIRE((instance[10] == CP[0]));
    for (int a = 11; a < 15; a++)
        REQUIRE((instance[a] == CP[a]));
}

TEST_CASE("Array of ints should delete one value and insert one value in the beginning with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(0, 1, move(SecondArray), 1);

    REQUIRE(instance.Size() == 15);
    REQUIRE(instance.Capacity() == capacity);

    REQUIRE((instance[0] == CP2[0]));
    for (int a = 1; a < 15; a++)
        REQUIRE((instance[a] == CP[a]));
}

TEST_CASE("Array of ints should delete one value and insert one value in the end with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(instance.Size(), 1, move(SecondArray), 1);

    REQUIRE(instance.Size() == 16);
    REQUIRE(instance.Capacity() >= 16);

    for (int a = 0; a < 15; a++)
        REQUIRE((instance[a] == CP[a]));
    REQUIRE((instance[15] == CP2[0]));
}

TEST_CASE("Array of ints should delete one value and insert one value before the end with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(instance.Size() - 1, 1, move(SecondArray), 1);

    REQUIRE(instance.Size() == 15);
    REQUIRE(instance.Capacity() == capacity);

    for (int a = 0; a < 14; a++)
        REQUIRE((instance[a] == CP[a]));
    REQUIRE((instance[14] == CP2[0]));
}
//endregion

//region delete one insert three
TEST_CASE("Array of ints should delete one value and insert three values in the middle with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(10, 1, move(SecondArray), 3);

    REQUIRE(instance.Size() == 17);
    REQUIRE(instance.Capacity() >= 17);

    for (int a = 0; a < 10; a++)
        REQUIRE((instance[a] == CP[a]));
    for (int a = 10; a < 13; a++)
        REQUIRE((instance[a] == CP2[a - 10]));
    for (int a = 13; a < 17; a++)
        REQUIRE((instance[a] == CP[a - 2]));
}

TEST_CASE("Array of ints should delete one value and insert three values in the beginning with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(0, 1, move(SecondArray), 3);

    REQUIRE(instance.Size() == 17);
    REQUIRE(instance.Capacity() >= 17);

    for (int i = 0; i < 3; i++)
        REQUIRE((instance[i] == CP2[i]));
    for (int a = 3; a < 17; a++)
        REQUIRE((instance[a] == CP[a - 2]));
}

TEST_CASE("Array of ints should delete one value and insert three values in the end with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(instance.Size(), 1, move(SecondArray), 3);

    REQUIRE(instance.Size() == 18);
    REQUIRE(instance.Capacity() >= 18);

    for (int a = 0; a < 15; a++)
        REQUIRE((instance[a] == CP[a]));
    for (int a = 15; a < 18; a++)
        REQUIRE((instance[a] == CP2[a - 15]));
}

TEST_CASE("Array of ints should delete one value and insert three values before the end with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(instance.Size() - 1, 1, move(SecondArray), 3);

    REQUIRE(instance.Size() == 17);
    REQUIRE(instance.Capacity() >= 17);

    for (int a = 0; a < 14; a++)
        REQUIRE((instance[a] == CP[a]));
    for (int a = 14; a < 17; a++)
        REQUIRE((instance[a] == CP2[a - 14]));
}
//endregion

//region delete three insert one
TEST_CASE("Array of ints should delete three value and insert one value in the middle with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(10, 3, move(SecondArray), 1);

    REQUIRE(instance.Size() == 13);
    REQUIRE(instance.Capacity() == capacity);

    for (int a = 0; a < 10; a++)
        REQUIRE((instance[a] == CP[a]));
    for (int a = 10; a < 11; a++)
        REQUIRE((instance[a] == CP2[a - 10]));
    for (int a = 11; a < 13; a++)
        REQUIRE((instance[a] == CP[a + 2]));
}

TEST_CASE("Array of ints should delete three values and insert one value in the beginning with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(0, 3, move(SecondArray), 1);

    REQUIRE(instance.Size() == 13);
    REQUIRE(instance.Capacity() == capacity);

    for (int i = 0; i < 1; i++)
        REQUIRE((instance[i] == CP2[i]));
    for (int a = 1; a < 13; a++)
        REQUIRE((instance[a] == CP[a + 2]));
}

TEST_CASE("Array of ints should delete three values and insert one value in the end with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(instance.Size(), 3, move(SecondArray), 1);

    REQUIRE(instance.Size() == 16);
    REQUIRE(instance.Capacity() >= 16);

    for (int a = 0; a < 15; a++)
        REQUIRE((instance[a] == CP[a]));
    for (int a = 15; a < 16; a++)
        REQUIRE((instance[a] == CP2[a - 15]));
}

TEST_CASE("Array of ints should delete three values and insert one value before the end with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(instance.Size() - 3, 3, move(SecondArray), 1);

    REQUIRE(instance.Size() == 13);
    REQUIRE(instance.Capacity() == capacity);

    for (int a = 0; a < 12; a++)
        REQUIRE((instance[a] == CP[a]));
    for (int a = 12; a < 13; a++)
        REQUIRE((instance[a] == CP2[a - 12]));
}
//endregion

//region delete four insert three
TEST_CASE("Array of ints should delete four value and insert three values in the middle with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(10, 4, move(SecondArray), 3);

    REQUIRE(instance.Size() == 14);
    REQUIRE(instance.Capacity() == capacity);

    for (int a = 0; a < 10; a++)
        REQUIRE((instance[a] == CP[a]));
    for (int a = 10; a < 13; a++)
        REQUIRE((instance[a] == CP2[a - 10]));
    for (int a = 13; a < 14; a++)
        REQUIRE((instance[a] == CP[a + 1]));
}

TEST_CASE("Array of ints should delete four values and insert three values in the beginning with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(0, 4, move(SecondArray), 3);

    REQUIRE(instance.Size() == 14);
    REQUIRE(instance.Capacity() == capacity);

    for (int i = 0; i < 3; i++)
        REQUIRE((instance[i] == CP2[i]));
    for (int a = 3; a < 14; a++)
        REQUIRE((instance[a] == CP[a + 1]));
}

TEST_CASE("Array of ints should delete four values and insert three values in the end with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);

    instance.Splice(instance.Size(), 4, move(SecondArray), 3);

    REQUIRE(instance.Size() == 18);
    REQUIRE(instance.Capacity() >= 18);

    for (int a = 0; a < 15; a++)
        REQUIRE((instance[a] == CP[a]));
    for (int a = 15; a < 18; a++)
        REQUIRE((instance[a] == CP2[a - 15]));
}

TEST_CASE("Array of ints should delete four values and insert three values before the end with move semantic",
          "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW CP[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    MW SecondArray[3] = {97, 98, 99};
    MW CP2[3] = {97, 98, 99};

    Array<MW> instance(OriginalArray, 15);
    int capacity = (int) instance.Capacity();

    instance.Splice(instance.Size() - 4, 4, move(SecondArray), 3);

    REQUIRE(instance.Size() == 14);
    REQUIRE(instance.Capacity() == capacity);

    for (int a = 0; a < 11; a++)
        REQUIRE((instance[a] == CP[a]));
    for (int a = 11; a < 14; a++)
        REQUIRE((instance[a] == CP2[a - 11]));
}
//endregion


TEST_CASE("Splice with negative index should throw a exception with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

    Array<MW> instance(OriginalArray, 15);
    try
    {
        instance.Splice(-2, 3, (MW*&&) nullptr, 0);
        REQUIRE(false);
    }
    catch (OutOfRangeException&)
    {
        REQUIRE(true);
    }
}

TEST_CASE("Splice with big index should throw a exception with move semantic", "[Array][Splice]")
{
    MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};


    Array<MW> instance(OriginalArray, 15);
    try
    {
        instance.Splice(20, 3, (MW*&&) nullptr, 0);
        REQUIRE(false);
    }
    catch (OutOfRangeException&)
    {
        REQUIRE(true);
    }
}
