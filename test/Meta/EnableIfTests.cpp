#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;


template<class T, class Enable = void>
struct s0 {
    static void f(){
        REQUIRE(false);
    }
};
template<class T>
struct s0<T, typename enable_if<are_same<int, T>::value>::type> {
    static void f(){
        REQUIRE(true);
    }
};
template<typename T>
void f1(T val){
    s0<T>::f();
}
TEST_CASE("Should call specialization template","[Meta][enable_if]"){
    f1(1);
}

template<class T, class Enable = void>
struct s1 {
    static void f(){
        REQUIRE(true);
    }
};
template<class T>
struct s1<T, typename enable_if<are_same<int, T>::value>::type> {
    static void f(){
        REQUIRE(false);
    }
};
template<typename T>
void f2(T val){
    s1<T>::f();
}
TEST_CASE("Should call global template","[Meta][enable_if]"){
    f2('a');
}

