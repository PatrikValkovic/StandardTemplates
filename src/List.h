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

        class Iterator
        {
            friend class List;

        private:
            Node* WorkingNode;
            List* ListInstance;
        public:
            /**
             * Creates invalid iterator.
             */
            Iterator()
            {
                WorkingNode = nullptr;
                ListInstance = nullptr;
            }

            /**
             * Create iterator chained with specific list
             */
            Iterator(List::Node* Node, List* ListInstance)
            {
                WorkingNode = Node;
                this->ListInstance = ListInstance;
            }

            /**
             * Copy constructor
             */
            Iterator(const Iterator& Copy)
            {
                this->WorkingNode = Copy.WorkingNode;
                this->ListInstance = Copy.ListInstance;
            }

            /**
             * Assignment operator
             */
            Iterator& operator=(const Iterator& Second)
            {
                if (this != &Second)
                {
                    this->WorkingNode = Second.WorkingNode;
                    this->ListInstance = Second.ListInstance;
                }
                return *this;
            }

            /**
             * Clone iterator
             */
            Iterator Clone()
            {
                return Iterator(this->WorkingNode, this->ListInstance);
            }

            virtual bool AreEqual(const Iterator& second) const
            {
                return this->WorkingNode == second.WorkingNode;
            }

            /**
             * Return true, if is valis iterator, otherwise false.
             * Valid mean, that can call GetValue, SetValue etc.
             */
            virtual bool IsValidIterator() const
            {
                return WorkingNode != nullptr && WorkingNode->Forward != nullptr;
            }

            /**
             * Return value in specific element. Otherwise nullptr.
             */
            virtual T* GetValue()
            {
                if (!IsValidIterator())
                    return nullptr;
                return &(WorkingNode->Value);
            }

            /**
             * Set value in specific element.
             * Note that value must have assignment operator defined.
             */
            virtual void SetValue(const T& Val)
            {
#ifdef ADDITIONAL_TESTS
                if (!IsValidIterator())
                    throw new InternalException(__FILE__, __LINE__);
#endif
                WorkingNode->Value = Val;
            }

            /**
             * Move to next element. Return true if can.
             * Note that true don't mean, that iterator is valid.
             */
            virtual bool Next()
            {
                return Next(1);
            }

            /**
             * Move to #HowManyth element. Return true if can.
             * Note that true don't mean, that iterator is valid.
             */
            virtual bool Next(int HowMany)
            {
#ifdef ADDITIONAL_TESTS
                if (!IsValidIterator())
                    return false;
#endif
                Node* Temp = WorkingNode;
                for (int a = 0; a < HowMany; a++)
                {
                    if (Temp->Forward == nullptr)
                        return false;
                    Temp = Temp->Forward;
                }
                WorkingNode = Temp;
                return true;
            }

            /**
             * Move to previous element. Return true if can, otherwise false.
             */
            virtual bool Back()
            {
                return Back(1);
            }

            /**
             * Move to @HowManyth element before actual element.
             * Return true if can, otherwise false;
             */
            virtual bool Back(int HowMany)
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == nullptr)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                Node* Temp = WorkingNode;
                for (int a = 0; a < HowMany; a++)
                {
                    if (Temp->Backward == nullptr)
                        return false;
                    Temp = Temp->Backward;
                }
                WorkingNode = Temp;
                return true;
            }

            /**
             * Insert Count elements after actual element. First value in Array will be first after actual element.
             * Returns how many values was inserted, -1 if there was a error.
             */
            virtual int Insert(const T* const Values, int Count)
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == nullptr)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                if (WorkingNode->Forward == nullptr)
                    return -1;

                for (int a = Count - 1; a >= 0; a--)
                    if (Insert(*(Values + a)) != 1)
                    {
                        this->ListInstance->_size += Count - 1 - a;
                        return Count - 1 - a;
                    }
                this->ListInstance->_size += Count;
                return Count;
            }

            /**
             * Insert Value after actual element.
             * Return 1, if was element inserted, 0 if doesn't. -1 if there was a error.
             */
            virtual int Insert(const T& Value)
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == nullptr)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                if (WorkingNode->Forward == nullptr)
                    return -1;

                Node* Temp = new Node;
                Temp->Value = Value;

                Node* Next = WorkingNode->Forward;
                Node* Back = WorkingNode;

                Temp->Backward = Back;
                Temp->Forward = Next;
                Next->Backward = Temp;
                Back->Forward = Temp;

                this->ListInstance->_size++;
                return 1;
            }

            /**
             * Insert Value before actual element.
             * Return 1, if was element inserted, 0 if doesn't. -1 if there was a error.
             */
            int InsertBefore(T Value)
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == nullptr)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                Node* NewNode = new Node;
                NewNode->Value = Value;

                if (WorkingNode == this->ListInstance->First)
                {
                    this->ListInstance->First = NewNode;
                    NewNode->Forward = WorkingNode;
                    NewNode->Backward = nullptr;
                    WorkingNode->Backward = NewNode;
                    this->ListInstance->_size++;
                    return 1;
                }
                else
                {
                    Node* Before = WorkingNode->Backward;
                    Node* After = WorkingNode;

                    NewNode->Forward = After;
                    NewNode->Backward = Before;
                    Before->Forward = NewNode;
                    After->Backward = NewNode;
                    this->ListInstance->_size++;
                    return 1;
                }
            }

            /**
             * Insert @Count elements before actual element from @Array.
             * Return count of inserted elements.
             */
            int InsertBefore(T* Array, int Count)
            {
                for (int a = 0; a < Count; a++)
                    if (!InsertBefore(*(Array + a)))
                        return a;
                return Count;
            }

            /**
             * Delete @Count elements before actual element.
             * Return count of deleted elements.
             */
            virtual int DeleteBefore(int Count)
            {
                Iterator working(*this);
                int ToDelete = 0;
                for (int a = 0; a <= Count && working.Back(); a++)
                    ToDelete++;
                if (ToDelete == 0)
                    return 0;
                return this->ListInstance->Delete(working, ToDelete);
            }

            /**
             * Delete @Count elements after actual element.
             * Return count of elements, that was deleted.
             */
            virtual int DeleteAfter(int Count)
            {
#ifdef ADDITIONAL_TESTS
                if (ListInstance == nullptr || WorkingNode == nullptr)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                return this->ListInstance->Delete(*this, Count);
            }

            int DeleteThis()
            {
                if (!IsValidIterator())
                    return 0;
                if (WorkingNode == ListInstance->First)
                {
                    Node* Next = WorkingNode->Forward;
                    ListInstance->First = Next;
                    Next->Backward = nullptr;
                    delete WorkingNode;
                    WorkingNode = Next;
                    this->ListInstance->_size--;
                    return 1;
                }
                else
                {
                    Node* Forward = WorkingNode->Forward;
                    Node* Backward = WorkingNode->Backward;
                    Forward->Backward = Backward;
                    Backward->Forward = Forward;
                    delete WorkingNode;
                    WorkingNode = Forward;
                    this->ListInstance->_size--;
                    return 1;
                }
            }

            /**
             * Return true, if are iterators equal.
             */
            bool AreEqual(const Iterator& Second)
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == nullptr || Second.WorkingNode == nullptr)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                return WorkingNode == Second.WorkingNode;
            }

            /**
             * Return true, if is actual iterator greater then @Second.
             */
            bool IsGreaterThan(const Iterator& Second)
            {
                Node* Temp = Second.WorkingNode;
                while (Temp != nullptr)
                {
                    if (Temp == this->WorkingNode)
                        return true;
                    Temp = Temp->Forward;
                }
                return false;
            }

            void FindBestFitting(bool(* IsFirstBeforeSecond)(const T* const First, const T* const Second))
            {
                if (!IsValidIterator())
                    return;

                Node* Specific = WorkingNode;
                Node* Temp = WorkingNode;
                while (Temp->Forward != nullptr)
                {
                    if (IsFirstBeforeSecond(&Temp->Value, &Specific->Value))
                        Specific = Temp;
                    Temp = Temp->Forward;
                }
                WorkingNode = Specific;
                return;
            }
        };

    public:


        using ConstIterator = T*;

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
            return;
        }

        /**
         * Return iterator to begin.
         * TODO
         */
        Iterator Begin()
        {
#ifdef ADDITIONAL_TESTS
            if (First == nullptr)
                throw new InternalException(__FILE__, __LINE__);
#endif
            return Iterator(_first, this);
        }

        /**
         * Return iterator one position after last element.
         * Note that this iterator can move back, but is invalid.
         * TODO
         */
        Iterator End()
        {
#ifdef ADDITIONAL_TESTS
            if (Last == nullptr)
                throw new InternalException(__FILE__, __LINE__);
#endif
            return Iterator(_last, this);
        }

        /**
         * Return iterator chained with @Indexth element in array.
         * If is @Index bigger than size of list, is equal to @End()
         * TODO
         */
        Iterator At(int Index)
        {
#ifdef ADDITIONAL_TESTS
            if (First == nullptr)
                throw new InternalException(__FILE__, __LINE__);
#endif
            Node* Temp = _first;
            int a;
            for (a = 0; a < Index && _first->Forward != nullptr; a++)
                Temp = Temp->Forward;
            return Iterator(Temp, this);
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
