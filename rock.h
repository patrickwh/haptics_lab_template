#ifndef ROCK_H
#define ROCK_H

#include "chai3d.h"
using namespace chai3d;

class Rock
{

private:
    bool enabled = true;
    void setEnabled(bool v);
public:
    Rock(int x,int y,int w,int h);

    bool triggered = false;
    int xpos;
    int ypos;
    int width;
    int height;

    cVector3d getForceFeedback(int x,int y, double t);

};

#endif // ROCK_H
