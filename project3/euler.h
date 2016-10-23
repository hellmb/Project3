#ifndef EULER_H
#define EULER_H


class Euler{
public:
    double h;

    Euler(double dt);
    void integrate(class SolarSystem &system);
};


#endif // EULER_H
