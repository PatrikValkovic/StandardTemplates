#define CATCH_CONFIG_MAIN
#include <assert.h>
#include "../libs/catch.h"
#include "../Templates.h"

class VectorTest
{
public:
    VectorTest()
    { }

    void Creation()
    {
        using namespace Templates;
        Vector<int>* Instance;
        Vector<int>::Iterator FirstIter;
        Vector<int>::Iterator SecondIter;
        int list[] = {2, 6, 8, 4, 7};

        Instance = new Vector<int>();
        assert(Instance->Size() == 0);
        assert(Instance->IsEmpty());
        FirstIter = Instance->Begin();
        SecondIter = Instance->End();
        assert(FirstIter.AreEqual(SecondIter));
        assert(!FirstIter.Next());
        assert(!SecondIter.Next(5));
        delete Instance;

        Instance = new Vector<int>(5);
        assert(!Instance->IsEmpty());
        assert(Instance->Size() == 5);
        FirstIter = Instance->Begin();
        assert(FirstIter.Next());   //move to second
        assert(!FirstIter.Next(5)); //move to 2+5 = 7, have just 5 values + 1 last
        assert(FirstIter.Next(4));  //move to 2+4 = 6 => To end noe
        SecondIter = Instance->End();
        assert(FirstIter.AreEqual(SecondIter));
        assert(!FirstIter.Next());
        delete Instance;

        Instance = new Vector<int>(list, 5); // {2, 6, 8, 4, 7}
        assert(Instance->Size() == 5);
        assert(!Instance->IsEmpty());
        FirstIter = Instance->Begin();
        assert(*FirstIter.GetValue() == 2);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 6);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 8);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 4);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 7);
        assert(FirstIter.Next());
		assert(FirstIter.GetValue() == NULL);
        assert(!FirstIter.Next());
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
        assert(Instance->Clear() == 5);
        assert(Instance->IsEmpty());
        assert(Instance->Size() == 0);
        delete Instance;

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        assert(Instance->Clear(2, 2) == 2);//{2, 6, 7}
        assert(Instance->Size() == 3);
        assert(!Instance->IsEmpty());
        Vector<int>::Iterator FirstIter = Instance->Begin();
        assert(!FirstIter.Next(8));
        assert(*FirstIter.GetValue() == 2);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 6);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 7);
        assert(FirstIter.Next());
		assert(FirstIter.GetValue() == NULL);
        assert(!FirstIter.Next());
        delete Instance;

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        FirstIter = Instance->Begin();
        assert(FirstIter.Next()); // to 6
        Vector<int>::Iterator SecondIter = Instance->Begin();
        assert(SecondIter.Next(3)); // to 4
        assert(Instance->Clear(FirstIter, SecondIter) == 1); //{2, 6, 4, 7}
        FirstIter = Instance->Begin();
        assert(*FirstIter.GetValue() == 2);
        assert(FirstIter.Next());
		assert(*FirstIter.GetValue() == 6);
		assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 4);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 7);
        delete Instance;

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        FirstIter = Instance->Begin();
        SecondIter = Instance->End();
        assert(Instance->Clear(FirstIter, SecondIter) == 4);// {2}
        assert(!Instance->IsEmpty());
        assert(Instance->Size() == 1);
		assert(*FirstIter.GetValue() == 2);
		assert(FirstIter.Next() && FirstIter.GetValue() == NULL);
		assert(Instance->Clear(0,1)==1);
		assert(Instance->IsEmpty() && Instance->Size() == 0);
        delete Instance;

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        assert(Instance->Clear(0, 8) == 5);
        FirstIter = Instance->Begin();
        SecondIter = Instance->End();
        assert((FirstIter.AreEqual(SecondIter)));
        assert(Instance->IsEmpty());
        assert(Instance->Size() == 0);
		assert(FirstIter.GetValue() == NULL);
		assert(SecondIter.GetValue() == NULL);
        delete Instance;
    }

    void ToArrayTest()
    {
        using namespace Templates;
        Vector<int>* Instance;
        int list[] = {2, 6, 8, 4, 7};

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        int Count;
        int* Array = Instance->ToArray(Count);
        assert(Count == 5);
        assert(Array[0] == 2 && Array[1] == 6 && Array[2] == 8 && Array[3] == 4 && Array[4] == 7);
        assert(Instance->Clear() == 5);
        assert(Instance->IsEmpty());
        delete [] Array;
        Array = Instance->ToArray(Count);
        assert(Array == NULL && Count == 0);
        delete Instance;
        return;
    }

    void InsertingTests()
    {
        using namespace Templates;
        Vector<int>* Instance;
        int list[] = {2, 6, 8, 4, 7};
        int SecondList[] = {12, 16, 22, 13};

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        Vector<int>::Iterator FirstIter = Instance->Begin();
        assert(FirstIter.Next());
        assert(FirstIter.Insert(SecondList, 4)); //{2, 6, 12, 16, 22, 13, 8, 4, 7}
        assert(Instance->Size() == 9);
        assert(!Instance->IsEmpty());
        assert(*FirstIter.GetValue() == 6);
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 12);
        delete Instance;

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        FirstIter = Instance->Begin();
        assert(FirstIter.Insert(9)); //{2,9,8,4,7}
        assert(FirstIter.Next());
        assert(*FirstIter.GetValue() == 9);
		delete Instance;
    }

    void IteratorsTest()
    {
        using namespace Templates;

        Vector<int>* Instance = new Vector<int>(5);
        Vector<int>::Iterator FirstIter = Instance->Begin();
        Vector<int>::Iterator SecondIter = Instance->End();
        assert(SecondIter.IsGreaterThan(FirstIter));
        assert(FirstIter.Next());
        assert(SecondIter.IsGreaterThan(FirstIter));
        assert(!FirstIter.IsGreaterThan(SecondIter));
		delete Instance;
    }

	void IteratorAt()
	{
		using namespace Templates;
		Vector<int>* Instance;
		Vector<int>::Iterator Iter;
		int list[] = { 2, 6, 8, 4, 7 };

		Instance = new Vector<int>(list,5);//{ 2, 6, 8, 4, 7 }
		assert(Instance->At(3,Iter));
		assert(*Iter.GetValue() == 8);
		delete Instance;

		Instance = new Vector<int>(list, 5);//{ 2, 6, 8, 4, 7 }
		assert(!Instance->At(8, Iter));
		delete Instance;
	}

    void VectorBaseTests()
    {
        using namespace Templates;
        Vector<int>* Instance;
        Iterators::ForwardIteratorBase<int>* FirstIter;
        Iterators::ForwardIteratorBase<int>* SecondIter;
        Vector<int>::Iterator FirstIterVal;
        Vector<int>::Iterator SecondIterVal;
        int list[] = {2, 6, 8, 4, 7};
        int SecondList[] = {12, 16, 22, 13};

        Instance = new Vector<int>();
        assert(Instance->Size() == 0);
        assert(Instance->IsEmpty());
        FirstIterVal = Instance->Begin();
        SecondIterVal = Instance->End();
        FirstIter = &FirstIterVal;
        SecondIter = &SecondIterVal;
        assert(!FirstIter->Next());
        assert(!SecondIter->Next(5));
        delete Instance;

        Instance = new Vector<int>(5);
        assert(!Instance->IsEmpty());
        assert(Instance->Size() == 5);
        FirstIterVal = Instance->Begin();
        SecondIterVal = Instance->End();
        FirstIter = &FirstIterVal;
        SecondIter = &SecondIterVal;
        assert(FirstIter->Next());   //move to second
        assert(!FirstIter->Next(5)); //move to 2+5 = 7, have just 5 values + 1 last
        assert(FirstIter->Next(4));  //move to 2+4 = 6 => To end noe
        assert(!FirstIter->Next());
        delete Instance;

        Instance = new Vector<int>(list, 5); //{2, 6, 8, 4, 7}
        FirstIterVal = Instance->Begin();
        Iterators::DeletingForwardIteratorBase<int>* DelIter = &FirstIterVal;
        assert(DelIter->Next());
        assert(DelIter->Insert(SecondList, 4)); //{2, 6, 12,16,22,13, 8, 4, 7}
        assert(Instance->Size() == 9);
        assert(!Instance->IsEmpty());
        assert(*DelIter->GetValue() == 6);
        assert(DelIter->Next());
        assert(*DelIter->GetValue() == 12);
        delete Instance;
    }

public:
    static void test()
    {
        VectorTest* Instance = new VectorTest;
        Instance->Creation();
        Instance->ClearingTests();
        Instance->ToArrayTest();
        Instance->InsertingTests();
        Instance->IteratorsTest();
		Instance->IteratorAt();
        Instance->VectorBaseTests();
		delete Instance;

        return;
    }
};

TEST_CASE("Vector tests"){
    VectorTest::test();
}