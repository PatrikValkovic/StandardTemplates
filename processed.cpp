#include <string.h>
#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>












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
class ArrayTests;










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


        friend class ::ArrayTests;


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

            else
                throw new QueueException("Queue.h", 279);

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

            else
                throw new QueueException("Queue.h", 313);

            return true;
        }




        int Clear()
        {
            return Clear(0x7FFFFFFF);
        }




        int Clear(int HowMany)
        {

            if ((First == NULL && Last != NULL) || (First != NULL && Last == NULL))
                throw new QueueException("Queue.h", 333);

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

            else
                throw new QueueException("Queue.h", 359);

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

                if (WorkingNode == NULL)
                    throw new VectorException("Vector.h", 95);

                if (!IsValidIterator())
                    return NULL;
                return &(WorkingNode->Value);
            }





            virtual void SetValue(const T& Val)
            {

                if (WorkingNode == NULL)
                    throw new VectorException("Vector.h", 110);

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

                if (WorkingNode == NULL)
                    throw new VectorException("Vector.h", 134);

                return Next(1);
            }





            virtual bool Next(int HowMany)
            {

                if (WorkingNode == NULL)
                    throw new VectorException("Vector.h", 147);

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

                if (WorkingNode == NULL)
                    throw new VectorException("Vector.h", 168);

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

                if (WorkingNode == NULL)
                    throw new VectorException("Vector.h", 231);

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

            if (First == NULL)
                throw new VectorException("Vector.h", 258);

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

            if (First == NULL)
                throw new VectorException("Vector.h", 373);

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

            if (First == NULL)
                throw new VectorException("Vector.h", 399);

            return Iterator(First, this);
        }





        Iterator End()
        {

            if (First == NULL)
                throw new VectorException("Vector.h", 412);

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

            if (First == NULL)
                throw new VectorException("Vector.h", 439);

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

            if (From.WorkingNode == NULL || First == NULL || To.WorkingNode == NULL)
                throw new VectorException("Vector.h", 476);

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

            if (First == NULL)
                throw new VectorException("Vector.h", 506);

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

                if (!IsValidIterator())
                    throw new ListException("List.h", 202);

                WorkingNode->Value = Val;
            }





            virtual bool Next()
            {
                return Next(1);
            }





            virtual bool Next(int HowMany)
            {

                if (!IsValidIterator())
                    return false;

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

                if (WorkingNode == NULL)
                    throw new ListException("List.h", 253);

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

                if (WorkingNode == NULL)
                    throw new ListException("List.h", 274);

                if (WorkingNode->Forward == NULL)
                    return -1;

                for (int a = Count - 1; a >= 0; a--)
                    if (Insert(*(Values + a)) != 1)
                        return Count - 1 - a;
                return Count;
            }





            virtual int Insert(const T& Value)
            {

                if (WorkingNode == NULL)
                    throw new ListException("List.h", 293);

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

                if (WorkingNode == NULL)
                    throw new ListException("List.h", 320);

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

                if (ListInstance == NULL || WorkingNode == NULL)
                    throw new ListException("List.h", 381);

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

                if (WorkingNode == NULL || Second.WorkingNode == NULL)
                    throw new ListException("List.h", 418);

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

            if (Iter.WorkingNode == NULL)
                throw new ListException("List.h", 464);

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

            if (First == NULL || Last == NULL)
                throw new ListException("List.h", 514);

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

            if (First == NULL || Last == NULL)
                throw new ListException("List.h", 583);

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

            if (First == NULL)
                throw new ListException("List.h", 602);

            return Iterator(First, this);
        }





        Iterator End()
        {

            if (Last == NULL)
                throw new ListException("List.h", 615);

            return Iterator(Last, this);
        }





        Iterator At(int Index)
        {

            if (First == NULL)
                throw new ListException("List.h", 628);

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


            if (Iter.WorkingNode == NULL || Iter.ListInstance != this)
                throw new ListException("List.h", 681);

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

            if (First == NULL || Last == NULL)
                throw new ListException("List.h", 704);

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

                if (!CopyQueue.Pop(ToCopy))
                    throw new QueueException("BinarySearchTree.h", 59);



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

            if(Val==NULL)
                return false;

            if (Validation(Val,params))
                return true;
            Iter->Next();
        }
        return false;
    }
}








class VectorTest
{
public:
    VectorTest()
    { }

    void Creation()
    {
        using namespace Templates;
        Vector<int>* Instance;
        Vector<int>::Iterator FirstIter;
        Vector<int>::Iterator SecondIter;
        int list[] = {2, 6, 8, 4, 7};

        Instance = new Vector<int>();
        assert(Instance->Size() == 0);
        assert(Instance->IsEmpty());
        FirstIter = Instance->Begin();
        SecondIter = Instance->End();
        assert(FirstIter.AreEqual(SecondIter));
        assert(!FirstIter.Next());
        assert(!SecondIter.Next(5));
        delete Instance;

        Instance = new Vector<int>(5);
        assert(!Instance->IsEmpty());
        assert(Instance->Size() == 5);
        FirstIter = Instance->Begin();
        assert(FirstIter.Next());
        assert(!FirstIter.Next(5));
        assert(FirstIter.Next(4));
        SecondIter = Instance->End();
        assert(FirstIter.AreEqual(SecondIter));
        assert(!FirstIter.Next());
        delete Instance;

        Instance = new Vector<int>(list, 5);
        assert(Instance->Size() == 5);
        assert(!Instance->IsEmpty());
        FirstIter = Instance->Begin();
        assert(*FirstIter.GetValue() == 2);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 6);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 8);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 4);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 7);
        assert(FirstIter.Next());
  assert(FirstIter.GetValue() == NULL);
        assert(!FirstIter.Next());
  delete Instance;
    }

    void ClearingTests()
    {
        using namespace Templates;
        Vector<int>* Instance;


        int list[] = {2, 6, 8, 4, 7};

        Instance = new Vector<int>(list, 5);
        assert(Instance->Clear() == 5);
        assert(Instance->IsEmpty());
        assert(Instance->Size() == 0);
        delete Instance;

        Instance = new Vector<int>(list, 5);
        assert(Instance->Clear(2, 2) == 2);
        assert(Instance->Size() == 3);
        assert(!Instance->IsEmpty());
        Vector<int>::Iterator FirstIter = Instance->Begin();
        assert(!FirstIter.Next(8));
        assert(*FirstIter.GetValue() == 2);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 6);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 7);
        assert(FirstIter.Next());
  assert(FirstIter.GetValue() == NULL);
        assert(!FirstIter.Next());
        delete Instance;

        Instance = new Vector<int>(list, 5);
        FirstIter = Instance->Begin();
        assert(FirstIter.Next());
        Vector<int>::Iterator SecondIter = Instance->Begin();
        assert(SecondIter.Next(3));
        assert(Instance->Clear(FirstIter, SecondIter) == 1);
        FirstIter = Instance->Begin();
        assert(*FirstIter.GetValue() == 2);
        assert(FirstIter.Next());
  assert(*FirstIter.GetValue() == 6);
  assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 4);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 7);
        delete Instance;

        Instance = new Vector<int>(list, 5);
        FirstIter = Instance->Begin();
        SecondIter = Instance->End();
        assert(Instance->Clear(FirstIter, SecondIter) == 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Size() == 1);
  assert(*FirstIter.GetValue() == 2);
  assert(FirstIter.Next() && FirstIter.GetValue() == NULL);
  assert(Instance->Clear(0,1)==1);
  assert(Instance->IsEmpty() && Instance->Size() == 0);
        delete Instance;

        Instance = new Vector<int>(list, 5);
        assert(Instance->Clear(0, 8) == 5);
        FirstIter = Instance->Begin();
        SecondIter = Instance->End();
        assert((FirstIter.AreEqual(SecondIter)));
        assert(Instance->IsEmpty());
        assert(Instance->Size() == 0);
  assert(FirstIter.GetValue() == NULL);
  assert(SecondIter.GetValue() == NULL);
        delete Instance;
    }

    void ToArrayTest()
    {
        using namespace Templates;
        Vector<int>* Instance;
        int list[] = {2, 6, 8, 4, 7};

        Instance = new Vector<int>(list, 5);
        int Count;
        int* Array = Instance->ToArray(Count);
        assert(Count == 5);
        assert(Array[0] == 2 && Array[1] == 6 && Array[2] == 8 && Array[3] == 4 && Array[4] == 7);
        assert(Instance->Clear() == 5);
        assert(Instance->IsEmpty());
        free(Array);
        Array = Instance->ToArray(Count);
        assert(Array == NULL && Count == 0);
        delete Instance;
        return;
    }

    void InsertingTests()
    {
        using namespace Templates;
        Vector<int>* Instance;
        int list[] = {2, 6, 8, 4, 7};
        int SecondList[] = {12, 16, 22, 13};

        Instance = new Vector<int>(list, 5);
        Vector<int>::Iterator FirstIter = Instance->Begin();
        assert(FirstIter.Next());
        assert(FirstIter.Insert(SecondList, 4));
        assert(Instance->Size() == 9);
        assert(!Instance->IsEmpty());
        assert(*FirstIter.GetValue() == 6);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 12);
        delete Instance;

        Instance = new Vector<int>(list, 5);
        FirstIter = Instance->Begin();
        assert(FirstIter.Insert(9));
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 9);
  delete Instance;
    }

    void IteratorsTest()
    {
        using namespace Templates;

        Vector<int>* Instance = new Vector<int>(5);
        Vector<int>::Iterator FirstIter = Instance->Begin();
        Vector<int>::Iterator SecondIter = Instance->End();
        assert(SecondIter.IsGreaterThan(FirstIter));
        assert(FirstIter.Next());
        assert(SecondIter.IsGreaterThan(FirstIter));
        assert(!FirstIter.IsGreaterThan(SecondIter));
  delete Instance;
    }

 void IteratorAt()
 {
  using namespace Templates;
  Vector<int>* Instance;
  Vector<int>::Iterator Iter;
  int list[] = { 2, 6, 8, 4, 7 };

  Instance = new Vector<int>(list,5);
  assert(Instance->At(3,Iter));
  assert(*Iter.GetValue() == 8);
  delete Instance;

  Instance = new Vector<int>(list, 5);
  assert(!Instance->At(8, Iter));
  delete Instance;
 }

    void VectorBaseTests()
    {
        using namespace Templates;
        Vector<int>* Instance;
        Iterators::ForwardIteratorBase<int>* FirstIter;
        Iterators::ForwardIteratorBase<int>* SecondIter;
        Vector<int>::Iterator FirstIterVal;
        Vector<int>::Iterator SecondIterVal;
        int list[] = {2, 6, 8, 4, 7};
        int SecondList[] = {12, 16, 22, 13};

        Instance = new Vector<int>();
        assert(Instance->Size() == 0);
        assert(Instance->IsEmpty());
        FirstIterVal = Instance->Begin();
        SecondIterVal = Instance->End();
        FirstIter = &FirstIterVal;
        SecondIter = &SecondIterVal;
        assert(!FirstIter->Next());
        assert(!SecondIter->Next(5));
        delete Instance;

        Instance = new Vector<int>(5);
        assert(!Instance->IsEmpty());
        assert(Instance->Size() == 5);
        FirstIterVal = Instance->Begin();
        SecondIterVal = Instance->End();
        FirstIter = &FirstIterVal;
        SecondIter = &SecondIterVal;
        assert(FirstIter->Next());
        assert(!FirstIter->Next(5));
        assert(FirstIter->Next(4));
        assert(!FirstIter->Next());
        delete Instance;

        Instance = new Vector<int>(list, 5);
        FirstIterVal = Instance->Begin();
        Iterators::DeletingForwardIteratorBase<int>* DelIter = &FirstIterVal;
        assert(DelIter->Next());
        assert(DelIter->Insert(SecondList, 4));
        assert(Instance->Size() == 9);
        assert(!Instance->IsEmpty());
        assert(*DelIter->GetValue() == 6);
        assert(DelIter->Next());
        assert(*DelIter->GetValue() == 12);
        delete Instance;
    }

public:
    static void test()
    {
        VectorTest* Instance = new VectorTest;
        Instance->Creation();
        Instance->ClearingTests();
        Instance->ToArrayTest();
        Instance->InsertingTests();
        Instance->IteratorsTest();
  Instance->IteratorAt();
        Instance->VectorBaseTests();
  delete Instance;

        return;
    }
};








class QueueTests
{
private:
 QueueTests()
 { }

 void CreationTests()
 {
  using namespace Templates;
  int list[] = { 2, 6, 7, 4, 3 };
  Queue<int>* Instance;
  int value;

  Instance = new Queue<int>();
  assert(Instance->IsEmpty());
  assert(Instance->Push(5));
  assert(!Instance->IsEmpty());
  assert(Instance->Pop(value) && value == 5);
  delete Instance;

  Instance = new Queue<int>(list, 5);
  assert(!Instance->IsEmpty());
  assert(Instance->Pop(value) && value == 2);
  assert(Instance->Pop(value) && value == 6);
  assert(Instance->Pop(value) && value == 7);
  assert(Instance->Pop(value) && value == 4);
  assert(Instance->Pop(value) && value == 3);
  assert(!Instance->Pop(value));
  delete Instance;

  return;
 }

 void ClearTests()
 {
  using namespace Templates;
  int list[] = { 2, 6, 7, 4, 3 };
  Queue<int>* Instance;
  int value;

  Instance = new Queue<int>(list, 5);
  assert(!Instance->IsEmpty());
  assert(Instance->Clear() == 5);
  assert(Instance->IsEmpty());
  delete Instance;

  Instance = new Queue<int>(list, 5);
  assert(Instance->Clear(3) == 3);
  assert(Instance->Pop(value) && value == 4);
  assert(Instance->Pop(value) && value == 3);
  assert(!Instance->Pop(value));
  delete Instance;

  Instance = new Queue<int>(list, 5);
  assert(Instance->Clear(8) == 5);
  assert(!Instance->Pop(value));
  delete Instance;
 }

 void PushingTests()
 {
  using namespace Templates;
  int list[] = { 2, 6, 7, 4, 3 };
  Queue<int>* Instance;
  int value;

  Instance = new Queue<int>(list, 3);
  assert(Instance->Push(list, 3) == 3);
  assert(Instance->Pop(value) && value == 2);
  assert(Instance->Pop(value) && value == 6);
  assert(Instance->Pop(value) && value == 7);
  assert(Instance->Pop(value) && value == 2);
  assert(Instance->Pop(value) && value == 6);
  assert(Instance->Pop(value) && value == 7);
  assert(!Instance->Pop(value));
  delete Instance;

  Instance = new Queue<int>(list, 3);
  assert(Instance->Push(list+2, 3) == 3);
  assert(Instance->Push(12) == 1);
  assert(Instance->Pop(value) && value == 2);
  assert(Instance->Pop(value) && value == 6);
  assert(Instance->Pop(value) && value == 7);
  assert(Instance->Pop(value) && value == 7);
  assert(Instance->Pop(value) && value == 4);
  assert(Instance->Pop(value) && value == 3);
  assert(Instance->Pop(value) && value == 12);
  assert(!Instance->Pop(value));
  delete Instance;
 }

 void IteratorTests()
 {
  using namespace Templates;
  int list[] = { 2, 6, 7, 4, 3 };
  Queue<int>* Instance;
  Queue<int>::Iterator Iterator;

  Instance = new Queue<int>(list, 5);
  Iterator = Instance->Begin();
  assert(*Iterator.GetValue() == 2);
  assert(Iterator.Next());
  assert(*Iterator.GetValue()==6);
  assert(Iterator.Next());
  assert(*Iterator.GetValue() == 7);
  assert(Iterator.Next());
  assert(*Iterator.GetValue() == 4);
  assert(Iterator.Next());
  assert(*Iterator.GetValue() == 3);
  assert(Iterator.Next());
  assert(!Iterator.Next());
  assert(Instance->IsEmpty());
  delete Instance;

  Instance = new Queue<int>(list, 5);
  Iterator = Instance->Begin();
  assert(*Iterator.GetValue() == 2);
  assert(Iterator.Next(3));
  assert(*Iterator.GetValue() == 4);
  assert(Iterator.Next());
  assert(!Instance->IsEmpty());
  delete Instance;

  Instance = new Queue<int>(list, 5);
  Iterator = Instance->Begin();
  assert(*Iterator.GetValue() == 2);
  assert(!Iterator.Next(10));
  assert(!Instance->IsEmpty());
  delete Instance;
 }

public:
 static void test()
 {
  QueueTests test;
  test.CreationTests();
  test.ClearTests();
  test.PushingTests();
  test.IteratorTests();
 }
};








static bool MyValidation(const int* const x)
{
    return *x < 5;
}

static bool ReturnsTrue(const int* const x)
{
    return true;
}

class CondQueueTests
{
private:
    CondQueueTests()
    { }

    void Creating()
    {
        using namespace Templates;
        CondQueue<int>* Instance;
        int val =0;
        int list[] = {2,6,3,1,8,7};

        Instance = new CondQueue<int>(MyValidation,list,6);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val) && val == 2);
        assert(Instance->Pop(val) && val == 3);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new CondQueue<int>(MyValidation);
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;
    }

    void PushingTests()
    {
        using namespace Templates;
        CondQueue<int>* Instance;
        int val =0;
        int list[] = {2,6,3,1,8,7};
        int listFirst[] = {1,4,2,3};
        int listBad[] = {8,12,7,6};
        int listBeginBad[] = {8,3,2,4,4};

        Instance = new CondQueue<int>(MyValidation,list,3);
        assert(!Instance->Push(9));
        assert(Instance->Push(4));
        assert(Instance->Push(list+3,2));
        assert(Instance->Pop(val) && val==2);
        assert(Instance->Pop(val) && val==3);
        assert(Instance->Pop(val) && val==4);
        assert(Instance->Pop(val) && val==1);
        assert(!Instance->Pop(val));
        assert(Instance->IsEmpty());
        delete Instance;

        Instance = new CondQueue<int>(ReturnsTrue,listFirst,4);
        Instance->SetCallback(MyValidation);
        assert(Instance->ValidateQueue()==0);
        assert(Instance->Pop(val) && val==1);
        assert(Instance->Pop(val) && val==4);
        assert(Instance->Pop(val) && val==2);
        assert(Instance->Pop(val) && val==3);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new CondQueue<int>(ReturnsTrue,listBad,4);
        Instance->SetCallback(MyValidation);
        assert(Instance->ValidateQueue()==4);
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new CondQueue<int>(ReturnsTrue,listBeginBad,5);
        Instance->SetCallback(MyValidation);
        assert(Instance->ValidateQueue()==1);
        assert(Instance->Pop(val) && val==3);
        assert(Instance->Pop(val) && val==2);
        assert(Instance->Pop(val) && val==4);
        assert(Instance->Pop(val) && val==4);
        assert(!Instance->Pop(val));
        assert(Instance->IsEmpty());
        delete Instance;
    }

public:
    static void test()
    {
        CondQueueTests test;
        test.Creating();
        test.PushingTests();
    }
};

bool FindSix(const int* const Val, void* data)
{
    return *Val==6;
}

bool FindTwelve(const int* const Val, void* data)
{
    return *Val==12;
}

bool FindValue(const int* const Val, void* data)
{
    return *Val==*((int*)data);
}
class AlgorithmsTests
{
private:
    AlgorithmsTests()
    { }

    void FindTest()
    {
        using namespace Templates;
        Vector<int>* Instance;
        Vector<int>::Iterator Iter;
        int list[] = {1,6,8,4,2,3,5,7};

        Instance = new Vector<int>(list,8);
        Iter = Instance->Begin();
        assert(!Find(&Iter,FindTwelve));
        Iter = Instance->Begin();
        assert(Find(&Iter,FindSix));
        assert(*Iter.GetValue()==6);
        delete Instance;

        Instance = new Vector<int>(list,8);
        Iter = Instance->Begin();
        int val = 5;
        assert(Find(&Iter,FindValue,&val));
        assert(*Iter.GetValue()==5);
        val = 24;
        assert(!Find(&Iter,FindValue,&val));
        delete Instance;
    }
public:
    static void test()
    {
        AlgorithmsTests tests;
        tests.FindTest();
    }
};








class ListTests
{
private:
    void Creation()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>();
        assert(Instance->Size() == 0);
        assert(Instance->IsEmpty());
        delete Instance;

        Instance = new List<int>(3);
        assert(Instance->Size() == 3);
        assert(!Instance->IsEmpty());
        delete Instance;

        Instance = new List<int>(arr, 6);
        assert(!Instance->IsEmpty());
        assert(Instance->Size() == 6);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2);
        assert(Iter.Next() && *Iter.GetValue() == 6);
        assert(Iter.Next() && *Iter.GetValue() == 8);
        assert(Iter.Next() && *Iter.GetValue() == 4);
        assert(Iter.Next() && *Iter.GetValue() == 2);
        assert(Iter.Next() && *Iter.GetValue() == 6);
        assert(Iter.Next());
        assert(!Iter.IsValidIterator());
        assert(Iter.AreEqual(Instance->End()));
        assert(Iter.Back() && *Iter.GetValue() == 6);
        assert(Iter.IsValidIterator());
        delete Instance;

        return;
    }

    void Iterators()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator First;
        List<int>::Iterator Second;
        List<int>* SecondInstance;
        int arr[] = {2, 6, 8, 4, 2, 6};

        assert(!First.IsValidIterator());
        Instance = new List<int>(arr, 6);
        SecondInstance = new List<int>(arr, 6);
        First = Instance->Begin();
        Second = SecondInstance->End();
        assert(Instance->IsMyIterator(First));
        assert(!Instance->IsMyIterator(Second));
        assert(!SecondInstance->IsMyIterator(First));
        assert(SecondInstance->IsMyIterator(Second));
        delete Instance;
        delete SecondInstance;

        Instance = new List<int>(arr, 6);
        First = Instance->Begin();
        Second = Instance->End();
        assert(Instance->IsMyIterator(First));
        assert(Instance->IsMyIterator(Second));
        assert(Second.IsGreaterThan(First));
        assert(!First.IsGreaterThan(Second));
        while (!First.AreEqual(Second))
            assert(First.Next());
        assert(First.AreEqual(Second));
        assert(Second.AreEqual(First));
        assert(First.Back() && Second.Back());
        assert(First.AreEqual(Second));
        assert(*First.GetValue() == 6 && *Second.GetValue() == 6);
        delete Instance;

        Instance = new List<int>(arr, 6);
        First = Instance->Begin();
        Second = Instance->End();
        assert(First.Next(4) && *First.GetValue() == 2);
        assert(Second.Back(3) && *Second.GetValue() == 4);
        First = Instance->Begin();
        Second = Instance->End();
        assert(!First.Next(12));
        assert(*First.GetValue() == 2);
        assert(!Second.Back(10));
        assert(!Second.IsValidIterator());
        assert(Second.Back() && *Second.GetValue() == 6);
        delete Instance;

        Instance = new List<int>(arr, 6);
        First = Instance->Begin();
        Second = Instance->End();
        assert(First.Next());
        First.SetValue(12);
        Second = Instance->Begin();
        assert(Second.Next() && *Second.GetValue() == 12);
        delete Instance;
    }

    void Inserting()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};
        int secondArr[] = {12, 16, 18, 14, 13};

        Instance = new List<int>(arr, 6);
        Iter = Instance->Begin();
        assert(Iter.Insert(4) == 1);
        assert(*Iter.GetValue() == 2);
        assert(Iter.Next() && *Iter.GetValue() == 4);
        assert(Iter.Next() && *Iter.GetValue() == 6);
        assert(Iter.Insert(secondArr, 3));
        assert(*Iter.GetValue() == 6);
        assert(Iter.Next() && *Iter.GetValue() == 12);
        assert(Iter.Next() && *Iter.GetValue() == 16);
        assert(Iter.Next() && *Iter.GetValue() == 18);
        assert(Iter.Next() && *Iter.GetValue() == 8);
        delete Instance;

        Instance = new List<int>(arr, 6);
        Iter = Instance->End();
        assert(Iter.Insert(12) == -1);
        assert(Iter.Insert(secondArr, 5) == -1);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>();
        Iter = Instance->End();
        assert(Iter.Insert(12) == -1);
        assert(Iter.Insert(secondArr, 5) == -1);
        assert(Iter.InsertBefore(14));
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 14 && Iter.Next());
        delete Instance;

        Instance = new List<int>();
        Iter = Instance->Begin();
        assert(Iter.Insert(14) == -1);
        assert(Iter.AreEqual(Instance->End()));
        assert(Instance->End().InsertBefore(14));
        assert(Iter.Back() && *Iter.GetValue() == 14 && Iter.Next());
        delete Instance;


        Instance = new List<int>(arr, 6);
        Iter = Instance->Begin();
        assert(Iter.Insert(12)==1);
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 12 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);
        Iter = Instance->Begin();
        assert(Iter.InsertBefore(12)==1);
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        Iter=Instance->Begin();
        assert(*Iter.GetValue() == 12 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;
    }

    void Deleting()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>(arr, 6);
        assert(Instance->Delete(1) == 1);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);
        assert(Instance->Delete(3) == 3);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);
        Iter = Instance->Begin();
        assert(Instance->Delete(Iter, 3) == 3);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);
        Iter = Instance->Begin();
        assert(Instance->Delete(Iter, 3) == 3);
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);
        Iter = Instance->Begin();
        assert(Iter.Next());
        assert(Instance->Delete(Iter, 3) == 3);
        assert(Iter.Back() && *Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);
        assert(Instance->Delete() == 6);
        assert(Instance->Size() == 0);
        assert(Instance->IsEmpty());
        delete Instance;

        Instance = new List<int>(arr, 6);
        Iter = Instance->End();
        assert(Iter.DeleteBefore(2) == 2);
        assert(!Instance->IsEmpty());
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);
        Iter = Instance->Begin();
        assert(Iter.DeleteBefore(3) == 0);
        delete Instance;

        Instance = new List<int>(arr, 6);
        Iter = Instance->End();
        try
        {
            Iter.DeleteAfter(3);
            assert(false);
        }
        catch (OutOfRangeException* e)
        {
            delete e;
            assert(true);
        }
        delete Instance;
    }

    void BackInserting()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>();
        Iter = Instance->Begin();
        Iter.InsertBefore(5);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 5);
        delete Instance;

        Instance = new List<int>();
        Iter = Instance->Begin();
        Iter.InsertBefore(5);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 5);
        delete Instance;

        Instance = new List<int>(arr, 3);
        Iter = Instance->End();
        Iter.InsertBefore(4);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        delete Instance;


        Instance = new List<int>(arr, 3);
        Iter = Instance->End();
        Iter.InsertBefore(arr + 2, 2);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 3);
        Iter = Instance->Begin();
        Iter.InsertBefore(arr + 2, 2);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        delete Instance;
    }

    void ToArrayTest()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int count;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>(arr, 6);
        int* Array = Instance->ToArray(count);
        assert(count == 6);
        assert(*Array == 2);
        assert(*(Array + 1) == 6);
        assert(*(Array + 2) == 8);
        assert(*(Array + 3) == 4);
        assert(*(Array + 4) == 2);
        assert(*(Array + 5) == 6);
        delete Instance;
        free(Array);

        Instance = new List<int>(arr, 6);
        int** WriteArray = Instance->ToWriteArray(count);
        assert(count == 6);
        **(WriteArray + 1) = 12;
        **(WriteArray + 4) = 25;
        free(WriteArray);
        Array = Instance->ToArray(count);
        assert(count == 6);
        assert(*Array == 2);
        assert(*(Array + 1) == 12);
        assert(*(Array + 2) == 8);
        assert(*(Array + 3) == 4);
        assert(*(Array + 4) == 25);
        assert(*(Array + 5) == 6);
        free(Array);
        delete Instance;
    }

    void DeleteThisTests()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>(arr, 6);
        Iter = Instance->Begin();
        assert(Iter.Next() && Iter.Next());
        assert(*Iter.GetValue() == 8);
        assert(Iter.DeleteThis() == 1);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(!Iter.IsValidIterator());
        assert(!Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);
        Iter = Instance->Begin();
        assert(Iter.DeleteThis() == 1);
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(!Iter.IsValidIterator());
        assert(!Iter.Next());
        delete Instance;
    }

    static bool FittingCallback(const int* const First, const int* const Second)
    {
        return *First < *Second;
    }

    void BestFittingsTests()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>(arr, 6);
        Iter = Instance->Begin();
        Iter.FindBestFitting(FittingCallback);
        assert(*Iter.GetValue() == 2);
        assert(Iter.DeleteThis() == 1);
        Iter = Instance->Begin();
        Iter.FindBestFitting(FittingCallback);
        assert(*Iter.GetValue() == 2);
        assert(Iter.DeleteThis() == 1);
        Iter = Instance->Begin();
        Iter.FindBestFitting(FittingCallback);
        assert(*Iter.GetValue() == 4);
        delete Instance;
    }

    static bool Sorting(const int* const First, const int* const Second)
    {
        return *First < *Second;
    }

    void SortingTests()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>(arr,6);
        Instance->Sort(Sorting);
        Iter = Instance->Begin();
        assert(*Iter.GetValue()==2 && Iter.Next());
        assert(*Iter.GetValue()==2 && Iter.Next());
        assert(*Iter.GetValue()==4 && Iter.Next());
        assert(*Iter.GetValue()==6 && Iter.Next());
        assert(*Iter.GetValue()==6 && Iter.Next());
        assert(*Iter.GetValue()==8 && Iter.Next());
        delete Instance;
        return;
    }

public:
    static void test()
    {
        ListTests instane;
        instane.Creation();
        instane.Iterators();
        instane.Inserting();
        instane.Deleting();
        instane.BackInserting();
        instane.ToArrayTest();
        instane.DeleteThisTests();
        instane.BestFittingsTests();
        instane.SortingTests();
    }
};




class PriorityQueueTests
{
private:
    static int Valid(const int* const First, const int* const Second)
    {
        return *First - *Second;
    }

    void tests()
    {
        using namespace Templates;
        PriorityQueue<int>* Queue;
        int val;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(5));
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(5));
        assert(Queue->Push(1));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(1));
        assert(Queue->Push(5));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(5));
        assert(Queue->Push(1));
        assert(Queue->Push(3));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(1));
        assert(Queue->Push(3));
        assert(Queue->Push(5));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(5));
        assert(Queue->Push(3));
        assert(Queue->Push(1));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(1));
        assert(Queue->Push(5));
        assert(Queue->Push(3));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(3));
        assert(Queue->Push(5));
        assert(Queue->Push(1));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;

        Queue = new PriorityQueue<int>(Valid);
        assert(Queue->Push(3));
        assert(Queue->Push(1));
        assert(Queue->Push(5));
        assert(Queue->Pop(val) && val == 1);
        assert(Queue->Pop(val) && val == 3);
        assert(Queue->Pop(val) && val == 5);
        assert(!Queue->Pop(val));
        delete Queue;
    }

    void SortingTest()
    {
        using namespace Templates;
        PriorityQueue<int>* Queue;
        int val;
        int list[] = {25, 12, 36, 52, 14, 98, 52, 36, 54, 74, 32};

        Queue = new PriorityQueue<int>(Valid);
        for (int a = 0; a < 11; a++)
            Queue->Push(list[a]);


        assert(Queue->Pop(val) && val == 12);
        assert(Queue->Pop(val) && val == 14);
        assert(Queue->Pop(val) && val == 25);
        assert(Queue->Pop(val) && val == 32);
        assert(Queue->Pop(val) && val == 36);
        assert(Queue->Pop(val) && val == 36);
        assert(Queue->Pop(val) && val == 52);
        assert(Queue->Pop(val) && val == 52);
        assert(Queue->Pop(val) && val == 54);
        assert(Queue->Pop(val) && val == 74);
        assert(Queue->Pop(val) && val == 98);
        assert(!Queue->Pop(val));
        delete Queue;
        return;
    };

    void LaterInserting()
    {
        using namespace Templates;
        PriorityQueue<int>* Queue;
        int val;
        int list[] = {25, 12, 36, 52, 14, 98, 52, 36, 54, 74, 32};

        Queue = new PriorityQueue<int>(Valid);
        for (int a = 0; a < 11; a++)
            Queue->Push(list[a]);


        assert(Queue->Pop(val) && val == 12);
        assert(Queue->Pop(val) && val == 14);
        assert(Queue->Pop(val) && val == 25);
        assert(Queue->Pop(val) && val == 32);
        assert(Queue->Pop(val) && val == 36);
        assert(Queue->Pop(val) && val == 36);

        for(int a=4;a<8;a++)
            assert(Queue->Push(list[a]));


        assert(Queue->Pop(val) && val == 14);
        assert(Queue->Pop(val) && val == 36);
        assert(Queue->Pop(val) && val == 52);
        assert(Queue->Pop(val) && val == 52);
        assert(Queue->Pop(val) && val == 52);
        assert(Queue->Pop(val) && val == 54);
        assert(Queue->Pop(val) && val == 74);
        assert(Queue->Pop(val) && val == 98);
        assert(Queue->Pop(val) && val == 98);
        assert(!Queue->Pop(val));
        delete Queue;
    }

public:
    static void test()
    {
        PriorityQueueTests test;
        test.SortingTest();
        test.LaterInserting();
        test.tests();
    }
};






using namespace Templates;

class StackTests
{
private:
    static void CreatingTests()
    {
        Stack<int>* Instance;
        int val;
        int array[4] = {1, 5, 8, 9};

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val));
        assert(val == 9);
        delete Instance;
    }

    static void CloneAndAssignmentTests()
    {
        Stack<int>* Instance;
        Stack<int>* SecondInstance;
        int val;
        int array[4] = {1, 5, 8, 9};

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        SecondInstance = new Stack<int>(*Instance);
        assert(SecondInstance->IsEmpty());
        assert(!SecondInstance->Pop(val));
        delete Instance;
        delete SecondInstance;

        Instance = new Stack<int>(array, 4);
        SecondInstance = new Stack<int>(*Instance);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val));
        assert(val == 9);
        assert(!SecondInstance->IsEmpty());
        assert(SecondInstance->Pop(val));
        assert(val == 9);
        assert(Instance->Pop(val));
        assert(val == 8);
        assert(SecondInstance->Pop(val));
        assert(val == 8);
        delete Instance;
        delete SecondInstance;


        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        SecondInstance = new Stack<int>(array, 4);
        *SecondInstance = *Instance;
        assert(SecondInstance->IsEmpty());
        assert(!SecondInstance->Pop(val));
        delete Instance;
        delete SecondInstance;

        Instance = new Stack<int>(array, 4);
        SecondInstance = new Stack<int>(array, 2);
        *SecondInstance = *Instance;
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val));
        assert(val == 9);
        assert(!SecondInstance->IsEmpty());
        assert(SecondInstance->Pop(val));
        assert(val == 9);
        assert(Instance->Pop(val));
        assert(val == 8);
        assert(SecondInstance->Pop(val));
        assert(val == 8);
        delete Instance;
        delete SecondInstance;

        Instance = new Stack<int>(array, 4);
        SecondInstance = new Stack<int>();
        *SecondInstance = *Instance;
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val));
        assert(val == 9);
        assert(!SecondInstance->IsEmpty());
        assert(SecondInstance->Pop(val));
        assert(val == 9);
        assert(Instance->Pop(val));
        assert(val == 8);
        assert(SecondInstance->Pop(val));
        assert(val == 8);
        delete Instance;
        delete SecondInstance;
    }

    static void PushAndPopTests()
    {
        Stack<int>* Instance;
        int val;
        int array[4] = {1, 5, 8, 9};

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val) && val == 9);
        assert(Instance->Pop(val) && val == 8);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        assert(Instance->Push(5) == 1);
        assert(Instance->Pop(val) && val == 5);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Push(16) == 1);
        assert(Instance->Pop(val) && val == 16);
        assert(Instance->Pop(val) && val == 9);
        assert(Instance->Pop(val) && val == 8);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val) && val == 9);
        assert(Instance->Pop(val) && val == 8);
        assert(Instance->Push(16) == 1);
        assert(Instance->Pop(val) && val == 16);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val) && val == 9);
        assert(Instance->Pop(val) && val == 8);
        assert(Instance->Push(16) == 1);
        assert(Instance->Push(27) == 1);
        assert(Instance->Pop(val) && val == 27);
        assert(Instance->Pop(val) && val == 16);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        assert(Instance->Push(array, 4) == 4);
        assert(Instance->Pop(val) && val == 9);
        assert(Instance->Pop(val) && val == 8);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val) && val == 9);
        assert(Instance->Pop(val) && val == 8);
        assert(Instance->Push(array, 2) == 2);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;
    }

    static void IteratorTests()
    {
        Stack<int>* Instance;
        int array[4] = {2, 5, 6, 8};
        Stack<int>::Iterator Iterator;

        Instance = new Stack<int>(array,4);
        Iterator = Instance->Begin();
        assert(Iterator.IsValidIterator());
        assert(*Iterator.GetValue()==8);
        assert(Iterator.Next());
        assert(*Iterator.GetValue()==6);
        assert(Iterator.Next());
        assert(*Iterator.GetValue()==5);
        assert(Iterator.Next());
        assert(*Iterator.GetValue()==2);
        assert(!Iterator.Next());
        delete Instance;

        Instance = new Stack<int>(array,4);
        Iterator = Instance->Begin();
        assert(Iterator.IsValidIterator());
        assert(*Iterator.GetValue()==8);
        assert(Iterator.Next(4));
        assert(!Iterator.Next());
        delete Instance;

        Instance = new Stack<int>(array,4);
        Iterator = Instance->Begin();
        assert(Iterator.IsValidIterator());
        assert(*Iterator.GetValue()==8);
        assert(!Iterator.Next(5));
        assert(*Iterator.GetValue()==8);
        assert(Iterator.Next());
        assert(*Iterator.GetValue()==6);
        assert(Iterator.Next());
        assert(*Iterator.GetValue()==5);
        assert(Iterator.Next());
        assert(*Iterator.GetValue()==2);
        assert(!Iterator.Next());
        delete Instance;
    }

    static void ToArrayTests()
    {
        Stack<int>* Instance;
        int val;
        int array[4] = {2, 5, 6, 8};
        int* NextArray;

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        NextArray = Instance->ToArray(val);
        assert(NextArray == NULL);
        free(NextArray);
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        NextArray = Instance->ToArray(val);
        assert(NextArray != NULL && val == 4);
        assert(NextArray[0] == 8 && NextArray[1] == 6 && NextArray[2] == 5 && NextArray[3] == 2);
        free(NextArray);
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(Instance->Push(15) == 1);
        assert(!Instance->IsEmpty());
        NextArray = Instance->ToArray(val);
        assert(NextArray != NULL && val == 5);
        assert(NextArray[0]==15 && NextArray[1] == 8 && NextArray[2] == 6 && NextArray[3] == 5 && NextArray[4] == 2);
        free(NextArray);
        delete Instance;

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(Instance->Push(array,4)==4);
        NextArray = Instance->ToArray(val);
        assert(NextArray != NULL && val == 4);
        assert(NextArray[0] == 8 && NextArray[1] == 6 && NextArray[2] == 5 && NextArray[3] == 2);
        free(NextArray);
        delete Instance;
    }

    static void ClearTests()
    {
        Stack<int>* Instance;
        int val;
        int array[4] = {2, 5, 6, 8};

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        assert(Instance->Clear() == 0);
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Clear() == 4);
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>();
        assert(Instance->Push(array, 4) == 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Clear() == 4);
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;
    }

public:
    static void test()
    {
        CreatingTests();
        CloneAndAssignmentTests();
        PushAndPopTests();
        IteratorTests();
        ToArrayTests();
        ClearTests();
    }
};




using namespace Templates;

class BinaryHeapTests
{
private:

    static int Sorting(const int* const First, const int* const Second)
    {
        return *First-*Second;
    }

    static void demo()
    {
        BinaryMinHeap<int>* Instance = new BinaryMinHeap<int>(Sorting);
        int val;
        for(int a=0;a<10;a++)
            Instance->Insert(a);
        for(int a=0;a<10;a++)
        {
            assert(Instance->Pop(val));
            assert(val == a);
        }
        delete Instance;
    }
public:
    static void tests()
    {
        demo();
    }
};




extern "C" {


extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     throw () __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     throw () __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     throw () __attribute__ ((__noreturn__));


}



extern "C" {






typedef unsigned _Unwind_Word __attribute__((__mode__(__unwind_word__)));
typedef signed _Unwind_Sword __attribute__((__mode__(__unwind_word__)));



typedef unsigned _Unwind_Ptr __attribute__((__mode__(__pointer__)));

typedef unsigned _Unwind_Internal_Ptr __attribute__((__mode__(__pointer__)));





typedef unsigned _Unwind_Exception_Class __attribute__((__mode__(__DI__)));



typedef enum
{
  _URC_NO_REASON = 0,
  _URC_FOREIGN_EXCEPTION_CAUGHT = 1,
  _URC_FATAL_PHASE2_ERROR = 2,
  _URC_FATAL_PHASE1_ERROR = 3,
  _URC_NORMAL_STOP = 4,
  _URC_END_OF_STACK = 5,
  _URC_HANDLER_FOUND = 6,
  _URC_INSTALL_CONTEXT = 7,
  _URC_CONTINUE_UNWIND = 8
} _Unwind_Reason_Code;
struct _Unwind_Exception;

typedef void (*_Unwind_Exception_Cleanup_Fn) (_Unwind_Reason_Code,
           struct _Unwind_Exception *);

struct _Unwind_Exception
{
  _Unwind_Exception_Class exception_class;
  _Unwind_Exception_Cleanup_Fn exception_cleanup;




  _Unwind_Word private_1;
  _Unwind_Word private_2;





} __attribute__((__aligned__));




typedef int _Unwind_Action;
struct _Unwind_Context;


extern _Unwind_Reason_Code
_Unwind_RaiseException (struct _Unwind_Exception *);



typedef _Unwind_Reason_Code (*_Unwind_Stop_Fn)
     (int, _Unwind_Action, _Unwind_Exception_Class,
      struct _Unwind_Exception *, struct _Unwind_Context *, void *);

extern _Unwind_Reason_Code
_Unwind_ForcedUnwind (struct _Unwind_Exception *, _Unwind_Stop_Fn, void *);


extern void _Unwind_DeleteException (struct _Unwind_Exception *);



extern void
_Unwind_Resume (struct _Unwind_Exception *);



extern _Unwind_Reason_Code
_Unwind_Resume_or_Rethrow (struct _Unwind_Exception *);




typedef _Unwind_Reason_Code (*_Unwind_Trace_Fn)
     (struct _Unwind_Context *, void *);

extern _Unwind_Reason_Code
_Unwind_Backtrace (_Unwind_Trace_Fn, void *);






extern _Unwind_Word _Unwind_GetGR (struct _Unwind_Context *, int);
extern void _Unwind_SetGR (struct _Unwind_Context *, int, _Unwind_Word);

extern _Unwind_Ptr _Unwind_GetIP (struct _Unwind_Context *);
extern _Unwind_Ptr _Unwind_GetIPInfo (struct _Unwind_Context *, int *);
extern void _Unwind_SetIP (struct _Unwind_Context *, _Unwind_Ptr);


extern _Unwind_Word _Unwind_GetCFA (struct _Unwind_Context *);

extern void *_Unwind_GetLanguageSpecificData (struct _Unwind_Context *);

extern _Unwind_Ptr _Unwind_GetRegionStart (struct _Unwind_Context *);
typedef _Unwind_Reason_Code (*_Unwind_Personality_Fn)
     (int, _Unwind_Action, _Unwind_Exception_Class,
      struct _Unwind_Exception *, struct _Unwind_Context *);




struct SjLj_Function_Context;
extern void _Unwind_SjLj_Register (struct SjLj_Function_Context *);
extern void _Unwind_SjLj_Unregister (struct SjLj_Function_Context *);

extern _Unwind_Reason_Code
_Unwind_SjLj_RaiseException (struct _Unwind_Exception *);
extern _Unwind_Reason_Code
_Unwind_SjLj_ForcedUnwind (struct _Unwind_Exception *, _Unwind_Stop_Fn, void *);
extern void
_Unwind_SjLj_Resume (struct _Unwind_Exception *);
extern _Unwind_Reason_Code
_Unwind_SjLj_Resume_or_Rethrow (struct _Unwind_Exception *);
extern _Unwind_Ptr _Unwind_GetDataRelBase (struct _Unwind_Context *);
extern _Unwind_Ptr _Unwind_GetTextRelBase (struct _Unwind_Context *);




extern void * _Unwind_FindEnclosingFunction (void *pc);
  typedef long _sleb128_t;
  typedef unsigned long _uleb128_t;
}





using namespace Templates;

class BinarySearchTreeTests
{
private:
    static int Solve(const int *const First, const int *const Second)
    {
        return *Second - *First;
    }

    static int comparer(const void *first, const void *second)
    {
        return (*(int *) first) - (*(int *) second);
    }

    static bool DeleteBiggerThan(const int *const value, void *data)
    {
        int val = *((int *) data);
        return *value > val;
    }

    static void ContainTest()
    {
        BinarySearchTree<int> *Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 10; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            Instance->Insert(val);
        }
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/BinarySearchTreeTests.h", 37, __PRETTY_FUNCTION__))
                                     ;
        for (int a = 0; a < 15; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            
           ((
           Instance->Contain(val) == (a < 10)
           ) ? static_cast<void> (0) : __assert_fail (
           "Instance->Contain(val) == (a < 10)"
           , "Tests/BinarySearchTreeTests.h", 41, __PRETTY_FUNCTION__))
                                                     ;
        }
        delete Instance;
    }

    static void CopyConstructorTest()
    {
        BinarySearchTree<int> *Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 10; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            Instance->Insert(val);
        }
        BinarySearchTree<int> *Second = new BinarySearchTree<int>(*Instance);
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/BinarySearchTreeTests.h", 55, __PRETTY_FUNCTION__))
                                     ;
        for (int a = 0; a < 15; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            
           ((
           Instance->Contain(val) == (a < 10)
           ) ? static_cast<void> (0) : __assert_fail (
           "Instance->Contain(val) == (a < 10)"
           , "Tests/BinarySearchTreeTests.h", 59, __PRETTY_FUNCTION__))
                                                     ;
        }
        
       ((
       Second->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Second->Size() == 10"
       , "Tests/BinarySearchTreeTests.h", 61, __PRETTY_FUNCTION__))
                                   ;
        for (int a = 0; a < 15; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            
           ((
           Second->Contain(val) == (a < 10)
           ) ? static_cast<void> (0) : __assert_fail (
           "Second->Contain(val) == (a < 10)"
           , "Tests/BinarySearchTreeTests.h", 65, __PRETTY_FUNCTION__))
                                                   ;
        }
        delete Second;
        delete Instance;
    }

    static void OneElementDeleteTests()
    {
        BinarySearchTree<int> *Instance = NULL;
        int *Array = NULL;
        int count;
        int DeleteLeafTestBase[13] = {30, 10, 5, 15, 3, 7, 18, 1, 4, 6, 8, 17, 20};
        int DeleteLeafTestResult[12] = {1, 3, 4, 5, 6, 7, 8, 10, 15, 17, 18, 30};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 13; a++)
            Instance->Insert(DeleteLeafTestBase[a]);
        
       ((
       Instance->Size() == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 13"
       , "Tests/BinarySearchTreeTests.h", 94, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Delete(20) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(20) == 1"
       , "Tests/BinarySearchTreeTests.h", 95, __PRETTY_FUNCTION__))
                                        ;
        
       ((
       Instance->Size() == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 12"
       , "Tests/BinarySearchTreeTests.h", 96, __PRETTY_FUNCTION__))
                                     ;
        Array = Instance->ToArray(count);
        
       ((
       count == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 12"
       , "Tests/BinarySearchTreeTests.h", 98, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
            
           ((
           Array[a] == DeleteLeafTestResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "Array[a] == DeleteLeafTestResult[a]"
           , "Tests/BinarySearchTreeTests.h", 100, __PRETTY_FUNCTION__))
                                                      ;
        delete Instance;
        free(Array);
        int DeleteLeftChildrenNullBase[13] = {30, 10, 5, 15, 3, 7, 18, 1, 4, 6, 8, 17, 20};
        int DeleteLeftChildrenNullResult[12] = {1, 3, 4, 5, 6, 7, 8, 10, 17, 18, 20, 30};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 13; a++)
            Instance->Insert(DeleteLeftChildrenNullBase[a]);
        
       ((
       Instance->Size() == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 13"
       , "Tests/BinarySearchTreeTests.h", 121, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Delete(15) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(15) == 1"
       , "Tests/BinarySearchTreeTests.h", 122, __PRETTY_FUNCTION__))
                                        ;
        
       ((
       Instance->Size() == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 12"
       , "Tests/BinarySearchTreeTests.h", 123, __PRETTY_FUNCTION__))
                                     ;
        Array = Instance->ToArray(count);
        
       ((
       count == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 12"
       , "Tests/BinarySearchTreeTests.h", 125, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
            
           ((
           Array[a] == DeleteLeftChildrenNullResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "Array[a] == DeleteLeftChildrenNullResult[a]"
           , "Tests/BinarySearchTreeTests.h", 127, __PRETTY_FUNCTION__))
                                                              ;
        delete Instance;
        free(Array);
        int DeleteRightChildrenNullBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        int DeleteRightChildrenNullResult[14] = {5, 10, 12, 30, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 15; a++)
            Instance->Insert(DeleteRightChildrenNullBase[a]);
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/BinarySearchTreeTests.h", 151, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Delete(15) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(15) == 1"
       , "Tests/BinarySearchTreeTests.h", 152, __PRETTY_FUNCTION__))
                                        ;
        
       ((
       Instance->Size() == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 14"
       , "Tests/BinarySearchTreeTests.h", 153, __PRETTY_FUNCTION__))
                                     ;
        Array = Instance->ToArray(count);
        
       ((
       count == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 14"
       , "Tests/BinarySearchTreeTests.h", 155, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
            
           ((
           Array[a] == DeleteRightChildrenNullResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "Array[a] == DeleteRightChildrenNullResult[a]"
           , "Tests/BinarySearchTreeTests.h", 157, __PRETTY_FUNCTION__))
                                                               ;
        delete Instance;
        free(Array);
        int LeftRotateTestBase[13] = {30, 10, 5, 15, 3, 7, 18, 1, 4, 6, 8, 17, 20};
        int LeftRotateTestResult[12] = {1, 3, 4, 5, 6, 7, 8, 15, 17, 18, 20, 30};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 13; a++)
            Instance->Insert(LeftRotateTestBase[a]);
        
       ((
       Instance->Size() == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 13"
       , "Tests/BinarySearchTreeTests.h", 178, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Delete(10) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(10) == 1"
       , "Tests/BinarySearchTreeTests.h", 179, __PRETTY_FUNCTION__))
                                        ;
        
       ((
       Instance->Size() == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 12"
       , "Tests/BinarySearchTreeTests.h", 180, __PRETTY_FUNCTION__))
                                     ;
        Array = Instance->ToArray(count);
        
       ((
       count == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 12"
       , "Tests/BinarySearchTreeTests.h", 182, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
            
           ((
           Array[a] == LeftRotateTestResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "Array[a] == LeftRotateTestResult[a]"
           , "Tests/BinarySearchTreeTests.h", 184, __PRETTY_FUNCTION__))
                                                      ;
        delete Instance;
        free(Array);
        int RightRotateTestBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        int RightRotateTestResult[14] = {5, 10, 12, 15, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 15; a++)
            Instance->Insert(RightRotateTestBase[a]);
        
       ((
       Instance->Delete(30) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(30) == 1"
       , "Tests/BinarySearchTreeTests.h", 208, __PRETTY_FUNCTION__))
                                        ;
        Array = Instance->ToArray(count);
        
       ((
       count == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 14"
       , "Tests/BinarySearchTreeTests.h", 210, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
            
           ((
           Array[a] == RightRotateTestResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "Array[a] == RightRotateTestResult[a]"
           , "Tests/BinarySearchTreeTests.h", 212, __PRETTY_FUNCTION__))
                                                       ;
        delete Instance;
        free(Array);
        int RotateInTreeBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        int RotateInTreeResult[14] = {5, 10, 12, 15, 30, 40, 41, 42, 60, 62, 65, 67, 90, 95};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 15; a++)
            Instance->Insert(RotateInTreeBase[a]);
        
       ((
       Instance->Delete(50) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(50) == 1"
       , "Tests/BinarySearchTreeTests.h", 236, __PRETTY_FUNCTION__))
                                        ;
        Array = Instance->ToArray(count);
        
       ((
       count == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 14"
       , "Tests/BinarySearchTreeTests.h", 238, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
            
           ((
           Array[a] == RotateInTreeResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "Array[a] == RotateInTreeResult[a]"
           , "Tests/BinarySearchTreeTests.h", 240, __PRETTY_FUNCTION__))
                                                    ;
        delete Instance;
        free(Array);
        int DeletInTreeFirstBase[15] = {50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 35, 55, 65, 75, 85};
        int DeletInTreeFirstResult[14] = {5, 10, 15, 20, 25, 30, 35, 50, 55, 60, 65, 75, 80, 85};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 15; a++)
            Instance->Insert(DeletInTreeFirstBase[a]);
        
       ((
       Instance->Delete(70) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(70) == 1"
       , "Tests/BinarySearchTreeTests.h", 261, __PRETTY_FUNCTION__))
                                        ;
        Array = Instance->ToArray(count);
        
       ((
       count == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 14"
       , "Tests/BinarySearchTreeTests.h", 263, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
            
           ((
           Array[a] == DeletInTreeFirstResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "Array[a] == DeletInTreeFirstResult[a]"
           , "Tests/BinarySearchTreeTests.h", 265, __PRETTY_FUNCTION__))
                                                        ;
        delete Instance;
        free(Array);
        int DeleRootInTreeBase[15] = {50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 35, 55, 65, 75, 85};
        int DeleRootInTreeResult[14] = {5, 10, 15, 20, 25, 30, 35, 55, 60, 65, 70, 75, 80, 85};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 15; a++)
            Instance->Insert(DeleRootInTreeBase[a]);
        
       ((
       Instance->Delete(50) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(50) == 1"
       , "Tests/BinarySearchTreeTests.h", 285, __PRETTY_FUNCTION__))
                                        ;
        Array = Instance->ToArray(count);
        
       ((
       count == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 14"
       , "Tests/BinarySearchTreeTests.h", 287, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
            
           ((
           Array[a] == DeleRootInTreeResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "Array[a] == DeleRootInTreeResult[a]"
           , "Tests/BinarySearchTreeTests.h", 289, __PRETTY_FUNCTION__))
                                                      ;
        delete Instance;
        free(Array);
    }

    static void ToArrayTest()
    {
        BinarySearchTree<int> *Instance = new BinarySearchTree<int>(Solve);
        int HelpArray[] = {50, 538, 1037, 1525, 2024, 2512, 3011, 3499, 3510, 3998};
        int SecondHelpInstance[100];
        int *Array = NULL;
        int Count;

        for (int a = 0; a < 10; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            Instance->Insert(val);
        }
        Array = Instance->ToArray(Count);
        for (int a = 0; a < 10; a++)
            
           ((
           Array[a] == HelpArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "Array[a] == HelpArray[a]"
           , "Tests/BinarySearchTreeTests.h", 309, __PRETTY_FUNCTION__))
                                           ;
        free(Array);
        delete Instance;

        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 100; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            Instance->Insert(val);
            SecondHelpInstance[a] = val;
        }
        Array = Instance->ToArray(Count);
        qsort(&SecondHelpInstance, 100, sizeof(int), comparer);
        for (int a = 0; a < 10; a++)
            
           ((
           Array[a] == SecondHelpInstance[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "Array[a] == SecondHelpInstance[a]"
           , "Tests/BinarySearchTreeTests.h", 323, __PRETTY_FUNCTION__))
                                                    ;
        free(Array);
        delete Instance;
    }

    static void MultipleDeletion()
    {
        BinarySearchTree<int> *Instance = NULL;
        int count;
        int *Array;



        Instance = new BinarySearchTree<int>(Solve);
        count = 2000;
        
       ((
       Instance->Size() == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 0"
       , "Tests/BinarySearchTreeTests.h", 338, __PRETTY_FUNCTION__))
                                    ;
        
       ((
       Instance->Delete(DeleteBiggerThan, &count) == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(DeleteBiggerThan, &count) == 0"
       , "Tests/BinarySearchTreeTests.h", 339, __PRETTY_FUNCTION__))
                                                              ;
        
       ((
       Instance->Size() == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 0"
       , "Tests/BinarySearchTreeTests.h", 340, __PRETTY_FUNCTION__))
                                    ;
        delete Instance;


        Instance = new BinarySearchTree<int>(Solve);
        int ResultSecond[] = {50, 538, 1037, 1525};
        for (int a = 0; a < 10; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            Instance->Insert(val);
        }
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/BinarySearchTreeTests.h", 351, __PRETTY_FUNCTION__))
                                     ;
        count = 2000;
        
       ((
       Instance->Delete(DeleteBiggerThan, &count) == 6
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(DeleteBiggerThan, &count) == 6"
       , "Tests/BinarySearchTreeTests.h", 353, __PRETTY_FUNCTION__))
                                                              ;
        
       ((
       Instance->Size() == 4
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 4"
       , "Tests/BinarySearchTreeTests.h", 354, __PRETTY_FUNCTION__))
                                    ;
        Array = Instance->ToArray(count);
        
       ((
       count == 4
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 4"
       , "Tests/BinarySearchTreeTests.h", 356, __PRETTY_FUNCTION__))
                         ;
        for (int a = 0; a < 4; a++)
            
           ((
           Array[a] == ResultSecond[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "Array[a] == ResultSecond[a]"
           , "Tests/BinarySearchTreeTests.h", 358, __PRETTY_FUNCTION__))
                                              ;
        delete Instance;
        free(Array);
    }

    static void GetTest()
    {
        int BaseArray[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        BinarySearchTree<int> *Instance = NULL;
        int ToFind;
        int* ToGet;

        Instance = new BinarySearchTree<int>(Solve);
        Instance->Insert(BaseArray, 15);
        ToFind = 15;
        
       ((
       Instance->Get(ToGet, ToFind)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Get(ToGet, ToFind)"
       , "Tests/BinarySearchTreeTests.h", 387, __PRETTY_FUNCTION__))
                                           ;
        
       ((
       *ToGet == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "*ToGet == 15"
       , "Tests/BinarySearchTreeTests.h", 388, __PRETTY_FUNCTION__))
                           ;
        delete Instance;

        Instance = new BinarySearchTree<int>(Solve);
        Instance->Insert(BaseArray, 15);
        ToFind = 43;
        
       ((
       !Instance->Get(ToGet, ToFind)
       ) ? static_cast<void> (0) : __assert_fail (
       "!Instance->Get(ToGet, ToFind)"
       , "Tests/BinarySearchTreeTests.h", 394, __PRETTY_FUNCTION__))
                                            ;
        delete Instance;
    }

    static void NotDuplicateTests()
    {
        int BaseArray[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        BinarySearchTree<int, false> *Instance = NULL;
        int ToInsert;

        Instance = new BinarySearchTree<int, false>(Solve);
        Instance->Insert(BaseArray, 15);
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/BinarySearchTreeTests.h", 420, __PRETTY_FUNCTION__))
                                     ;
        ToInsert = 62;
        
       ((
       Instance->Insert(ToInsert) == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(ToInsert) == 0"
       , "Tests/BinarySearchTreeTests.h", 422, __PRETTY_FUNCTION__))
                                              ;
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/BinarySearchTreeTests.h", 423, __PRETTY_FUNCTION__))
                                     ;
        ToInsert = 43;
        
       ((
       Instance->Insert(ToInsert) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(ToInsert) == 1"
       , "Tests/BinarySearchTreeTests.h", 425, __PRETTY_FUNCTION__))
                                              ;
        
       ((
       Instance->Size() == 16
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 16"
       , "Tests/BinarySearchTreeTests.h", 426, __PRETTY_FUNCTION__))
                                     ;
        delete Instance;


        Instance = new BinarySearchTree<int, false>(Solve);
        Instance->Insert(BaseArray, 10);
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/BinarySearchTreeTests.h", 432, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Insert(BaseArray, 5) == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(BaseArray, 5) == 0"
       , "Tests/BinarySearchTreeTests.h", 433, __PRETTY_FUNCTION__))
                                                  ;
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/BinarySearchTreeTests.h", 434, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Insert(BaseArray + 10, 5) == 5
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(BaseArray + 10, 5) == 5"
       , "Tests/BinarySearchTreeTests.h", 435, __PRETTY_FUNCTION__))
                                                       ;
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/BinarySearchTreeTests.h", 436, __PRETTY_FUNCTION__))
                                     ;
        delete Instance;

        int TempArray[5] = {1, 2, 3, 1, 2};
        Instance = new BinarySearchTree<int, false>(Solve);
        
       ((
       Instance->Insert(TempArray, 5) == 3
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(TempArray, 5) == 3"
       , "Tests/BinarySearchTreeTests.h", 441, __PRETTY_FUNCTION__))
                                                  ;
        
       ((
       Instance->Size() == 3
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 3"
       , "Tests/BinarySearchTreeTests.h", 442, __PRETTY_FUNCTION__))
                                    ;
        for (int a = 0; a < 3; a++)
            Instance->Contain(TempArray[a]);
        delete Instance;
    }

    struct CustomClass
    {
        int Key;
        int Value;
    };

    static int CompareCustomClass(const CustomClass *const First, const CustomClass *const Second)
    {
        return Second->Key - First->Key;
    }

    static void GetOrCreateIntTests()
    {
        BinarySearchTree<int, false> *Instance = NULL;
        int array[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 17};
        int *CreatedArray;
        int count;
        int ToInsert;
        int* ToGet = NULL;

        Instance = new BinarySearchTree<int, false>(Solve);
        
       ((
       Instance->Insert(array, 10) == 9
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(array, 10) == 9"
       , "Tests/BinarySearchTreeTests.h", 469, __PRETTY_FUNCTION__))
                                               ;
        
       ((
       Instance->Size() == 9
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 9"
       , "Tests/BinarySearchTreeTests.h", 470, __PRETTY_FUNCTION__))
                                    ;
        ToInsert = 15;
        
       ((
       Instance->GetOrCreate(ToInsert, ToGet) == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetOrCreate(ToInsert, ToGet) == 0"
       , "Tests/BinarySearchTreeTests.h", 472, __PRETTY_FUNCTION__))
                                                          ;
        
       ((
       *ToGet == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "*ToGet == 15"
       , "Tests/BinarySearchTreeTests.h", 473, __PRETTY_FUNCTION__))
                           ;
        delete Instance;

        Instance = new BinarySearchTree<int, false>(Solve);
        
       ((
       Instance->Insert(array, 10) == 9
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(array, 10) == 9"
       , "Tests/BinarySearchTreeTests.h", 477, __PRETTY_FUNCTION__))
                                               ;
        
       ((
       Instance->Size() == 9
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 9"
       , "Tests/BinarySearchTreeTests.h", 478, __PRETTY_FUNCTION__))
                                    ;
        ToInsert = 19;
        
       ((
       Instance->GetOrCreate(ToInsert, ToGet) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetOrCreate(ToInsert, ToGet) == 1"
       , "Tests/BinarySearchTreeTests.h", 480, __PRETTY_FUNCTION__))
                                                          ;
        
       ((
       *ToGet == 19
       ) ? static_cast<void> (0) : __assert_fail (
       "*ToGet == 19"
       , "Tests/BinarySearchTreeTests.h", 481, __PRETTY_FUNCTION__))
                           ;
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/BinarySearchTreeTests.h", 482, __PRETTY_FUNCTION__))
                                     ;
        delete Instance;

        Instance = new BinarySearchTree<int, false>(Solve);
        
       ((
       Instance->Insert(array, 10) == 9
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(array, 10) == 9"
       , "Tests/BinarySearchTreeTests.h", 486, __PRETTY_FUNCTION__))
                                               ;
        
       ((
       Instance->Size() == 9
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 9"
       , "Tests/BinarySearchTreeTests.h", 487, __PRETTY_FUNCTION__))
                                    ;
        ToInsert = 19;
        
       ((
       Instance->GetOrCreate(ToInsert, ToGet) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetOrCreate(ToInsert, ToGet) == 1"
       , "Tests/BinarySearchTreeTests.h", 489, __PRETTY_FUNCTION__))
                                                          ;
        
       ((
       *ToGet == 19
       ) ? static_cast<void> (0) : __assert_fail (
       "*ToGet == 19"
       , "Tests/BinarySearchTreeTests.h", 490, __PRETTY_FUNCTION__))
                           ;
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/BinarySearchTreeTests.h", 491, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->GetOrCreate(ToInsert, ToGet) == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetOrCreate(ToInsert, ToGet) == 0"
       , "Tests/BinarySearchTreeTests.h", 492, __PRETTY_FUNCTION__))
                                                          ;
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/BinarySearchTreeTests.h", 493, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       *ToGet == 19
       ) ? static_cast<void> (0) : __assert_fail (
       "*ToGet == 19"
       , "Tests/BinarySearchTreeTests.h", 494, __PRETTY_FUNCTION__))
                           ;
        CreatedArray = Instance->ToArray(count);
        
       ((
       count == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 10"
       , "Tests/BinarySearchTreeTests.h", 496, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < 9; a++)
            
           ((
           CreatedArray[a] == array[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a] == array[a]"
           , "Tests/BinarySearchTreeTests.h", 498, __PRETTY_FUNCTION__))
                                              ;
        
       ((
       CreatedArray[9] == 19
       ) ? static_cast<void> (0) : __assert_fail (
       "CreatedArray[9] == 19"
       , "Tests/BinarySearchTreeTests.h", 499, __PRETTY_FUNCTION__))
                                    ;
        delete Instance;
        free(CreatedArray);
    }

    static void GetOrCreateCustomClassTests()
    {
        BinarySearchTree<CustomClass, false> *Instance = NULL;
        int count;
        CustomClass BaseArrayThrteen[13] = {{30, 1},
                                            {10, 2},
                                            {5, 3},
                                            {15, 4},
                                            {3, 5},
                                            {7, 6},
                                            {18, 7},
                                            {1, 8},
                                            {4, 9},
                                            {6, 10},
                                            {8, 11},
                                            {17, 12},
                                            {20, 13}};
        int AfterSorted[14] = {1, 3, 4, 5, 6, 7, 8, 10, 15, 17, 18, 20, 25, 30};
        CustomClass ToCreate;
        CustomClass* ToGet;
        CustomClass *CreatedArray;
        Instance = new BinarySearchTree<CustomClass, false>(CompareCustomClass);
        
       ((
       Instance->Insert(BaseArrayThrteen, 13) == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(BaseArrayThrteen, 13) == 13"
       , "Tests/BinarySearchTreeTests.h", 539, __PRETTY_FUNCTION__))
                                                           ;
        
       ((
       Instance->Size() == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 13"
       , "Tests/BinarySearchTreeTests.h", 540, __PRETTY_FUNCTION__))
                                     ;
        ToCreate.Key = 15;
        
       ((
       Instance->GetOrCreate(ToCreate, ToGet) == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetOrCreate(ToCreate, ToGet) == 0"
       , "Tests/BinarySearchTreeTests.h", 542, __PRETTY_FUNCTION__))
                                                          ;
        
       ((
       Instance->Size() == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 13"
       , "Tests/BinarySearchTreeTests.h", 543, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       ToGet->Key == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet->Key == 15"
       , "Tests/BinarySearchTreeTests.h", 544, __PRETTY_FUNCTION__))
                               ;
        
       ((
       ToGet->Value == 4
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet->Value == 4"
       , "Tests/BinarySearchTreeTests.h", 545, __PRETTY_FUNCTION__))
                                ;
        delete Instance;

        Instance = new BinarySearchTree<CustomClass, false>(CompareCustomClass);
        
       ((
       Instance->Insert(BaseArrayThrteen, 13) == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(BaseArrayThrteen, 13) == 13"
       , "Tests/BinarySearchTreeTests.h", 549, __PRETTY_FUNCTION__))
                                                           ;
        
       ((
       Instance->Size() == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 13"
       , "Tests/BinarySearchTreeTests.h", 550, __PRETTY_FUNCTION__))
                                     ;
        ToCreate.Key = 25;
        
       ((
       Instance->GetOrCreate(ToCreate, ToGet) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetOrCreate(ToCreate, ToGet) == 1"
       , "Tests/BinarySearchTreeTests.h", 552, __PRETTY_FUNCTION__))
                                                          ;
        
       ((
       Instance->Size() == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 14"
       , "Tests/BinarySearchTreeTests.h", 553, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       ToGet->Key == 25
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet->Key == 25"
       , "Tests/BinarySearchTreeTests.h", 554, __PRETTY_FUNCTION__))
                               ;
        ToGet->Value=0;
        
       ((
       Instance->GetOrCreate(ToCreate, ToGet) == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetOrCreate(ToCreate, ToGet) == 0"
       , "Tests/BinarySearchTreeTests.h", 556, __PRETTY_FUNCTION__))
                                                          ;
        
       ((
       Instance->Size() == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 14"
       , "Tests/BinarySearchTreeTests.h", 557, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       ToGet->Key == 25
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet->Key == 25"
       , "Tests/BinarySearchTreeTests.h", 558, __PRETTY_FUNCTION__))
                               ;
        
       ((
       ToGet->Value == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet->Value == 0"
       , "Tests/BinarySearchTreeTests.h", 559, __PRETTY_FUNCTION__))
                                ;
        CreatedArray = Instance->ToArray(count);
        
       ((
       count==14
       ) ? static_cast<void> (0) : __assert_fail (
       "count==14"
       , "Tests/BinarySearchTreeTests.h", 561, __PRETTY_FUNCTION__))
                        ;
        for (int a = 0; a < count; a++)
            
           ((
           CreatedArray[a].Key == AfterSorted[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Key == AfterSorted[a]"
           , "Tests/BinarySearchTreeTests.h", 563, __PRETTY_FUNCTION__))
                                                        ;
        delete Instance;
        free(CreatedArray);
    }

    static void GetAndDeleteTests()
    {
        BinarySearchTree<CustomClass> *Instance = NULL;
        int count;
        CustomClass BaseArrayThrteen[13] = {{30, 1},
                                            {10, 2},
                                            {5, 3},
                                            {15, 4},
                                            {3, 5},
                                            {7, 6},
                                            {18, 7},
                                            {1, 8},
                                            {4, 9},
                                            {6, 10},
                                            {8, 11},
                                            {17, 12},
                                            {20, 13}};
        CustomClass ToDelete;
        CustomClass ToGet;
        CustomClass *CreatedArray;
        int DeleteLeafTestBase[13] = {30, 10, 5, 15, 3, 7, 18, 1, 4, 6, 8, 17, 20};
        int DeleteLeafTestResult[12] = {1, 3, 4, 5, 6, 7, 8, 10, 15, 17, 18, 30};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        
       ((
       Instance->Insert(BaseArrayThrteen, 13) == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(BaseArrayThrteen, 13) == 13"
       , "Tests/BinarySearchTreeTests.h", 604, __PRETTY_FUNCTION__))
                                                           ;
        
       ((
       Instance->Size() == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 13"
       , "Tests/BinarySearchTreeTests.h", 605, __PRETTY_FUNCTION__))
                                     ;
        ToDelete.Key = 20;
        
       ((
       Instance->GetAndDelete(ToDelete, ToGet) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetAndDelete(ToDelete, ToGet) == 1"
       , "Tests/BinarySearchTreeTests.h", 607, __PRETTY_FUNCTION__))
                                                           ;
        
       ((
       ToGet.Key == 20
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Key == 20"
       , "Tests/BinarySearchTreeTests.h", 608, __PRETTY_FUNCTION__))
                              ;
        
       ((
       ToGet.Value == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Value == 13"
       , "Tests/BinarySearchTreeTests.h", 609, __PRETTY_FUNCTION__))
                                ;
        
       ((
       Instance->Size() == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 12"
       , "Tests/BinarySearchTreeTests.h", 610, __PRETTY_FUNCTION__))
                                     ;
        CreatedArray = Instance->ToArray(count);
        
       ((
       count == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 12"
       , "Tests/BinarySearchTreeTests.h", 612, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
        {
            
           ((
           CreatedArray[a].Key == DeleteLeafTestResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Key == DeleteLeafTestResult[a]"
           , "Tests/BinarySearchTreeTests.h", 615, __PRETTY_FUNCTION__))
                                                                 ;
            int RealValue = -2;
            for (int b = 0; b < 13; b++)
                if (DeleteLeafTestBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            
           ((
           CreatedArray[a].Value == RealValue + 1
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Value == RealValue + 1"
           , "Tests/BinarySearchTreeTests.h", 620, __PRETTY_FUNCTION__))
                                                         ;
        }
        delete Instance;
        free(CreatedArray);
        int DeleteLeftChildrenNullBase[13] = {30, 10, 5, 15, 3, 7, 18, 1, 4, 6, 8, 17, 20};
        int DeleteLeftChildrenNullResult[12] = {1, 3, 4, 5, 6, 7, 8, 10, 17, 18, 20, 30};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        for (int a = 0; a < 13; a++)
            Instance->Insert(BaseArrayThrteen[a]);
        
       ((
       Instance->Size() == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 13"
       , "Tests/BinarySearchTreeTests.h", 642, __PRETTY_FUNCTION__))
                                     ;
        ToDelete.Key = 15;
        
       ((
       Instance->GetAndDelete(ToDelete, ToGet) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetAndDelete(ToDelete, ToGet) == 1"
       , "Tests/BinarySearchTreeTests.h", 644, __PRETTY_FUNCTION__))
                                                           ;
        
       ((
       Instance->Size() == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 12"
       , "Tests/BinarySearchTreeTests.h", 645, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       ToGet.Key == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Key == 15"
       , "Tests/BinarySearchTreeTests.h", 646, __PRETTY_FUNCTION__))
                              ;
        
       ((
       ToGet.Value == 4
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Value == 4"
       , "Tests/BinarySearchTreeTests.h", 647, __PRETTY_FUNCTION__))
                               ;
        CreatedArray = Instance->ToArray(count);
        
       ((
       count == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 12"
       , "Tests/BinarySearchTreeTests.h", 649, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
        {
            
           ((
           CreatedArray[a].Key == DeleteLeftChildrenNullResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Key == DeleteLeftChildrenNullResult[a]"
           , "Tests/BinarySearchTreeTests.h", 652, __PRETTY_FUNCTION__))
                                                                         ;
            int RealValue = -2;
            for (int b = 0; b < 13; b++)
                if (DeleteLeftChildrenNullBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            
           ((
           CreatedArray[a].Value == RealValue + 1
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Value == RealValue + 1"
           , "Tests/BinarySearchTreeTests.h", 657, __PRETTY_FUNCTION__))
                                                         ;
        }
        delete Instance;
        free(CreatedArray);
        CustomClass BaseFifteen[15] = {{90, 0},
                                       {50, 1},
                                       {95, 2},
                                       {30, 3},
                                       {60, 4},
                                       {15, 5},
                                       {40, 6},
                                       {65, 7},
                                       {10, 8},
                                       {41, 9},
                                       {62, 10},
                                       {67, 11},
                                       {5, 12},
                                       {12, 13},
                                       {42, 14}};
        int DeleteRightChildrenNullBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        int DeleteRightChildrenNullResult[14] = {5, 10, 12, 30, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        
       ((
       Instance->Insert(BaseFifteen, 15) == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(BaseFifteen, 15) == 15"
       , "Tests/BinarySearchTreeTests.h", 695, __PRETTY_FUNCTION__))
                                                      ;
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/BinarySearchTreeTests.h", 696, __PRETTY_FUNCTION__))
                                     ;
        ToDelete.Key = 15;
        
       ((
       Instance->GetAndDelete(ToDelete, ToGet) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetAndDelete(ToDelete, ToGet) == 1"
       , "Tests/BinarySearchTreeTests.h", 698, __PRETTY_FUNCTION__))
                                                           ;
        
       ((
       ToGet.Key == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Key == 15"
       , "Tests/BinarySearchTreeTests.h", 699, __PRETTY_FUNCTION__))
                              ;
        
       ((
       ToGet.Value == 5
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Value == 5"
       , "Tests/BinarySearchTreeTests.h", 700, __PRETTY_FUNCTION__))
                               ;
        
       ((
       Instance->Size() == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 14"
       , "Tests/BinarySearchTreeTests.h", 701, __PRETTY_FUNCTION__))
                                     ;
        CreatedArray = Instance->ToArray(count);
        
       ((
       count == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 14"
       , "Tests/BinarySearchTreeTests.h", 703, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
        {
            
           ((
           CreatedArray[a].Key == DeleteRightChildrenNullResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Key == DeleteRightChildrenNullResult[a]"
           , "Tests/BinarySearchTreeTests.h", 706, __PRETTY_FUNCTION__))
                                                                          ;
            int RealValue = -2;
            for (int b = 0; b < 15; b++)
                if (DeleteRightChildrenNullBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            
           ((
           CreatedArray[a].Value == RealValue
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Value == RealValue"
           , "Tests/BinarySearchTreeTests.h", 711, __PRETTY_FUNCTION__))
                                                     ;
        }
        delete Instance;
        free(CreatedArray);
        int LeftRotateTestBase[13] = {30, 10, 5, 15, 3, 7, 18, 1, 4, 6, 8, 17, 20};
        int LeftRotateTestResult[12] = {1, 3, 4, 5, 6, 7, 8, 15, 17, 18, 20, 30};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        
       ((
       Instance->Insert(BaseArrayThrteen, 13)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(BaseArrayThrteen, 13)"
       , "Tests/BinarySearchTreeTests.h", 731, __PRETTY_FUNCTION__))
                                                     ;
        
       ((
       Instance->Size() == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 13"
       , "Tests/BinarySearchTreeTests.h", 732, __PRETTY_FUNCTION__))
                                     ;
        ToDelete.Key = 10;
        
       ((
       Instance->GetAndDelete(ToDelete, ToGet) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetAndDelete(ToDelete, ToGet) == 1"
       , "Tests/BinarySearchTreeTests.h", 734, __PRETTY_FUNCTION__))
                                                           ;
        
       ((
       Instance->Size() == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 12"
       , "Tests/BinarySearchTreeTests.h", 735, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       ToGet.Key == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Key == 10"
       , "Tests/BinarySearchTreeTests.h", 736, __PRETTY_FUNCTION__))
                              ;
        
       ((
       ToGet.Value == 2
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Value == 2"
       , "Tests/BinarySearchTreeTests.h", 737, __PRETTY_FUNCTION__))
                               ;
        CreatedArray = Instance->ToArray(count);
        
       ((
       count == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 12"
       , "Tests/BinarySearchTreeTests.h", 739, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
        {
            
           ((
           CreatedArray[a].Key == LeftRotateTestResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Key == LeftRotateTestResult[a]"
           , "Tests/BinarySearchTreeTests.h", 742, __PRETTY_FUNCTION__))
                                                                 ;
            int RealValue = -2;
            for (int b = 0; b < 13; b++)
                if (LeftRotateTestBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            
           ((
           CreatedArray[a].Value == RealValue + 1
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Value == RealValue + 1"
           , "Tests/BinarySearchTreeTests.h", 747, __PRETTY_FUNCTION__))
                                                         ;
        }
        delete Instance;
        free(CreatedArray);
        int RightRotateTestBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        int RightRotateTestResult[14] = {5, 10, 12, 15, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        
       ((
       Instance->Insert(BaseFifteen, 15) == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(BaseFifteen, 15) == 15"
       , "Tests/BinarySearchTreeTests.h", 770, __PRETTY_FUNCTION__))
                                                      ;
        ToDelete.Key = 30;
        
       ((
       Instance->GetAndDelete(ToDelete, ToGet) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetAndDelete(ToDelete, ToGet) == 1"
       , "Tests/BinarySearchTreeTests.h", 772, __PRETTY_FUNCTION__))
                                                           ;
        
       ((
       ToGet.Key == 30
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Key == 30"
       , "Tests/BinarySearchTreeTests.h", 773, __PRETTY_FUNCTION__))
                              ;
        
       ((
       ToGet.Value == 3
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Value == 3"
       , "Tests/BinarySearchTreeTests.h", 774, __PRETTY_FUNCTION__))
                               ;
        CreatedArray = Instance->ToArray(count);
        
       ((
       count == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 14"
       , "Tests/BinarySearchTreeTests.h", 776, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
        {
            
           ((
           CreatedArray[a].Key == RightRotateTestResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Key == RightRotateTestResult[a]"
           , "Tests/BinarySearchTreeTests.h", 779, __PRETTY_FUNCTION__))
                                                                  ;
            int RealValue = -2;
            for (int b = 0; b < 15; b++)
                if (RightRotateTestBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            
           ((
           CreatedArray[a].Value == RealValue
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Value == RealValue"
           , "Tests/BinarySearchTreeTests.h", 784, __PRETTY_FUNCTION__))
                                                     ;
        }
        delete Instance;
        free(CreatedArray);
        int RotateInTreeBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        int RotateInTreeResult[14] = {5, 10, 12, 30, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        
       ((
       Instance->Insert(BaseFifteen, 15) == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(BaseFifteen, 15) == 15"
       , "Tests/BinarySearchTreeTests.h", 807, __PRETTY_FUNCTION__))
                                                      ;
        ToDelete.Key = 15;
        
       ((
       Instance->GetAndDelete(ToDelete, ToGet) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetAndDelete(ToDelete, ToGet) == 1"
       , "Tests/BinarySearchTreeTests.h", 809, __PRETTY_FUNCTION__))
                                                           ;
        
       ((
       ToGet.Key == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Key == 15"
       , "Tests/BinarySearchTreeTests.h", 810, __PRETTY_FUNCTION__))
                              ;
        
       ((
       ToGet.Value == 5
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Value == 5"
       , "Tests/BinarySearchTreeTests.h", 811, __PRETTY_FUNCTION__))
                               ;
        CreatedArray = Instance->ToArray(count);
        
       ((
       count == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 14"
       , "Tests/BinarySearchTreeTests.h", 813, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
        {
            
           ((
           CreatedArray[a].Key == RotateInTreeResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Key == RotateInTreeResult[a]"
           , "Tests/BinarySearchTreeTests.h", 816, __PRETTY_FUNCTION__))
                                                               ;
            int RealValue = -2;
            for (int b = 0; b < 15; b++)
                if (RotateInTreeBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            
           ((
           CreatedArray[a].Value == RealValue
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Value == RealValue"
           , "Tests/BinarySearchTreeTests.h", 821, __PRETTY_FUNCTION__))
                                                     ;
        }
        delete Instance;
        free(CreatedArray);
        CustomClass FullTree[15] = {{50, 0},
                                    {20, 1},
                                    {70, 2},
                                    {10, 3},
                                    {30, 4},
                                    {60, 5},
                                    {80, 6},
                                    {5, 7},
                                    {15, 8},
                                    {25, 9},
                                    {35, 10},
                                    {55, 11},
                                    {65, 12},
                                    {75, 13},
                                    {85, 14}};
        int DeletInTreeFirstBase[15] = {50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 35, 55, 65, 75, 85};
        int DeletInTreeFirstResult[14] = {5, 10, 15, 20, 25, 30, 35, 50, 55, 60, 65, 75, 80, 85};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        
       ((
       Instance->Insert(FullTree, 15) == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(FullTree, 15) == 15"
       , "Tests/BinarySearchTreeTests.h", 856, __PRETTY_FUNCTION__))
                                                   ;
        ToDelete.Key = 70;
        
       ((
       Instance->GetAndDelete(ToDelete, ToGet) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetAndDelete(ToDelete, ToGet) == 1"
       , "Tests/BinarySearchTreeTests.h", 858, __PRETTY_FUNCTION__))
                                                           ;
        
       ((
       ToGet.Key == 70
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Key == 70"
       , "Tests/BinarySearchTreeTests.h", 859, __PRETTY_FUNCTION__))
                              ;
        
       ((
       ToGet.Value == 2
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Value == 2"
       , "Tests/BinarySearchTreeTests.h", 860, __PRETTY_FUNCTION__))
                               ;
        CreatedArray = Instance->ToArray(count);
        
       ((
       count == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 14"
       , "Tests/BinarySearchTreeTests.h", 862, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
        {
            
           ((
           CreatedArray[a].Key == DeletInTreeFirstResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Key == DeletInTreeFirstResult[a]"
           , "Tests/BinarySearchTreeTests.h", 865, __PRETTY_FUNCTION__))
                                                                   ;
            int RealValue = -2;
            for (int b = 0; b < 15; b++)
                if (DeletInTreeFirstBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            
           ((
           CreatedArray[a].Value == RealValue
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Value == RealValue"
           , "Tests/BinarySearchTreeTests.h", 870, __PRETTY_FUNCTION__))
                                                     ;
        }
        delete Instance;
        free(CreatedArray);
        int DeleRootInTreeBase[15] = {50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 35, 55, 65, 75, 85};
        int DeleRootInTreeResult[14] = {5, 10, 15, 20, 25, 30, 35, 55, 60, 65, 70, 75, 80, 85};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        
       ((
       Instance->Insert(FullTree, 15) == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Insert(FullTree, 15) == 15"
       , "Tests/BinarySearchTreeTests.h", 889, __PRETTY_FUNCTION__))
                                                   ;
        ToDelete.Key = 50;
        
       ((
       Instance->GetAndDelete(ToDelete, ToGet) == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->GetAndDelete(ToDelete, ToGet) == 1"
       , "Tests/BinarySearchTreeTests.h", 891, __PRETTY_FUNCTION__))
                                                           ;
        
       ((
       ToGet.Key == 50
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Key == 50"
       , "Tests/BinarySearchTreeTests.h", 892, __PRETTY_FUNCTION__))
                              ;
        
       ((
       ToGet.Value == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "ToGet.Value == 0"
       , "Tests/BinarySearchTreeTests.h", 893, __PRETTY_FUNCTION__))
                               ;
        CreatedArray = Instance->ToArray(count);
        
       ((
       count == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 14"
       , "Tests/BinarySearchTreeTests.h", 895, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
        {
            
           ((
           CreatedArray[a].Key == DeleRootInTreeResult[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Key == DeleRootInTreeResult[a]"
           , "Tests/BinarySearchTreeTests.h", 898, __PRETTY_FUNCTION__))
                                                                 ;
            int RealValue = -2;
            for (int b = 0; b < 15; b++)
                if (DeleRootInTreeBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            
           ((
           CreatedArray[a].Value == RealValue
           ) ? static_cast<void> (0) : __assert_fail (
           "CreatedArray[a].Value == RealValue"
           , "Tests/BinarySearchTreeTests.h", 903, __PRETTY_FUNCTION__))
                                                     ;
        }
        delete Instance;
        free(CreatedArray);
    }

public:
    static void tests()
    {
        CopyConstructorTest();

        ContainTest();

        ToArrayTest();

        OneElementDeleteTests();

        MultipleDeletion();

        GetTest();

        NotDuplicateTests();

        GetOrCreateIntTests();

        GetAndDeleteTests();

        GetOrCreateCustomClassTests();
    }
};








using namespace Templates;

class ArrayTests
{
    static void CreatingTests()
    {
        Array<int> *Instance = NULL;
        int array[] = {1, 3, 5, 7, 9};

        Instance = new Array<int>();
        
       ((
       Instance->Allocated == Instance->BaseSize
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Allocated == Instance->BaseSize"
       , "Tests/ArrayTests.h", 20, __PRETTY_FUNCTION__))
                                                        ;
        for (int a = 0; a < Instance->BaseSize; a++)
            
           ((
           Instance->Containing[a] == NULL
           ) ? static_cast<void> (0) : __assert_fail (
           "Instance->Containing[a] == NULL"
           , "Tests/ArrayTests.h", 22, __PRETTY_FUNCTION__))
                                                  ;
        delete Instance;

        Instance = new Array<int>(25);
        
       ((
       Instance->Capacity() == 25
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 25"
       , "Tests/ArrayTests.h", 26, __PRETTY_FUNCTION__))
                                         ;
        for (int a = 0; a < 25; a++)
            
           ((
           Instance->Containing[a] == NULL
           ) ? static_cast<void> (0) : __assert_fail (
           "Instance->Containing[a] == NULL"
           , "Tests/ArrayTests.h", 28, __PRETTY_FUNCTION__))
                                                  ;
        delete Instance;

        Instance = new Array<int>(4);
        
       ((
       Instance->Capacity() == 4
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 4"
       , "Tests/ArrayTests.h", 32, __PRETTY_FUNCTION__))
                                        ;
        for (int a = 0; a < 4; a++)
            
           ((
           Instance->Containing[a] == NULL
           ) ? static_cast<void> (0) : __assert_fail (
           "Instance->Containing[a] == NULL"
           , "Tests/ArrayTests.h", 34, __PRETTY_FUNCTION__))
                                                  ;
        delete Instance;

        Instance = new Array<int>(-5);
        
       ((
       Instance->Capacity() == Instance->BaseSize
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == Instance->BaseSize"
       , "Tests/ArrayTests.h", 38, __PRETTY_FUNCTION__))
                                                         ;
        for (int a = 0; a < Instance->BaseSize; a++)
            
           ((
           Instance->Containing[a] == NULL
           ) ? static_cast<void> (0) : __assert_fail (
           "Instance->Containing[a] == NULL"
           , "Tests/ArrayTests.h", 40, __PRETTY_FUNCTION__))
                                                  ;
        delete Instance;

        Instance = new Array<int>(1584);
        
       ((
       Instance->Capacity() == 1584
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 1584"
       , "Tests/ArrayTests.h", 44, __PRETTY_FUNCTION__))
                                           ;
        for (int a = 0; a < 1584; a++)
            
           ((
           Instance->Containing[a] == NULL
           ) ? static_cast<void> (0) : __assert_fail (
           "Instance->Containing[a] == NULL"
           , "Tests/ArrayTests.h", 46, __PRETTY_FUNCTION__))
                                                  ;
        delete Instance;

        Instance = new Array<int>(array, 5);
        
       ((
       Instance->Capacity() == 5
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 5"
       , "Tests/ArrayTests.h", 50, __PRETTY_FUNCTION__))
                                        ;
        for (int a = 0; a < 5; a++)
            
           ((
           *Instance->Containing[a] == array[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*Instance->Containing[a] == array[a]"
           , "Tests/ArrayTests.h", 52, __PRETTY_FUNCTION__))
                                                       ;
        delete Instance;
    }

    static void ToArrayTests()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;
        int *array;
        int **writablearray;
        int count;

        Instance = new Array<int>(OriginalArray, 15);
        array = Instance->ToArray(count);
        
       ((
       count == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 15"
       , "Tests/ArrayTests.h", 66, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
            
           ((
           OriginalArray[a] == array[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "OriginalArray[a] == array[a]"
           , "Tests/ArrayTests.h", 68, __PRETTY_FUNCTION__))
                                               ;
        free(array);
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        writablearray = Instance->ToWriteArray(count);
        
       ((
       count == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 15"
       , "Tests/ArrayTests.h", 74, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
            *(writablearray[a]) = a;
        array = Instance->ToArray(count);
        
       ((
       count == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "count == 15"
       , "Tests/ArrayTests.h", 78, __PRETTY_FUNCTION__))
                          ;
        for (int a = 0; a < count; a++)
            
           ((
           array[a] == a
           ) ? static_cast<void> (0) : __assert_fail (
           "array[a] == a"
           , "Tests/ArrayTests.h", 80, __PRETTY_FUNCTION__))
                                ;
        free(array);
        free(writablearray);
        delete Instance;

    }

    static void DeleteTests()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;

        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->Delete() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete() == 15"
       , "Tests/ArrayTests.h", 93, __PRETTY_FUNCTION__))
                                       ;
        
       ((
       Instance->Size() == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 0"
       , "Tests/ArrayTests.h", 94, __PRETTY_FUNCTION__))
                                    ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->Delete(15) == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(15) == 15"
       , "Tests/ArrayTests.h", 98, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 0"
       , "Tests/ArrayTests.h", 99, __PRETTY_FUNCTION__))
                                    ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->Delete(5) == 5
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(5) == 5"
       , "Tests/ArrayTests.h", 103, __PRETTY_FUNCTION__))
                                       ;
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/ArrayTests.h", 104, __PRETTY_FUNCTION__))
                                     ;
        for (int a = 0; a < Instance->Size(); a++) 
                                                  ((
                                                  *Instance->Containing[a] == OriginalArray[a + 5]
                                                  ) ? static_cast<void> (0) : __assert_fail (
                                                  "*Instance->Containing[a] == OriginalArray[a + 5]"
                                                  , "Tests/ArrayTests.h", 105, __PRETTY_FUNCTION__))
                                                                                                          ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->Delete(25) == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(25) == 15"
       , "Tests/ArrayTests.h", 109, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 0"
       , "Tests/ArrayTests.h", 110, __PRETTY_FUNCTION__))
                                    ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->Delete(3) == 3
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Delete(3) == 3"
       , "Tests/ArrayTests.h", 114, __PRETTY_FUNCTION__))
                                       ;
        
       ((
       Instance->Size() == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 12"
       , "Tests/ArrayTests.h", 115, __PRETTY_FUNCTION__))
                                     ;
        for (int a = 0; a < Instance->Size(); a++) 
                                                  ((
                                                  *Instance->Containing[a] == OriginalArray[a + 3]
                                                  ) ? static_cast<void> (0) : __assert_fail (
                                                  "*Instance->Containing[a] == OriginalArray[a + 3]"
                                                  , "Tests/ArrayTests.h", 116, __PRETTY_FUNCTION__))
                                                                                                          ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->DeleteFromEnd(3) == 3
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->DeleteFromEnd(3) == 3"
       , "Tests/ArrayTests.h", 120, __PRETTY_FUNCTION__))
                                              ;
        
       ((
       Instance->Size() == 12
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 12"
       , "Tests/ArrayTests.h", 121, __PRETTY_FUNCTION__))
                                     ;
        for (int a = 0; a < Instance->Size(); a++) 
                                                  ((
                                                  *Instance->Containing[a] == OriginalArray[a]
                                                  ) ? static_cast<void> (0) : __assert_fail (
                                                  "*Instance->Containing[a] == OriginalArray[a]"
                                                  , "Tests/ArrayTests.h", 122, __PRETTY_FUNCTION__))
                                                                                                      ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->DeleteFromEnd(15) == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->DeleteFromEnd(15) == 15"
       , "Tests/ArrayTests.h", 126, __PRETTY_FUNCTION__))
                                                ;
        
       ((
       Instance->Size() == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 0"
       , "Tests/ArrayTests.h", 127, __PRETTY_FUNCTION__))
                                    ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->DeleteFromEnd(20) == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->DeleteFromEnd(20) == 15"
       , "Tests/ArrayTests.h", 131, __PRETTY_FUNCTION__))
                                                ;
        
       ((
       Instance->Size() == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 0"
       , "Tests/ArrayTests.h", 132, __PRETTY_FUNCTION__))
                                    ;
        delete Instance;
    }

    static void ShiftTest1()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;




        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->Capacity() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 15"
       , "Tests/ArrayTests.h", 145, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/ArrayTests.h", 146, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Shift(9, -2)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Shift(9, -2)"
       , "Tests/ArrayTests.h", 147, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Capacity() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 15"
       , "Tests/ArrayTests.h", 148, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 13"
       , "Tests/ArrayTests.h", 149, __PRETTY_FUNCTION__))
                                     ;
        for (int a = 0; a < 7; a++) 
                                   ((
                                   *Instance->Containing[a] == OriginalArray[a]
                                   ) ? static_cast<void> (0) : __assert_fail (
                                   "*Instance->Containing[a] == OriginalArray[a]"
                                   , "Tests/ArrayTests.h", 150, __PRETTY_FUNCTION__))
                                                                                       ;
        for (int a = 7; a < 13; a++) 
                                    ((
                                    *Instance->Containing[a] == OriginalArray[a + 2]
                                    ) ? static_cast<void> (0) : __assert_fail (
                                    "*Instance->Containing[a] == OriginalArray[a + 2]"
                                    , "Tests/ArrayTests.h", 151, __PRETTY_FUNCTION__))
                                                                                            ;
        delete Instance;
    }

    static void ShiftTest2()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;



        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->Capacity() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 15"
       , "Tests/ArrayTests.h", 163, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/ArrayTests.h", 164, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Shift(9, 5)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Shift(9, 5)"
       , "Tests/ArrayTests.h", 165, __PRETTY_FUNCTION__))
                                    ;
        
       ((
       Instance->Capacity() == 20
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 20"
       , "Tests/ArrayTests.h", 166, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 20
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 20"
       , "Tests/ArrayTests.h", 167, __PRETTY_FUNCTION__))
                                     ;
        for (int a = 0; a < 9; a++) 
                                   ((
                                   *Instance->Containing[a] == OriginalArray[a]
                                   ) ? static_cast<void> (0) : __assert_fail (
                                   "*Instance->Containing[a] == OriginalArray[a]"
                                   , "Tests/ArrayTests.h", 168, __PRETTY_FUNCTION__))
                                                                                       ;
        for (int a = 9; a < 14; a++) 
                                    ((
                                    Instance->Containing[a] == NULL
                                    ) ? static_cast<void> (0) : __assert_fail (
                                    "Instance->Containing[a] == NULL"
                                    , "Tests/ArrayTests.h", 169, __PRETTY_FUNCTION__))
                                                                           ;
        for (int a = 14; a < 20; a++) 
                                     ((
                                     *Instance->Containing[a] == OriginalArray[a - 5]
                                     ) ? static_cast<void> (0) : __assert_fail (
                                     "*Instance->Containing[a] == OriginalArray[a - 5]"
                                     , "Tests/ArrayTests.h", 170, __PRETTY_FUNCTION__))
                                                                                             ;
        delete Instance;
    }

    static void ShiftTest3()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;



        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->Capacity() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 15"
       , "Tests/ArrayTests.h", 182, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/ArrayTests.h", 183, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Shift(9, -20)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Shift(9, -20)"
       , "Tests/ArrayTests.h", 184, __PRETTY_FUNCTION__))
                                      ;
        
       ((
       Instance->Capacity() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 15"
       , "Tests/ArrayTests.h", 185, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 6
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 6"
       , "Tests/ArrayTests.h", 186, __PRETTY_FUNCTION__))
                                    ;
        for (int a = 0; a < 6; a++) 
                                   ((
                                   *Instance->Containing[a] == OriginalArray[a + 9]
                                   ) ? static_cast<void> (0) : __assert_fail (
                                   "*Instance->Containing[a] == OriginalArray[a + 9]"
                                   , "Tests/ArrayTests.h", 187, __PRETTY_FUNCTION__))
                                                                                           ;
        delete Instance;
    }

    static void ShiftTest4()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;



        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->Capacity() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 15"
       , "Tests/ArrayTests.h", 199, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/ArrayTests.h", 200, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Shift(0, 5)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Shift(0, 5)"
       , "Tests/ArrayTests.h", 201, __PRETTY_FUNCTION__))
                                    ;
        
       ((
       Instance->Capacity() == 20
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 20"
       , "Tests/ArrayTests.h", 202, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 20
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 20"
       , "Tests/ArrayTests.h", 203, __PRETTY_FUNCTION__))
                                     ;
        for (int a = 0; a < 5; a++) 
                                   ((
                                   Instance->Containing[a] == NULL
                                   ) ? static_cast<void> (0) : __assert_fail (
                                   "Instance->Containing[a] == NULL"
                                   , "Tests/ArrayTests.h", 204, __PRETTY_FUNCTION__))
                                                                          ;
        for (int a = 5; a < 20; a++) 
                                    ((
                                    *Instance->Containing[a] == OriginalArray[a - 5]
                                    ) ? static_cast<void> (0) : __assert_fail (
                                    "*Instance->Containing[a] == OriginalArray[a - 5]"
                                    , "Tests/ArrayTests.h", 205, __PRETTY_FUNCTION__))
                                                                                            ;
        delete Instance;
    }

    static void ShiftTest5()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;



        Instance = new Array<int>(OriginalArray, 15);
        
       ((
       Instance->Capacity() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 15"
       , "Tests/ArrayTests.h", 217, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/ArrayTests.h", 218, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Shift(13, 5)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Shift(13, 5)"
       , "Tests/ArrayTests.h", 219, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Capacity() == 20
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 20"
       , "Tests/ArrayTests.h", 220, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 20
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 20"
       , "Tests/ArrayTests.h", 221, __PRETTY_FUNCTION__))
                                     ;
        for (int a = 0; a < 13; a++) 
                                    ((
                                    *Instance->Containing[a] == OriginalArray[a]
                                    ) ? static_cast<void> (0) : __assert_fail (
                                    "*Instance->Containing[a] == OriginalArray[a]"
                                    , "Tests/ArrayTests.h", 222, __PRETTY_FUNCTION__))
                                                                                        ;
        for (int a = 13; a < 18; a++) 
                                     ((
                                     Instance->Containing[a] == NULL
                                     ) ? static_cast<void> (0) : __assert_fail (
                                     "Instance->Containing[a] == NULL"
                                     , "Tests/ArrayTests.h", 223, __PRETTY_FUNCTION__))
                                                                            ;
        for (int a = 18; a < 20; a++) 
                                     ((
                                     *Instance->Containing[a] == OriginalArray[a - 5]
                                     ) ? static_cast<void> (0) : __assert_fail (
                                     "*Instance->Containing[a] == OriginalArray[a - 5]"
                                     , "Tests/ArrayTests.h", 224, __PRETTY_FUNCTION__))
                                                                                             ;
        delete Instance;
    }

    static void ShiftTests()
    {
        ShiftTest1();
        ShiftTest2();
        ShiftTest3();
        ShiftTest4();
        ShiftTest5();
    }

    static void IteratorsTests()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;
        Array<int>::Iterator iter;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        
       ((
       !iter.Back()
       ) ? static_cast<void> (0) : __assert_fail (
       "!iter.Back()"
       , "Tests/ArrayTests.h", 245, __PRETTY_FUNCTION__))
                           ;
        for (int a = 0; a < 15; a++)
        {
            
           ((
           *iter.GetValue() == OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue() == OriginalArray[a]"
           , "Tests/ArrayTests.h", 248, __PRETTY_FUNCTION__))
                                                       ;
            
           ((
           iter.Next()
           ) ? static_cast<void> (0) : __assert_fail (
           "iter.Next()"
           , "Tests/ArrayTests.h", 249, __PRETTY_FUNCTION__))
                              ;
        }
        
       ((
       !iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "!iter.Next()"
       , "Tests/ArrayTests.h", 251, __PRETTY_FUNCTION__))
                           ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        
       ((
       !iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "!iter.Next()"
       , "Tests/ArrayTests.h", 256, __PRETTY_FUNCTION__))
                           ;
        for (int a = 14; a >= 0; a--)
        {
            
           ((
           iter.Back()
           ) ? static_cast<void> (0) : __assert_fail (
           "iter.Back()"
           , "Tests/ArrayTests.h", 259, __PRETTY_FUNCTION__))
                              ;
            
           ((
           *iter.GetValue() == OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue() == OriginalArray[a]"
           , "Tests/ArrayTests.h", 260, __PRETTY_FUNCTION__))
                                                       ;
        }
        
       ((
       !iter.Back()
       ) ? static_cast<void> (0) : __assert_fail (
       "!iter.Back()"
       , "Tests/ArrayTests.h", 262, __PRETTY_FUNCTION__))
                           ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->At(5);
        for (int a = 5; a < 15; a++)
        {
            
           ((
           *iter.GetValue() == OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue() == OriginalArray[a]"
           , "Tests/ArrayTests.h", 269, __PRETTY_FUNCTION__))
                                                       ;
            
           ((
           iter.Next()
           ) ? static_cast<void> (0) : __assert_fail (
           "iter.Next()"
           , "Tests/ArrayTests.h", 270, __PRETTY_FUNCTION__))
                              ;
        }
        
       ((
       iter.JumpToBegin()
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.JumpToBegin()"
       , "Tests/ArrayTests.h", 272, __PRETTY_FUNCTION__))
                                 ;
        for (int a = 0; a < 15; a++)
        {
            
           ((
           *iter.GetValue() == OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue() == OriginalArray[a]"
           , "Tests/ArrayTests.h", 275, __PRETTY_FUNCTION__))
                                                       ;
            
           ((
           iter.Next()
           ) ? static_cast<void> (0) : __assert_fail (
           "iter.Next()"
           , "Tests/ArrayTests.h", 276, __PRETTY_FUNCTION__))
                              ;
        }
        
       ((
       !iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "!iter.Next()"
       , "Tests/ArrayTests.h", 278, __PRETTY_FUNCTION__))
                           ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        
       ((
       iter.Next(5)
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next(5)"
       , "Tests/ArrayTests.h", 283, __PRETTY_FUNCTION__))
                           ;
        for (int a = 5; a < 15; a++)
        {
            
           ((
           *iter.GetValue() == OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue() == OriginalArray[a]"
           , "Tests/ArrayTests.h", 286, __PRETTY_FUNCTION__))
                                                       ;
            
           ((
           iter.Next()
           ) ? static_cast<void> (0) : __assert_fail (
           "iter.Next()"
           , "Tests/ArrayTests.h", 287, __PRETTY_FUNCTION__))
                              ;
        }
        
       ((
       !iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "!iter.Next()"
       , "Tests/ArrayTests.h", 289, __PRETTY_FUNCTION__))
                           ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        
       ((
       !iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "!iter.Next()"
       , "Tests/ArrayTests.h", 294, __PRETTY_FUNCTION__))
                           ;
        
       ((
       iter.Back(4)
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Back(4)"
       , "Tests/ArrayTests.h", 295, __PRETTY_FUNCTION__))
                           ;
        for (int a = 10; a >= 0; a--)
        {
            
           ((
           iter.Back()
           ) ? static_cast<void> (0) : __assert_fail (
           "iter.Back()"
           , "Tests/ArrayTests.h", 298, __PRETTY_FUNCTION__))
                              ;
            
           ((
           *iter.GetValue() == OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue() == OriginalArray[a]"
           , "Tests/ArrayTests.h", 299, __PRETTY_FUNCTION__))
                                                       ;
        }
        
       ((
       !iter.Back()
       ) ? static_cast<void> (0) : __assert_fail (
       "!iter.Back()"
       , "Tests/ArrayTests.h", 301, __PRETTY_FUNCTION__))
                           ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        
       ((
       !iter.Next(25)
       ) ? static_cast<void> (0) : __assert_fail (
       "!iter.Next(25)"
       , "Tests/ArrayTests.h", 306, __PRETTY_FUNCTION__))
                             ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        
       ((
       !iter.Back(24)
       ) ? static_cast<void> (0) : __assert_fail (
       "!iter.Back(24)"
       , "Tests/ArrayTests.h", 311, __PRETTY_FUNCTION__))
                             ;
        delete Instance;
    }

    static void IteratorsDelete()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;
        Array<int>::Iterator iter;




        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        
       ((
       iter.DeleteThis() == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.DeleteThis() == 1"
       , "Tests/ArrayTests.h", 326, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       *iter.GetValue() == 3
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue() == 3"
       , "Tests/ArrayTests.h", 327, __PRETTY_FUNCTION__))
                                    ;
        
       ((
       Instance->Size() == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 14"
       , "Tests/ArrayTests.h", 328, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Capacity() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 15"
       , "Tests/ArrayTests.h", 329, __PRETTY_FUNCTION__))
                                         ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        
       ((
       iter.DeleteThis() == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.DeleteThis() == 0"
       , "Tests/ArrayTests.h", 334, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       iter.GetValue() == NULL
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.GetValue() == NULL"
       , "Tests/ArrayTests.h", 335, __PRETTY_FUNCTION__))
                                      ;
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/ArrayTests.h", 336, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Capacity() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 15"
       , "Tests/ArrayTests.h", 337, __PRETTY_FUNCTION__))
                                         ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->At(5);
        
       ((
       iter.DeleteThis() == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.DeleteThis() == 1"
       , "Tests/ArrayTests.h", 342, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       *iter.GetValue() == 13
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue() == 13"
       , "Tests/ArrayTests.h", 343, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Size() == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 14"
       , "Tests/ArrayTests.h", 344, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       Instance->Capacity() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Capacity() == 15"
       , "Tests/ArrayTests.h", 345, __PRETTY_FUNCTION__))
                                         ;
        delete Instance;




        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        
       ((
       iter.DeleteBefore(5) == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.DeleteBefore(5) == 0"
       , "Tests/ArrayTests.h", 353, __PRETTY_FUNCTION__))
                                        ;
        
       ((
       *iter.GetValue() == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue() == 1"
       , "Tests/ArrayTests.h", 354, __PRETTY_FUNCTION__))
                                    ;
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/ArrayTests.h", 355, __PRETTY_FUNCTION__))
                                     ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->At(5);
        
       ((
       iter.DeleteBefore(10) == 5
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.DeleteBefore(10) == 5"
       , "Tests/ArrayTests.h", 360, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/ArrayTests.h", 361, __PRETTY_FUNCTION__))
                                     ;
        iter = Instance->Begin();
        for (int a = 5; a < 15; a++)
        {
            
           ((
           *iter.GetValue() == OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue() == OriginalArray[a]"
           , "Tests/ArrayTests.h", 365, __PRETTY_FUNCTION__))
                                                       ;
            
           ((
           iter.Next()
           ) ? static_cast<void> (0) : __assert_fail (
           "iter.Next()"
           , "Tests/ArrayTests.h", 366, __PRETTY_FUNCTION__))
                              ;
        }
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        
       ((
       iter.DeleteBefore(5) == 5
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.DeleteBefore(5) == 5"
       , "Tests/ArrayTests.h", 372, __PRETTY_FUNCTION__))
                                        ;
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/ArrayTests.h", 373, __PRETTY_FUNCTION__))
                                     ;
        iter = Instance->Begin();
        for (int a = 0; a < 10; a++)
        {
            
           ((
           *iter.GetValue() == OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue() == OriginalArray[a]"
           , "Tests/ArrayTests.h", 377, __PRETTY_FUNCTION__))
                                                       ;
            
           ((
           iter.Next()
           ) ? static_cast<void> (0) : __assert_fail (
           "iter.Next()"
           , "Tests/ArrayTests.h", 378, __PRETTY_FUNCTION__))
                              ;
        }
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        
       ((
       iter.DeleteBefore(25) == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.DeleteBefore(25) == 15"
       , "Tests/ArrayTests.h", 384, __PRETTY_FUNCTION__))
                                          ;
        
       ((
       Instance->Size() == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 0"
       , "Tests/ArrayTests.h", 385, __PRETTY_FUNCTION__))
                                    ;
        delete Instance;




        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        
       ((
       iter.DeleteAfter(5) == 5
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.DeleteAfter(5) == 5"
       , "Tests/ArrayTests.h", 393, __PRETTY_FUNCTION__))
                                       ;
        
       ((
       *iter.GetValue() == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue() == 1"
       , "Tests/ArrayTests.h", 394, __PRETTY_FUNCTION__))
                                    ;
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/ArrayTests.h", 395, __PRETTY_FUNCTION__))
                                     ;
        
       ((
       iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next()"
       , "Tests/ArrayTests.h", 396, __PRETTY_FUNCTION__))
                          ;
        for (int a = 6; a < 10; a++)
        {
            
           ((
           *iter.GetValue() == OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue() == OriginalArray[a]"
           , "Tests/ArrayTests.h", 399, __PRETTY_FUNCTION__))
                                                       ;
            
           ((
           iter.Next()
           ) ? static_cast<void> (0) : __assert_fail (
           "iter.Next()"
           , "Tests/ArrayTests.h", 400, __PRETTY_FUNCTION__))
                              ;
        }
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        
       ((
       iter.DeleteAfter(5) == 0
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.DeleteAfter(5) == 0"
       , "Tests/ArrayTests.h", 406, __PRETTY_FUNCTION__))
                                       ;
        
       ((
       iter.GetValue() == NULL
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.GetValue() == NULL"
       , "Tests/ArrayTests.h", 407, __PRETTY_FUNCTION__))
                                      ;
        
       ((
       Instance->Size() == 15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 15"
       , "Tests/ArrayTests.h", 408, __PRETTY_FUNCTION__))
                                     ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        
       ((
       iter.DeleteAfter(25) == 14
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.DeleteAfter(25) == 14"
       , "Tests/ArrayTests.h", 413, __PRETTY_FUNCTION__))
                                         ;
        
       ((
       *iter.GetValue() == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue() == 1"
       , "Tests/ArrayTests.h", 414, __PRETTY_FUNCTION__))
                                    ;
        
       ((
       Instance->Size() == 1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 1"
       , "Tests/ArrayTests.h", 415, __PRETTY_FUNCTION__))
                                    ;
        
       ((
       iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next()"
       , "Tests/ArrayTests.h", 416, __PRETTY_FUNCTION__))
                          ;
        
       ((
       !iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "!iter.Next()"
       , "Tests/ArrayTests.h", 417, __PRETTY_FUNCTION__))
                           ;
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->At(5);
        
       ((
       iter.DeleteAfter(5) == 5
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.DeleteAfter(5) == 5"
       , "Tests/ArrayTests.h", 422, __PRETTY_FUNCTION__))
                                       ;
        
       ((
       Instance->Size() == 10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 10"
       , "Tests/ArrayTests.h", 423, __PRETTY_FUNCTION__))
                                     ;
        iter = Instance->Begin();
        for (int a = 0; a < 6; a++)
        {
            
           ((
           *iter.GetValue() == OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue() == OriginalArray[a]"
           , "Tests/ArrayTests.h", 427, __PRETTY_FUNCTION__))
                                                       ;
            
           ((
           iter.Next()
           ) ? static_cast<void> (0) : __assert_fail (
           "iter.Next()"
           , "Tests/ArrayTests.h", 428, __PRETTY_FUNCTION__))
                              ;
        }
        for (int a = 11; a < 15; a++)
        {
            
           ((
           *iter.GetValue() == OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue() == OriginalArray[a]"
           , "Tests/ArrayTests.h", 432, __PRETTY_FUNCTION__))
                                                       ;
            
           ((
           iter.Next()
           ) ? static_cast<void> (0) : __assert_fail (
           "iter.Next()"
           , "Tests/ArrayTests.h", 433, __PRETTY_FUNCTION__))
                              ;
        }
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->At(5);
        
       ((
       iter.DeleteAfter(25) == 9
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.DeleteAfter(25) == 9"
       , "Tests/ArrayTests.h", 439, __PRETTY_FUNCTION__))
                                        ;
        
       ((
       Instance->Size() == 6
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size() == 6"
       , "Tests/ArrayTests.h", 440, __PRETTY_FUNCTION__))
                                    ;
        iter = Instance->Begin();
        for (int a = 0; a < 6; a++)
        {
            
           ((
           *iter.GetValue() == OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue() == OriginalArray[a]"
           , "Tests/ArrayTests.h", 444, __PRETTY_FUNCTION__))
                                                       ;
            
           ((
           iter.Next()
           ) ? static_cast<void> (0) : __assert_fail (
           "iter.Next()"
           , "Tests/ArrayTests.h", 445, __PRETTY_FUNCTION__))
                              ;
        }
        delete Instance;
    }

    static void PushTests()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;
        Array<int>::Iterator iter;

        Instance=new Array<int>(OriginalArray,15);
        
       ((
       Instance->Push(31)==1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Push(31)==1"
       , "Tests/ArrayTests.h", 457, __PRETTY_FUNCTION__))
                                    ;
        
       ((
       Instance->Size()==16
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==16"
       , "Tests/ArrayTests.h", 458, __PRETTY_FUNCTION__))
                                   ;
        iter = Instance->Begin();
        for(int a=0;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 461, __PRETTY_FUNCTION__))
                                                     ;
        
       ((
       *iter.GetValue()==31
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue()==31"
       , "Tests/ArrayTests.h", 462, __PRETTY_FUNCTION__))
                                   ;
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        
       ((
       Instance->Push(35)==1
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Push(35)==1"
       , "Tests/ArrayTests.h", 466, __PRETTY_FUNCTION__))
                                    ;
        
       ((
       Instance->Size()==16
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==16"
       , "Tests/ArrayTests.h", 467, __PRETTY_FUNCTION__))
                                   ;
        iter = Instance->Begin();
        for(int a=0;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 470, __PRETTY_FUNCTION__))
                                                     ;
        
       ((
       *iter.GetValue()==35
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue()==35"
       , "Tests/ArrayTests.h", 471, __PRETTY_FUNCTION__))
                                   ;
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        
       ((
       Instance->Push(OriginalArray,10)==10
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Push(OriginalArray,10)==10"
       , "Tests/ArrayTests.h", 475, __PRETTY_FUNCTION__))
                                                   ;
        
       ((
       Instance->Size()==25
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==25"
       , "Tests/ArrayTests.h", 476, __PRETTY_FUNCTION__))
                                   ;
        iter = Instance->Begin();
        for(int a=0;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 479, __PRETTY_FUNCTION__))
                                                     ;
        for(int a=0;a<10;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 481, __PRETTY_FUNCTION__))
                                                     ;
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        
       ((
       Instance->Push(OriginalArray,15)==15
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Push(OriginalArray,15)==15"
       , "Tests/ArrayTests.h", 485, __PRETTY_FUNCTION__))
                                                   ;
        
       ((
       Instance->Size()==30
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==30"
       , "Tests/ArrayTests.h", 486, __PRETTY_FUNCTION__))
                                   ;
        iter = Instance->Begin();
        for(int a=0;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 489, __PRETTY_FUNCTION__))
                                                     ;
        for(int a=0;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 491, __PRETTY_FUNCTION__))
                                                     ;
        delete Instance;
    }

    static void IteratorsInsertTests()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;
        Array<int>::Iterator iter;




        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        
       ((
       iter.Insert(15)==1
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Insert(15)==1"
       , "Tests/ArrayTests.h", 506, __PRETTY_FUNCTION__))
                                 ;
        
       ((
       Instance->Size()==16
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==16"
       , "Tests/ArrayTests.h", 507, __PRETTY_FUNCTION__))
                                   ;
        
       ((
       *iter.GetValue()==1
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue()==1"
       , "Tests/ArrayTests.h", 508, __PRETTY_FUNCTION__))
                                  ;
        
       ((
       iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next()"
       , "Tests/ArrayTests.h", 509, __PRETTY_FUNCTION__))
                          ;
        
       ((
       *iter.GetValue()==15
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue()==15"
       , "Tests/ArrayTests.h", 510, __PRETTY_FUNCTION__))
                                   ;
        
       ((
       iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next()"
       , "Tests/ArrayTests.h", 511, __PRETTY_FUNCTION__))
                          ;
        
       ((
       *iter.GetValue()==3
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue()==3"
       , "Tests/ArrayTests.h", 512, __PRETTY_FUNCTION__))
                                  ;
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        
       ((
       iter.Next(5)
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next(5)"
       , "Tests/ArrayTests.h", 517, __PRETTY_FUNCTION__))
                           ;
        
       ((
       iter.Insert(66)==1
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Insert(66)==1"
       , "Tests/ArrayTests.h", 518, __PRETTY_FUNCTION__))
                                 ;
        
       ((
       Instance->Size()==16
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==16"
       , "Tests/ArrayTests.h", 519, __PRETTY_FUNCTION__))
                                   ;
        iter=Instance->Begin();
        for(int a=0;a<6;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 522, __PRETTY_FUNCTION__))
                                                     ;
        
       ((
       *iter.GetValue()==66
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue()==66"
       , "Tests/ArrayTests.h", 523, __PRETTY_FUNCTION__))
                                   ;
        
       ((
       iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next()"
       , "Tests/ArrayTests.h", 524, __PRETTY_FUNCTION__))
                          ;
        for(int a=6;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 526, __PRETTY_FUNCTION__))
                                                     ;
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->End();
        
       ((
       iter.Insert(15)==0
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Insert(15)==0"
       , "Tests/ArrayTests.h", 531, __PRETTY_FUNCTION__))
                                 ;
        delete Instance;




        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        
       ((
       iter.Insert(OriginalArray,5)==5
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Insert(OriginalArray,5)==5"
       , "Tests/ArrayTests.h", 539, __PRETTY_FUNCTION__))
                                              ;
        
       ((
       Instance->Size()==20
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==20"
       , "Tests/ArrayTests.h", 540, __PRETTY_FUNCTION__))
                                   ;
        
       ((
       *iter.GetValue()==1
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue()==1"
       , "Tests/ArrayTests.h", 541, __PRETTY_FUNCTION__))
                                  ;
        
       ((
       iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next()"
       , "Tests/ArrayTests.h", 542, __PRETTY_FUNCTION__))
                          ;
        for(int a=0;a<5;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 544, __PRETTY_FUNCTION__))
                                                     ;
        for(int a=1;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 546, __PRETTY_FUNCTION__))
                                                     ;
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        
       ((
       iter.Next(5)
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next(5)"
       , "Tests/ArrayTests.h", 551, __PRETTY_FUNCTION__))
                           ;
        
       ((
       iter.Insert(OriginalArray,5)==5
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Insert(OriginalArray,5)==5"
       , "Tests/ArrayTests.h", 552, __PRETTY_FUNCTION__))
                                              ;
        
       ((
       Instance->Size()==20
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==20"
       , "Tests/ArrayTests.h", 553, __PRETTY_FUNCTION__))
                                   ;
        iter = Instance->Begin();
        for(int a=0;a<6;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 556, __PRETTY_FUNCTION__))
                                                     ;
        for(int a=0;a<5;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 558, __PRETTY_FUNCTION__))
                                                     ;
        for(int a=6;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 560, __PRETTY_FUNCTION__))
                                                     ;
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->End();
        
       ((
       iter.Insert(OriginalArray,5)==0
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Insert(OriginalArray,5)==0"
       , "Tests/ArrayTests.h", 565, __PRETTY_FUNCTION__))
                                              ;
        delete Instance;




        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        
       ((
       iter.InsertBefore(15)==1
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.InsertBefore(15)==1"
       , "Tests/ArrayTests.h", 573, __PRETTY_FUNCTION__))
                                       ;
        
       ((
       Instance->Size()==16
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==16"
       , "Tests/ArrayTests.h", 574, __PRETTY_FUNCTION__))
                                   ;
        iter = Instance->Begin();
        
       ((
       *iter.GetValue()==15
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue()==15"
       , "Tests/ArrayTests.h", 576, __PRETTY_FUNCTION__))
                                   ;
        
       ((
       iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next()"
       , "Tests/ArrayTests.h", 577, __PRETTY_FUNCTION__))
                          ;
        for(int a=0;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 579, __PRETTY_FUNCTION__))
                                                     ;
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        
       ((
       iter.Next(5)
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next(5)"
       , "Tests/ArrayTests.h", 584, __PRETTY_FUNCTION__))
                           ;
        
       ((
       iter.InsertBefore(66)==1
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.InsertBefore(66)==1"
       , "Tests/ArrayTests.h", 585, __PRETTY_FUNCTION__))
                                       ;
        
       ((
       Instance->Size()==16
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==16"
       , "Tests/ArrayTests.h", 586, __PRETTY_FUNCTION__))
                                   ;
        iter=Instance->Begin();
        for(int a=0;a<5;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 589, __PRETTY_FUNCTION__))
                                                     ;
        
       ((
       *iter.GetValue()==66
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue()==66"
       , "Tests/ArrayTests.h", 590, __PRETTY_FUNCTION__))
                                   ;
        
       ((
       iter.Next()
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next()"
       , "Tests/ArrayTests.h", 591, __PRETTY_FUNCTION__))
                          ;
        for(int a=5;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 593, __PRETTY_FUNCTION__))
                                                     ;
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->End();
        
       ((
       iter.InsertBefore(66)==1
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.InsertBefore(66)==1"
       , "Tests/ArrayTests.h", 598, __PRETTY_FUNCTION__))
                                       ;
        
       ((
       Instance->Size()==16
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==16"
       , "Tests/ArrayTests.h", 599, __PRETTY_FUNCTION__))
                                   ;
        iter = Instance->Begin();
        for(int a=0;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 602, __PRETTY_FUNCTION__))
                                                     ;
        
       ((
       *iter.GetValue()==66
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue()==66"
       , "Tests/ArrayTests.h", 603, __PRETTY_FUNCTION__))
                                   ;
        delete Instance;





        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        
       ((
       iter.InsertBefore(OriginalArray,5)==5
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.InsertBefore(OriginalArray,5)==5"
       , "Tests/ArrayTests.h", 612, __PRETTY_FUNCTION__))
                                                    ;
        
       ((
       Instance->Size()==20
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==20"
       , "Tests/ArrayTests.h", 613, __PRETTY_FUNCTION__))
                                   ;
        
       ((
       *iter.GetValue()==1
       ) ? static_cast<void> (0) : __assert_fail (
       "*iter.GetValue()==1"
       , "Tests/ArrayTests.h", 614, __PRETTY_FUNCTION__))
                                  ;
        iter=Instance->Begin();
        for(int a=0;a<5;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 617, __PRETTY_FUNCTION__))
                                                     ;
        for(int a=0;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 619, __PRETTY_FUNCTION__))
                                                     ;
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        
       ((
       iter.Next(5)
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.Next(5)"
       , "Tests/ArrayTests.h", 624, __PRETTY_FUNCTION__))
                           ;
        
       ((
       iter.InsertBefore(OriginalArray,5)==5
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.InsertBefore(OriginalArray,5)==5"
       , "Tests/ArrayTests.h", 625, __PRETTY_FUNCTION__))
                                                    ;
        
       ((
       Instance->Size()==20
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==20"
       , "Tests/ArrayTests.h", 626, __PRETTY_FUNCTION__))
                                   ;
        iter = Instance->Begin();
        for(int a=0;a<5;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 629, __PRETTY_FUNCTION__))
                                                     ;
        for(int a=0;a<5;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 631, __PRETTY_FUNCTION__))
                                                     ;
        for(int a=5;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 633, __PRETTY_FUNCTION__))
                                                     ;
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->End();
        
       ((
       iter.InsertBefore(OriginalArray,5)==5
       ) ? static_cast<void> (0) : __assert_fail (
       "iter.InsertBefore(OriginalArray,5)==5"
       , "Tests/ArrayTests.h", 638, __PRETTY_FUNCTION__))
                                                    ;
        
       ((
       Instance->Size()==20
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Size()==20"
       , "Tests/ArrayTests.h", 639, __PRETTY_FUNCTION__))
                                   ;
        iter = Instance->Begin();
        for(int a=0;a<15;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 642, __PRETTY_FUNCTION__))
                                                     ;
        for(int a=0;a<5;a++,iter.Next())
            
           ((
           *iter.GetValue()==OriginalArray[a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*iter.GetValue()==OriginalArray[a]"
           , "Tests/ArrayTests.h", 644, __PRETTY_FUNCTION__))
                                                     ;
        delete Instance;
    }

    static void SwapTests()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;

        Instance = new Array<int>(OriginalArray,15);
        
       ((
       Instance->Swap(0,14)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Swap(0,14)"
       , "Tests/ArrayTests.h", 654, __PRETTY_FUNCTION__))
                                   ;
        
       ((
       Instance->Swap(1,13)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Swap(1,13)"
       , "Tests/ArrayTests.h", 655, __PRETTY_FUNCTION__))
                                   ;
        
       ((
       Instance->Swap(2,12)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Swap(2,12)"
       , "Tests/ArrayTests.h", 656, __PRETTY_FUNCTION__))
                                   ;
        
       ((
       Instance->Swap(3,11)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Swap(3,11)"
       , "Tests/ArrayTests.h", 657, __PRETTY_FUNCTION__))
                                   ;
        
       ((
       Instance->Swap(4,10)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Swap(4,10)"
       , "Tests/ArrayTests.h", 658, __PRETTY_FUNCTION__))
                                   ;
        
       ((
       Instance->Swap(5,9)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Swap(5,9)"
       , "Tests/ArrayTests.h", 659, __PRETTY_FUNCTION__))
                                  ;
        
       ((
       Instance->Swap(6,8)
       ) ? static_cast<void> (0) : __assert_fail (
       "Instance->Swap(6,8)"
       , "Tests/ArrayTests.h", 660, __PRETTY_FUNCTION__))
                                  ;
        for(int a=14;a>=0;a--)
            
           ((
           *Instance->Containing[a]==OriginalArray[14-a]
           ) ? static_cast<void> (0) : __assert_fail (
           "*Instance->Containing[a]==OriginalArray[14-a]"
           , "Tests/ArrayTests.h", 662, __PRETTY_FUNCTION__))
                                                                ;
        delete Instance;
    }

public:
    static void tests()
    {
        CreatingTests();

        ShiftTests();

        ToArrayTests();

        DeleteTests();

        IteratorsTests();

        IteratorsDelete();

        PushTests();

        IteratorsInsertTests();

        SwapTests();
    }
};




using namespace Math;

class IntervalTests
{
private:
    static void Minus()
    {
        Interval<int> Instance(5, 10);
        Interval<int> Before(0, 2);
        Interval<int> After(15, 17);
        Interval<int> In(7, 9);
        Interval<int> Left(4, 6);
        Interval<int> Right(9, 11);

        Interval<int> BeforeMinus = Instance-Before;
        Interval<int> AfterMinus = Instance-After;
        Interval<int> InMinus = Instance-In;
        Interval<int> LeftMinus = Instance-Left;
        Interval<int> RightMinus = Instance-Right;

        
       ((
       BeforeMinus.GetBegin()==5
       ) ? static_cast<void> (0) : __assert_fail (
       "BeforeMinus.GetBegin()==5"
       , "Tests/IntervalTests.h", 26, __PRETTY_FUNCTION__))
                                        ;
        
       ((
       BeforeMinus.GetEnd()==10
       ) ? static_cast<void> (0) : __assert_fail (
       "BeforeMinus.GetEnd()==10"
       , "Tests/IntervalTests.h", 27, __PRETTY_FUNCTION__))
                                       ;

        
       ((
       AfterMinus.GetBegin()==5
       ) ? static_cast<void> (0) : __assert_fail (
       "AfterMinus.GetBegin()==5"
       , "Tests/IntervalTests.h", 29, __PRETTY_FUNCTION__))
                                       ;
        
       ((
       AfterMinus.GetEnd()==10
       ) ? static_cast<void> (0) : __assert_fail (
       "AfterMinus.GetEnd()==10"
       , "Tests/IntervalTests.h", 30, __PRETTY_FUNCTION__))
                                      ;

        
       ((
       InMinus.GetBegin()==5
       ) ? static_cast<void> (0) : __assert_fail (
       "InMinus.GetBegin()==5"
       , "Tests/IntervalTests.h", 32, __PRETTY_FUNCTION__))
                                    ;
        
       ((
       InMinus.GetEnd()==7
       ) ? static_cast<void> (0) : __assert_fail (
       "InMinus.GetEnd()==7"
       , "Tests/IntervalTests.h", 33, __PRETTY_FUNCTION__))
                                  ;

        
       ((
       LeftMinus.GetBegin()==6
       ) ? static_cast<void> (0) : __assert_fail (
       "LeftMinus.GetBegin()==6"
       , "Tests/IntervalTests.h", 35, __PRETTY_FUNCTION__))
                                      ;
        
       ((
       LeftMinus.GetEnd()==10
       ) ? static_cast<void> (0) : __assert_fail (
       "LeftMinus.GetEnd()==10"
       , "Tests/IntervalTests.h", 36, __PRETTY_FUNCTION__))
                                     ;

        
       ((
       RightMinus.GetBegin()==5
       ) ? static_cast<void> (0) : __assert_fail (
       "RightMinus.GetBegin()==5"
       , "Tests/IntervalTests.h", 38, __PRETTY_FUNCTION__))
                                       ;
        
       ((
       RightMinus.GetEnd()==9
       ) ? static_cast<void> (0) : __assert_fail (
       "RightMinus.GetEnd()==9"
       , "Tests/IntervalTests.h", 39, __PRETTY_FUNCTION__))
                                     ;
    }


public:
    static void tests()
    {
        Minus();
    }
};

int main()
{
    IntervalTests::tests();
    VectorTest::test();
    QueueTests::test();
    CondQueueTests::test();
    AlgorithmsTests::test();
    ListTests::test();
    PriorityQueueTests::test();
    StackTests::test();
    ArrayTests::tests();
    BinaryHeapTests::tests();
    BinarySearchTreeTests::tests();

    std::cout << "No errors" << std::endl;

    exit(0);
}
