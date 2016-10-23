#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "planet.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class SolarSystem{
public:
    SolarSystem();
    ofstream myfile, myfile2;

    double E_kin;
    double E_pot;
    vector3 Mom_planets;
    vector3 Mom_sun;
    vector3 AngMom;

    // function to create a new planet
    Planet &createPlanet( vector3 position, vector3 velocity, double mass );

    // function to find number of planets
    int NumberOfPlanets();

    // forces and energies
    void ForceAndEnergy();
    void ForceMercury();
    double KineticEnergy() const;
    double PotentialEnergy() const;
    double TotalEnergy() const;
    double AngularMomentum();
    void Momentum();

    void WriteToFile(string filename, string filename2);


    vector<Planet> planets;
    vector<Planet> &bodies();
};

#endif // SOLARSYSTEM_H
