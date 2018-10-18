#ifndef TEMPLATES_ARRAYITERATOR_H
#define TEMPLATES_ARRAYITERATOR_H

class Iterator
{
private:
    Array* _instance;
    int _index;
public:
    /**
     * Creates new invalid iterator.
     */
    Iterator() : Iterator(nullptr, -1)
    {}

    /**
     * Creates new valid iterator pointed to specific elements in Array.
     */
    Iterator(Array* array, int index) : _instance(array), _index(index)
    {}

    Iterator(const Iterator&) = default;
    Iterator(Iterator&&) = default;

    /**
     * Assignment operator.
     */
    Iterator& operator=(const Iterator&) = default;
    Iterator& operator==(Iterator&&) = default;

    /**
     * Dereference operator.
     */
    T& operator*()
    {
        if(!Valid())
            throw InvalidIteratorException("Array iterator is not valid", __LINE__);

        return _instance[_index];
    }

    /**
     * Dereference operator.
     */
    const T& operator*() const
    {
        if(!Valid())
            throw InvalidIteratorException("Array iterator is not valid", __LINE__);

        return _instance[_index];
    }

    /**
     * Arrow operator.
     */
    T* operator->()
    {
        if(!Valid())
            throw InvalidIteratorException("Array iterator is not valid", __LINE__);

        return &_instance[_index];
    }

    /**
     * Arrow operator.
     */
    const T* operator->() const
    {
        if(!Valid())
            throw InvalidIteratorException("Array iterator is not valid", __LINE__);

        return &_instance[_index];
    }

    /**
     * Return true, if is iterator valid, false otherwise.
     */
    bool Valid() const
    {
        return _index >= 0 && _instance != nullptr && _index < _instance->_inserted;
    }

    /**
     * Equal operator.
     */
    bool operator==(const Iterator& s) const noexcept
    {
        return _instance == s._instance && _index == s._index;
    }

    /**
     * Lower then operator.
     */
    bool operator<(const Iterator& s) const noexcept
    {
        return _index < s._index;
    }

    /**
     * Greater then operator.
     */
    bool operator>(const Iterator& s) const noexcept
    {
        return _index > s._index;
    }

    /**
     * Lower or equal operator.
     */
    bool operator<=(const Iterator& s) const noexcept
    {
        return _index <= s._index;
    }

    /**
     * Greater or equal operator.
     */
    bool operator>=(const Iterator& s) const noexcept
    {
        return _index >= s._index;
    }

    /**
     * Return raw pointer.
     */
    T* Raw() noexcept
    {
        return &_instance[index];
    }

    /**
     * Return raw pointer.
     */
    const T* Raw() const noexcept
    {
        return &_instance[index];
    }

    /**
     * Implicit conversion operator to raw pointer.
     */
    operator T*() const noexcept
    {
        return this->Raw();
    }

    /**
     * Pre-increment operator
     */
    Iterator& operator++()
    {
        _index++;
        return *this;
    }

    /**
     * Post-increment operator
     */
    Iterator operator++(int)
    {
        Iterator tmp(*this);
        (*this)++;
        return tmp;
    }

    /**
     * Pre-decrement operator
     */
    Iterator& operator--()
    {
        _index--;
        return *this;
    }

    /**
     * Post-decrement operator
     * @return
     */
    Iterator operator--(int)
    {
        Iterator tmp(*this);
        (*this)--;
        return tmp;
    }


    /**
     * Move iterator to next element in Array.
     * Return true if can, false otherwise.
     * Can invalidate iterator.
     */
    virtual bool Next() noexcept
    {
        if (_index + 1 < 0 || _index + 1 > _instance->_inserted)
            return false;
        ++(*this);
        return true;
    }

    /**
     * Move iterator to @HowMany-th element after referencing element.
     * Return true if can, false otherwise.
     * Can invalidate iterator.
     * @param how_many How many places to move.
     */
    virtual bool Next(int how_many) noexcept
    {
        if (_index + how_many < 0 || _index + how_many > _instance->_inserted)
            return false;
        _index += how_many;
        return true;
    }

    /**
     * Move iterator to previous element in Array.
     * Return true if can, false otherwise.
     */
    virtual bool Back() noexcept
    {
        if (_index - 1 < 0 || _index - 1 > _instance->_inserted)
            return false;
        --(*this);
        return true;
    }

    /**
     * Move iterator to @HowMany-th element before referencing element
     * Return true if can, false otherwise
     * @param how_many How many places to move.
     */
    virtual bool Back(int how_many) noexcept
    {
        if (_index - how_many < 0 || _index - how_many > _instance->_inserted)
            return false;
        _index -= how_many;
        return true;
    }

    /**
     * Set iterator's position to the beginning of the Array.
     * @return Return true, false if iterator is not valid.
     */
    bool ToBegin()
    {
        if (_instance == nullptr)
            return false;
        _index = 0;
        return true;
    }

    /**
     * Set iterator's position to the end of the Array.
     * @return Return true, false if iterator is not valid.
     */
    bool ToEnd()
    {
        if (_instance == nullptr)
            return false;
        _index = _instance->Size();
        return true;
    }

    //region inserting
    bool Insert(T& elem)
    {
        _instance->Insert(_index, elem);
        return true;
    }

    bool Insert(T* elems, int count)
    {
        _instance->Insert(_index, elems, count);
        return true;
    }

    bool InsertBack(T& elem)
    {

    }

    bool InsertBack(T* elems, int count)
    {

    }
    //endregion

    //region deleting
    bool Delete()
    {
        _instance->Delete(_index, 1);
        return true;
    }
    bool Delete(int count)
    {
        _instance->Delete(_index, 1);
        return true;
    }
    bool DeleteBack()
    {
        --(*this);
        return this->Delete();
    }
    bool DeleteBack(int count)
    {

    }
    //endregion
};

#endif //TEMPLATES_ARRAYITERATOR_H
