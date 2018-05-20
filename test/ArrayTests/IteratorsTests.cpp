#define CATCH_CONFIG_MAIN
#include "../../libs/catch.h"
#define private public
#include "../../Templates.h"
using namespace Templates;

int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
Array<int>::Iterator iter;



class CreationTests
{

    static void IteratorsTests()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;
        Array<int>::Iterator iter;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        assert(!iter.Back());
        for (int a = 0; a < 15; a++)
        {
            assert(*iter.GetValue() == OriginalArray[a]);
            assert(iter.Next());
        }
        assert(!iter.Next());
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        assert(!iter.Next());
        for (int a = 14; a >= 0; a--)
        {
            assert(iter.Back());
            assert(*iter.GetValue() == OriginalArray[a]);
        }
        assert(!iter.Back());
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->At(5);
        for (int a = 5; a < 15; a++)
        {
            assert(*iter.GetValue() == OriginalArray[a]);
            assert(iter.Next());
        }
        assert(iter.JumpToBegin());
        for (int a = 0; a < 15; a++)
        {
            assert(*iter.GetValue() == OriginalArray[a]);
            assert(iter.Next());
        }
        assert(!iter.Next());
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        assert(iter.Next(5));
        for (int a = 5; a < 15; a++)
        {
            assert(*iter.GetValue() == OriginalArray[a]);
            assert(iter.Next());
        }
        assert(!iter.Next());
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        assert(!iter.Next());
        assert(iter.Back(4));
        for (int a = 10; a >= 0; a--)
        {
            assert(iter.Back());
            assert(*iter.GetValue() == OriginalArray[a]);
        }
        assert(!iter.Back());
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        assert(!iter.Next(25));
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        assert(!iter.Back(24));
        delete Instance;
    }

    static void IteratorsDelete()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;
        Array<int>::Iterator iter;

        /*
         * Delete actual
         */
        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        assert(iter.DeleteThis() == 1);
        assert(*iter.GetValue() == 3);
        assert(Instance->Size() == 14);
        assert(Instance->Capacity() == 15);
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        assert(iter.DeleteThis() == 0);
        assert(iter.GetValue() == NULL);
        assert(Instance->Size() == 15);
        assert(Instance->Capacity() == 15);
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->At(5);
        assert(iter.DeleteThis() == 1);
        assert(*iter.GetValue() == 13);
        assert(Instance->Size() == 14);
        assert(Instance->Capacity() == 15);
        delete Instance;

        /*
         * Delete before
         */
        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        assert(iter.DeleteBefore(5) == 0);
        assert(*iter.GetValue() == 1);
        assert(Instance->Size() == 15);
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->At(5);
        assert(iter.DeleteBefore(10) == 5);
        assert(Instance->Size() == 10);
        iter = Instance->Begin();
        for (int a = 5; a < 15; a++)
        {
            assert(*iter.GetValue() == OriginalArray[a]);
            assert(iter.Next());
        }
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        assert(iter.DeleteBefore(5) == 5);
        assert(Instance->Size() == 10);
        iter = Instance->Begin();
        for (int a = 0; a < 10; a++)
        {
            assert(*iter.GetValue() == OriginalArray[a]);
            assert(iter.Next());
        }
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        assert(iter.DeleteBefore(25) == 15);
        assert(Instance->Size() == 0);
        delete Instance;

        /*
         * Delete after
         */
        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        assert(iter.DeleteAfter(5) == 5);
        assert(*iter.GetValue() == 1);
        assert(Instance->Size() == 10);
        assert(iter.Next());
        for (int a = 6; a < 10; a++)
        {
            assert(*iter.GetValue() == OriginalArray[a]);
            assert(iter.Next());
        }
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->End();
        assert(iter.DeleteAfter(5) == 0);
        assert(iter.GetValue() == NULL);
        assert(Instance->Size() == 15);
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->Begin();
        assert(iter.DeleteAfter(25) == 14);
        assert(*iter.GetValue() == 1);
        assert(Instance->Size() == 1);
        assert(iter.Next());
        assert(!iter.Next());
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->At(5);
        assert(iter.DeleteAfter(5) == 5);
        assert(Instance->Size() == 10);
        iter = Instance->Begin();
        for (int a = 0; a < 6; a++)
        {
            assert(*iter.GetValue() == OriginalArray[a]);
            assert(iter.Next());
        }
        for (int a = 11; a < 15; a++)
        {
            assert(*iter.GetValue() == OriginalArray[a]);
            assert(iter.Next());
        }
        delete Instance;

        Instance = new Array<int>(OriginalArray, 15);
        iter = Instance->At(5);
        assert(iter.DeleteAfter(25) == 9);
        assert(Instance->Size() == 6);
        iter = Instance->Begin();
        for (int a = 0; a < 6; a++)
        {
            assert(*iter.GetValue() == OriginalArray[a]);
            assert(iter.Next());
        }
        delete Instance;
    }

    static void PushTests()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;
        Array<int>::Iterator iter;

        Instance=new Array<int>(OriginalArray,15);
        assert(Instance->Push(31)==1);
        assert(Instance->Size()==16);
        iter = Instance->Begin();
        for(int a=0;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        assert(*iter.GetValue()==31);
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        assert(Instance->Push(35)==1);
        assert(Instance->Size()==16);
        iter = Instance->Begin();
        for(int a=0;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        assert(*iter.GetValue()==35);
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        assert(Instance->Push(OriginalArray,10)==10);
        assert(Instance->Size()==25);
        iter = Instance->Begin();
        for(int a=0;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        for(int a=0;a<10;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        assert(Instance->Push(OriginalArray,15)==15);
        assert(Instance->Size()==30);
        iter = Instance->Begin();
        for(int a=0;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        for(int a=0;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        delete Instance;
    }

    static void IteratorsInsertTests()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;
        Array<int>::Iterator iter;

        /*
         * Insert one element after iterator
         */
        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        assert(iter.Insert(15)==1);
        assert(Instance->Size()==16);
        assert(*iter.GetValue()==1);
        assert(iter.Next());
        assert(*iter.GetValue()==15);
        assert(iter.Next());
        assert(*iter.GetValue()==3);
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        assert(iter.Next(5));
        assert(iter.Insert(66)==1);
        assert(Instance->Size()==16);
        iter=Instance->Begin();
        for(int a=0;a<6;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        assert(*iter.GetValue()==66);
        assert(iter.Next());
        for(int a=6;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->End();
        assert(iter.Insert(15)==0);
        delete Instance;

        /*
         * Insert array after iterator
         */
        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        assert(iter.Insert(OriginalArray,5)==5);
        assert(Instance->Size()==20);
        assert(*iter.GetValue()==1);
        assert(iter.Next());
        for(int a=0;a<5;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        for(int a=1;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        assert(iter.Next(5));
        assert(iter.Insert(OriginalArray,5)==5);
        assert(Instance->Size()==20);
        iter = Instance->Begin();
        for(int a=0;a<6;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        for(int a=0;a<5;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        for(int a=6;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->End();
        assert(iter.Insert(OriginalArray,5)==0);
        delete Instance;

        /*
         * Insert one element before iterator
         */
        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        assert(iter.InsertBefore(15)==1);
        assert(Instance->Size()==16);
        iter = Instance->Begin();
        assert(*iter.GetValue()==15);
        assert(iter.Next());
        for(int a=0;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        assert(iter.Next(5));
        assert(iter.InsertBefore(66)==1);
        assert(Instance->Size()==16);
        iter=Instance->Begin();
        for(int a=0;a<5;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        assert(*iter.GetValue()==66);
        assert(iter.Next());
        for(int a=5;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->End();
        assert(iter.InsertBefore(66)==1);
        assert(Instance->Size()==16);
        iter = Instance->Begin();
        for(int a=0;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        assert(*iter.GetValue()==66);
        delete Instance;


        /*
         * Insert array before iterator
         */
        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        assert(iter.InsertBefore(OriginalArray,5)==5);
        assert(Instance->Size()==20);
        assert(*iter.GetValue()==1);
        iter=Instance->Begin();
        for(int a=0;a<5;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        for(int a=0;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->Begin();
        assert(iter.Next(5));
        assert(iter.InsertBefore(OriginalArray,5)==5);
        assert(Instance->Size()==20);
        iter = Instance->Begin();
        for(int a=0;a<5;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        for(int a=0;a<5;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        for(int a=5;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        delete Instance;

        Instance=new Array<int>(OriginalArray,15);
        iter=Instance->End();
        assert(iter.InsertBefore(OriginalArray,5)==5);
        assert(Instance->Size()==20);
        iter = Instance->Begin();
        for(int a=0;a<15;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        for(int a=0;a<5;a++,iter.Next())
            assert(*iter.GetValue()==OriginalArray[a]);
        delete Instance;
    }

    static void SwapTests()
    {
        int OriginalArray[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
        Array<int> *Instance;

        Instance = new Array<int>(OriginalArray,15);
        assert(Instance->Swap(0,14));
        assert(Instance->Swap(1,13));
        assert(Instance->Swap(2,12));
        assert(Instance->Swap(3,11));
        assert(Instance->Swap(4,10));
        assert(Instance->Swap(5,9));
        assert(Instance->Swap(6,8));
        for(int a=14;a>=0;a--)
            assert(*Instance->Containing[a]==OriginalArray[14-a]);
        delete Instance;
    }
};
