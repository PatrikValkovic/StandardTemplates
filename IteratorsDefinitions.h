#ifndef TEMPLATES_ITERATORSDEFINITIONS_H
#define TEMPLATES_ITERATORSDEFINITIONS_H

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

#endif //TEMPLATES_ITERATORSDEFINITIONS_H
