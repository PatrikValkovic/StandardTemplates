#ifndef TEMPLATES_BASIS_H
#define TEMPLATES_BASIS_H
#include "Meta.h"

//TODO remove
#include <cstring>

namespace Templates
{

    template<typename T>
    inline typename Meta::remove_reference<T>::type&& move(T &param)
    {
        return static_cast<typename Meta::remove_reference<T>::type&&>(param);
    }

    template<typename T, typename ENABLE = void>
    struct __swap_impl {
        static void swap(T& first, T& second){
            static_assert(true, "Need copyable or movable semantic");
        }
    };
    template<typename T>
    struct __swap_impl<T,
            typename Meta::enable_if<
                    Meta::and_<
                            Meta::is_assignable_copy<T>::value,
                            Meta::is_constructible_copyable<T>::value,
                            Meta::not_<
                                    Meta::and_<
                                            Meta::is_assignable_move<T>::value,
                                            Meta::is_constructible_movable<T>::value
                                    >::value
                            >::value
                    >::value
            >::type
    > {
        static void swap(T& first, T& second){
            T temp(first);
            first = second;
            second = temp;
        }
    };
    template<typename T>
    struct __swap_impl<T,
            typename Meta::enable_if<
                    Meta::and_<
                            Meta::is_assignable_move<T>::value,
                            Meta::is_constructible_movable<T>::value
                    >::value
            >::type
    > {
        static void swap(T& first, T& second){
            T temp(move(first));
            first = move(second);
            second = move(temp);
        }
    };
    template<typename T>
    void swap(T& first, T& second){
        if(&first == &second)
            return;
        __swap_impl<T>::swap(first, second);
    }


    template<typename T>
    struct __defaultDeleter{
        static void perform(T* p){
            delete p;
        }
    };
    template<typename T>
    struct __defaultDeleter<T[]>{
        static void perform(T* p){
            delete [] p;
        }
    };

    template<typename T>
    struct __deleterWithoutDestruction{
        static void perform(T* p){
            ::operator delete(p);
        }
    };


	//TODO rename later
	template<typename T=void>
	T* malloc_own(unsigned long int size){
		return (T*)::operator new(sizeof(T) * size);
	}
	template<>
	void* malloc_own<void>(unsigned long int size){
		return ::operator new(size);
	}
	
	template<typename T>
	void free_own(T* ptr)
    {
        ::operator delete((void*) ptr);
    }


    template<typename T>
    const T& max(const T& l, const T& r){
        return l < r ? r : l;
    }


    template<typename T>
    const T& min(const T& l, const T& r){
        return l < r ? l : r;
    }


    template<typename T, typename ENABLE = void>
    struct __fastest_init {
        static void fastest_init(T* where, T& what){
            static_assert(true, "Need copy or move constructor");
        }
    };
    template<typename T>
    struct __fastest_init<T,
            typename Meta::enable_if<Meta::is_constructible_movable<T>::value>::type
    >
    {
        static void fastest_init(T* where, T& what){
            new (where) T(move(what));
        }
    };
    template<typename T>
    struct __fastest_init<T,
            typename Meta::enable_if<
                    Meta::and_<
                            Meta::is_constructible_copyable<T>::value,
                            Meta::not_<Meta::is_constructible_movable<T>::value>::value
                            >::value
                    >::type
    >
    {
        static void fastest_init(T* where, T& what){
            new (where) T(what);
        }
    };
    template<typename T>
    void fastest_init(T* where, T& what){
        __fastest_init<T>::fastest_init(where, what);
    }
}


#endif //TEMPLATES_BASIS_H
