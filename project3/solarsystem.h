#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "planet.h"
#include <vector>
#include <string>
#include <fstream>

class SolarSystem{
public:
    SolarSystem();
    std::ofstream myfile, myfile2;

    double E_kin;
    double E_pot;
    //double E_tot;

    // function to create a new planet
    Planet &createPlanet( vector3 position, vector3 velocity, double mass );

    // function to find number of planets
    int NumberOfPlanets();

    // forces and energies
    void ForceAndEnergy();

    // write to file
    void WriteToFile(string filename, string filename2);

    double KineticEnergy() const;
    double PotentialEnergy() const;
    double TotalEnergy() const;

    vector<Planet> planets;
    vector<Planet> &bodies();
};

#endif // SOLARSYSTEM_H
