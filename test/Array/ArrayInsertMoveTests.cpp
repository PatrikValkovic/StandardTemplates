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

    MyWrapper(const MyWrapper&) = default;

    MyWrapper(MyWrapper&& w)
    {
        value = w.value;
        w.value = -1;
    }

    bool operator==(const MyWrapper& s)
    {
        return value == s.value;
    }
    bool operator==(int v)
    {
        return value == v;
    }

    operator int() {
        return value;
    }
};

using MW = MyWrapper;

const MW OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};

TEST_CASE("Array should insert one element into middle", "[Array][Insert]")
{
    Array<MW> instance(OriginalArray, 15);
    MW tmp(100);
    instance.Insert(10, move(tmp));
    REQUIRE((tmp == -1));

    REQUIRE((instance.Size() == 16));
    for (int i = 0; i < 10; i++)
        REQUIRE((instance[i] == OriginalArray[i]));
    REQUIRE((instance[10] == 100));
    for (int i = 11; i < 16; i++)
        REQUIRE((instance[i] == OriginalArray[i - 1]));
}

TEST_CASE("Array should insert five elements into middle", "[Array][Insert]")
{
    MW SecondArray[5] = {90, 91, 92, 93, 94};
    MW CP2[5] = {90, 91, 92, 93, 94};

    Array<MW> instance(OriginalArray, 15);
    instance.Insert(10, move(SecondArray), 5);
    for(int i=0;i<5;i++)
        REQUIRE((SecondArray[i].value == -1));

    REQUIRE((instance.Size() == 20));
    for (int i = 0; i < 10; i++)
        REQUIRE((instance[i] == OriginalArray[i]));
    for (int i = 10; i < 15; i++)
        REQUIRE((instance[i] == CP2[i - 10]));
    for (int i = 15; i < 20; i++)
        REQUIRE((instance[i] == OriginalArray[i - 5]));
}

TEST_CASE("Array should insert one element in the beginning", "[Array][Insert]")
{
    Array<MW> instance(OriginalArray, 15);
    MW tmp(100);
    instance.Insert(0, move(tmp));
    REQUIRE((tmp == -1));

    REQUIRE((instance.Size() == 16));
    REQUIRE((instance[0] == 100));
    for (int i = 1; i < 16; i++)
        REQUIRE((instance[i] == OriginalArray[i - 1]));
}

TEST_CASE("Array should insert five elements in the beginning", "[Array][Insert]")
{
    MW SecondArray[5] = {90, 91, 92, 93, 94};
    MW CP2[5] = {90, 91, 92, 93, 94};

    Array<MW> instance(OriginalArray, 15);
    instance.Insert(0, move(SecondArray), 5);
    for(int i=0;i<5;i++)
        REQUIRE((SecondArray[i].value == -1));

    REQUIRE((instance.Size() == 20));
    for (int i = 0; i < 5; i++)
        REQUIRE((instance[i] == CP2[i]));
    for (int i = 5; i < 20; i++)
        REQUIRE((instance[i] == OriginalArray[i - 5]));
}

TEST_CASE("Array should insert one element in the end", "[Array][Insert]")
{
    Array<MW> instance(OriginalArray, 15);
    MW tmp(100);
    instance.Insert(15, move(tmp));
    REQUIRE((tmp == -1));

    REQUIRE((instance.Size() == 16));
    for (int i = 0; i < 15; i++)
        REQUIRE((instance[i] == OriginalArray[i]));
    REQUIRE((instance[15] == 100));
}

TEST_CASE("Array should insert five elements in the end", "[Array][Insert]")
{
    MW SecondArray[5] = {90, 91, 92, 93, 94};
    MW CP2[5] = {90, 91, 92, 93, 94};

    Array<MW> instance(OriginalArray, 15);
    instance.Insert(15, move(SecondArray), 5);
    for(int i=0;i<5;i++)
        REQUIRE((SecondArray[i].value == -1));

    REQUIRE((instance.Size() == 20));
    for (int i = 0; i < 15; i++)
        REQUIRE((instance[i] == OriginalArray[i]));
    for (int i = 15; i < 20; i++)
        REQUIRE((instance[i] == CP2[i - 15]));
}

TEST_CASE("Array should insert one element before the end", "[Array][Insert]")
{
    Array<MW> instance(OriginalArray, 15);
    MW tmp(100);
    instance.Insert(14, move(tmp));
    REQUIRE((tmp == -1));

    REQUIRE((instance.Size() == 16));
    for (int i = 0; i < 14; i++)
        REQUIRE((instance[i] == OriginalArray[i]));
    REQUIRE((instance[14] == 100));
    REQUIRE((instance[15] == OriginalArray[14]));
}

TEST_CASE("Array should insert five elements before the end", "[Array][Insert]")
{
    MW SecondArray[5] = {90, 91, 92, 93, 94};
    MW CP2[5] = {90, 91, 92, 93, 94};

    Array<MW> instance(OriginalArray, 15);
    instance.Insert(14, move(SecondArray), 5);
    for(int i=0;i<5;i++)
        REQUIRE((SecondArray[i].value == -1));
    
    REQUIRE((instance.Size() == 20));
    for (int i = 0; i < 14; i++)
        REQUIRE((instance[i] == OriginalArray[i]));
    for (int i = 14; i < 19; i++)
        REQUIRE((instance[i] == CP2[i - 14]));
    REQUIRE((instance[19] == OriginalArray[14]));
}
