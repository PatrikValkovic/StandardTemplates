#ifndef TEMPLATES_ARRAY_H_H
#define TEMPLATES_ARRAY_H_H

#ifndef _STALIB_
#include <cstring>
#endif

#ifdef ADDITIONAL_TESTS

class ArrayTests;

#endif

#include "Exceptions.h"
#include "IteratorsDefinitions.h"
#include "Interval.h"

namespace Templates
{
    template<typename T,int BaseSize = 10>
    class Array
    {
#ifdef ADDITIONAL_TESTS

        friend class ::ArrayTests;

#endif
    private:
        int Allocated;
        int Inserted;

        T** Containing;
    public:
        class Iterator : public virtual Iterators::DeletingBackwardIteratorBase<T>,
                         virtual Iterators::InsertingIteratorBase<T>
        {
        private:
            Array* Instance;
            int index;
        public:
            /**
             * Creates new invalid iterator
             */
            Iterator()
            {
                index = -1;
                Instance = NULL;
            }

            /**
             * Creates new valid iterator pointed to specific elements in Array
             */
            Iterator(Array* ArrayInstance, int index)
            {
                this->index = index;
                this->Instance = ArrayInstance;
            }

            /**
             * Assignment operator
             */
            Iterator& operator=(const Iterator& Second)
            {
                if (this == &Second)
                    return *this;

                this->Instance = Second.Instance;
                this->index = Second.index;
                return *this;
            }

            /**
             * Return true, if is iterator valid, false otherwise
             */
            virtual bool IsValidIterator() const
            {
                return index >= 0 && Instance != NULL && index < Instance->Inserted;
            }

            /**
             * Check if are iterators equal
             * @param second Iterator compare to
             * @return True if are iterators at the same position, false otherwise
             */
            virtual bool AreEqual(const Iterator& second) const
            {
                return this->index == second.index && this->Instance == second.Instance;
            }

            /**
             * Return editable value, where iterator referencing
             * If is not valid, return NULL
             */
            virtual T* GetValue()
            {
                if (!IsValidIterator())
                    return NULL;
                return Instance->Containing[this->index];
            }

            /**
             * Set value of element, which iterator referencing
             * If is iterator invalid, do nothing
             */
            virtual void SetValue(const T& Val)
            {
                if (!IsValidIterator())
                    return;

                *Instance->Containing[this->index] = Val;
            }

            /**
             * Move iterator to next element in Array
             * Return true if can, false otherwise
             * Can invalidate iterator
             */
            virtual bool Next()
            {
                if (index + 1 < 0 || index + 1 > Instance->Inserted)
                    return false;
                index++;
                return true;
            }

            /**
             * Move iterator to @HowMany-th element after referencing element
             * Return true if can, false otherwise
             * Can invalidate iterator
             */
            virtual bool Next(int HowMany)
            {
                if (index + HowMany < 0 || index + HowMany > Instance->Inserted)
                    return false;
                index += HowMany;
                return true;
            }

            /**
             * Move iterator to previous element in Array
             * Return true if can, false otherwise
             */
            virtual bool Back()
            {
                if (index - 1 < 0 || index - 1 > Instance->Inserted)
                    return false;
                index--;
                return true;
            }

            /**
             * Move iterator to @HowMany-th element before referencing element
             * Return true if can, false otherwise
             */
            virtual bool Back(int HowMany)
            {
                if (index - HowMany < 0 || index - HowMany > Instance->Inserted)
                    return false;
                index -= HowMany;
                return true;
            }

            /**
             * Set iterator's position to beginning of Array
             * Return true, false if iterator is not valid
             */
            bool JumpToBegin()
            {
                if (Instance == NULL)
                    return false;
                index = 0;
                return true;
            }

            /**
             * Insert @Value after actual referencing element
             * Return 1 if success, 0 otherwise
             * Can change capacity of Array
             */
            virtual int Insert(const T& Value)
            {
                if (!IsValidIterator())
                    return 0;

                if (!Instance->Shift(index + 1, 1))
                    return 0;
                Instance->Containing[index + 1] = new T(Value);
                return 1;
            }

            /**
             * Insert @Value before actual referencing element
             * Return 1 if success, 0 otherwise
             * Can change capacity of Array
             */
            int InsertBefore(const T& Value)
            {
                if (Instance->Inserted == this->index)
                    return Instance->Push(Value);

                if (Instance->Shift(index, 1) == 0)
                    return 0;
                index++;
                Instance->Containing[index - 1] = new T(Value);
                return 1;
            }

            /**
             * Insert @Count values from $Values array after actual referencing element
             * Return count of inserted elements
             * Can change capacity of Array
             */
            virtual int Insert(const T* const Values, int Count)
            {
                if (!IsValidIterator())
                    return 0;

                if (!Instance->Shift(index + 1, Count))
                    return 0;

                for (int a = 0; a < Count; a++)
                    Instance->Containing[index + 1 + a] = new T(Values[a]);
                return Count;
            }

            /**
             * Insert @Count values from $Values array before actual referencing element
             * @Count-th element in @Values will be previous element of actual referencing element
             * Return count of inserted elements
             * Can change capacity of Array
             */
            int InsertBefore(const T* const Values, int Count)
            {
                if (Instance->Inserted == this->index)
                    return Instance->Push(Values, Count);

                if (!Instance->Shift(index, Count))
                    return 0;

                for (int a = 0; a < Count; a++)
                    Instance->Containing[index + a] = new T(Values[a]);
                index += Count;
                return Count;
            }

            /**
             * Delete @Count elements before referencing element
             * Default value is 1
             * Return count of deleted elements
             * Dont change capacity of Array and delete only elements in range
             */
            virtual int DeleteBefore(int Count = 1)
            {
                if (this->Instance == NULL)
                    return 0;

                if (this->index == Instance->Inserted)
                    return Instance->DeleteFromEnd(Count);

                if (!IsValidIterator())
                    return 0;

                int temp = (-1) * this->Instance->Shift(this->index, -Count);

                index = index - temp;

                return temp;
            }

            /**
             * Delete @Count elements after referencing element
             * Default value is 1
             * Return count of deleted elements
             * Dont change capacity of Vector and delete only elements in range
             */
            virtual int DeleteAfter(int Count = 1)
            {
                if (!IsValidIterator())
                    return 0;

                if (index + Count > Instance->Size())
                    return Instance->DeleteFromEnd(Instance->Inserted - index - 1);

                Instance->Shift(index + Count + 1, -Count);
                return Count;
            }

            /**
             * Delete referencing element
             * Move iterator to next element (previous, if is last element)
             * Return 1 if success, 0 otherwise
             */
            virtual int DeleteThis()
            {
                if (!this->IsValidIterator())
                    return 0;
                if (this->index == Instance->Inserted - 1)
                    return Instance->DeleteFromEnd(1);
                Instance->Shift(index + 1, -1);
                return 1;
            }
        };

        /**
         * Inicialize new instance with @Capacity
         */
        Array(int Capacity)
        {
            Capacity = (Capacity <= BaseSize ? BaseSize : Capacity);
            Containing = (T**) calloc((size_t)Capacity, sizeof(T*));
            Allocated = Capacity;
            Inserted = 0;
        }

        /**
         * Initialize new instance with default size 10
         */
        Array() : Array(BaseSize)
        {}

        /**
         * Initialize new instance with same values as second Array
         * Creates deep copy
         */
        Array(const Array& Second) : Array(Second.Size())
        {
            int SizeOfSecond = Second.Size();
            for (int a = 0; a < SizeOfSecond; a++)
                Containing[a] = new T(*Second.Containing[a]);
            this->Inserted = SizeOfSecond;
        }

        /**
         * Initialize new instance and fill it with values in array
         */
        Array(T* array, int count) : Array(count)
        {
            for (int a = 0; a < count; a++, array++)
                this->Containing[a] = new T(*array);
            Inserted = count;
        }

        /**
         * Destructor
         */
        ~Array()
        {
            Delete();
            free(Containing);
        }

        /**
         * Copy all elements from second array to this
         * Creates deep copy of second array
         */
        Array& operator=(const Array& Second)
        {
            if (this == &Second)
                return *this;

            Delete();
            this->Expand(Second.Inserted - Allocated);

            for (int a = 0; a < Second.Inserted; a++)
                Containing[a] = new T(*Second.Containing[a]);
            this->Inserted = Second.Inserted;
            return *this;
        }

        /**
         * Return count of values in Array
         */
        int Size() const
        {
            return Inserted;
        }

        int Capacity() const
        {
            return Allocated;
        }

        /**
         * Return iterator to begin of array
         */
        Iterator Begin()
        {
            return Iterator(this, 0);
        }

        /**
         * Return iterator referencing one element after last one
         * This iterator will not be valid
         */
        Iterator End()
        {
            return Iterator(this, Inserted);
        }

        /**
         * Return iterator at specific position in array
         * Iterator might not be valid
         */
        Iterator At(int index)
        {
            return Iterator(this, index);
        }

        /**
         * Try to create iterator at specific position in array
         * Return false, if is index out of range
         */
        bool TryAt(int index, Iterator& Out)
        {
            if (index >= Inserted || index < 0)
                return false;

            Out = Iterator(this, index);
            return true;
        }


    private:

        T& GetElementAtIndex(int index) const
        {
            if (index >= Inserted || index < 0)
                throw new() OutOfRangeException("Operator is out of range in Array", __LINE__);

            return *Containing[index];
        }


        void Expand(int By = 0)
        {
            //By could be < 0

            if (By <= 0)
                By = int(Allocated * 0.5 == 0 ? BaseSize : Allocated * 0.5);

            int OldAllocation = Allocated;
            this->Allocated = Allocated + By;
            Containing = (T**) realloc(Containing, sizeof(T*) * (Allocated));

            if (By > 0)
                memset(Containing + OldAllocation, 0, sizeof(T*) * (By));
        }

        void ExpandTo(int To)
        {
            if (To <= 0)
                return;

            if (To < 10)
                To = 10;

            int OldAllocation = Allocated;
            this->Allocated = To;
            Containing = (T**) realloc(Containing, sizeof(T*) * (Allocated));
            if (To > OldAllocation)
                memset(Containing + OldAllocation, 0, sizeof(T*) * (To - OldAllocation));
        }

        /**
         * Shift array by @PlacesToShift
         * can shift forward or backward
         * delete shifting space
         */
        int Shift(int index, int PlacesToShift)
        {
            if (index < 0 || index >= Inserted)
                return 0;
            if (PlacesToShift == 0 || Inserted == 0)
                return 0;

            if (index + PlacesToShift < 0)
                PlacesToShift = (-1) * index;

            if (PlacesToShift < 0)
                for (int a = index + PlacesToShift; a < index; a++)
                    delete Containing[a];

            else if (Inserted + PlacesToShift > Allocated)
                ExpandTo(Inserted + PlacesToShift);

            memmove(Containing + index + PlacesToShift, Containing + index, sizeof(T*) * (Inserted - index));

            Math::Interval<int> Original(index, Allocated);
            Math::Interval<int> MovedTo(index + PlacesToShift, Inserted + PlacesToShift);
            Math::Interval<int> ToDelete = Original - MovedTo;
            memset(Containing + ToDelete.GetBegin(), 0,
                   sizeof(T*) * (ToDelete.GetEnd() - ToDelete.GetBegin()));

            this->Inserted += PlacesToShift;

            return PlacesToShift;
        }

    public:

        /**
         * Return element at @ith index.
         * Throw exception, if is index out of range
         */
        T& operator[](int i)
        {
            return GetElementAtIndex(i);
        }

        const T& operator[](int i) const
        {
            return GetElementAtIndex(i);
        }

        /**
         * Delete @Count values from array
         * Dont change capacity
         * Return count of deleted elements
         */
        int Delete(int Count)
        {
            if (Count >= Inserted)
                return Delete();

            int deleted = (-1) * this->Shift(Count, -Count);
            return deleted;
        }

        /**
         * Delete all elements in array
         * Also change capacity of array to default value
         * Return count of deleted elements
         */
        int Delete()
        {
            for (int a = 0; a < Inserted; a++)
                delete Containing[a];
            int deleted = Inserted;
            ExpandTo(10);
            Inserted = 0;
            return deleted;
        }

        int DeleteFromEnd(int Count)
        {
            int deleted = 0;
            for (int i = Inserted - 1, a = 0; a < Count && i >= 0; a++, i--)
            {
                delete Containing[i];
                Containing[i] = NULL;
                deleted++;
                Inserted--;
            }
            return deleted;
        }

        /**
         * Convert Array to C++-like array (must be cleared by delete [])
         * Return new array, NULL otherwise
         */
        T* ToArray(int& count) const
        {
            if (Inserted == 0)
                return NULL;
            count = Inserted;
            T* CreatedArray = new T[this->Inserted];
            for (int a = 0; a < Inserted; a++)
                new(CreatedArray + a) T(*Containing[a]);
            return CreatedArray;
        }

        /**
         * Create array, that can be edited
         * Return editable array, NULL otherwise
         */
        T** ToWriteArray(int& count)
        {
            if (Inserted == 0)
                return NULL;
            count = Inserted;

            T** CreatedArray = new T*[this->Inserted];
            CreatedArray = (T**) memcpy(CreatedArray, this->Containing, sizeof(T*) * this->Inserted);
            return CreatedArray;
        }

        /**
         * Insert @Value in the end of Array
         * Return 1 if success, otherwise 0
         */
        int Push(const T& Value)
        {
            if (Allocated == Inserted)
            {
                int NewAlloc = int(Allocated * 1.5);
                Expand(NewAlloc - Allocated);
            }

            Containing[Inserted] = new T(Value);
            Inserted++;
            return 1;
        }

        /**
         * Insert @Count values from @Values array
         * Return count of inserted elements, 0 if error was detected
         */
        int Push(const T* const Values, int Count)
        {
            if (Allocated < Inserted + Count)
            {
                int NewAlloc = Inserted + Count;

                Expand(NewAlloc - Allocated);
            }

            for (int a = 0; a < Count; a++)
                Containing[Inserted + a] = new T(Values[a]);
            Inserted += Count;
            return Count;
        }

        /**
         * Set size of array to best fit count of values already in
         * Return new capacity of array
         */
        int ShrinkToFit()
        {
            int NewSize = Inserted > 10 ? Inserted : 10;
            this->Containing = (T**) realloc(this->Containing, sizeof(T*) * NewSize);
            this->Allocated = NewSize;
            if (Allocated > Inserted)
                memset(this->Containing + Inserted, 0, sizeof(T*) * (NewSize - Inserted));
            return Inserted;
        }

        /**
         * Swap elements at speciic indexes
         */
        bool Swap(int FirstIndex, int SecondIndex)
        {
            if (FirstIndex < 0 || FirstIndex >= Inserted || SecondIndex < 0 || SecondIndex >= Inserted ||
                FirstIndex == SecondIndex)
                return false;

            T* temp = Containing[FirstIndex];
            Containing[FirstIndex] = Containing[SecondIndex];
            Containing[SecondIndex] = temp;
            return true;
        }
    };
}

#endif //TEMPLATES_ARRAY_H_H
