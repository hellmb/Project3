#include "solarsystem.h"
#include <iostream>
#include <cmath>

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

    E_kin = 0;
    E_pot = 0;
    AngMom.zeros();

    double m_G = 4 * M_PI * M_PI;

    for(Planet &body : planets){
        // reset forces on all planets
        body.force.zeros();
    }

    for(int i = 0; i < NumberOfPlanets(); i++){
        Planet &body1 = planets[i];
        for(int j = i+1; j < NumberOfPlanets(); j++){
            Planet &body2 = planets[j];
            vector3 dr_vector = body1.position - body2.position;
            double dr = dr_vector.length();

            body1.force -= (m_G*body1.mass*body2.mass*dr_vector) / (dr*dr*dr);
            body2.force += (m_G*body1.mass*body2.mass*dr_vector) / (dr*dr*dr);

            // updating potential energy and angular momentum
            E_pot += - ( m_G * body2.mass * body1.mass ) / dr;
            AngMom += dr_vector.cross(body1.velocity);
        }

        // updating kinetic energy
        E_kin += 0.5 * body1.mass * body1.velocity.length_squared();
    }
}

void SolarSystem::ForceMercury(){

    E_kin = 0;
    E_pot = 0;
    AngMom.zeros();

    double m_G = 4 * M_PI * M_PI;
    double c = 3e8;

    for(Planet &body : planets){
        // reset forces on all planets
        body.force.zeros();
    }

    Planet &body_sun = planets[0];
    Planet &body_mercury = planets[1];

    vector3 dr_vector = body_sun.position - body_mercury.position;
    double dr = dr_vector.length();

    AngMom += dr_vector.cross(body_sun.velocity);
    body_sun.force -= ( (m_G*body_sun.mass*body_mercury.mass*dr_vector) / (dr*dr*dr) ) * (1.0 + (3.0 * AngMom.dot(AngMom)) / (dr * dr * c * c) );
    body_mercury.force += ( (m_G*body_sun.mass*body_mercury.mass*dr_vector) / (dr*dr*dr) ) * (1.0 + (3.0 * AngMom.dot(AngMom)) / (dr * dr * c * c) );

    // updating energy
    E_pot += - ( m_G * body_sun.mass * body_mercury.mass ) / dr;
    E_kin += 0.5 * body_sun.mass * body_sun.velocity.length_squared();

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
