#ifndef __KowalSTL_H_
#define __KowalSTL_H_
#ifndef _STALIB_
#include <stdlib.h>
#include <iostream>
#include <string.h>
#endif
namespace Templates
{
    namespace Iterators
    {
        template<typename T>
        class IteratorBase
        {
        public:
            virtual bool IsValidIterator() const = 0;
            virtual T* GetValue() = 0;
            virtual void SetValue(const T& Val) = 0;
        };
        template<typename T>
        class ForwardIteratorBase : virtual public IteratorBase<T>
        {
        public:
            virtual bool Next() = 0;
            virtual bool Next(int HowMany) = 0;
        };
        template<typename T>
        class BackwardIteratorBase : virtual public ForwardIteratorBase<T>
        {
        public:
            virtual bool Back() = 0;
            virtual bool Back(int HowMany) = 0;
        };
        template<typename T>
        class InsertingIteratorBase : virtual public ForwardIteratorBase<T>
        {
        public:
            virtual int Insert(const T* const Array, int Count) = 0;
            virtual int Insert(const T& Value) = 0;
        };
        template<typename T>
        class DeletingForwardIteratorBase : virtual public InsertingIteratorBase<T>
        {
        public:
            virtual int DeleteAfter(int Count) = 0;
        };
        template<typename T>
        class DeletingBackwardIteratorBase :
                virtual public DeletingForwardIteratorBase<T>,
                virtual public BackwardIteratorBase<T>
        {
        public:
            virtual int DeleteBefore(int Count) = 0;
        };
    }
}
namespace Templates
{
    class Exception
    {
    protected:
        const char *Message;
        int LineNumber;
        virtual std::ostream &ToString(std::ostream &os) const
        {
            return os << "Error in " << this->Message << " on line " << this->LineNumber << std::endl;
        }
    public:
        Exception(const char *Message, const int &LineNumber)
        {
            this->Message = Message;
            this->LineNumber = LineNumber;
        };
        virtual ~Exception()
        { }
    private:
        friend std::ostream &operator<<(std::ostream &os, const Exception &e)
        {
            return (&e)->ToString(os);
        }
    };
    class InvalidArgumentException : public Exception
    {
    public:
        InvalidArgumentException(const char *Message, int LineNumber)
                : Exception(Message, LineNumber)
        { }
        virtual ~InvalidArgumentException()
        { }
    };
    class VectorException : public Exception
    {
    public:
        VectorException(const char *Message, int LineNumber)
                : Exception(Message, LineNumber)
        { }
        virtual ~VectorException()
        { }
    };
    class OutOfRangeException : public Exception
    {
    protected:
        virtual std::ostream &ToString(std::ostream &os)
        {
            return os << this->Message << std::endl;
        }
    public:
        OutOfRangeException() : Exception("Index is out of range.", -1)
        { }
        OutOfRangeException(const char *Message)
                : Exception(Message, -1)
        { }
        OutOfRangeException(const char *Message, int LineNumber)
                : Exception(Message, LineNumber)
        { }
        virtual ~OutOfRangeException()
        { }
    };
    class QueueException : public Exception
    {
    public:
        QueueException(const char *File, const int Line) :
                Exception(File, Line)
        { }
        virtual ~QueueException()
        { }
    };
    class ListException : public Exception
    {
    public:
        ListException(const char *File, const int Line) :
                Exception(File, Line)
        { }
        virtual ~ListException()
        { }
    };
    class ArrayException : public Exception
    {
    public:
        ArrayException(const char *File, const int Line) :
                Exception(File, Line)
        { }
        virtual ~ArrayException()
        { }
    };
    class NotImplementedException : public Exception
    {
    public:
        NotImplementedException(const char *File, const int Line) :
                Exception(File, Line)
        { }
        virtual ~NotImplementedException()
        { }
    };
}
namespace Math
{
    class IntervalException : public Templates::Exception
    {
    public:
        IntervalException(const char *File, const int Line) :
                Exception(File, Line)
        { }
        virtual ~IntervalException()
        { }
    };
}
using Templates::Exception;
namespace Math
{
    template<typename T>
    class Interval
    {
    private:
        void InsertVals(T First, T Second)
        {
            T Smaller = First < Second ? First : Second;
            T Bigger = First < Second ? Second : First;
            Begin = Smaller;
            End = Bigger;
        }
        T Begin;
        T End;
    public:
        Interval() : Interval(0, 0)
        { }
        Interval(T Begin, T End)
        {
            InsertVals(Begin, End);
        }
        T GetBegin() const
        {
            return Begin;
        }
        void SetBegin(T Value)
        {
            Begin = Value;
            InsertVals(Begin, End);
        }
        T GetEnd() const
        {
            return End;
        }
        void SetEnd(T Value)
        {
            End = Value;
            InsertVals(Begin, End);
        }
        Interval &operator=(const Interval &Second)
        {
            if (this == &Second)
                return *this;
            Begin = Second.Begin;
            End = Second.End;
            InsertVals(Begin, End);
        }
        Interval operator+(const Interval &Second) const
        {
            T Begin = Begin < Second.Begin ? Begin : Second.Begin;
            T End = End < Second.End ? Second.End : End;
            return Interval(Begin, End);
        }
        Interval operator-(const Interval &Second) const
        {
            if (Second.End < Begin || Second.Begin > End)
                return Interval(Begin, End);
            if (Second.Begin <= Begin && Second.End >= End)
                return Interval(0, 0);
            if (Second.Begin < Begin)
                return Interval(Second.End, End);
            if (Second.Begin > Begin)
                return Interval(Begin, Second.Begin);
            throw new IntervalException("Interval.h", 100);
        }
        bool operator==(const Interval &Second) const
        {
            return Begin == Second.Begin && End == Second.Begin;
        }
        bool operator!=(const Interval &Second) const
        {
            return !(*this == Second);
        }
    };
}
namespace Templates
{
    template<typename T>
    class Array
    {
    private:
        static const int BaseSize = 10;
        int Allocated;
        int Inserted;
        T **Containing;
    public:
        class Iterator : public virtual Iterators::DeletingBackwardIteratorBase<T>,
                         virtual Iterators::InsertingIteratorBase<T>
        {
        private:
            Array *Instance;
            int index;
        public:
            Iterator()
            {
                    index = -1;
                    Instance = NULL;
            }
            Iterator(Array *ArrayInstance, int index)
            {
                this->index = index;
                this->Instance = ArrayInstance;
            }
            Iterator &operator=(const Iterator &Second)
            {
                if (this == &Second)
                    return *this;
                this->Instance = Second.Instance;
                this->index = Second.index;
                return *this;
            }
            virtual bool IsValidIterator() const
            {
                return index >= 0 && Instance != NULL && index < Instance->Inserted;
            }
            virtual T *GetValue()
            {
                if (!IsValidIterator())
                    return NULL;
                return Instance->Containing[this->index];
            }
            virtual void SetValue(const T &Val)
            {
                if (!IsValidIterator())
                    return;
                *Instance->Containing[this->index] = Val;
            }
            virtual bool Next()
            {
                if (index + 1 < 0 || index + 1 > Instance->Inserted)
                    return false;
                index++;
                return true;
            }
            virtual bool Next(int HowMany)
            {
                if (index + HowMany < 0 || index + HowMany > Instance->Inserted)
                    return false;
                index += HowMany;
                return true;
            }
            virtual bool Back()
            {
                if (index - 1 < 0 || index - 1 > Instance->Inserted)
                    return false;
                index--;
                return true;
            }
            virtual bool Back(int HowMany)
            {
                if (index - HowMany < 0 || index - HowMany > Instance->Inserted)
                    return false;
                index -= HowMany;
                return true;
            }
            bool JumpToBegin()
            {
                if (Instance == NULL)
                    return false;
                index = 0;
                return true;
            }
            virtual int Insert(const T &Value)
            {
                if(!IsValidIterator())
                    return 0;
                if (!Instance->Shift(index + 1, 1))
                    return 0;
                Instance->Containing[index + 1] = new T(Value);
                return 1;
            }
            int InsertBefore(const T &Value)
            {
                if(Instance->Inserted==this->index)
                    return Instance->Push(Value);
                if (Instance->Shift(index, 1)==0)
                    return 0;
                index++;
                Instance->Containing[index - 1] = new T(Value);
                return 1;
            }
            virtual int Insert(const T *const Values, int Count)
            {
                if(!IsValidIterator())
                    return 0;
                if (!Instance->Shift(index + 1, Count))
                    return 0;
                for (int a = 0; a < Count; a++)
                    Instance->Containing[index + 1 + a] = new T(Values[a]);
                return Count;
            }
            int InsertBefore(const T *const Values, int Count)
            {
                if(Instance->Inserted==this->index)
                    return Instance->Push(Values,Count);
                if (!Instance->Shift(index, Count))
                    return 0;
                for (int a = 0; a < Count; a++)
                    Instance->Containing[index + a] = new T(Values[a]);
                index += Count;
                return Count;
            }
            virtual int DeleteBefore(int Count = 1)
            {
                if(this->Instance==NULL)
                    return 0;
                if(this->index==Instance->Inserted)
                    return Instance->DeleteFromEnd(Count);
                if(!IsValidIterator())
                    return 0;
                int temp = (-1)*this->Instance->Shift(this->index,-Count);
                index = index - temp;
                return temp;
            }
            virtual int DeleteAfter(int Count = 1)
            {
                if(!IsValidIterator())
                    return 0;
                if(index+Count>Instance->Size())
                    return Instance->DeleteFromEnd(Instance->Inserted-index-1);
                Instance->Shift(index + Count+1, -Count);
                return Count;
            }
            virtual int DeleteThis()
            {
                if (!this->IsValidIterator())
                    return 0;
                if(this->index==Instance->Inserted-1)
                    return Instance->DeleteFromEnd(1);
                Instance->Shift(index + 1, -1);
                return 1;
            }
        };
        Array(int Capacity)
        {
            Capacity = (Capacity <= 0 ? BaseSize : Capacity);
            Containing = (T **) calloc(Capacity, sizeof(T *));
            Allocated = Capacity;
            Inserted = 0;
        }
        Array() : Array(BaseSize)
        { }
        Array(const Array &Second) : Array(Second.Size())
        {
            int SizeOfSecond = Second.Size();
            for (int a = 0; a < SizeOfSecond; a++)
                Containing[a] = new T(*Second.Containing[a]);
        }
        Array(T *array, int count) : Array(count)
        {
            for (int a = 0; a < count; a++, array++)
                this->Containing[a] = new T(*array);
            Inserted = count;
        }
        ~Array()
        {
            Delete();
            free(Containing);
        }
        Array &operator=(const Array &Second)
        {
            if (this == &Second)
                return *this;
            Delete();
            this->Expand(Second.Inserted - Allocated);
            for (int a = 0; a < Second.Inserted; a++)
                Containing[a] = new T(Second.Containing[a]);
            return *this;
        }
        int Size() const
        {
            return Inserted;
        }
        int Capacity() const
        {
            return Allocated;
        }
        Iterator Begin()
        {
            return Iterator(this, 0);
        }
        Iterator End()
        {
            return Iterator(this, Inserted);
        }
        Iterator At(int index)
        {
            return Iterator(this, index);
        }
        bool TryAt(int index, Iterator &Out)
        {
            if (index >= Inserted || index < 0)
                return false;
            Out = Iterator(this, index);
            return true;
        }
    private:
        T& GetElementAtIndex(int index) const
        {
            if (index >= Inserted || index < 0)
                throw new() OutOfRangeException("Operator is out of range in Array", 418);
            return *Containing[index];
        }
        void Expand(int By = 0)
        {
            if (By == 0)
                By = int(Allocated * 0.4 == Allocated ? 2 : Allocated * 0.4);
            int OldAllocation = Allocated;
            this->Allocated = Allocated + By;
            Containing = (T **) realloc(Containing, sizeof(T *) * (Allocated));
            if (By > 0)
                memset(Containing + OldAllocation, 0, sizeof(T *) * (By));
        }
        void ExpandTo(int To)
        {
            if (To <= 0)
                return;
            if (To < 10)
                To = 10;
            int OldAllocation = Allocated;
            this->Allocated = To;
            Containing = (T **) realloc(Containing, sizeof(T *) * (Allocated));
            if (To > OldAllocation)
                memset(Containing + OldAllocation, 0, sizeof(T *) * (To - OldAllocation));
        }
        int Shift(int index, int PlacesToShift)
        {
            if (index < 0 || index >= Inserted)
                return 0;
            if (PlacesToShift == 0 || Inserted==0)
                return 0;
            if(index+PlacesToShift<0)
                PlacesToShift = (-1)*index;
            if(PlacesToShift<0)
                for(int a=index+PlacesToShift;a<index;a++)
                    delete Containing[a];
            else if (Inserted + PlacesToShift > Allocated)
                ExpandTo(Inserted + PlacesToShift);
            memmove(Containing + index + PlacesToShift, Containing + index, sizeof(T *) * (Inserted - index));
            Math::Interval<int> Original(index, Allocated);
            Math::Interval<int> MovedTo(index + PlacesToShift, Inserted + PlacesToShift);
            Math::Interval<int> ToDelete = Original - MovedTo;
            memset(Containing + ToDelete.GetBegin(), 0,
                   sizeof(T *) * (ToDelete.GetEnd() - ToDelete.GetBegin()));
            this->Inserted += PlacesToShift;
            return PlacesToShift;
        }
    public:
        T& operator[](int i)
        {
            return GetElementAtIndex(i);
        }
        const T& operator[](int i) const
        {
            return GetElementAtIndex(i);
        }
        int Delete(int Count)
        {
            if (Count >= Inserted)
                return Delete();
            int deleted = (-1)*this->Shift(Count, -Count);
            return deleted;
        }
        int Delete()
        {
            for (int a = 0; a < Inserted; a++)
                delete Containing[a];
            int deleted = Inserted;
            ExpandTo(10);
            Inserted = 0;
            return deleted;
        }
        int DeleteFromEnd(int Count)
        {
            int deleted=0;
            for(int i=Inserted-1,a=0;a<Count && i>=0;a++,i--)
            {
                delete Containing[i];
                Containing[i]=NULL;
                deleted++;
                Inserted--;
            }
            return deleted;
        }
        T *ToArray(int &count) const
        {
            if (Inserted == 0)
                return NULL;
            count = Inserted;
            T *CreatedArray = (T *) malloc(sizeof(T) * this->Inserted);
            for (int a = 0; a < Inserted; a++)
                new(CreatedArray + a) T(*Containing[a]);
            return CreatedArray;
        }
        T **ToWriteArray(int &count)
        {
            if (Inserted == 0)
                return NULL;
            count = Inserted;
            T **CreatedArray = (T **) malloc(sizeof(T *) * this->Inserted);
            CreatedArray = (T **) memcpy(CreatedArray, this->Containing, sizeof(T *) * this->Inserted);
            return CreatedArray;
        }
        int Push(const T &Value)
        {
            if (Allocated == Inserted)
            {
                int NewAlloc = int(Allocated * 1.4);
                Expand(NewAlloc - Allocated);
            }
            Containing[Inserted] = new T(Value);
            Inserted++;
            return 1;
        }
        int Push(const T *const Values, int Count)
        {
            if (Allocated < Inserted + Count)
            {
                int NewAlloc = Inserted + Count;
                Expand(NewAlloc - Allocated);
            }
            for (int a = 0; a < Count; a++)
                Containing[Inserted + a] = new T(Values[a]);
            Inserted += Count;
            return Count;
        }
        int ShrinkToFit()
        {
            int NewSize = Inserted > 10 ? Inserted : 10;
            this->Containing = (T **) realloc(this->Containing, sizeof(T *) * NewSize);
            this->Allocated = NewSize;
            if (Allocated > Inserted)
                memset(this->Containing + Inserted, 0, sizeof(T *) * (NewSize - Inserted));
            return Inserted;
        }
        bool Swap(int FirstIndex, int SecondIndex)
        {
            if(FirstIndex<0 || FirstIndex>=Inserted || SecondIndex<0 || SecondIndex>=Inserted || FirstIndex==SecondIndex)
                return false;
            T* temp = Containing[FirstIndex];
            Containing[FirstIndex] = Containing[SecondIndex];
            Containing[SecondIndex] = temp;
            return true;
        }
    };
}
namespace Templates
{
    template<typename T>
    class Queue
    {
    protected:
        class Node
        {
        public:
            T Value;
            Node* Next;
            Node()
            { Next = NULL; }
        };
        Node* First;
        Node* Last;
    public:
        class Iterator :
                virtual public Iterators::ForwardIteratorBase<T>,
                virtual public Iterators::DeletingForwardIteratorBase<T>
        {
            friend class Queue;
        private:
            Queue* WorkingQueue;
        public:
            Iterator()
            {
                WorkingQueue = NULL;
            }
            Iterator(Queue* Que) : Iterator()
            {
                this->WorkingQueue = Que;
            }
            Iterator(const Iterator& Copy)
                    : Iterator(Copy.WorkingQueue)
            { }
            virtual bool IsValidIterator() const
            {
                return WorkingQueue != NULL;
            }
            virtual T* GetValue()
            {
                return &this->WorkingQueue->First->Value;
            }
            virtual void SetValue(const T& Val)
            {
                this->WorkingQueue->First->Value = Val;
            }
            virtual bool Next()
            {
                return Next(1);
            }
            virtual bool Next(int HowMany)
            {
                bool CanMove = true;
                T* Values = (T*) malloc(sizeof(T) * HowMany + 1);
                T* Base = Values;
                int a = 0;
                for (; a < HowMany && CanMove; a++)
                    if (!this->WorkingQueue->Pop(*(Values + a)))
                        CanMove = false;
                if (!CanMove)
                {
                    for (int i = 0; i < a - 1; i++)
                    {
                        this->WorkingQueue->Push(*Values);
                        Values++;
                    }
                }
                free(Base);
                return CanMove;
            }
            virtual int DeleteAfter(int Count = 1)
            {
                return this->WorkingQueue->Clear(Count);
            }
            virtual int Insert(const T& Value)
            {
                return this->WorkingQueue->Push(Value);
            }
            virtual int Insert(const T* const Array, int Count)
            {
                return this->WorkingQueue->Push(Array, Count);
            }
            Iterator Clone()
            {
                return Iterator(this->WorkingQueue);
            }
        };
        Queue()
        {
            First = NULL;
            Last = NULL;
        }
        Queue(const T* Array, int Count) : Queue()
        {
            if (Count <= 0)
                return;
            for (int a = 0; a < Count; a++)
                if (!Push(*(Array + a)))
                    return;
        }
        Queue(const Queue& Copy)
        {
            int val;
            T* Array = Copy.ToArray(val);
            Queue(Array,val);
            free(Array);
        }
        Queue& operator=(const Queue& Second)
        {
            if (this != &Second)
            {
                int val;
                T* Array = Second.ToArray(val);
                this->Push(Array,val);
                free(Array);
            }
            return *this;
        }
        virtual ~Queue()
        {
            while (First != NULL)
            {
                Node* Temp = First;
                First = Temp->Next;
                delete Temp;
            }
        }
        virtual Iterator Begin()
        {
            return Iterator(this);
        }
        int Size()
        {
            Node* Temp = First;
            int count = 0;
            while (Temp != NULL)
            {
                Temp = Temp->Next;
                count++;
            }
            return count;
        }
        T* ToArray(int& Count)
        {
            int CountOfStoredElements = Size();
            if (CountOfStoredElements == 0)
                return NULL;
            T* array = (T*) malloc(sizeof(T) * CountOfStoredElements);
            if (array == NULL)
                return NULL;
            T* Base = array;
            Node* Working = First;
            while (Working != NULL)
            {
                *array = Working->Value;
                array++;
                Working = Working->Next;
            }
            return Base;
        }
        virtual bool Push(const T& Value)
        {
            if (First == NULL && Last == NULL)
            {
                Node* Temp = new Node;
                Temp->Value = Value;
                First = Last = Temp;
            }
            else if (First != NULL && Last != NULL)
            {
                Node* Temp = new Node;
                Temp->Value = Value;
                Last->Next = Temp;
                Last = Temp;
            }
            return true;
        }
        virtual int Push(const T* Array, int Count)
        {
            for (int i = 0; i < Count; i++)
                if (!Push(*(Array + i)))
                    return i;
            return Count;
        }
        virtual bool Pop(T& Value)
        {
            if (First == NULL && Last == NULL)
                return false;
            else if (First != NULL && Last != NULL)
            {
                Node* Temp = First;
                First = Temp->Next;
                Value = Temp->Value;
                if (First == NULL && Temp == Last)
                    Last = NULL;
                delete Temp;
            }
            return true;
        }
        int Clear()
        {
            return Clear(0x7FFFFFFF);
        }
        int Clear(int HowMany)
        {
            int deleted = 0;
            for (int a = 0; a < HowMany && First != NULL; a++)
            {
                Node* Temp = First;
                First = Temp->Next;
                delete Temp;
                deleted++;
            }
            if (First == NULL)
                Last = NULL;
            return deleted;
        }
        bool IsEmpty()
        {
            if (First == NULL && Last == NULL)
                return true;
            else if (First != NULL && Last != NULL)
                return false;
            throw new QueueException("Queue.h", 361);
        }
    };
}
namespace Templates
{
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
            Iterator(Node* WorkingNode, Vector* Vec)
            {
                this->WorkingNode = WorkingNode;
                this->Vect = Vec;
            }
        public:
            Iterator()
            {
                WorkingNode = NULL;
            }
            Iterator(const Iterator& Copy)
            {
                this->WorkingNode = Copy.WorkingNode;
                this->Vect = Copy.Vect;
            }
            Iterator& operator=(const Iterator& Second)
            {
                if (this != &Second)
                {
                    this->WorkingNode = Second.WorkingNode;
                    this->Vect = Second.Vect;
                }
                return *this;
            }
            Iterator Clone()
            {
                return Iterator(WorkingNode);
            }
            virtual T* GetValue()
            {
                if (!IsValidIterator())
                    return NULL;
                return &(WorkingNode->Value);
            }
            virtual void SetValue(const T& Val)
            {
                if (!IsValidIterator())
                    throw new OutOfRangeException();
                WorkingNode->Value = Val;
            }
            virtual bool IsValidIterator() const
            {
                return Vect != NULL && WorkingNode != NULL && WorkingNode->Next != NULL;
            }
            virtual bool Next()
            {
                return Next(1);
            }
            virtual bool Next(int HowMany)
            {
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
            bool AreEqual(const Iterator& Second)
            {
                return WorkingNode == Second.WorkingNode;
            }
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
            virtual int Insert(const T& Value)
            {
                return Insert(&Value, 1);
            }
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
            virtual int DeleteAfter(int Count)
            {
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
        bool IsMyIterator(const Iterator& Iter)
        {
            Node* Temp = First;
            while (Temp != NULL)
            {
                if (Temp == Iter.WorkingNode)
                    return true;
                Temp = Temp->Next;
            }
            return false;
        }
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
        Vector() : Vector(0)
        { }
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
        Vector(const T* const Array, int Count) : Vector(Count)
        {
            Node* WorkingWith = First;
            for (int a = 0; a < Count; a++)
            {
                WorkingWith->Value = *(Array + a);
                WorkingWith = WorkingWith->Next;
            }
        }
        Vector(const Vector& Copy)
        {
            int val;
            T* Array = Copy.ToArray(val);
            Vector(Array, val);
            free(Array);
        }
        Vector& operator=(const Vector& Second)
        {
            if (this != &Second)
            {
                this->Clear();
                int val;
                T* Array = Second.ToArray(val);
                Vector(Array, val);
                free(Array);
            }
            return *this;
        }
        ~Vector()
        {
            this->Clear();
            delete First;
        }
        T* ToArray(int& Count)
        {
            Count = Size();
            if (Count == 0)
                return NULL;
            T* Array = (T*) malloc(sizeof(T) * Count);
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
        Iterator Begin()
        {
            return Iterator(First, this);
        }
        Iterator End()
        {
            Node* Temp = First;
            while (Temp->Next != NULL)
                Temp = Temp->Next;
            return Iterator(Temp, this);
        }
        bool At(int Position, Iterator& BackIterator)
        {
            if (Position > Size())
                return false;
            BackIterator = Begin();
            return BackIterator.Next(Position - 1);
        }
        int Size()
        {
            Node* Working = First;
            int Count = 0;
            while (Working->Next != NULL)
            {
                Count++;
                Working = Working->Next;
            }
            return Count;
        }
        inline bool IsEmpty()
        {
            return Size() == 0;
        }
        inline int Clear()
        {
            return Clear(0, Size());
        }
        int Clear(Iterator& From, Iterator& To)
        {
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
        int Clear(int IndexFrom, int HowMany)
        {
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
            for(int a=0;a<Count;a++,Array++)
                inserted += this->Insert(*Array);
            return 0;
        }
    };
}
namespace Templates
{
    template<typename T>
    class CondQueue : public Queue<T>
    {
    private:
        bool(* ValidCallback)(const T* What) = NULL;
    public:
        CondQueue(bool(* Validation)(const T* What))
                : Queue<T>::Queue()
        {
            this->ValidCallback = Validation;
        }
        CondQueue(bool(* Validation)(const T* What), T* Array, int Count)
                : CondQueue(Validation)
        {
            Push(Array, Count);
        }
        CondQueue(const CondQueue& Copy)
                : CondQueue(Copy.ValidCallback)
        {
            typename Queue<T>::Node* Temp = this->First;
            while (Temp->Next != NULL)
            {
                Push(Temp->Value);
                Temp = Temp->Next;
            }
        }
        virtual bool Push(const T& Value)
        {
            if (ValidCallback(&Value))
                return Queue<T>::Push(Value);
            return false;
        }
        CondQueue& operator=(const CondQueue& Second)
        {
            if (this != &Second)
            {
                this->ValidCallback = Second.ValidCallback;
                this->Clear();
                typename Queue<T>::Iterator Iter = Second.Begin();
                while (Iter.IsValidIterator())
                {
                    this->Push(*Iter.GetValue());
                    Iter.Next();
                }
            }
            return *this;
        }
        inline void SetCallback(bool(* Validation)(const T* What))
        {
            ValidCallback = Validation;
        }
        int ValidateQueue()
        {
            int deleted = 0;
            while (this->First != NULL && !ValidCallback(&this->First->Value))
            {
                typename Queue<T>::Node* Temp = this->First;
                this->First = Temp->Next;
                delete Temp;
                deleted++;
            }
            if (this->First == NULL)
            {
                this->Last = NULL;
                return deleted;
            }
            typename Queue<T>::Node* Previous = this->First;
            while (Previous->Next != NULL)
            {
                typename Queue<T>::Node* Temp = Previous->Next;
                if (ValidCallback(&Temp->Value))
                    Previous = Temp;
                else
                {
                    Previous->Next = Temp->Next;
                    delete Temp;
                    deleted++;
                }
            }
            if (this->First == NULL)
                this->Last = NULL;
            return deleted;
        }
        virtual int Push(const T* Array, int Count)
        {
            int pushed = 0;
            for (int i = 0; i < Count; i++)
                if (this->Push(*(Array + i)))
                    pushed++;
            return pushed;
        }
        virtual bool Pop(T& Value)
        {
            while (true)
            {
                T temp;
                if (!Queue<T>::Pop(temp))
                    return false;
                if (ValidCallback(&temp))
                {
                    Value = temp;
                    return true;
                }
            }
        }
        virtual T* ToArray(int& Count)
        {
            this->ValidateQueue();
            return Queue<T>::ToArray(Count);
        }
        virtual typename Queue<T>::Iterator Begin()
        {
            return typename Queue<T>::Iterator(this);
        }
    };
}
namespace Templates
{
    template<typename T>
    class PriorityQueue;
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
            Iterator()
            {
                WorkingNode = NULL;
                ListInstance = NULL;
            }
            Iterator(Node* Node, List* ListInstance)
            {
                WorkingNode = Node;
                this->ListInstance = ListInstance;
            }
            Iterator(const Iterator& Copy)
            {
                this->WorkingNode = Copy.WorkingNode;
                this->ListInstance = Copy.ListInstance;
            }
            Iterator& operator=(const Iterator& Second)
            {
                if (this != &Second)
                {
                    this->WorkingNode = Second.WorkingNode;
                    this->ListInstance = Second.ListInstance;
                }
                return *this;
            }
            Iterator Clone()
            {
                return Iterator(this->WorkingNode, this->ListInstance);
            }
            virtual bool IsValidIterator() const
            {
                return WorkingNode != NULL && WorkingNode->Forward != NULL;
            }
            virtual T* GetValue()
            {
                if (!IsValidIterator())
                    return NULL;
                return &(WorkingNode->Value);
            }
            virtual void SetValue(const T& Val)
            {
                WorkingNode->Value = Val;
            }
            virtual bool Next()
            {
                return Next(1);
            }
            virtual bool Next(int HowMany)
            {
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
            virtual bool Back()
            {
                return Back(1);
            }
            virtual bool Back(int HowMany)
            {
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
            virtual int Insert(const T* const Values, int Count)
            {
                if (WorkingNode->Forward == NULL)
                    return -1;
                for (int a = Count - 1; a >= 0; a--)
                    if (Insert(*(Values + a)) != 1)
                        return Count - 1 - a;
                return Count;
            }
            virtual int Insert(const T& Value)
            {
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
                return 1;
            }
            int InsertBefore(T Value)
            {
                Node* NewNode = new Node;
                NewNode->Value = Value;
                if (WorkingNode == this->ListInstance->First)
                {
                    this->ListInstance->First = NewNode;
                    NewNode->Forward = WorkingNode;
                    NewNode->Backward = NULL;
                    WorkingNode->Backward = NewNode;
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
                    return 1;
                }
            }
            int InsertBefore(T* Array, int Count)
            {
                for (int a = 0; a < Count; a++)
                    if (!InsertBefore(*(Array + a)))
                        return a;
                return Count;
            }
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
            virtual int DeleteAfter(int Count)
            {
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
                    return 1;
                }
            }
            bool AreEqual(const Iterator& Second)
            {
                return WorkingNode == Second.WorkingNode;
            }
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
        bool IsMyIterator(const Iterator& Iter)
        {
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
        List()
        {
            Node* Temp = new Node;
            First = Temp;
            Last = Temp;
        }
        List(int Capacity) : List()
        {
            List();
            if (Capacity < 1)
                return;
            for (int a = 0; a < Capacity; a++)
            {
                Node* Temp = new Node;
                First->Backward = Temp;
                Temp->Forward = First;
                First = Temp;
            }
        }
        List(T* Array, int Count) : List(Count)
        {
            if (Count < 1 || Array == NULL)
                throw new ::Templates::InvalidArgumentException("Cannot pass null array with count < 1", 511);
            Node* Temp = First;
            while (Temp->Forward != NULL)
            {
                Temp->Value = *Array;
                Array++;
                Temp = Temp->Forward;
            }
            return;
        }
        List(const List& Copy) : List(Copy.Size())
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
        List& operator=(const List& Second)
        {
            this->Delete();
            if(Second.Size()==0)
                return;
            Node* Start = Second.First;
            Node* End = Second.Last;
            Node* Temp = Start;
            do
            {
                this->End().InsertBefore(Temp->Value);
                Temp = Temp->Forward;
            }while(Temp!=End);
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
        int Size()
        {
            Node* Temp = First;
            int Count = 0;
            while (Temp->Forward != NULL)
            {
                Temp = Temp->Forward;
                Count++;
            }
            return Count;
        }
        Iterator Begin()
        {
            return Iterator(First, this);
        }
        Iterator End()
        {
            return Iterator(Last, this);
        }
        Iterator At(int Index)
        {
            Node* Temp = First;
            int a;
            for (a = 0; a < Index && First->Forward != NULL; a++)
                Temp = Temp->Forward;
            return Iterator(Temp, this);
        }
        int Delete()
        {
            return this->Delete(0xFFFFFFFF >> 1);
        }
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
            Node* Temp = First->Forward;
            delete First;
            First = Temp;
            deleted++;
            return deleted;
        }
        int Delete(Iterator& Iter, int HowMany = 1)
        {
            if (HowMany < 1 || Iter.WorkingNode == Last)
                throw new OutOfRangeException();
            if (!IsMyIterator(Iter))
                throw new InvalidArgumentException("Iterator is not chain with this instance", 677);
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
            return deleted;
        }
        bool IsEmpty()
        {
            return Size() == 0;
        }
        T* ToArray(int& Count)
        {
            Count = Size();
            if(Count==0)
                return NULL;
            T* Array = (T*)malloc((sizeof(T)*Count));
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
        T** ToWriteArray(int& Count)
        {
            Count = Size();
            if(Count==0)
                return NULL;
            T** Array = (T**)malloc((sizeof(T*)*Count));
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
namespace Templates
{
    template<typename T>
    class BinaryMinHeap
    {
    private:
        Array <T> *Container;
        int (*Sorting)(const T *const First, const T *const Second);
        void RepairHeap(int index)
        {
            int Child = index;
            int Parent = (Child - 1) / 2;
            T ChildElement = (*Container)[Child];
            T ParentElement = (*Container)[Parent];
            while (Parent >= 0 && Sorting(&ChildElement, &ParentElement) < 0)
            {
                Container->Swap(Child, Parent);
                Child = Parent;
                Parent = (Child - 1) / 2;
                ChildElement = (*Container)[Child];
                ParentElement = (*Container)[Parent];
            }
        }
        void DowngradeRepairHeap(int index)
        {
            int ParentIndex = index;
            int LastIndex = Container->Size() - 1;
            int RightChildIndex;
            int LeftChildIndex;
            int result;
            int IndexToSwap;
            T Child;
            T Parent;
            while (true)
            {
                if (ParentIndex > LastIndex)
                    return;
                LeftChildIndex = ParentIndex == 0 ? 1 : ParentIndex * 2 + 1;
                RightChildIndex = LeftChildIndex + 1;
                if (LeftChildIndex > LastIndex && RightChildIndex > LastIndex)
                    return;
                else if (LeftChildIndex <= LastIndex && RightChildIndex <= LastIndex)
                {
                    result = this->Sorting(&((*Container)[LeftChildIndex]), &((*Container)[RightChildIndex]));
                    IndexToSwap = result < 0 ? LeftChildIndex : RightChildIndex;
                }
                else
                    IndexToSwap = LeftChildIndex <= LastIndex ? LeftChildIndex : RightChildIndex;
                Parent = (*Container)[ParentIndex];
                Child = (*Container)[IndexToSwap];
                result = this->Sorting(&Parent, &Child);
                if (result < 0)
                    return;
                Container->Swap(ParentIndex, IndexToSwap);
                ParentIndex = IndexToSwap;
            }
        }
    public:
        BinaryMinHeap(int(*SortCallback)(const T *const First, const T *const Second))
        {
            this->Sorting = SortCallback;
            Container = new Array<T>();
        }
        BinaryMinHeap(const BinaryMinHeap &Second)
        {
            this->Container = new Array<T>(*Second.Container);
        }
        BinaryMinHeap &operator=(const BinaryMinHeap &Second)
        {
            *this->Container = *Second.Container;
        }
        ~BinaryMinHeap()
        {
            delete Container;
        }
        int Insert(T &Value)
        {
            if (this->Container->Push(Value) == 0)
                return 0;
            RepairHeap(Container->Size() - 1);
            return 1;
        }
        int Insert(T *Values, int Count)
        {
            int inserted = Container->Push(Values, Count);
            for (int a = inserted; a >= 0; a++)
                RepairHeap(Container->Size() - inserted);
            return inserted;
        }
        int Clear()
        {
            return Container->Delete();
        }
        bool Pop(T &Val)
        {
            typename Array<T>::Iterator iter;
            if (!Container->TryAt(0, iter))
                return false;
            Val = *iter.GetValue();
            this->Container->Swap(Container->Size() - 1, 0);
            this->Container->DeleteFromEnd(1);
            this->DowngradeRepairHeap(0);
            return true;
        }
    };
}
namespace Templates
{
    template<typename T>
    class PriorityQueue
    {
    private:
        BinaryMinHeap<T>* Instance;
    public:
        PriorityQueue(int(* SwitchCallback)(const T* const First, const T* const Second))
        {
            this->Instance = new BinaryMinHeap<T>(SwitchCallback);
        }
        PriorityQueue(const PriorityQueue& Second)
        {
            this->Instance = new BinaryMinHeap<T>(*Second.Instance);
        }
        ~PriorityQueue()
        {
            delete Instance;
        }
        PriorityQueue& operator=(const PriorityQueue& Second)
        {
            this->Instance = Second.Instance;
        }
        bool Push(T Value)
        {
            return this->Instance->Insert(Value);
        }
        bool Pop(T& Value)
        {
            return this->Instance->Pop(Value);
        }
    };
}
namespace Templates
{
    template<typename T>
    class Stack
    {
    private:
        class Node
        {
        public:
            T Value;
            Node* Next;
            Node()
            { Next = NULL; }
        };
        Node* TopNode;
    public:
        class Iterator :
                virtual public Iterators::ForwardIteratorBase<T>,
                virtual public Iterators::DeletingForwardIteratorBase<T>
        {
        private:
            Stack* WorkingStack;
        public:
            Iterator()
            { WorkingStack = NULL; }
            Iterator(Stack* Que) : Iterator()
            { this->WorkingStack = Que; }
            Iterator(const Iterator& Copy)
                    : Iterator(Copy.WorkingStack)
            { }
            Iterator Clone()
            { return Iterator(this->WorkingStack); }
            virtual bool IsValidIterator() const
            { return WorkingStack != NULL && WorkingStack->TopNode!=NULL; }
            virtual T* GetValue()
            { return &this->WorkingStack->TopNode->Value; }
            virtual void SetValue(const T& Val)
            { this->WorkingStack->TopNode->Value = Val; }
            virtual bool Next()
            {
                T val;
                return this->WorkingStack->Pop(val) && this->WorkingStack->TopNode!=NULL;
            }
            virtual bool Next(int HowMany)
            {
                T* Array = (T*) malloc(sizeof(T) * HowMany);
                int i;
                for (i = 0; i < HowMany; i++)
                    if (!this->WorkingStack->Pop(*(Array + i)))
                        break;
                if (i == HowMany)
                {
                    free(Array);
                    return true;
                }
                for (int j = i - 1; j >= 0; j--)
                    this->WorkingStack->Push(*(Array + j));
                free(Array);
                return false;
            }
            virtual int DeleteAfter(int Count = 1)
            { return this->Next(Count) ? Count : 0; }
            virtual int Insert(const T& Value)
            { return this->WorkingStack->Push(Value); }
            virtual int Insert(const T* const Array, int Count)
            { return this->WorkingStack->Push(Array, Count); }
        };
        Stack() : TopNode(NULL)
        { }
        Stack(const T* Array, int Count) : Stack()
        { this->Push(Array, Count); }
        Stack& operator=(const Stack& Second)
        {
            if(this!=&Second)
            {
                this->Clear();
                if(Second.IsEmpty())
                {
                    this->TopNode = NULL;
                    return *this;
                }
                Node* Created = new Node;
                Created->Value = Second.TopNode->Value;
                this->TopNode = Created;
                Node* Temp = Second.TopNode->Next;
                for(;Temp!=NULL;Temp=Temp->Next)
                {
                    Node* ToAdd = new Node;
                    ToAdd->Value = Temp->Value;
                    Created->Next = ToAdd;
                    Created = ToAdd;
                }
            }
            return *this;
        }
        Stack(const Stack& Second) : Stack()
        {
            if(Second.IsEmpty())
            {
                this->TopNode = NULL;
                return;
            }
            Node* Created = new Node;
            Created->Value = Second.TopNode->Value;
            this->TopNode = Created;
            Node* Temp = Second.TopNode->Next;
            for(;Temp!=NULL;Temp=Temp->Next)
            {
                Node* ToAdd = new Node;
                ToAdd->Value = Temp->Value;
                Created->Next = ToAdd;
                Created = ToAdd;
            }
        }
        ~Stack()
        {
            this->Clear();
        }
        Iterator Begin()
        { return Iterator(this); }
        int Size()
        {
            int Count = 0;
            Node* Temp = this->TopNode;
            while (Temp != NULL)
            {
                Count++;
                Temp = Temp->Next;
            }
            return Count;
        }
        T* ToArray(int& count)
        {
            count = this->Size();
            if(count==0)
                return NULL;
            T* Array = (T*) malloc(sizeof(T) * count);
            Node* Temp = this->TopNode;
            for(int i=0;i<count;i++,Temp=Temp->Next)
                *(Array+i) = Temp->Value;
            return Array;
        }
        int Push(const T& Val)
        {
            Node* Temp = new Node;
            Temp->Value = Val;
            if (this->TopNode != NULL)
                Temp->Next = this->TopNode;
            this->TopNode = Temp;
            return 1;
        }
        int Push(const T* Array, int Count)
        {
            int Added = 0;
            for (int a = 0; a < Count; a++, Array++)
                Added += this->Push(*Array);
            return Added;
        }
        bool Pop(T& Value)
        {
            if (this->TopNode == NULL)
                return false;
            Node* Temp = this->TopNode;
            this->TopNode = Temp->Next;
            Value = Temp->Value;
            delete Temp;
            return true;
        }
        int Clear()
        {
            int deleted = 0;
            Node* Temp = this->TopNode;
            while (Temp != NULL)
            {
                Node* ToDelete = Temp;
                Temp = Temp->Next;
                delete ToDelete;
                deleted++;
            }
            this->TopNode = NULL;
            return deleted;
        }
        bool IsEmpty() const
        { return this->TopNode == NULL; }
    };
}
namespace Templates
{
    template<typename T, bool ALLOW_DUPLICITIES = true>
    class BinarySearchTree
    {
    private:
        class Node
        {
        public:
            T Val;
            Node *Child[2] = {NULL, NULL};
        };
        Node *Root = NULL;
        struct TempCopyStructure
        {
            Node *CopyFrom;
            Node **CopyTo;
        };
        int(*Distribution)(const T *const First, const T *const Second);
        int CountOfElements;
    public:
        BinarySearchTree(int(*Distribution)(const T *const First, const T *const Second))
        {
            this->CountOfElements = 0;
            this->Distribution = Distribution;
            this->Root = NULL;
        }
        BinarySearchTree(BinarySearchTree &Second)
                : BinarySearchTree(Second.Distribution)
        {
            CountOfElements = Second.CountOfElements;
            Queue<TempCopyStructure> CopyQueue;
            TempCopyStructure ToCopy{Second.Root, &this->Root};
            CopyQueue.Push(ToCopy);
            while (!CopyQueue.IsEmpty())
            {
                CopyQueue.Pop(ToCopy);
                *ToCopy.CopyTo = new Node;
                (*ToCopy.CopyTo)->Val = ToCopy.CopyFrom->Val;
                for (int a = 0; a < 2; a++)
                    if (ToCopy.CopyFrom->Child[a] != NULL)
                        CopyQueue.Push(TempCopyStructure{ToCopy.CopyFrom->Child[a],
                                                         (&(*ToCopy.CopyTo)->Child[a])});
            }
        }
        ~BinarySearchTree()
        {
            this->Clear();
        }
        BinarySearchTree &operator=(const BinarySearchTree &Second)
        {
            throw new NotImplementedException("BinarySearchTree.h", 82);
        }
        int Size()
        {
            return this->CountOfElements;
        }
        int Insert(T &Value)
        {
            Node *Created = new Node;
            Created->Val = Value;
            if (Root == NULL)
            {
                this->Root = Created;
                CountOfElements++;
                return 1;
            }
            Node *Previous = NULL;
            Node *Temp = this->Root;
            while (Temp != NULL)
            {
                int Result = this->Distribution(&Temp->Val, &Value);
                Previous = Temp;
                if (!ALLOW_DUPLICITIES && Result == 0)
                {
                    delete Created;
                    return 0;
                }
                Temp = Temp->Child[Result >= 0];
            }
            Previous->Child[this->Distribution(&Previous->Val, &Value) >= 0] = Created;
            CountOfElements++;
            return 1;
        }
        int Insert(T *Values, int Count)
        {
            int inserted = 0;
            for (int a = 0; a < Count; a++)
                inserted += this->Insert(*(Values++));
            return inserted;
        }
        int Clear()
        {
            if (this->Root == NULL)
                return 0;
            int Deleted = 0;
            Stack<Node *> *ToDeleteStack = new Stack<Node *>();
            ToDeleteStack->Push(this->Root);
            Node *ToDelete;
            while (!ToDeleteStack->IsEmpty())
            {
                if (!ToDeleteStack->Pop(ToDelete))
                {
                    delete ToDeleteStack;
                    return -1;
                }
                if (ToDelete->Child[1])
                    ToDeleteStack->Push(ToDelete->Child[1]);
                if (ToDelete->Child[0])
                    ToDeleteStack->Push(ToDelete->Child[0]);
                delete ToDelete;
                Deleted++;
            }
            this->Root = NULL;
            delete ToDeleteStack;
            CountOfElements -= Deleted;
            return Deleted;
        }
        bool Contain(const T &Value) const
        {
            if (this->Root == NULL)
                return false;
            Node *Temp = this->Root;
            while (Temp != NULL)
            {
                int Resolve = this->Distribution(&Temp->Val, &Value);
                if (Resolve == 0)
                    return true;
                Temp = Temp->Child[Resolve > 0];
            }
            return false;
        }
        bool Get(T* &Returned, const T &ToFind) const
        {
            if (this->Root == NULL)
                return false;
            Node *Temp = this->Root;
            while (Temp != NULL)
            {
                int Resolve = this->Distribution(&Temp->Val, &ToFind);
                if (Resolve == 0)
                {
                    Returned = &(Temp->Val);
                    return true;
                }
                Temp = Temp->Child[Resolve > 0];
            }
            return false;
        }
        Vector <T*> Get(bool(*Callback)(const T *const Value, void *data), void *data = NULL, int Count = 1)
        {
        }
        int GetOrCreate(T &ToFind, T* &Return)
        {
            if (ALLOW_DUPLICITIES)
                return 0;
            if (this->Root == NULL)
            {
                this->Insert(ToFind);
                Return = &(this->Root->Val);
                CountOfElements++;
                return 1;
            };
            Node *Parent = this->Root;
            Node *Temp = this->Root;
            while (Temp != NULL)
            {
                int Resolve = this->Distribution(&Temp->Val, &ToFind);
                if (Resolve == 0)
                {
                    Return = &(Temp->Val);
                    return 0;
                }
                Parent = Temp;
                Temp = Temp->Child[Resolve > 0];
            }
            Node *Created = new Node;
            Created->Val = ToFind;
            int resolve = this->Distribution(&Parent->Val, &ToFind);
            Parent->Child[resolve > 0] = Created;
            Return = &(Created->Val);
            CountOfElements++;
            return 1;
        }
        int GetAndDelete(T &ToFind, T &Return)
        {
            if (this->Root == NULL)
                return 0;
            Node *Parent = NULL;
            Node *Temp = this->Root;
            while (Temp != NULL)
            {
                int Resolve = this->Distribution(&Temp->Val, &ToFind);
                if (Resolve == 0)
                {
                    Return = Temp->Val;
                    this->RemoveNode(ToDeleteHelpClass{Parent, Temp});
                    this->CountOfElements--;
                    return 1;
                }
                Parent = Temp;
                Temp = Temp->Child[Resolve > 0];
            }
            return 0;
        }
    private:
        void ToArrayRecursive(Vector <T> &Array, Node *Temp) const
        {
            if (Temp == NULL)
                return;
            ToArrayRecursive(Array,
                             Temp->Child[1]);
            Array.Insert(Temp->Val);
            ToArrayRecursive(Array, Temp->Child[0]);
            return;
        }
        class ToDeleteHelpClass
        {
        public:
            ToDeleteHelpClass()
            { }
            ToDeleteHelpClass(Node *Parent, Node *ToDelete)
                    : Parent(Parent), ToDelete(ToDelete)
            { }
            Node *Parent = NULL;
            Node *ToDelete = NULL;
        };
        Node *RemoveNode(ToDeleteHelpClass Deleting)
        {
            Node **ParentPointer = NULL;
            if (Deleting.ToDelete == this->Root)
                ParentPointer = &this->Root;
            else
                ParentPointer = &Deleting.Parent->Child[(Deleting.Parent->Child[1] == Deleting.ToDelete)];
            if (Deleting.ToDelete->Child[0] == NULL && Deleting.ToDelete->Child[1] == NULL)
            {
                delete Deleting.ToDelete;
                *ParentPointer = NULL;
                return NULL;
            }
            if (Deleting.ToDelete->Child[0] == NULL || Deleting.ToDelete->Child[1] == NULL)
            {
                *ParentPointer = Deleting.ToDelete->Child[Deleting.ToDelete->Child[0] == NULL];
                delete Deleting.ToDelete;
                return *ParentPointer;
            }
            if (Deleting.ToDelete->Child[0]->Child[1] == NULL)
            {
                Deleting.ToDelete->Child[0]->Child[1] = Deleting.ToDelete->Child[1];
                *ParentPointer = Deleting.ToDelete->Child[0];
                delete Deleting.ToDelete;
                return *ParentPointer;
            }
            if (Deleting.ToDelete->Child[1]->Child[0] == NULL)
            {
                Deleting.ToDelete->Child[1]->Child[0] = Deleting.ToDelete->Child[0];
                *ParentPointer = Deleting.ToDelete->Child[1];
                delete Deleting.ToDelete;
                return *ParentPointer;
            }
            Node *Parent = Deleting.ToDelete->Child[0];
            Node *Replaced = Parent->Child[1];
            while (Replaced->Child[1] != NULL)
            {
                Parent = Replaced;
                Replaced = Parent->Child[1];
            }
            Parent->Child[1] = Replaced->Child[0];
            for (int a = 0; a < 2; a++)
                Replaced->Child[a] = Deleting.ToDelete->Child[a];
            *ParentPointer = Replaced;
            delete Deleting.ToDelete;
            return *ParentPointer;
        }
    public:
        T *ToArray(int &Count) const
        {
            Vector<T> ArrayTemp;
            ToArrayRecursive(ArrayTemp, this->Root);
            return ArrayTemp.ToArray(Count);
        }
        int Delete(bool(*Callback)(const T *const Value, void *data), void *data = NULL)
        {
            if (this->Root == NULL)
                return 0;
            int deleted = 0;
            Queue<ToDeleteHelpClass> Nodes;
            Nodes.Push(ToDeleteHelpClass(NULL, this->Root));
            ToDeleteHelpClass Temp;
            while (Nodes.Pop(Temp))
            {
                if (Callback(&Temp.ToDelete->Val, data))
                {
                    Node *Replaced = this->RemoveNode(Temp);
                    if (Replaced != NULL)
                        Nodes.Push(ToDeleteHelpClass(Temp.Parent, Replaced));
                    deleted++;
                }
                else
                {
                    for (int a = 0; a < 2; a++)
                        if (Temp.ToDelete->Child[a] != NULL)
                            Nodes.Push(ToDeleteHelpClass(Temp.ToDelete, Temp.ToDelete->Child[a]));
                }
            }
            CountOfElements -= deleted;
            return deleted;
        }
        int Delete(T value)
        {
            if (this->Root == NULL)
                return 0;
            Node *Temp = this->Root;
            Node *Parent = NULL;
            while (Temp != NULL)
            {
                int Resolve = this->Distribution(&Temp->Val, &value);
                if (Resolve == 0)
                    break;
                Parent = Temp;
                Temp = Temp->Child[Resolve > 0];
            }
            if (Temp == NULL)
                return 0;
            this->RemoveNode(ToDeleteHelpClass(Parent, Temp));
            CountOfElements--;
            return 1;
        }
    };
}
namespace Templates
{
    using namespace Iterators;
    template<typename T>
    bool Find(ForwardIteratorBase<T>* Iter,bool(*Validation)(const T* const Value,void* data), void* params = NULL)
    {
        while(Iter->IsValidIterator())
        {
            T* Val = Iter->GetValue();
            if (Validation(Val,params))
                return true;
            Iter->Next();
        }
        return false;
    }
}
#endif
