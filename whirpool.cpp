#include "whirpool.h"

whirPool::whirPool(double x,double y,double r):xpos{x},ypos{y},radius{r}
{

}
cVector3d whirPool::poolForce(double x, double y,double t){

    cVector3d force(0,0,0);
    double factor = 50.0;
    double f = 100;
    double A = 5;
    double warning =2;
    double dis = sqrt((x-xpos)*(x-xpos)+(y-ypos)*(y-ypos));
    std::cout<<"Pool dis: "<<dis<<std::endl;
    double sgnx;
    double sgny;

    if (dis>radius&&dis<radius+warning){
        force(1) = A*cSinRad(f*t);
        force(0) = A*cSinRad(f*t);
    }else if(dis <= radius)
    {
        triggered = true;
        std::cout<<"In the pool!!!"<<std::endl;
        if(dis==0)
        {
            std::cout<<"In Hole!"<<std::endl;
            force(0)=0;
            force(1)=0;
        }else
        {
            if((y-ypos)==0)
            {
                std::cout<<"vertical move"<<std::endl;
                sgnx = cSign(x-xpos);
                force(0)= sgnx*factor*(radius-cAbs(x-xpos));
            }else if ((x-xpos)==0)
            {
                std::cout<<"horizon move"<<std::endl;
                sgny = cSign(y-ypos);
                force(1) = -sgny*factor*(radius-cAbs(y-ypos));
            }else
            {
                std::cout<<"Other moves"<<std::endl;
                sgnx =cSign(x-xpos);
                sgny = cSign(y-ypos);
                double ratio = cAbs(x-xpos)/cAbs(y-ypos);
                double x = sqrt(((radius-dis)*(radius-dis))/(1.0+1.0/(ratio*ratio)));
                double y = x/ratio;
                force(0)=sgnx*factor*x;
                force(1)= -sgny*factor*y;
                std::cout<<"Force(0):!"<<force(0)<<"Force(1)"<<force(1)<<std::endl;
            }
        }
    }
    else triggered = false;
    return force;
}
