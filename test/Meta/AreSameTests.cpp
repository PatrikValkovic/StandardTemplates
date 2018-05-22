#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"

using namespace Templates::Meta;

TEST_CASE("Are same for integer and integer", "[Meta][are_same]")
{
    REQUIRE(are_same<int,int>::value);
}

TEST_CASE("Are same for integer and integer point", "[Meta][are_same]")
{
    REQUIRE(!are_same<int,int*>::value);
}

TEST_CASE("Are same for integer and integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int,int&>::value);
}

TEST_CASE("Are same for integer and integer movable reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int,int&&>::value);
}

TEST_CASE("Are same for integer and const integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<int,const int>::value);
}

TEST_CASE("Are same for integer and const integer pointer", "[Meta][are_same]")
{
    REQUIRE(!are_same<int,const int *>::value);
}

TEST_CASE("Are same for integer and const integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int,const int &>::value);
}

TEST_CASE("Are same for integer and const integer rreference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int,const int &&>::value);
}

// ------

TEST_CASE("Are same for integer pointer and integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<int*,int>::value);
}

TEST_CASE("Are same for integer pointer and integer point", "[Meta][are_same]")
{
    REQUIRE(are_same<int*,int*>::value);
}

TEST_CASE("Are same for integer pointer and integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int*,int&>::value);
}

TEST_CASE("Are same for integer pointer and integer movable reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int*,int&&>::value);
}

TEST_CASE("Are same for integer pointer and const integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<int*,const int>::value);
}

TEST_CASE("Are same for integer pointer and const integer pointer", "[Meta][are_same]")
{
    REQUIRE(!are_same<int*,const int *>::value);
}

TEST_CASE("Are same for integer pointer and const integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int*,const int &>::value);
}

TEST_CASE("Are same for integer pointer and const integer rreference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int*,const int &&>::value);
}

//------

TEST_CASE("Are same for integer reference and integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&,int>::value);
}

TEST_CASE("Are same for integer reference and integer point", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&,int*>::value);
}

TEST_CASE("Are same for integer reference and integer reference", "[Meta][are_same]")
{
    REQUIRE(are_same<int&,int&>::value);
}

TEST_CASE("Are same for integer reference and integer movable reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&,int&&>::value);
}

TEST_CASE("Are same for integer reference and const integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&,const int>::value);
}

TEST_CASE("Are same for integer reference and const integer pointer", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&,const int *>::value);
}

TEST_CASE("Are same for integer reference and const integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&,const int &>::value);
}

TEST_CASE("Are same for integer reference and const integer rreference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&,const int &&>::value);
}

//--------------

TEST_CASE("Are same for integer rreference and integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&&,int>::value);
}

TEST_CASE("Are same for integer rreference and integer point", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&&,int*>::value);
}

TEST_CASE("Are same for integer rreference and integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&&,int&>::value);
}

TEST_CASE("Are same for integer rreference and integer movable reference", "[Meta][are_same]")
{
    REQUIRE(are_same<int&&,int&&>::value);
}

TEST_CASE("Are same for integer rreference and const integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&&,const int>::value);
}

TEST_CASE("Are same for integer rreference and const integer pointer", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&&,const int *>::value);
}

TEST_CASE("Are same for integer rreference and const integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&&,const int &>::value);
}

TEST_CASE("Are same for integer rreference and const integer rreference", "[Meta][are_same]")
{
    REQUIRE(!are_same<int&&,const int &&>::value);
}

//-----

TEST_CASE("Are same for const integer and integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int,int>::value);
}

TEST_CASE("Are same for const integer and integer point", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int,int*>::value);
}

TEST_CASE("Are same for const integer and integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int,int&>::value);
}

TEST_CASE("Are same for const integer and integer movable reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int,int&&>::value);
}

TEST_CASE("Are same for const integer and const integer", "[Meta][are_same]")
{
    REQUIRE(are_same<const int,const int>::value);
}

TEST_CASE("Are same for const integer and const integer pointer", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int,const int *>::value);
}

TEST_CASE("Are same for const integer and const integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int,const int &>::value);
}

TEST_CASE("Are same for const integer and const integer rreference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int,const int &&>::value);
}

//----

TEST_CASE("Are same for const integer pointer and integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int *,int>::value);
}

TEST_CASE("Are same for const integer pointer and integer point", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int *,int*>::value);
}

TEST_CASE("Are same for const integer pointer and integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int *,int&>::value);
}

TEST_CASE("Are same for const integer pointer and integer movable reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int *,int&&>::value);
}

TEST_CASE("Are same for const integer pointer and const integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int *,const int>::value);
}

TEST_CASE("Are same for const integer pointer and const integer pointer", "[Meta][are_same]")
{
    REQUIRE(are_same<const int *,const int *>::value);
}

TEST_CASE("Are same for const integer pointer and const integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int *,const int &>::value);
}

TEST_CASE("Are same for const integer pointer and const integer rreference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int *,const int &&>::value);
}
//---

TEST_CASE("Are same for const int reference and integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &,int>::value);
}

TEST_CASE("Are same for const int reference  and integer point", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &,int*>::value);
}

TEST_CASE("Are same for const int reference  and integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &,int&>::value);
}

TEST_CASE("Are same for const int reference  and integer movable reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &,int&&>::value);
}

TEST_CASE("Are same for const int reference  and const integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &,const int>::value);
}

TEST_CASE("Are same for const int reference  and const integer pointer", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &,const int *>::value);
}

TEST_CASE("Are same for const int reference  and const integer reference", "[Meta][are_same]")
{
    REQUIRE(are_same<const int &,const int &>::value);
}

TEST_CASE("Are same for const int reference  and const integer rreference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &,const int &&>::value);
}

//-----

TEST_CASE("Are same for const integer rreference and integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &&,int>::value);
}

TEST_CASE("Are same for const integer rreference and integer point", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &&,int*>::value);
}

TEST_CASE("Are same for const integer rreference and integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &&,int&>::value);
}

TEST_CASE("Are same for const integer rreference and integer movable reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &&,int&&>::value);
}

TEST_CASE("Are same for const integer rreference and const integer", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &&,const int>::value);
}

TEST_CASE("Are same for const integer rreference and const integer pointer", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &&,const int *>::value);
}

TEST_CASE("Are same for const integer rreference and const integer reference", "[Meta][are_same]")
{
    REQUIRE(!are_same<const int &&,const int &>::value);
}

TEST_CASE("Are same for const integer rreference and const integer rreference", "[Meta][are_same]")
{
    REQUIRE(are_same<const int &&,const int &&>::value);
}


