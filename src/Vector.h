#ifndef TEMPLATES_VECTOR_H
#define TEMPLATES_VECTOR_H
#include "Basis.h"
#include "Array.h"

namespace Templates
{
    /**
     * Data structure that represent one-way linked list.
     * The structure keeps its size and pointers to the first and last element.
     * Vector can have more nodes then number of elements. Use ShrinkToFit to delete these nodes.
     */
    template<typename T>
    class Vector
    {
    private:
        class Node
        {
        public:
            alignas(alignof(T)) unsigned char _value[sizeof(T)];
            Node* _next = nullptr;
            T* const Pointer() noexcept
            {
                return static_cast<T*>(static_cast<void*>(_value));
            }
            T& Value() noexcept
            {
                return *Pointer();
            }
        };

        Node* _first;
        Node* _last;
        unsigned int _count;

        template<typename __BaseType>
        class BaseIterator
        {
            friend class Vector;
        protected:
            Node* _node = nullptr;
            __BaseType* _vector;

            /**
             * Create iterator pointing to specific node.
             */
            BaseIterator(Node* working_node, __BaseType* v) : _node(working_node), _vector(v)
            {}
        public:

            /**
             * Equality operator.
             * @return True if iterators points to the same node, false otherwise.
             */
            bool operator==(const BaseIterator& s) const noexcept
            {
                return _node == s._node;
            }

            /**
             * Non equality operator.
             * @return True if iterators points to different nodes, false otherwise.
             */
            bool operator!=(const BaseIterator& s) const noexcept
            {
                return !(*this == s);
            }

            /**
             * Dereference iterator to get value.
             */
            const T& operator*() const noexcept
            {
                return _node->Value();
            }

            /**
             * Structure dereference iterator to get pointer.
             */
            const T* operator->() const noexcept
            {
                return _node->Pointer();
            }

            /**
             * Move to the next element. Return true if can, false otherwise.
             * Note that it doesn't mean, that is iterator valid on the new position.
             */
            bool Next()
            {
                return Next(1);
            }

            /**
             * Move {@code how_many} elements after actual element. Return true, if can, otherwise false.
             * Note that it doesn't mean, that is iterator valid on the new position.
             * If the return value is false, then the position of the iterator was not changed.
             */
            bool Next(unsigned int how_many)
            {
                Node* tmp = _node;
                for (unsigned int a = 0; a < how_many; a++)
                {
                    if (tmp->_next == nullptr)
                        return false;
                    tmp = tmp->_next;
                }
                _node = tmp;
                return true;
            }

            /**
             * Move iterator to the beginning of the vector.
             * Iterator is not valid if the vector is empty.
             */
            void JumpToBegin() noexcept
            {
                *this = _vector->Begin();
            }

            /**
             * Move iterator to the end of the vector.
             * Iterator is not valid.
             */
            void JumpToEnd() noexcept
            {
                *this = _vector->End();
            }
        };
    public:
        class ConstIterator: public BaseIterator<const Vector>
        {
            friend class Vector;
        protected:
            ConstIterator(Node* working_node, const Vector* v) : BaseIterator<const Vector>(working_node, v)
            {}
        public:
            ConstIterator(const ConstIterator& iterator) = default;
            ConstIterator(ConstIterator&& iterator) noexcept = default;
            ConstIterator& operator=(const ConstIterator& iterator) = default;
            ConstIterator& operator=(ConstIterator&& iterator) noexcept = default;
            /**
             * Prefix increment operator.
             */
            ConstIterator& operator++()
            {
                this->Next();
                return *this;
            }

            /**
             * Postfix increment operator.
             */
            ConstIterator operator++(int)
            {
                ConstIterator tmp(*this);
                this->Next();
                return tmp;
            }

            /**
             * Plus operator with the number.
             * Move iterator {@code v} places after the current node.
             * If the position is not valid, iterator stay at the same node.
             * The result iterator doesn't need to be valid.
             * @param v Number of nodes to skip.
             */
            ConstIterator& operator+(unsigned int v)
            {
                this->Next(v);
                return *this;
            }
        };

        class Iterator : public BaseIterator<Vector>
        {
            friend class Vector;
        protected:
            Iterator(Node* working_node, Vector* v) : BaseIterator<Vector>(working_node, v)
            {}
        public:
            Iterator(const Iterator& iterator) = default;
            Iterator(Iterator&& iterator) noexcept = default;
            Iterator& operator=(const Iterator& iterator) = default;
            Iterator& operator=(Iterator&& iterator) noexcept = default;

            /**
             * Dereference iterator to get value.
             */
            T& operator*() noexcept
            {
                return this->_node->Value();
            }

            /**
             * Structure dereference iterator to get pointer.
             */
            T* operator->() noexcept
            {
                return this->_node->Pointer();
            }

            /**
             * Prefix increment operator.
             */
            Iterator& operator++()
            {
                this->Next();
                return *this;
            }

            /**
             * Postfix increment operator.
             */
            Iterator operator++(int)
            {
                Iterator tmp(*this);
                this->Next();
                return tmp;
            }

            /**
             * Plus operator with the number.
             * Move iterator {@code v} places after the current node.
             * If the position is not valid, iterator stay at the same node.
             * The result iterator doesn't need to be valid.
             * @param v Number of nodes to skip.
             */
            Iterator& operator+(unsigned int v)
            {
                this->Next(v);
                return *this;
            }

            /**
             * Insert elements after the current node.
             * First element in the array will be next element of the current node.
             * This method is potentially dangerous. You must be absolutely sure, that the iterator is valid.
             * Valid iterator point to existing node with already allocated value.
             * Valid iterator is from Begin and not already equal to End.
             * Otherwise Vector will be in undefined state and it's behaviour is undefined (even the destructuring of the Vector!!).
             * In case of exception Vector stay valid but previous inserted elements remain in the Vector.
             * @param values Values to insert
             * @param count number of elements to insert
             */
            void Insert(const T* values, unsigned int count)
            {
                const T* tmp = values + count;
                while(tmp --> values)
                    Insert(*tmp);
            }

            /**
             * Insert element after the current node.
             * This method is potentially dangerous. You must be absolutely sure, that the iterator is valid.
             * Valid iterator point to existing node with already allocated value.
             * Valid iterator is from Begin and not already equal to End.
             * Otherwise Vector will be in undefined state and it's behaviour is undefined (even the destructuring of the Vector!!).
             * In case of exception Vector stay in the same state.
             * @param value Element to insert.
             */
            void Insert(const T& value)
            {
                Node* tmp = new Node();
                try
                {
                    new (tmp->Pointer()) T(value);
                }
                catch(...)
                {
                    delete tmp;
                    throw;
                }

                tmp->_next = this->_node->_next;
                this->_node->_next = tmp;
                this->_vector->_count++;
            }

            /**
             * Delete next element in the Vector.
             * The iterator stays at the same node.
             * This method is potentially dangerous. You must be absolutely sure, that the iterator is valid.
             * Valid iterator point to existing node with already allocated value.
             * Valid iterator is from Begin and not already equal to End.
             * Otherwise Vector will be in undefined state and it's behaviour is undefined (even the destructuring of the Vector!!).
             * In case of exception Vector stay valid but element is deleted anyway.
             * @return True if the element was deleted, false otherwise.
             */
            bool Delete()
            {
                Node* next = this->_node->_next;
                if(next == this->_vector->_last)
                    return false;

                try
                {
                    next->Value().~T();
                }
                catch(...)
                {
                    this->_node->_next = next->_next;
                    this->_vector->_count--;
                    next->_next = this->_vector->_last->_next;
                    this->_vector->_last->_next = next;
                    throw;
                }

                this->_node->_next = next->_next;
                this->_vector->_count--;
                next->_next = this->_vector->_last->_next;
                this->_vector->_last->_next = next;
                return true;
            }

            /**
             * Delete next elements in the Vector.
             * Only elements up to Vector's end are deleted, so number of deleted elements can be lower then provided parameter.
             * The iterator stays at the same node.
             * This method is potentially dangerous. You must be absolutely sure, that the iterator is valid.
             * Valid iterator point to existing node with already allocated value.
             * Valid iterator is from Begin and not already equal to End.
             * Otherwise Vector will be in undefined state and it's behaviour is undefined (even the destructuring of the Vector!!).
             * In case of exception Vector stay valid but element is deleted anyway.
             * @param count Number of elements to delete.
             * @return Number of deleted elements.
             */
            unsigned int Delete(unsigned int count)
            {
                unsigned int i = 0;
                for(;i < count && this->Delete();i++);
                return i;
            }
        };

    public:

        /**
         * Creates new instance of Vector
         */
        Vector() : Vector(0)
        {}

        /**
         * Create new instance with provided capacity.
         * The nodes are allocated, but not valid yet.
         * @param capacity Number of nodes to allocate.
         */
        Vector(unsigned int capacity) : _first(nullptr), _last(nullptr), _count(0)
        {
            try
            {
                capacity++;
                Node* tmp = _last = _first = new Node;
                for (unsigned int a = 0; a < capacity; a++)
                {
                    Node* created = new Node;
                    tmp->_next = created;
                    tmp = created;
                }
            }
            catch(...)
            {
                Node* ptr = _first;
                while(ptr != nullptr)
                {
                    Node* tmp = ptr->_next;
                    delete ptr;
                    ptr = tmp;
                }
                throw;
            }

        }

        /**
         * Creates new instance and inserts all elements from the array into the vector.
         * The elements will be added in the same order, so first element in the array will be first in the list.
         * @param array Array of elements to add into list.
         * @param count Count of elements in the array.
         */
        Vector(const T* array, unsigned int count) : Vector(count)
        {
            this->PushBack(array, count);

            //don't call destructor, even in catch block
            //https://stackoverflow.com/questions/17657761/is-the-destructor-called-when-a-delegating-constructor-throws
            //this->~Vector();
        }

        /**
         * Copy constructor.
         * Makes copy of all elements in the second array.
         */
        Vector(const Vector& copy): Vector(copy._count)
        {
            Vector::ConstIterator b = copy.Begin();
            Vector::ConstIterator e = copy.End();
            for(;b != e;b++)
                this->PushBack(*b);

            //don't call destructor, even in catch block
            //https://stackoverflow.com/questions/17657761/is-the-destructor-called-when-a-delegating-constructor-throws
            //this->~Vector();
        }

        /**
         * Move constructor.
         * Second vector will be cleared.
         */
        Vector(Vector&& second) : Vector(0)
        {
            swap(*this, second);
        }

        /**
         * Copy assignment operator.
         * Values will be copied from the second vector.
         */
        Vector& operator=(const Vector& second)
        {
            if(this==&second)
                return *this;

            {
                Vector tmp(second.Size());
                swap(*this, tmp);
            }

            Vector::Iterator b = second.Begin();
            Vector::Iterator e = second.End();
            for(;b != e;b++)
                this->PushBack(*b);

            return *this;
        }

        /**
         * Move assignment operator.
         * Second vector will be cleared.
         */
        Vector& operator=(Vector&& second)
        {
            if(this==&second)
                return *this;

            {
                Vector tmp(move(*this));
            }

            swap(*this, second);
            return *this;
        }

        /**
         * Destructor
         */
        ~Vector()
        {
            this->Delete();
            this->ShrinkToFit();
            delete _first;
        }

        T& operator[](unsigned int x)
        {
            Iterator b = this->Begin();
            Iterator e = this->End();
            for(unsigned int i = 0;b != e && i < x;b++,i++);
            if(b == e)
                throw OutOfRangeException("Index is out of range", __LINE__);

            return *b;
        }

        const T& operator[](unsigned int x) const
        {
            ConstIterator b = this->Begin();
            ConstIterator e = this->End();
            for(unsigned int i = 0;b != e && i < x;b++,i++);
            if(b == e)
                throw OutOfRangeException("Index is out of range", __LINE__);

            return *b;
        }


        Array<T> ToArray() const
        {
            Array<T> tmp(this->Size());

            ConstIterator b = this->Begin();
            ConstIterator e = this->End();
            for(;b != e;b++)
                tmp.Push(*b);

            return move(tmp);
        }

        /**
         * Return iterator to beginning of Vector.
         */
        Iterator Begin()
        {
            return Iterator(_first, this);
        }

        /**
         * Return iterator to element after last element.
         * This iterator will be not valid.
         */
        Iterator End()
        {
            return Iterator(_last, this);
        }

        /**
         * Return constant iterator to beginning of Vector.
         */
        ConstIterator Begin() const
        {
            return ConstIterator(_first, this);
        }

        /**
         * Return constant iterator to element after last element.
         * This iterator will be not valid.
         */
        ConstIterator End() const
        {
            return ConstIterator(_last, this);
        }

        /**
         * Return count of elements in Vector.
         */
        unsigned int Size() const
        {
            return _count;
        }

        /**
         * Return true if the Vector is empty, false otherwise.
         * Allocated nodes are not taken into account.
         */
        inline bool IsEmpty() const
        {
            return _first == _last;
        }

        void PushBack(const T& value)
        {
            if(_last->_next == nullptr)
                _last->_next = new Node;

            new (_last->Pointer()) T(value);
            _count++;
            _last = _last->_next;
        }

        void PushBack(const T* array, unsigned int count)
        {
            const T* last_element = array + count;
            for(;array != last_element;array++)
                PushBack(*array);
        }

        /**
         * Because vector can hold more nodes then is number of elements, this method delete unused nodes.
         */
        void ShrinkToFit() noexcept
        {
            Node* working = _last->_next;
            while(working != nullptr){
                Node* tmp = working->_next;
                delete working;
                working = tmp;
            }
            _last->_next = nullptr;
        }

        /**
         * Delete all elements from the Vector.
         */
        inline unsigned int Delete()
        {
            return Delete(Size());
        }

        /**
         * Delete specific amount of elements from the beginning of the Vector.
         * The method takes care about size of the Vector, so maximum of Size() elements will be removed.
         * In case of exception, Vector stay in valid state, however some elements could be already deleted.
         * @param count Number of elements to delete.
         * @return Number of deleted elements.
         */
        unsigned int Delete(unsigned int count)
        {
            if(count != 1)
            {
                unsigned int old_size = this->Size();
                while(count --> 0 && this->Delete(1));
                return old_size - this->Size();
            }

            if(_first == _last)
                return 0;

            Node* working = _first;
            _first = working->_next;
            working->_next = _last->_next;
            _last->_next = working;
            _count--;

            working->Value().~T();

            return 1;
        }

        /**
         * Insert element at the beginning of the Vector.
         * In case of exception, Vector stay in valid state, however additional Node could be allocated after the end element.
         * @param value Element to insert.
         */
        void Insert(const T& value)
        {
            if(_last->_next == nullptr)
                _last->_next = new Node;

            new (_last->_next->Pointer()) T(value);

            Node* current_first = _first;
            Node* created = _last->_next;
            _last->_next = created->_next;
            created->_next = current_first;
            _first = created;
            _count++;
        }

        /**
         * Insert {@code count} elements into the Vector at the beginning.
         * First element in the array begin the first element in the Vector.
         * In case of exception, the Vector stay in valid state, however some elements could be inserted.
         * @param array Array of elements to insert.
         * @param count Count of elements to insert.
         */
        void Insert(const T* array, int count)
        {
            const T* end_ptr = array + count;
            while(end_ptr --> array)
                this->Insert(*end_ptr);
        }

        /**
         * Swap two instances of Vector.
         */
        void Swap(Vector& second) noexcept
        {
            swap(_count, second._count);
            swap(_first, second._first);
            swap(_last, second._last);
        }
    };

    /**
     * Swap two instances of the Vector.
     * @param first First vector.
     * @param second Second vector.
     */
    template<typename T>
    void swap(Vector<T>& first,Vector<T>& second)
    {
        first.Swap(second);
    }
}




#endif //TEMPLATES_QUEUE_H
