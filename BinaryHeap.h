#ifndef TEMPLATES_BINARYHEAP_H
#define TEMPLATES_BINARYHEAP_H

#include "Array.h"

namespace Templates
{
    template<typename T>
    class BinaryHeap
    {
    private:
        Array <T> *Container;
        int (*Sorting)(const T *const First, const T *const Second);

        void RepairHeap(int index)
        {
            int Child = index;
            int Parent = (Child - 1) / 2;
            T ChildElement = (*Container)[Child];
            T ParentElement = (*Container)[Parent];

            /**
             * return < 0 if Second is bigger than First
             * return 0 if First and Second are equal
             * return > 0 if First is bigger than Second
             */
            while (Parent >= 0 && Sorting(&ChildElement, &ParentElement) < 0)
            {
                Container->Swap(Child, Parent);
                Child = Parent;
                Parent = (Child - 1) / 2;
                ChildElement = (*Container)[Child];
                ParentElement = (*Container)[Parent];
            }
        }

        void DowngradeRepairHeap(int index)
        {
            int ParentIndex = index;
            int LastIndex = Container->Size() - 1;
            int RightChildIndex;
            int LeftChildIndex;
            int result;
            int IndexToSwap;
            T Child;
            T Parent;

            while (true)
            {
                if (ParentIndex > LastIndex)
                    return;

                LeftChildIndex = ParentIndex == 0 ? 1 : ParentIndex * 2 + 1;
                RightChildIndex = LeftChildIndex + 1;

                //resolve child
                if (LeftChildIndex > LastIndex && RightChildIndex > LastIndex)
                    return;
                else if (LeftChildIndex <= LastIndex && RightChildIndex <= LastIndex)
                {
                    /**
                     * return < 0 if Second is bigger than First
                     * return 0 if First and Second are equal
                     * return > 0 if First is bigger than Second
                     */
                    result = this->Sorting(&((*Container)[LeftChildIndex]), &((*Container)[RightChildIndex]));
                    IndexToSwap = result < 0 ? LeftChildIndex : RightChildIndex;
                }
                else
                    IndexToSwap = LeftChildIndex <= LastIndex ? LeftChildIndex : RightChildIndex;

                //swap
                Parent = (*Container)[ParentIndex];
                Child = (*Container)[IndexToSwap];

                /**
                 * return < 0 if Second is bigger than First
                 * return 0 if First and Second are equal
                 * return > 0 if First is bigger than Second
                 */
                result = this->Sorting(&Parent, &Child);
                if (result < 0)
                    return;

                Container->Swap(ParentIndex, IndexToSwap);
                ParentIndex = IndexToSwap;
            }
        }

    public:
        /**
         * Callback
         * return < 0 if Second is bigger than First
         * return 0 if First and Second are equal
         * return > 0 if First is bigger than Second
         */
        BinaryHeap(int(*SortCallback)(const T *const First, const T *const Second))
        {
            this->Sorting = SortCallback;
            Container = new Array<T>();
        }

        BinaryHeap(const BinaryHeap &Second)
        {
            this->Container = new Array<T>(*Second.Container);
        }

        BinaryHeap &operator=(const BinaryHeap &Second)
        {
            if(this==&Second)
                return *this;
            *this->Container = *Second.Container;
            return *this;
        }

        ~BinaryHeap()
        {
            delete Container;
        }

        /**
         * Add next element to bottom layer on first empty cell.
         * Return count of unserted elements
         */
        int Insert(T &Value)
        {
            if (this->Container->Push(Value) == 0)
                return 0;

            RepairHeap(Container->Size() - 1);
            return 1;
        }

        int Insert(T *Values, int Count)
        {
            int inserted = Container->Push(Values, Count);
            for (int a = inserted; a >= 0; a++)
                RepairHeap(Container->Size() - inserted);
            return inserted;
        }

        /**
         * Remove all elements from Heap.
         * Return count of deleted elements.
         */
        int Clear()
        {
            return Container->Delete();
        }

        bool IsEmpty()
        {
            return this->Container->Size()==0;
        }

        bool Top(T &val)
        {
            typename Array<T>::Iterator iter;
            if (!Container->TryAt(0, iter))
                return false;
            val = *iter.GetValue();
            return true;
        }

        bool Pop(T &Val)
        {
            if(!this->Top(Val))
                return false;

            this->Container->Swap(Container->Size() - 1, 0);
            this->Container->DeleteFromEnd(1);
            this->DowngradeRepairHeap(0);

            return true;
        }

        void Merge(BinaryHeap& second)
        {
            for(int a=0,s=second.Container->Size();a<s;a++)
                this->Insert((*second.Container)[a]);

            second.Container = new Array<T>();
            return;
        }
    };

}
#endif //TEMPLATES_BINARYHEAP_H
