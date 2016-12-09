#include "rock.h"

Rock::Rock(int x,int y,int w,int h):xpos{x},ypos{y},width{w},height{h}
{

}

void Rock::setEnabled(bool v){
    enabled = v;
}

cVector3d Rock::getForceFeedback(double x,double y,double t,bool xupdate,bool yupdate){
    cVector3d force(0,0,0);
    int A = 10;
    double f = 100;

    if(enabled){
        if(x > xpos && x< xpos+height && y> ypos && y< ypos+width)
        {
            triggered = true;
            if(xupdate || yupdate) force(2) = A*cSinRad(f*t);
            if(yupdate) force(1) = A*cSinRad(f*t);
            if(xupdate) force(0) = A*cSinRad(f*t);
        }else{
            triggered = false;
        }
    }
    return force;
}
