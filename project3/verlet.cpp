#include <iostream>
#include "verlet.h"
#include "solarsystem.h"

using namespace std;

// member functions for class Verlet

Verlet::Verlet(double dt):
    h(dt)
{

}

void Verlet::integrate(SolarSystem &system){

    system.ForceAndEnergy();
    //system.ForceMercury();

    // Velocity Verlet solver
    for(Planet &body : system.bodies()){

        // calculating 'previous' acceleration and storing it for usage in the velocity calculation
        vector3 acc = body.force / body.mass;

        // updating the position
        body.position += body.velocity * h + acc * h * h / 2.;

        // calculates the forces one more time, keeping the previous accelereation from above
        system.ForceAndEnergy();
        //system.ForceMercury();

        // updating the velocity
        body.velocity += ( body.force / body.mass ) * h / 2. + acc * h / 2.;
    }
}
