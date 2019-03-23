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

        int _allocated;
        int _inserted;
        UniquePointer<T, __deleterWithoutDestruction<T>> _array;

    public:

        using Iterator = T*;
        using ConstIterator = const T*;

        /**
         * Initialize new instance with default size.
         */
        Array() noexcept: Array(BASE_SIZE)
        {}

        /**
         * Initialize new instance with provided size.
         * @param capacity Capacity of the created array.
         */
        explicit Array(int capacity) noexcept : _allocated(0), _inserted(0), _array(nullptr)
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
         * Move constructor, initialize Array from the values of other array.
         * The second instance will be cleared.
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
         * Destructor.
         * Is exception safe if the containing object does not throw exception in the destructor.
         */
        ~Array() noexcept
        {
            for (; _inserted > 0;)
                _array[--_inserted].~T();
        }

        /**
         * Copy all elements from second array to this one.
         * Entities from the second array are copied.
         */
        Array& operator=(const Array& second)
        {
            if (this == &second)
                return *this;

            Array tmp(second._array.Raw(), second.Size());
            swap(*this, tmp);

            return *this;
        }

        /**
         * Move all elements from the second array to this one.
         * Second array is cleared.
         */
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
         * Get number of elements in the array.
         * @return Number of elements in the array.
         */
        int Size() const noexcept
        {
            return _inserted;
        }

        /**
         * Return allocated capacity of the array.
         * @return Allocated capacity of the array.
         */
        int Capacity() const noexcept
        {
            return _allocated;
        }

        /**
         * Check if is array empty.
         * @return True if is array empty, false otherwise.
         */
        bool IsEmpty() const noexcept
        {
            return this->Size() == 0;
        }

        /**
        * Return element at @i-th index.
        * Throw exception, if is index out of range
        */
        T& operator[](int i)
        {
            if (i >= _inserted || i < 0)
                throw OutOfRangeException("Operator is out of array range", __LINE__);

            return _array[i];
        }

        /**
         * Return element at @i-th index.
         * Throw exception, if is index out of range
         */
        const T& operator[](int i) const
        {
            if (i >= _inserted || i < 0)
                throw OutOfRangeException("Operator is out of array range", __LINE__);

            return _array[i];
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
         * Delete {@code count} elements from the beginning.
         * @param count How many elements delete
         */
        void Delete(int count)
        {
            this->DeleteFromBegin(count);
        }

        /**
         * Delete {@code count} elements from the beginning.
         * Safe version make sure, that the array remains valid if exception occurs.
         * Safe version needs more memory than the unsafe one.
         * @param count How many elements delete
         */
        void DeleteSafe(int count)
        {
            this->DeleteFromBeginSafe(count);
        }

        /**
         * Delete {@code count} elements from the {@code index}.
         * @param index From which element delete
         * @param count How many elements delete
         */
        void Delete(int index, int count)
        {
            this->Splice(index, count);
        }

        /**
         * Delete {@code count} elements from the {@code index}.
         * Safe version make sure, that the array remains valid if exception occurs.
         * Safe version needs more memory than the unsafe one.
         * @param index From which element delete
         * @param count How many elements delete
         */
        void DeleteSafe(int index, int count)
        {
            this->SpliceSafe(index, count);
        }

        /**
         * Delete {@code count} elements from the end.
         * In case of exception, the array stays in valid state, but the state can change.
         * @param count Number of elements to delete
         */
        void DeleteFromEnd(int count)
        {
            count = max(count, 0);
            this->Delete(max(0, _inserted-count), count);
        }

        /**
         * Delete {@code count} elements from the end.
         * In case of exception, the array stays in the old state.
         * Safe version needs more memory than the unsafe one.
         * @param count Number of elements to delete
         */
        void DeleteFromEndSafe(int count)
        {
            count = max(count, 0);
            this->DeleteSafe(max(0, _inserted-count), count);
        }

        /**
         * Delete {@code count} elements from the beginning of the array.
         * In case the of exception, the array may stay in invalid state.
         * @param count Number of elements to delete
         */
        void DeleteFromBegin(int count)
        {
            return this->Delete(0, count);
        }

        /**
         * Delete {@code count} elements from the beginning of the array.
         * In case the destuctor throws a exception, the array stay in valid state.
         * Safe method needs more memory than the unsafe one.
         * @param count Number of elements to delete
         */
        void DeleteFromBeginSafe(int count)
        {
            return this->DeleteSafe(0, count);
        }

        /**
         * Delete all the elements in the array, but the allocated capacity stay.
         */
        void Delete()
        {
            return this->Delete(0, _inserted);
        }

        /**
         * Delete all elements in the array, but the allocated capacity stay.
         * Safe version make sure, that the array remain valid if exception occurs.
         * Safe version require more space than the unsafe one.
         */
        void DeleteSafe()
        {
            this->DeleteSafe(0, _inserted);
        }

        /**
         * Delete elements at the specific position.
         * @param index Index where start deleting the elements.
         * @param elements_to_delete Number of elements to delete.
         */
        void Splice(int index, int elements_to_delete)
        {
            this->Splice(index, elements_to_delete, nullptr, 0);
        }

        /**
         * Delete elements at the specific position.
         * Safe version of method make sure that the array is not changed in case of exception.
         * Safe version needs more memory and is slower then the unsafe version.
         * @param index Index where start deleting the elements.
         * @param elements_to_delete Number of elements to delete.
         */
        void SpliceSafe(int index, int elements_to_delete)
        {
            this->SpliceSafe(index, elements_to_delete, nullptr, 0);
        }

        /**
         * Insert elements at the specific position.
         * @param index Index where to put the elements.
         * @param arr Array with the new elements
         * @param elements_to_insert How many elements insert to the array.
         */
        void Splice(int index, const T* arr, int elements_to_insert)
        {
            this->Splice(index, 0, arr, elements_to_insert);
        }

        /**
         * Insert elements at the specific position.
         * Safe version of method make sure that the array is not changed in case of exception.
         * Safe version needs more memory and is slower then the unsafe version.
         * @param index Index where to put the elements.
         * @param arr Array with the new elements
         * @param elements_to_insert How many elements insert to the array.
         */
        void SpliceSafe(int index, const T* arr, int elements_to_insert)
        {
            this->SpliceSafe(index, 0, arr, elements_to_insert);
        }

        /**
         * Method that can delete or/and add elements into array.
         *
         * First, the elements from the index will be removed.
         * Then, in place of the deleted items new elements are inserted.
         * If inserted array is smaller or bigger then the size of deleted sequence, then rest of the array will be moved left or right to fill the gab.
         * @param index Index where to delete or put the elements.
         * @param elements_to_delete How many elements delete.
         * @param arr Array with the new elements
         * @param elements_to_insert How many elements insert to the array.
         */
        void Splice(int index, int elements_to_delete, const T* arr, int elements_to_insert)
        {
            //TODO rewrite
            this->SpliceSafe(index, elements_to_delete, arr, elements_to_insert);
        }

        /**
         * Method that can delete or/and add elements into array.
         * Safe version of method make sure that the array is not changed in case of exception.
         * Safe version needs more memory and is slower then the unsafe version.
         *
         * First, the elements from the index will be removed.
         * Then, in place of the deleted items new elements are inserted.
         * If inserted array is smaller or bigger then the size of deleted sequence, then rest of the array will be moved left or right to fill the gab.
         * @param index Index where to delete or put the elements.
         * @param elements_to_delete How many elements delete.
         * @param arr Array with the new elements
         * @param elements_to_insert How many elements insert to the array.
         */
        void SpliceSafe(int index, int elements_to_delete, const T* arr, int elements_to_insert)
        {
            if(index < 0 || index > _inserted)
                throw OutOfRangeException("Index is out of range", __LINE__);

            elements_to_delete = max(elements_to_delete, 0);
            elements_to_delete = index + elements_to_delete > _inserted ? _inserted - index : elements_to_delete;
            elements_to_insert = max(elements_to_insert, 0);
            int to_allocate = _inserted - elements_to_delete + elements_to_insert;
            to_allocate = max(to_allocate, _allocated);

            Array tmp(to_allocate);
            tmp.Push(_array.Raw(), index);
            tmp.Push(arr, elements_to_insert);
            tmp.Push(_array.Raw() + index + elements_to_delete, _inserted - elements_to_delete - index);

            swap(*this, tmp);
        }

        /**
         * Insert element at the specific index.
         * Other elements are shifted right.
         * In case the copy constructor throws a exception, the array may stay in invalid state.
         * The index is validated, but you can use this method to insert element at the end of the array.
         * @param index Position where to put the element.
         * @param element Element to insert.
         */
        void Insert(int index, const T& element)
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
         */
        void Insert(int position, const T* elements, int count)
        {
            this->Splice(position, elements, count);
        }

        /**
         * Insert element at the specific index.
         * Other elements are shifted right.
         * In case the copy constructor throws a exception, the stay in valid state.
         * The safe version needs more space than the unsafe one.
         * The index is validated, but you can use this method to insert element at the end of the array.
         * @param index Position where to put the element.
         */
        void InsertSafe(int position, const T& element)
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
         */
        void InsertSafe(int position, const T* elements, int count)
        {
            this->SpliceSafe(position, elements, count);
        }



        //TODO implement emplace



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
         * Insert element to the end of the array
         * @param value Element to insert
         */
        void Push(const T& value)
        {
            this->Push(&value, 1);
        }

        /**
         * Push elements to the end of the array
         * @param values Elements to push
         * @param count Number of elements to push
         */
        void Push(const T * values, int count)
        {
            int newCapacity = _allocated;
            if(newCapacity < _inserted + count)
                newCapacity *= EXPANDING_COEFICIENT;
            if(newCapacity < _inserted + count)
                newCapacity = _inserted + count;

            if(newCapacity != _allocated)
                this->Resize(newCapacity);

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
        }

        /**
         * Move element to the end of the array
         * @param value Element to insert
         */
        void Push(T&& value)
        {
            using Templates::move;
            this->Push(&value, 1);
        }

        /**
         * Move elements to the end of the array.
         * Doesn't move the array but the values itself, array still needs to be destroyed after the call.
         * @param values Elements to push.
         * @param count Number of elements to push.
         */
        void Push(T* &&values, int count)
        {
            using Templates::move;
            int newCapacity = _allocated;
            if(newCapacity < _inserted + count)
                newCapacity *= EXPANDING_COEFICIENT;
            if(newCapacity < _inserted + count)
                newCapacity = _inserted + count;

            if(newCapacity != _allocated)
                this->Resize(newCapacity);

            T* interArray = _array.Raw()+_inserted;
            int i = 0;
            for(i=0;i<count;i++,values++, interArray++){
                try
                {
                    new (interArray) T(move(*values));
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

        /**
         * Swaps to instances of the array
         */
        void Swap(Array &second) noexcept {
            using Templates::swap;
            swap(_allocated, second._allocated);
            swap(_inserted, second._inserted);
            swap(_array, second._array);
        }

        /**
         * Get iterator at the beginning of the array.
         */
        Iterator Begin() noexcept
        {
            return _array.Raw();
        }

        /**
         * Get iterator at the end of the array.
         * The iterator is not valid, it points one element after the end of the array.
         */
        Iterator End() noexcept
        {
            return _array.Raw() + _inserted;
        }

        /**
         * Get iterator at the beginning of the array.
         */
        ConstIterator Begin() const noexcept
        {
            return _array.Raw();
        }

        /**
         * Get iterator at the end of the array.
         * The iterator is not valid, it points one element after the end of the array.
         */
        ConstIterator End() const noexcept
        {
            return _array.Raw() + _inserted;
        }

    };

    /**
     * Swap two instances of the array
     * @param first First array
     * @param second Second array
     */
    template<typename T>
    void swap(Array<T>& first,Array<T>& second)
    {
        first.Swap(second);
    }
}

#endif //TEMPLATES_ARRAY_H_H
