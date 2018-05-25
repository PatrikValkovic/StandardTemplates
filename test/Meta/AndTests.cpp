#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

TEST_CASE("AND Should return true for one value","[Meta][and_]"){
    REQUIRE(and_<true>::value);
}

TEST_CASE("AND Should return false for one value","[Meta][and_]"){
    REQUIRE(!and_<false>::value);
}

TEST_CASE("AND Should return true for two value","[Meta][and_]"){
    REQUIRE(and_<true, true>::value);
}

TEST_CASE("AND Should return false for two values","[Meta][and_]"){
    REQUIRE(!and_<false, false>::value);
}

TEST_CASE("AND Should return false for two mixed values","[Meta][and_]"){
    REQUIRE(!and_<false, true>::value);
}

TEST_CASE("AND Should return true for five values","[Meta][and_]"){
    REQUIRE(and_<true, true, true, true, true>::value);
}

TEST_CASE("AND Should return true for five false values","[Meta][and_]"){
    REQUIRE(!and_<false, false, false, false, false>::value);
}

TEST_CASE("AND Should return true for one false values","[Meta][and_]"){
    REQUIRE(!and_<true, true, true, false, true>::value);
}





