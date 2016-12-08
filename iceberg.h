#ifndef ICEBERG_H
#define ICEBERG_H

#include "chai3d.h"
using namespace chai3d;

class iceBerg
{
public:
    iceBerg(int x,int y,int r);
    cVector3d iceForce(int x,int y);
    bool triggered = false;
public:
    int xpos =0;
    int ypos = 0;
    int radius =0;
    bool willBeBlocked(int x,int y);
};

#endif // ICEBERG_H
