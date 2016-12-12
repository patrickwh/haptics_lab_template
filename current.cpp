#include "current.h"

Current::Current(double x1,double y1,double x2,double y2,double r):x1{x1},x2{x2},y1{y1},y2{y2},entranceRadius{r}
{

}

cVector3d Current::getForceFeedback(double x, double y){

    double dist1 = sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
    double dist2 = sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
    if(dist1 <= entranceRadius){
        inArea1 = true;
    }else if(dist2 <= entranceRadius){
        inArea2 = true;
    }else{
        inArea1 = false;
        inArea2 = false;
    }

}

void Current::transferTriggered(double x,double y){
    triggered = true;
    transferFinished = false;
    transferStartx = inArea1?x1:x2;
    transferStarty = inArea1?y1:y2;
}

cVector3d Current::updatePosition(double x, double y){
    double dist1 = sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
    double dist2 = sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
    if(inArea1){
        if(dist2<(entranceRadius/2)){
            transferFinished = true;
            inArea1 = false;
            inArea2 = true;
        }
    }
    else if(inArea2){
        if(dist1<(entranceRadius/2)){
            transferFinished = true;
            inArea1 = true;
            inArea2 = false;
        }
    }
    else std::cout<<"ERROR! - in current update position";
}

cVector3d Current::getSpeed(){
    cVector3d speed(0.0,0.0,0.0);
    double totalspeed = 5;
    double deltax = 0.0;
    double deltay = 0.0;
    if(inArea1){
        deltax = x2-transferStartx;
        deltay = y2-transferStarty;
    }else{
        deltax = x1-transferStartx;
        deltay = y1-transferStarty;
    }
    double longest = sqrt(deltax*deltax+deltay*deltay);
    speed(0) = totalspeed*deltax/longest;
    speed(1) = totalspeed*deltay/longest;
    return speed;
}
