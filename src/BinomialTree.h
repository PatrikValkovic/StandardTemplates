#ifndef TEMPLATES_BINOMIALTREE_H
#define TEMPLATES_BINOMIALTREE_H

#include "Exceptions.h"
#include "Vector.h"
#include "Stack.h"

namespace Templates
{
    //return -1, if first is lower
    //return 0, if are equal
    //return 1, if is second lower
    //int(*comp)(const T& first, const T& second)

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

        struct Assign
        {
            Node* prev;
            Node* toProccess;
        };

        Node* top = NULL;
    public:
        BinomialTree()
        {
            this->top = NULL;
        }

        BinomialTree(T val) : BinomialTree()
        {
            Node* created = new Node(val);
            this->top = created;
        }

        ~BinomialTree()
        {

            if (top == NULL)
                return;

            Stack<Node*> ToProcess;
            ToProcess.Push(top);
            Node* ToDelete;

            while (!ToProcess.IsEmpty())
            {
                ToProcess.Pop(ToDelete);
                typename Vector<Node*>::Iterator moving = ToDelete->rest.Begin();
                typename Vector<Node*>::Iterator e = ToDelete->rest.End();
                for (; moving != e; moving++)
                    ToProcess.Push(*moving);
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
            if (this == &Second)
                return *this;

            this->Clear();

            if(Second.top == NULL)
                return *this;

            Stack<Assign> ToProcess;
            ToProcess.Push(Assign{NULL, Second.top});
            Assign ToCopy;

            while (!ToProcess.IsEmpty())
            {
                ToProcess.Pop(ToCopy);
                Node* newOne = new Node(ToCopy.toProccess->val);

                if (ToCopy.prev != NULL)
                    ToCopy.prev->rest.Insert(newOne);
                else
                        this->top = newOne;

                typename Vector<Node*>::Iterator moving = ToCopy.toProccess->rest.Begin();
                typename Vector<Node*>::Iterator e = ToCopy.toProccess->rest.End();
                for (; moving != e; moving++)
                    ToProcess.Push(Assign {newOne, *moving});
            }

            return *this;
        }

        void Clear()
        {
            if (top == NULL)
                return;

            this->~BinomialTree();
            this->top = NULL;
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
            else if ((accomp == 0 && allowDuplicities) || accomp > 0)
            {
                second.top->rest.Insert(top);
                this->top = second.top;
                second.top = NULL;
            }
            return;
        }

        List<BinomialTree<T, comp, allowDuplicities>> InnerTrees()
        {
            BinomialTree temp = *this;
            List<BinomialTree<T, comp, allowDuplicities>> inner;
            typename Vector<Node*>::Iterator moving = temp.top->rest.Begin();
            typename Vector<Node*>::Iterator e = temp.top->rest.End();
            for (; moving != e; moving++)
            {
                BinomialTree<T, comp, allowDuplicities> innerTree;
                innerTree.top = *moving;
                inner.End().InsertBefore(innerTree);
            }
            delete temp.top;
            temp.top = NULL;
            //flip
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
