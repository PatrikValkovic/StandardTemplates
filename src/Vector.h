#ifndef TEMPLATES_VECTOR_H
#define TEMPLATES_VECTOR_H
#include "Basis.h"

namespace Templates
{
    template<typename T>
    class Vector
    {
    private:
        class Node;
        Node* _first;
        Node* _last;
        unsigned int _size;
        unsigned int _allocated;
        template<typename VECT, typename NODE>
        class BaseIterator;
        void AllocateNode(unsigned int count = 1);
    public:
        class ConstIterator;
        class Iterator;

        //region lifetime
        /**
         * Create new empty vector, where no memory is allocated.
         */
        Vector() noexcept;
        /**
         * Create new vector with  `capacity` element allocated in memory.
         * @param capacity Capacity to allocate.
         */
        explicit Vector(unsigned int capacity);
        /**
         * Create new vector with `count` elements from the `elements` parameter by copying them.
         * @param elements Array of elements to insert.
         * @param count Number of elements to insert.
         */
        Vector(T const* elements, unsigned int count);
        /**
         * Create new vector with `count` elements from the `elements` parameter by moving them.
         * The array is not deleted and the calling procedure needs to manage the memory.
         * @param elements Array of elements to insert.
         * @param count Number of elements to insert.
         */
        Vector(T*&& elements, unsigned int count);
        /**
         * Copy constructor.
         */
        Vector(const Vector&);
        /**
         * Movable constructor.
         */
        Vector(Vector&&) noexcept;
        /**
         * Copy assignable operator.
         */
        Vector<T>& operator=(const Vector&);
        /**
         * Move assignable operator.
         */
        Vector<T>& operator=(Vector&&) noexcept;
        /**
         * Destructor.
         */
        ~Vector();
        //endregion

        //region swap
        /**
         * Swap this instance with different one.
         * @param v Instance to swap with.
         */
        void Swap(Vector& v) noexcept;
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
        /**
         * Get element at the `i` position. Has linear complexity.
         * @param i Index of the element.
         * @return Element.
         */
        const T& operator[](unsigned int i) const;
        /**
         * Get element at the `i` position. Has linear complexity.
         * @param i Index of the element.
         * @return Element.
         */
        T& operator[](unsigned int i);
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
    class Vector<T>::Node
    {
    private:
        /**
         * Memory for the element.
         */
        alignas(T) unsigned char mem[sizeof(T)];
        /**
         * Pointer to the next node.
         */
    public:
        /**
         * Pointer to the next node.
         */
        Node* next = nullptr;

        /**
         * Return typed pointer to the memory with element.
         * @return Pointer to memory with element.
         */
        inline T* p() noexcept {
            return static_cast<T*>(static_cast<void*>(mem));
        }
        /**
         * Return typed pointer to the memory with element.
         * @return Pointer to memory with element.
         */
        inline T const * p() const noexcept {
            return static_cast<T const *>(static_cast<const void*>(mem));
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
    template<typename VECT, typename NODE>
    class Vector<T>::BaseIterator
    {
    protected:
        NODE _node = nullptr;
        VECT* _vector = nullptr;
    public:
        bool operator==(const BaseIterator& v) const noexcept
        {
            return *_node == *v._node;
        }
        bool operator!=(const BaseIterator& v) const noexcept
        {
            return !(*this == v);
        }
        const T& operator*() const
        {
            return (*_node)->v();
        }
        T const * operator->() const noexcept
        {
            return (*_node)->p();
        }
        /**
         * Move iterator to the beginning of the vector.
         */
        void Begin() noexcept
        {
            _node = &(_vector->_first);
        }
        /**
         * Move iterator to the end of the vector.
         */
        void End() noexcept
        {
            _node = &(_vector->_last);
        }
    };

    template<typename T>
    class Vector<T>::ConstIterator : public Vector<T>::template BaseIterator<const Vector<T>, Vector<T>::Node const * const *>
    {
    public:
        ConstIterator() noexcept = default;
        ConstIterator(Node const * const * n, const Vector* vect) noexcept
        {
            this->_node = n;
            this->_vector = vect;
        }
        ConstIterator(const ConstIterator&) noexcept = default;
        ConstIterator(ConstIterator&&) noexcept = default;
        ConstIterator& operator=(const ConstIterator&) = default;
        ConstIterator& operator=(ConstIterator&&) noexcept = default;

        /**
         * Move iterator to the next node.
         * @return This iterator on the next node.
         */
        ConstIterator& operator++()
        {
            this->_node = &((*this->_node)->next);
            return *this;
        }
        /**
         * Move iterator to the next node.
         * @return Iterator to the previous node.
         */
        ConstIterator operator++(int)
        {
            const ConstIterator &c = *this;
            ConstIterator tmp(c);
            ++(*this);
            return tmp;
        }
        /**
         * Move iterator `count` nodes ahead.
         * @return Iterator to the node `count` nodes ahead.
         */
        ConstIterator operator+(unsigned int count)
        {
            const ConstIterator &c = *this;
            ConstIterator tmp(c);
            for(unsigned int i=0; i < count; i++)
                tmp++;
            return tmp;
        }
    };

    template<typename T>
    class Vector<T>::Iterator: public Vector<T>::template BaseIterator<Vector<T>, Vector<T>::Node**>
    {
    public:
        Iterator() noexcept = default;
        Iterator(Node** n, Vector* vect) noexcept
        {
            this->_node = n;
            this->_vector = vect;
        }
        Iterator(const Iterator&) noexcept = default;
        Iterator(Iterator&&) noexcept = default;
        Iterator& operator=(const Iterator&) = default;
        Iterator& operator=(Iterator&&) = default;
        operator ConstIterator() const noexcept
        {
            return ConstIterator(this->_node, this->_vector);
        }

        T& operator*()
        {
            return (*(this->_node))->v();
        }
        T* operator->() noexcept
        {
            return (*(this->_node))->p();
        }

        /**
         * Move iterator to the next node.
         * @return This iterator on the next node.
         */
        Iterator& operator++()
        {
            this->_node = &((*this->_node)->next);
            return *this;
        }
        /**
         * Move iterator to the next node.
         * @return Iterator to the previous node.
         */
        const Iterator operator++(int)
        {
            const Iterator &c = *this;
            Iterator tmp(c);
            ++(*this);
            return tmp;
        }
        /**
         * Move iterator `count` nodes ahead.
         * @return Iterator to the node `count` nodes ahead.
         */
        Iterator operator+(unsigned int count)
        {
            const Iterator &c = *this;
            Iterator tmp(c);
            for(unsigned int i=0; i < count; i++)
                tmp++;
            return tmp;
        }


        /**
         * Insert `value` at the position of current iterator and move iterator on next element.
         * That mean the iterator stay at the same node.
         * @param value Value to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(const T& value)
        {
            Node** n = this->_node;
            Vector<T>* v = this->_vector;
            // check size
            if(v->Size() + 1 > v->Capacity())
                v->AllocateNode();
            // check if the iterator wasn't null before
            if(*n == nullptr)
            {
                this->_node = &(v->_last);
                n = this->_node;
            }
            // move free node
            if(*n != v->_last){
                Node* after_last = v->_last->next;
                v->_last->next = after_last->next;
                after_last->next = *n;
                *n = after_last;
            }
            // construct the element
            new ((*n)->p()) T(value);
            v->_size++;
            // check vector pointers
            if(*n == v->_last)
            {
                v->_last = (*n)->n();
                this->_node = &(v->_last);
            }
            else
            {
                this->_node = &((*n)->next);
            }
            return 1;
        }
        /**
         * Insert `value` at the position of current iterator and move iterator on next element.
         * That mean the iterator stay at the same node.
         * @param value Value to insert.
         * @return NUmber of inserted elements.
         */
        unsigned int Insert(T&& value)
        {
            Node** n = this->_node;
            Vector<T>* v = this->_vector;
            // check size
            if(v->Size() + 1 > v->Capacity())
                v->AllocateNode();
            // check if the iterator wasn't null before
            if(*n == nullptr)
            {
                this->_node = &(v->_last);
                n = this->_node;
            }
            // move free node
            if(*n != v->_last){
                Node* after_last = v->_last->next;
                v->_last->next = after_last->next;
                after_last->next = *n;
                *n = after_last;
            }
            // construct the element
            new ((*n)->p()) T(move(value));
            v->_size++;
            // check vector pointers
            if(*n == v->_last)
            {
                v->_last = (*n)->n();
                this->_node = &(v->_last);
            }
            else
            {
                this->_node = &((*n)->next);
            }
            return 1;
        }
        /**
         * Insert `count` values from `values` array into the vector.
         * The values are copied into the vector.
         * The vector ends after the last inserted element (at the same node).
         * @param values Values to insert.
         * @param count How many values insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(T const * values, unsigned int count)
        {
            Vector<T>* v = this->_vector;
            // allocate nodes
            if(v->Size() + count > v->Capacity())
                v->Resize(v->Size() + count);
            // insert elements
            unsigned int old_size = v->Size();
            T const *from = values, *ends = values + count;
            for(;from != ends; from++)
                Insert(*from);
            return v->Size() - old_size;
        }

        /**
         * Insert `count` values from `values` array into the vector.
         * The values are moved into the vector, but the vector needs to be managed by the calling procedure.
         * The vector ends after the last inserted element (at the same node).
         * @param values Array of values to insert.
         * @param count Number of elements to insert.
         * @return Number of inserted elements.
         */
        unsigned int Insert(T* &&values, unsigned int count)
        {
            Vector<T>* v = this->_vector;
            // allocate nodes
            if(v->Size() + count > v->Capacity())
                v->Resize(v->Size() + count);
            // insert elements
            unsigned int old_size = v->Size();
            T *from = values, *ends = values + count;
            for(;from != ends; from++)
            {
                T& value = *from;
                Insert(move(value));
            }
            return v->Size() - old_size;
        }

        /**
         * Delete `count` elements and move iterator to the next not-deleted element (including current one)
         * The elements are deleted only until the last element in the vector.
         * @param count Number of nodes to remove.
         * @return Number of deleted elements.
         */
        unsigned int Delete(unsigned int count = 1)
        {
            Node** n = this->_node;
            Vector<T>* v = this->_vector;

            unsigned int old_size = v->Size();
            for(unsigned int i=0; i < count && *this != v->End(); i++)
            {
                Node* next = (*n)->n();
                Node* to_delete = *n;
                *n = next;
                to_delete->v().~T();
                v->_size--;
            }
            return v->Size() - old_size;
        }
    };

    /**
     * Swap two instances of the array
     * @param first First array
     * @param second Second array
     */
    template<typename T>
    void swap(Vector<T>& first, Vector<T>& second)
    {
        first.Swap(second);
    }

    //region implementation
    template<typename T>
    void Vector<T>::AllocateNode(unsigned int count)
    {
        if (!_last)
        {
            _first = _last = new Node();
            _allocated++;
        }

        for (unsigned int i = 0; i < count; i++)
        {
            Node* n = new Node();
            n->next = _last->next;
            _last->next = n;
            _allocated++;
        }
    }

    template<typename T>
    Vector<T>::Vector() noexcept: _first(nullptr), _last(nullptr), _size(0), _allocated(0)
    {}

    template<typename T>
    Vector<T>::Vector(unsigned int capacity) : Vector()
    {
        AllocateNode(capacity);
    }

    template<typename T>
    Vector<T>::Vector(T const* elements, unsigned int count) : Vector(count)
    {
        Begin().Insert(elements, count);
    }

    template<typename T>
    Vector<T>::Vector(T*&& elements, unsigned int count) : Vector(count)
    {
        Begin().Insert(move(elements), count);
    }

    template<typename T>
    Vector<T>::Vector(const Vector& v) : Vector(v.Size())
    {
        *this = v;
    }

    template<typename T>
    Vector<T>::Vector(Vector &&v) noexcept : Vector()
    {
        Swap(v);
    }

    template<typename T>
    void Vector<T>::Swap(Vector& v) noexcept
    {
        using Templates::swap;
        swap(_first, v._first);
        swap(_last, v._last);
        swap(_allocated, v._allocated);
        swap(_size, v._size);
    }

    template<typename T>
    Vector<T>& Vector<T>::operator=(const Vector& v)
    {
        if(this == &v)
            return *this;

        Clear();
        ConstIterator working = v.Begin(), ending = v.End();
        Iterator push=Begin();
        for(; working != ending; working++)
            push.Insert(*working);
        return *this;
    }

    template<typename T>
    Vector<T>& Vector<T>::operator=(Vector&& v) noexcept
    {
        if(this == &v)
            return *this;

        Swap(v);
        return *this;
    }

    template<typename T>
    Vector<T>::~Vector()
    {
        Delete();
        ShrinkToFit();
        delete _first;
        _first = _last = nullptr;
        _allocated = 0;
    }

    template<typename T>
    unsigned int Vector<T>::Size() const noexcept
    {
        return _size;
    }

    template<typename T>
    unsigned int Vector<T>::Capacity() const noexcept
    {
        return _allocated == 0 ? 0 : _allocated - 1;
    }

    template<typename T>
    bool Vector<T>::Empty() const noexcept
    {
        return Size() == 0;
    }

    template<typename T>
    unsigned int Vector<T>::ShrinkToFit()
    {
        return Resize(Capacity());
    }

    template<typename T>
    unsigned int Vector<T>::Resize(unsigned int new_capacity)
    {
        // allocate more
        if(Capacity() < new_capacity)
            AllocateNode(new_capacity - Capacity());

        // deallocate from the end
        while(Size() < Capacity() && new_capacity < Capacity() && _last->next){
            Node* to_delete = _last->next;
            _last->next = _last->next->next;
            delete to_delete;
            _allocated--;
        }
        //TODO assert size == capacity

        // deallocate from the beginning
        while(new_capacity < Capacity())
            Begin().Delete();

        return Capacity();
    }

    template<typename T>
    unsigned int Vector<T>::ResizeBy(int resize_by)
    {
        return Resize(max(0, (int)Capacity() + resize_by));
    }

    template<typename T>
    typename Vector<T>::ConstIterator Vector<T>::Begin() const noexcept
    {
        return ConstIterator(&_first, this);
    }

    template<typename T>
    typename Vector<T>::ConstIterator Vector<T>::End() const noexcept
    {
        return ConstIterator(&_last, this);
    }

    template<typename T>
    typename Vector<T>::Iterator Vector<T>::Begin() noexcept
    {
        return Iterator(&_first, this);
    }

    template<typename T>
    typename Vector<T>::Iterator Vector<T>::End() noexcept
    {
        return Iterator(&_last, this);
    }

    template<typename T>
    unsigned int Vector<T>::Push(const T& element)
    {
        unsigned int old_size = Size();
        End().Insert(element);
        return Size() - old_size;
    }

    template<typename T>
    unsigned int Vector<T>::Push(T&& element)
    {
        unsigned int old_size = Size();
        End().Insert(move(element));
        return Size() - old_size;
    }

    template<typename T>
    unsigned int Vector<T>::Push(T const* elements, unsigned int count)
    {
        unsigned int old_size = Size();
        End().Insert(elements, count);
        return Size() - old_size;    }

    template<typename T>
    unsigned int Vector<T>::Push(T*&& elements, unsigned int count)
    {
        unsigned int old_size = Size();
        End().Insert(move(elements), count);
        return Size() - old_size;
    }

    template<typename T>
    unsigned int Vector<T>::Insert(const T& element)
    {
        unsigned int old_size = Size();
        Begin().Insert(element);
        return Size() - old_size;
    }

    template<typename T>
    unsigned int Vector<T>::Insert(T&& element)
    {
        unsigned int old_size = Size();
        Begin().Insert(move(element));
        return Size() - old_size;
    }

    template<typename T>
    unsigned int Vector<T>::Insert(T const* elements, unsigned int count)
    {
        unsigned int old_size = Size();
        Begin().Insert(elements, count);
        return Size() - old_size;
    }

    template<typename T>
    unsigned int Vector<T>::Insert(T*&& elements, unsigned int count)
    {
        unsigned int old_size = Size();
        Begin().Insert(move(elements), count);
        return Size() - old_size;
    }

    template<typename T>
    unsigned int Vector<T>::Clear()
    {
        return Delete();
    }

    template<typename T>
    unsigned int Vector<T>::Delete()
    {
        return Delete(Size());
    }

    template<typename T>
    unsigned int Vector<T>::Delete(unsigned int count)
    {
        return Begin().Delete(count);
    }

    template<typename T>
    const T& Vector<T>::operator[](unsigned int i) const
    {
        if(i >= Size())
            throw OutOfRangeException("Index is out of vector's range.", __LINE__);
        return *(Begin() + i);
    }

    template<typename T>
    T& Vector<T>::operator[](unsigned int i)
    {
        if(i >= Size())
            throw OutOfRangeException("Index is out of vector's range.", __LINE__);
        return *(Begin() + i);
    }
    //endregion
}

#endif //TEMPLATES_VECTOR_H
