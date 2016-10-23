#include "euler.h"
#include "solarsystem.h"
#include <iostream>

// member functions for class Euler

Euler::Euler(double dt) :
    h(dt)
{

}

void Euler::integrate(SolarSystem &system){

    system.ForceAndEnergy();

    for(Planet &body : system.bodies()){
        // updating position and velocity
        body.position += body.velocity * h;
        body.velocity += body.force / body.mass * h;
    }
}



