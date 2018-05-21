#define CATCH_CONFIG_MAIN
#include <assert.h>
#include "../libs/catch.h"
#include "../Templates.h"

bool FindSix(const int* const Val, void* data)
{
    return *Val==6;
}

bool FindTwelve(const int* const Val, void* data)
{
    return *Val==12;
}

bool FindValue(const int* const Val, void* data)
{
    return *Val==*((int*)data);
}
class AlgorithmsTests
{
private:
    AlgorithmsTests()
    { }

    void FindTest()
    {
        using namespace Templates;
        Vector<int>* Instance;
        Vector<int>::Iterator Iter;
        int list[] = {1,6,8,4,2,3,5,7};

        Instance = new Vector<int>(list,8);
        Iter = Instance->Begin();
        assert(!Find(&Iter,FindTwelve));
        Iter = Instance->Begin();
        assert(Find(&Iter,FindSix));
        assert(*Iter.GetValue()==6);
        delete Instance;

        Instance = new Vector<int>(list,8);
        Iter = Instance->Begin();
        int val = 5;
        assert(Find(&Iter,FindValue,&val));
        assert(*Iter.GetValue()==5);
        val = 24;
        assert(!Find(&Iter,FindValue,&val));
        delete Instance;
    }
public:
    static void test()
    {
        AlgorithmsTests tests;
        tests.FindTest();
    }
};

TEST_CASE("Algorithm tests"){
    AlgorithmsTests::test();
}