#ifndef TEMPLATES_CONDQUEUE_H
#define TEMPLATES_CONDQUEUE_H

#include "Queue.h"

namespace Templates
{
    /**
     * Condition queue, only element passed Validation will be added.
     */
    template<typename T>
    class CondQueue : public Queue<T>
    {
    private:
        bool(* ValidCallback)(const T* What) = nullptr;
    public:
        /**
         * Constructor
         * @param Validation Function that return true, if should element be passed to queue
         * @return Instance of CondQueue
         */
        CondQueue(bool(* Validation)(const T* What))
                : Queue<T>::Queue()
        {
            this->ValidCallback = Validation;
        }

        /**
         * Create condition queue and add only elements meet the condition.
         */
        CondQueue(bool(* Validation)(const T* What), T* Array, int Count)
                : CondQueue(Validation)
        {
            Push(Array, Count);
        }

        /**
         * Copy contructor
         */
        CondQueue(const CondQueue& Copy)
                : CondQueue(Copy.ValidCallback)
        {
            typename Queue<T>::Node* Temp = this->First;
            while (Temp->Next != nullptr)
            {
                Push(Temp->Value);
                Temp = Temp->Next;
            }
        }

        /**
         * Push element to end of queue.
         * Return true, if was elements inserted, otherwise false.
         */
        virtual bool Push(const T& Value)
        {
            if (ValidCallback(&Value))
                return Queue<T>::Push(Value);
            return false;
        }

        /**
         * Assignment operator
         */
        CondQueue& operator=(const CondQueue& Second)
        {
            if (this != &Second)
            {
                this->ValidCallback = Second.ValidCallback;
                this->Clear();
                typename Queue<T>::Iterator Iter = Second.Begin();
                while (Iter.IsValidIterator())
                {
                    this->Push(*Iter.GetValue());
                    Iter.Next();
                }
            }
            return *this;
        }


        /**
         * Sets validation callback.
         */
        inline void SetCallback(bool(* Validation)(const T* What))
        {
            ValidCallback = Validation;
        }

        /**
         * Validate whole queue. Return count of deleted elements.
         * Could save memory, if were elements changed out of queue.
         */
        int ValidateQueue()
        {
            int deleted = 0;
            // 1 - Find first Validate
            while (this->First != nullptr && !ValidCallback(&this->First->Value))
            {
                typename Queue<T>::Node* Temp = this->First;
                this->First = Temp->Next;
                delete Temp;
                deleted++;
            }
            //If whole queue was deleted
            if (this->First == nullptr)
            {
                this->Last = nullptr;
                return deleted;
            }
            // 3 - Validate rest
            typename Queue<T>::Node* Previous = this->First;
            while (Previous->Next != nullptr)
            {
                typename Queue<T>::Node* Temp = Previous->Next;
                if (ValidCallback(&Temp->Value))
                    Previous = Temp;
                else
                {
                    Previous->Next = Temp->Next;
                    delete Temp;
                    deleted++;
                }
            }
            if (this->First == nullptr)
                this->Last = nullptr;
            return deleted;
        }

        /**
         * Push Count elements from Array.
         * Returns count of elements inserted.
         */
        virtual int Push(const T* Array, int Count)
        {
            int pushed = 0;
            for (int i = 0; i < Count; i++)
                if (this->Push(*(Array + i)))
                    pushed++;
            return pushed;
        }

        /**
         * Remove and return first element in queue. Element will be returned by parametr.
         * Return true, if was element returned, otherwise false.
         */
        virtual bool Pop(T& Value)
        {
            while (true)
            {
                T temp;
                if (!Queue<T>::Pop(temp))
                    return false;
                if (ValidCallback(&temp))
                {
                    Value = temp;
                    return true;
                }
            }
        }

        virtual T* ToArray(int& Count)
        {
            this->ValidateQueue();
            return Queue<T>::ToArray(Count);
        }

        virtual typename Queue<T>::Iterator Begin()
        {
            return typename Queue<T>::Iterator(this);
        }
    };
}
#endif //TEMPLATES_CONDQUEUE_H
