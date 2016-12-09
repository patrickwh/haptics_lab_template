#include "whirpool.h"

whirPool::whirPool(double x,double y,double r):xpos{x},ypos{y},radius{r}
{

}
cVector3d whirPool::poolForce(double x, double y){

    cVector3d force(0,0,0);
    double factor = 50.0;
    double dis = sqrt((x-xpos)*(x-xpos)+(y-ypos)*(y-ypos));
    std::cout<<"Pool dis: "<<dis<<std::endl;
    double sgnx;
    double sgny;

    if(dis <= radius)
    {
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
                if((x-xpos)==0){
                    force(0)=0;
                }else
                {
                    force(0)= sgnx*factor*(radius-cAbs(x-xpos));
                }
            }else if ((x-xpos)==0)
            {
                std::cout<<"horizon move"<<std::endl;
                sgny = cSign(y-ypos);
                if((y-ypos)==0)
                {
                    force(1)=0;
                }else
                {
                    force(1) = sgny*factor*(radius-cAbs(y-ypos));
                }
            }else
            {
                std::cout<<"Other moves"<<std::endl;
                sgnx =cSign(x-xpos);
                sgny = cSign(y-ypos);
                double ratio = cAbs(x-xpos)/cAbs(y-ypos);
                double x = sqrt((radius-dis)/(1.0+1.0/(ratio*ratio)));
                double y = x/ratio;
//                std::cout<<"In pool!"<<std::endl;
                force(0)=sgnx*factor*x;
                force(1)= sgny*factor*y;
                std::cout<<"Force(0):!"<<force(0)<<"Force(1)"<<force(1)<<std::endl;
            }
        }
    }
    return force;
}
