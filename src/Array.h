#ifndef TEMPLATES_ARRAY_H
#define TEMPLATES_ARRAY_H

#include "Basis.h"
#include "Meta.h"
#include "UniquePointer.h"
#include "Exceptions.h"

namespace Templates
{
    /**
     * Class that represents dynamic array.
     * @tparam T Type to store
     */
    template<typename T>
    class Array
    {
    private:
        UniquePointer<T, __deleterWithoutDestruction<T>> _array;
        unsigned int _allocated{};
        unsigned int _size{};

        template<int EXPAND = 2>
        void SpliceCommon(unsigned int position, unsigned int to_delete, unsigned int to_insert);
    public:
        using ConstIterator = const T*;
        using Iterator = T*;

        //region lifetime
        /**
         * Create new empty array, where no memory is allocated.
         */
        Array() noexcept;
        /**
         * Create new array with no elements by `capacity` allocated memory.
         * @param capacity Capacity to allocate.
         */
        explicit Array(unsigned int capacity);
        /**
         * Create new array with `count` elements from the `elements` parameter by copying them.
         * @param elements Array of elements to insert.
         * @param count Number of elements to insert.
         */
        Array(T const* elements, unsigned int count);
        /**
         * Create new array with `count` elements from the `elements` parameter by moving them.
         * The array is not deleted and the calling procedure needs to manage the memory.
         * @param elements Array of elements to insert.
         * @param count Number of elements to insert.
         */
        Array(T*&& elements, unsigned int count);
        /**
         * Copy constructor.
         */
        Array(const Array&);
        /**
         * Movable constructor.
         */
        Array(Array&&) noexcept;
        /**
         * Copy assignable operator.
         */
        Array<T>& operator=(const Array&);
        /**
         * Move assignable operator.
         */
        Array<T>& operator=(Array&&) noexcept;
        /**
         * Destructor.
         */
        ~Array();
        //endregion

        //region swap
        /**
         * Swap elements at indexes.
         * @param first_index Index of the first element.
         * @param second_index Index of the second element.
         */
        void Swap(unsigned int first_index, unsigned int second_index);
        /**
         * Swap this instance with different one.
         * @param NewArray Instance to swap with.
         */
        void Swap(Array&) noexcept;
        //endregion

        //region queries
        /**
         * Returns number of elements inserted into the array.
         * @return Number of elements in array.
         */
        inline unsigned int Size() const noexcept;
        /**
         * Get how many elements can fit into container without reallocating.
         * @return Capacity of the array.
         */
        inline unsigned int Capacity() const noexcept;
        /**
         * Check if the array is empty.
         * @return True if the array is empty, false otherwise.
         */
        inline bool Empty() const noexcept;
        /**
         * Cast array to pointer.
         */
        explicit operator T*() noexcept;
        /**
         * Cast const array to const pointer.
         */
        explicit operator T const* const() const noexcept;
        /**
         * Cast array to pointer.
         */
        T* Raw() noexcept;
        /**
         * Cast const array to const pointer.
         */
        T const* const Raw() const noexcept;
        /**
         * Get const element at `index` in the array.
         * @param index Index of the element.
         * @return Const element at index `index`.
         */
        const T& operator[](unsigned int index) const;
        /**
         * Get const element at `index` in the array.
         * @param index Index of the element.
         * @return Const element at index `index`.
         */
        T& operator[](unsigned int index);
        //endregion

        //region resizing
        /**
         * Resize array to new capacity.
         * When new capacity is lower than the size, elements from the end of the array are destructed.
         * @param new_capacity New capacity of the array.
         * @return New capacity of the array.
         */
        unsigned int Resize(unsigned int new_capacity);
        /**
         * Resize array by `resize_by` parameter. For negative values the array will be shrinking.
         * When new capacity is lower than the size, elements from the end of the array are destructed.
         * @param resize_by Amount of resize.
         * @return New capacity of the array.
         */
        unsigned int ResizeBy(int resize_by);
        /**
         * Shrink the array so capacity would be equal to size.
         * @return New capacity of the array.
         */
        unsigned int ShrinkToFit();
        //endregion

        //region slicing
        /**
         * From the position `position`, remove `to_delete` elements and then insert `to_insert` elements (by copy) from `elements` array.
         * If size of inserted elements is higher then number of deleted elements, the array is shifted (as well as the other way around).
         * @param position Position where to delete and insert elements.
         * @param to_delete Number of elements to delete.
         * @param elements Array of elements to insert.
         * @param to_insert Number of elements to insert.
         */
        void Splice(unsigned int position, unsigned int to_delete, T const* elements, unsigned int to_insert);
        /**
         * From the position `position`, remove `to_delete` elements.
         * If size of inserted elements is higher then number of deleted elements, the array is shifted (as well as the other way around).
         * @param position Position where to delete and insert elements.
         * @param to_delete Number of elements to delete..
         */
        void Splice(unsigned int position, unsigned int to_delete);
        /**
         * From the position `position`, insert `to_insert` elements (by copy) from `elements` array.
         * If size of inserted elements is higher then number of deleted elements, the array is shifted (as well as the other way around).
         * @param position Position where to delete and insert elements.
         * @param elements Array of elements to insert.
         * @param to_insert Number of elements to insert.
         */
        void Splice(unsigned int position, T const* elements, unsigned int to_insert);
        /**
         * From the position `position`, remove `to_delete` elements and then insert `to_insert` elements (by copy) from `elements` array.
         * If size of inserted elements is higher then number of deleted elements, the array is shifted (as well as the other way around).
         * The array needs to be managed by the calling procedure.
         * @param position Position where to delete and insert elements.
         * @param to_delete Number of elements to delete.
         * @param elements Array of elements to insert.
         * @param to_insert Number of elements to insert.
         */
        void Splice(unsigned int position, unsigned int to_delete, T*&& elements, unsigned int to_insert);
        /**
         * From the position `position`, insert `to_insert` elements (by move) from `elements` array.
         * If size of inserted elements is higher then number of deleted elements, the array is shifted (as well as the other way around).
         * The array needs to be managed by the calling procedure.
         * @param position Position where to delete and insert elements.
         * @param elements Array of elements to insert.
         * @param to_insert Number of elements to insert.
         */
        void Splice(unsigned int position, T*&& elements, unsigned int to_insert);
        //endregion

        //region inserting
        /**
         * Insert element at the end of the array.
         * @param element Element to insert.
         * @return Number of inserted elements.
         */
        unsigned int Push(const T& element);
        /**
         * Insert element at the end of the array.
         * @param element Element to insert.
         * @return Number of inserted elements.
         */
        unsigned int Push(T&& element);
        /**
         * Insert `count` elements from the `elements` array to the end of the array.
         * @param elements Elements to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
         */
        unsigned int Push(T const* elements, unsigned int count);
        /**
         * Insert `count` elements from the `elements` array to the end of the array.
         * @param elements Elements to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
         */
        unsigned int Push(T*&& elements, unsigned int count);
        /**
         * Insert element at the beginning of the array.
         * @param element Element to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(const T& element);
        /**
         * Insert element at the beginning of the array.
         * @param element Element to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(T&& element);
        /**
         * Insert `count` elements from the `elements` array to the beginning of the array.
         * @param elements Elements to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(T const* elements, unsigned int count);
        /**
         * Insert `count` elements from the `elements` array to the beginning of the array.
         * @param elements Elements to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(T*&& elements, unsigned int count);
        /**
         * Insert element `element` at position `position` by copy.
         * @param position Position where to insert element.
         * @param element Element to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(unsigned int position, const T& element);
        /**
         * Insert `count` elements from `element` array at position `position` by copy.
         * @param position Position where to insert element.
         * @param elements Elements to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
        */
        unsigned int Insert(unsigned int position, T const * elements, unsigned int count);
        /**
         * Insert element `element` at position `position` by move.
         * @param position Position where to insert element.
         * @param element Element to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(unsigned int position, T&& element);
        /**
         * Insert `count` elements from `element` array at position `position` by move.
         * @param position Position where to insert element.
         * @param elements Elements to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
        */
        unsigned int Insert(unsigned int position, T* &&elements, unsigned int count);
        //endregion

        //region deleting
        /**
         * Delete all the elements in the array. The capacity remain unchanged.
         * @return Number of deleted elements.
         */
        inline unsigned int Clear();
        /**
         * Delete all the elements in the array. The capacity remain unchanged.
         * @return Number of deleted elements.
         */
        inline unsigned int Delete();
        /**
         * Delete `count` elements from the array.
         * For positive parameter returns elements from the beginning, for negative one from the end.
         * @param count Number of elements to delete.
         * @return Number of deleted elements.
         */
        inline unsigned int Delete(int count);
        /**
         * Delete all elements between `from` (included) and `to` (excluded).
         * @param from Index of the first element to delete.
         * @param to Index of the first element NOT TO DELETE.
         * @return Number of deleted elements.
         */
        unsigned int Delete(unsigned int from, unsigned int to);
        //endregion

        //region iterators
        /**
         * Returns iterator to the beginning of the array.
         * @return Iterator to the beginning of the array.
         */
        ConstIterator Begin() const noexcept;
        /**
         * Returns iterator to the end of the array.
         * @return Iterator to the end of the array.
         */
        ConstIterator End() const noexcept;
        /**
         * Returns iterator at the position in the array.
         * @return Iterator to the end of the array.
         */
        ConstIterator At(unsigned int position) const noexcept;
        /**
         * Returns iterator to the beginning of the array.
         * @return Iterator to the beginning of the array.
         */
        Iterator Begin() noexcept;
        /**
         * Returns iterator to the end of the array.
         * @return Iterator to the end of the array.
         */
        Iterator End() noexcept;
        /**
         * Returns iterator at the position in the array.
         * @return Iterator to the end of the array.
         */
        Iterator At(unsigned int position) noexcept;
        //endregion
    };

    /**
     * Swap two instances of the array
     * @param first First array
     * @param second Second array
     */
    template<typename T>
    void swap(Array<T>& first, Array<T>& second)
    {
        first.Swap(second);
    }

    //region implementation
    template<typename T>
    Array<T>::Array() noexcept : _array(nullptr), _allocated(0), _size(0)
    {}

    template<typename T>
    Array<T>::Array(unsigned int capacity): _array(malloc_own<T>(capacity)), _allocated(capacity), _size(0)
    {}

    template<typename T>
    Array<T>::Array(T const* elements, unsigned int count): Array(count)
    {
        Splice(0, elements, count);
    }

    template<typename T>
    Array<T>::Array(T*&& elements, unsigned int count): Array(count)
    {
        Splice(0, move(elements), count);
    }

    template<typename T>
    Array<T>::Array(const Array& arr): Array(arr.Raw(), arr.Size())
    {}

    template<typename T>
    Array<T>::Array(Array&& arr) noexcept : Array()
    {
        Swap(arr);
    }

    template<typename T>
    void Array<T>::Swap(Array& arr) noexcept
    {
        using Templates::swap;
        swap(_array, arr._array);
        swap(_size, arr._size);
        swap(_allocated, arr._allocated);
    }

    template<typename T>
    void Array<T>::Swap(unsigned int first_index, unsigned int second_index)
    {
        using Templates::swap;
        if(first_index > Size() || second_index > Size())
            throw OutOfRangeException("Cant swap values out of the array", __LINE__);
        swap(*(Raw() + first_index), *(Raw() + second_index));
    }

    template<typename T>
    Array<T>& Array<T>::operator=(const Array& arr)
    {
        if (this == &arr)
            return *this;

        Array<T> tmp(arr);
        swap(*this, tmp);
        return *this;
    }

    template<typename T>
    Array<T>& Array<T>::operator=(Array&& arr) noexcept
    {
        if (this == &arr)
            return *this;

        Array<T> tmp(move(arr));
        swap(*this, tmp);
        return *this;
    }

    template<typename T>
    void Array<T>::Splice(unsigned int position, T*&& elements, unsigned int to_insert)
    {
        return Splice(position, 0, move(elements), to_insert);
    }

    template<typename T>
    void Array<T>::Splice(unsigned int position, unsigned int to_delete)
    {
        return Splice(position, to_delete, static_cast<T const *>(nullptr), 0);
    }

    template<typename T>
    void Array<T>::Splice(unsigned int position, T const* elements, unsigned int to_insert)
    {
        return Splice(position, 0, elements, to_insert);
    }

    template<typename T>
    void Array<T>::Splice(unsigned int position, unsigned int to_delete, T const* elements, unsigned int to_insert)
    {
        if(position > Size())
            throw OutOfRangeException("Position is bigger than size of the array", __LINE__);
        SpliceCommon(position, to_delete, to_insert);
        T const* start = elements, * end = elements + to_insert;
        T* arr = Raw() + position;
        for (; start != end; start++, arr++, _size++)
            new(arr) T(*start);
    }

    template<typename T>
    void Array<T>::Splice(unsigned int position, unsigned int to_delete, T*&& elements, unsigned int to_insert)
    {
        if(position > Size())
            throw OutOfRangeException("Position is bigger than size of the array", __LINE__);
        SpliceCommon(position, to_delete, to_insert);
        T const* start = elements, * end = elements + to_insert;
        T* arr = Raw() + position;
        for (; start != end; start++, arr++, _size++)
            new (arr) T((T&&)*start);
    }

    template<typename T>
    template<int EXPAND>
    void Array<T>::SpliceCommon(unsigned int position, unsigned int to_delete, unsigned int to_insert)
    {
        to_delete = position + to_delete > Size() ? Size() - position : to_delete;
        unsigned int remain_after = Size() - position - to_delete;
        //check if it fit
        if (position + remain_after + to_insert > Capacity())
        {
            unsigned int new_capacity =
                    position + remain_after + to_insert > EXPAND * Capacity() ? position + remain_after + to_insert :
                    EXPAND * Capacity();
            Resize(new_capacity);
        }
        //delete elements
        T* del = Raw() + position, *end = Raw() + position + to_delete;
        for (; del != end; del++, _size--)
            del->~T();
        //move elements
        T* move_from = Raw() + position + to_delete, *move_from_end = Raw() + position + to_delete + remain_after;
        T* move_to = Raw() + position + to_insert;
        if(move_from == move_to)
            return;
        signed char step = move_to < move_from ? 1 : -1;
        if(move_to > move_from)
        {
            swap(move_from, move_from_end);
            move_from--;
            move_from_end--;
            move_to += remain_after;
            move_to--;
        }
        for (; move_from != move_from_end; move_from += step, move_to += step)
        {
            fastest_init(move_to, *move_from);
            move_from->~T();
        }
    }

    template<typename T>
    Array<T>::~Array()
    {
        T* start = Raw(), *end = Raw() + Size();
        for(;start != end; start++)
            start->~T();
        _size = 0;
    }

    template<typename T>
    unsigned int Array<T>::Size() const noexcept
    {
        return _size;
    }

    template<typename T>
    unsigned int Array<T>::Capacity() const noexcept
    {
        return _allocated;
    }

    template<typename T>
    bool Array<T>::Empty() const noexcept
    {
        return Size() == 0;
    }

    template<typename T>
    Array<T>::operator T*() noexcept
    {
        return Raw();
    }

    template<typename T>
    Array<T>::operator T const* const() const noexcept
    {
        return Raw();
    }

    template<typename T>
    T* Array<T>::Raw() noexcept
    {
        return _array.Raw();
    }

    template<typename T>
    T const* const Array<T>::Raw() const noexcept
    {
        return _array.Raw();
    }

    template<typename T>
    const T& Array<T>::operator[](unsigned int index) const
    {
        if(index >= Size())
            throw OutOfRangeException("Index is out of range for this Array", __LINE__);
        return *(Raw() + index);
    }

    template<typename T>
    T& Array<T>::operator[](unsigned int index)
    {
        if(index >= Size())
            throw OutOfRangeException("Index is out of range for this Array", __LINE__);
        return *(Raw() + index);
    }

    template<typename T>
    unsigned int Array<T>::ShrinkToFit()
    {
        return Resize(Size());
    }

    template<typename T>
    unsigned int Array<T>::ResizeBy(int resize_by)
    {
        return Resize(max((int)Capacity() + resize_by, 0));
    }

    template<typename T>
    unsigned int Array<T>::Resize(unsigned int new_capacity)
    {
        Array tmp(new_capacity);
        T* data = Raw();
        tmp.Splice(0, move(data), min(Size(), new_capacity));
        swap(*this, tmp);
        return Capacity();
    }

    template<typename T>
    typename Array<T>::ConstIterator Array<T>::Begin() const noexcept
    {
        return Raw();
    }

    template<typename T>
    typename Array<T>::Iterator Array<T>::Begin() noexcept
    {
        return Raw();
    }

    template<typename T>
    typename Array<T>::ConstIterator Array<T>::End() const noexcept
    {
        return Raw() + Size();
    }

    template<typename T>
    typename Array<T>::Iterator Array<T>::End() noexcept
    {
        return Raw() + Size();
    }

    template<typename T>
    typename Array<T>::ConstIterator Array<T>::At(unsigned int position) const noexcept
    {
        return Raw() + position;
    }

    template<typename T>
    typename Array<T>::Iterator Array<T>::At(unsigned int position) noexcept
    {
        return Raw() + position;
    }

    template<typename T>
    unsigned int Array<T>::Push(const T& element)
    {
        return Push(&element, 1);
    }

    template<typename T>
    unsigned int Array<T>::Push(T&& element)
    {
        return Push(static_cast<T*&&>(&element), 1);
    }

    template<typename T>
    unsigned int Array<T>::Push(T const* elements, unsigned int count)
    {
        unsigned int old_size = Size();
        Splice(Size(), elements, count);
        return Size() - old_size;
    }

    template<typename T>
    unsigned int Array<T>::Push(T*&& elements, unsigned int count)
    {
        unsigned int old_size = Size();
        Splice(Size(), move(elements), count);
        return Size() - old_size;
    }

    template<typename T>
    unsigned int Array<T>::Insert(const T& element)
    {
        return Insert(&element, 1);
    }

    template<typename T>
    unsigned int Array<T>::Insert(T&& element)
    {
        return Insert(static_cast<T*&&>(&element), 1);
    }

    template<typename T>
    unsigned int Array<T>::Insert(T const* elements, unsigned int count)
    {
        unsigned int old_size = Size();
        Splice(0, elements, count);
        return Size() - old_size;
    }

    template<typename T>
    unsigned int Array<T>::Insert(T*&& elements, unsigned int count)
    {
        unsigned int old_size = Size();
        Splice(0, move(elements), count);
        return Size() - old_size;
    }

    template<typename T>
    inline unsigned int Array<T>::Clear()
    {
        return Delete();
    }

    template<typename T>
    inline unsigned int Array<T>::Delete()
    {
        return Delete(Size());
    }

    template<typename T>
    inline unsigned int Array<T>::Delete(int count)
    {
        unsigned int from = 0;
        unsigned int to = count;
        if(count < 0)
        {
            from = (unsigned int)-count > Size() ? 0 : Size() + count;
            to = min((unsigned int)-count, Size());
        }
        return Delete(from, to);
    }

    template<typename T>
    unsigned int Array<T>::Delete(unsigned int from, unsigned int to)
    {
        unsigned int old_size = Size();
        if(from > to){
            swap(from, to);
            from++;
            to++;
        }
        Splice(from, to - from);
        return old_size - Size();
    }

    template<typename T>
    unsigned int Array<T>::Insert(unsigned int position, const T& element)
    {
        return Insert(position, &element, 1);
    }

    template<typename T>
    unsigned int Array<T>::Insert(unsigned int position, T const* elements, unsigned int count)
    {
        unsigned int old_size = Size();
        Splice(position, 0, elements, count);
        return Size() - old_size;
    }

    template<typename T>
    unsigned int Array<T>::Insert(unsigned int position, T&&element)
    {
        return Insert(position, (T*&&)&element, 1);
    }

    template<typename T>
    unsigned int Array<T>::Insert(unsigned int position, T* &&elements, unsigned int count)
    {
        unsigned int old_size = Size();
        Splice(position, 0, move(elements), count);
        return Size() - old_size;
    }
    //endregion
}

#endif //TEMPLATES_ARRAY_H
