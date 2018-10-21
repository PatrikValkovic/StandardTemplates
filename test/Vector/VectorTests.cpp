#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
/*
#include "../../Templates.h"

class VectorTest
{
public:
    VectorTest()
    { }

    void Creation()
    {
        using namespace Templates;
        Vector<int>* Instance;
        int list[] = {2, 6, 8, 4, 7};

        Instance = new Vector<int>();
        REQUIRE(Instance->Size() == 0);
        REQUIRE(Instance->IsEmpty());
        Vector<int>::Iterator FirstIter = Instance->Begin();
        Vector<int>::Iterator SecondIter = Instance->End();
        REQUIRE(FirstIter == SecondIter);
        REQUIRE(!FirstIter.Next());
        REQUIRE(!SecondIter.Next(5));
        delete Instance;

        Instance = new Vector<int>(5);
        REQUIRE(!Instance->IsEmpty());
        REQUIRE(Instance->Size() == 5);
        FirstIter = Instance->Begin();
        REQUIRE(FirstIter.Next());   //move to second
        REQUIRE(!FirstIter.Next(5)); //move to 2+5 = 7, have just 5 values + 1 last
        REQUIRE(FirstIter.Next(4));  //move to 2+4 = 6 => To end noe
        SecondIter = Instance->End();
        REQUIRE(FirstIter == SecondIter);
        REQUIRE(!FirstIter.Next());
        delete Instance;

        Instance = new Vector<int>(list, 5); // {2, 6, 8, 4, 7}
        REQUIRE(Instance->Size() == 5);
        REQUIRE(!Instance->IsEmpty());
        FirstIter = Instance->Begin();
        REQUIRE(*FirstIter == 2);
        REQUIRE(FirstIter.Next());
        REQUIRE(*FirstIter == 6);
        REQUIRE(FirstIter.Next());
        REQUIRE(*FirstIter == 8);
        REQUIRE(FirstIter.Next());
        REQUIRE(*FirstIter == 4);
        REQUIRE(FirstIter.Next());
        REQUIRE(*FirstIter == 7);
        REQUIRE(FirstIter.Next());
        REQUIRE(!FirstIter.Next());
		delete Instance;
    }

    void ClearingTests()
    {
        using namespace Templates;
        Vector<int>* Instance;
        //Vector<int>::Iterator* FirstIter;
        //Vector<int>::Iterator* SecondIter;
        int list[] = {2, 6, 8, 4, 7};

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        REQUIRE(Instance->Delete() == 5);
        REQUIRE(Instance->IsEmpty());
        REQUIRE(Instance->Size() == 0);
        delete Instance;

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        REQUIRE(Instance->Delete(2) == 2);//{2, 6, 7}
        REQUIRE(Instance->Size() == 3);
        REQUIRE(!Instance->IsEmpty());
        Vector<int>::Iterator FirstIter = Instance->Begin();
        REQUIRE(!FirstIter.Next(8));
        REQUIRE(*FirstIter == 2);
        REQUIRE(FirstIter.Next());
        REQUIRE(*FirstIter == 6);
        REQUIRE(FirstIter.Next());
        REQUIRE(*FirstIter == 7);
        REQUIRE(FirstIter.Next());
        REQUIRE(!FirstIter.Next());
        delete Instance;

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        FirstIter = Instance->Begin();
        REQUIRE(FirstIter.Next()); // to 6
        Vector<int>::Iterator SecondIter = Instance->Begin();
        REQUIRE(SecondIter.Next(3)); // to 4
        FirstIter = Instance->Begin();
        REQUIRE(*FirstIter == 2);
        REQUIRE(FirstIter.Next());
		REQUIRE(*FirstIter == 6);
		REQUIRE(FirstIter.Next());
        REQUIRE(*FirstIter == 4);
        REQUIRE(FirstIter.Next());
        REQUIRE(*FirstIter == 7);
        delete Instance;

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        FirstIter = Instance->Begin();
        SecondIter = Instance->End();
        REQUIRE(!Instance->IsEmpty());
        REQUIRE(Instance->Size() == 1);
		REQUIRE(*FirstIter == 2);
		REQUIRE(FirstIter.Next());
		REQUIRE((Instance->IsEmpty() && Instance->Size() == 0));
        delete Instance;

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        FirstIter = Instance->Begin();
        REQUIRE((FirstIter == SecondIter));
        REQUIRE(Instance->IsEmpty());
        REQUIRE(Instance->Size() == 0);
        delete Instance;
    }

    void InsertingTests()
    {
        using namespace Templates;
        Vector<int>* Instance;
        int list[] = {2, 6, 8, 4, 7};
        int SecondList[] = {12, 16, 22, 13};

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        Vector<int>::Iterator FirstIter = Instance->Begin();
        REQUIRE(FirstIter.Next());
        FirstIter.Insert(SecondList, 4); //{2, 6, 12, 16, 22, 13, 8, 4, 7}
        REQUIRE(Instance->Size() == 9);
        REQUIRE(!Instance->IsEmpty());
        REQUIRE(*FirstIter == 6);
        REQUIRE(FirstIter.Next());
        REQUIRE(*FirstIter == 12);
        delete Instance;

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        FirstIter = Instance->Begin();
        FirstIter.Insert(9); //{2,9,8,4,7}
        REQUIRE(FirstIter.Next());
        REQUIRE(*FirstIter == 9);
		delete Instance;
    }

    void IteratorsTest()
    {
        using namespace Templates;

        Vector<int>* Instance = new Vector<int>(5);
        Vector<int>::Iterator FirstIter = Instance->Begin();
        Vector<int>::Iterator SecondIter = Instance->End();
        REQUIRE(FirstIter.Next());
		delete Instance;
    }

    void VectorBaseTests()
    {
        using namespace Templates;
        Vector<int>* Instance;
        Vector<int>::Iterator* FirstIter;
        Vector<int>::Iterator* SecondIter;
        int list[] = {2, 6, 8, 4, 7};
        int SecondList[] = {12, 16, 22, 13};

        Instance = new Vector<int>();
        REQUIRE(Instance->Size() == 0);
        REQUIRE(Instance->IsEmpty());
        Vector<int>::Iterator FirstIterVal = Instance->Begin();
        Vector<int>::Iterator SecondIterVal = Instance->End();
        FirstIter = &FirstIterVal;
        SecondIter = &SecondIterVal;
        REQUIRE(!FirstIter->Next());
        REQUIRE(!SecondIter->Next(5));
        delete Instance;

        Instance = new Vector<int>(5);
        REQUIRE(!Instance->IsEmpty());
        REQUIRE(Instance->Size() == 5);
        FirstIterVal = Instance->Begin();
        SecondIterVal = Instance->End();
        FirstIter = &FirstIterVal;
        SecondIter = &SecondIterVal;
        REQUIRE(FirstIter->Next());   //move to second
        REQUIRE(!FirstIter->Next(5)); //move to 2+5 = 7, have just 5 values + 1 last
        REQUIRE(FirstIter->Next(4));  //move to 2+4 = 6 => To end noe
        REQUIRE(!FirstIter->Next());
        delete Instance;

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        FirstIterVal = Instance->Begin();
        Vector<int>::Iterator* DelIter = &FirstIterVal;
        REQUIRE(DelIter->Next());
        DelIter->Insert(SecondList, 4); //{2, 6, 12,16,22,13, 8, 4, 7}
        REQUIRE(Instance->Size() == 9);
        REQUIRE(!Instance->IsEmpty());
        REQUIRE(**DelIter == 6);
        REQUIRE(DelIter->Next());
        REQUIRE(**DelIter == 12);
        delete Instance;
    }

public:
    static void test()
    {
        VectorTest* Instance = new VectorTest;
        Instance->Creation();
        Instance->ClearingTests();
        Instance->InsertingTests();
        Instance->IteratorsTest();
        Instance->VectorBaseTests();
		delete Instance;

        return;
    }
};

TEST_CASE("Vector tests"){
    VectorTest::test();
}*/
