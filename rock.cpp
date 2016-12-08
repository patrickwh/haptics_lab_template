#include "rock.h"

Rock::Rock(int x,int y,int w,int h):xpos{x},ypos{y},width{w},height{h}
{

}

void Rock::setEnabled(bool v){
    enabled = v;
}

cVector3d Rock::getForceFeedback(int x,int y,double t){
    cVector3d force(0,0,0);
    int A = 10;
    double f = 100;
    if(enabled){
        if(x > xpos && x< xpos+height && y> ypos && y< ypos+width)
        {
            triggered = true;
            force(2) = A*cSinRad(f*t);
        }else{
            triggered = false;
        }
    }
    return force;
}
