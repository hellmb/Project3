#include "euler.h"
#include "solarsystem.h"
#include <iostream>

Euler::Euler(double dt) :
    h(dt)
{

}

void Euler::integrate(SolarSystem &system){

    system.ForceAndEnergy();

    for(Planet &body : system.bodies()){
        body.position += body.velocity * h;
        body.velocity += body.force / body.mass * h;
        cout << body.position(0)*body.position(0) + body.position(1)*body.position(1) + body.position(2)*body.position(2) << endl;
    }

}

