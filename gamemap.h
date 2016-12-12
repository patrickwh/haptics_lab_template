#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QList>
#include <QListIterator>
#include "chai3d.h"
#include "wave.h"
#include "rock.h"
#include "iceberg.h"
#include "whirpool.h"
#include "current.h"

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
    bool xpositionUpdated = false;
    bool ypositionUpdated = false;

    cVector3d getForceFeedback(cVector3d newPosition,bool butonClicked);

    Wave* wave;
    QList <Rock*> rock;
    QList <iceBerg*> iceberg;
    QList <whirPool*> whirpool;
    QList <Current*> current;

    GameMap();

    void setXspeed(double pos);
    void setYspeed(double pos);

    void updateXpos(double x);
    void updateYpos(double y);

    int blood = 1000;

    double xstart = 0;
    double ystart = 50;
    double currentx = xstart;
    double currenty = ystart;

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

    double base = 250.0;
    double speedScale = 1.0;

    void setTotalTime(double t);
    bool willBeBlocked(double x,double y);
};

#endif // GAMEMAP_H
