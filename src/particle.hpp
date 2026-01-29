#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector> //to use standard C++ vectors

class Particle {
    public:
        Particle(); //default constructor
        Particle(double x, double y, double theta, double r, double v); //parametrised constructor
        double x;
        double y;
        double theta;
        double r;
        double v;
};

#endif