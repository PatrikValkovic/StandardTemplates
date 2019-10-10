#ifndef TEMPLATES_NEWARRAY_H
#define TEMPLATES_NEWARRAY_H

#include "Basis.h"
#include "Meta.h"
#include "UniquePointer.h"

namespace Templates
{
    /**
     * Class that represents dynamic array.
     * @tparam T Type to store
     */
    template<typename T>
    class NewArray
    {
    private:
        unsigned int _allocated{};
        unsigned int _size{};
        UniquePointer<T, __deleterWithoutDestruction<T>> _array;

        template<int EXPAND = 2>
        void SpliceCommon(unsigned int position, unsigned int to_delete, unsigned int to_insert);
    public:
        using ConstIterator = const T*;
        using Iterator = T*;

        //region lifetime
        /**
         * Create new empty array, where no memory is allocated.
         */
        NewArray() noexcept;
        /**
         * Create new array with no elements by `capacity` allocated memory.
         * @param capacity Capacity to allocate.
         */
        explicit NewArray(int capacity);
        /**
         * Create new array with `count` elements from the `elements` parameter by copying them.
         * @param elements Array of elements to insert.
         * @param count Number of elements to insert.
         */
        NewArray(T const* elements, unsigned int count);
        /**
         * Create new array with `count` elements from the `elements` parameter by moving them.
         * The array is not deleted and the calling procedure needs to manage the memory.
         * @param elements Array of elements to insert.
         * @param count Number of elements to insert.
         */
        NewArray(T*&& elements, unsigned int count);
        /**
         * Copy constructor.
         */
        NewArray(const NewArray&);
        /**
         * Movable constructor.
         */
        NewArray(NewArray&&) noexcept;
        /**
         * Copy assignable operator.
         */
        NewArray<T>& operator=(const NewArray&);
        /**
         * Move assignable operator.
         */
        NewArray<T>& operator=(NewArray&&) noexcept;
        /**
         * Destructor.
         */
        ~NewArray();
        //endregion

        //region swap
        /**
         * Swap elements at indexes.
         * @param FirstIndex Index of the first element.
         * @param SecondIndex Index of the second element.
         */
        void Swap(unsigned int FirstIndex, unsigned int SecondIndex);
        /**
         * Swap this instance with different one.
         * @param NewArray Instance to swap with.
         */
        void Swap(NewArray&) noexcept;
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
        const T& operator[](unsigned int index) const noexcept;
        /**
         * Get const element at `index` in the array.
         * @param index Index of the element.
         * @return Const element at index `index`.
         */
        T& operator[](unsigned int index) noexcept;
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
    void swap(NewArray<T>& first, NewArray<T>& second)
    {
        first.Swap(second);
    }

    //region implementation
    template<typename T>
    NewArray<T>::NewArray() noexcept : _array(nullptr), _allocated(0), _size(0)
    {}

    template<typename T>
    NewArray<T>::NewArray(int capacity): _array(::operator new(sizeof(T) * capacity)), _allocated(capacity), _size(0)
    {}

    template<typename T>
    NewArray<T>::NewArray(T const* elements, unsigned int count): NewArray(count)
    {
        this->Splice(0, elements, count);
    }

    template<typename T>
    NewArray<T>::NewArray(T*&& elements, unsigned int count): NewArray(count)
    {
        this->Splice(0, move(elements), count);
    }

    template<typename T>
    NewArray<T>::NewArray(const NewArray& arr): NewArray(arr.Raw(), arr.Size())
    {}

    template<typename T>
    NewArray<T>::NewArray(NewArray&& arr) noexcept : NewArray()
    {
        Swap(arr);
    }

    template<typename T>
    void NewArray<T>::Swap(NewArray& arr) noexcept
    {
        using Templates::swap;
        swap(_array, arr._array);
        swap(_size, arr._size);
        swap(_allocated, arr._allocated);
    }

    template<typename T>
    void NewArray<T>::Swap(unsigned int FirstIndex, unsigned int SecondIndex)
    {
        using Templates::swap;
        swap(*(_array + FirstIndex), *(_array + SecondIndex));
    }

    template<typename T>
    NewArray<T>& NewArray<T>::operator=(const NewArray& arr)
    {
        if (this == &arr)
            return *this;

        NewArray<T> tmp(arr);
        swap(*this, tmp);
        return *this;
    }

    template<typename T>
    NewArray<T>& NewArray<T>::operator=(NewArray&& arr) noexcept
    {
        if (this == &arr)
            return *this;

        NewArray<T> tmp(move(arr));
        swap(*this, tmp);
        return *this;
    }

    template<typename T>
    void NewArray<T>::Splice(unsigned int position, T*&& elements, unsigned int to_insert)
    {
        return Splice(position, 0, move(elements), to_insert);
    }

    template<typename T>
    void NewArray<T>::Splice(unsigned int position, unsigned int to_delete)
    {
        return Splice(position, to_delete, nullptr, 0);
    }

    template<typename T>
    void NewArray<T>::Splice(unsigned int position, T const* elements, unsigned int to_insert)
    {
        return Splice(position, 0, elements, to_insert);
    }

    template<typename T>
    void NewArray<T>::Splice(unsigned int position, unsigned int to_delete, T const* elements, unsigned int to_insert)
    {
        SpliceCommon(position, to_delete, to_insert);
        T const* start = elements, * end = elements + to_insert;
        T* arr = this->_array + position;
        for (; start != end; start++, arr++)
            new(arr) T(*start);
    }

    template<typename T>
    void NewArray<T>::Splice(unsigned int position, unsigned int to_delete, T*&& elements, unsigned int to_insert)
    {
        SpliceCommon(position, to_delete, to_insert);
        T const* start = elements, * end = elements + to_insert;
        T* arr = this->_array + position;
        for (; start != end; start++, arr++)
            new(arr) T(move(*start));
    }

    template<typename T>
    template<int EXPAND>
    void NewArray<T>::SpliceCommon(unsigned int position, unsigned int to_delete, unsigned int to_insert)
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
        T* del = Raw() + position, end = Raw() + position + to_delete;
        for (; del != end; del++)
            del->~T();
        //move elements
        T* move_from = Raw() + position + to_delete, move_from_end = Raw() + Size();
        T* move_to = Raw() + position + to_insert;
        unsigned char step = move_to < move_from ? 1 : -1;
        move_to < move_from ? 0 : swap(move_from, move_to);
        for (; move_from != move_to; move_from += step, move_to += step)
        {
            fastest_init(move_to, *move_from);
            move_from->~T();
        }
    }

    template<typename T>
    NewArray<T>::~NewArray()
    {
        T* start = Raw(), end = Raw() + Size();
        for(;start != end; start++)
            start->~T();
        _size = 0;
    }

    template<typename T>
    unsigned int NewArray<T>::Size() const noexcept
    {
        return _size;
    }

    template<typename T>
    unsigned int NewArray<T>::Capacity() const noexcept
    {
        return _allocated;
    }

    template<typename T>
    bool NewArray<T>::Empty() const noexcept
    {
        return Size() == 0;
    }

    template<typename T>
    NewArray<T>::operator T*() noexcept
    {
        return Raw();
    }

    template<typename T>
    NewArray<T>::operator T const* const() const noexcept
    {
        return Raw();
    }

    template<typename T>
    T* NewArray<T>::Raw() noexcept
    {
        return _array;
    }

    template<typename T>
    T const* const NewArray<T>::Raw() const noexcept
    {
        return _array;
    }

    template<typename T>
    const T& NewArray<T>::operator[](unsigned int index) const noexcept
    {
        return *(_array + index);
    }

    template<typename T>
    T& NewArray<T>::operator[](unsigned int index) noexcept
    {
        return *(_array + index);
    }

    template<typename T>
    unsigned int NewArray<T>::ShrinkToFit()
    {
        return Resize(Size());
    }

    template<typename T>
    unsigned int NewArray<T>::ResizeBy(int resize_by)
    {
        return Resize(max((int)Capacity() + resize_by, 0));
    }

    template<typename T>
    unsigned int NewArray<T>::Resize(unsigned int new_capacity)
    {
        NewArray tmp(new_capacity);
        tmp.Splice(0, Raw(), Size());
        swap(*this, tmp);
        return Capacity();
    }

    template<typename T>
    typename NewArray<T>::ConstIterator NewArray<T>::Begin() const noexcept
    {
        return Raw();
    }

    template<typename T>
    typename NewArray<T>::Iterator NewArray<T>::Begin() noexcept
    {
        return Raw();
    }

    template<typename T>
    typename NewArray<T>::ConstIterator NewArray<T>::End() const noexcept
    {
        return Raw() + Size();
    }

    template<typename T>
    typename NewArray<T>::Iterator NewArray<T>::End() noexcept
    {
        return Raw() + Size();
    }

    template<typename T>
    typename NewArray<T>::ConstIterator NewArray<T>::At(unsigned int position) const noexcept
    {
        return Raw() + position;
    }

    template<typename T>
    typename NewArray<T>::Iterator NewArray<T>::At(unsigned int position) noexcept
    {
        return Raw() + position;
    }

    template<typename T>
    unsigned int NewArray<T>::Push(const T& element)
    {
        return Push(&element, 1);
    }

    template<typename T>
    unsigned int NewArray<T>::Push(T&& element)
    {
        return Push(static_cast<T*&&>(&element), 1);
    }

    template<typename T>
    unsigned int NewArray<T>::Push(T const* elements, unsigned int count)
    {
        unsigned int old_size = Size();
        Splice(Size(), elements, count);
        return Size() - old_size;
    }

    template<typename T>
    unsigned int NewArray<T>::Push(T*&& elements, unsigned int count)
    {
        unsigned int old_size = Size();
        Splice(Size(), move(elements), count);
        return Size() - old_size;
    }

    template<typename T>
    unsigned int NewArray<T>::Insert(const T& element)
    {
        return Insert(&element, 1);
    }

    template<typename T>
    unsigned int NewArray<T>::Insert(T&& element)
    {
        return Insert(static_cast<T*&&>(&element), 1);
    }

    template<typename T>
    unsigned int NewArray<T>::Insert(T const* elements, unsigned int count)
    {
        unsigned int old_size = Size();
        Splice(0, elements, count);
        return Size() - old_size;
    }

    template<typename T>
    unsigned int NewArray<T>::Insert(T*&& elements, unsigned int count)
    {
        unsigned int old_size = Size();
        Splice(0, move(elements), count);
        return Size() - old_size;
    }

    template<typename T>
    inline unsigned int NewArray<T>::Clear()
    {
        return Delete();
    }

    template<typename T>
    inline unsigned int NewArray<T>::Delete()
    {
        return Delete(Size());
    }

    template<typename T>
    inline unsigned int NewArray<T>::Delete(int count)
    {
        return Delete(0, count);
    }

    template<typename T>
    unsigned int NewArray<T>::Delete(unsigned int from, unsigned int to)
    {
        unsigned int old_size = Size();
        if(from > to){
            swap(from, to);
            from++;
            to++;
        }
        Splice(from, from - to);
        return old_size - Size();
    }
    //endregion
}

#endif //TEMPLATES_NEWARRAY_H
