#include "particle.hpp"
#include <iostream>

Particle::Particle(){
    // an empty constructor
}
Particle::Particle(double x, double y, double theta, double r, double v) {
  // whatever we want to do as we instantiate the system
  std::cout << "I am constructing the particle!";
  this->x = 0;
  this->y = 0;
  this->theta = 0;
  this->r = 0.1;
  this->v = 0.5;
}