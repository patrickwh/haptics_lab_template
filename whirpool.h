#ifndef WHIRPOOL_H
#define WHIRPOOL_H
#include "chai3d.h"
using namespace chai3d;

class whirPool
{
public:
    whirPool(int x, int y, int r);
    cVector3d poolForce(int x,int y);
    bool triggered = false;
    int xpos = 0;
    int ypos = 0;
    int radius = 0;
    bool willBeStuck(int x,int y);
};

#endif // WHIRPOOL_H
