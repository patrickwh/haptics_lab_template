#ifndef EXIT_H
#define EXIT_H

#include "chai3d.h"

using namespace chai3d;

class Exit
{
public:
    Exit(double x,double y,int t=Exit::TYPE_REAL);
    void updateState(double x,double y);
    double xpos;
    double ypos;
    int type;
    int state;
    double radius = 4.0;

    const static int TYPE_REAL = 0;
    const static int TYPE_FAKE_TRANSFER_TO_START = -1;
    const static int STATE_GAME_UNGOING = 0;
    const static int STATE_GAME_OVER = -1;
    const static int STATE_BACK_TO_START = 2;

};

#endif // EXIT_H
