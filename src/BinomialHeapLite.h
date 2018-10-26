#ifndef TEMPLATES_BIMIALHEAPLITE_H
#define TEMPLATES_BIMIALHEAPLITE_H

#include "Exceptions.h"
#include "Stack.h"

namespace Templates
{
    namespace BinomialHeapLiteDelete
    {
        template<typename K>
        struct PointerDeleter
        {
            void operator()(K&)
            {}
        };

        template<typename K>
        struct PointerDeleter<K*>
        {
            void operator()(K* t)
            {
                delete t;
            }
        };

        template<typename K>
        struct Default
        {
            void operator()(K x)
            {}
        };
    }

    //return -1, if first is lower
    //return 0, if are equal
    //return 1, if is second lower
    template<typename T,
            int (* comp)(const T& first, const T& second),
            typename Deleter = BinomialHeapLiteDelete::Default<T>>
    class BinomialHeapLite
    {
    private:
        class Node
        {
        public:
            Node() = default;

            Node(T pers) : instance(pers)
            {}

            T instance;
            Node* next = nullptr;
            Node* childs = nullptr;
            unsigned int CountOfChilds = 0;

            static Node* FlipNodes(Node* actual)
            {
                if (actual == nullptr)
                    return nullptr;

                Templates::Stack<Node*> toFlip;
                while (actual != nullptr)
                {
                    toFlip.Push(actual);
                    actual = actual->next;
                }
                Node* temp;
                toFlip.Pop(actual);
                Node* toReturn = actual;
                while (!toFlip.IsEmpty())
                {
                    toFlip.Pop(temp);
                    actual->next = temp;
                    actual = temp;
                }
                actual->next = nullptr;
                return toReturn;
            }
        };

        class Tree
        {
        private:
            Node* top;
        public:
            Tree() = delete;

            Tree(T p) : top(new Node(p))
            {}

            Tree(Tree& second) = delete;

            Tree& operator=(const Tree& Second) = delete;

            static void MergeNodes(Node* lower, Node* bigger)
            {
                Node* nextBigger = bigger->next;
                bigger->next = lower->childs;
                lower->childs = bigger;
                lower->CountOfChilds++;
                if (nextBigger != lower)
                    lower->next = nextBigger;
            }

            void Merge(Tree& second)
            {
                if (this == &second)
                    throw new InvalidArgumentException("Cannot merge tree with self", __LINE__);

                /**
                 * return < 0 if Second is bigger than First
                 * return 0 if First and Second are equal
                 * return > 0 if First is bigger than Second
                 */
                long int accomp = comp(this->top->instance, second.top->instance);
                if (accomp < 0)
                {
                    MergeNodes(this->top, second.top);
                    second.top = nullptr;
                }
                else
                {
                    MergeNodes(second.top, this->top);
                    this->top = second.top;
                    second.top = nullptr;
                }
                return;
            }

            Node* DeleteTreeAndGetInnerTrees()
            {
                Node* inners = this->top->childs;
                delete this->top->instance;
                delete this->top;
                this->top = nullptr;
                return inners;
            }

            const T& Top()
            {
                return this->top->instance;
            }

            int Level()
            {
                return this->top->CountOfChilds;
            }
        };

        Node* Trees = nullptr;
        Node* currentLowerPerson = nullptr;
        Node** pointerToLower = nullptr;

        void ValidateList()
        {
            if (this->Trees == nullptr || this->Trees->next == nullptr)
            {
                currentLowerPerson = this->Trees;
                pointerToLower = &this->Trees;
                return;
            }
            Node** prev = &this->Trees;
            Node* cur = this->Trees;
            Node* next = cur->next;
            Node* sib = next->next;

            Node* currentLower = cur;
            Node** pointer = &this->Trees;

            while (next != nullptr)
            {
                if ((cur->CountOfChilds == next->CountOfChilds &&
                     sib == nullptr) ||
                    (cur->CountOfChilds == next->CountOfChilds &&
                     next->CountOfChilds != sib->CountOfChilds))
                {
                    /**
                     * return < 0 if Second is bigger than First
                     * return 0 if First and Second are equal
                     * return > 0 if First is bigger than Second
                     */
                    long int accomp = comp(cur->instance, next->instance);
                    if (accomp < 0)
                    {
                        Tree::MergeNodes(cur, next);
                        next = cur->next;
                        sib = next == nullptr ? nullptr : next->next;
                    }
                    else
                    {
                        Tree::MergeNodes(next, cur);
                        *prev = next;
                        cur = next;
                        next = cur->next;
                        sib = next == nullptr ? nullptr : next->next;
                    }
                }
                else
                {
                    prev = &cur->next;
                    cur = cur->next;
                    next = next->next;
                    if (sib != nullptr)
                        sib = sib->next;
                }
                if (comp(cur->instance, currentLower->instance) <= 0)
                {
                    currentLower = cur;
                    pointer = prev;
                }
            }
            this->currentLowerPerson = currentLower;
            this->pointerToLower = pointer;
            return;
        }

        void ValidBeginning()
        {
            if (this->Trees == nullptr || this->Trees->next == nullptr)
            {
                currentLowerPerson = this->Trees;
                pointerToLower = &this->Trees;
                return;
            }
            Node* cur = this->Trees;
            Node* next = cur->next;

            while (next != nullptr && cur->CountOfChilds == next->CountOfChilds)
            {
                /**
                 * return < 0 if Second is bigger than First
                 * return 0 if First and Second are equal
                 * return > 0 if First is bigger than Second
                 */
                long int accomp = comp(cur->instance, next->instance);
                if (accomp < 0)
                {
                    Tree::MergeNodes(cur, next);
                    next = cur->next;
                }
                else
                {
                    Tree::MergeNodes(next, cur);
                    cur = next;
                    next = cur->next;
                }
            }

            this->Trees = cur;

            /**
             * return < 0 if Second is bigger than First
             * return 0 if First and Second are equal
             * return > 0 if First is bigger than Second
             */
            if (this->Trees != nullptr &&
                (currentLowerPerson == nullptr || comp(this->Trees->instance, currentLowerPerson->instance) <= 0))
            {
                this->currentLowerPerson = this->Trees;
                this->pointerToLower = &this->Trees;
            }
            else if (this->Trees->next == currentLowerPerson)
            {
                pointerToLower = &this->Trees->next;
            }
            return;
        }

        void Merge(Node* Second)
        {
            Node* inserting;
            Node* thisMoving = this->Trees;
            Node* secondMoving = Node::FlipNodes(Second);

            if (this->Trees == nullptr)
            {
                this->Trees = secondMoving;
                ValidateList();
                return;
            }
            if (Second == nullptr)
                return;

            if (this->Trees == Second)
                throw new InvalidArgumentException("Cannot merge heaps with same nodes", __LINE__);

            if (thisMoving->CountOfChilds < secondMoving->CountOfChilds)
            {
                inserting = thisMoving;
                thisMoving = thisMoving->next;
            }
            else
            {
                inserting = secondMoving;
                secondMoving = secondMoving->next;
            }

            this->Trees = inserting;

            for (; thisMoving != nullptr && secondMoving != nullptr; inserting = inserting->next)
            {
                if (thisMoving->CountOfChilds < secondMoving->CountOfChilds)
                {
                    inserting->next = thisMoving;
                    thisMoving = thisMoving->next;
                }
                else
                {
                    inserting->next = secondMoving;
                    secondMoving = secondMoving->next;
                }
            }

            if (thisMoving != nullptr)
                inserting->next = thisMoving;
            else if (secondMoving != nullptr)
                inserting->next = secondMoving;

            ValidateList();
        }

    public:

        BinomialHeapLite() = default;

        BinomialHeapLite(const BinomialHeapLite& second) = delete;

        BinomialHeapLite& operator=(const BinomialHeapLite& second) = delete;

        ~BinomialHeapLite()
        {
            if (this->Trees == nullptr)
                return;
            Templates::Stack<Node*> nodes;
            nodes.Push(this->Trees);
            Deleter d;
            while (!nodes.IsEmpty())
            {
                nodes.Pop(this->Trees);
                if (this->Trees->next != nullptr)
                    nodes.Push(this->Trees->next);
                if (this->Trees->childs != nullptr)
                    nodes.Push(this->Trees->childs);
                d(this->Trees->instance);
                delete this->Trees;
            }
        }

        void Push(T val)
        {
            Node* created = new Node(val);
            created->next = this->Trees;
            this->Trees = created;
            ValidBeginning();
        }

        bool Pop(T& val)
        {
            if (this->Trees == nullptr)
                return false;

            //delete current lower node
            val = currentLowerPerson->instance;
            *pointerToLower = currentLowerPerson->next;
            Node* OldCurrentPersons = currentLowerPerson;
            this->Merge(OldCurrentPersons->childs);
            delete OldCurrentPersons;

            //find new lower
            Node* currentLower = this->Trees;
            Node** pointer = &this->Trees;


            Node* current = this->Trees;
            Node* prev = nullptr;
            for (; current != nullptr; current = current->next)
            {
                /**
                 * return < 0 if Second is bigger than First
                 * return 0 if First and Second are equal
                 * return > 0 if First is bigger than Second
                 */
                long int res = comp(currentLower->instance, current->instance);
                if (res > 0)
                {
                    currentLower = current;
                    pointer = &prev->next;
                }
                prev = current;
            }

            this->currentLowerPerson = currentLower;
            this->pointerToLower = pointer;
            return true;
        }

        bool Top(T& val)
        {
            if (this->Trees != nullptr)
            {
                val = this->currentLowerPerson->instance;
                return true;
            }
            return false;
        }

        void Merge(BinomialHeapLite& second)
        {
            this->Merge(second.Trees);
            second.Trees = nullptr;
            second.pointerToLower = nullptr;
            second.currentLowerPerson = nullptr;
        }
    };
}

#endif //TEMPLATES_BIMIALHEAPLITE_H
