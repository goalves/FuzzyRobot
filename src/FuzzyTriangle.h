#ifndef FUZZYGROUP_ADD
#define FUZZYGROUP_ADD
#include "FuzzySet.h"
#endif
class FuzzyTriangle:public FuzzySet
{
    protected:
    float alpha;
    float beta;
    float gamma;
    public:
    FuzzyTriangle(float alpha, float beta, float gamma);
    float membershipFunction(float u);
};
