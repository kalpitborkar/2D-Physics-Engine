#ifndef spring_hpp
#define spring_hpp
#define _USE_MATH_DEFINES

#include <math.h>
#include "particle.hpp"

class Spring
{
public:
    Spring(Particle *p1, Particle *p2, float length = 50, float strength = 0.5);
    Particle *getP1() { return p1; }
    Particle *getP2() { return p2; }
    void update();

protected:
    float length;
    float strength;
    Particle *p1;
    Particle *p2;
};

#endif