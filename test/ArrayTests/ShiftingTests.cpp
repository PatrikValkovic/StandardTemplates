#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#define private public
#include "../../Templates.h"
using namespace Templates;



TEST_CASE("Array should shift negative") {
    // {1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,27,29};
    //                        -2: -----------------
    // {1, 3, 5, 7, 9,11,13,19,21,23,25,27,29};
    int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    Array<int> Instance(OriginalArray, 15);
    REQUIRE(Instance.Capacity() == 15);
    REQUIRE(Instance.Size() == 15);
    REQUIRE(Instance.Shift(9, -2));
    REQUIRE(Instance.Capacity() == 15);
    REQUIRE(Instance.Size() == 13);
    for (int a = 0; a < 7; a++)
        REQUIRE(*Instance.Containing[a] == OriginalArray[a]);
    for (int a = 7; a < 13; a++)
        REQUIRE(*Instance.Containing[a] == OriginalArray[a + 2]);
}

TEST_CASE("Array should shift positive") {
    // {1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,27,29};
    //                        +5: -----------------
    // {1, 3, 5, 7, 9,11,13,15,17,__,__,__,__,__,19,21,23,25,27,29};
    int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    Array<int> Instance(OriginalArray, 15);
    REQUIRE(Instance.Capacity() == 15);
    REQUIRE(Instance.Size() == 15);
    REQUIRE(Instance.Shift(9, 5));
    REQUIRE(Instance.Capacity() >= 20);
    REQUIRE(Instance.Size() == 20);
    for (int a = 0; a < 9; a++)
        REQUIRE(*Instance.Containing[a] == OriginalArray[a]);
    for (int a = 9; a < 14; a++)
        REQUIRE(Instance.Containing[a] == NULL);
    for (int a = 14; a < 20; a++)
        REQUIRE(*Instance.Containing[a] == OriginalArray[a - 5]);
}

TEST_CASE("Array should shift negative over size") {
    // {1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,27,29};
    //                       -20: -----------------
    // {19,21,23,25,27,29};
    int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    Array<int> Instance(OriginalArray, 15);
    REQUIRE(Instance.Capacity() == 15);
    REQUIRE(Instance.Size() == 15);
    REQUIRE(Instance.Shift(9, -20));
    REQUIRE(Instance.Capacity() >= 6);
    REQUIRE(Instance.Size() == 6);
    for (int a = 0; a < 6; a++)
        REQUIRE(*Instance.Containing[a] == OriginalArray[a + 9]);
}

TEST_CASE("Array should shift positive from the beginning") {
    //    {1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,27,29};
    // 5: -----------------
    //   {__,__,__,__,__, 1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,27,29};
    int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    Array<int> Instance(OriginalArray, 15);
    REQUIRE(Instance.Capacity() == 15);
    REQUIRE(Instance.Size() == 15);
    REQUIRE(Instance.Shift(0, 5));
    REQUIRE(Instance.Capacity() >= 20);
    REQUIRE(Instance.Size() == 20);
    for (int a = 0; a < 5; a++)
        REQUIRE(Instance.Containing[a] == NULL);
    for (int a = 5; a < 20; a++)
        REQUIRE(*Instance.Containing[a] == OriginalArray[a - 5]);
}

TEST_CASE("Array should shift positive at the end") {
    //    {1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,27,29};
    //                                        5: -----
    //    {1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,__,__,__,__,__,27,29};
    int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    Array<int> Instance(OriginalArray, 15);
    REQUIRE(Instance.Capacity() == 15);
    REQUIRE(Instance.Size() == 15);
    REQUIRE(Instance.Shift(13, 5));
    REQUIRE(Instance.Capacity() >= 20);
    REQUIRE(Instance.Size() == 20);
    for (int a = 5; a < 13; a++)
        REQUIRE(*Instance.Containing[a] == OriginalArray[a]);
    for (int a = 13; a < 18; a++)
        REQUIRE(Instance.Containing[a] == NULL);
    for (int a = 18; a < 20; a++)
        REQUIRE(*Instance.Containing[a] == OriginalArray[a - 5]);
}
