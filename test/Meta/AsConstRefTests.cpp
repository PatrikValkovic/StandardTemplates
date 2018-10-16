#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

TEST_CASE("As const ref for integer","[Meta][as_const_ref]"){
    REQUIRE(are_same<const int&, as_const_ref<int>::type>::value);
}

TEST_CASE("As const ref for pointer","[Meta][as_const_ref]"){
    REQUIRE(are_same<int * const &, as_const_ref<int*>::type>::value);
}

TEST_CASE("As const ref for reference","[Meta][as_const_ref]"){
    REQUIRE(are_same<const int&, as_const_ref<int&>::type>::value);
}

TEST_CASE("As const ref for rreference","[Meta][as_const_ref]"){
    REQUIRE(are_same<const int&, as_const_ref<int&&>::type>::value);
}





