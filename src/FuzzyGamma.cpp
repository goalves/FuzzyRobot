#include "FuzzyGamma.h"

FuzzyGamma::FuzzyGamma(float alpha, float beta)
{
    this->alpha = alpha;
    this->beta = beta;
    this->center = beta;
}

float FuzzyGamma::membershipFunction(float u)
{
    float mi = 0.0;
    if (u < alpha) mi = 0.0;
    if ((u >= alpha) && (u <= beta)) mi = (u - alpha)/(beta - alpha);
    if (u > beta) mi = 1.0;
    return mi;
}

