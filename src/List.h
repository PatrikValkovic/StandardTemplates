#ifndef __TEMPLATELIST_H_
#define __TEMPLATELIST_H_
#include "Basis.h"
#include "Exceptions.h"

namespace Templates
{
    /**
     * Represent two way linked list
     */
    template<typename T>
    class List
    {
    private:
        class Node
        {
        public:
#ifdef ___OUT_OF_MEMORY_TESTING
            static unsigned int allocation;

            Node()
            {
                allocation--;
                if (allocation == 0)
                    throw 0;
            }

#endif
            Node* _forward = nullptr;
            Node* _backward = nullptr;
            alignas(alignof(T)) unsigned char _value[sizeof(T)];

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
        int _size;

        template<typename _ListType, typename _CurrentType>
        class BaseIterator
        {
            friend class List;

        protected:
            Node* _node = nullptr;
            _ListType* _list = nullptr;

            BaseIterator(Node* n, _ListType* list) : _node(n), _list(list)
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
            inline bool Next()
            {
                if (this->_node->_forward == nullptr)
                    return false;

                this->_node = this->_node->_forward;
                return true;
            }

            /**
             * Move {@code how_many} elements after actual element. Return true, if can, otherwise false.
             * Note that it doesn't mean, that is iterator valid on the new position.
             * If the return value is false, then the position of the iterator was not changed.
             */
            bool Next(unsigned int how_many)
            {
                _CurrentType iter = *static_cast<_CurrentType*>(this);
                for (unsigned int i = 0; i < how_many; i++)
                    if (!iter.Next())
                        return false;

                *this = iter;
                return true;
            }

            /**
             * Move to the previous element. Return true if can, false otherwise.
             * The iterator is always valid at the new position.
             */
            inline bool Back()
            {
                if (this->_node->_backward == nullptr)
                    return false;

                this->_node = this->_node->_backward;
                return true;
            }

            /**
             * Move {@code how_many} elements after actual element. Return true, if can, otherwise false.
             * If the return value is false, then the position of the iterator was not changed.
             */
            bool Back(unsigned int how_many)
            {
                _CurrentType iter = *static_cast<_CurrentType*>(this);
                for (unsigned int i = 0; i < how_many; i++)
                    if (!iter.Back())
                        return false;

                *this = iter;
                return true;
            }

            /**
             * Move iterator to the beginning of the list.
             * Iterator is not valid if the vector is empty.
             */
            void JumpToBegin() noexcept
            {
                *this = _list->Begin();
            }

            /**
             * Move iterator to the end of the list.
             * Iterator is not valid.
             */
            void JumpToEnd() noexcept
            {
                *this = _list->End();
            }


            /**
             * Prefix increment operator.
             * @throw OutOfRangeException if it's end iterator.
             */
            _CurrentType& operator++()
            {
                if (!this->Next())
                    throw OutOfRangeException("Cannot increment end iterator");
                return *this;
            }

            /**
             * Postfix increment operator.
             * @throw OutOfRangeException if it's end iterator.
             */
            _CurrentType operator++(int)
            {
                _CurrentType tmp(*static_cast<_CurrentType*>(this));
                if (!this->Next())
                    throw OutOfRangeException("Cannot increment end iterator");
                return tmp;
            }

            /**
             * Plus operator with the number.
             * Move iterator {@code v} places after the current node.
             * If the position is not valid, iterator stay at the same node.
             * The result iterator doesn't need to be valid.
             * @param v Number of nodes to skip.
             * @throw OutOfRangeException if the new index is not in the list.
             */
            _CurrentType operator+(unsigned int v)
            {
                ConstIterator tmp(*this);
                if (!tmp.Next(v))
                    throw OutOfRangeException("Iterator can't move to the index");
                return tmp;
            }

            /**
             * Prefix decrement operator.
             * @throw OutOfRangeException if it's begin iterator.
             */
            _CurrentType& operator--()
            {
                if (!this->Back())
                    throw OutOfRangeException("Cannot decrement begin iterator");
                return *this;
            }

            /**
             * Postfix decrement operator.
             * @throw OutOfRangeException if it's begin iterator.
             */
            _CurrentType operator--(int)
            {
                ConstIterator tmp(*this);
                if (!this->Back())
                    throw OutOfRangeException("Cannot decrement begin iterator");
                return tmp;
            }

            /**
             * Minus operator with the number.
             * Move iterator {@code v} places before the current node.
             * If the position is not valid, iterator stay at the same node.
             * @param v Number of nodes to skip.
             * @throw OutOfRangeException if the new index is not in the list.
             */
            _CurrentType operator-(unsigned int v)
            {
                ConstIterator tmp(*this);
                if (!tmp.Back(v))
                    throw OutOfRangeException("Iterator can't move to the index");
                return tmp;
            }

        };

        /**
         * Chains two nodes together.
         */
        static inline void ChainNodes(Node* first, Node* second)
        {
            first->_forward = second;
            second->_backward = first;
        }

    public:
        class ConstIterator : public BaseIterator<const List, ConstIterator>
        {
            friend class List;

        protected:
            ConstIterator(Node* node, const List* list) : BaseIterator<const List, ConstIterator>(node, list)
            {}

        public:
            ConstIterator(const ConstIterator& iterator) = default;
            ConstIterator(ConstIterator&& iterator) noexcept = default;
            ConstIterator& operator=(const ConstIterator& iterator) = default;
            ConstIterator& operator=(ConstIterator&& iterator) noexcept = default;
        };

        class Iterator : public BaseIterator<List, Iterator>
        {
            friend class List;

        protected:
            Iterator(Node* node, List* list) : BaseIterator<List, Iterator>(node, list)
            {}

        public:
            Iterator(const Iterator& iterator) = default;
            Iterator(Iterator&& iterator) noexcept = default;
            Iterator& operator=(const Iterator& iterator) = default;
            Iterator& operator=(Iterator&& iterator) noexcept = default;

            /**
             * Implicit cast to ConstIterator.
             */
            operator ConstIterator() const
            {
                return ConstIterator(this->_node, this->_vector);
            }

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
             * Insert element after current element.
             * The iterator stay at the same position.
             * @param value Element to insert.
             * @throw OutOfRangeException If it's end iterator.
             */
            void Insert(const T& value)
            {
                this->Insert(&value, 1);
            }

            /**
             * Insert elements after current element.
             * The iterator stay at the same position.
             * The order in the array remains same in the list.
             * @param array Elements to insert.
             * @param count Number of elements to insert.
             * @throw OutOfRangeException If it's end iterator.
             */
            void Insert(T const* array, unsigned int count)
            {
                Iterator iter = *this;

                if (!iter.Next())
                    throw OutOfRangeException("Cannot insert to the end iterator");

                iter.InsertBefore(array, count);
            }

            /**
             * Insert element before current element.
             * The iterator stay at the same position.
             * Do not throw exception, in case of begin iterator inserts elements at the beginning of the list.
             * @param value Element to insert.
             */
            void InsertBefore(const T& value)
            {
                this->InsertBefore(&value, 1);
            }

            /**
             * Insert elements before current element.
             * The iterator stay at the same position.
             * The order in the array remains same in the list.
             * Do not throw exception, in case of begin iterator inserts elements at the beginning of the list.
             * @param array Elements to insert.
             * @param count Number of elements to insert.
             */
            void InsertBefore(T const* array, unsigned int count)
            {
                List tmp(array, count);

                if (this->_list->_first == this->_node)
                    this->_list->_first = tmp._first;
                else
                    List::ChainNodes(this->_node->_backward, tmp._first);

                List::ChainNodes(tmp._last->_backward, this->_node);

                this->_list->_size += tmp._size;

                tmp._first = tmp._last;
                tmp._first->_backward = nullptr;
                tmp._size = 0;
            }

            /**
             * Delete next element in the list.
             * The position remains same.
             * @throw OutOfRangeException If it's end iterator.
             */
            void Delete()
            {
                if (this->Delete(1) != 1)
                    throw OutOfRangeException("Invalid call of delete on end iterator");;
            }

            /**
             * Delete multiple elements after current element.
             * The position remains same.
             * If the count is bigger then the remaining size, the elements are removed to the end.
             * @param count Number of elements to delete.
             * @return Number of deleted elements.
             */
            unsigned int Delete(unsigned int count)
            {
                Iterator iter = *this;

                if (!iter.Next())
                    return 0;

                unsigned int deleted = 0;
                for (; iter != this->_list->End() && deleted < count; deleted++)
                    iter.DeleteThis();

                return deleted;
            }

            /**
             * Delete current element.
             * The iterator move to the next element.
             * @throw OutOfRangeException if it's end iterator.
             */
            void DeleteThis()
            {
                if (*this == this->_list->End())
                    throw OutOfRangeException("Invalid call of delete on end iterator");


                Node* next_element = this->_node->_forward;

                if (*this == this->_list->Begin())
                    this->_list->_first = next_element;
                else
                    List::ChainNodes(this->_node->_backward, next_element);

                this->_list->_size--;

                this->_node->Value().~T();
                delete this->_node;

                this->_node = next_element;
            }

            /**
             * Delete previous element in the list.
             * The position remains same.
             * @throw OutOfRangeException If it's begin iterator.
             */
            void DeleteBefore()
            {
                if(this->DeleteBefore(1) != 1)
                    throw OutOfRangeException("Invalid call of deleteBefore on begin iterator");
            }

            /**
             * Delete multiple elements before current element.
             * The position remains same.
             * If the count is bigger then the number of element to current element, the elements are removed to the current element.
             * @param count Number of elements to delete.
             * @return Number of deleted elements.
             */
            unsigned int DeleteBefore(unsigned int count)
            {
                unsigned int deleted = 0;
                while (deleted < count && this->Back())
                {
                    this->DeleteThis();
                    deleted++;
                }

                return deleted;
            }
        };


        /**
         * Allocate empty List.
         */
        List() : _first(new Node()), _last(_first), _size(0)
        {}

        /**
         * Creates new instance and inserts all elements from the array into the list.
         * The elements will be added in the same order, so first element in the array will be first in the list.
         * @param array Array of elements to add into list.
         * @param count Count of elements in the array.
         */
        List(T const* array, unsigned int count) : List()
        {
            T const* e = array + count;

            for (; array != e; array++)
            {
                new(_last->Pointer()) T(*array);

                try
                {
                    _last->_forward = new Node();
                }
                catch (...)
                {
                    _last->Value().~T();
                    throw;
                }

                _last->_forward->_backward = _last;
                _last = _last->_forward;
                _size++;
            }

            //Don't call destructor, see Vector
            //this->~List();
        }


        /**
         * Copy constructor.
         */
        List(const List& copy) : List()
        {
            List::ConstIterator b = copy.Begin();
            List::ConstIterator e = copy.End();
            for (; b != e; b++)
                this->Push(*b);

            //Don't call destructor, see Vector
            //this->~List();
        }

        /**
         * Move constructor.
         */
        List(List&& second) : List()
        {
            swap(*this, second);
        }

        /**
         * Copy assignment operator.
         */
        List& operator=(const List& second)
        {
            if (this == &second)
                return *this;

            List tmp(second);
            swap(*this, tmp);

            return *this;
        }

        /**
         * Move assignment operator.
         */
        List& operator=(List&& second)
        {
            if (this == &second)
                return *this;

            {
                List tmp(move(*this));
            }

            swap(*this, second);
            return *this;
        }

        /**
         * Destructor.
         */
        ~List()
        {
            this->Delete();
            delete _first;
        }

        /**
         * Return count of elements in list.
         */
        inline int Size() const
        {
            return this->_size;
        }

        /**
         * Check if the list is empty.
         * @return True if the list is empty, false otherwse.
         */
        inline bool IsEmpty() const
        {
            return this->Size() == 0;
        }

        /**
         * Access operator.
         * Linear complexity.
         * In case of invalid index OutOfRangeException is thrown.
         * @param index Index to access.
         */
        const T& operator[](unsigned int index) const
        {
            ConstIterator iter = this->Begin();
            if (!iter.Next(index) || iter == this->End())
                throw OutOfRangeException("The index in List is out of range", __LINE__);
            return *iter;
        }

        /**
         * Access operator.
         * Linear complexity.
         * In case of invalid index OutOfRangeException is thrown.
         * @param index Index to access.
         */
        T& operator[](unsigned int index)
        {
            Iterator iter = this->Begin();
            if (!iter.Next(index) || iter == this->End())
                throw OutOfRangeException("The index in List is out of range", __LINE__);
            return *iter;
        }

        /**
         * Delete all elements from the list.
         * @return Number of deleted elements.
         */
        inline unsigned int Delete()
        {
            return this->Delete(~0U);
        }

        /**
         * Delete count elements from the list.
         * In case of exception, some elements could be already deleted from the list.
         * @param count Number of elements to delete.
         * @return Number of deleted elements.
         */
        unsigned int Delete(unsigned int count)
        {
            Iterator iter = this->Begin();
            unsigned int deleted = iter.Delete(count - 1);
            if (iter != this->End())
            {
                iter.DeleteThis();
                deleted++;
            }
            return deleted;
        }

        /**
         * Push count elements from the array in the end of the list.
         * The method is exception safe, in case of exception the list stays in the same state.
         * @param array Elements to insert.
         * @param count Number of elements to insert.
         */
        void Push(T const* array, unsigned int count)
        {
            Iterator iter = this->End();
            iter.InsertBefore(array, count);
        }

        /**
         * Insert element at the end of the list.
         * @param value Element to insert.
         */
        void Push(const T& value)
        {
            this->Push(&value, 1);
        }

        /**
         * Insert element at the beginning of the list.
         * @param value Element to insert.
         */
        void Insert(T& value)
        {
            this->Insert(&value, 1);
        }

        /**
         * Insert elements at the beginning of the list.
         * The method is exception safe, in case of exception the list stays in the same state.
         * @param array Array of elements to insert.
         * @param count Number of elements to insert.
         */
        void Insert(T const* array, unsigned int count)
        {
            Iterator iter = this->Begin();
            iter.InsertBefore(array, count);
        }

        //TODO implement emplace front
        //TODO implement emplace back
        //TODO implement sort
        //TODO implement to array method

        /**
         * Return iterator to begin.
         */
        Iterator Begin()
        {
            return Iterator(_first, this);
        }

        /**
         * Return iterator one position after last element.
         * Note that this iterator is not valid.
         */
        Iterator End()
        {
            return Iterator(_last, this);
        }

        /**
         * Return iterator to begin.
         */
        ConstIterator Begin() const
        {
            return ConstIterator(_first, this);
        }

        /**
         * Return iterator one position after last element.
         * Note that this iterator is not valid.
         */
        ConstIterator End() const
        {
            return ConstIterator(_last, this);
        }

        /**
         * Return iterator pointing to the specific element in the list.
         * In case the index is invalid, OutOfRangeException is thrown.
         * The complexity is linear.
         */
        Iterator At(int index)
        {
            return this->Begin() + index;
        }

        /**
         * Return iterator pointing to the specific element in the list.
         * In case the index is invalid, OutOfRangeException is thrown.
         * The complexity is linear.
         */
        Iterator At(int index) const
        {
            return this->Begin() + index;
        }

        /**
         * Swap two instances of List.
         */
        void Swap(List& second) noexcept
        {
            swap(_size, second._size);
            swap(_first, second._first);
            swap(_last, second._last);
        }

#ifdef ___OUT_OF_MEMORY_TESTING
        static void _SetAllocationLimit(unsigned int limit)
        {
            Node::allocation = limit;
        }
#endif

    };

    /**
     * Swap two instances of the List.
     * @param first First list.
     * @param second Second list.
     */
    template<typename T>
    void swap(List<T>& first, List<T>& second)
    {
        first.Swap(second);
    }
}


#ifdef ___OUT_OF_MEMORY_TESTING
template<typename T>
unsigned int Templates::List<T>::Node::allocation = ~0U;
#endif


#endif
