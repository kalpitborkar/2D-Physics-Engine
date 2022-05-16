# 2D-Physics-Engine
A simple 2D Physics library written in C++.

## Concepts
### Particle
A `Particle` is an object representing a physical particle in `Environment`. A `Particle` has a mass, speed, position, size, elasticity and other properties.
### Spring
A `Spring` is an object representing a physical spring in `Environment`. A `Spring` has two `Particles` attached to it's either ends.  A `Spring` has length and strength properties.
### Environment
The `Environment` class represents the environment in which the simulation is occuring. An `Environment` holds multiple `Particle` and `Spring` objects during simulation. 


