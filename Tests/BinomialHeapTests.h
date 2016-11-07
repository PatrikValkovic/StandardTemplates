#ifndef TEMPLATES_BINOMIALHEAP_H
#define TEMPLATES_BINOMIALHEAP_H

#include "../BinomialHeap.h"

class BinomialHeapTests
{
private:
    static int comp(const int& f, const int& s)
    {
        return f - s;
    }

    static void Base()
    {
        using namespace Templates;
        BinomialHeap<int,comp>* Queue;
        int val;

        Queue = new BinomialHeap<int,comp>;
        assert(Queue->Push(5));
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new BinomialHeap<int,comp>;
        assert(Queue->Push(5));
        assert(Queue->Push(1));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new BinomialHeap<int,comp>;
        assert(Queue->Push(1));
        assert(Queue->Push(5));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new BinomialHeap<int,comp>;
        assert(Queue->Push(5));
        assert(Queue->Push(1));
        assert(Queue->Push(3));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new BinomialHeap<int,comp>;
        assert(Queue->Push(1));
        assert(Queue->Push(3));
        assert(Queue->Push(5));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new BinomialHeap<int,comp>;
        assert(Queue->Push(5));
        assert(Queue->Push(3));
        assert(Queue->Push(1));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new BinomialHeap<int,comp>;
        assert(Queue->Push(1));
        assert(Queue->Push(5));
        assert(Queue->Push(3));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new BinomialHeap<int,comp>;
        assert(Queue->Push(3));
        assert(Queue->Push(5));
        assert(Queue->Push(1));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new BinomialHeap<int,comp>;
        assert(Queue->Push(3));
        assert(Queue->Push(1));
        assert(Queue->Push(5));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;
    }

    static void SortingTest()
    {
        using namespace Templates;
        BinomialHeap<int,comp>* Queue;
        int val;
        int list[] = {25, 12, 36, 52, 14, 98, 52, 36, 54, 74, 32};

        Queue = new BinomialHeap<int, comp>;
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

    static void LaterInserting()
    {
        using namespace Templates;
        BinomialHeap<int,comp>* Queue;
        int val;
        int list[] = {25, 12, 36, 52, 14, 98, 52, 36, 54, 74, 32};

        Queue = new BinomialHeap<int,comp>();
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

    static void EightNumbers()
    {
        /**
         *                  -8
         *                 / |
         *                /| |
         *               / | |
         *              1  4 10
         *             /|  |
         *            / |  |
         *           3  9  21
         *           |
         *           5
         */
        BinomialHeap<int, comp> heap;
        heap.Push(5);
        heap.Push(3);
        heap.Push(9);
        heap.Push(1);
        heap.Push(-8);
        heap.Push(10);
        heap.Push(4);
        heap.Push(21);
        int val;
        assert(heap.Pop(val));
        assert(val == -8);
        assert(heap.Pop(val));
        assert(val == 1);
        assert(heap.Pop(val));
        assert(val == 3);
        assert(heap.Pop(val));
        assert(val == 4);
        assert(heap.Pop(val));
        assert(val == 5);
        assert(heap.Pop(val));
        assert(val == 9);
        assert(heap.Pop(val));
        assert(val == 10);
        assert(heap.Pop(val));
        assert(val == 21);
        assert(!heap.Pop(val));
    }

    static void FourNumbers()
    {
        /**
         *            1
         *           /|
         *          3  9
         *          |
         *          5
         */
        BinomialHeap<int, comp> heap;
        heap.Push(5);
        heap.Push(3);
        heap.Push(9);
        heap.Push(1);
        int val;
        assert(heap.Pop(val));
        assert(val == 1);
        assert(heap.Pop(val));
        assert(val == 3);
        assert(heap.Pop(val));
        assert(val == 5);
        assert(heap.Pop(val));
        assert(val == 9);
        assert(!heap.Pop(val));
    }

    static void TwoNumbers()
    {
        /**
         *      3
         *      |
         *      5
         */
        BinomialHeap<int, comp> heap;
        heap.Push(5);
        heap.Push(3);
        int val;
        assert(heap.Pop(val));
        assert(val == 3);
        assert(heap.Pop(val));
        assert(val == 5);
        assert(!heap.Pop(val));
    }
public:
    static void tests()
    {
        TwoNumbers();

        FourNumbers();

        EightNumbers();

        Base();

        SortingTest();

        LaterInserting();
    }
};

#endif //TEMPLATES_BINOMIALHEAP_H
