#ifndef TEMPLATES_BINOMIALTREETESTS_H
#define TEMPLATES_BINOMIALTREETESTS_H

#include "../BinomialTree.h"

using namespace Templates;

class BinomialTreeTest
{
private:
    static int comp(const int& f, const int& s)
    {
        return f - s;
    }

    static void FourNumbers()
    {
        BinomialTree<int,comp> tree1(5,3,9,1);
        assert(tree1.Top() == 1);
        auto inner1 = tree1.InnerTrees();
        assert(inner1.Size()==2);
        auto mov = inner1.Begin();
        auto left = *mov.GetValue();
        mov.Next();
        auto right = *mov.GetValue();
        assert(right.Top() == 9);
        assert(left.Top() == 3);
        auto rest = left.InnerTrees();
        assert(rest.Size() == 1);
        assert(rest.Begin().GetValue()->Top() == 5);
    }

    static void TwoNumbers()
    {
        BinomialTree<int,comp> tree1(5,3);
        assert(tree1.Top() == 3);
        auto inner1 = tree1.InnerTrees();
        assert(inner1.Size()==1);
        assert(inner1.Begin().GetValue()->Top() == 5);
    }

public:
    static void tests()
    {
        TwoNumbers();

        FourNumbers();
        //BinomialTree<int,comp> tree(5,3,9,1,-8,10,4,21);
        //BinomialTree<int,comp> second = tree;
    }
};

#endif //TEMPLATES_BINOMIALTREETESTS_H
