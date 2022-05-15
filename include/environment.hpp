#ifndef environment_hpp
#define environment_hpp
#define _USE_MATH_DEFINES

#include <math.h>
#include <random>
#include <vector>
#include "particle.hpp"
#include "spring.hpp"

class Environment
{
public:
    Environment(int height, int width);
    ~Environment();
    int getHeight() { return height; }
    int getWidth() { return width; }
    Particle *addParticle();
    Particle *addParticle(float x, float y, float size = 10, float mass = 100, float speed = 0, float angle = 0, float elasticity = 0.9);
    Particle *getParticle(float x, float y); // {return particle?}
    Spring *addSpring(Particle *p1, Particle *p2, float lenght = 50, float strenght = 0.5);
    std::vector<Particle *> getParticles() { return particles; }
    std::vector<Spring *> getSprings() { return springs; }
    void bounce(Particle *particle);
    void removeParticle(Particle *particle);
    void removeSpring(Spring *spring);
    void setAirMass(float a) { airMass = a; }
    void setAllowAccelerate(bool b) { allowAccelerate = b; }
    void setAllowAttract(bool b) { allowAttract = b; }
    void setAllowBounce(bool b) { allowBounce = b; }
    void setAllowCollide(bool b) { allowCollide = b; }
    void setAllowCombine(bool b) { allowCombine = b; }
    void setAllowDrag(bool b) { allowDrag = b; }
    void setAllowMove(bool b) { allowMove = b; }
    void setElasticity(float e) { elasticity = e; }
    void update();

protected:
    const int height;
    const int width;
    bool allowAccelerate = true;
    bool allowAttract = false;
    bool allowBounce = true;
    bool allowCollide = true;
    bool allowCombine = false;
    bool allowDrag = true;
    bool allowMove = true;
    float airMass = 0.2;
    float elasticity = 0.75;
    std::vector<Particle *> particles;
    std::vector<Spring *> springs;
    Vector acceleration = {M_PI, 0.2};
};

#endif