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
        struct add_const_ref
        {
            using type = typename add_const<as_ref<T>>::type;
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
        inline typename as_rref<T>::type declval();

        template<bool, typename T = void>
        struct enable_if
        {
        };
        template<typename T>
        struct enable_if<true, T>
        {
            typedef T type;
        };

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
        {
        };

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

        struct __is_assignable_copy_impl
        {
            template<typename T, typename = decltype(declval<T>().operator=(static_cast<const T&>(declval<T>())))>
            static true_type test(int)
            { return {}; }

            template<typename T>
            static false_type test(...)
            { return {}; }
        };
        template<typename T>
        struct is_assignable_copy : decltype(__is_assignable_copy_impl::test<T>(0))
        {};

        struct __is_assignable_move_impl
        {
            template<typename T, typename = decltype(declval<T>().operator=(declval<T>()))>
            static true_type test(int)
            { return {}; }

            template<typename T>
            static false_type test(...)
            { return {}; }
        };
        template<typename T>
        struct is_assignable_move : decltype(__is_assignable_move_impl::test<T>(0))
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

    }
}

#endif //TEMPLATES_META_H
