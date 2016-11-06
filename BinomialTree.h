#ifndef TEMPLATES_BINOMIALTREE_H
#define TEMPLATES_BINOMIALTREE_H

#include "Exceptions.h"
#include "Vector.h"
#include "Queue.h"
#include "BinomialMinHeap.h"

namespace Templates
{
    //return -1, if first is lower
    //return 0, if are equal
    //return 1, if is second lower
    //bool(*comp)(const T& first, const T& second)

    template<typename T, int(* comp)(const T& first, const T& second), bool allowDuplicities = true>
    class BinomialTree
    {
    private:
        class Node
        {
        public:
            Node(T val) : val(val)
            {}

            T val;
            Vector<Node*> rest;
        };

        Node* top;

        BinomialTree() : top(NULL)
        {}

    public:
        BinomialTree(T val)
        {
            Node* created = new Node(val);
            this->top = created;
        }

        ~BinomialTree()
        {
            if (top == NULL)
                return;

            Queue<Node*> ToProcess;
            ToProcess.Push(top);
            Node* ToDelete;

            while (ToProcess.Pop(ToDelete))
            {
                typename Vector<Node*>::Iterator moving = ToDelete->rest.Begin();
                typename Vector<Node*>::Iterator end = ToDelete->rest.End();
                for (; !moving.AreEqual(end) && moving.Next();)
                    ToProcess.Push(*moving.GetValue());
                delete ToDelete;
            }
        }

        BinomialTree(T a, T b)
                : BinomialTree(a)
        {
            BinomialTree x(b);
            Merge(x);
        }

        BinomialTree(T a, T b, T c, T d)
                : BinomialTree(a, b)
        {
            BinomialTree x(c, d);
            Merge(x);
        }

        BinomialTree(T a, T b, T c, T d, T e, T f, T g, T h)
                : BinomialTree(a, b, c, d)
        {
            BinomialTree x(e, f, g, h);
            Merge(x);
        }

        BinomialTree(const BinomialTree& second)
            : BinomialTree()
        {
            *this = second;
        }

        BinomialTree& operator=(const BinomialTree& Second)
        {
            if(this==&Second)
                return *this;

            //TODO

            return *this;
        }

        void Merge(BinomialTree& second)
        {
            if (this->top->rest.Size() != second.top->rest.Size())
                throw new InvalidArgumentException("Level of trees are not same", __LINE__);

            int accomp = comp(top->val, second.top->val);
            if (accomp < 0)
            {
                top->rest.Insert(second.top);
                second.top = NULL;
            }
            else if((accomp==0 && allowDuplicities) || accomp > 0)
            {
                second.top->rest.Insert(top);
                this->top = second.top;
                second.top = NULL;
            }
        }

        Vector<BinomialTree<T,comp,allowDuplicities>> InnerTrees()
        {
            Vector<BinomialTree> inner;
            typename Vector<Node*>::Iterator moving = this->top->rest.Begin();
            for(;moving.IsValidIterator();moving.Next())
            {
                BinomialTree x;
                x.top = *moving.GetValue();
                inner.Insert(x);
            }
            return inner;
        }

        T Top()
        {
            return this->top->val;
        }

        int Level()
        {
            return this->top->rest.Size();
        }
    };

}

#endif //TEMPLATES_BINOMIALTREE_H
