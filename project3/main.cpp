#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>

#include "time.h"
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

        // coordinates of Earth in 2D, for checking our algorithms
        //Planet &earth = Solar_System.createPlanet(vector3(1, 0, 0), vector3(0, 2*M_PI, 0), 3e-6);

        double T  = 5.0;
        double dt = 1e-3;
        int NumStep = T/dt;

        Solar_System.ForceAndEnergy();
        double energy_bf = Solar_System.TotalEnergy();
        double angmom_bf = Solar_System.AngularMomentum();

        // timing each algorithm
        clock_t start, finish;
        start = clock();

        //Euler integrator(dt);
        Verlet integrator(dt);
        for(int time = 0; time < NumStep; time++){

            integrator.integrate(Solar_System);
            Solar_System.WriteToFile("../positions.txt", "../velocities.txt");

        }

        finish = clock();
        cout << "Time algorithm: " << ( (double) ( finish - start ) / ((double)CLOCKS_PER_SEC )) << endl;

        double energy_af = Solar_System.TotalEnergy();
        double angmom_af = Solar_System.AngularMomentum();
        Solar_System.Momentum();

        cout << "Difference in energy: " << energy_af - energy_bf << endl;
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
        double angmom_bf = Solar_System.AngularMomentum();

        Verlet integrator(dt);
        for(int time = 0; time < NumStep; time++){

            integrator.integrate(Solar_System);
            Solar_System.WriteToFile("../positions_escape.txt", "../velocities_escape.txt");

        }

        double energy_af = Solar_System.TotalEnergy();
        double angmom_af = Solar_System.AngularMomentum();

        cout << "Difference in energy: " << energy_af - energy_bf << endl;
        cout << "Difference in angular momentum: " << angmom_af - angmom_bf << endl;
    }

    else if( atoi(argv[1])  == 3 ){
        // Sun-Earth-Jupiter system
        // Jupiter's mass has to be changed manually, and vary between 1.0, 10.0 and 1000.0

        Planet &sun = Solar_System.createPlanet(vector3(3.5555e-3, 3.4437e-3, -1.5959e-4), vector3(-7.4438e-4, 2.4914e-3, 1.5295e-5), 1.0);
        Planet &earth = Solar_System.createPlanet(vector3(8.9232e-1, 4.5235e-1, -1.7817e-4), vector3(-2.9316, 5.5834, -2.0685e-4), 3e-6);
        Planet &jupiter = Solar_System.createPlanet(vector3(-5.4257, -4.8938e-1, 1.2337e-1), vector3(0.2153, -2.6128, 6.0411e-3), 1.0);
        //Planet &jupiter = Solar_System.createPlanet(vector3(-5.4257, -4.8938e-1, 1.2337e-1), vector3(0.2153, -2.6128, 6.0411e-3), 10.0);
        //Planet &jupiter = Solar_System.createPlanet(vector3(-5.4257, -4.8938e-1, 1.2337e-1), vector3(0.2153, -2.6128, 6.0411e-3), 1000.0);

        double T  = 5.0;
        // we used dt = 1e-5 for Jupiter with mass 1.0 and 10.0
        double dt = 1e-5;
        // we used dt = 1e-7 for Jupiter with mass 1000.0
        //double dt = 1e-7;
        long int NumStep = T/dt;
        cout << NumStep << endl;

        Solar_System.ForceAndEnergy();
        double energy_bf = Solar_System.TotalEnergy();

        Verlet integrator(dt);
        for(long int time = 0; time < NumStep; time++){

            integrator.integrate(Solar_System);

            int printEvery = 1000;
            if(time % printEvery == 0) {
                Solar_System.WriteToFile("../positions_3body.txt", "../velocities_3body.txt");
            }
        }

        double energy_af = Solar_System.TotalEnergy();

        cout << "Difference in energy: " << energy_af - energy_bf << endl;

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

        // for pluto to go all the way around
        double T  = 300.0;
        double dt = 1e-4;
        long int NumStep = T/dt;
        cout << NumStep << endl;

        Solar_System.ForceAndEnergy();
        double energy_bf = Solar_System.TotalEnergy();

        Verlet integrator(dt);
        for(long int time = 0; time < NumStep; time++){

            integrator.integrate(Solar_System);

            int printEvery = 1000;
            if(time % printEvery == 0) {
                Solar_System.WriteToFile("../positions_system.txt", "../velocities_system.txt");
            }
        }

        double energy_af = Solar_System.TotalEnergy();
        Solar_System.Momentum();
        cout << "Difference in energy: " << energy_af - energy_bf << endl;

    }

    else if( atoi(argv[1])  == 5 ){
        // perihelion of mercury

        Planet &sun = Solar_System.createPlanet(vector3(0, 0, 0), vector3(0, 0, 0), 1.0);
        Planet &mercury = Solar_System.createPlanet(vector3(0.3075, 0, 0), vector3(0, 12.44, 0), 1.65e-7);

        ofstream myfile;
        string filename = "../perhelion_angle_GR.txt";
        if(!myfile.is_open()) {
            myfile.open(filename.c_str(), ios_base::out);
        }

        vector<Planet> &bodies = Solar_System.bodies();

        double T = 20.0;
        double dt = 1e-8;
        long int NumStep = T/dt;

        double rPrevPrev = 0;
        double rPrev = 0;
        double r = 0;

        double thetaPrev = 0;

        Verlet integrator(dt);
        for(long int time = 0; time < NumStep; time++){

            integrator.integrate(Solar_System);

            double x = bodies[1].position.x() - bodies[0].position.x();
            double y = bodies[1].position.y() - bodies[0].position.y();
            double thetaCurrent = atan2(y, x);

            double rCurrent = (bodies[1].position - bodies[0].position).length();

            if(rCurrent > rPrev && rPrev < rPrevPrev){
                // entered the loop when Mercury was at its closest to the Sun

                myfile << thetaPrev << endl;
                myfile << time << endl;
            }

            rPrevPrev = rPrev;
            rPrev = rCurrent;
            thetaPrev = thetaCurrent;
        }
    }

    cout << "Number of planets in our solar system: " << Solar_System.NumberOfPlanets()<< endl;

    return 0;
}
