#ifndef TEMPLATES_BASIS_H
#define TEMPLATES_BASIS_H

namespace Templates
{
    namespace Meta
    {
        struct true_type {
            static const bool value = true;
        };
        struct false_type {
            static const bool value = false;
        };

        template<typename T, typename V>
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
    }


    template<typename T>
    inline T& move(T param)
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
