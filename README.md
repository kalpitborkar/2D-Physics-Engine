# 2D-Physics-Engine
A simple 2D Physics library written in C++.

## Structure
### Particle
A `Particle` is an object representing a physical particle in `Environment`.<br />
A `Particle` has a mass, speed, position, size, elasticity and other properties.<br />
### Spring
A `Spring` is an object representing a physical spring in `Environment`.<br />
A `Spring` has two `Particles` attached to it's either ends.  A `Spring` has length and strength properties.<br />
### Environment
The `Environment` class represents the environment in which the simulation is occuring.<br />
An `Environment` holds multiple `Particle` and `Spring` objects during simulation. <br />

## References
- https://www.petercollingridge.co.uk/tutorials/pygame-physics-simulation/
- https://developer.ibm.com/tutorials/wa-build2dphysicsengine/
