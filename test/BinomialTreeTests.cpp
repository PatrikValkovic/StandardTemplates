#define CATCH_CONFIG_MAIN
#include <assert.h>
#include "../libs/catch.h"
#include "../Templates.h"

using namespace Templates;

class BinomialTreeTest
{
private:
    static int comp(const int& f, const int& s)
    {
        return f - s;
    }

    static void EightNumbersSameTwoLevel()
    {
        /**
         *                  -8
         *                 / |
         *                /| |
         *               / | |
         *              1  4 10
         *             /|  |
         *            / |  |
         *           3  9  21
         *           |
         *           5
         */
        BinomialTree<int, comp> tree1(5, 3, 9, 1, -8, 10, 4, 21);
        assert(tree1.Top() == -8);
        assert(tree1.Level() == 3);
        auto firstLevel = tree1.InnerTrees();
        auto firstLevelMov = firstLevel.Begin();
        auto Top1 = *firstLevelMov;
        firstLevelMov.Next();
        auto Top4 = *firstLevelMov;
        firstLevelMov.Next();
        auto Top10 = *firstLevelMov;
        assert(Top1.Top() == 1);
        assert(Top1.Level() == 2);
        assert(Top4.Top() == 4);
        assert(Top4.Level() == 1);
        assert(Top10.Top() == 10);
        assert(Top10.Level() == 0);
        auto secondLevel = Top4.InnerTrees();
        auto Top21 = *secondLevel.Begin();
        secondLevel = Top1.InnerTrees();
        auto secondLevelMove = secondLevel.Begin();
        auto Top3 = *secondLevelMove;
        secondLevelMove.Next();
        auto Top9 = *secondLevelMove;
        assert(Top21.Top() == 21);
        assert(Top21.Level() == 0);
        assert(Top9.Top() == 9);
        assert(Top9.Level() == 0);
        assert(Top3.Top() == 3);
        assert(Top3.Level() == 1);
        auto Top5 = *Top3.InnerTrees().Begin();
        assert(Top5.Top() == 5);
        assert(Top5.Level() == 0);
    }

    static void EightNumbers()
    {
        /**
         *                  -8
         *                 / |
         *                /| |
         *               / | |
         *              1  4 10
         *             /|  |
         *            / |  |
         *           3  9  21
         *           |
         *           5
         */
        BinomialTree<int, comp> tree1(5, 3, 9, 1, -8, 10, 4, 21);
        assert(tree1.Top() == -8);
        assert(tree1.Level() == 3);
        auto firstLevel = tree1.InnerTrees();
        auto firstLevelMov = firstLevel.Begin();
        auto Top1 = *firstLevelMov;
        firstLevelMov.Next();
        auto Top4 = *firstLevelMov;
        firstLevelMov.Next();
        auto Top10 = *firstLevelMov;
        assert(Top1.Top() == 1);
        assert(Top1.Level() == 2);
        assert(Top4.Top() == 4);
        assert(Top4.Level() == 1);
        assert(Top10.Top() == 10);
        assert(Top10.Level() == 0);
        auto secondLevelRight = Top4.InnerTrees();
        auto Top21 = *secondLevelRight.Begin();
        auto secondLevelLeft = Top1.InnerTrees();
        auto secondLevelMove = secondLevelLeft.Begin();
        auto Top3 = *secondLevelMove;
        secondLevelMove.Next();
        auto Top9 = *secondLevelMove;
        assert(Top21.Top() == 21);
        assert(Top21.Level() == 0);
        assert(Top9.Top() == 9);
        assert(Top9.Level() == 0);
        assert(Top3.Top() == 3);
        assert(Top3.Level() == 1);
        auto Top5 = *Top3.InnerTrees().Begin();
        assert(Top5.Top() == 5);
        assert(Top5.Level() == 0);
    }

    static void FourNumbers()
    {
        /**
         *            1
         *           /|
         *          3  9
         *          |
         *          5
         */
        BinomialTree<int, comp> tree1(5, 3, 9, 1);
        assert(tree1.Top() == 1);
        auto inner1 = tree1.InnerTrees();
        assert(inner1.Size() == 2);
        auto mov = inner1.Begin();
        auto left = *mov;
        mov.Next();
        auto right = *mov;
        assert(right.Top() == 9);
        assert(left.Top() == 3);
        auto rest = left.InnerTrees();
        assert(rest.Size() == 1);
        assert(rest.Begin()->Top() == 5);
    }

    static void TwoNumbers()
    {
        /**
         *      3
         *      |
         *      5
         */
        BinomialTree<int, comp> tree1(5, 3);
        assert(tree1.Top() == 3);
        assert(tree1.Level() == 1);
        auto inner1 = tree1.InnerTrees();
        assert(inner1.Size() == 1);
        assert(inner1.Begin()->Top() == 5);
    }

public:
    static void tests()
    {
        TwoNumbers();

        FourNumbers();

        EightNumbers();

        EightNumbersSameTwoLevel();
    }
};

TEST_CASE("Binomial tree tests"){
    BinomialTreeTest::tests();
}