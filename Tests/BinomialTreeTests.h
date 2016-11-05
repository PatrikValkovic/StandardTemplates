#ifndef TEMPLATES_BINOMIALTREETESTS_H
#define TEMPLATES_BINOMIALTREETESTS_H

#include "../BinomialTree.h"

using namespace Templates;

class BinomialTreeTest
{
private:
    static bool comp(const int& f, const int& s)
    {
        return f < s;
    }

    //TODO do tests

public:
    static void tests()
    {
        BinomialTree<int, comp> x(1, 3);
        BinomialTree<int, comp> y(5, 2);
        x.Merge(y);
        return;
    }
};

#endif //TEMPLATES_BINOMIALTREETESTS_H
