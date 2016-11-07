#ifndef TEMPLATES_VECTOR_H
#define TEMPLATES_VECTOR_H

#include "IteratorsDefinitions.h"
#include "Exceptions.h"

namespace Templates
{
    /**
     * Represent one way linked list
     */
    template<typename T>
    class Vector
    {
    protected:
        class Node
        {
        public:
            T Value;
            Node* Next = NULL;
        };

        Node* First = NULL;
    public:
        class Iterator :
                virtual public Iterators::ForwardIteratorBase<T>,
                virtual public Iterators::DeletingForwardIteratorBase<T>
        {
            friend class Vector;

        private:
            Node* WorkingNode;
            Vector* Vect;

            /**
             * Create iterator chained with Vector.
             */
            Iterator(Node* WorkingNode, Vector* Vec)
            {
                this->WorkingNode = WorkingNode;
                this->Vect = Vec;
            }

        public:

            /**
             * Creates new invalid iterator.
             */
            Iterator()
            {
                WorkingNode = NULL;
                Vect = NULL;
            }

            /**
             * Copy contstructor
             */
            Iterator(const Iterator& Copy)
            {
                this->WorkingNode = Copy.WorkingNode;
                this->Vect = Copy.Vect;
            }

            /**
             * Assignment operator
             */
            Iterator& operator=(const Iterator& Second)
            {
                if (this != &Second)
                {
                    this->WorkingNode = Second.WorkingNode;
                    this->Vect = Second.Vect;
                }
                return *this;
            }

            /**
             * Clone iterator
             */
            Iterator Clone()
            {
                return Iterator(this->WorkingNode, this->Vect);
            }

            /**
             * Check if are iterators at the same position
             * @param Second Iterator compare to
             * @return True if are iterators equal, false otherwise
             */
            virtual bool AreEqual(const Iterator& Second) const
            {
                return this->WorkingNode == Second.WorkingNode;
            }

            /**
             * Return value in actual element.
             * Return NULL, if is invalid.
             */
            virtual T* GetValue()
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == NULL)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                if (!IsValidIterator())
                    return NULL;
                return &(WorkingNode->Value);
            }

            /**
             * Set value of object, where is pointing. Type must have assignment operator.
             * Throw OutOfRangeException, if is invalid.
             */
            virtual void SetValue(const T& Val)
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == NULL)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                if (!IsValidIterator())
                    throw new OutOfRangeException();
                WorkingNode->Value = Val;
            }

            /**
             * Returns true, if validatior points to valid object, otherwise false
             * (means that we can call GetValue or SetValue)
             */
            virtual bool IsValidIterator() const
            {
                return Vect != NULL && WorkingNode != NULL && WorkingNode->Next != NULL;
            }

            virtual bool isEnding() const
            {
                return Vect != NULL && WorkingNode != NULL && WorkingNode->Next == NULL;
            }

            /**
             * Move to the next element. Return true if can, false otherwise.
             * Note that it don't mean, that is iterator valid on the new position.
             */
            virtual bool Next()
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == NULL)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                return Next(1);
            }

            /**
             * Move @HowMany elements after actual element. Return true, if can, otherwise false.
             * Note that it don't mean, that is iterator valid on the new position.
             */
            virtual bool Next(int HowMany)
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == NULL)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                Node* Temp = WorkingNode;
                for (int a = 0; a < HowMany; a++)
                {
                    if (Temp->Next == NULL)
                        return false;
                    Temp = Temp->Next;
                }
                WorkingNode = Temp;
                return true;
            }

            /**
             * Return true, if is actual iterator equal with @Second iterator.
             * Otherwise false
             */
            bool AreEqual(const Iterator& Second)
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == NULL)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                return WorkingNode == Second.WorkingNode;
            }

            /**
             * Insert Count elements after actual element. First value in Array will be first after actual element.
             * Returns how many values was inserted, -1 if there was a error.
             */
            virtual int Insert(const T* const Values, int Count)
            {
                if (!IsValidIterator() || Count < 1)
                    return -1;

                Node* Begin = WorkingNode;
                Node* End = WorkingNode->Next;

                Node* Previous = End;
                for (int a = Count - 1; a >= 0; a--)
                {
                    Node* Temp = new Node;
                    Temp->Value = *(Values + a);

                    Temp->Next = Previous;
                    Begin->Next = Temp;
                    Previous = Temp;
                }
                return true;
            }

            /**
             * Insert Value after actual element.
             * Return 1, if was element inserted, 0 if doesn't. -1 if there was a error.
             */
            virtual int Insert(const T& Value)
            {
                return Insert(&Value, 1);
            }

            /**
             * Return true, if is actual iterator greater (points to farer elelment) then @Second.
             * Otherwise false.
             */
            bool IsGreaterThan(const Iterator& Second)
            {
                Node* Temp = Second.WorkingNode->Next;
                while (Temp != NULL)
                {
                    if (Temp == this->WorkingNode)
                        return true;
                    Temp = Temp->Next;
                }
                return false;
            }

            /**
             * Delete @Count elements after actual element.
             * Return count of elements, that was deleted.
             */
            virtual int DeleteAfter(int Count)
            {
#ifdef ADDITIONAL_TESTS
                if (WorkingNode == NULL)
                    throw new InternalException(__FILE__, __LINE__);
#endif
                if (!IsValidIterator())
                    throw new OutOfRangeException();
                Node* Base = WorkingNode;
                Node* Temp = WorkingNode->Next;
                int deleted = 0;
                for (int a = 0; a < Count && Temp->Next != NULL; a++)
                {
                    Node* ToDelete = Temp;
                    Temp = ToDelete->Next;
                    delete ToDelete;
                    deleted++;
                }
                Base->Next = Temp;
                return deleted;
            }
        };

    protected:
        /**
         * Check, if is iterator chained with instance of this Vector.
         */
        bool IsMyIterator(const Iterator& Iter)
        {
#ifdef ADDITIONAL_TESTS
            if (First == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            Node* Temp = First;
            while (Temp != NULL)
            {
                if (Temp == Iter.WorkingNode)
                    return true;
                Temp = Temp->Next;
            }
            return false;
        }

        /**
         * Return index of element, where @Iter points.
         * Return -1, if was error.
         */
        int Index(const Iterator& Iter)
        {
            if (!IsMyIterator(Iter) || Iter.IsValidIterator())
                return -1;

            int index = 0;
            Node* Working = First;
            while (Working != NULL)
            {
                if (Working == Iter.WorkingNode)
                    return index;
                Working = Working->Next;
                index++;
            }
            return -1;
        }

    public:

        /**
         * Creates new instance of Vector
         */
        Vector() : Vector(0)
        {}

        /**
         * Creates new vector with @Capacity. This space could be iterator and is valid.
         */
        Vector(int Capacity)
        {
            Node* Temp = new Node;
            Temp->Next = NULL;
            for (int a = 0; a < Capacity; a++)
            {
                Node* Created = new Node;
                Created->Next = Temp;
                Temp = Created;
            }
            First = Temp;
        }

        /**
         * Creates new Vector and insert @Count elements from Array.
         */
        Vector(const T* const Array, int Count) : Vector(Count)
        {
            Node* WorkingWith = First;
            for (int a = 0; a < Count; a++)
            {
                WorkingWith->Value = *(Array + a);
                WorkingWith = WorkingWith->Next;
            }
        }

        /**
         * Copy constructor
         */
        Vector(const Vector& Copy)
                : Vector(0)
        {
            int val;
            T* Array = Copy.ToArray(val);
            this->Insert(Array,val);
            delete[] (Array);
        }

        /**
         * Assignment operator
         */
        Vector& operator=(const Vector& Second)
        {
            if (this != &Second)
            {
                this->Clear();
                int val;
                T* Array = Second.ToArray(val);

                Node* prev = this->First;
                Node* created = this->First;
                for (int a = val-1; a >= 0; a--)
                {
                    created = new Node;
                    created->Value = Array[a];
                    created->Next = prev;
                    prev = created;
                }
                this->First = created;

                delete [] (Array);
            }
            return *this;
        }

        /**
         * Destructor
         */
        ~Vector()
        {
            this->Clear();
            delete First;
        }

        /**
         * Creates array with new[], where will be stored elements.
         * Return pointer to array and Count of elements in parametr.
         * If fails, return NULL.
         */
        T* ToArray(int& Count) const
        {
#ifdef ADDITIONAL_TESTS
            if (First == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            Count = Size();
            if (Count == 0)
                return NULL;
            T* Array = new T[Count];
            if (Array == NULL)
                return NULL;

            Node* Temp = First;
            int SizeOfVector = Size();
            for (int a = 0; a < SizeOfVector; a++)
            {
                *(Array + a) = Temp->Value;
                Temp = Temp->Next;
            }
            return Array;
        }

        /**
         * Return iterator to beginning of Vector.
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
         * Return iterator to element after last element.
         * This iterator will be not valid.
         */
        Iterator End()
        {
#ifdef ADDITIONAL_TESTS
            if (First == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            Node* Temp = First;
            while (Temp->Next != NULL)
                Temp = Temp->Next;
            return Iterator(Temp, this);
        }

        /**
         * Return iterator at specified position.
         * Return true if fails.
         */
        bool At(int Position, Iterator& BackIterator)
        {
            if (Position > Size())
                return false;
            BackIterator = Begin();
            return BackIterator.Next(Position - 1);
        }

        /**
         * Return count of elements in Vector.
         */
        int Size() const
        {
#ifdef ADDITIONAL_TESTS
            if (First == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            Node* Working = First;
            int Count = 0;
            while (Working->Next != NULL)
            {
                Count++;
                Working = Working->Next;
            }
            return Count;
        }

        /**
         * Return true, if is array empty.
         */
        inline bool IsEmpty()
        {
#ifdef ADDITIONAL_TESTS
            if (this->First == NULL)
                throw new InternalException();
#endif
            return this->First->Next == NULL;
        }

        /**
         * Remove all elements in Array.
         */
        inline int Clear()
        {
            return Clear(0, Size());
        }

        /**
         * Removes elements between @From and @To.
         * @From and @To will not be deleted.
         * Return count of deleted items.
         */
        int Clear(Iterator& From, Iterator& To)
        {
#ifdef ADDITIONAL_TESTS
            if (From.WorkingNode == NULL || First == NULL || To.WorkingNode == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            if (!IsMyIterator(From) || !IsMyIterator(To) || !To.IsGreaterThan(From))
                return 0;

            int deleted = 0;

            Node* Begin = From.WorkingNode;
            Node* End = To.WorkingNode;

            Node* Temp = Begin->Next;
            while (Temp != End)
            {
                Node* ToDelete = Temp;
                Temp = ToDelete->Next;
                delete ToDelete;
                deleted++;
            }
            Begin->Next = End;
            return deleted;
        }

        /**
         * Removes @HowMany elements from Vector.
         * First removed element will be @IndexFromth element
         */
        int Clear(int IndexFrom, int HowMany)
        {
#ifdef ADDITIONAL_TESTS
            if (First == NULL)
                throw new InternalException(__FILE__, __LINE__);
#endif
            if (HowMany == 0 || IndexFrom > Size())
                return 0;

            int deleted = 0;
            if (IndexFrom == 0)
            {
                Node* Temp = First;
                for (int a = 0; a < HowMany && Temp->Next != NULL; a++)
                {
                    Node* ToDelete = Temp;
                    Temp = ToDelete->Next;
                    delete ToDelete;
                    deleted++;
                }
                First = Temp;
            }
            else
            {
                Node* Stay = First;
                for (int a = 1; a < IndexFrom && Stay->Next != NULL; a++)
                    Stay = Stay->Next;

                Node* Temp = Stay->Next;
                for (int a = 0; a < HowMany && Temp->Next != NULL; a++)
                {
                    Node* ToDelete = Temp;
                    Temp = ToDelete->Next;
                    delete ToDelete;
                    deleted++;
                }
                if (Stay->Next != Temp)
                    Stay->Next = Temp;
            }
            return deleted;
        }

        int Insert(T& Value)
        {
            Node* temp = new Node;
            temp->Next = this->First;
            temp->Value = Value;
            this->First = temp;
            return 1;
        }

        int Insert(T* Array, int Count)
        {
            int inserted = 0;
            for (int a = Count-1; a >= 0; a--)
                inserted += this->Insert(Array[a]);
            return inserted;
        }
    };
}


#endif //TEMPLATES_QUEUE_H
