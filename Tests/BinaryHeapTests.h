#ifndef TEMPLATES_BINARYHEAPTESTS_H
#define TEMPLATES_BINARYHEAPTESTS_H

#include "../BinaryMinHeap.h"

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
        BinaryMinHeap<int>* Instance = new BinaryMinHeap<int>(Sorting);
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
#endif //TEMPLATES_BINARYHEAPTESTS_H
