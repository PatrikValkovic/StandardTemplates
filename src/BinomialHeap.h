#ifndef TEMPLATES_BINOMIALMINHEAP_H
#define TEMPLATES_BINOMIALMINHEAP_H

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

            for (next.Next(), sib.Next(2); next != this->Trees.End();)
            {
                if ((cur->Level() == next->Level() &&
                     sib == this->Trees.End()) ||
                    (cur->Level() == next->Level() &&
                     next->Level() != sib->Level()))
                {
                    cur->Merge(*next);
                    next.DeleteThis();
                    next = cur;
                    sib = cur;
                    next.Next();
                    sib.Next(2);
                }
                else
                {
                    cur.Next();
                    next.Next();
                    sib.Next();
                }
            }
            return;
        }

    public:
        bool Push(T val)
        {
            BinomialTree<T, comp> x(val);
            Trees.Insert(x);
            ValidateList();
            return true;
        }

        bool Pop(T& val)
        {
            if (this->Trees.IsEmpty())
                return false;

            //find lower
            typename List<BinomialTree<T, comp>>::Iterator moving = this->Trees.Begin();
            typename List<BinomialTree<T, comp>>::Iterator lower = moving;
            for (; moving != this->Trees.End(); moving.Next())
            {
                int res = comp(lower->Top(), moving->Top());
                if (res > 0)
                    lower = moving;
            }
            //delete it from vector
            BinomialTree<T, comp> lowest = *lower;
            lower.DeleteThis();
            //create new heap
            BinomialHeap h;
            h.Trees = lowest.InnerTrees();
            this->Merge(h);
            //return val
            val = lowest.Top();
            return true;
        }

        bool Top(T& val)
        {
            if (this->Trees.IsEmpty())
                return false;

            //find lower
            typename List<BinomialTree<T, comp>>::Iterator moving = this->Trees.Begin();
            typename List<BinomialTree<T, comp>>::Iterator lower = moving;
            for (; moving.IsValidIterator(); moving.Next())
            {
                int res = comp(lower->Top(), moving->Top());
                if (res > 0)
                    lower = moving;
            }
            val = lower->Top();
            return true;
        }

        void Merge(BinomialHeap& Second)
        {
            typename List<BinomialTree<T, comp>>::Iterator movingThis = this->Trees.Begin();
            typename List<BinomialTree<T, comp>>::Iterator movingSecond = Second.Trees.Begin();
            List<BinomialTree<T, comp>> res;
            typename List<BinomialTree<T, comp>>::Iterator inserting = res.End();
            while (movingThis != this->Trees.End() && movingSecond != Second.Trees.End())
            {
                if (movingThis->Level() < movingSecond->Level())
                {
                    inserting.InsertBefore(*movingThis);
                    movingThis.Next();
                }
                else
                {
                    inserting.InsertBefore(*movingSecond);
                    movingSecond.Next();
                }
            }
            for (; movingThis != this->Trees.End(); movingThis.Next())
                inserting.InsertBefore(*movingThis);
            for (; movingSecond != Second.Trees.End(); movingSecond.Next())
                inserting.InsertBefore(*movingSecond);

            this->Trees = res;
            ValidateList();
        }
    };

}

#endif //TEMPLATES_BINOMIALMINHEAP_H
