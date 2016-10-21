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

    SolarSystem Solar_System;

    // position, velocity and mass
    Planet &sun = Solar_System.createPlanet(vector3(3.5555e-3, 3.4437e-3, -1.5959e-4), vector3(-7.4438e-4, 2.4914e-3, 1.5295e-5), 1.0);
    Planet &mercury = Solar_System.createPlanet(vector3(-3.9067e-1, -5.3842e-2, 3.1326e-2), vector3(-0.6591, -9.7181, 0.7339), 1.65e-7);
    //Planet &venus = Solar_System.createPlanet(vector3(2.9535e-1, -6.6297e-1, -2.6136e-2), vector3(6.7124, 2.9387, -0.3471), 2.45e-6);
    //Planet &earth = Solar_System.createPlanet(vector3(8.9232e-1, 4.5235e-1, -1.7817e-4), vector3(-2.9316, 5.5834, -2.0685e-4), 3e-6);
    //Planet &mars = Solar_System.createPlanet(vector3(1.2012, -6.8454e-1, -4.3970e-2), vector3(2.7378, 4.8691, 0.0348), 3.3e-7);
    //Planet &jupiter = Solar_System.createPlanet(vector3(-5.4257, -4.8938e-1, 1.2337e-1), vector3(0.2153, -2.6128, 6.0411e-5), 9.5e-4);
    //Planet &saturn = Solar_System.createPlanet(vector3(-2.2414, -9.7812, 2.5927e-1), vector3(1.8735, -0.4613, -0.0665), 2.75e-4);
    //Planet &uranus = Solar_System.createPlanet(vector3(1.8456e+1, 7.5787, -2.1095e-1), vector3(-0.5558, 1.2610, 0.0119), 4.4e-5);
    //Planet &neptune = Solar_System.createPlanet(vector3(2.8266e+1, -9.9074, -4.4740e-1), vector3(0.3712, 1.0881, -0.0308), 5.15e-5);
    //Planet &pluto = Solar_System.createPlanet(vector3(9.4392, -3.1817e+1, 6.7425e-1), vector3(1.1240, 0.0922, -0.0331), 6.55e-9);

    // special case planets
    //Planet &sun = Solar_System.createPlanet(vector3(0, 0, 0, vector3(0, 0, 0), 1.0);
    //Planet &too_fun = Solar_System.createPlanet(vector3(1, 0, 0), vector3(0, 2.8*M_PI, 0), 3e-6);
    //Planet &jupiter = Solar_System.createPlanet(vector3(-5.4257, -4.8938e-1, 1.2337e-1), vector3(0.2153, -2.6128, 6.0411e-3), 1.0);

    //vector<Planet> &bodies = Solar_System.bodies();



    // years -> T = 1 = earth year
    double T  = 300.0;
    double dt = 1e-4;
    int NumStep = T/dt;
    cout << NumStep << endl;
    Solar_System.ForceAndEnergy();
    double energy_bf = Solar_System.TotalEnergy();
    //Euler integrator(dt);
    Verlet integrator(dt);
    for(int time = 0; time < NumStep; time++){
        integrator.integrate(Solar_System);

        if(dt <=1e-4){
            int printEvery = 100;
            if(time % printEvery == 0) {
                Solar_System.WriteToFile("../positions.txt", "../velocities.txt");
            }
        }
        else {
            Solar_System.WriteToFile("../positions.txt", "../velocities.txt");
        }
    }

    double energy_af = Solar_System.TotalEnergy();

    cout << "Difference in energy: " << energy_bf - energy_af << endl;

    cout << "Number of planets: " << Solar_System.NumberOfPlanets()<< endl;
    //cout << "Number of planets: " << Solar_System.bodies().size() << endl;


    return 0;
}
