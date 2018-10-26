#define CATCH_CONFIG_MAIN
#include <assert.h>
#include "../libs/catch.h"
#include "../Templates.h"

using namespace Templates;

class StackTests
{
private:
    static void CreatingTests()
    {
        Stack<int>* Instance;
        int val;
        int array[4] = {1, 5, 8, 9};

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val));
        assert(val == 9);
        delete Instance;
    }

    static void CloneAndAssignmentTests()
    {
        Stack<int>* Instance;
        Stack<int>* SecondInstance;
        int val;
        int array[4] = {1, 5, 8, 9};

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        SecondInstance = new Stack<int>(*Instance);
        assert(SecondInstance->IsEmpty());
        assert(!SecondInstance->Pop(val));
        delete Instance;
        delete SecondInstance;

        Instance = new Stack<int>(array, 4);
        SecondInstance = new Stack<int>(*Instance);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val));
        assert(val == 9);
        assert(!SecondInstance->IsEmpty());
        assert(SecondInstance->Pop(val));
        assert(val == 9);
        assert(Instance->Pop(val));
        assert(val == 8);
        assert(SecondInstance->Pop(val));
        assert(val == 8);
        delete Instance;
        delete SecondInstance;

        //assignment
        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        SecondInstance = new Stack<int>(array, 4);
        *SecondInstance = *Instance;
        assert(SecondInstance->IsEmpty());
        assert(!SecondInstance->Pop(val));
        delete Instance;
        delete SecondInstance;

        Instance = new Stack<int>(array, 4);
        SecondInstance = new Stack<int>(array, 2);
        *SecondInstance = *Instance;
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val));
        assert(val == 9);
        assert(!SecondInstance->IsEmpty());
        assert(SecondInstance->Pop(val));
        assert(val == 9);
        assert(Instance->Pop(val));
        assert(val == 8);
        assert(SecondInstance->Pop(val));
        assert(val == 8);
        delete Instance;
        delete SecondInstance;

        Instance = new Stack<int>(array, 4);
        SecondInstance = new Stack<int>();
        *SecondInstance = *Instance;
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val));
        assert(val == 9);
        assert(!SecondInstance->IsEmpty());
        assert(SecondInstance->Pop(val));
        assert(val == 9);
        assert(Instance->Pop(val));
        assert(val == 8);
        assert(SecondInstance->Pop(val));
        assert(val == 8);
        delete Instance;
        delete SecondInstance;
    }

    static void PushAndPopTests()
    {
        Stack<int>* Instance;
        int val;
        int array[4] = {1, 5, 8, 9};

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val) && val == 9);
        assert(Instance->Pop(val) && val == 8);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        assert(Instance->Push(5) == 1);
        assert(Instance->Pop(val) && val == 5);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Push(16) == 1);
        assert(Instance->Pop(val) && val == 16);
        assert(Instance->Pop(val) && val == 9);
        assert(Instance->Pop(val) && val == 8);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val) && val == 9);
        assert(Instance->Pop(val) && val == 8);
        assert(Instance->Push(16) == 1);
        assert(Instance->Pop(val) && val == 16);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val) && val == 9);
        assert(Instance->Pop(val) && val == 8);
        assert(Instance->Push(16) == 1);
        assert(Instance->Push(27) == 1);
        assert(Instance->Pop(val) && val == 27);
        assert(Instance->Pop(val) && val == 16);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        assert(Instance->Push(array, 4) == 4);
        assert(Instance->Pop(val) && val == 9);
        assert(Instance->Pop(val) && val == 8);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Pop(val) && val == 9);
        assert(Instance->Pop(val) && val == 8);
        assert(Instance->Push(array, 2) == 2);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(Instance->Pop(val) && val == 5);
        assert(Instance->Pop(val) && val == 1);
        assert(!Instance->Pop(val));
        delete Instance;
    }

    static void IteratorTests()
    {
        Stack<int>* Instance;
        int array[4] = {2, 5, 6, 8};
        Stack<int>::Iterator Iterator;

        Instance = new Stack<int>(array,4);
        Iterator = Instance->Begin();
        assert(Iterator.IsValidIterator());
        assert(*Iterator.GetValue()==8);
        assert(Iterator.Next());
        assert(*Iterator.GetValue()==6);
        assert(Iterator.Next());
        assert(*Iterator.GetValue()==5);
        assert(Iterator.Next());
        assert(*Iterator.GetValue()==2);
        assert(!Iterator.Next());
        delete Instance;

        Instance = new Stack<int>(array,4);
        Iterator = Instance->Begin();
        assert(Iterator.IsValidIterator());
        assert(*Iterator.GetValue()==8);
        assert(Iterator.Next(4));
        assert(!Iterator.Next());
        delete Instance;

        Instance = new Stack<int>(array,4);
        Iterator = Instance->Begin();
        assert(Iterator.IsValidIterator());
        assert(*Iterator.GetValue()==8);
        assert(!Iterator.Next(5));
        assert(*Iterator.GetValue()==8);
        assert(Iterator.Next());
        assert(*Iterator.GetValue()==6);
        assert(Iterator.Next());
        assert(*Iterator.GetValue()==5);
        assert(Iterator.Next());
        assert(*Iterator.GetValue()==2);
        assert(!Iterator.Next());
        delete Instance;
    }

    static void ToArrayTests()
    {
        Stack<int>* Instance;
        int val;
        int array[4] = {2, 5, 6, 8};
        int* NextArray;

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        NextArray = Instance->ToArray(val);
        assert(NextArray == nullptr);
        delete [] NextArray;
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        NextArray = Instance->ToArray(val);
        assert(NextArray != nullptr && val == 4);
        assert(NextArray[0] == 8 && NextArray[1] == 6 && NextArray[2] == 5 && NextArray[3] == 2);
        delete [] (NextArray);
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(Instance->Push(15) == 1);
        assert(!Instance->IsEmpty());
        NextArray = Instance->ToArray(val);
        assert(NextArray != nullptr && val == 5);
        assert(NextArray[0]==15 && NextArray[1] == 8 && NextArray[2] == 6 && NextArray[3] == 5 && NextArray[4] == 2);
        delete [] (NextArray);
        delete Instance;

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(Instance->Push(array,4)==4);
        NextArray = Instance->ToArray(val);
        assert(NextArray != nullptr && val == 4);
        assert(NextArray[0] == 8 && NextArray[1] == 6 && NextArray[2] == 5 && NextArray[3] == 2);
        delete [] (NextArray);
        delete Instance;
    }

    static void ClearTests()
    {
        Stack<int>* Instance;
        int val;
        int array[4] = {2, 5, 6, 8};

        Instance = new Stack<int>();
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        assert(Instance->Clear() == 0);
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>(array, 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Clear() == 4);
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;

        Instance = new Stack<int>();
        assert(Instance->Push(array, 4) == 4);
        assert(!Instance->IsEmpty());
        assert(Instance->Clear() == 4);
        assert(Instance->IsEmpty());
        assert(!Instance->Pop(val));
        delete Instance;
    }

public:
    static void test()
    {
        CreatingTests();
        CloneAndAssignmentTests();
        PushAndPopTests();
        IteratorTests();
        ToArrayTests();
        ClearTests();
    }
};

TEST_CASE("Stack tests"){
    StackTests::test();
}