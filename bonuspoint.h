#ifndef BONUSPOINT_H
#define BONUSPOINT_H

#include "chai3d.h"

using namespace chai3d;

class BonusPoint
{
public:
    BonusPoint(double x,double y,double a=100.0);
    void updateState(double x,double y);
    double ammount;
    double xpos;
    double ypos;
    double radius;
    bool valid = true;
    bool triggered = false;
};

#endif // BONUSPOINT_H
