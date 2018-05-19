#ifndef __TEMPLATELIST_H_
#define __TEMPLATELIST_H_

#include "IteratorsDefinitions.h"
#include "Exceptions.h"

namespace Templates
{
    /**
     * Represent two way linked list
     */
    template<typename T>
    class List
    {
    protected:
        class Node
        {
        public:
            Node* Forward;
            Node* Backward;
            T Value;

            Node()
            {
                Forward = NULL;
                Backward = NULL;
            }

            Node(Node* Next, Node* Back)
            {
                Forward = Next;
                Backward = Back;
            }
        };

        Node* First;
        Node* Last;
        int size;

        Node* MergeSort(Node* WhatToSort, int HowMany,
                        bool(*IsFirstBeforeSecond)(const T* const First, const T* const Second))
        {
            if (HowMany <= 1)
            {
                WhatToSort->Forward = NULL;
                WhatToSort->Backward = NULL;
                return WhatToSort;
            }
            int FirstCount = HowMany / 2;
            int SecondCount = HowMany - FirstCount;
            Node* SecondNode = WhatToSort;
            for (int a = 0; a < FirstCount; a++)
            {
                SecondNode = SecondNode->Forward;
            }
            Node* First = MergeSort(WhatToSort, FirstCount,IsFirstBeforeSecond);
            Node* Second = MergeSort(SecondNode, SecondCount,IsFirstBeforeSecond);
            Node* ToReturn = Join(First, FirstCount, Second, SecondCount,IsFirstBeforeSecond);
            return ToReturn;
        }
        Node* Join(Node* First, int FirstCount,
                   Node* Second, int SecondCount,
                   bool(*IsFirstBeforeSecond)(const T* const First, const T* const Second))
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
                Second=Second->Forward;
            }
            Working->Backward = NULL;
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
            if(deletedFirst != FirstCount)
            {
                Working->Forward = First;
                First->Backward = Working;
            }
            if(deletedSecont != SecondCount)
            {
                Working->Forward = Second;
                Second->Backward = Working;
            }
            return Base;
        }
    public:
        class Iterator : public virtual Iterators::DeletingBackwardIteratorBase<T>
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
                WorkingNode = NULL;
                ListInstance = NULL;
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
                return WorkingNode != NULL && WorkingNode->Forward != NULL;
            }

            /**
             * Return value in specific element. Otherwise NULL.
             */
            virtual T* GetValue()
            {
                if (!IsValidIterator())
                    return NULL;
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
                    if (Temp->Forward == NULL)
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
                if (WorkingNode == NULL)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                Node* Temp = WorkingNode;
                for (int a = 0; a < HowMany; a++)
                {
                    if (Temp->Backward == NULL)
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
                if (WorkingNode == NULL)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                if (WorkingNode->Forward == NULL)
                    return -1;

                for (int a = Count - 1; a >= 0; a--)
                    if (Insert(*(Values + a)) != 1)
                    {
                        this->ListInstance->size += Count-1-a;
                        return Count - 1 - a;
                    }
                this->ListInstance->size += Count;
                return Count;
            }

            /**
             * Insert Value after actual element.
             * Return 1, if was element inserted, 0 if doesn't. -1 if there was a error.
             */
            virtual int Insert(const T& Value)
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == NULL)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                if (WorkingNode->Forward == NULL)
                    return -1;

                Node* Temp = new Node;
                Temp->Value = Value;

                Node* Next = WorkingNode->Forward;
                Node* Back = WorkingNode;

                Temp->Backward = Back;
                Temp->Forward = Next;
                Next->Backward = Temp;
                Back->Forward = Temp;

                this->ListInstance->size++;
                return 1;
            }

            /**
             * Insert Value before actual element.
             * Return 1, if was element inserted, 0 if doesn't. -1 if there was a error.
             */
            int InsertBefore(T Value)
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == NULL)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                Node* NewNode = new Node;
                NewNode->Value = Value;

                if (WorkingNode == this->ListInstance->First)
                {
                    this->ListInstance->First = NewNode;
                    NewNode->Forward = WorkingNode;
                    NewNode->Backward = NULL;
                    WorkingNode->Backward = NewNode;
                    this->ListInstance->size++;
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
                    this->ListInstance->size++;
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
                if (ListInstance == NULL || WorkingNode == NULL)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                return this->ListInstance->Delete(*this, Count);
            }

            int DeleteThis()
            {
                if(!IsValidIterator())
                    return 0;
                if(WorkingNode==ListInstance->First)
                {
                    Node* Next = WorkingNode->Forward;
                    ListInstance->First = Next;
                    Next->Backward=NULL;
                    delete WorkingNode;
                    WorkingNode = Next;
                    this->ListInstance->size--;
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
                    this->ListInstance->size--;
                    return 1;
                }
            }

            /**
             * Return true, if are iterators equal.
             */
            bool AreEqual(const Iterator& Second)
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == NULL || Second.WorkingNode == NULL)
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
                while (Temp != NULL)
                {
                    if (Temp == this->WorkingNode)
                        return true;
                    Temp = Temp->Forward;
                }
                return false;
            }

            void FindBestFitting(bool(*IsFirstBeforeSecond)(const T* const First, const T* const Second))
            {
                if(!IsValidIterator())
                    return;

                Node* Specific = WorkingNode;
                Node* Temp = WorkingNode;
                while(Temp->Forward != NULL)
                {
                    if(IsFirstBeforeSecond(&Temp->Value,&Specific->Value))
                        Specific = Temp;
                    Temp = Temp->Forward;
                }
                WorkingNode = Specific;
                return;
            }
        };

    public:
        /**
         * Check, if is iterator chained with actual instance of list.
         */
        bool IsMyIterator(const Iterator& Iter)
        {
#ifdef ADDITIONAL_TESTS
            if (Iter.WorkingNode == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            if (Iter.ListInstance != this)
                return false;
            Node* Temp = Iter.WorkingNode;
            while (Temp != NULL)
            {
                if (Temp == Last)
                    return true;
                Temp = Temp->Forward;
            }
            return false;
        }

        /**
         * Constructor with empty capacity.
         */
        List()
        {
            Node* Temp = new Node;
            First = Temp;
            Last = Temp;
            this->size = 0;
        }

        /**
         * Constructor with specific @Capacity.
         */
        List(int Capacity) : List()
        {
            if (Capacity < 1)
                return;
            for (int a = 0; a < Capacity; a++)
            {
                Node* Temp = new Node;
                First->Backward = Temp;
                Temp->Forward = First;
                First = Temp;
            }
            this->size = Capacity;
        }

        /**
         * Create list with @Count elements and set values from @Array.
         */
        List(T* Array, int Count) : List(Count)
        {
            if (Count < 1 || Array == NULL)
                throw new InvalidArgumentException("Cannot pass null array with count < 1", __LINE__);
#ifdef ADDITIONAL_TESTS
            if (First == NULL || Last == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            Node* Temp = First;
            while (Temp->Forward != NULL)
            {
                Temp->Value = *Array;
                Array++;
                Temp = Temp->Forward;
            }
            return;
        }


        /**
         * Copy constructor
         */
        List(const List& Copy) : List()
        {
            if(Copy.Size()==0)
                    return;

            Node* Start = Copy.First;
            Node* End = Copy.Last;
            Node* Temp = Start;
            do
            {
                this->End().InsertBefore(Temp->Value);
                Temp = Temp->Forward;
            }while(Temp!=End);
        }

        /**
         * Assignment operator.
         */
        List& operator=(const List& Second)
        {
            if(this==&Second)
                return *this;

            this->Delete();

            if(Second.Size()==0)
                return *this;

            Node* Start = Second.First;
            Node* End = Second.Last;
            Node* Temp = Start;
            do
            {
                this->End().InsertBefore(Temp->Value);
                Temp = Temp->Forward;
            }while(Temp!=End);
            return *this;
        }

        ~List()
        {
            Node* Temp = First;
            while (Temp != NULL)
            {
                Node* ToDelete = Temp;
                Temp = ToDelete->Forward;
                delete ToDelete;
            }
        }

        /**
         * Return count of elements in list.
         */
        int Size() const
        {
#ifdef ADDITIONAL_TESTS
            if (First == NULL || Last == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            return this->size;
            /*
            Node* Temp = First;
            int Count = 0;
            while (Temp->Forward != NULL)
            {
                Temp = Temp->Forward;
                Count++;
            }
            return Count;*/
        }

        /**
         * Return iterator to begin.
         */
        Iterator Begin()
        {
#ifdef ADDITIONAL_TESTS
            if (First == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            return Iterator(First, this);
        }

        /**
         * Return iterator one position after last element.
         * Note that this iterator can move back, but is invalid.
         */
        Iterator End()
        {
#ifdef ADDITIONAL_TESTS
            if (Last == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            return Iterator(Last, this);
        }

        /**
         * Return iterator chained with @Indexth element in array.
         * If is @Index bigger than size of list, is equal to @End()
         */
        Iterator At(int Index)
        {
#ifdef ADDITIONAL_TESTS
            if (First == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            Node* Temp = First;
            int a;
            for (a = 0; a < Index && First->Forward != NULL; a++)
                Temp = Temp->Forward;
            return Iterator(Temp, this);
        }

        /**
         * Delete all elements in list.
         */
        int Delete()
        {
            return this->Delete(0xFFFFFFFF >> 1);
        }

        /**
         * Delete @Count elements from begining of list.
         * Return count of deleted items.
         */
        int Delete(int Count)
        {
            if (Size() == 0)
                return 0;
            int deleted = 0;
            if(Count>1)
            {
                Iterator Temp = Begin();
                deleted = Delete(Temp, Count - 1);
            }
            //delete first one
            Node* Temp = First->Forward;
            delete First;
            First = Temp;
            deleted++;
            this->size--;
            return deleted;
        }

        /**
         * Delete @HowMany=1 elements from Iterator.
         * Return count of deleted items.
         */
        int Delete(Iterator& Iter, int HowMany = 1)
        {
            if (HowMany < 1 || Iter.WorkingNode == Last)
                throw new OutOfRangeException();

            if (!IsMyIterator(Iter))
                throw new InvalidArgumentException("Iterator is not chain with this instance", __LINE__);

#ifdef ADDITIONAL_TESTS
            if (Iter.WorkingNode == NULL || Iter.ListInstance != this)
                throw new InternalException(__FILE__, __LINE__);
#endif
            Node* ToDelete = Iter.WorkingNode->Forward;
            int deleted = 0;
            while (ToDelete->Forward != NULL && deleted < HowMany)
            {
                Node* Temp = ToDelete;
                ToDelete = Temp->Forward;
                delete Temp;
                deleted++;
            }
            ToDelete->Backward = Iter.WorkingNode;
            Iter.WorkingNode->Forward = ToDelete;
            this->size -= deleted;
            return deleted;
        }

        /**
         * Return true, if is list empty.
         */
        bool IsEmpty()
        {
#ifdef ADDITIONAL_TESTS
            if (First == NULL || Last == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            return Size() == 0;
        }

        /**
         * Convert list to array
         * Must be clared by delete[]
         */
        T* ToArray(int& Count)
        {
            Count = Size();
            if(Count==0)
                return NULL;
            T* Array = new T[Count];
            if(Array==NULL)
            {
                Count=0;
                return NULL;
            }

            T* Base = Array;
            Iterator temp = Begin();
            while(temp.IsValidIterator())
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
         */
        T** ToWriteArray(int& Count)
        {
            Count = Size();
            if(Count==0)
                return NULL;
            T** Array = new T*[Count];
            if(Array==NULL)
            {
                Count=0;
                return NULL;
            }

            T** Base = Array;
            Iterator temp = Begin();
            while(temp.IsValidIterator())
            {
                *Array = temp.GetValue();
                Array++;
                temp.Next();
            }
            return Base;
        }

        void Sort(bool(*IsFirstBeforeSecond)(const T* const First, const T* const Second))
        {
            Node* Working = MergeSort(this->First, Size(),IsFirstBeforeSecond);
            this->First = Working;
            Node* Temp = Working;
            while (Temp->Forward != NULL)
                Temp = Temp->Forward;
            this->Last->Backward = Temp;
            Temp->Forward = this->Last;
            return;
        }

    };
}

#endif
