#include "wave.h"

Wave::Wave(int a, double f):amplitude{a},frequency{f}
{

}

cVector3d Wave::getForceFeedback(int x,int y, double t){

    cVector3d force(0,0,0);
    if(enabled) force(2) = amplitude*cSinRad(frequency*t);
    return force;
}

void Wave::setEnabled(bool value){
    enabled = value;
}
