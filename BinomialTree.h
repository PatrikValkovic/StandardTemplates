#ifndef TEMPLATES_BINOMIALTREE_H
#define TEMPLATES_BINOMIALTREE_H

#include "Exceptions.h"
#include "Vector.h"
#include "Queue.h"

namespace Templates
{
    //return true, if is first lower then second
    //bool(*comp)(const T& first, const T& second)

    template<typename T, bool(*comp)(const T& first, const T& second)>
    class BinomialTree
    {
    private:
        class Node
        {
        public:
            Node(T val): val(val) {}
            T val;
            Vector<Node*> rest;
        };

        Node* top;

    public:
        BinomialTree(T val)
        {
            Node* created = new Node(val);
            this->top = created;
        }

        ~BinomialTree()
        {
            if(top == NULL)
                return;

            Queue<Node*> ToProcess;
            ToProcess.Push(top);
            Node* ToDelete;

            while(ToProcess.Pop(ToDelete))
            {
                typename Vector<Node*>::Iterator moving = ToDelete->rest.Begin();
                typename Vector<Node*>::Iterator end = ToDelete->rest.End();
                for(;!moving.AreEqual(end) && moving.Next();)
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

        void Merge(BinomialTree& second)
        {
            if (this->top->rest.Size() != second.top->rest.Size())
                throw new InvalidArgumentException("Level of trees are not same", __LINE__);

            if (comp(top->val,second.top->val))
            {
                top->rest.Insert(second.top);
                second.top = NULL;
            }
            else
            {
                second.top->rest.Insert(top);
                this->top = second.top;
                second.top = NULL;
            }
        }
    };

}

#endif //TEMPLATES_BINOMIALTREE_H
