#ifndef FUZZYGROUP_ADD
#define FUZZYGROUP_ADD
#include "FuzzySet.h"
#endif
class FuzzyGamma:public FuzzySet
{
    protected:
    float alpha;
    float beta;
    public:
    FuzzyGamma(float alpha, float beta);
    float membershipFunction(float u);
};

