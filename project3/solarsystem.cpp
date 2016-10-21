#include "solarsystem.h"
#include <iostream>
#include <cmath>

using namespace std;

SolarSystem::SolarSystem(){
    //E_kin;
    //E_pot;
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

    double m_G = 4 * M_PI * M_PI;

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

            body1.force -= (m_G*body1.mass*body2.mass*dr_vector) / (dr*dr*dr);
            body2.force += (m_G*body1.mass*body2.mass*dr_vector) / (dr*dr*dr);

            //body1.force += (m_G * dr_vector)/pow(dr,3);
            //body2.force -= (m_G * dr_vector)/pow(dr,3);
            // debugging output
            //cout << body2.mass << endl;
            //cout << body2.position(0)<< " " << body2.position(1) << " " << body2.position(2) << endl;
            //cout << body2.force(0) << " " << body2.force(1) << " " << body2.force(2) << endl;
            //cout << body2.force(1) << endl;

            // updating energy and angular momentum
            E_pot += - ( m_G * body2.mass * body1.mass ) / dr;
        }

        E_kin += 0.5 * body1.mass * body1.velocity.length_squared();
    }
}

void SolarSystem::ForceMercury(){

    E_kin = 0;
    E_pot = 0;

    double m_G = 4 * M_PI * M_PI;
    double c = 2.99e8;

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

            body1.force -= ( (m_G*body1.mass*body2.mass*dr_vector) / (dr*dr*dr) ) * (1.0 + (3.0 * angumom * angumom) / (dr * dr * c * c) );
            body2.force += (m_G*body1.mass*body2.mass*dr_vector) / (dr*dr*dr);

            // updating energy and angular momentum
            E_pot += - ( m_G * body2.mass * body1.mass ) / dr;
        }

        E_kin += 0.5 * body1.mass * body1.velocity.length_squared();
    }
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

void SolarSystem::WriteToFile(string filename, string filename2){
    if(!myfile.is_open()) {
        myfile.open(filename.c_str(), ios_base::out);
    }

    if (!myfile2.is_open()){
        myfile2.open(filename2.c_str(), ios_base::out);
    }

    //myfile << "Number of planets in solar system: " << NumberOfPlanets() << endl;
    for( Planet &body : planets ){
        myfile << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
    }

    //myfile2 << "Number of planets in solar system: " << NumberOfPlanets() << endl;
    for( Planet &body : planets ){
        myfile2 << body.velocity.x() << " " << body.velocity.y() << " " << body.velocity.z() << "\n";
    }

}
