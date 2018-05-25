#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

TEST_CASE("OR Should return true for one value","[Meta][or_]"){
    REQUIRE(or_<true>::value);
}

TEST_CASE("OR Should return false for one value","[Meta][or_]"){
    REQUIRE(!or_<false>::value);
}

TEST_CASE("OR Should return true for two value","[Meta][or_]"){
    REQUIRE(or_<true, true>::value);
}

TEST_CASE("OR Should return false for two values","[Meta][or_]"){
    REQUIRE(!or_<false, false>::value);
}

TEST_CASE("OR Should return true for two mixed values","[Meta][or_]"){
    REQUIRE(or_<false, true>::value);
}

TEST_CASE("OR Should return true for five values","[Meta][or_]"){
    REQUIRE(or_<true, true, true, true, true>::value);
}

TEST_CASE("OR Should return false for five false values","[Meta][or_]"){
    REQUIRE(!or_<false, false, false, false, false>::value);
}

TEST_CASE("OR Should return true for one false values","[Meta][or_]"){
    REQUIRE(or_<true, true, true, false, true>::value);
}

TEST_CASE("OR Should return true for one true values","[Meta][or_]"){
    REQUIRE(or_<false, false, true, false, false>::value);
}
