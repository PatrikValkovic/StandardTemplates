#define CATCH_CONFIG_MAIN
#include <assert.h>
#include "../libs/catch.h"
#include "../Templates.h"

using namespace Templates;

class BinaryHeapTests
{
private:

    static int Sorting(const int* const First, const int* const Second)
    {
        return *First-*Second;
    }

    static void demo()
    {
        BinaryHeap<int>* Instance = new BinaryHeap<int>(Sorting);
        int val;
        for(int a=0;a<10;a++)
            Instance->Insert(a);
        for(int a=0;a<10;a++)
        {
            assert(Instance->Pop(val));
            assert(val == a);
        }
        delete Instance;
    }
public:
    static void tests()
    {
        demo();
    }
};

TEST_CASE("Binary heap tests"){
    BinaryHeapTests::tests();
}