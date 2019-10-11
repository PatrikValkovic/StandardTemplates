#ifndef TEMPLATES_NEWVECTOR_H
#define TEMPLATES_NEWVECTOR_H

namespace Templates
{
    template<typename T>
    class NewVector
    {
    private:
        class Node;
        Node* _first;
        Node* _last;
        unsigned int _size;
        unsigned int _allocated;
        template<typename TYPE, typename VECT, typename NODE>
        class BaseIterator;
        void AllocateNode(unsigned int count);
    public:
        class ConstIterator;
        class Iterator;

        //region lifetime
        /**
         * Create new empty vector, where no memory is allocated.
         */
        NewVector() noexcept;
        /**
         * Create new vector with  `capacity` element allocated in memory.
         * @param capacity Capacity to allocate.
         */
        explicit NewVector(unsigned int capacity);
        /**
         * Create new vector with `count` elements from the `elements` parameter by copying them.
         * @param elements Array of elements to insert.
         * @param count Number of elements to insert.
         */
        NewVector(T const* elements, unsigned int count);
        /**
         * Create new vector with `count` elements from the `elements` parameter by moving them.
         * The array is not deleted and the calling procedure needs to manage the memory.
         * @param elements Array of elements to insert.
         * @param count Number of elements to insert.
         */
        NewVector(T*&& elements, unsigned int count);
        /**
         * Copy constructor.
         */
        NewVector(const NewVector&);
        /**
         * Movable constructor.
         */
        NewVector(NewVector&&) noexcept;
        /**
         * Copy assignable operator.
         */
        NewVector<T>& operator=(const NewVector&);
        /**
         * Move assignable operator.
         */
        NewVector<T>& operator=(NewVector&&) noexcept;
        /**
         * Destructor.
         */
        ~NewVector();
        //endregion

        //region swap
        /**
         * Swap this instance with different one.
         * @param v Instance to swap with.
         */
        void Swap(NewVector& v) noexcept;
        //endregion

        //region queries
        /**
         * Returns number of elements inserted into the vector.
         * @return Number of elements in vector.
         */
        inline unsigned int Size() const noexcept;
        /**
         * Get how many elements can fit into container without reallocating.
         * @return Capacity of the vector.
         */
        inline unsigned int Capacity() const noexcept;
        /**
         * Check if the vector is empty.
         * @return True if the vector is empty, false otherwise.
         */
        inline bool Empty() const noexcept;
        //endregion

        //region resizing
        /**
         * Resize vector to the new capacity.
         * When new capacity is lower than the size, elements from the beginning of the vector are destructed.
         * @param new_capacity New capacity of the vector.
         * @return New capacity of the vector.
         */
        unsigned int Resize(unsigned int new_capacity);
        /**
         * Resize vector by `resize_by` parameter. For negative values the vector will be shrinking.
         * When new capacity is lower than the size, elements from the beginning of the vector are destructed.
         * @param resize_by Amount of resize.
         * @return New capacity of the vector.
         */
        unsigned int ResizeBy(int resize_by);
        /**
         * Shrink the vector so capacity would be equal to size + 1 (because of the last empty node).
         * @return New capacity of the vector.
         */
        unsigned int ShrinkToFit();
        //endregion

        //region iterators
        /**
         * Returns iterator to the beginning of the vector.
         * @return Iterator to the beginning of the vector.
         */
        ConstIterator Begin() const noexcept;
        /**
         * Returns iterator to the end of the vector.
         * @return Iterator to the end of the vector.
         */
        ConstIterator End() const noexcept;
        /**
         * Returns iterator to the beginning of the vector.
         * @return Iterator to the beginning of the vector.
         */
        Iterator Begin() noexcept;
        /**
         * Returns iterator to the end of the vector.
         * @return Iterator to the end of the vector.
         */
        Iterator End() noexcept;
        //endregion

        //region inserting
        /**
         * Insert element at the end of the vector.
         * @param element Element to insert.
         * @return Number of inserted elements.
         */
        unsigned int Push(const T& element);
        /**
         * Insert element at the end of the vector.
         * @param element Element to insert.
         * @return Number of inserted elements.
         */
        unsigned int Push(T&& element);
        /**
         * Insert `count` elements from the `elements` array to the end of the vector.
         * @param elements Elements to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
         */
        unsigned int Push(T const* elements, unsigned int count);
        /**
         * Insert `count` elements from the `elements` array to the end of the vector.
         * @param elements Elements to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
         */
        unsigned int Push(T*&& elements, unsigned int count);
        /**
         * Insert element at the beginning of the vector.
         * @param element Element to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(const T& element);
        /**
         * Insert element at the beginning of the vector.
         * @param element Element to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(T&& element);
        /**
         * Insert `count` elements from the `elements` array to the beginning of the vector.
         * @param elements Elements to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(T const* elements, unsigned int count);
        /**
         * Insert `count` elements from the `elements` array to the beginning of the vector.
         * @param elements Elements to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(T*&& elements, unsigned int count);
        //endregion

        //region deleting
        /**
         * Delete all the elements in the vector. The capacity remain unchanged.
         * @return Number of deleted elements.
         */
        inline unsigned int Clear();
        /**
         * Delete all the elements in the vector. The capacity remain unchanged.
         * @return Number of deleted elements.
         */
        inline unsigned int Delete();
        /**
         * Delete `count` elements from the beginning of the vector.
         * @param count Number of elements to delete.
         * @return Number of deleted elements.
         */
        inline unsigned int Delete(unsigned int count);
        //endregion
    };

    template<typename T>
    class NewVector<T>::Node
    {
    private:
        /**
         * Memory for the element.
         */
        alignas(T) unsigned char mem[sizeof(T)];
        /**
         * Pointer to the next node.
         */
        Node* next = nullptr;
    public:
        /**
         * Return typed pointer to the memory with element.
         * @return Pointer to memory with element.
         */
        inline T* p() noexcept {
            return static_cast<T*>(mem);
        }
        /**
         * Return typed pointer to the memory with element.
         * @return Pointer to memory with element.
         */
        inline T const * p() const noexcept {
            return static_cast<T const *>(mem);
        }
        /**
         * Return reference to the containing element.
         * If no element is present, the behavior is undefined.
         * @return Reference to the element.
         */
        inline T& v() noexcept {
            return *p();
        }
        /**
         * Return reference to the containing element.
         * If no element is present, the behavior is undefined.
         * @return Reference to the element.
         */
        inline const T& v() const noexcept {
            return *p();
        }
        /**
         * Get pointer to the next node.
         * @return Next node.
         */
        inline Node* n() noexcept {
            return next;
        }
        /**
         * Get pointer to the next node.
         * @return Next node.
         */
        inline Node const * n() const noexcept {
            return next;
        }
    };

    template<typename T>
    template<typename TYPE, typename VECT, typename NODE>
    class NewVector<T>::BaseIterator
    {
    protected:
        NODE** _node = nullptr;
        VECT* _vector = nullptr;
    public:
        bool operator==(const BaseIterator&) const noexcept;
        bool operator!=(const BaseIterator&) const noexcept;
        const T& operator*() const;
        T const * operator->() const noexcept;
        /**
         * Move iterator to the beginning of the vector.
         */
        void Beginning() noexcept;
        /**
         * Move iterator to the end of the vector.
         */
        void End() noexcept;
    };

    template<typename T>
    class NewVector<T>::ConstIterator: public NewVector<T>::BaseIterator<const T, const NewVector<T>, const NewVector<T>::Node>
    {
    public:
        ConstIterator() noexcept = default;
        ConstIterator(const Node* &n, const NewVector* vect) noexcept;
        ConstIterator(const ConstIterator&) noexcept = default;
        ConstIterator(ConstIterator&&) noexcept = default;
        ConstIterator& operator=(const ConstIterator&) = default;
        ConstIterator& operator=(const ConstIterator&&) = default;

        /**
         * Move iterator to the next node.
         * @return This iterator on the next node.
         */
        ConstIterator& operator++();
        /**
         * Move iterator to the next node.
         * @return Iterator to the previous node.
         */
        ConstIterator operator++(int);
        /**
         * Move iterator `count` nodes ahead.
         * @return Iterator to the node `count` nodes ahead.
         */
        ConstIterator operator+(unsigned int count);
    };

    template<typename T>
    class NewVector<T>::Iterator: public NewVector<T>::BaseIterator<T, NewVector<T>, NewVector<T>::Node>
    {
    public:
        Iterator() noexcept = default;
        Iterator(const Node* &n, const NewVector* vect) noexcept;
        Iterator(const Iterator&) noexcept = default;
        Iterator(Iterator&&) noexcept = default;
        Iterator& operator=(const Iterator&) = default;
        Iterator& operator=(const Iterator&&) = default;
        operator ConstIterator() const noexcept;

        T& operator*();
        T* operator->() noexcept;

        /**
         * Move iterator to the next node.
         * @return This iterator on the next node.
         */
        Iterator& operator++();
        /**
         * Move iterator to the next node.
         * @return Iterator to the previous node.
         */
        Iterator operator++(int);
        /**
         * Move iterator `count` nodes ahead.
         * @return Iterator to the node `count` nodes ahead.
         */
        Iterator operator+(unsigned int count);

        /**
         * Insert `value` after current iterator and move iterator on that element.
         * @param value Value to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(const T& value);
        /**
         * Insert `value` after current iterator and move iterator on that element.
         * @param value Value to insert.
         * @return NUmber of inserted elements.
         */
        unsigned int Insert(T&& value);
        /**
         * Insert `count` values from `values` array into the vector.
         * The values are copied into the vector.
         * The vector ends at the last inserted element.
         * @param values Values to insert.
         * @param count How many values insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(T const * values, unsigned int count);
        /**
         * Insert `count` values from `values` array into the vector.
         * The values are moved into the vector, but the vector needs to be managed by the valling procedure.
         * The vector ends at the last inserted element.
         * @param values Array of values to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(T* &&values, unsigned int count);

        /**
         * Delete `count` elements and move iterator to the next not-deleted element.
         * The elements are deleted only until last element in the vector.
         * @param count Number of nodes to remove.
         * @return Number of deleted elements.
         */
        unsigned int Delete(unsigned int count = 1);
    };

    /**
     * Swap two instances of the array
     * @param first First array
     * @param second Second array
     */
    template<typename T>
    void swap(NewVector<T>& first, NewVector<T>& second)
    {
        first.Swap(second);
    }
}

#endif //TEMPLATES_NEWVECTOR_H
