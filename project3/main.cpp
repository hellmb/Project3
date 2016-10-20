#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>

#include "vector3.h"
#include "planet.h"
#include "solarsystem.h"
#include "euler.h"
#include "verlet.h"

using namespace std;


int main(int numArguments, char **arguments) {

    int NumStep = 20000;
    if(numArguments >= 2) NumStep = atoi(arguments[1]);

    SolarSystem Solar_System;

    // position, velocity and mass
    Planet &sun = Solar_System.createPlanet(vector3(0, 0, 0), vector3(0, 0, 0), 1.0);
    //Planet &earth = Solar_System.createPlanet(vector3(1, 0, 0), vector3(0, 2*M_PI, 0), 3e-6);
    Planet &earth = Solar_System.createPlanet(vector3(8.9232e-1, 4.5235e-1, -1.7817e-4), vector3(-2.9316, 5.5834, -2.0685e-4), 3e-6);
    Planet &jupiter = Solar_System.createPlanet(vector3(-5.4257, -4.8938e-1, 1.2337e-1), vector3(0.2153, -2.6128, 6.0411e-5), 9.49e-4);

    vector<Planet> &bodies = Solar_System.bodies();


    //double finaltime = 1.0;
    double dt = 0.001;

    //Euler integrator(dt);
    Verlet integrator(dt);
    for(int time = 0; time < NumStep; time++){
        integrator.integrate(Solar_System);
        Solar_System.WriteToFile("positions.txt", "velocities.txt");
        cout << "Time: " << time << endl;
    }

    cout << "Number of planets: " << Solar_System.NumberOfPlanets()<< endl;
    cout << "Number of planets: " << Solar_System.bodies().size() << endl;


    return 0;
}
