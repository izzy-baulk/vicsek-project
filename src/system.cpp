#include "system.hpp"
#include <iostream>
#include <random>

System::System(int particleNumber,double sideLength, double timeStep,double noiseStrength, int seed)
  : simulationBox(sideLength, sideLength, 0.0, 0.0), gen(seed), uniformDist(0.0, 1.0) {
  // whatever we want to do as we instantiate the system
  std::cout << "I am constructing the System!";
  this->particleNumber = particleNumber;
  this->noiseStrength = noiseStrength;
  this->timeStep = timeStep;

  particles.resize(particleNumber);
}

double System::uniform(double min,double max) {
  return (max-min)*this->uniformDist(this->gen)+min;
}

void System::updateRule(){
  // the Vicsek update rule...
  std::cout << "Updating the system...";
}

