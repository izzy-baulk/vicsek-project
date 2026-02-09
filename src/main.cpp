#include <iostream>
#include "system.hpp"
#include "box.hpp"

int main(){
    System mySystem(100,20,0.5,0.1,42);
    mySystem.randomStart();

    std::cout << "\n" << mySystem.noiseStrength << "\n" << mySystem.particleNumber << "\n";
    std::cout<<"The system has a simulation box of side "<<mySystem.simulationBox.getSidex()<<std::endl;
    std::cout<<"random num "<<mySystem.uniform(10, 20)<<std::endl;

    std::string initf("init.conf");
    mySystem.saveConfig(initf);

    for (int i = 0; i < 100; i++){
        mySystem.updateRule();
        std::string s = std::to_string(i);
        std::string filename = "output/" + s;
        mySystem.saveConfig(filename);
    };
}