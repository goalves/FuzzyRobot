#include "FuzzyTriangle.h"
FuzzyTriangle::FuzzyTriangle(float alpha, float beta, float gamma)
{
    this->alpha = alpha;
    this->beta = beta;
    this->gamma = gamma;
    this->center = beta;
}

float FuzzyTriangle::membershipFunction(float u)
{
    float mi = 0.0;
    if ((u < alpha) || (u > gamma)) mi = 0.0;
    if ((u >= alpha) && (u <= beta)) mi = (u - alpha)/(beta - alpha);
    if ((u > beta) && (u <= gamma)) mi = (gamma - u)/(gamma - beta);

    return mi;
}
