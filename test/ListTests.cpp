#define CATCH_CONFIG_MAIN
#include <assert.h>
#include "../libs/catch.h"
#include "../Templates.h"

class ListTests
{
private:
    /*void Creation()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>();
        assert(Instance->Size() == 0);
        assert(Instance->IsEmpty());
        delete Instance;

        Instance = new List<int>(3);
        assert(Instance->Size() == 3);
        assert(!Instance->IsEmpty());
        delete Instance;

        Instance = new List<int>(arr, 6);//{2,6,8,4,2,6}
        assert(!Instance->IsEmpty());
        assert(Instance->Size() == 6);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2);
        assert(Iter.Next() && *Iter.GetValue() == 6);
        assert(Iter.Next() && *Iter.GetValue() == 8);
        assert(Iter.Next() && *Iter.GetValue() == 4);
        assert(Iter.Next() && *Iter.GetValue() == 2);
        assert(Iter.Next() && *Iter.GetValue() == 6);
        assert(Iter.Next()); //moved one after
        assert(!Iter.IsValidIterator());
        assert(Iter.AreEqual(Instance->End()));
        assert(Iter.Back() && *Iter.GetValue() == 6);
        assert(Iter.IsValidIterator());
        delete Instance;

        return;
    }

    void Iterators()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator First;
        List<int>::Iterator Second;
        List<int>* SecondInstance;
        int arr[] = {2, 6, 8, 4, 2, 6};

        assert(!First.IsValidIterator());
        Instance = new List<int>(arr, 6);//{2,6,8,4,2,6}
        SecondInstance = new List<int>(arr, 6);//{2,6,8,4,2,6}
        First = Instance->Begin();
        Second = SecondInstance->End();
        assert(Instance->IsMyIterator(First));
        assert(!Instance->IsMyIterator(Second));
        assert(!SecondInstance->IsMyIterator(First));
        assert(SecondInstance->IsMyIterator(Second));
        delete Instance;
        delete SecondInstance;

        Instance = new List<int>(arr, 6);//{2,6,8,4,2,6}
        First = Instance->Begin();
        Second = Instance->End();
        assert(Instance->IsMyIterator(First));
        assert(Instance->IsMyIterator(Second));
        assert(Second.IsGreaterThan(First));
        assert(!First.IsGreaterThan(Second));
        while (!First.AreEqual(Second))
            assert(First.Next());
        assert(First.AreEqual(Second));
        assert(Second.AreEqual(First));
        assert(First.Back() && Second.Back());
        assert(First.AreEqual(Second));
        assert(*First.GetValue() == 6 && *Second.GetValue() == 6);
        delete Instance;

        Instance = new List<int>(arr, 6);//{2,6,8,4,2,6}
        First = Instance->Begin();
        Second = Instance->End();
        assert(First.Next(4) && *First.GetValue() == 2);
        assert(Second.Back(3) && *Second.GetValue() == 4);
        First = Instance->Begin();
        Second = Instance->End();
        assert(!First.Next(12));
        assert(*First.GetValue() == 2);
        assert(!Second.Back(10));
        assert(!Second.IsValidIterator());
        assert(Second.Back() && *Second.GetValue() == 6);
        delete Instance;

        Instance = new List<int>(arr, 6);//{2,6,8,4,2,6}
        First = Instance->Begin();
        Second = Instance->End();
        assert(First.Next());
        First.SetValue(12);//{2,12,8,4,2,6}
        Second = Instance->Begin();
        assert(Second.Next() && *Second.GetValue() == 12);
        delete Instance;
    }

    void Inserting()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};
        int secondArr[] = {12, 16, 18, 14, 13};

        Instance = new List<int>(arr, 6);//{2,6,8,4,2,6}
        Iter = Instance->Begin();
        assert(Iter.Insert(4) == 1);//{2,4,6,8,4,2,6}
        assert(*Iter.GetValue() == 2);
        assert(Iter.Next() && *Iter.GetValue() == 4);
        assert(Iter.Next() && *Iter.GetValue() == 6);
        assert(Iter.Insert(secondArr, 3));//{2,4,6,12,16,18,8,4,2,6}
        assert(*Iter.GetValue() == 6);
        assert(Iter.Next() && *Iter.GetValue() == 12);
        assert(Iter.Next() && *Iter.GetValue() == 16);
        assert(Iter.Next() && *Iter.GetValue() == 18);
        assert(Iter.Next() && *Iter.GetValue() == 8);
        delete Instance;

        Instance = new List<int>(arr, 6);//{2,6,8,4,2,6}
        Iter = Instance->End();
        assert(Iter.Insert(12) == -1);
        assert(Iter.Insert(secondArr, 5) == -1);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>();
        Iter = Instance->End();
        assert(Iter.Insert(12) == -1);
        assert(Iter.Insert(secondArr, 5) == -1);
        assert(Iter.InsertBefore(14));
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 14 && Iter.Next());
        delete Instance;

        Instance = new List<int>();
        Iter = Instance->Begin(); //is also last one
        assert(Iter.Insert(14) == -1);
        assert(Iter.AreEqual(Instance->End()));
        assert(Instance->End().InsertBefore(14));
        assert(Iter.Back() && *Iter.GetValue() == 14 && Iter.Next());
        delete Instance;


        Instance = new List<int>(arr, 6);//{2,6,8,4,2,6}
        Iter = Instance->Begin();
        assert(Iter.Insert(12)==1);
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 12 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);//{2,6,8,4,2,6}
        Iter = Instance->Begin();
        assert(Iter.InsertBefore(12)==1);
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        Iter=Instance->Begin();
        assert(*Iter.GetValue() == 12 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;
    }

    void Deleting()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        assert(Instance->Delete(1) == 1);//{6, 8, 4, 2, 6}
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        assert(Instance->Delete(3) == 3);//{4, 2, 6}
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        Iter = Instance->Begin();
        assert(Instance->Delete(Iter, 3) == 3);//{2, 2, 6}
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        Iter = Instance->Begin();
        assert(Instance->Delete(Iter, 3) == 3);//{2, 2, 6}
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        Iter = Instance->Begin();
        assert(Iter.Next());
        assert(Instance->Delete(Iter, 3) == 3);//{2, 6, 6}
        assert(Iter.Back() && *Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        assert(Instance->Delete() == 6);
        assert(Instance->Size() == 0);
        assert(Instance->IsEmpty());
        delete Instance;

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        Iter = Instance->End();
        assert(Iter.DeleteBefore(2) == 2);//{2, 6, 8, 4}
        assert(!Instance->IsEmpty());
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        Iter = Instance->Begin();
        assert(Iter.DeleteBefore(3) == 0);//{2, 6, 8, 4, 2, 6}
        delete Instance;

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        Iter = Instance->End();
        try
        {
            Iter.DeleteAfter(3);
            assert(false);
        }
        catch (OutOfRangeException* e)
        {
            delete e;
            assert(true);
        }
        delete Instance;
    }

    void BackInserting()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>();
        Iter = Instance->Begin();
        Iter.InsertBefore(5);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 5);
        delete Instance;

        Instance = new List<int>();
        Iter = Instance->Begin();
        Iter.InsertBefore(5);
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 5);
        delete Instance;

        Instance = new List<int>(arr, 3);//{ 2, 6, 8 }
        Iter = Instance->End();
        Iter.InsertBefore(4);//{ 2, 6, 8, 4 }
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        delete Instance;

        //{2, 6, 8, 4, 2, 6}
        Instance = new List<int>(arr, 3);//{ 2, 6, 8 }
        Iter = Instance->End();
        Iter.InsertBefore(arr + 2, 2);//{ 2, 6, 8, 8, 4 }
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 3);//{ 2, 6, 8 }
        Iter = Instance->Begin();
        Iter.InsertBefore(arr + 2, 2);//{ 8, 4, 2, 6, 8 }
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        delete Instance;
    }

    void ToArrayTest()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int count;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        int* Array = Instance->ToArray(count);
        assert(count == 6);
        assert(*Array == 2);
        assert(*(Array + 1) == 6);
        assert(*(Array + 2) == 8);
        assert(*(Array + 3) == 4);
        assert(*(Array + 4) == 2);
        assert(*(Array + 5) == 6);
        delete Instance;
        delete [] Array;

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        int** WriteArray = Instance->ToWriteArray(count);
        assert(count == 6);
        **(WriteArray + 1) = 12;//{2, 12, 8, 4, 2, 6}
        **(WriteArray + 4) = 25;//{2, 12, 8, 4, 25, 6}
        delete [] WriteArray;
        Array = Instance->ToArray(count);
        assert(count == 6);
        assert(*Array == 2);
        assert(*(Array + 1) == 12);
        assert(*(Array + 2) == 8);
        assert(*(Array + 3) == 4);
        assert(*(Array + 4) == 25);
        assert(*(Array + 5) == 6);
        delete [] Array;
        delete Instance;
    }

    void DeleteThisTests()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        Iter = Instance->Begin();
        assert(Iter.Next() && Iter.Next());
        assert(*Iter.GetValue() == 8);
        assert(Iter.DeleteThis() == 1);//{2, 6, 4, 2, 6}
        Iter = Instance->Begin();
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(!Iter.IsValidIterator());
        assert(!Iter.Next());
        delete Instance;

        Instance = new List<int>(arr, 6);//{2, 6, 8, 4, 2, 6}
        Iter = Instance->Begin();
        assert(Iter.DeleteThis() == 1);//{ 6, 8, 4, 2, 6}
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(*Iter.GetValue() == 8 && Iter.Next());
        assert(*Iter.GetValue() == 4 && Iter.Next());
        assert(*Iter.GetValue() == 2 && Iter.Next());
        assert(*Iter.GetValue() == 6 && Iter.Next());
        assert(!Iter.IsValidIterator());
        assert(!Iter.Next());
        delete Instance;
    }

    static bool FittingCallback(const int* const First, const int* const Second)
    {
        return *First < *Second;
    }

    void BestFittingsTests()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>(arr, 6);
        Iter = Instance->Begin();
        Iter.FindBestFitting(FittingCallback);
        assert(*Iter.GetValue() == 2);
        assert(Iter.DeleteThis() == 1);
        Iter = Instance->Begin();
        Iter.FindBestFitting(FittingCallback);
        assert(*Iter.GetValue() == 2);
        assert(Iter.DeleteThis() == 1);
        Iter = Instance->Begin();
        Iter.FindBestFitting(FittingCallback);
        assert(*Iter.GetValue() == 4);
        delete Instance;
    }

    static bool Sorting(const int* const First, const int* const Second)
    {
        return *First < *Second;
    }

    void SortingTests()
    {
        using namespace Templates;
        List<int>* Instance;
        List<int>::Iterator Iter;
        int arr[] = {2, 6, 8, 4, 2, 6};

        Instance = new List<int>(arr,6);
        Instance->Sort(Sorting);
        Iter = Instance->Begin();
        assert(*Iter.GetValue()==2 && Iter.Next());
        assert(*Iter.GetValue()==2 && Iter.Next());
        assert(*Iter.GetValue()==4 && Iter.Next());
        assert(*Iter.GetValue()==6 && Iter.Next());
        assert(*Iter.GetValue()==6 && Iter.Next());
        assert(*Iter.GetValue()==8 && Iter.Next());
        delete Instance;
        return;
    }*/

public:
    static void test()
    {
        /*ListTests instane;
        instane.Creation();
        instane.Iterators();
        instane.Inserting();
        instane.Deleting();
        instane.BackInserting();
        instane.ToArrayTest();
        instane.DeleteThisTests();
        instane.BestFittingsTests();
        instane.SortingTests();*/
    }
};

TEST_CASE("List tests"){
    ListTests::test();
}