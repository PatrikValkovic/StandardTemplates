#ifndef TEMPLATES_CONDQUEUETESTS_H
#define TEMPLATES_CONDQUEUETESTS_H

#ifndef _STALIB_
#include <assert.h>
#endif

#include "../src/CondQueue.h"

static bool MyValidation(const int* const x)
{
    return *x < 5;
}

static bool ReturnsTrue(const int* const x)
{
    return true;
}

class CondQueueTests
{
private:
    CondQueueTests()
    { }

    void Creating()
    {
        using namespace Templates;
        CondQueue<int>* Instance;
        int val =0;
        int list[] = {2,6,3,1,8,7};

        Instance = new CondQueue<int>(MyValidation,list,6); //{2,3,1};
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val) && val == 2);
        assert(Instance->Pop(val) && val == 3);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new CondQueue<int>(MyValidation);
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;
    }

    void PushingTests()
    {
        using namespace Templates;
        CondQueue<int>* Instance;
        int val =0;
        int list[] = {2,6,3,1,8,7};
        int listFirst[] = {1,4,2,3};
        int listBad[] = {8,12,7,6};
        int listBeginBad[] = {8,3,2,4,4};

        Instance = new CondQueue<int>(MyValidation,list,3);//{2,3}
        assert(!Instance->Push(9));
        assert(Instance->Push(4));//{2,3,4}
        assert(Instance->Push(list+3,2));//{2,3,4,1}
        assert(Instance->Pop(val) && val==2);
        assert(Instance->Pop(val) && val==3);
        assert(Instance->Pop(val) && val==4);
        assert(Instance->Pop(val) && val==1);
        assert(!Instance->Pop(val));
        assert(Instance->IsEmpty());
        delete Instance;

        Instance = new CondQueue<int>(ReturnsTrue,listFirst,4); //{1,4,2,3}
        Instance->SetCallback(MyValidation);
        assert(Instance->ValidateQueue()==0); //{1,4,2,3} remove nothing
        assert(Instance->Pop(val) && val==1);
        assert(Instance->Pop(val) && val==4);
        assert(Instance->Pop(val) && val==2);
        assert(Instance->Pop(val) && val==3);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new CondQueue<int>(ReturnsTrue,listBad,4);
        Instance->SetCallback(MyValidation);
        assert(Instance->ValidateQueue()==4);
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new CondQueue<int>(ReturnsTrue,listBeginBad,5); //{8,3,2,4,4}
        Instance->SetCallback(MyValidation); //{3,2,4,4}
        assert(Instance->ValidateQueue()==1);
        assert(Instance->Pop(val) && val==3);
        assert(Instance->Pop(val) && val==2);
        assert(Instance->Pop(val) && val==4);
        assert(Instance->Pop(val) && val==4);
        assert(!Instance->Pop(val));
        assert(Instance->IsEmpty());
        delete Instance;
    }

public:
    static void test()
    {
        CondQueueTests test;
        test.Creating();
        test.PushingTests();
    }
};

#endif //TEMPLATES_CONDQUEUETESTS_H
