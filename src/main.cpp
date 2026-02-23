#include <iostream>
#include <cstdlib>
#include "system.hpp"
#include "box.hpp"

int main(int argc, char* argv[]){
    double noiseStrength = std::stof(argv[1]);
    System mySystem(500,20,1,noiseStrength,42);
    mySystem.randomStart();

    std::cout << "\n" << mySystem.noiseStrength << "\n" << mySystem.particleNumber << "\n";
    std::cout<<"The system has a simulation box of side "<<mySystem.simulationBox.getSidex()<<std::endl;
    std::cout<<"random num "<<mySystem.uniform(10, 20)<<std::endl;

    std::string initf("init.conf");
    mySystem.saveConfig(initf);

    for (int i = 0; i < 500; i++){
        mySystem.updateRule();
        std::string s = std::to_string(i);
        std::string filename = "output/" + s;
        mySystem.saveConfig(filename);
    };
}