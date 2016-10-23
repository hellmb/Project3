#include "solarsystem.h"
#include <iostream>
#include <cmath>

// member functions for class SolarSystem

using namespace std;

SolarSystem::SolarSystem(){}

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

    // setting conserved quantities to be zero
    E_kin = 0;
    E_pot = 0;
    Mom_planets.zeros();
    Mom_sun.zeros();
    AngMom.zeros();

    double m_G = 4 * M_PI * M_PI;

    for(Planet &body : planets){
        // reset forces on all planets
        body.force.zeros();
    }

    for(int i = 0; i < NumberOfPlanets(); i++){
        Planet &sun_ = planets[0];
        Planet &body1 = planets[i];
        for(int j = i+1; j < NumberOfPlanets(); j++){
            Planet &body2 = planets[j];
            vector3 dr_vector = body1.position - body2.position;
            double dr = dr_vector.length();

            body1.force -= (m_G*body1.mass*body2.mass*dr_vector) / (dr*dr*dr);
            body2.force += (m_G*body1.mass*body2.mass*dr_vector) / (dr*dr*dr);

            // updating potential energy and momentum
            E_pot += - ( m_G * body2.mass * body1.mass ) / dr;
            Mom_planets += body2.mass * body2.velocity;
        }

        // updating kinetic energy, angular momentum and momentum
        E_kin += 0.5 * body1.mass * body1.velocity.length_squared();
        AngMom += body1.position.cross(body1.velocity);
        Mom_sun += sun_.mass * sun_.velocity;
    }
}

// function to calculate the special forces for Mercury and Sun only
// adding a general relativity correction to the Newtonian force
void SolarSystem::ForceMercury(){

    E_kin = 0;
    E_pot = 0;
    AngMom.zeros();

    double m_G = 4 * M_PI * M_PI;
    double c = 63240;

    for(Planet &body : planets){
        // reset forces on all planets
        body.force.zeros();
    }

    for(int i = 0; i < NumberOfPlanets(); i++){
        Planet &body1 = planets[i];
        for(int j = i+1; j < NumberOfPlanets(); j++){
            Planet &body2 = planets[j];
            vector3 dr_vector = body1.position - body2.position;
            vector3 dv_vector = body1.velocity - body2.velocity;
            double dr = dr_vector.length();

            double l = (dr_vector.cross(dv_vector)).length();
            body1.force -= ( (m_G*body1.mass*body2.mass*dr_vector) / (dr*dr*dr) ) * (1.0 + (3.0 * l * l) / (dr * dr * c * c) );
            body2.force += ( (m_G*body1.mass*body2.mass*dr_vector) / (dr*dr*dr) ) * (1.0 + (3.0 * l * l) / (dr * dr * c * c) );

            // updating energy
            E_pot += - ( m_G * body1.mass * body2.mass ) / dr;
        }
        E_kin += 0.5 * body1.mass * body1.velocity.length_squared();
    }

}


double SolarSystem::KineticEnergy() const {

    return E_kin;
}

double SolarSystem::PotentialEnergy() const {

    return E_pot;
}

double SolarSystem::TotalEnergy() const {

    return E_kin + E_pot;
}

void SolarSystem::Momentum(){

    cout << "Momentum vector: " << "(" << Mom_sun.x() + Mom_planets.x() << ", " << Mom_sun.y() + Mom_planets.y() << ", " << Mom_sun.z() + Mom_planets.z() << ")" << endl;
}


double SolarSystem::AngularMomentum(){

    return AngMom.length();
}

void SolarSystem::WriteToFile(string filename, string filename2){

    if(!myfile.is_open()) {
        myfile.open(filename.c_str(), ios_base::out);
    }

    for( Planet &body : planets ){
        myfile << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
    }


    if (!myfile2.is_open()){
        myfile2.open(filename2.c_str(), ios_base::out);
    }

    for( Planet &body : planets ){
        myfile2 << body.velocity.x() << " " << body.velocity.y() << " " << body.velocity.z() << "\n";
    }

}
