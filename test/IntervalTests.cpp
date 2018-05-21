#define CATCH_CONFIG_MAIN
#include <assert.h>
#include "../libs/catch.h"
#include "../Templates.h"

using namespace Math;

class IntervalTests
{
private:
    static void Minus()
    {
        Interval<int> Instance(5, 10);
        Interval<int> Before(0, 2);
        Interval<int> After(15, 17);
        Interval<int> In(7, 9);
        Interval<int> Left(4, 6);
        Interval<int> Right(9, 11);

        Interval<int> BeforeMinus = Instance-Before;
        Interval<int> AfterMinus = Instance-After;
        Interval<int> InMinus = Instance-In; //TODO bug
        Interval<int> LeftMinus = Instance-Left;
        Interval<int> RightMinus = Instance-Right;

        assert(BeforeMinus.GetBegin()==5);
        assert(BeforeMinus.GetEnd()==10);

        assert(AfterMinus.GetBegin()==5);
        assert(AfterMinus.GetEnd()==10);

        assert(InMinus.GetBegin()==5); //FIX
        assert(InMinus.GetEnd()==7);

        assert(LeftMinus.GetBegin()==6);
        assert(LeftMinus.GetEnd()==10);

        assert(RightMinus.GetBegin()==5);
        assert(RightMinus.GetEnd()==9);
    }


public:
    static void tests()
    {
        Minus();
    }
};

TEST_CASE("interval tests"){
    IntervalTests::tests();
}
