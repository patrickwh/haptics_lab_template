#include "iceberg.h"

iceBerg::iceBerg(double x,double y,double r):xpos{x},ypos{y},radius{r}
{

}
cVector3d iceBerg::iceForce(double x, double y)
{
    cVector3d force(0,0,0);
    cVector3d pos(x,y,0);
    cVector3d pos2(x,y,0);
    cVector3d proxyPos;
    double factor = -20.0;

    double sgnx =cSign(x-xpos);
    double sgny = cSign(y-ypos);
    double dis = sqrt((x-xpos)*(x-xpos)+(y-ypos)*(y-ypos));
    if(triggered){

//        pos.normalize();
//        pos.mul(radius);
//        pos2.normalize();
//        pos2.mul(factor*(radius));
//        force = pos2;


        force(1)=-sgny*factor*cAbs(y-ypos);
        force(0) = sgnx*factor*cAbs(x-xpos);
        proxyPos.x(x);
        proxyPos.y(y);





        std::cout<<"Hit the iceberg!!!"<<std::endl;


        //triggered = true;
    }else{
        //triggered = false;
    }
    return force;
}

bool iceBerg::willBeBlocked(double x,double y){
    double dis = sqrt((x-xpos)*(x-xpos)+(y-ypos)*(y-ypos));
    std::cout<<"Dis with iceberg :"<<dis<<std::endl;
    if(dis <= radius) triggered = true;
    else triggered = false;
    return triggered;
}
