#ifndef CURRENT_H
#define CURRENT_H

#include "chai3d.h"
using namespace chai3d;

class Current
{
public:
    Current(double x1,double y1,double x2,double y2,double r);
    cVector3d getForceFeedback(double x,double y);
    cVector3d updatePosition(double x,double y);
    cVector3d getSpeed();
    void transferTriggered(double x,double y);
    double entranceRadius;
    double x1;
    double y1;
    double x2;
    double y2;
    double transferStartx;
    double transferStarty;
    bool inArea1 = false;
    bool inArea2 = false;
    bool triggered = false;
    bool transferFinished = true;
};

#endif // CURRENT_H
