#include "../include/particle.hpp"

Vector operator+(Vector const &v1, Vector const &v2)
{
    float x = sin(v1.angle) * v1.speed + sin(v2.angle) * v2.speed;
    float y = cos(v1.angle) * v1.speed + cos(v2.angle) * v2.speed;
    return Vector{static_cast<float>(0.5 * M_PI - atan2(y, x)), hypot(x, y)};
}

Particle::Particle(float x, float y, float size, float mass, float speed, float angle, float elasticity, float drag) : x(x), y(y), size(size), mass(mass), speed(speed), angle(angle), elasticity(elasticity), drag(drag)
{
}

// Particle::Particle(float x, float y, float size, float mass, float speed, float angle, float elasticity, float drag)
// {
//     this->x = x;
//     this->y = y;
//     this->size = size;
//     this->mass = mass;
//     this->speed = speed;
//     this->angle = angle;
//     this->elasticity = elasticity;
//     this->drag = drag;
// }

void Particle::accelerate(Vector vector)
{
    Vector velocity = Vector{angle, speed} + vector;
    angle = velocity.angle;
    speed = velocity.speed;
}

void Particle::attract(Particle *otherP)
{
    float dx = x - otherP->x;
    float dy = y - otherP->y;
    float distance = hypot(dx, dy);
    float theta = atan2(dy, dx);
    float force = 0.2 * mass * otherP->mass / pow(distance, 2);
    accelerate(Vector{static_cast<float>(theta - 0.5 * M_PI), force / mass});
    otherP->accelerate(Vector{static_cast<float>(theta + 0.5 * M_PI), force / otherP->mass});
}

void Particle::collide(Particle *otherP)
{
    float dx = x - otherP->x;
    float dy = y - otherP->y;
    float distance = hypot(dx, dy);

    if (distance < size + otherP->size)
    {
        float tangent = atan2(dy, dx);
        float newAngle = M_PI_2 + tangent;
        float totalMass = mass + otherP->mass;

        Vector v1 = Vector{angle, speed * (mass - otherP->mass) / totalMass} + Vector{newAngle, 2 * otherP->speed * otherP->mass / totalMass};
        Vector v2 = Vector{otherP->angle, otherP->speed * (otherP->mass - mass) / totalMass} + Vector{static_cast<float>(newAngle + M_PI), 2 * speed * mass / totalMass};

        angle = v1.angle;
        speed = v1.speed;
        otherP->angle = v2.angle;
        otherP->speed = v2.speed;

        float newElasticity = elasticity * otherP->elasticity;
        speed *= newElasticity;
        otherP->speed *= newElasticity;

        float overlap = 0.5 * (size + otherP->size - distance + 1);
        x += sin(newAngle) * overlap;
        y -= cos(newAngle) * overlap;
        otherP->x -= sin(newAngle) * overlap;
        otherP->y += cos(newAngle) * overlap;
    }
}

void Particle::combine(Particle *otherP)
{
    float dx = x - otherP->x;
    float dy = y - otherP->y;
    float distance = hypot(dx, dy);

    if (distance < size + otherP->size)
    {
        float totalMass = mass + otherP->mass;
        x = (x * mass + otherP->x * otherP->mass);
        y = (y * mass + otherP->y * otherP->mass);
        Vector vector = Vector{angle, speed * mass / totalMass} + Vector{otherP->angle, otherP->speed * otherP->mass / totalMass};
        angle = vector.angle;
        speed = vector.speed * elasticity * otherP->elasticity;
        mass += otherP->mass;
        collideWith = otherP;
    }
}

void Particle::experienceDrag()
{
    speed *= drag;
}

void Particle::move()
{
    x += sin(angle) * speed;
    y -= cos(angle) * speed;
}

void Particle::moveTo(float moveX, float moveY)
{
    float dx = moveX - x;
    float dy = moveY - y;
    angle = atan2(dy, dx) + M_PI_2;
    speed = hypot(dx, dy) * 0.1;
}
