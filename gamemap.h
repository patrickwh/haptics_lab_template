#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QList>
#include <QListIterator>
#include <stdlib.h>
#include "chai3d.h"
#include "wave.h"
#include "rock.h"
#include "iceberg.h"
#include "whirpool.h"
#include "current.h"
#include "exit.h"
#include "bonuspoint.h"

using namespace chai3d;

class GameMap
{
public:

    double totalTime;

    double xmax = 100;
    double ymax = 100;
    double destx = 99;
    double desty = 99;
    bool blocked = false;
    bool xpositionUpdated = false;
    bool ypositionUpdated = false;
    bool blockedByCurrent = false;
    bool gameOver = false;

    cVector3d getForceFeedback(cVector3d newPosition,bool buttonClicked);

    Wave* wave;
    Current* triggeredCurrent = nullptr;
    QList <Rock*> rock;
    QList <iceBerg*> iceberg;
    QList <whirPool*> whirpool;
    QList <Current*> current;
    QList <Exit*> exit;
    QList <BonusPoint*> bonus;

    GameMap();

    void setXspeed(double pos);
    void setYspeed(double pos);
    void updateCurrentx(double x);
    void updateCurrenty(double y);
    void updateXpos(double x);
    void updateYpos(double y);    
    void setTotalTime(double t);
    void generateRandomBouns(int num);

    double bloodMax = 1000.0;
    double blood = bloodMax;

    double xstart = 50;
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

    bool willBeBlocked(double x,double y);
};

#endif // GAMEMAP_H
