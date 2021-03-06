#ifndef TEMPLATES_QUEUE_H
#define TEMPLATES_QUEUE_H

#include "Exceptions.h"
#include "IteratorsDefinitions.h"

namespace Templates
{
    /**
     * Represent FIFO structure
     */
    template<typename T>
    class Queue
    {
    protected:
        class Node
        {
        public:
            T Value;
            Node* Next;

            Node()
            { Next = nullptr; }
        };

        Node* First;
        Node* Last;
    public:
        class Iterator :
                virtual public Iterators::ForwardIteratorBase<T>,
                virtual public Iterators::DeletingForwardIteratorBase<T>
        {
            friend class Queue;

        private:
            Queue* WorkingQueue;
        public:
            /**
             * Creates non valid empty iterator.
             */
            Iterator()
            {
                WorkingQueue = nullptr;
            }

            /**
             * Return iterator tied with queue.
             */
            Iterator(Queue* Que) : Iterator()
            {
                this->WorkingQueue = Que;
            }

            /**
             * Copy constructor
             */
            Iterator(const Iterator& Copy)
                    : Iterator(Copy.WorkingQueue)
            { }

            /**
             * Check if are iterators at the same position
             * @param Second Iterator compare to
             * @return True if are iterators equal, false otherwise
             */
            virtual bool AreEqual(const Iterator& Second) const
            {
                return this->WorkingQueue == Second.WorkingQueue;
            }

            /**
             * Return true, if is iterator valid and may work with it.
             */
            virtual bool IsValidIterator() const
            {
                return WorkingQueue != nullptr;
            }

            /**
             * Return first value in array, but dont remove it.
             */
            virtual T* GetValue()
            {
                return &this->WorkingQueue->First->Value;
            }

            /**
             * Set value of first object in queue. Dont remove it.
             */
            virtual void SetValue(const T& Val)
            {
                this->WorkingQueue->First->Value = Val;
            }

            /**
             * Removes first element in queue and point to another one.
             * Return true, if was action successful, otherwise false.
             */
            virtual bool Next()
            {
                return Next(1);
            }

            /**
             * Move @HowMany elements after actual element. Return true, if can, otherwise false.
             * If success, removes HowMany elements from queue.
             */
            virtual bool Next(int HowMany)
            {
                bool CanMove = true;
                T* Values = new T[HowMany+1];
                T* Base = Values;
                int a = 0;
                for (; a < HowMany && CanMove; a++)
                    if (!this->WorkingQueue->Pop(*(Values + a)))
                        CanMove = false;
                if (!CanMove)
                {
                    for (int i = 0; i < a - 1; i++)
                    {
                        this->WorkingQueue->Push(*Values);
                        Values++;
                    }
                }
                delete [] Base;
                return CanMove;
            }

            /**
             * Removes @Count elements from beginning of the queue.
             * Return count of deleted elements.
             */
            virtual int DeleteAfter(int Count = 1)
            {
                return this->WorkingQueue->Clear(Count);
            }

            /**
             * Insert Value to end of queue.
             * Return 1, if was element inserted.
             */
            virtual int Insert(const T& Value)
            {
                return this->WorkingQueue->Push(Value);
            }

            /**
             * Insert Count of elements from Array to end of queue.
             * Return count of inserted elements.
             */
            virtual int Insert(const T* const Array, int Count)
            {
                return this->WorkingQueue->Push(Array, Count);
            }

            /**
             * Copy iterator.
             */
            Iterator Clone()
            {
                return Iterator(this->WorkingQueue);
            }
        };

        /**
         * Creates empty Queue
         */
        Queue()
        {
            First = nullptr;
            Last = nullptr;
        }

        /**
         * First field in array will be first in Queue
         */
        Queue(const T* Array, int Count) : Queue()
        {
            if (Count <= 0)
                return;
            for (int a = 0; a < Count; a++)
                if (!Push(*(Array + a)))
                    return;
        }

        /**
         * Copy constructor
         */
        Queue(const Queue& Copy)
        {
            int val;
            T* Array = Copy.ToArray(val);
            Queue(Array,val);
            delete [] (Array);
        }

        /**
         * Assignment operator
         */
        Queue& operator=(const Queue& Second)
        {
            if (this != &Second)
            {
                int val;
                T* Array = Second.ToArray(val);
                this->Push(Array,val);
                delete [] (Array);
            }
            return *this;
        }

        virtual ~Queue()
        {
            while (First != nullptr)
            {
                Node* Temp = First;
                First = Temp->Next;
                delete Temp;
            }
        }

        /**
         * Return valid iterator to first element in queue.
         */
        virtual Iterator Begin()
        {
            return Iterator(this);
        }

        /**
         * Return count of elements stored in queue.
         */
        int Size() const
        {
            Node* Temp = First;
            int count = 0;
            while (Temp != nullptr)
            {
                Temp = Temp->Next;
                count++;
            }
            return count;
        }

        /**
         * Return elements as array.
         * Array must be cleared by delete[]
         */
        T* ToArray(int& Count) const
        {
            int CountOfStoredElements = Size();
            if (CountOfStoredElements == 0)
                return nullptr;
            T* array = new T[CountOfStoredElements];
            if (array == nullptr)
                return nullptr;

            T* Base = array;

            Node* Working = First;
            while (Working != nullptr)
            {
                *array = Working->Value;
                array++;
                Working = Working->Next;
            }
            return Base;
        }

        /**
         * Push Value to end of Queue
         */
        virtual bool Push(const T& Value)
        {
            if (First == nullptr && Last == nullptr)
            {
                Node* Temp = new Node;
                Temp->Value = Value;
                First = Last = Temp;
            }
            else if (First != nullptr && Last != nullptr)
            {
                Node* Temp = new Node;
                Temp->Value = Value;
                Last->Next = Temp;
                Last = Temp;
            }
#ifdef ADDITIONAL_TESTS
            else
                throw new InternalException(__FILE__, __LINE__);
#endif
            return true;
        }

        /**
         * Push array into Queue, first element in array will be first in Queue
         */
        virtual int Push(const T* Array, int Count)
        {
            for (int i = 0; i < Count; i++)
                if (!Push(*(Array + i)))
                    return i;
            return Count;
        }

        /**
         * Get first element at queue and remove it. Return false if error.
         */
        virtual bool Pop(T& Value)
        {
            if (First == nullptr && Last == nullptr)
                return false;
            else if (First != nullptr && Last != nullptr)
            {
                Node* Temp = First;
                First = Temp->Next;
                Value = Temp->Value;
                if (First == nullptr && Temp == Last)
                    Last = nullptr;
                delete Temp;
            }
#ifdef ADDITIONAL_TESTS
            else
                throw new InternalException(__FILE__, __LINE__);
#endif
            return true;
        }

        /**
         * Clear whole Queue
         */
        int Clear()
        {
            return Clear(0x7FFFFFFF);
        }

        /**
         * Clear HowMany elements from begin of queue
         */
        int Clear(int HowMany)
        {
#ifdef ADDITIONAL_TESTS
            if ((First == nullptr && Last != nullptr) || (First != nullptr && Last == nullptr))
                throw new InternalException(__FILE__, __LINE__);
#endif
            int deleted = 0;
            for (int a = 0; a < HowMany && First != nullptr; a++)
            {
                Node* Temp = First;
                First = Temp->Next;
                delete Temp;
                deleted++;
            }
            if (First == nullptr)
                Last = nullptr;
            return deleted;
        }

        /**
         * Check, if is Queue empty
         */
        bool IsEmpty()
        {
            if (First == nullptr && Last == nullptr)
                return true;
            else if (First != nullptr && Last != nullptr)
                return false;
#ifdef ADDITIONAL_TESTS
            else
                throw new InternalException(__FILE__, __LINE__);
#endif
            throw new QueueException(__FILE__, __LINE__);
        }
    };
}

#endif //TEMPLATES_QUEUE_H
