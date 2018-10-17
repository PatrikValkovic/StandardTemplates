#ifndef TEMPLATES_ARRAY_H_H
#define TEMPLATES_ARRAY_H_H

#include "Exceptions.h"
#include "IteratorsDefinitions.h"
#include "Interval.h"
#include "UniquePointer.h"

namespace Templates
{
    template<typename T>
    class Array
    {
    private:
        static const int BASE_SIZE = 8;

        int _allocated{};
        int _inserted{};
        UniquePointer<T, __deleterWithoutDestruction<T>> _array;

        //TODO get rid of
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
                Instance = nullptr;
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
                return index >= 0 && Instance != nullptr && index < Instance->_inserted;
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
                    return nullptr;
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
                if (index + 1 < 0 || index + 1 > Instance->_inserted)
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
                if (index + HowMany < 0 || index + HowMany > Instance->_inserted)
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
                if (index - 1 < 0 || index - 1 > Instance->_inserted)
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
                if (index - HowMany < 0 || index - HowMany > Instance->_inserted)
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
                if (Instance == nullptr)
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
                if (Instance->_inserted == this->index)
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
                if (Instance->_inserted == this->index)
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
                if (this->Instance == nullptr)
                    return 0;

                if (this->index == Instance->_inserted)
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
                    return Instance->DeleteFromEnd(Instance->_inserted - index - 1);

                int count = Instance->Shift(index + Count + 1, -Count);
                return count < 0 ? -count : count;
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
                if (this->index == Instance->_inserted - 1)
                    return Instance->DeleteFromEnd(1);
                Instance->Shift(index + 1, -1);
                return 1;
            }
        };

        /**
         * Initialize new instance with default size BASE_SIZE
         */
        Array() : Array(BASE_SIZE)
        {}

        /**
         * Inicialize new instance with @Capacity
         */
        explicit Array(int capacity) : _allocated(0), _inserted(0), _array(nullptr)
        {

            capacity = (capacity <= 0 ? BASE_SIZE : capacity);
            _array = UniquePointer<T, __deleterWithoutDestruction<T>>(
                    (T*)::operator new(sizeof(T) * capacity)
            );
            _allocated = capacity;
            _inserted = 0;
        }

        /**
         * Initialize new instance with same values as second Array.
         * Creates copy of values from the second array.
         */
        Array(const Array& second) : Array(second._array.Raw(), second._inserted)
        {}

        /**
         * Move constructor, initializate Array from the values of other array.
         * The second instance will be cleared
         */
        Array(Array&& second) noexcept : Array()
        {
            swap(second, *this);
        }

        /**
         * Initialize new instance and fill it with values in array.
         * The Array create copy of the values.
         */
        Array(T* array, int count) : Array(count)
        {
            T* internalPointer = _array.Raw();
            for (int i = 0; i < count; i++, array++, internalPointer++)
                try
                {
                    new (internalPointer) T(*array);
                }
                catch(...)
                {
                    i--;
                    for(;i >= 0; i--)
                        _array[i].~T();
                    throw;
                }
            _inserted = count;
        }

        /**
         * Destructor
         */
        ~Array()
        {
            for (; _inserted > 0;)
                _array[--_inserted].~T();
        }

        /**
         * Copy all elements from second array to this
         * Creates deep copy of second array
         */
        Array& operator=(const Array& second)
        {
            if (this == &second)
                return *this;

            Delete();
            this->Expand(second._inserted - _allocated);

            for (int a = 0; a < second._inserted; a++)
                Containing[a] = new T(*second.Containing[a]);
            this->_inserted = second._inserted;
            return *this;
        }

        /**
         * Return count of values in Array
         */
        int Size() const
        {
            return _inserted;
        }

        int Capacity() const
        {
            return _allocated;
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
            return Iterator(this, _inserted);
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
            if (index >= _inserted || index < 0)
                return false;

            Out = Iterator(this, index);
            return true;
        }


    private:

        T& GetElementAtIndex(int index)
        {
            if (index >= _inserted || index < 0)
                throw OutOfRangeException("Operator is out of array range", __LINE__);

            return _array[index];
        }


        void Expand(int By = 0)
        {
            //By could be < 0

            if (By <= 0)
                By = int(_allocated * 0.5 == 0 ? BASE_SIZE : _allocated * 0.5);

            int OldAllocation = _allocated;
            this->_allocated = _allocated + By;
            Containing = (T**) realloc(Containing, sizeof(T*) * (_allocated));

            if (By > 0)
                memset(Containing + OldAllocation, 0, sizeof(T*) * (By));
        }

        void ExpandTo(int To)
        {
            if (To <= 0)
                return;

            if (To < 10)
                To = 10;

            int OldAllocation = _allocated;
            this->_allocated = To;
            Containing = (T**) realloc(Containing, sizeof(T*) * (_allocated));
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
            if (index < 0 || index >= _inserted)
                return 0;
            if (PlacesToShift == 0 || _inserted == 0)
                return 0;

            if (index + PlacesToShift < 0)
                PlacesToShift = (-1) * index;

            if (PlacesToShift < 0)
                for (int a = index + PlacesToShift; a < index; a++)
                    delete Containing[a];

            else if (_inserted + PlacesToShift > _allocated)
                ExpandTo(_inserted + PlacesToShift);

            memmove(Containing + index + PlacesToShift, Containing + index, sizeof(T*) * (_inserted - index));

            Math::Interval<int> Original(index, _allocated);
            Math::Interval<int> MovedTo(index + PlacesToShift, _inserted + PlacesToShift);
            Math::Interval<int> ToDelete = Original - MovedTo;
            memset(Containing + ToDelete.GetBegin(), 0,
                   sizeof(T*) * (ToDelete.GetEnd() - ToDelete.GetBegin()));

            this->_inserted += PlacesToShift;

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
            if (Count >= _inserted)
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

            _inserted = 0;
            Array tmp;
            swap(*this, tmp);

            return 0;
        }

        int DeleteFromEnd(int Count)
        {
            int deleted = 0;
            for (int i = _inserted - 1, a = 0; a < Count && i >= 0; a++, i--)
            {
                delete Containing[i];
                Containing[i] = nullptr;
                deleted++;
                _inserted--;
            }
            return deleted;
        }

        /**
         * Convert Array to C++-like array (must be cleared by delete [])
         * Return new array, NULL otherwise
         */
        T* ToArray(int& count) const
        {
            if (_inserted == 0)
                return nullptr;
            count = _inserted;
            T* CreatedArray = new T[this->_inserted];
            for (int a = 0; a < _inserted; a++)
                new(CreatedArray + a) T(*Containing[a]);
            return CreatedArray;
        }

        /**
         * Create array, that can be edited
         * Return editable array, NULL otherwise
         */
        T** ToWriteArray(int& count)
        {
            if (_inserted == 0)
                return nullptr;
            count = _inserted;

            T** CreatedArray = new T*[this->_inserted];
            CreatedArray = (T**) memcpy(CreatedArray, this->Containing, sizeof(T*) * this->_inserted);
            return CreatedArray;
        }

        /**
         * Insert @Value in the end of Array
         * Return 1 if success, otherwise 0
         */
        int Push(const T& Value)
        {
            if (_allocated == _inserted)
            {
                int NewAlloc = int(_allocated * 1.5);
                Expand(NewAlloc - _allocated);
            }

            Containing[_inserted] = new T(Value);
            _inserted++;
            return 1;
        }

        /**
         * Insert @Count values from @Values array
         * Return count of inserted elements, 0 if error was detected
         */
        int Push(const T* const Values, int Count)
        {
            if (_allocated < _inserted + Count)
            {
                int NewAlloc = _inserted + Count;

                Expand(NewAlloc - _allocated);
            }

            for (int a = 0; a < Count; a++)
                Containing[_inserted + a] = new T(Values[a]);
            _inserted += Count;
            return Count;
        }

        /**
         * Set size of array to best fit count of values already in
         * Return new capacity of array
         */
        int ShrinkToFit()
        {
            int NewSize = _inserted > 10 ? _inserted : 10;
            this->Containing = (T**) realloc(this->Containing, sizeof(T*) * NewSize);
            this->_allocated = NewSize;
            if (_allocated > _inserted)
                memset(this->Containing + _inserted, 0, sizeof(T*) * (NewSize - _inserted));
            return _inserted;
        }

        /**
         * Swap elements at speciic indexes
         */
        bool Swap(int FirstIndex, int SecondIndex)
        {
            if (FirstIndex < 0 || FirstIndex >= _inserted || SecondIndex < 0 || SecondIndex >= _inserted ||
                FirstIndex == SecondIndex)
                return false;

            T* temp = Containing[FirstIndex];
            Containing[FirstIndex] = Containing[SecondIndex];
            Containing[SecondIndex] = temp;
            return true;
        }

        void Swap(Array &second) noexcept {
            using Templates::swap;
            swap(_allocated, second._allocated);
            swap(_inserted, second._inserted);
            swap(_array, second._array);
        }
    };

    template<typename T>
    void swap(Array<T>& first,Array<T>& second)
    {
        first.Swap(second);
    }
}

#endif //TEMPLATES_ARRAY_H_H
