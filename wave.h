#ifndef WAVE_H
#define WAVE_H

#include "chai3d.h"

using namespace chai3d;

class Wave
{
private:
    bool enabled = true;
public:
    Wave(int a, double f);
    int amplitude;
    double frequency;

    cVector3d getForceFeedback(int x,int y,double t);
    void setEnabled(bool value);

};

#endif // WAVE_H
