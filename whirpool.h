#ifndef WHIRPOOL_H
#define WHIRPOOL_H
#include "chai3d.h"
using namespace chai3d;

class whirPool
{
public:
    whirPool(double x, double y, double r);
    cVector3d poolForce(double x,double y);
//    bool istriggered = false;
public:
    double xpos = 0;
    double ypos = 0;
    double radius = 0;
//    bool willBeStuck(int x,int y);
};

#endif // WHIRPOOL_H
