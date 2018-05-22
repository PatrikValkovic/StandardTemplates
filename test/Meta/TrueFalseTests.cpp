#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

TEST_CASE("False type is false", "[Meta][false_type]")
{
    REQUIRE(!false_type::value);
}
TEST_CASE("ATrue type is true", "[Meta][true_type]")
{
    REQUIRE(true_type::value);
}
