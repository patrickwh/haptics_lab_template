#include "iceberg.h"

iceBerg::iceBerg(int x,int y,int r):xpos{x},ypos{y},radius{r}
{

}
cVector3d iceBerg::iceForce(int x, int y)
{
    cVector3d force(0,0,0);
    if(triggered){
        force(0) = -1000*(x-xpos);
        //force(1) = -1000*(y-ypos);
        //triggered = true;
    }else{
        //triggered = false;
    }
    return force;
}

bool iceBerg::willBeBlocked(int x,int y){
    if((cAbs(x-xpos)+cAbs(y-ypos)) <= radius) triggered = true;
    else triggered = false;
    return triggered;
}
