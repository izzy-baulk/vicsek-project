#include <iostream>
#include "header.hpp"

int main(){
    System mySystem(100,20,0.5,0.1);
    mySystem.updateRule();

    std::cout << "\n" << mySystem.noiseStrength << "\n" << mySystem.particleNumber;
}