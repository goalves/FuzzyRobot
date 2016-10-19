#ifndef FUZZYGROUP_ADD
#define FUZZYGROUP_ADD
#include "FuzzySet.h"
#endif

#ifndef FUZZYFUNCTIONS
#define FUZZYFUNCTIONS
#include "FuzzyTriangle.h"
#include "FuzzyDelta.h"
#include "FuzzyGamma.h"
#endif // FUZZYFUNCTIONS


// Static Class that calculates the whole Fuzzy Logic system
class FuzzyLogic
{
    private:
    static float ballAngle;
    static float targetAngle;
    static float ballDistance;
    static FuzzySet* distanceRule;


    public:
    static void setBallAngle(float value);
    static void setTargetAngle(float value);
    static void setBallDistance(float value);
    static void setDistanceRule(FuzzySet* rule);
    static FuzzyDelta* NB;
    static FuzzyTriangle* NS;
    static FuzzyTriangle* ZE;
    static FuzzyTriangle* PS;
    static FuzzyGamma* PB;


    static float calculateActivationValue(FuzzySet* first, FuzzySet* second, FuzzySet* third);
    static float mamdaniValue(float alpha, FuzzySet* group, float z);
    static void calculateFuzzyMatrix(float A[]);
    static float calculateFuzzyWeightedSum(float A[]);
    static void centroidDeffuzification(float longMatrix[], float mediumMatrix[], float nearMatrix[],float* sum, float* weightedSum);
};

