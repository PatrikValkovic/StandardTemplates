#define CATCH_CONFIG_MAIN
#include <assert.h>
#include "../libs/catch.h"
#include "../Templates.h"

class PriorityQueueTests
{
private:
    static int Valid(const int* const First, const int* const Second)
    {
        return *First - *Second;
    }

    void Base()
    {
        using namespace Templates;
        PriorityQueue<int>* Queue;
        int val;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(5));
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(5));
        assert(Queue->Push(1));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(1));
        assert(Queue->Push(5));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(5));
        assert(Queue->Push(1));
        assert(Queue->Push(3));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(1));
        assert(Queue->Push(3));
        assert(Queue->Push(5));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(5));
        assert(Queue->Push(3));
        assert(Queue->Push(1));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(1));
        assert(Queue->Push(5));
        assert(Queue->Push(3));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(3));
        assert(Queue->Push(5));
        assert(Queue->Push(1));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(3));
        assert(Queue->Push(1));
        assert(Queue->Push(5));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;
    }

    void SortingTest()
    {
        using namespace Templates;
        PriorityQueue<int>* Queue;
        int val;
        int list[] = {25, 12, 36, 52, 14, 98, 52, 36, 54, 74, 32};

        Queue = new PriorityQueue<int>(Valid);
        for (int a = 0; a < 11; a++)
            Queue->Push(list[a]);

        //98,74,54,52,52,36,36,32,25,14,12
        assert(Queue->Pop(val) && val == 12);
        assert(Queue->Pop(val) && val == 14);
        assert(Queue->Pop(val) && val == 25);
        assert(Queue->Pop(val) && val == 32);
        assert(Queue->Pop(val) && val == 36);
        assert(Queue->Pop(val) && val == 36);
        assert(Queue->Pop(val) && val == 52);
        assert(Queue->Pop(val) && val == 52);
        assert(Queue->Pop(val) && val == 54);
        assert(Queue->Pop(val) && val == 74);
        assert(Queue->Pop(val) && val == 98);
        assert(!Queue->Pop(val));
        delete Queue;
        return;
    };

    void LaterInserting()
    {
        using namespace Templates;
        PriorityQueue<int>* Queue;
        int val;
        int list[] = {25, 12, 36, 52, 14, 98, 52, 36, 54, 74, 32};

        Queue = new PriorityQueue<int>(Valid);
        for (int a = 0; a < 11; a++)
            Queue->Push(list[a]);

        //98,74,54,52,52,36,36,32,25,14,12
        assert(Queue->Pop(val) && val == 12);
        assert(Queue->Pop(val) && val == 14);
        assert(Queue->Pop(val) && val == 25);
        assert(Queue->Pop(val) && val == 32);
        assert(Queue->Pop(val) && val == 36);
        assert(Queue->Pop(val) && val == 36);
        //98,74,54,52,52
        for(int a=4;a<8;a++)
            assert(Queue->Push(list[a]));
        // 14, 98, 52, 36 + 98,74,54,52,52
        // 14, 36, 52, 52, 52, 54, 74, 98, 98
        assert(Queue->Pop(val) && val == 14);
        assert(Queue->Pop(val) && val == 36);
        assert(Queue->Pop(val) && val == 52);
        assert(Queue->Pop(val) && val == 52);
        assert(Queue->Pop(val) && val == 52);
        assert(Queue->Pop(val) && val == 54);
        assert(Queue->Pop(val) && val == 74);
        assert(Queue->Pop(val) && val == 98);
        assert(Queue->Pop(val) && val == 98);
        assert(!Queue->Pop(val));
        delete Queue;
    }

public:
    static void test()
    {
        PriorityQueueTests test;
        test.SortingTest();
        test.LaterInserting();
        test.Base();
    }
};

TEST_CASE("Priority queue tests"){
    PriorityQueueTests::test();
}