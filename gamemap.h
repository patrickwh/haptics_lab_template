#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "chai3d.h"
#include "wave.h"
#include "rock.h"
#include "iceberg.h"
#include "whirpool.h"

using namespace chai3d;

class GameMap
{
public:

    double totalTime;

    int xmax = 100;
    int ymax = 100;
    int destx = 99;
    int desty = 99;
    bool blocked = false;

    cVector3d getForceFeedback(int xpos,int ypos);

    Wave* wave;
    Rock* rock;
    iceBerg* iceberg;
    whirPool* whirpool;

    GameMap();

    void setXspeed(double pos);
    void setYspeed(double pos);

    void updateXpos(double x);
    void updateYpos(double y);

    int blood = 1000;

    double currentx = 0;
    double currenty = 50;

    double xthreshold = 0.015;
    double ythreshold = 0.015;
    double ymaxtmp = 0.045;
    double xmaxtmp = 0.036;
    double xstep = (xmaxtmp - xthreshold)/2;
    double ystep = (ymaxtmp - ythreshold)/2;

    double xspeed;
    double yspeed;

    double xinc;
    double yinc;

    double base = 1000.0;

    void setTotalTime(double t);
    bool willBeBlocked(double x,double y);
};

#endif // GAMEMAP_H
