#include "../include/environment.hpp"

Environment::Environment(int height, int width) : width(width), height(height)
{
}
Environment::~Environment()
{
    for (int i = 0; i < springs.size(); i++)
        delete springs[i];
    for (int i = 0; i < particles.size(); i++)
        delete particles[i];
}

Particle *Environment::addParticle()
{
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> sizeDist(10, 20);
    float size = sizeDist(rd);
    std::uniform_int_distribution<int> massDist(100, 10000);
    float mass = massDist(rd);
    std::uniform_int_distribution<int> xDist(size, width - size);
    float x = xDist(rd);
    std::uniform_int_distribution<int> yDist(size, height - size);
    float y = yDist(rd);
    std::uniform_real_distribution<float> speedDist(0, 1);
    float speed = speedDist(rd);
    std::uniform_real_distribution<float> angleDist(0, 2 * M_PI);
    float angle = angleDist(rd);
    std::uniform_real_distribution<float> elasticityDist(0.8, 1);
    float elasticity = elasticityDist(rd);
    return addParticle(x, y, size, mass, speed, angle, elasticity);
}

Particle *Environment::addParticle(float x, float y, float size = 10, float mass = 100, float speed = 0, float angle = 0, float elasticity = 0.9)
{
    float drag = pow((mass / (mass + airMass)), size);
    Particle *particle = new Particle(x, y, size, mass, speed, angle, elasticity, drag);
    particles.push_back(particle);
    return particle;
}

Particle *Environment::getParticle(float x, float y)
{
    for (int i = 0; i < particles.size(); i++)
    {
        if (hypot(particles[i]->getX() - x, particles[i]->getY() - y) <= particles[i]->getSize())
        {
            return particles[i];
        }
    }
    return nullptr;
}

Spring *Environment::addSpring(Particle *p1, Particle *p2, float length = 50, float strength = 0.5)
{
    Spring *spring = new Spring(p1, p2, length, strength);
    springs.push_back(spring);
    return spring;
}

void Environment::bounce(Particle *particle)
{
    if (particle->getX() > width - particle->getSize())
    {
        particle->setX(2 * (width - particle->getSize()) - particle->getX());
        particle->setAngle(-particle->getAngle());
        particle->setSpeed(particle->getSpeed() * particle->getElasticity());
    }
    else if (particle->getX() < particle->getSize())
    {
        particle->setX(2 * particle->getSize() - particle->getX());
        particle->setAngle(-particle->getAngle());
        particle->setSpeed(particle->getSpeed() * particle->getElasticity());
    }
    if (particle->getY() > (height - particle->getSize()))
    {
        particle->setY(2 * (height - particle->getSize()) - particle->getY());
        particle->setAngle(M_PI - particle->getAngle());
        particle->setSpeed(particle->getSpeed() * particle->getElasticity());
    }
    else if (particle->getY() < particle->getSize())
    {
        particle->setY(2 * particle->getSize() - particle->getY());
        particle->setAngle(M_PI - particle->getAngle());
        particle->setSpeed(particle->getSpeed() * particle->getElasticity());
    }
}

void Environment::removeParticle(Particle *particle)
{
    for (int i = 0; i < particles.size(); i++)
    {
        if (particle == particles[i])
        {
            delete particles[i];
            particles.erase(particles.begin() + i);
        }
    }
}

void Environment::removeSpring(Spring *spring)
{
    for (int i = 0; i < springs.size(); i++)
    {
        if (spring == springs[i])
        {
            delete springs[i];
            springs.erase(springs.begin() + i);
        }
    }
}

void Environment::update()
{
    for (int i = 0; i < particles.size(); i++)
    {
        Particle *particle = particles[i];
        if (allowAccelerate)
            particle->accelerate(acceleration);
        if (allowMove)
            particle->move();
        if (allowDrag)
            particle->experienceDrag();
        if (allowBounce)
            bounce(particle);
        for (int x = i + 1; x < particles.size(); x++)
        {
            Particle *otherParticle = particles[x];
            if (allowCollide)
                particle->collide(otherParticle);
            if (allowAttract)
                particle->attract(otherParticle);
            if (allowCombine)
                particle->combine(otherParticle);
        }
    }
    for (int i = 0; i < springs.size(); i++)
    {
        Spring *spring = springs[i];
        spring->update();
    }
}