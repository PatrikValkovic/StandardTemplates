#ifndef TEMPLATES_STACK_H
#define TEMPLATES_STACK_H
#ifndef _STALIB_
#include <stdlib.h>
#endif

#include "IteratorsDefinitions.h"

namespace Templates
{
    /**
     * Represent LIFO structure
     */
    template<typename T>
    class Stack
    {
    private:
        class Node
        {
        public:
            T Value;
            Node* Next;

            Node()
            { Next = NULL; }
        };

        Node* TopNode;
    public:
        class Iterator :
                virtual public Iterators::ForwardIteratorBase<T>,
                virtual public Iterators::DeletingForwardIteratorBase<T>
        {
        private:
            Stack* WorkingStack;
        public:
            /**
             * Creates non valid empty iterator.
             */
            Iterator()
            { WorkingStack = NULL; }

            /**
             * Return iterator tied with queue.
             */
            Iterator(Stack* Que) : Iterator()
            { this->WorkingStack = Que; }

            /**
             * Copy constructor
             */
            Iterator(const Iterator& Copy)
                    : Iterator(Copy.WorkingStack)
            { }

            /**
             * Copy iterator.
             */
            Iterator Clone()
            { return Iterator(this->WorkingStack); }

            /**
             * Check if are iterators at the same position
             * @param Second Iterator compare to
             * @return True if are iterators equal, false otherwise
             */
            virtual bool AreEqual(const Iterator& Second) const
            {
                return this->WorkingStack == Second.WorkingStack;
            }

            /**
             * Return true, if is iterator valid and may work with it.
             */
            virtual bool IsValidIterator() const
            { return WorkingStack != NULL && WorkingStack->TopNode!=NULL; }

            /**
             * Return first value on Stack, but dont remove it.
             */
            virtual T* GetValue()
            { return &this->WorkingStack->TopNode->Value; }

            /**
             * Set value of first object in Stack. Don't remove it.
             */
            virtual void SetValue(const T& Val)
            { this->WorkingStack->TopNode->Value = Val; }

            /**
             * Removes first element in Stack and point to another one.
             * Return true, if was action successful, otherwise false.
             */
            virtual bool Next()
            {
                T val;
                return this->WorkingStack->Pop(val) && this->WorkingStack->TopNode!=NULL;
            }

            /**
             * Move @HowMany elements after actual element. Return true, if can, otherwise false.
             * If success, removes HowMany elements from queue.
             */
            virtual bool Next(int HowMany)
            {
                T* Array = (T*) malloc(sizeof(T) * HowMany);
                int i;
                for (i = 0; i < HowMany; i++)
                    if (!this->WorkingStack->Pop(*(Array + i)))
                        break;
                if (i == HowMany)
                {
                    free(Array);
                    return true;
                }

                for (int j = i - 1; j >= 0; j--)
                    this->WorkingStack->Push(*(Array + j));
                free(Array);
                return false;
            }

            /**
             * Removes @Count elements from Stack.
             * Return count of deleted elements.
             */
            virtual int DeleteAfter(int Count = 1)
            { return this->Next(Count) ? Count : 0; }

            /**
             * Insert elements on top of Stack.
             * Return 1 if was inserted.
             */
            virtual int Insert(const T& Value)
            { return this->WorkingStack->Push(Value); }

            /**
             * Insert Count of elements from Array to Stack. Last element in Array will be on top of Stack.
             * Return count of inserted elements.
             */
            virtual int Insert(const T* const Array, int Count)
            { return this->WorkingStack->Push(Array, Count); }


        };

        /**
         * Creates empty Stack
         */
        Stack() : TopNode(NULL)
        { }

        /**
         * First field in array will be the last in Stack
         */
        Stack(const T* Array, int Count) : Stack()
        { this->Push(Array, Count); }

        /**
         * Assignment operator
         */
        Stack& operator=(const Stack& Second)
        {
            if(this!=&Second)
            {
                this->Clear();
                if(Second.IsEmpty())
                {
                    this->TopNode = NULL;
                    return *this;
                }

                Node* Created = new Node;
                Created->Value = Second.TopNode->Value;
                this->TopNode = Created;

                Node* Temp = Second.TopNode->Next;
                for(;Temp!=NULL;Temp=Temp->Next)
                {
                    Node* ToAdd = new Node;
                    ToAdd->Value = Temp->Value;
                    Created->Next = ToAdd;
                    Created = ToAdd;
                }
            }
            return *this;
        }

        /**
         * Copy constructor
         */
        Stack(const Stack& Second) : Stack()
        {
            if(Second.IsEmpty())
            {
                this->TopNode = NULL;
                return;
            }

            Node* Created = new Node;
            Created->Value = Second.TopNode->Value;
            this->TopNode = Created;

            Node* Temp = Second.TopNode->Next;
            for(;Temp!=NULL;Temp=Temp->Next)
            {
                Node* ToAdd = new Node;
                ToAdd->Value = Temp->Value;
                Created->Next = ToAdd;
                Created = ToAdd;
            }
        }

        /**
         * Destructor
         */
        ~Stack()
        {
            this->Clear();
        }

        /**
         * Return valid iterator to top element
         */
        Iterator Begin()
        { return Iterator(this); }

        /**
         *  Return count of elements stored in Stack
         */
        int Size()
        {
            int Count = 0;
            Node* Temp = this->TopNode;
            while (Temp != NULL)
            {
                Count++;
                Temp = Temp->Next;
            }
            return Count;
        }

        /**
         *  Return elements in Stack as array without deleting them
         *  Top element on stack will be first in array
         */
        T* ToArray(int& count)
        {
            count = this->Size();
            if(count==0)
                return NULL;
            T* Array = (T*) malloc(sizeof(T) * count);
            Node* Temp = this->TopNode;
            for(int i=0;i<count;i++,Temp=Temp->Next)
                *(Array+i) = Temp->Value;
            return Array;
        }

        /**
         *  Add element to top of Stack.
         *  Return count of inserted elements
         */
        int Push(const T& Val)
        {
            Node* Temp = new Node;
            Temp->Value = Val;
            if (this->TopNode != NULL)
                Temp->Next = this->TopNode;
            this->TopNode = Temp;
            return 1;
        }

        /**
         * Add Count elements from Array into Stack.
         * Return count of inserted elements.
         */
        int Push(const T* Array, int Count)
        {
            int Added = 0;
            for (int a = 0; a < Count; a++, Array++)
                Added += this->Push(*Array);
            return Added;
        }

        /**
         * Get first elements from top of Stack and remove it.
         * Return false if error occurs.
         */
        bool Pop(T& Value)
        {
            if (this->TopNode == NULL)
                return false;
            Node* Temp = this->TopNode;
            this->TopNode = Temp->Next;
            Value = Temp->Value;
            delete Temp;
            return true;
        }

        /**
         * Removes all elements from Stack.
         * Return count of deleted items.
         */
        int Clear()
        {
            int deleted = 0;
            Node* Temp = this->TopNode;
            while (Temp != NULL)
            {
                Node* ToDelete = Temp;
                Temp = Temp->Next;
                delete ToDelete;
                deleted++;
            }
            this->TopNode = NULL;
            return deleted;
        }

        /**
         * Return true, if is Stack empty.
         */
        bool IsEmpty() const
        { return this->TopNode == NULL; }
    };
}
#endif //TEMPLATES_STACK_H
