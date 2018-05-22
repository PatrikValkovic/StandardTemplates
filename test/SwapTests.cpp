#define CATCH_CONFIG_MAIN
#include "../libs/catch.h"
#include "../Templates.h"

class OnlyMovable
{
public:
    OnlyMovable() = default;
    ~OnlyMovable() = default;
    OnlyMovable(const OnlyMovable& second) = delete;
    OnlyMovable(OnlyMovable&& second) = default;
    OnlyMovable& operator=(const OnlyMovable& second) = delete;
    OnlyMovable& operator=(OnlyMovable&& second) = default;
};

class OnlyCopy
{
public:
    OnlyCopy() = default;
    ~OnlyCopy() = default;
    OnlyCopy(const OnlyCopy& second) = default;
    OnlyCopy(OnlyCopy&& second) = delete;
    OnlyCopy& operator=(const OnlyCopy& second) = default;
    OnlyCopy& operator=(OnlyCopy&& second) = delete;
};

/*TEST_CASE("Should call only move semantic", "[swap]")
{
    OnlyMovable a;
    OnlyMovable b;
    Templates::swap(a,b);
}

TEST_CASE("Should call only copy semantic", "[swap]")
{
    OnlyCopy a;
    OnlyCopy b;
    Templates::swap(a,b);
}*/

