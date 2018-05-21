#define CATCH_CONFIG_MAIN
#include <assert.h>
#include "../libs/catch.h"
#include "../Templates.h"

class BinomialHeapLiteTests
{
    static int comparer(const int& first, const int& second)
    {
        return first - second;
    }

    static int comparer(int* const &first, int* const &second)
    {
        return *first - *second;
    }

    static void pointersUsage()
    {
        using namespace Templates;
        BinomialHeapLite<int*,comparer,Templates::BinomialHeapLiteDelete::PointerDeleter<int*>> in;

        int* val;
        int list[] = {25, 12, 36, 52, 14, 98, 52, 36, 54, 74, 32};

        for (int a = 0; a < 11; a++)
            in.Push(new int(list[a]));

        //98,74,54,52,52,36,36,32,25,14,12
        assert(in.Pop(val) && *val == 12);
        delete val;
        assert(in.Pop(val) && *val == 14);
        delete val;
        assert(in.Pop(val) && *val == 25);
        delete val;
        assert(in.Pop(val) && *val == 32);
        delete val;
        assert(in.Pop(val) && *val == 36);
        delete val;
        assert(in.Pop(val) && *val == 36);
        delete val;
        assert(in.Pop(val) && *val == 52);
        delete val;
    }

    static void valuesUsage()
    {
        using namespace Templates;
        BinomialHeapLite<int,comparer> in;

        int val;
        int list[] = {25, 12, 36, 52, 14, 98, 52, 36, 54, 74, 32};

        for (int a = 0; a < 11; a++)
            in.Push(list[a]);

        //98,74,54,52,52,36,36,32,25,14,12
        assert(in.Pop(val) && val == 12);
        assert(in.Pop(val) && val == 14);
        assert(in.Pop(val) && val == 25);
        assert(in.Pop(val) && val == 32);
        assert(in.Pop(val) && val == 36);
        assert(in.Pop(val) && val == 36);
        assert(in.Pop(val) && val == 52);
        assert(in.Pop(val) && val == 52);
        assert(in.Pop(val) && val == 54);
        assert(in.Pop(val) && val == 74);
        assert(in.Pop(val) && val == 98);
        assert(!in.Pop(val));
    }

public:
    static void tests()
    {
        valuesUsage();
        pointersUsage();
    }
};

TEST_CASE("Binomial heap lite tests"){
    BinomialHeapLiteTests::tests();
}