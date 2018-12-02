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

        Node* MergeSort(Node* WhatToSort, int HowMany,
                        bool(* IsFirstBeforeSecond)(const T* const First, const T* const Second))
        {
            if (HowMany <= 1)
            {
                WhatToSort->Forward = nullptr;
                WhatToSort->Backward = nullptr;
                return WhatToSort;
            }
            int FirstCount = HowMany / 2;
            int SecondCount = HowMany - FirstCount;
            Node* SecondNode = WhatToSort;
            for (int a = 0; a < FirstCount; a++)
            {
                SecondNode = SecondNode->Forward;
            }
            Node* First = MergeSort(WhatToSort, FirstCount, IsFirstBeforeSecond);
            Node* Second = MergeSort(SecondNode, SecondCount, IsFirstBeforeSecond);
            Node* ToReturn = Join(First, FirstCount, Second, SecondCount, IsFirstBeforeSecond);
            return ToReturn;
        }

        Node* Join(Node* First, int FirstCount,
                   Node* Second, int SecondCount,
                   bool(* IsFirstBeforeSecond)(const T* const First, const T* const Second))
        {
            typename List<T>::Node* Working;
            typename List<T>::Node* Base;
            int deletedFirst = 0;
            int deletedSecont = 0;
            if (IsFirstBeforeSecond(&First->Value, &Second->Value))
            {
                Working = First;
                deletedFirst++;
                First = First->Forward;
            }
            else
            {
                Working = Second;
                deletedSecont++;
                Second = Second->Forward;
            }
            Working->Backward = nullptr;
            Base = Working;
            while (deletedFirst < FirstCount && deletedSecont < SecondCount)
            {
                if (IsFirstBeforeSecond(&First->Value, &Second->Value))
                {
                    Working->Forward = First;
                    First->Backward = Working;
                    First = First->Forward;
                    deletedFirst++;
                }
                else
                {
                    Working->Forward = Second;
                    Second->Backward = Working;
                    Second = Second->Forward;
                    deletedSecont++;
                }
                Working = Working->Forward;
            }
            if (deletedFirst != FirstCount)
            {
                Working->Forward = First;
                First->Backward = Working;
            }
            if (deletedSecont != SecondCount)
            {
                Working->Forward = Second;
                Second->Backward = Working;
            }
            return Base;
        }

        template<typename _ListType>
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
                    if (tmp->_forward == nullptr)
                        return false;
                    tmp = tmp->_forward;
                }
                _node = tmp;
                return true;
            }

            /**
             * Move to the previous element. Return true if can, false otherwise.
             * The iterator is always valid at the new position.
             */
            inline bool Back()
            {
                return Next(1);
            }

            /**
             * Move {@code how_many} elements after actual element. Return true, if can, otherwise false.
             * If the return value is false, then the position of the iterator was not changed.
             */
            bool Back(unsigned int how_many)
            {
                Node* tmp = _node;
                for (unsigned int a = 0; a < how_many; a++)
                {
                    if (tmp->_backward == nullptr)
                        return false;
                    tmp = tmp->_backward;
                }
                _node = tmp;
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
        };

    public:
        class ConstIterator : public BaseIterator<const List>
        {
            friend class List;
        protected:
            ConstIterator(Node* node, const List* list) : BaseIterator<const List>(node, list)
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
            ConstIterator operator+(unsigned int v)
            {
                ConstIterator tmp(*this);
                tmp.Next(v);
                return tmp;
            }

            /**
             * Prefix decrement operator.
             */
            ConstIterator& operator--()
            {
                this->Back();
                return *this;
            }

            /**
             * Postfix decrement operator.
             */
            ConstIterator operator--(int)
            {
                ConstIterator tmp(*this);
                this->Back();
                return tmp;
            }

            /**
             * Minus operator with the number.
             * Move iterator {@code v} places before the current node.
             * If the position is not valid, iterator stay at the same node.
             * @param v Number of nodes to skip.
             */
            ConstIterator operator-(unsigned int v)
            {
                ConstIterator tmp(*this);
                tmp.Back(v);
                return tmp;
            }
        };

        class Iterator : public BaseIterator<List>
        {
            friend class List;
        protected:
            Iterator(Node* node, List* list) : BaseIterator<List>(node, list)
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
            Iterator operator+(unsigned int v)
            {
                Iterator tmp(*this);
                tmp.Next(v);
                return tmp;
            }

            /**
             * Prefix decrement operator.
             */
            Iterator& operator--()
            {
                this->Back();
                return *this;
            }

            /**
             * Postfix decrement operator.
             */
            Iterator operator--(int)
            {
                Iterator tmp(*this);
                this->Back();
                return tmp;
            }

            /**
             * Minus operator with the number.
             * Move iterator {@code v} places before the current node.
             * If the position is not valid, iterator stay at the same node.
             * @param v Number of nodes to skip.
             */
            Iterator operator-(unsigned int v)
            {
                Iterator tmp(*this);
                tmp.Back(v);
                return tmp;
            }

            //TODO insert, delete
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
        List(T* array, unsigned int count) : List()
        {
            T* e = array + count;

            for (; array != e; array++)
            {
                new (_last->Pointer()) T(*array);

                try
                {
                    _last->_forward = new Node();
                }
                catch(...)
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
            if(!iter.Next(index) || iter == this->End())
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
            if(!iter.Next(index) || iter == this->End())
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
            unsigned int deleted = 0;
            for(; deleted < count && _size > 0; deleted++)
            {
                _first->Value().~T();
                _first->_forward->_backward = nullptr;
                Node* toDelete = _first;
                _first = _first->_forward;
                _size--;
                delete toDelete;
            }
            return deleted;
        }

        /**
         * Push count elements from the array in the end of the list.
         * The method is exception safe, in case of exception the list stays in the same state.
         * @param array Elements to insert.
         * @param count Number of elements to insert.
         */
        void Push(T* array, unsigned int count)
        {
            List tmp(array, count);

            Node* to_insert_begin = tmp._first;
            Node* to_insert_end = tmp._last->_backward;

            to_insert_begin->_backward = _last->_backward;
            _last->_backward->_forward = to_insert_begin;
            to_insert_end->_forward = _last;
            _last->_backward = to_insert_end;

            _size += tmp._size;

            tmp._first = tmp._last;
            tmp._size = 0;
        }

        /**
         * Insert element at the end of the list.
         * @param value Element to insert.
         */
        void Push(T& value)
        {
            this->Push(&value, 1);
        }

        /**
         * Insert element at the beginning of the list.
         * @param value Element to insert.
         */
        void Insert(T &value)
        {
            this->Insert(&value, 1);
        }

        /**
         * Insert elements at the beginning of the list.
         * The method is exception safe, in case of exception the list stays in the same state.
         * @param array Array of elements to insert.
         * @param count Number of elements to insert.
         */
        void Insert(T* array, unsigned int count)
        {
            List tmp(array, count);

            Node* current_first = _first;
            _first = tmp._first;
            tmp._last->_backward->_forward = current_first;
            current_first->_backward = tmp._last->_backward;
            _size += tmp._size;

            tmp._first = tmp._last;
            tmp._first->_forward = nullptr;
            tmp._first->_backward = nullptr;
            tmp._size = 0;
        }

        /**
         * Convert list to array
         * Must be clared by delete[]
         * TODO
         */
        T* ToArray(int& Count)
        {
            Count = Size();
            if (Count == 0)
                return nullptr;
            T* Array = new T[Count];
            if (Array == nullptr)
            {
                Count = 0;
                return nullptr;
            }

            T* Base = Array;
            Iterator temp = Begin();
            while (temp.IsValidIterator())
            {
                *Array = *temp.GetValue();
                Array++;
                temp.Next();
            }
            return Base;
        }

        /**
         * Convert list to array pointing to original source in list
         * Must be clared by delete []
         * TODO
         */
        T** ToWriteArray(int& Count)
        {
            Count = Size();
            if (Count == 0)
                return nullptr;
            T** Array = new T* [Count];
            if (Array == nullptr)
            {
                Count = 0;
                return nullptr;
            }

            T** Base = Array;
            Iterator temp = Begin();
            while (temp.IsValidIterator())
            {
                *Array = temp.GetValue();
                Array++;
                temp.Next();
            }
            return Base;
        }

        //TODO
        void Sort(bool(* IsFirstBeforeSecond)(const T* const First, const T* const Second))
        {
            Node* Working = MergeSort(this->First, Size(), IsFirstBeforeSecond);
            this->First = Working;
            Node* Temp = Working;
            while (Temp->Forward != nullptr)
                Temp = Temp->Forward;
            this->Last->Backward = Temp;
            Temp->Forward = this->Last;
        }

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

#ifdef ___OUT_OF_MEMORY_TESTING
        static void _SetAllocationLimit(unsigned int limit)
        {
            Node::allocation = limit;
        }
#endif

    };
}


#ifdef ___OUT_OF_MEMORY_TESTING
template<typename T>
unsigned int Templates::List<T>::Node::allocation = ~0U;
#endif


#endif
