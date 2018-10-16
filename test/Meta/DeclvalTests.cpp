#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

TEST_CASE("Should return rreference type","[Meta][declval]"){
    REQUIRE(are_same<decltype(declval<int>()), int&&>::value);
}

TEST_CASE("Should return reference from reference type","[Meta][declval]"){
    REQUIRE(are_same<decltype(declval<int&>()), int&>::value);
}

TEST_CASE("Should return rreference from rreference type","[Meta][declval]"){
    REQUIRE(are_same<decltype(declval<int&&>()), int&&>::value);
}

TEST_CASE("Should return rreference type transformed to reference","[Meta][declval]"){
    REQUIRE(are_same<as_ref<decltype(declval<int>())>::type, int&>::value);
}

TEST_CASE("Should return rreference type transformed to value","[Meta][declval]"){
    REQUIRE(are_same<remove_reference<decltype(declval<int>())>::type, int>::value);
}

class C4 {
public:
    int prop;
};

TEST_CASE("Should be able to call property","[Meta][declval]"){
    REQUIRE(are_same<decltype(declval<C4>().prop), int>::value);
}

