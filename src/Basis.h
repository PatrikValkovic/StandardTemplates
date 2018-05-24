#ifndef TEMPLATES_BASIS_H
#define TEMPLATES_BASIS_H

#include <type_traits>
namespace Templates
{
    namespace Meta
    {
        void _void_f(){}

        struct true_type {
            static const bool value = true;
        };
        struct false_type {
            static const bool value = false;
        };

        template<typename T, typename V = void>
        struct are_same : false_type {};
        template<typename T>
        struct are_same<T,T> : true_type {};

        template<typename T>
        struct add_const {
            using type = const T;
        };
        template<typename T>
        struct add_const<const T> {
            using type = const T;
        };

        template<typename T>
        struct as_ref {
            using type = T&;
        };
        template<typename T>
        struct as_ref<T&> {
            using type = T&;
        };
        template<typename T>
        struct as_ref<T&&> {
            using type = T&;
        };

        template<typename T>
        struct as_rref {
            using type = T&&;
        };
        template<typename T>
        struct as_rref<T&> {
            using type = T&&;
        };
        template<typename T>
        struct as_rref<T&&> {
            using type = T&&;
        };

        template<typename T>
        struct add_const_ref {
            using type = add_const<as_ref<T>>;
        };

        template<typename T>
        struct remove_reference{
            using type = T;
        };
        template<typename T>
        struct remove_reference<T&>{
            using type = T;
        };
        template<typename T>
        struct remove_reference<T&&>{
            using type = T;
        };

        template <bool, typename T = void>
        struct enable_if
        {};
        template <typename T>
        struct enable_if<true, T> {
            typedef T type;
        };

        struct __is_constructible_default_impl{

            template<typename T, typename = decltype(T())>
            static true_type test(int)
            {return {};}

            template<typename T>
            static false_type test(...)
            {return {};}
        };
        template<typename T>
        struct is_constructible_default : decltype(__is_constructible_default_impl::test<T>(0))
        {};

        template<typename T>
        inline typename as_rref<T>::type declval();
    }


    template<typename T>
    inline typename Meta::remove_reference<T>::type&& move(T &param)
    {
        return param;
    }

    template<typename T>
    inline void swap(T &first, T &second)
    {
        T temp(move(first));
        first = move(second);
        second = move(temp);
    }
}

#endif //TEMPLATES_BASIS_H
