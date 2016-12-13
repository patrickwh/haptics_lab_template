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
    Rock(double x,double y,double w,double h);

    bool triggered = false;
    double xpos;
    double ypos;
    double width;
    double height;
    double damage = 0.07;

    cVector3d getForceFeedback(double x,double y, double t,bool xupdate,bool yupdate);

};

#endif // ROCK_H
