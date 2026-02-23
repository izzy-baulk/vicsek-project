#include "particle.hpp"
#include <iostream>

// This is the one called by particles.resize()
Particle::Particle() {
  this->x = 0.0;
  this->y = 0.0;
  this->theta = 0.0;
  this->r = 1.0;  // Standard Vicsek radius is usually 1.0
  this->v = 1;  // Standard Vicsek velocity
}

// Use the arguments passed to the constructor!
Particle::Particle(double x, double y, double theta, double r, double v) {
  this->x = x;
  this->y = y;
  this->theta = theta;
  this->r = r;
  this->v = v;
}