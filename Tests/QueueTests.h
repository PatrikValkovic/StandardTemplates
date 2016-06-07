#ifndef TEMPLATES_QUEUETESTS_H
#define TEMPLATES_QUEUETESTS_H

#ifndef _STALIB_
#include <assert.h>
#endif

#include "../Queue.h"

class QueueTests
{
private:
	QueueTests()
	{ }

	void CreationTests()
	{
		using namespace Templates;
		int list[] = { 2, 6, 7, 4, 3 };
		Queue<int>* Instance;
		int value;

		Instance = new Queue<int>();
		assert(Instance->IsEmpty());
		assert(Instance->Push(5));
		assert(!Instance->IsEmpty());
		assert(Instance->Pop(value) && value == 5);
		delete Instance;

		Instance = new Queue<int>(list, 5);
		assert(!Instance->IsEmpty());
		assert(Instance->Pop(value) && value == 2);
		assert(Instance->Pop(value) && value == 6);
		assert(Instance->Pop(value) && value == 7);
		assert(Instance->Pop(value) && value == 4);
		assert(Instance->Pop(value) && value == 3);
		assert(!Instance->Pop(value));
		delete Instance;

		return;
	}

	void ClearTests()
	{
		using namespace Templates;
		int list[] = { 2, 6, 7, 4, 3 };
		Queue<int>* Instance;
		int value;

		Instance = new Queue<int>(list, 5);
		assert(!Instance->IsEmpty());
		assert(Instance->Clear() == 5);
		assert(Instance->IsEmpty());
		delete Instance;

		Instance = new Queue<int>(list, 5);
		assert(Instance->Clear(3) == 3);
		assert(Instance->Pop(value) && value == 4);
		assert(Instance->Pop(value) && value == 3);
		assert(!Instance->Pop(value));
		delete Instance;

		Instance = new Queue<int>(list, 5);
		assert(Instance->Clear(8) == 5);
		assert(!Instance->Pop(value));
		delete Instance;
	}

	void PushingTests()
	{
		using namespace Templates;
		int list[] = { 2, 6, 7, 4, 3 };
		Queue<int>* Instance;
		int value;

		Instance = new Queue<int>(list, 3); //{2,6,7}
		assert(Instance->Push(list, 3) == 3); //{2,6,7,2,6,7}
		assert(Instance->Pop(value) && value == 2);
		assert(Instance->Pop(value) && value == 6);
		assert(Instance->Pop(value) && value == 7);
		assert(Instance->Pop(value) && value == 2);
		assert(Instance->Pop(value) && value == 6);
		assert(Instance->Pop(value) && value == 7);
		assert(!Instance->Pop(value));
		delete Instance;

		Instance = new Queue<int>(list, 3); //{2,6,7}
		assert(Instance->Push(list+2, 3) == 3); //{2,6,7,7,4,3}
		assert(Instance->Push(12) == 1); //{2,6,7,7,4,3,12}
		assert(Instance->Pop(value) && value == 2);
		assert(Instance->Pop(value) && value == 6);
		assert(Instance->Pop(value) && value == 7);
		assert(Instance->Pop(value) && value == 7);
		assert(Instance->Pop(value) && value == 4);
		assert(Instance->Pop(value) && value == 3);
		assert(Instance->Pop(value) && value == 12);
		assert(!Instance->Pop(value));
		delete Instance;
	}

	void IteratorTests()
	{
		using namespace Templates;
		int list[] = { 2, 6, 7, 4, 3 };
		Queue<int>* Instance;
		Queue<int>::Iterator Iterator;

		Instance = new Queue<int>(list, 5); //{ 2, 6, 7, 4, 3 }
		Iterator = Instance->Begin();
		assert(*Iterator.GetValue() == 2);
		assert(Iterator.Next());
		assert(*Iterator.GetValue()==6);
		assert(Iterator.Next());
		assert(*Iterator.GetValue() == 7);
		assert(Iterator.Next());
		assert(*Iterator.GetValue() == 4);
		assert(Iterator.Next());
		assert(*Iterator.GetValue() == 3);
		assert(Iterator.Next());
		assert(!Iterator.Next());
		assert(Instance->IsEmpty());
		delete Instance;

		Instance = new Queue<int>(list, 5); //{ 2, 6, 7, 4, 3 }
		Iterator = Instance->Begin();
		assert(*Iterator.GetValue() == 2);
		assert(Iterator.Next(3));
		assert(*Iterator.GetValue() == 4);
		assert(Iterator.Next());
		assert(!Instance->IsEmpty());
		delete Instance;

		Instance = new Queue<int>(list, 5); //{ 2, 6, 7, 4, 3 }
		Iterator = Instance->Begin();
		assert(*Iterator.GetValue() == 2);
		assert(!Iterator.Next(10));
		assert(!Instance->IsEmpty());
		delete Instance;
	}

public:
	static void test()
	{
		QueueTests test;
		test.CreationTests();
		test.ClearTests();
		test.PushingTests();
		test.IteratorTests();
	}
};

#endif //TEMPLATES_QUEUETESTS_H
