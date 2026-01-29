#include <iostream>
#include "system.hpp"
#include "box.hpp"

int main(){
    System mySystem(100,20,0.5,0.1,42);
    mySystem.updateRule();

    std::cout << "\n" << mySystem.noiseStrength << "\n" << mySystem.particleNumber << "\n";
    std::cout<<"The system has a simulation box of side "<<mySystem.simulationBox.getSidex()<<std::endl;
    std::cout<<"random num "<<mySystem.uniform(10, 20)<<std::endl;
}