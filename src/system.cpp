#include "header.hpp"
#include <iostream>

System::System(int particleNumber,double sideLength, double timeStep,double noiseStrength){
  // whatever we want to do as we instantiate the system
  std::cout << "I am constructing the System!";
  this->particleNumber = particleNumber;
  this->noiseStrength = noiseStrength;
  this->timeStep = timeStep;
  this->timeStep = timeStep;

}

void System::updateRule(){
  // the Vicsek update rule...
  std::cout << "Updating the system...";
}