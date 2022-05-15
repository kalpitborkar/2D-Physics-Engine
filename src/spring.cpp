#include "../include/spring.hpp"

Spring::Spring(Particle *p1, Particle *p2, float length = 50, float strength = 0.5) : p1(p1), p2(p2), length(length), strength(strength)
{
}

void Spring::update()
{
    float dx = p1->getX() - p2->getY();
    float dy = p1->getY() - p2->getY();
    float distance = hypot(dx, dy);
    float theta = atan2(dy, dx);
    float force = (length - distance) * strength;
    p1->accelerate(Vector{static_cast<float>(theta + 0.5 * M_PI), force / p1->getMass()});
    p2->accelerate(Vector{static_cast<float>(theta - 0.5 * M_PI), force / p2->getMass()});
}