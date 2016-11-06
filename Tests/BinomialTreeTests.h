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

    //TODO do tests

public:
    static void tests()
    {
        BinomialTree<int,comp> tree(5,3,9,1,-8,10,4,21);
        BinomialTree<int,comp> second = tree;
    }
};

#endif //TEMPLATES_BINOMIALTREETESTS_H
