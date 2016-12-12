#include "current.h"

Current::Current(double x1,double y1,double x2,double y2,double r):x1{x1},x2{x2},y1{y1},y2{y2},entranceRadius{r}
{

}

cVector3d Current::getForceFeedback(double x, double y){

    double dist1 = sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
    double dist2 = sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
    if(dist1 <= entranceRadius){
        inArea = true;
    }else if(dist2 <= entranceRadius){
        inArea = true;
    }else inArea = false;

}
