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

  for (int i = 0; i < particleNumber; i++){

      int count = 1;

      // COMPLETE HERE
      // get cosine and sine sums of the angle of particle i and its neighbours
      double sum_cos = std::cos(particles[i].theta);
      double sum_sin = std::sin(particles[i].theta);
      
      for (int j = 0 ; j < particleNumber; j++){

          if (i!=j){
              // calculate distance
              double dx = particles[j].x - particles[i].x;
              double dy = particles[j].y - particles[i].y;

              // periodic boundaries
              if(dx>Lx*0.5) dx-=Lx;
              if(dx<-Lx*0.5) dx+=Lx;
              if(dy>Ly*0.5) dy-=Ly;
              if(dy<-Ly*0.5) dy+=Ly;
              
              // calculate the distance between the two particles
              double dist = std::sqrt(dx*dx + dy*dy);
          
                // check if the distance is below the interaction radius
                if (dist < particles[i].r){
                  // accumulate orientation components from neighbour j
                  sum_cos +=  std::cos(particles[j].theta);
                  sum_sin +=  std::sin(particles[j].theta);
                  count+=1;
                }
          }
      }
      
      //COMPLETE HERE
        // normalise sine and cosine to get the local average
        sum_sin /= count;
        sum_cos /= count;

        // average + noise
        double avg_theta = std::atan2(sum_sin, sum_cos);
        new_theta[i] = avg_theta + this->noiseStrength*this->uniform(-M_PI,M_PI);
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