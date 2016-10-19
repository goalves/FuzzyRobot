#include "FuzzyLogic.h"
#include <math.h>

float FuzzyLogic::ballAngle = 0.0;
float FuzzyLogic::targetAngle = 0.0;
float FuzzyLogic::ballDistance = 0.0;
FuzzyDelta* FuzzyLogic::NB = 0;
FuzzyTriangle* FuzzyLogic::NS = 0;
FuzzyTriangle* FuzzyLogic::ZE = 0;
FuzzyTriangle* FuzzyLogic::PS = 0;
FuzzyGamma* FuzzyLogic::PB = 0;

FuzzySet* FuzzyLogic::distanceRule = 0;


float FuzzyLogic::calculateActivationValue(FuzzySet* first, FuzzySet* second, FuzzySet* third)
{
    float mi[3];

    mi[0] = first->membershipFunction(ballAngle);
    mi[1] = second->membershipFunction(targetAngle);
    mi[2] = third->membershipFunction(ballDistance);
    float result = 1.0;
    if (mi[0] < result) result = mi[0];
    if (mi[1] < result) result = mi[1];
    if (mi[2] < result) result = mi[2];

    return result;
}

float FuzzyLogic::mamdaniValue(float alpha, FuzzySet* group, float z)
{
    if (alpha == 0.0)
        return 0.0;

    float mi = group->membershipFunction(z);
    float result = 1.0;

    if (mi < result)
        result = mi;
    if (alpha < result)
        result = alpha;
    return result;
}

void FuzzyLogic::setBallAngle(float value)
{
    ballAngle = value;
}
void FuzzyLogic::setTargetAngle(float value)
{
    targetAngle = value;
}
void FuzzyLogic::setBallDistance(float value)
{
    ballDistance = value;
}

void FuzzyLogic::calculateFuzzyMatrix(float A[])
{
    A[0] = FuzzyLogic::calculateActivationValue(NB, NB, distanceRule);
    A[1] = FuzzyLogic::calculateActivationValue(NB, NS, distanceRule);
    A[2] = FuzzyLogic::calculateActivationValue(NB, ZE, distanceRule);
    A[3] = FuzzyLogic::calculateActivationValue(NB, PS, distanceRule);
    A[4] = FuzzyLogic::calculateActivationValue(NB, PB, distanceRule);

    A[5] = FuzzyLogic::calculateActivationValue(NS, NB, distanceRule);
    A[6] = FuzzyLogic::calculateActivationValue(NS, NS, distanceRule);
    A[7] = FuzzyLogic::calculateActivationValue(NS, ZE, distanceRule);
    A[8] = FuzzyLogic::calculateActivationValue(NS, PS, distanceRule);
    A[9] = FuzzyLogic::calculateActivationValue(NS, PB, distanceRule);

    A[10] = FuzzyLogic::calculateActivationValue(ZE, NB, distanceRule);
    A[11] = FuzzyLogic::calculateActivationValue(ZE, NS, distanceRule);
    A[12] = FuzzyLogic::calculateActivationValue(ZE, ZE, distanceRule);
    A[13] = FuzzyLogic::calculateActivationValue(ZE, PS, distanceRule);
    A[14] = FuzzyLogic::calculateActivationValue(ZE, PB, distanceRule);

    A[15] = FuzzyLogic::calculateActivationValue(PS, NB, distanceRule);
    A[16] = FuzzyLogic::calculateActivationValue(PS, NS, distanceRule);
    A[17] = FuzzyLogic::calculateActivationValue(PS, ZE, distanceRule);
    A[18] = FuzzyLogic::calculateActivationValue(PS, PS, distanceRule);
    A[19] = FuzzyLogic::calculateActivationValue(PS, PB, distanceRule);

    A[20] = FuzzyLogic::calculateActivationValue(PB, NB, distanceRule);
    A[21] = FuzzyLogic::calculateActivationValue(PB, NS, distanceRule);
    A[22] = FuzzyLogic::calculateActivationValue(PB, ZE, distanceRule);
    A[23] = FuzzyLogic::calculateActivationValue(PB, PS, distanceRule);
    A[24] = FuzzyLogic::calculateActivationValue(PB, PB, distanceRule);
}

float FuzzyLogic::calculateFuzzyWeightedSum(float A[])
{
    float weightedSum = 0.0;
    weightedSum += A[0]*NB->center;
    weightedSum += A[1]*NB->center;
    weightedSum += A[2]*NB->center;
    weightedSum += A[3]*NB->center;
    weightedSum += A[4]*NB->center;

    weightedSum += A[5]*NS->center;
    weightedSum += A[6]*NS->center;
    weightedSum += A[7]*NS->center;
    weightedSum += A[8]*NS->center;
    weightedSum += A[9]*NS->center;

    weightedSum += A[10]*ZE->center;
    weightedSum += A[11]*ZE->center;
    weightedSum += A[12]*ZE->center;
    weightedSum += A[13]*ZE->center;
    weightedSum += A[14]*ZE->center;

    weightedSum += A[15]*PS->center;
    weightedSum += A[16]*PS->center;
    weightedSum += A[17]*PS->center;
    weightedSum += A[18]*PS->center;
    weightedSum += A[19]*PS->center;

    weightedSum += A[20]*PB->center;
    weightedSum += A[21]*PB->center;
    weightedSum += A[22]*PB->center;
    weightedSum += A[23]*PB->center;
    weightedSum += A[24]*PB->center;

    return weightedSum;
}
void FuzzyLogic::setDistanceRule(FuzzySet *rule)
{
    distanceRule = rule;
}

/*
    Método de defuzificação do centróide ( de Mamdani )
*/

void FuzzyLogic::centroidDeffuzification(float longMatrix[], float mediumMatrix[], float nearMatrix[],float* sum, float* weightedSum)
{
    float outValue = 0.0;
    // Feito com 101 iterações
    for (int i = 0; i <= 100; i++)
    {
        float z = i*(M_PI/50) - M_PI;
        outValue = 0.0;
        float C = 0.0;

        if ((C = FuzzyLogic::mamdaniValue(longMatrix[0], NB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[1], NB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[2], NB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[3], NB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[4], NB, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(longMatrix[5], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[6], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[7], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[8], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[9], NS, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(longMatrix[10], ZE, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[11], ZE, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[12], ZE, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[13], ZE, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[14], ZE, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(longMatrix[15], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[16], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[17], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[18], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[19], PS, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(longMatrix[20], PB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[21], PB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[22], PB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[23], PB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(longMatrix[24], PB, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[0], NB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[1], NB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[2], NB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[3], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[4], PS, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[5], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[6], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[7], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[8], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[9], NS, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[10], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[11], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[12], ZE, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[13], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[14], NS, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[15], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[16], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[17], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[18], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[19], PS, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[20], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[21], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[22], PB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[23], PB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(mediumMatrix[24], PB, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[0], NB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[1], NB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[2], NB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[3], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[4], PS, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[5], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[6], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[7], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[8], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[9], NS, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[10], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[11], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[12], ZE, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[13], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[14], NS, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[15], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[16], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[17], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[18], PS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[19], PS, z)) > outValue) outValue = C;

        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[20], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[21], NS, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[22], PB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[23], PB, z)) > outValue) outValue = C;
        if ((C = FuzzyLogic::mamdaniValue(nearMatrix[24], PB, z)) > outValue) outValue = C;

        *sum += outValue;
        *weightedSum += z*outValue;
    }
}
