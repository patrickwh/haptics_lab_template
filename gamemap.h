#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "chai3d.h"
#include "wave.h"
#include "rock.h"
#include "iceberg.h"
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

    GameMap();

    void setXspeed(double pos);
    void setYspeed(double pos);

    void updateXpos(double x);
    void updateYpos(double y);

    int blood = 1000;

    int currentx = 0;
    int currenty = 50;

    int xaccm = 0;
    int yaccm = 0;

    double xthreshold = 0.015;
    double ythreshold = 0.015;
    double ymaxtmp = 0.045;
    double xmaxtmp = 0.036;
    double xstep = (xmaxtmp - xthreshold)/2;
    double ystep = (ymaxtmp - ythreshold)/2;

    double xspeed;
    double yspeed;

    int incbase = 1000;
    int xincth = 1000;
    int yincth = 1000;

    void setTotalTime(double t);
    bool willBeBlocked(int x,int y);
};

#endif // GAMEMAP_H
