#include "box.hpp"
#include <iostream>

Box::Box(){
    // an empty constructor
}
Box::Box(double lx, double ly, double x0, double y0){
     //this constructor actually assigns values
     this->sidex = lx;
     this->sidey = ly;
     this->x0 = x0;
     this->y0 = y0;
}

void Box::setSides(double lx, double ly){
    sidex = lx;
    sidey = ly;
}

void Box::setOrigin(double x, double y){
    x0 = x;
    y0 = y;
}

double Box::getSidex(){
    return sidex;

}

double Box::getSidey(){
    return sidey;
}


