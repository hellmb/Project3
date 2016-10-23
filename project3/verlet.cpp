#include <iostream>

#include "verlet.h"
#include "solarsystem.h"

Verlet::Verlet(double dt):
    h(dt)
{

}

void Verlet::integrate(SolarSystem &system){

    system.ForceAndEnergy();
    //system.ForceMercury();

    // Velocity Verlet solver
    for(Planet &body : system.bodies()){
        vector3 acc = body.force / body.mass; // v derivert av i
        body.position += body.velocity * h + acc * h * h / 2.;

        //system.ForceMercury();
        system.ForceAndEnergy(); //regner ut alt på nytt, men acc har fortsatt "forrige" verdi
        body.velocity += ( body.force / body.mass ) * h / 2. + acc * h / 2.;
    }
}
