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


int main(int argc, char *argv[]) {

    SolarSystem Solar_System = SolarSystem();

    if( atoi(argv[1]) == 1 ){
        // Sun-Earth system

        Planet &sun = Solar_System.createPlanet(vector3(0, 0, 0), vector3(0, 0, 0), 1.0);
        Planet &earth = Solar_System.createPlanet(vector3(8.9232e-1, 4.5235e-1, -1.7817e-4), vector3(-2.9316, 5.5834, -2.0685e-4), 3e-6);

        double T  = 5.0;
        double dt = 1e-3;
        int NumStep = T/dt;
        cout << NumStep << endl;

        Solar_System.ForceAndEnergy();
        double energy_bf = Solar_System.TotalEnergy();
        //double mom_bf = ...
        double angmom_bf = Solar_System.AngularMomentum();

        //Euler integrator(dt);
        Verlet integrator(dt);
        for(int time = 0; time < NumStep; time++){

            integrator.integrate(Solar_System);
            Solar_System.WriteToFile("../positions.txt", "../velocities.txt");

        }

        double energy_af = Solar_System.TotalEnergy();
        double angmom_af = Solar_System.AngularMomentum();

        cout << "Difference in energy: " << energy_bf - energy_af << endl;
        cout << "Difference in angular momentum: " << angmom_af - angmom_bf << endl;
    }

    else if( atoi(argv[1])  == 2 ){
        // escaping planet from the solar system

        Planet &sun = Solar_System.createPlanet(vector3(0, 0, 0), vector3(0, 0, 0), 1.0);
        Planet &too_fun = Solar_System.createPlanet(vector3(1, 0, 0), vector3(0, 2.8*M_PI, 0), 3e-6);

        double T  = 1.0;
        double dt = 1e-3;
        long int NumStep = T/dt;
        cout << NumStep << endl;

        Solar_System.ForceAndEnergy();
        double energy_bf = Solar_System.TotalEnergy();
        //double mom_bf = ...
        double angmom_bf = Solar_System.AngularMomentum();

        Verlet integrator(dt);
        for(int time = 0; time < NumStep; time++){

            integrator.integrate(Solar_System);
            Solar_System.WriteToFile("../positions_escape.txt", "../velocities_escape.txt");

        }

        double energy_af = Solar_System.TotalEnergy();
        double angmom_af = Solar_System.AngularMomentum();

        cout << "Difference in energy: " << energy_bf - energy_af << endl;
        cout << "Difference in angular momentum: " << angmom_af - angmom_bf << endl;
    }

    else if( atoi(argv[1])  == 3 ){
        // Sun-Earth-Jupiter, where the Sun is not the mass center
        // Jupiter's mass has to be changed manually, and vary between 1.0, 10.0 and 1000.0

        Planet &sun = Solar_System.createPlanet(vector3(3.5555e-3, 3.4437e-3, -1.5959e-4), vector3(-7.4438e-4, 2.4914e-3, 1.5295e-5), 1.0);
        Planet &earth = Solar_System.createPlanet(vector3(8.9232e-1, 4.5235e-1, -1.7817e-4), vector3(-2.9316, 5.5834, -2.0685e-4), 3e-6);
        //Planet &jupiter = Solar_System.createPlanet(vector3(-5.4257, -4.8938e-1, 1.2337e-1), vector3(0.2153, -2.6128, 6.0411e-3), 1.0);
        //Planet &jupiter = Solar_System.createPlanet(vector3(-5.4257, -4.8938e-1, 1.2337e-1), vector3(0.2153, -2.6128, 6.0411e-3), 10.0);
        Planet &jupiter = Solar_System.createPlanet(vector3(-5.4257, -4.8938e-1, 1.2337e-1), vector3(0.2153, -2.6128, 6.0411e-3), 1000.0);

        double T  = 5.0;
        double dt = 1e-5;
        long int NumStep = T/dt;
        cout << NumStep << endl;

        Solar_System.ForceAndEnergy();
        double energy_bf = Solar_System.TotalEnergy();
        //double mom_bf = ...

        Verlet integrator(dt);
        for(int time = 0; time < NumStep; time++){

            integrator.integrate(Solar_System);

            int printEvery = 100;
            if(time % printEvery == 0) {
                Solar_System.WriteToFile("../positions_3body.txt", "../velocities_3body.txt");
            }
        }

        double energy_af = Solar_System.TotalEnergy();
        // check if momentum should be conserved for more than 2 bodies

        cout << "Difference in energy: " << energy_bf - energy_af << endl;

    }

    else if( atoi(argv[1])  == 4 ){
        // complete solar system

        Planet &sun = Solar_System.createPlanet(vector3(3.5555e-3, 3.4437e-3, -1.5959e-4), vector3(-7.4438e-4, 2.4914e-3, 1.5295e-5), 1.0);
        Planet &mercury = Solar_System.createPlanet(vector3(-3.9067e-1, -5.3842e-2, 3.1326e-2), vector3(-0.6591, -9.7181, 0.7339), 1.65e-7);
        Planet &venus = Solar_System.createPlanet(vector3(2.9535e-1, -6.6297e-1, -2.6136e-2), vector3(6.7124, 2.9387, -0.3471), 2.45e-6);
        Planet &earth = Solar_System.createPlanet(vector3(8.9232e-1, 4.5235e-1, -1.7817e-4), vector3(-2.9316, 5.5834, -2.0685e-4), 3e-6);
        Planet &mars = Solar_System.createPlanet(vector3(1.2012, -6.8454e-1, -4.3970e-2), vector3(2.7378, 4.8691, 0.0348), 3.3e-7);
        Planet &jupiter = Solar_System.createPlanet(vector3(-5.4257, -4.8938e-1, 1.2337e-1), vector3(0.2153, -2.6128, 6.0411e-5), 9.5e-4);
        Planet &saturn = Solar_System.createPlanet(vector3(-2.2414, -9.7812, 2.5927e-1), vector3(1.8735, -0.4613, -0.0665), 2.75e-4);
        Planet &uranus = Solar_System.createPlanet(vector3(1.8456e+1, 7.5787, -2.1095e-1), vector3(-0.5558, 1.2610, 0.0119), 4.4e-5);
        Planet &neptune = Solar_System.createPlanet(vector3(2.8266e+1, -9.9074, -4.4740e-1), vector3(0.3712, 1.0881, -0.0308), 5.15e-5);
        Planet &pluto = Solar_System.createPlanet(vector3(9.4392, -3.1817e+1, 6.7425e-1), vector3(1.1240, 0.0922, -0.0331), 6.55e-9);

        // years -> T = 1 -> 1 earth year
        double T  = 300.0; // for pluto to go all the way around
        double dt = 1e-4;
        long int NumStep = T/dt;
        cout << NumStep << endl;

        Solar_System.ForceAndEnergy();
        double energy_bf = Solar_System.TotalEnergy();
        //double mom_bf = ...

        Verlet integrator(dt);
        for(int time = 0; time < NumStep; time++){

            integrator.integrate(Solar_System);

            int printEvery = 1000;
            if(time % printEvery == 0) {
                Solar_System.WriteToFile("../positions_system.txt", "../velocities_system.txt");
            }
        }

        double energy_af = Solar_System.TotalEnergy();

        cout << "Difference in energy: " << energy_bf - energy_af << endl;
    }

    else if( atoi(argv[1])  == 5 ){
        // perihelion of mercury

        Planet &sun = Solar_System.createPlanet(vector3(0, 0, 0), vector3(0, 0, 0), 1.0);
        Planet &mercury = Solar_System.createPlanet(vector3(0.3075, 0, 0), vector3(0, 12.44, 0), 1.65e-7);

        double T = 20.0;
        double dt = 1e-6;
        long int NumStep = T/dt;
        cout << NumStep << endl;

        Solar_System.ForceAndEnergy();
        double energy_bf = Solar_System.TotalEnergy();

        double rPrevPrev = 0;
        double rPrev = 0;
        double r = 0;

        vector3 PrevPos(0, 0, 0);

        Verlet integrator(dt);
        for(int time = 0; time < NumStep; time++){

            integrator.integrate(Solar_System);

            Planet &body_sun = Solar_System.planets[0];
            Planet &body_mercury = Solar_System.planets[1];
            vector3 pos = body_mercury.position - body_sun.position;
            r = pos.length();

            if(r > rPrev && rPrev < rPrevPrev){
                // every new position where Mercury is at perihelion
                double x = PrevPos.x();
                double y = PrevPos.y();
                double z = PrevPos.z();

                double degree = atan2(y, x);
                double arc_sec = ( 3600 * 180 / M_PI ) * degree;

                cout << "Perihelion angle: " << atan2(y, x) << endl;
                cout << "Arc seconds: " << arc_sec << endl;
                cout << "Time: " << time << endl;

            }

            rPrevPrev = rPrev;
            rPrev = r;
            PrevPos = pos;

            int printEvery = 1000;
            if(time % printEvery == 0) {
                Solar_System.WriteToFile("../positions_perihelion.txt", "../velocities_perihelion.txt");
            }
        }

        double energy_af = Solar_System.TotalEnergy();

        cout << "Difference in energy: " << energy_bf - energy_af << endl;

    }

    cout << "Number of planets: " << Solar_System.NumberOfPlanets()<< endl;

    return 0;
}
