#ifndef FUZZYGROUP_ADD
#define FUZZYGROUP_ADD
#include "FuzzySet.h"
#endif
class FuzzyTrapezium:public FuzzySet
{
    protected:
    float alpha;
    float beta;
    float gamma;
    float delta;
    public:
    FuzzyTrapezium(float alpha, float beta, float gamma, float delta);
    float membershipFunction(float u);
};

