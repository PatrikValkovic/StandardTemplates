#ifndef TEMPLATES_SHAREPOINTER_H
#define TEMPLATES_SHAREPOINTER_H

#include "SharedPointer.h"

namespace Templates
{

    template<typename _T, typename DELETER = __defaultDeleter<_T>>
    class SharedPointer
    {
        using T = typename Meta::remove_array<_T>::type;
    private:
        T* _raw;
        int* _numReferences;
    public:
        SharedPointer() noexcept : _raw(nullptr), _numReferences(nullptr)
        {}

        explicit SharedPointer(T* ptr): _raw(ptr), _numReferences(new int(1))
        {
            if(!bool(*this)){
                delete _numReferences;
                _numReferences = nullptr;
            }
        }

        SharedPointer(const SharedPointer& second) : _raw(second._raw), _numReferences(second._numReferences)
        {
            if(_numReferences)
                (*_numReferences)++;
        }

        SharedPointer(SharedPointer&& second) noexcept : SharedPointer()
        {
            using Templates::swap;
            swap(*this, second);
        }

        ~SharedPointer()
        {
            this->Release();
        }

        SharedPointer& operator=(const SharedPointer& second)
        {
            if(this == &second)
                return *this;

            this->Release();
            _raw = second._raw;
            _numReferences = second._numReferences;
            (*_numReferences)++;
            return *this;
        }


        SharedPointer& operator=(SharedPointer&& second) noexcept
        {
            using Templates::swap;
            if (this == &second)
                return *this;

            this->Release();
            swap(this->_raw, second._raw);
            swap(this->_numReferences, second._numReferences);
            return *this;
        }

        T& operator*()
        {
            return *this->Get();
        }

        const T& operator*() const
        {
            return *this->Get();
        }

        T& operator[](int i)
        {
            return this->Get()[i];
        }

        const T& operator[](int i) const
        {
            return this->Get()[i];
        }


        T* operator->() const noexcept
        {
            return Get();
        }

        explicit operator bool() const noexcept
        {
            return this->_raw != nullptr;
        }

        void Release()
        {
            if(!bool(*this))
                return;

            (*_numReferences)--;
            if(*_numReferences == 0)
            {
                DELETER::perform(this->_raw);
                delete _numReferences;
            }
            this->_raw = nullptr;
            this->_numReferences = nullptr;
        }

        T* Get() const noexcept
        {
            return this->_raw;
        }

        T* Raw() const noexcept
        {
            return this->Get();
        }

        void Swap(SharedPointer& second) noexcept
        {
            using Templates::swap;
            swap(this->_raw, second._raw);
            swap(this->_numReferences, second._numReferences);
        }
    };

    template<typename T, typename ...ARGS>
    SharedPointer<T> make_shared(ARGS... args)
    {
        return SharedPointer<T>(new T(args...));
    }

    template<typename T>
    void swap(SharedPointer<T>& first,SharedPointer<T>& second)
    {
        first.Swap(second);
    }

}


#endif //TEMPLATES_SMARTPOINTERS_H
