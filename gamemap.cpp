#include "gamemap.h"



cVector3d GameMap::getForceFeedback(int xpos, int ypos){
    cVector3d fwave = wave->getForceFeedback(xpos,ypos,totalTime);
    cVector3d frock = rock->getForceFeedback(xpos,ypos,totalTime);
    cVector3d fice = iceberg->iceForce(xpos,ypos);
    cVector3d fpool = whirpool->poolForce(xpos,ypos);

    //std::cout<<"f: "<<fice(0)<<" "<<fice(1)<<";";

    cVector3d f(0,0,0);

    if(rock->triggered){
        f.add(frock);
    }else{
        f.add(fwave);
    }
    f.add(fice);
    f.add(fpool);

    return f;
}

void GameMap::setTotalTime(double t){
    totalTime = t;
}

GameMap::GameMap(){
    int ainit = 10;
    double finit = 1;
    wave = new Wave(ainit,finit);
    rock = new Rock(50,25,50,5);
    iceberg = new iceBerg(30,50,5);
    whirpool = new whirpool(10,50,5);
}

bool GameMap::willBeBlocked(double x,double y){
    return iceberg->willBeBlocked(x,y);
}

void GameMap::setXspeed(double pos){
    if(pos<=xthreshold){
        xspeed = 0;
        xinc = 0;
    }else{
        xspeed = (pos-xthreshold)/xstep;
        xinc = xspeed/base;
    }
}

void GameMap::setYspeed(double pos){
    if(pos<=ythreshold){
        yspeed = 0;
        yinc = 0;
    }else{
        yspeed = (pos-ythreshold)/ystep;
        yinc = yspeed/base;
    }
}

void GameMap::updateXpos(double x){
    double xabs = cAbs(x);
    if(xabs>xthreshold){
        setXspeed(xabs);
        if(x>0){
            currentx += xinc;int
            if(willBeBlocked(currentx,currenty)) currentx-=xinc;
            currentx = currentx>=xmax?xmax:currentx;
        }
        if(x<0){
            currentx -= xinc;
            if(willBeBlocked(currentx,currenty)) currentx+=xinc;
            currentx = currentx<=0?0:currentx;
       }
    }
}

void GameMap::updateYpos(double y){
    double yabs = cAbs(y);
    if(yabs>ythreshold){
        setYspeed(yabs);
        if(y>0){
            currenty += yinc;
            if(willBeBlocked(currentx,currenty)) currenty-=yinc;
            currenty = currenty>=ymax?ymax:currenty;
        }
        if(y<0){
            currenty -= yinc;
            if(willBeBlocked(currentx,currenty)) currenty+=yinc;
            currenty = currenty<=0?0:currenty;
       }
    }
}

