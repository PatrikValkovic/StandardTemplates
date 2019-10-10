#ifndef TEMPLATES_NEWARRAY_H
#define TEMPLATES_NEWARRAY_H

#include "Basis.h"
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
        unsigned int _allocated;
        unsigned int _inserted;
        UniquePointer<T, __deleterWithoutDestruction<T>> _array;
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
        NewArray(int capacity);
        /**
         * Create new array with `count` elements from the `elements` parameter by copying them.
         * @param elements Array of elements to insert.
         * @param count Number of elements to insert.
         */
        NewArray(T const * elements, unsigned int count);
        /**
         * Create new array with `count` elements from the `elements` parameter by moving them.
         * The array is not deleted and the calling procedure needs to manage the memory.
         * @param elements Array of elements to insert.
         * @param count Number of elements to insert.
         */
        NewArray(T* &&elements, unsigned int count);
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
        NewArray& operator=(const NewArray&);
        /**
         * Move assignable operator.
         */
        NewArray& operator=(NewArray&&);
        /**
         * Destructor.
         */
        ~NewArray() = default;
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
        void Swap(NewArray&);
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
        operator T*() noexcept;
        /**
         * Cast const array to const pointer.
         */
        operator T const * const() const noexcept;
        /**
         * Cast array to pointer.
         */
        T* Raw() noexcept;
        /**
         * Cast const array to const pointer.
         */
        T const * const Raw() const noexcept;
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
        void Splice(unsigned int position, unsigned int to_delete, T const * elements, unsigned int to_insert);
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
        void Splice(unsigned int position, T const * elements, unsigned int to_insert);
        /**
         * From the position `position`, remove `to_delete` elements and then insert `to_insert` elements (by copy) from `elements` array.
         * If size of inserted elements is higher then number of deleted elements, the array is shifted (as well as the other way around).
         * The array needs to be managed by the calling procedure.
         * @param position Position where to delete and insert elements.
         * @param to_delete Number of elements to delete.
         * @param elements Array of elements to insert.
         * @param to_insert Number of elements to insert.
         */
        void Splice(unsigned int position, unsigned int to_delete, T* &&elements, unsigned int to_insert);
        /**
         * From the position `position`, insert `to_insert` elements (by move) from `elements` array.
         * If size of inserted elements is higher then number of deleted elements, the array is shifted (as well as the other way around).
         * The array needs to be managed by the calling procedure.
         * @param position Position where to delete and insert elements.
         * @param elements Array of elements to insert.
         * @param to_insert Number of elements to insert.
         */
        void Splice(unsigned int position, T* &&elements, unsigned int to_insert);
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
        unsigned int Push(T const * elements, unsigned int count);
        /**
         * Insert `count` elements from the `elements` array to the end of the array.
         * @param elements Elements to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
         */
        unsigned int Push(T* &&elements, unsigned int count);
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
        unsigned int Insert(T const * elements, unsigned int count);
        /**
         * Insert `count` elements from the `elements` array to the beginning of the array.
         * @param elements Elements to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(T* &&elements, unsigned int count);
        //endregion

        //region deleting
        /**
         * Delete all the elements in the array. The capacity remain unchanged.
         * @return Number of deleted elements.
         */
        unsigned int Clear();
        /**
         * Delete all the elements in the array. The capacity remain unchanged.
         * @return Number of deleted elements.
         */
        unsigned int Delete();
        /**
         * Delete `count` elements from the array.
         * For positive parameter returns elements from the beginning, for negative one from the end.
         * @param count Number of elements to delete.
         * @return Number of deleted elements.
         */
        unsigned int Delete(int count);
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
    void swap(NewArray<T>& first,NewArray<T>& second)
    {
        first.Swap(second);
    }
}


#endif //TEMPLATES_NEWARRAY_H
