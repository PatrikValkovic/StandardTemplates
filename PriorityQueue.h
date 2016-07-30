#ifndef __PRIORITYQUEUE_H_
#define __PRIORITYQUEUE_H_
#ifndef _STALIB_
#include <stdlib.h>
#endif
#include "BinaryMinHeap.h"


namespace Templates
{
    template<typename T>
    class PriorityQueue
    {
    private:
        BinaryMinHeap<T>* Instance;
    public:
        PriorityQueue(int(* SwitchCallback)(const T* const First, const T* const Second))
        {
            this->Instance = new BinaryMinHeap<T>(SwitchCallback);
        }

        /**
         * Copy contructor
         */
        PriorityQueue(const PriorityQueue& Second)
        {
            this->Instance = new BinaryMinHeap<T>(*Second.Instance);
        }

        ~PriorityQueue()
        {
            delete Instance;
        }

        /**
         * Assignment operator
         */
        PriorityQueue& operator=(const PriorityQueue& Second)
        {
            if(this==&Second)
                return *this;
            this->Instance = Second.Instance;
            return *this;
        }


        /**
         * Push element to queue.
         * Returns true, if was value inserted.
         */
        bool Push(T  Value)
        {
            return this->Instance->Insert(Value) == 1;
        }

        /**
         * Removes element from queue and remove it.
         * Value will be passed by parametr.
         * Return true, if could pop, false otherwise.
         */
        bool Pop(T& Value)
        {
            return this->Instance->Pop(Value);
        }
    };
}


#endif