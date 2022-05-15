
#ifndef particle_hpp
#define particle_hpp
#define _USE_MATH_DEFINES

#include <math.h>

struct Vector
{
    float angle;
    float speed;
};

Vector operator+(Vector const &v1, Vector const &v2);

class Particle
{
public:
    Particle(float x, float y, float size, float mass, float speed, float angle, float elasticity, float drag);
    Particle *getCollideWith() { return collideWith; }
    float getAngle() { return angle; }
    float getDrag() { return drag; }
    float getElasticity() { return elasticity; }
    float getMass() { return mass; }
    float getSize() { return size; }
    float getSpeed() { return speed; }
    float getX() { return x; }
    float getY() { return y; }
    void accelerate(Vector vector);
    void attract(Particle *otherP);
    void collide(Particle *otherP);
    void combine(Particle *otherP);
    void experienceDrag();
    void move();
    void moveTo(float moveX, float moveY);
    void setAngle(float a) { angle = a; }
    void setDrag(float d) { drag = d; }
    void setElasticity(float e) { elasticity = e; }
    void setMass(float m) { mass = m; }
    void setSize(float s) { size = s; }
    void setSpeed(float s) { speed = s; }
    void setX(float setToX) { x = setToX; }
    void setY(float setToY) { y = setToY; }

protected:
    float angle;
    float drag;
    float elasticity;
    float mass;
    float size;
    float speed;
    float x;
    float y;
    Particle *collideWith = NULL;
};

#endif