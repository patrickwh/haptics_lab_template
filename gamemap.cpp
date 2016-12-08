#include "gamemap.h"



cVector3d GameMap::getForceFeedback(int xpos, int ypos){
    cVector3d fwave = wave->getForceFeedback(xpos,ypos,totalTime);
    cVector3d frock = rock->getForceFeedback(xpos,ypos,totalTime);
    cVector3d fice = iceberg->iceForce(xpos,ypos);

    //std::cout<<"f: "<<fice(0)<<" "<<fice(1)<<";";

    cVector3d f(0,0,0);

    if(rock->triggered){
        f.add(frock);
    }else{
        f.add(fwave);
    }
    f.add(fice);

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
    iceberg = new iceBerg(20,50,5);
}

bool GameMap::willBeBlocked(int x,int y){
    return iceberg->willBeBlocked(x,y);
}

void GameMap::setXspeed(double pos){
    if(pos<=xthreshold){
        xspeed = 0;
        xincth = 0;
    }else{
        xspeed = (pos-xthreshold)/xstep;
        xincth = incbase/xspeed;
    }
}

void GameMap::setYspeed(double pos){
    if(pos<=ythreshold){
        yspeed = 0;
        yincth = 0;
    }else{
        yspeed = (pos-ythreshold)/ystep;
        yincth = incbase/yspeed;
    }
}

void GameMap::updateXpos(double x){
    double xabs = abs(x);
    if(xabs>xthreshold){
        setXspeed(xabs);
        if(x>0){
            xaccm++;
            if(xaccm>xincth){
                currentx++;
                if(willBeBlocked(currentx,currenty)) currentx--;
                currentx = currentx>=xmax?xmax:currentx;
                xaccm = 0;
            }
        }
        else{
            xaccm--;
            if(xaccm<0){
                currentx--;
                if(willBeBlocked(currentx,currenty)) currentx++;
                currentx = currentx<=0?0:currentx;
                xaccm = xincth;
            }
        }
    }
}

void GameMap::updateYpos(double y){
    double yabs = abs(y);
    if(yabs > ythreshold)
    {
        setYspeed(yabs);
        if(y>0){
            yaccm++;
            if(yaccm>yincth){
                currenty++;
                if(willBeBlocked(currentx,currenty)) currenty--;
                currenty = currenty>=ymax?ymax:currenty;
                yaccm = 0;
            }
        }
        else{
            yaccm--;
            if(yaccm<0){
                currenty--;
                if(willBeBlocked(currentx,currenty)) currenty++;
                currenty = currenty<=0?0:currenty;
                yaccm = yincth;
            }
        }
    }
}

