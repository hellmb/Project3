#include <iostream>
#include <cmath>

#include "verlet.h"
#include "solarsystem.h"

void mercury_solver() {

    SolarSystem Solar_System;

    double energy_bf = Solar_System.TotalEnergy();


    double T = 20.0;
    double dt = 1e-6;
    long int NumStep = T/dt;

    double rPrevPrev = 0;
    double rPrev = 0;
    double r = 0;

    vector3 PrevPos(0, 0, 0);

    Verlet integrator(dt);
    for(long int time = 0; time < NumStep; time++){

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
