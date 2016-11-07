#ifndef TEMPLATES_BINOMIALMINHEAP_H
#define TEMPLATES_BINOMIALMINHEAP_H

#ifdef ADDITIONAL_TESTS
#include <iostream>
using namespace std;
#endif

#include "List.h"
#include "BinomialTree.h"

namespace Templates
{
    //return -1, if first is lower
    //return 0, if are equal
    //return 1, if is second lower
    //int(*comp)(const T& first, const T& second)
    template<typename T, int(* comp)(const T& first, const T& second)>
    class BinomialHeap
    {
    private:
        List <BinomialTree<T, comp>> Trees;

        void ValidateList()
        {
            typename List<BinomialTree<T, comp>>::Iterator cur = this->Trees.Begin();
            typename List<BinomialTree<T, comp>>::Iterator next = cur;
            typename List<BinomialTree<T, comp>>::Iterator sib = cur;

            for (next.Next(), sib.Next(2);
                 next.IsValidIterator();
                 cur.Next(), next.Next(), sib.Next())
            {
                if ((cur.GetValue()->Level() == next.GetValue()->Level() &&
                     !sib.IsValidIterator()) ||
                    (cur.GetValue()->Level() == next.GetValue()->Level() &&
                     next.GetValue()->Level() != sib.GetValue()->Level()))
                {
                    cur.GetValue()->Merge(*next.GetValue());
                    next.DeleteThis();
                    next = cur;
                    sib = cur;
                    next.Next();
                    next.Next(2);
                }
            }
            return;
        }

    public:
        bool Push(T val)
        {
            BinomialTree<T, comp> x(val);
            bool success = Trees.Begin().InsertBefore(x) == 1;
            if (success)
                ValidateList();
            return success;
        }

        bool Pop(T& val)
        {
            if (this->Trees.IsEmpty())
                return false;

            //find lower
            typename List<BinomialTree<T, comp>>::Iterator moving = this->Trees.Begin();
            typename List<BinomialTree<T, comp>>::Iterator lower = moving;
            for (; moving.IsValidIterator(); moving.Next())
            {
                int res = comp(lower.GetValue()->Top(), moving.GetValue()->Top());
                if (res > 0)
                    lower = moving;
            }
            //delete it from vector
            BinomialTree<T, comp> lowest = *lower.GetValue();
            lower.DeleteThis();
            //create new heap
            BinomialHeap h;
            h.Trees = lowest.InnerTrees();
            this->Merge(h);
            //return val
            val = lowest.Top();
            return true;
        }

        void Merge(BinomialHeap& Second)
        {
            typename List<BinomialTree<T, comp>>::Iterator movingThis = this->Trees.Begin();
            typename List<BinomialTree<T, comp>>::Iterator movingSecond = Second.Trees.Begin();
            List<BinomialTree<T, comp>> res;
            typename List<BinomialTree<T, comp>>::Iterator inserting = res.End();
            while (movingThis.IsValidIterator() && movingSecond.IsValidIterator())
            {
                if (movingThis.GetValue()->Level() < movingSecond.GetValue()->Level())
                {
                    inserting.InsertBefore(*movingThis.GetValue());
                    movingThis.Next();
                }
                else
                {
                    inserting.InsertBefore(*movingSecond.GetValue());
                    movingSecond.Next();
                }
            }
            for (; movingThis.IsValidIterator(); movingThis.Next())
                inserting.InsertBefore(*movingThis.GetValue());
            for (; movingSecond.IsValidIterator(); movingSecond.Next())
                inserting.InsertBefore(*movingSecond.GetValue());

            this->Trees = res;
            ValidateList();
        }
    };

}

#endif //TEMPLATES_BINOMIALMINHEAP_H
