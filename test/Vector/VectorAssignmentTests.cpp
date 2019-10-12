#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#include "../../Templates.h"
using namespace Templates;


int array[] = {1, 3, 5, 7, 9};

TEST_CASE("Should copy Vector", "[Vector][Assignment]") {
    Vector<int> instance(array, 5);
    Vector<int> second(10);
    second = instance;
    REQUIRE(!instance.Empty());
    REQUIRE(!second.Empty());
    REQUIRE(instance.Size() == 5);
    REQUIRE(second.Size() == 5);

    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == array[i]);
    for(int i=0;i<5;i++)
        REQUIRE(second[i] == array[i]);

    for(int i=0;i<5;i++)
        second[i]=i;

    for(int i=0;i<5;i++)
        REQUIRE(instance[i] == array[i]);
    for(int i=0;i<5;i++)
        REQUIRE(second[i] == i);
}

TEST_CASE("Should move Vector by assignment operator", "[Vector][Assignment]") {
    Vector<int> instance(array, 5);
    Vector<int> second(10);
    second = move(instance);
    REQUIRE(instance.Empty());
    REQUIRE(!second.Empty());
    REQUIRE(instance.Size() == 0);
    REQUIRE(second.Size() == 5);

    for(int i=0;i<5;i++)
        REQUIRE(second[i] == array[i]);
}

TEST_CASE("Should copy even empty Vector", "[Vector][Assignment]"){
    Vector<int> instance1;
    Vector<int> instance2;
    instance2 = instance1;

    REQUIRE(instance1.Empty());
    REQUIRE(instance2.Empty());
}

TEST_CASE("Should move even empty Vector", "[Vector][Assignment]"){
    Vector<int> instance1;
    Vector<int> instance2;
    instance2 = move(instance1);

    REQUIRE(instance1.Empty());
    REQUIRE(instance2.Empty());
}

TEST_CASE("Vector calling copy on self have not affect", "[Vector][Assignment]"){
    Vector<int> instance1;
    instance1 = instance1;
    REQUIRE(instance1.Empty());
}

TEST_CASE("Vector calling move assignment on self have not affect", "[Vector][Assignment]"){
    Vector<int> instance1;
    instance1 = move(instance1);
    REQUIRE(instance1.Empty());
}
