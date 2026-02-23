#define _USE_MATH_DEFINES

#include "system.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
#include <string>

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
  // Notice that "this" is not stricly needed for the member variables

  // correctly initialise new_theta as a vector of doubles sized to particleNumber.
  std::vector<double> new_theta(particleNumber);
  // get Lx and Ly values
  double Lx = this->simulationBox.getSidex();
  double Ly = this->simulationBox.getSidey();

  for (int i = 0; i < particleNumber; i++) {
    double sum_cos = 0; 
    double sum_sin = 0;

    // We include particle 'i' in its own average by iterating j from 0 to particleNumber
    for (int j = 0; j < particleNumber; j++) {
        double dx = particles[j].x - particles[i].x;
        double dy = particles[j].y - particles[i].y;

        // Periodic Boundary Condition (PBC) for distance
        if (dx > Lx * 0.5)  dx -= Lx;
        if (dx < -Lx * 0.5) dx += Lx;
        if (dy > Ly * 0.5)  dy -= Ly;
        if (dy < -Ly * 0.5) dy += Ly;

        double distSq = dx*dx + dy*dy;
        
        // Use squared distance comparison to save computation (no sqrt needed)
        if (distSq < (particles[i].r * particles[i].r)) {
            sum_cos += std::cos(particles[j].theta);
            sum_sin += std::sin(particles[j].theta);
        }
    }

      // atan2 handles the normalization/averaging internally
      double avg_theta = std::atan2(sum_sin, sum_cos);
      
      // Apply noise: eta * random_angle
      new_theta[i] = avg_theta + (this->noiseStrength * this->uniform(-M_PI, M_PI));
  }
  // move the particles
  for (int i = 0; i < particleNumber; i++){
      particles[i].x += std::cos(new_theta[i])*particles[i].v*this->timeStep;
      // COMPLETE HERE
      // update also the y coordinate
        particles[i].y += std::sin(new_theta[i])*particles[i].v*this->timeStep;
      
      particles[i].theta = new_theta[i];
      // periodic boundaries
      if (particles[i].x >Lx) particles[i].x -= Lx;
      if (particles[i].x <0) particles[i].x += Lx;
      if (particles[i].y >Ly) particles[i].y -= Ly;
      if (particles[i].y <0) particles[i].y += Ly;
  }
}

void System::randomStart(){
  for (Particle &p : this->particles){
    p.x = this->uniform(0,this->simulationBox.getSidex());
    p.y = this->uniform(0,this->simulationBox.getSidey());
    p.theta = this->uniform(-1* M_PI, M_PI);
  }
}

void System::saveConfig(std::string &filename)
{   
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return; // Exit if file cannot be opened
    }
    outFile << std::to_string(particles.size())+"\nParticles"<<std::endl;
    
    // Write particle properties to the file

    for (size_t i = 0; i < particles.size(); ++i) {
        outFile << i << " " << particles[i].x <<" "<<particles[i].y<<" "<<particles[i].theta << std::endl;
    }
    
    outFile.close(); // Close the file
}    