#define CATCH_CONFIG_MAIN
#include <assert.h>
#include "../libs/catch.h"
#include "../Templates.h"

using namespace Templates;

class BinarySearchTreeTests
{
private:
    static int Solve(const int *const First, const int *const Second)
    {
        return *Second - *First;
    }

    static int comparer(const void *first, const void *second)
    {
        return (*(int *) first) - (*(int *) second);
    }

    static bool DeleteBiggerThan(const int *const value, void *data)
    {
        int val = *((int *) data);
        return *value > val;
    }

    static void ContainTest()
    {
        BinarySearchTree<int> *Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 10; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            Instance->Insert(val);
        }
        assert(Instance->Size() == 10);
        for (int a = 0; a < 15; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            assert(Instance->Contain(val) == (a < 10));
        }
        delete Instance;
    }

    static void CopyConstructorTest()
    {
        BinarySearchTree<int> *Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 10; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            Instance->Insert(val);
        }
        BinarySearchTree<int> *Second = new BinarySearchTree<int>(*Instance);
        assert(Instance->Size() == 10);
        for (int a = 0; a < 15; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            assert(Instance->Contain(val) == (a < 10));
        }
        assert(Second->Size() == 10);
        for (int a = 0; a < 15; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            assert(Second->Contain(val) == (a < 10));
        }
        delete Second;
        delete Instance;
    }

    static void OneElementDeleteTests()
    {
        BinarySearchTree<int> *Instance = NULL;
        int *Array = NULL;
        int count;

        //delete leaf
        /**
         *               30
         *               /
         *              10
         *             /  \
         *            5    15
         *           / \    \
         *          3   7    18
         *         /\  / \   / \
         *        1 4  6 8  17 20  <----DELETE
         */
        int DeleteLeafTestBase[13] = {30, 10, 5, 15, 3, 7, 18, 1, 4, 6, 8, 17, 20};
        int DeleteLeafTestResult[12] = {1, 3, 4, 5, 6, 7, 8, 10, 15, 17, 18, 30};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 13; a++)
            Instance->Insert(DeleteLeafTestBase[a]);
        assert(Instance->Size() == 13);
        assert(Instance->Delete(20) == 1);
        assert(Instance->Size() == 12);
        Array = Instance->ToArray(count);
        assert(count == 12);
        for (int a = 0; a < count; a++)
            assert(Array[a] == DeleteLeafTestResult[a]);
        delete Instance;
        delete [] (Array);

        //delete with left children null
        /**
         *               30
         *               /
         *              10
         *             /  \
         *            5    15 <----DELETE
         *           / \    \
         *          3   7    18
         *         /\  / \   / \
         *        1 4  6 8  17 20
         */
        int DeleteLeftChildrenNullBase[13] = {30, 10, 5, 15, 3, 7, 18, 1, 4, 6, 8, 17, 20};
        int DeleteLeftChildrenNullResult[12] = {1, 3, 4, 5, 6, 7, 8, 10, 17, 18, 20, 30};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 13; a++)
            Instance->Insert(DeleteLeftChildrenNullBase[a]);
        assert(Instance->Size() == 13);
        assert(Instance->Delete(15) == 1);
        assert(Instance->Size() == 12);
        Array = Instance->ToArray(count);
        assert(count == 12);
        for (int a = 0; a < count; a++)
            assert(Array[a] == DeleteLeftChildrenNullResult[a]);
        delete Instance;
        delete [] (Array);

        //delete node with right children null
        /**
         *                90
         *               /  \
         *             50    95
         *            /  \
         *          30    60
         *         /  \     \
         *       15    40    65    <----DELETE 15
         *      /       \    / \
         *    10         41 62  67
         *    /\          \
         *   5  12         42
         */
        // {5, 10, 12, 15, 30, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        int DeleteRightChildrenNullBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        int DeleteRightChildrenNullResult[14] = {5, 10, 12, 30, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 15; a++)
            Instance->Insert(DeleteRightChildrenNullBase[a]);
        assert(Instance->Size() == 15);
        assert(Instance->Delete(15) == 1);
        assert(Instance->Size() == 14);
        Array = Instance->ToArray(count);
        assert(count == 14);
        for (int a = 0; a < count; a++)
            assert(Array[a] == DeleteRightChildrenNullResult[a]);
        delete Instance;
        delete [] (Array);

        //left rotate test
        /**
         *               30
         *               /
         *              10 <----DELETE
         *             /  \
         *            5    15
         *           / \    \
         *          3   7    18
         *         /\  / \   / \
         *        1 4  6 8  17 20
         */
        int LeftRotateTestBase[13] = {30, 10, 5, 15, 3, 7, 18, 1, 4, 6, 8, 17, 20};
        int LeftRotateTestResult[12] = {1, 3, 4, 5, 6, 7, 8, 15, 17, 18, 20, 30};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 13; a++)
            Instance->Insert(LeftRotateTestBase[a]);
        assert(Instance->Size() == 13);
        assert(Instance->Delete(10) == 1);
        assert(Instance->Size() == 12);
        Array = Instance->ToArray(count);
        assert(count == 12);
        for (int a = 0; a < count; a++)
            assert(Array[a] == LeftRotateTestResult[a]);
        delete Instance;
        delete [] (Array);

        //right rotate test
        /**
         *                90
         *               /  \
         *             50    95
         *            /  \
         *          30    60  <----DELETE 30
         *         /  \     \
         *       15    40    65
         *      /       \    / \
         *    10         41 62  67
         *    /\          \
         *   5  12         42
         */
        // {10, 12, 15, 30, 40, 41, 42, 5, 50, 60, 62, 65, 67, 90, 95};
        int RightRotateTestBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        int RightRotateTestResult[14] = {5, 10, 12, 15, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 15; a++)
            Instance->Insert(RightRotateTestBase[a]);
        assert(Instance->Delete(30) == 1);
        Array = Instance->ToArray(count);
        assert(count == 14);
        for (int a = 0; a < count; a++)
            assert(Array[a] == RightRotateTestResult[a]);
        delete Instance;
        delete [] (Array);

        //Rotate in tree
        /**
         *                90
         *               /  \
         *             50    95 <----DELETE 50
         *            /  \
         *          30    60
         *         /  \     \
         *       15    40    65
         *      /       \    / \
         *    10         41 62  67
         *    /\          \
         *   5  12         42
         */
        // {5, 10, 12, 15, 30, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        int RotateInTreeBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        int RotateInTreeResult[14] = {5, 10, 12, 15, 30, 40, 41, 42, 60, 62, 65, 67, 90, 95};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 15; a++)
            Instance->Insert(RotateInTreeBase[a]);
        assert(Instance->Delete(50) == 1);
        Array = Instance->ToArray(count);
        assert(count == 14);
        for (int a = 0; a < count; a++)
            assert(Array[a] == RotateInTreeResult[a]);
        delete Instance;
        delete [] (Array);


        //Delete in tree
        /**
         *                    50
         *               /          \
         *             20            70  <---- DELETE 70
         *         /       \      /      \
         *        10       30    60      80
         *       /  \     /  \  /  \    /  \
         *      5   15   25 35  55 65  75  85
         */
        // {5, 10, 15, 20, 25, 30, 35, 50, 55, 60, 65, 70, 75, 80, 85};
        int DeletInTreeFirstBase[15] = {50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 35, 55, 65, 75, 85};
        int DeletInTreeFirstResult[14] = {5, 10, 15, 20, 25, 30, 35, 50, 55, 60, 65, 75, 80, 85};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 15; a++)
            Instance->Insert(DeletInTreeFirstBase[a]);
        assert(Instance->Delete(70) == 1);
        Array = Instance->ToArray(count);
        assert(count == 14);
        for (int a = 0; a < count; a++)
            assert(Array[a] == DeletInTreeFirstResult[a]);
        delete Instance;
        delete [] (Array);

        //Delete root
        /**
         *                    50         <---- DELETE 50
         *               /          \
         *             20            70
         *         /       \      /      \
         *        10       30    60      80
         *       /  \     /  \  /  \    /  \
         *      5   15   25 35  55 65  75  85
         */
        // {5, 10, 15, 20, 25, 30, 35, 50, 55, 60, 65, 70, 75, 80, 85};
        int DeleRootInTreeBase[15] = {50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 35, 55, 65, 75, 85};
        int DeleRootInTreeResult[14] = {5, 10, 15, 20, 25, 30, 35, 55, 60, 65, 70, 75, 80, 85};
        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 15; a++)
            Instance->Insert(DeleRootInTreeBase[a]);
        assert(Instance->Delete(50) == 1);
        Array = Instance->ToArray(count);
        assert(count == 14);
        for (int a = 0; a < count; a++)
            assert(Array[a] == DeleRootInTreeResult[a]);
        delete Instance;
        delete [] (Array);
    }

    static void ToArrayTest()
    {
        BinarySearchTree<int> *Instance = new BinarySearchTree<int>(Solve);
        int HelpArray[] = {50, 538, 1037, 1525, 2024, 2512, 3011, 3499, 3510, 3998};
        int SecondHelpInstance[100];
        int *Array = NULL;
        int Count;

        for (int a = 0; a < 10; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            Instance->Insert(val);
        }
        Array = Instance->ToArray(Count); // {50, 538, 1037, 1525, 2024, 2512, 3011, 3499, 3510, 3998 }
        for (int a = 0; a < 10; a++)
            assert(Array[a] == HelpArray[a]);
        delete [] (Array);
        delete Instance;

        Instance = new BinarySearchTree<int>(Solve);
        for (int a = 0; a < 100; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            Instance->Insert(val);
            SecondHelpInstance[a] = val;
        }
        Array = Instance->ToArray(Count);
        qsort(&SecondHelpInstance, 100, sizeof(int), comparer);
        for (int a = 0; a < 10; a++)
            assert(Array[a] == SecondHelpInstance[a]);
        delete [] (Array);
        delete Instance;
    }

    static void MultipleDeletion()
    {
        BinarySearchTree<int> *Instance = NULL;
        int count;
        int *Array;
        // {50, 538, 1037, 1525, 2024, 2512, 3011, 3499, 3510, 3998};

        //delete empty
        Instance = new BinarySearchTree<int>(Solve);
        count = 2000;
        assert(Instance->Size() == 0);
        assert(Instance->Delete(DeleteBiggerThan, &count) == 0);
        assert(Instance->Size() == 0);
        delete Instance;

        //delete bigger than 2000
        Instance = new BinarySearchTree<int>(Solve);
        int ResultSecond[] = {50, 538, 1037, 1525};
        for (int a = 0; a < 10; a++)
        {
            int val = (a * 7907 + 3499) % 4447;
            Instance->Insert(val);
        }
        assert(Instance->Size() == 10);
        count = 2000;
        assert(Instance->Delete(DeleteBiggerThan, &count) == 6);
        assert(Instance->Size() == 4);
        Array = Instance->ToArray(count);
        assert(count == 4);
        for (int a = 0; a < 4; a++)
            assert(Array[a] == ResultSecond[a]);
        delete Instance;
        delete [] (Array);
    }

    static void GetTest()
    {
        /**
         *                90
         *               /  \
         *             50    95
         *            /  \
         *          30    60
         *         /  \     \
         *       15    40    65
         *      /       \    / \
         *    10         41 62  67
         *    /\          \
         *   5  12         42
         */
        // {5, 10, 12, 15, 30, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        int BaseArray[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        BinarySearchTree<int> *Instance = NULL;
        int ToFind;
        int* ToGet;

        Instance = new BinarySearchTree<int>(Solve);
        Instance->Insert(BaseArray, 15);
        ToFind = 15;
        assert(Instance->Get(ToFind, ToGet));
        assert(*ToGet == 15);
        delete Instance;

        Instance = new BinarySearchTree<int>(Solve);
        Instance->Insert(BaseArray, 15);
        ToFind = 43;
        assert(!Instance->Get(ToFind, ToGet));
        delete Instance;
    }

    static void NotDuplicateTests()
    {
        /**
         *                90
         *               /  \
         *             50    95
         *            /  \
         *          30    60
         *         /  \     \
         *       15    40    65
         *      /       \    / \
         *    10         41 62  67
         *    /\          \
         *   5  12         42
         */
        // {5, 10, 12, 15, 30, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        int BaseArray[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        BinarySearchTree<int, false> *Instance = NULL;
        int ToInsert;

        Instance = new BinarySearchTree<int, false>(Solve);
        Instance->Insert(BaseArray, 15);
        assert(Instance->Size() == 15);
        ToInsert = 62;
        assert(Instance->Insert(ToInsert) == 0);
        assert(Instance->Size() == 15);
        ToInsert = 43;
        assert(Instance->Insert(ToInsert) == 1);
        assert(Instance->Size() == 16);
        delete Instance;


        Instance = new BinarySearchTree<int, false>(Solve);
        Instance->Insert(BaseArray, 10);
        assert(Instance->Size() == 10);
        assert(Instance->Insert(BaseArray, 5) == 0);
        assert(Instance->Size() == 10);
        assert(Instance->Insert(BaseArray + 10, 5) == 5);
        assert(Instance->Size() == 15);
        delete Instance;

        int TempArray[5] = {1, 2, 3, 1, 2};
        Instance = new BinarySearchTree<int, false>(Solve);
        assert(Instance->Insert(TempArray, 5) == 3);
        assert(Instance->Size() == 3);
        for (int a = 0; a < 3; a++)
            Instance->Contain(TempArray[a]);
        delete Instance;
    }

    struct CustomClass
    {
        int Key;
        int Value;
    };

    static int CompareCustomClass(const CustomClass *const First, const CustomClass *const Second)
    {
        return Second->Key - First->Key;
    }

    static void GetOrCreateIntTests()
    {
        BinarySearchTree<int, false> *Instance = NULL;
        int array[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 17};
        int *CreatedArray;
        int count;
        int ToInsert;
        int* ToGet = NULL;

        Instance = new BinarySearchTree<int, false>(Solve);
        assert(Instance->Insert(array, 10) == 9);
        assert(Instance->Size() == 9);
        ToInsert = 15;
        assert(Instance->GetOrCreate(ToInsert, ToGet) == 0);
        assert(*ToGet == 15);
        delete Instance;

        Instance = new BinarySearchTree<int, false>(Solve);
        assert(Instance->Insert(array, 10) == 9);
        assert(Instance->Size() == 9);
        ToInsert = 19;
        assert(Instance->GetOrCreate(ToInsert, ToGet) == 1);
        assert(*ToGet == 19);
        assert(Instance->Size() == 10);
        delete Instance;

        Instance = new BinarySearchTree<int, false>(Solve);
        assert(Instance->Insert(array, 10) == 9);
        assert(Instance->Size() == 9);
        ToInsert = 19;
        assert(Instance->GetOrCreate(ToInsert, ToGet) == 1);
        assert(*ToGet == 19);
        assert(Instance->Size() == 10);
        assert(Instance->GetOrCreate(ToInsert, ToGet) == 0);
        assert(Instance->Size() == 10);
        assert(*ToGet == 19);
        CreatedArray = Instance->ToArray(count);
        assert(count == 10);
        for (int a = 0; a < 9; a++)
            assert(CreatedArray[a] == array[a]);
        assert(CreatedArray[9] == 19);
        delete Instance;
        delete [] (CreatedArray);
    }

    static void GetOrCreateCustomClassTests()
    {
        BinarySearchTree<CustomClass, false> *Instance = NULL;
        int count;
        CustomClass BaseArrayThrteen[13] = {{30, 1},
                                            {10, 2},
                                            {5,  3},
                                            {15, 4},
                                            {3,  5},
                                            {7,  6},
                                            {18, 7},
                                            {1,  8},
                                            {4,  9},
                                            {6,  10},
                                            {8,  11},
                                            {17, 12},
                                            {20, 13}};
        int AfterSorted[14] = {1, 3, 4, 5, 6, 7, 8, 10, 15, 17, 18, 20, 25, 30};
        CustomClass ToCreate;
        CustomClass* ToGet;
        CustomClass *CreatedArray;

        /**
         *               30
         *               /
         *              10
         *             /  \
         *            5    15
         *           / \    \
         *          3   7    18
         *         /\  / \   / \
         *        1 4  6 8  17 20
         */

        Instance = new BinarySearchTree<CustomClass, false>(CompareCustomClass);
        assert(Instance->Insert(BaseArrayThrteen, 13) == 13);
        assert(Instance->Size() == 13);
        ToCreate.Key = 15;
        assert(Instance->GetOrCreate(ToCreate, ToGet) == 0);
        assert(Instance->Size() == 13);
        assert(ToGet->Key == 15);
        assert(ToGet->Value == 4);
        delete Instance;

        Instance = new BinarySearchTree<CustomClass, false>(CompareCustomClass);
        assert(Instance->Insert(BaseArrayThrteen, 13) == 13);
        assert(Instance->Size() == 13);
        ToCreate.Key = 25;
        assert(Instance->GetOrCreate(ToCreate, ToGet) == 1);
        assert(Instance->Size() == 14);
        assert(ToGet->Key == 25);
        ToGet->Value=0;
        assert(Instance->GetOrCreate(ToCreate, ToGet) == 0);
        assert(Instance->Size() == 14);
        assert(ToGet->Key == 25);
        assert(ToGet->Value == 0);
        CreatedArray = Instance->ToArray(count);
        assert(count==14);
        for (int a = 0; a < count; a++)
            assert(CreatedArray[a].Key == AfterSorted[a]);
        delete Instance;
        delete [] (CreatedArray);
    }

    static void GetAndDeleteTests()
    {
        BinarySearchTree<CustomClass> *Instance = NULL;
        int count;
        CustomClass BaseArrayThrteen[13] = {{30, 1},
                                            {10, 2},
                                            {5,  3},
                                            {15, 4},
                                            {3,  5},
                                            {7,  6},
                                            {18, 7},
                                            {1,  8},
                                            {4,  9},
                                            {6,  10},
                                            {8,  11},
                                            {17, 12},
                                            {20, 13}};
        CustomClass ToDelete;
        CustomClass ToGet;
        CustomClass *CreatedArray;

        //delete leaf
        /**
         *               30
         *               /
         *              10
         *             /  \
         *            5    15
         *           / \    \
         *          3   7    18
         *         /\  / \   / \
         *        1 4  6 8  17 20  <----DELETE
         */
        int DeleteLeafTestBase[13] = {30, 10, 5, 15, 3, 7, 18, 1, 4, 6, 8, 17, 20};
        int DeleteLeafTestResult[12] = {1, 3, 4, 5, 6, 7, 8, 10, 15, 17, 18, 30};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        assert(Instance->Insert(BaseArrayThrteen, 13) == 13);
        assert(Instance->Size() == 13);
        ToDelete.Key = 20;
        assert(Instance->GetAndDelete(ToDelete, ToGet) == 1);
        assert(ToGet.Key == 20);
        assert(ToGet.Value == 13);
        assert(Instance->Size() == 12);
        CreatedArray = Instance->ToArray(count);
        assert(count == 12);
        for (int a = 0; a < count; a++)
        {
            assert(CreatedArray[a].Key == DeleteLeafTestResult[a]);
            int RealValue = -2;
            for (int b = 0; b < 13; b++)
                if (DeleteLeafTestBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            assert(CreatedArray[a].Value == RealValue + 1);
        }
        delete Instance;
        delete [] (CreatedArray);

        //delete with left children null
        /**
         *               30
         *               /
         *              10
         *             /  \
         *            5    15 <----DELETE
         *           / \    \
         *          3   7    18
         *         /\  / \   / \
         *        1 4  6 8  17 20
         */
        int DeleteLeftChildrenNullBase[13] = {30, 10, 5, 15, 3, 7, 18, 1, 4, 6, 8, 17, 20};
        int DeleteLeftChildrenNullResult[12] = {1, 3, 4, 5, 6, 7, 8, 10, 17, 18, 20, 30};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        for (int a = 0; a < 13; a++)
            Instance->Insert(BaseArrayThrteen[a]);
        assert(Instance->Size() == 13);
        ToDelete.Key = 15;
        assert(Instance->GetAndDelete(ToDelete, ToGet) == 1);
        assert(Instance->Size() == 12);
        assert(ToGet.Key == 15);
        assert(ToGet.Value == 4);
        CreatedArray = Instance->ToArray(count);
        assert(count == 12);
        for (int a = 0; a < count; a++)
        {
            assert(CreatedArray[a].Key == DeleteLeftChildrenNullResult[a]);
            int RealValue = -2;
            for (int b = 0; b < 13; b++)
                if (DeleteLeftChildrenNullBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            assert(CreatedArray[a].Value == RealValue + 1);
        }
        delete Instance;
        delete [] (CreatedArray);

        //delete node with right children null
        /**
         *                90
         *               /  \
         *             50    95
         *            /  \
         *          30    60
         *         /  \     \
         *       15    40    65    <----DELETE 15
         *      /       \    / \
         *    10         41 62  67
         *    /\          \
         *   5  12         42
         */
        // {5, 10, 12, 15, 30, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        CustomClass BaseFifteen[15] = {{90, 0},
                                       {50, 1},
                                       {95, 2},
                                       {30, 3},
                                       {60, 4},
                                       {15, 5},
                                       {40, 6},
                                       {65, 7},
                                       {10, 8},
                                       {41, 9},
                                       {62, 10},
                                       {67, 11},
                                       {5,  12},
                                       {12, 13},
                                       {42, 14}};
        int DeleteRightChildrenNullBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        int DeleteRightChildrenNullResult[14] = {5, 10, 12, 30, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        assert(Instance->Insert(BaseFifteen, 15) == 15);
        assert(Instance->Size() == 15);
        ToDelete.Key = 15;
        assert(Instance->GetAndDelete(ToDelete, ToGet) == 1);
        assert(ToGet.Key == 15);
        assert(ToGet.Value == 5);
        assert(Instance->Size() == 14);
        CreatedArray = Instance->ToArray(count);
        assert(count == 14);
        for (int a = 0; a < count; a++)
        {
            assert(CreatedArray[a].Key == DeleteRightChildrenNullResult[a]);
            int RealValue = -2;
            for (int b = 0; b < 15; b++)
                if (DeleteRightChildrenNullBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            assert(CreatedArray[a].Value == RealValue);
        }
        delete Instance;
        delete [] (CreatedArray);

        //left rotate test
        /**
         *               30
         *               /
         *              10 <----DELETE
         *             /  \
         *            5    15
         *           / \    \
         *          3   7    18
         *         /\  / \   / \
         *        1 4  6 8  17 20
         */
        int LeftRotateTestBase[13] = {30, 10, 5, 15, 3, 7, 18, 1, 4, 6, 8, 17, 20};
        int LeftRotateTestResult[12] = {1, 3, 4, 5, 6, 7, 8, 15, 17, 18, 20, 30};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        assert(Instance->Insert(BaseArrayThrteen, 13));
        assert(Instance->Size() == 13);
        ToDelete.Key = 10;
        assert(Instance->GetAndDelete(ToDelete, ToGet) == 1);
        assert(Instance->Size() == 12);
        assert(ToGet.Key == 10);
        assert(ToGet.Value == 2);
        CreatedArray = Instance->ToArray(count);
        assert(count == 12);
        for (int a = 0; a < count; a++)
        {
            assert(CreatedArray[a].Key == LeftRotateTestResult[a]);
            int RealValue = -2;
            for (int b = 0; b < 13; b++)
                if (LeftRotateTestBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            assert(CreatedArray[a].Value == RealValue + 1);
        }
        delete Instance;
        delete [] (CreatedArray);

        //right rotate test
        /**
         *                90
         *               /  \
         *             50    95
         *            /  \
         *          30    60  <----DELETE 30
         *         /  \     \
         *       15    40    65
         *      /       \    / \
         *    10         41 62  67
         *    /\          \
         *   5  12         42
         */
        // {10, 12, 15, 30, 40, 41, 42, 5, 50, 60, 62, 65, 67, 90, 95};
        int RightRotateTestBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        int RightRotateTestResult[14] = {5, 10, 12, 15, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        assert(Instance->Insert(BaseFifteen, 15) == 15);
        ToDelete.Key = 30;
        assert(Instance->GetAndDelete(ToDelete, ToGet) == 1);
        assert(ToGet.Key == 30);
        assert(ToGet.Value == 3);
        CreatedArray = Instance->ToArray(count);
        assert(count == 14);
        for (int a = 0; a < count; a++)
        {
            assert(CreatedArray[a].Key == RightRotateTestResult[a]);
            int RealValue = -2;
            for (int b = 0; b < 15; b++)
                if (RightRotateTestBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            assert(CreatedArray[a].Value == RealValue);
        }
        delete Instance;
        delete [] (CreatedArray);

        //Rotate in tree
        /**
         *                90
         *               /  \
         *             50    95 <----DELETE 50
         *            /  \
         *          30    60
         *         /  \     \
         *       15    40    65
         *      /       \    / \
         *    10         41 62  67
         *    /\          \
         *   5  12         42
         */
        // {5, 10, 12, 15, 30, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        int RotateInTreeBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        int RotateInTreeResult[14] = {5, 10, 12, 30, 40, 41, 42, 50, 60, 62, 65, 67, 90, 95};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        assert(Instance->Insert(BaseFifteen, 15) == 15);
        ToDelete.Key = 15;
        assert(Instance->GetAndDelete(ToDelete, ToGet) == 1);
        assert(ToGet.Key == 15);
        assert(ToGet.Value == 5);
        CreatedArray = Instance->ToArray(count);
        assert(count == 14);
        for (int a = 0; a < count; a++)
        {
            assert(CreatedArray[a].Key == RotateInTreeResult[a]);
            int RealValue = -2;
            for (int b = 0; b < 15; b++)
                if (RotateInTreeBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            assert(CreatedArray[a].Value == RealValue);
        }
        delete Instance;
        delete [] (CreatedArray);


        //Delete in tree
        /**
         *                    50
         *               /          \
         *             20            70  <---- DELETE 70
         *         /       \      /      \
         *        10       30    60      80
         *       /  \     /  \  /  \    /  \
         *      5   15   25 35  55 65  75  85
         */
        // {5, 10, 15, 20, 25, 30, 35, 50, 55, 60, 65, 70, 75, 80, 85};
        CustomClass FullTree[15] = {{50, 0},
                                    {20, 1},
                                    {70, 2},
                                    {10, 3},
                                    {30, 4},
                                    {60, 5},
                                    {80, 6},
                                    {5,  7},
                                    {15, 8},
                                    {25, 9},
                                    {35, 10},
                                    {55, 11},
                                    {65, 12},
                                    {75, 13},
                                    {85, 14}};
        int DeletInTreeFirstBase[15] = {50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 35, 55, 65, 75, 85};
        int DeletInTreeFirstResult[14] = {5, 10, 15, 20, 25, 30, 35, 50, 55, 60, 65, 75, 80, 85};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        assert(Instance->Insert(FullTree, 15) == 15);
        ToDelete.Key = 70;
        assert(Instance->GetAndDelete(ToDelete, ToGet) == 1);
        assert(ToGet.Key == 70);
        assert(ToGet.Value == 2);
        CreatedArray = Instance->ToArray(count);
        assert(count == 14);
        for (int a = 0; a < count; a++)
        {
            assert(CreatedArray[a].Key == DeletInTreeFirstResult[a]);
            int RealValue = -2;
            for (int b = 0; b < 15; b++)
                if (DeletInTreeFirstBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            assert(CreatedArray[a].Value == RealValue);
        }
        delete Instance;
        delete [] (CreatedArray);

        //Delete root
        /**
         *                    50         <---- DELETE 50
         *               /          \
         *             20            70
         *         /       \      /      \
         *        10       30    60      80
         *       /  \     /  \  /  \    /  \
         *      5   15   25 35  55 65  75  85
         */
        // {5, 10, 15, 20, 25, 30, 35, 50, 55, 60, 65, 70, 75, 80, 85};
        int DeleRootInTreeBase[15] = {50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 35, 55, 65, 75, 85};
        int DeleRootInTreeResult[14] = {5, 10, 15, 20, 25, 30, 35, 55, 60, 65, 70, 75, 80, 85};
        Instance = new BinarySearchTree<CustomClass>(CompareCustomClass);
        assert(Instance->Insert(FullTree, 15) == 15);
        ToDelete.Key = 50;
        assert(Instance->GetAndDelete(ToDelete, ToGet) == 1);
        assert(ToGet.Key == 50);
        assert(ToGet.Value == 0);
        CreatedArray = Instance->ToArray(count);
        assert(count == 14);
        for (int a = 0; a < count; a++)
        {
            assert(CreatedArray[a].Key == DeleRootInTreeResult[a]);
            int RealValue = -2;
            for (int b = 0; b < 15; b++)
                if (DeleRootInTreeBase[b] == CreatedArray[a].Key)
                    RealValue = b;
            assert(CreatedArray[a].Value == RealValue);
        }
        delete Instance;
        delete [] (CreatedArray);
    }

    static void CopyTests()
    {
        BinarySearchTree<int> *Instance = NULL;

        //right rotate test
        /**
         *                90
         *               /  \
         *             50    95
         *            /  \
         *          30    60
         *         /  \     \
         *       15    40    65
         *      /       \    / \
         *    10         41 62  67
         *    /\          \
         *   5  12         42
         */
        // {10, 12, 15, 30, 40, 41, 42, 5, 50, 60, 62, 65, 67, 90, 95};
        int RightRotateTestBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        Instance = new BinarySearchTree<int>(Solve);
        for(int i=0;i<15;i++)
            Instance->Insert(RightRotateTestBase[i]);
        BinarySearchTree<int> secondInstance = *Instance;
        int countFirst;
        int countSecond;
        int* ArrayFirst = Instance->ToArray(countFirst);
        int* ArraySecond = secondInstance.ToArray(countSecond);
        assert(countFirst == countSecond);
        for(int a=0;a<countFirst;a++)
            assert(ArrayFirst[a]==ArraySecond[a]);
        delete Instance;
        delete [] (ArrayFirst);
        delete [] (ArraySecond);
        return;
    }

    static bool filter(const int* const val,void *data)
    {
        return *val < 50;
    }

    static void FilterTests()
    {
        BinarySearchTree<int> *Instance = NULL;

        //right rotate test
        /**
         *                90
         *               /  \
         *             50    95
         *            /  \
         *          30    60
         *         /  \     \
         *       15    40    65
         *      /       \    / \
         *    10         41 62  67
         *    /\          \
         *   5  12         42
         */
        // {5, 10, 12, 15, 30, 40, 41, 42, 5, 50, 60, 62, 65, 67, 90, 95};
        int RightRotateTestBase[15] = {90, 50, 95, 30, 60, 15, 40, 65, 10, 41, 62, 67, 5, 12, 42};
        Instance = new BinarySearchTree<int>(Solve);
        for(int i=0;i<15;i++)
            Instance->Insert(RightRotateTestBase[i]);
        Vector<int> lower = Instance->Get(filter);
        assert(lower.Size() == 8);
        delete Instance;
        return;
    }

public:
    static void tests()
    {
        CopyConstructorTest();

        ContainTest();

        ToArrayTest();

        OneElementDeleteTests();

        MultipleDeletion();

        GetTest();

        NotDuplicateTests();

        GetOrCreateIntTests();

        GetAndDeleteTests();

        GetOrCreateCustomClassTests();

        CopyTests();

        FilterTests();
    }
};

TEST_CASE("Binary search tree tests"){
    BinarySearchTreeTests::tests();
}