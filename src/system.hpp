#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector> //to use standard C++ vectors
#include "box.hpp" //yet to be created!
#include "particle.hpp" //yet to be created!
#include <random>

class System {
  public:
    System(int particleNumber,double sideLength, double timeStep,double noiseStrength, int seed);
    int   particleNumber;
    double noiseStrength;
    double sideLength;
    double timeStep;
    Box simulationBox;
    std::vector<Particle> particles;
    std::mt19937 gen;
    std::uniform_real_distribution<double> uniformDist;
    double uniform(double min, double max);

    void updateRule();
};

#endif