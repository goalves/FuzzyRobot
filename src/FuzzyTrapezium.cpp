#include "FuzzyTrapezium.h"
FuzzyTrapezium::FuzzyTrapezium(float alpha, float beta, float gamma, float delta)
{
    this->alpha = alpha;
    this->beta = beta;
    this->gamma = gamma;
    this->delta = delta;
    this->center = (beta + gamma)/2;
}

float FuzzyTrapezium::membershipFunction(float u)
{
    float mi = 0.0;
    if (u < alpha) mi = 0.0;
    if ((u >= alpha) && (u <= beta)) mi = (u - alpha)/(beta - alpha);
    if ((u >= beta) && (u <= gamma)) mi = 1.0;
    if ((u > gamma) && (u <= delta)) mi = (delta - u)/(delta - gamma);
    if (u>delta) mi = 0.0;

    return mi;
}

