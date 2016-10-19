#include "FuzzyDelta.h"

FuzzyDelta::FuzzyDelta(float alpha, float beta)
{
    this->alpha = alpha;
    this->beta = beta;
    this->center = alpha;
}

float FuzzyDelta::membershipFunction(float u)
{
    float mi = 0.0;
    if (u < alpha) mi = 1.0;
    if ((u >= alpha) && (u <= beta)) mi = (beta - u)/(beta - alpha);
    if (u > beta) mi = 0.0;
    return mi;

}
