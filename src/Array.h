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
        static const int EXPANDING_COEFICIENT = 2;

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
        Array(const T* array, int count) : Array(count)
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

            Array tmp(second._array.Raw(), second.Size());
            swap(*this, tmp);

            return *this;
        }

        Array& operator=(Array&& second) noexcept
        {
            if (this == &second)
                return *this;

            {
                Array tmp(move(*this));
            }

            swap(*this, second);

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
         * Return iterator to begin of array.
         * The iterator can't be valid, if the array is empty.
         */
        Iterator Begin()
        {
            return this->At(0);
        }

        /**
         * Return iterator referencing one element after last one.
         * This iterator will not be valid.
         */
        Iterator End()
        {
            return this->At(_inserted);
        }

        /**
         * Return iterator at specific position in array.
         * Position is validated, so it is valid, unless you want end of the array (one element after the last one).
         */
        Iterator At(int index)
        {
            if(index < 0 || index > _inserted)
                throw OutOfRangeException("", __LINE__);

            return Iterator(this, index);
        }

        /**
         * Try to create iterator at specific position in array.
         * Return false, if is index out of range.
         * Can return end iterator and thus invalid one. In all other cases the iterator is valid.
         * @param index Index of element to return
         * @param out Input parameter - iterator
         * @return True if the position is valid and thus iterator is valid, false otherwise
         */
        bool TryAt(int index, Iterator& out)
        {
            if (index > _inserted || index < 0)
                return false;

            out = At(index);
            return true;
        }

        /**
        * Return element at @i-th index.
        * Throw exception, if is index out of range
        */
        T& operator[](int i)
        {
            return GetElementAtIndex(i);
        }

        /**
         * Return element at @i-th index.
         * Throw exception, if is index out of range
         */
        const T& operator[](int i) const
        {
            return GetElementAtIndex(i);
        }

        /**
         * Resize the array by specific number of elements.
         * Can be used to expand or shrink the array.
         * Resize is based on capacity, on on the size.
         * @param by How much resize the array. If positive, the array will expand. If negative, the array will shrink.
         */
        void ResizeBy(int by)
        {
            this->Resize(_allocated + by);
        }

        /**
         * Resize the array to contain specific number of elements.
         * If the parameter is smaller then current size, overlapping elements will be destroyd.
         * @param to
         */
        void Resize(int to)
        {
            if(to < 0)
                throw OutOfRangeException("Cannot resize to negative value");

            Array tmp(to);
            tmp.Push(_array.Raw(), _inserted > to ? to : _inserted);

            swap(*this, tmp);
        }

        /**
         * Shrink the array so its capacity is same as the size.
         */
        void ShrinkToFit()
        {
            this->Resize(_inserted);
        }

        /**
         * Delete {@code count} elements from the {@code index}.
         * @param index From which element delete
         * @param count How many elements delete
         * @return Number of deleted elements
         */
        int Delete(int index, int count)
        {
            //TODO implement
        }

        /**
         * Delete {@code count} elements from the {@code index}.
         * Save version make sure, that the array remains valid if exception occurs.
         * Save version needs more memory than the unsafe one.
         * @param index From which element delete
         * @param count How many elements delete
         * @return Number of deleted elements
         */
        int DeleteSafe(int index, int count)
        {
            //TODO implement
        }


        /**
         * Delete {@code count} elements from the end.
         * In case the destructor throws a exception, the array stays in valid state.
         * @param count Number of elements to delete
         * @return Number of deleted elements
         */
        int DeleteFromEnd(int count)
        {
            //TODO implement safe
        }

        /**
         * Delete {@code count} elements from the beginning of the array.
         * In case the destuctor throws a exception, the array may stay in unvalid state.
         * @param count Number of elements to delete
         * @return Number of deleted elements
         */
        int DeleteFromBegin(int count)
        {
            return this->Delete(0, count);
        }

        /**
         * Delete {@code count} elements from the beginning of the array.
         * In case the destuctor throws a exception, the array stay in valid state.
         * Safe method needs more memory than the unsafe one.
         * @param count Number of elements to delete
         * @return Number of deleted elements
         */
        int DeleteFromBeginSave(int count)
        {
            return this->DeleteSafe(0, count);
        }

        /**
         * Delete all the elements in the array, but the allocated capacity stay.
         * @return
         */
        int Delete()
        {
            return this->DeleteFromEnd(_inserted);
        }


        /**
         * Insert element at the specific index.
         * Other elements are shifted right.
         * In case the copy constructor throws a exception, the array may stay in invalid state.
         * The index is validated, but you can use this method to insert element at the end of the array.
         * @param index Position where to put the element.
         * @param element Element to insert.
         * @return 1 if the element was inserted, 0 otherwise.
         */
        int Insert(int index, const T& element)
        {
            return this->Insert(index, &element, 1);
        }

        /**
         * Insert elements at the specific index.
         * Other elements are shifted right.
         * In case the copy constructor throws a exception, the array may stay in invalid state.
         * The index is validated, but you can use this method to insert elements at the end of the array.
         * @param index Position where to put the element.
         * @param element Element to insert.
         * @return Number of inserted elements.
         */
        int Insert(int position, const T* elements, int count)
        {
            //TODO implement
        }

        /**
         * Insert element at the specific index.
         * Other elements are shifted right.
         * In case the copy constructor throws a exception, the stay in valid state.
         * The safe version needs more space than the unsafe one.
         * The index is validated, but you can use this method to insert element at the end of the array.
         * @param index Position where to put the element.
         * @param element Element to insert.
         * @return 1 if the element was inserted, 0 otherwise.
         */
        int InsertSafe(int position, const T& element)
        {
            return this->InsertSafe(position, &element, 1);
        }

        /**
         * Insert elements at the specific index.
         * Other elements are shifted right.
         * In case the copy constructor throws a exception, the array stay in valid state.
         * The safe version needs more space than the unsafe one.
         * The index is validated, but you can use this method to insert elements at the end of the array.
         * @param index Position where to put the element.
         * @param element Element to insert.
         * @return Number of inserted elements.
         */
        int InsertSafe(int position, const T* elements, int count)
        {
            //TODO implement
        }



        //TODO implement emplace






    private:
        T& GetElementAtIndex(int index)
        {
            if (index >= _inserted || index < 0)
                throw OutOfRangeException("Operator is out of array range", __LINE__);

            return _array[index];
        }

        const T& GetElementAtIndex(int index) const
        {
            if (index >= _inserted || index < 0)
                throw OutOfRangeException("Operator is out of array range", __LINE__);

            return _array[index];
        }

        //TODO delete
        void Expand(int by = 0)
        {
            //By could be < 0

            if (by <= 0)
                by = int(_allocated * 0.5 == 0 ? BASE_SIZE : _allocated * 0.5);

            int OldAllocation = _allocated;
            this->_allocated = _allocated + by;
            Containing = (T**) realloc(Containing, sizeof(T*) * (_allocated));

            if (by > 0)
                memset(Containing + OldAllocation, 0, sizeof(T*) * (by));
        }

        //TODO delete
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
         * TODO delete
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
         * Delete {@code count} values from array
         * Don't change capacity
         * Return count of deleted elements
         * TODO delete
         */
        int Delete(int count)
        {
            if (count >= _inserted)
                return Delete();

            int deleted = (-1) * this->Shift(count, -count);
            return deleted;
        }

        /**
         * Return internal C-like array.
         * @param count Output parameter holding number of elements
         * @return Internal C-like array. Array can't be deleted.
         */
        const T* ToArray(int& count) const
        {
            count = _inserted;
            return _array.Raw();
        }

        /**
         * Return internal C-like array.
         * @param count Output parameter holding number of elements.
         * @return Internal C-like array. Array can't be deleted.
         */
        T* ToArray(int& count)
        {
            count = _inserted;
            return _array.Raw();
        }

        /**
         * Insert @Value in the end of Array
         * Return 1 if success, otherwise 0
         */
        int Push(const T& value)
        {
            return this->Push(&value, 1);
        }

        /**
         * Insert @Count values from @Values array
         * Return count of inserted elements, 0 if error was detected
         */
        int Push(const T * values, int count)
        {
            int newCapacity = _allocated;
            if(newCapacity < _inserted + count)
                newCapacity *= EXPANDING_COEFICIENT;
            if(newCapacity < _inserted + count)
                newCapacity = _inserted + count;

            if(newCapacity != _allocated)
            {
                Array tmp(newCapacity);
                tmp.Push(_array.Raw(), _inserted);
                swap(*this, tmp);
            }

            T* interArray = _array.Raw()+_inserted;
            int i = 0;
            for(i=0;i<count;i++,values++, interArray++){
                try
                {
                    new (interArray) T(*values);
                    _inserted++;
                }
                catch(...)
                {
                    while(i > 0)
                    {
                        --i;
                        _array[--_inserted].~T();
                    }
                    throw;
                }
            }
            return i;
        }

        /**
         * Swap elements at specific indexes.
         * The indexes are validated. In case of invalid indexes, {@code OutOfRange} exception is throwed.
         * @param FirstIndex Index of the first element
         * @param SecondIndex Index of the second element
         */
        void Swap(int FirstIndex, int SecondIndex)
        {
            if (FirstIndex < 0 || FirstIndex >= _inserted)
                throw OutOfRangeException("The index of the first element is not valid", __LINE__);
            if(SecondIndex < 0 || SecondIndex >= _inserted)
                throw OutOfRangeException("The index of the second element is not valid", __LINE__);

            if(FirstIndex == SecondIndex)
                return;

            using Templates::swap;
            swap(_array[FirstIndex], _array[SecondIndex]);
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
