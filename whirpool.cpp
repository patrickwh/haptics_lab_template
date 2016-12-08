#include "whirpool.h"

whirPool::whirPool(int x,int y,int r):xpos{x},ypos{y},radius{r}
{

}
cVector3d whirPool::poolForce(int x, int y){
     cVector3d force(0,0,0);
     std::cout<<"Range!!!"<<std::endl;

  if((cAbs(x-xpos)+cAbs(y-ypos))<=radius)
     {
        int factor = -1000;
        force(0) = factor/(x-xpos);
        force(1) =  factor/(y-ypos);
     }
     return force;
}

bool whirPool::willBeStuck(int x,int y){
    if((cAbs(x-xpos)+cAbs(y-ypos)) <= radius) triggered = true;
    else triggered = false;
    return triggered;
}

