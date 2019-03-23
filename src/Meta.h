#ifndef TEMPLATES_META_H
#define TEMPLATES_META_H

namespace Templates
{
    namespace Meta
    {
        void _void_f()
        {}

        struct true_type
        {
            static const bool value = true;
        };
        struct false_type
        {
            static const bool value = false;
        };

        template<bool>
        struct bool_type: false_type
        {};
        template<>
        struct bool_type<true>: true_type
        {};

        template<bool, bool ...Args>
        struct and_ : false_type{};
        template<bool ...Args>
        struct and_<true,Args...>{
            static const bool value = and_<Args...>::value;
        };
        template<>
        struct and_<true> : true_type {};
        template<>
        struct and_<false> : false_type {};

        template<bool, bool ...Args>
        struct or_ : false_type{};
        template<bool ...Args>
        struct or_<true,Args...> : true_type{};
        template<bool ...Args>
        struct or_<false,Args...> {
            static const bool value = or_<Args...>::value;
        };
        template<>
        struct or_<true> : true_type {};
        template<>
        struct or_<false> : false_type {};

        template<bool T>
        struct not_{
            static const bool value = !T;
        };

        template<typename T, typename V = void>
        struct are_same : false_type
        {
        };
        template<typename T>
        struct are_same<T, T> : true_type
        {
        };

        template<typename T>
        struct add_const
        {
            using type = const T;
        };
        template<typename T>
        struct add_const<const T>
        {
            using type = const T;
        };
        template<typename T>
        struct add_const<T&>
        {
            using type = const T&;
        };
        template<typename T>
        struct add_const<T&&>
        {
            using type = const T&&;
        };

        template<typename T>
        struct as_ref
        {
            using type = T&;
        };
        template<typename T>
        struct as_ref<T&>
        {
            using type = T&;
        };
        template<typename T>
        struct as_ref<T&&>
        {
            using type = T&;
        };

        template<typename T>
        struct as_rref
        {
            using type = T&&;
        };
        template<typename T>
        struct as_rref<T&>
        {
            using type = T&&;
        };
        template<typename T>
        struct as_rref<T&&>
        {
            using type = T&&;
        };

        template<typename T>
        struct as_const_ref
        {
            using type = typename add_const<typename as_ref<T>::type>::type;
        };

        template<typename T>
        struct remove_reference
        {
            using type = T;
        };
        template<typename T>
        struct remove_reference<T&>
        {
            using type = T;
        };
        template<typename T>
        struct remove_reference<T&&>
        {
            using type = T;
        };

        template<typename T>
        struct remove_array
        {
            using type = T;
        };
        template<typename T>
        struct remove_array<T[]>
        {
            using type = T;
        };

        template<bool, typename T = void>
        struct enable_if{};
        template<typename T>
        struct enable_if<true, T>{typedef T type;};

        template<typename T>
        struct is_lvalue_reference : false_type{};
        template<typename T>
        struct is_lvalue_reference<T&> : true_type {};

        template<typename T>
        struct is_rvalue_reference : false_type{};
        template<typename T>
        struct is_rvalue_reference<T&&> : true_type {};

        template<typename T>
        struct is_reference :
                    or_<
                        is_lvalue_reference<T>::value,
                        is_rvalue_reference<T>::value
                    >
        {};

        template<typename T, bool = is_reference<T>::value>
        struct __declval_rref{
            using type= typename as_rref<T>::type;
        };
        template<typename T>
        struct __declval_rref<T, true>{
            using type=T;
        };
        template<typename T>
        inline typename __declval_rref<T>::type declval() noexcept;

        struct __is_constructible_default_impl
        {
            template<typename T, typename = decltype(T())>
            static true_type test(int)
            { return {}; }

            template<typename T>
            static false_type test(...)
            { return {}; }
        };
        template<typename T>
        struct is_constructible_default : decltype(__is_constructible_default_impl::test<T>(0))
        {};

        struct __is_constructible_default_noexcept_impl
        {
            template<typename T, bool = noexcept(T())>
            static bool_type<noexcept(T())> test(int)
            { return {}; }

            template<typename T>
            static false_type test(...)
            { return {}; }
        };
        template<typename T>
        struct is_constructible_default_noexcept
                : decltype(__is_constructible_default_noexcept_impl::test<T>(0))
        {};


        struct __is_constructible_movable_impl
        {

            template<typename T, typename = decltype(T(declval<T>()))>
            static true_type test(int)
            { return {}; }

            template<typename T>
            static false_type test(...)
            { return {}; }
        };
        template<typename T>
        struct is_constructible_movable :
                decltype(__is_constructible_movable_impl::test<T>(0))
        {};
        template<typename T>
        struct is_constructible_movable<T&> :
                true_type
        {};
        template<typename T>
        struct is_constructible_movable<T&&> :
                true_type
        {};

        struct __is_constructible_movable_noexcept_impl
        {
            template<typename T, bool = noexcept(T(declval<T>()))>
            static bool_type<noexcept(T(declval<T>()))> test(int)
            { return {}; }

            template<typename T>
            static false_type test(...)
            { return {}; }
        };
        template<typename T>
        struct is_constructible_movable_noexcept
                : decltype(__is_constructible_movable_noexcept_impl::test<T>(0))
        {};

        struct __is_constructable_copyable_impl
        {
            template<typename T, typename = decltype(T(static_cast<const T&>(declval<T>())))>
            static true_type test(int)
            { return {}; }

            template<typename T>
            static false_type test(...)
            { return {}; }
        };
        template<typename T>
        struct is_constructible_copyable :
                decltype(__is_constructable_copyable_impl::test<T>(0))
        {};
        template<typename T>
        struct is_constructible_copyable<T&> : true_type
        {};

        struct __is_constructible_copyable_noexcept_impl
        {
            template<typename T, bool = noexcept(T(static_cast<const T&>(declval<T>())))>
            static bool_type<noexcept(T(static_cast<const T&>(declval<T>())))> test(int)
            { return {}; }

            template<typename T>
            static false_type test(...)
            { return {}; }
        };
        template<typename T>
        struct is_constructible_copyable_noexcept
                : decltype(__is_constructible_copyable_noexcept_impl::test<T>(0))
        {};

        struct __is_assignable_impl
        {
            template<typename T, typename U,
                    typename = decltype(declval<T>() = declval<U>())
                    >
            static true_type test(int)
            { return {}; }

            template<typename, typename>
            static false_type test(...)
            { return {}; }
        };
        template<typename T, typename U>
        struct is_assignable : decltype(__is_assignable_impl::test<T, U>(0))
        {};

        struct __is_assignable_noexcept_impl
        {
            template<typename T, typename U,
                    bool = noexcept(declval<T>() = declval<U>())
            >
            static bool_type<noexcept(declval<T>() = declval<U>())> test(int)
            { return {}; }

            template<typename, typename>
            static false_type test(...)
            { return {}; }
        };
        template<typename T, typename U>
        struct is_assignable_noexcept : decltype(__is_assignable_noexcept_impl::test<T, U>(0))
        {};


        template<typename T>
        struct is_assignable_copy : is_assignable<
                typename as_ref<T>::type,
                typename as_const_ref<T>::type
            >
        {};

        template<typename T>
        struct is_assignable_move : is_assignable<
                typename as_ref<T>::type,
                typename as_rref<T>::type
        >
        {};

        template<typename T>
        struct is_assignable_copy_noexcept : is_assignable_noexcept<
                typename as_ref<T>::type,
                typename as_const_ref<T>::type
        >
        {};

        template<typename T>
        struct is_assignable_move_noexcept : is_assignable_noexcept<
                typename as_ref<T>::type,
                typename as_rref<T>::type
            >
        {};

    }
}

#endif //TEMPLATES_META_H
