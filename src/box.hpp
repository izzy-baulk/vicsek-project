#ifndef BOX_H
#define BOX_H

#include <vector> //to use standard C++ vectors

class Box {
    public:
        Box(); //default constructor with no parameters
        Box(double lx, double ly, double x0, double y0); //parametrised constructor
        void setSides(double lx, double ly);
        void setOrigin(double x, double y);
        double getSidex();
        double getSidey();
    private:
        double sidex;
        double sidey;
        double x0;
        double y0;
};

#endif