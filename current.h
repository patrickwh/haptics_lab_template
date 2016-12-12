#ifndef CURRENT_H
#define CURRENT_H

#include "chai3d.h"
using namespace chai3d;

class Current
{
public:
    Current(double x1,double y1,double x2,double y2,double r);
    cVector3d getForceFeedback(double x,double y);
    double entranceRadius;
    double x1;
    double y1;
    double x2;
    double y2;
    bool inArea = false;
};

#endif // CURRENT_H
