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
        class BackwardIteratorBase : virtual public IteratorBase<T>
        {
        public:
            virtual bool Back() = 0;
            virtual bool Back(int HowMany) = 0;
        };

        template<typename T>
        class RandomAccessIteratorBase : virtual public BackwardIteratorBase<T>, virtual public ForwardIteratorBase<T>
        {
        public:
            virtual void To(int Position) = 0;
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

    /**
     * Iterator
     * - T& operator*
     * - T* operator->
     * - bool Valid()
     * - T* Raw()
     * - operator T*()
     *
     * ForwardIterator : Iterator
     * - Iterator& operator++
     * - Iterator& operator++(int)
     * - bool Next()
     *
     * BackwardIterator : Iterator
     * - Iterator& operator--
     * - Iterator& operator--(int)
     * - bool Back()
     *
     * RandomAccessIterator: ForwardIterator, BackwardIterator
     * - bool Next(int how_many)
     * - bool Back(int how_many)
     * - void ToBeginning()
     * - void ToEnd()
     * - void To(int position)
     * - compare functions
     *
     * InsertingIterator
     * - bool Insert(T& elem)
     *     insert at current position, next position will be on the inserted value.
     * - bool Insert(T* elems, int count)
     *     insert at current location, next position will be on the first element of the array.
     *
     * BackInsertingIterator
     * - bool InsertBack(T& elem)
     *     Insert element at the previous position, iterator stay at same position.
     * - bool InsertBack(T* elems, int count)
     *     Insert elements before current element, iterator stay at same position.
     *
     * DeletingIterator
     * - Delete()
     *     Delete current item, iterator moves to next element.
     * - Delete(int count)
     *     Delete count elements included current one, iterators move to next not deleted element.
     *
     * BackDeletingIterator
     * - DeleteBack()
     *     Delete element before current element. Iterator stay at the same element.
     * - DeleteBack(int count)
     *     Delete elements before current element. Iterator stay at the same element.
     */
}

#endif //TEMPLATES_ITERATORSDEFINITIONS_H
