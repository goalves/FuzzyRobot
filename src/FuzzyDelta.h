#ifndef FUZZYGROUP_ADD
#define FUZZYGROUP_ADD
#include "FuzzySet.h"
#endif
class FuzzyDelta:public FuzzySet
{
    protected:
    float alpha;
    float beta;
    public:
    FuzzyDelta(float alpha, float beta);
    float membershipFunction(float u);
};

