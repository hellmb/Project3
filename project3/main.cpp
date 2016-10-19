#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>

#include "vector3.h"
#include "planet.h"

using namespace std;

// class SolarSystem -> here we want to calculate a number of stuff
class SolarSystem{
public:
    SolarSystem();

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

    //double KineticEnergy();
    //double PotentialEnergy();
    //double TotalEnergy();

    vector<Planet> planets;
    vector<Planet> &bodies();
    double m_G = 4 * M_PI * M_PI;
};

// define energies here and set them to 0
SolarSystem::SolarSystem(){
    E_kin;
    E_pot;
}

Planet& SolarSystem::createPlanet(vector3 position, vector3 velocity, double mass){
    planets.push_back( Planet(position, velocity, mass) );
    // return reference to newest added planet
    return planets.back();
}

int SolarSystem::NumberOfPlanets(){
    return planets.size();
}

vector<Planet> &SolarSystem::bodies(){
    return planets;
}

void SolarSystem::ForceAndEnergy(){
    E_kin = 0;
    E_pot = 0;


    for(Planet &body : planets){
        // reset forces on all planets
        //body.ResetForce();
        body.force.zeros();
    }

    for(int i = 0; i < NumberOfPlanets(); i++){
        Planet &body1 = planets[i];
        for(int j = i+1; j < NumberOfPlanets(); j++){
            Planet &body2 = planets[j];
            vector3 dr_vector = body1.position - body2.position;
            double dr = dr_vector.length();

            body1.force += (m_G*body1.mass*body2.mass*dr_vector)/pow(dr,3);
            body2.force -= (m_G*body1.mass*body2.mass*dr_vector)/pow(dr,3);

            // debugging output
            //cout << body2.mass << endl;
            cout << body2.position(0)<< " " << body2.position(1) << " " << body2.position(2) << endl;
            //cout << body2.force(0) << " " << body2.force(1) << " " << body2.force(2) << endl;
            //cout << body2.force(1) << endl;

            // updating potential energy
            E_pot += - ( 4.0 * 3.14 * 3.14 * body1.mass ) / dr;
        }

        E_kin += 0.5 * body1.mass * body1.velocity.length_squared();
    }
}

void SolarSystem::WriteToFile(string filename, string filename2){
    ofstream myfile, myfile2;
    //ios_base::app -> appends new elements to file, instead of overwriting them
    myfile.open(filename.c_str(), ios_base::app);
    myfile2.open(filename2.c_str(), ios_base::app);

    //myfile << "Number of planets in solar system: " << NumberOfPlanets() << endl;
    for( Planet &body : planets ){
        myfile << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
    }

    //myfile2 << "Number of planets in solar system: " << NumberOfPlanets() << endl;
    for( Planet &body : planets ){
        myfile2 << body.velocity.x() << " " << body.velocity.y() << " " << body.velocity.z() << "\n";
    }

    myfile.close();
    myfile2.close();
}


class Euler{
public:
    double h;

    Euler(double dt);
    void integrate(class SolarSystem &system);
};

Euler::Euler(double dt) :
    h(dt)
{

}

void Euler::integrate(SolarSystem &system){

    system.ForceAndEnergy();

    for(Planet &body : system.bodies()){
        body.position += body.velocity * h;
        body.velocity += body.force / body.mass * h;
        //cout << body.position(0) << " " << body.position(1) << " " << body.position(2) << endl;
    }
}



// main program
int main() {

    int timesteps = 1000;

    SolarSystem Solar_System;

    // position, velocity and mass
    Planet &sun = Solar_System.createPlanet(vector3(0, 0, 0), vector3(0, 0, 0), 1.0);
    Planet &earth = Solar_System.createPlanet(vector3(1, 0, 0), vector3(0, 2*M_PI, 0), 3e-6);
    //Planet &earth = Solar_System.createPlanet(vector3(8.9232e-1, 4.5235e-1, -1.7817e-4), vector3(-2.2005e-5, 4.1909e-5, -1.5526e-9), 3e-6);

    vector<Planet> &bodies = Solar_System.bodies();

    //Solar_System.WriteToFile("positions", "velocities");

    double dt = 0.001;
    Euler integrator(dt);
    for(int timestep = 0; timestep < timesteps; timestep++){
        integrator.integrate(Solar_System);
        Solar_System.WriteToFile("position.xyz", "velocity.xyz");
        //cout << "Loop entered" << endl;
    }

    cout << "Number of planets: " << Solar_System.NumberOfPlanets()<< endl;
    cout << "Number of planets: " << Solar_System.bodies().size() << endl;


    return 0;
}
