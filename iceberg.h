#ifndef ICEBERG_H
#define ICEBERG_H

#include "chai3d.h"
using namespace chai3d;

class iceBerg
{
public:
    iceBerg(double x,double y,double r);
    cVector3d iceForce(double x,double y,double t);
    bool triggered = false;
public:
    double xpos =0;
    double ypos = 0;
    double radius =0;
    bool willBeBlocked(double x,double y);
    double damage = 0.009;
};

#endif // ICEBERG_H
