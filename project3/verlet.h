#ifndef VERLET_H
#define VERLET_H

#include "solarsystem.h"

class Verlet{
public:
    double h;
    Verlet(double dt);
    void integrate(SolarSystem &system);
};

#endif // VERLET_H
