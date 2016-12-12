#include "gamemap.h"



cVector3d GameMap::getForceFeedback(cVector3d newPosition,bool buttonClicked){

    int xpos = currentx;
    int ypos = currenty;

    cVector3d f(0,0,0);

    if(blockedByCurrent){
        if(xpos == xmax || ypos == ymax || xpos == 0 || ypos == 0)
        {
            blockedByCurrent = false;
            triggeredCurrent->transferFinished = true;
            currentx = triggeredCurrent->transferStartx;
            currenty = triggeredCurrent->transferStarty;
        }
        triggeredCurrent->updatePosition(xpos,ypos);
        if(!triggeredCurrent->transferFinished){
            cVector3d speed = triggeredCurrent->getSpeed();
            xspeed = cAbs(speed(0));
            xinc = xspeed/base;
            yspeed = cAbs(speed(1));
            yinc = yspeed/base;
            std::cout<<" sp "<<speed(0)<<" "<<speed(1)<<std::endl;
            updateCurrentx(speed(0));
            updateCurrenty(speed(1));
        }else{
            blockedByCurrent = false;
            triggeredCurrent = nullptr;
        }
        return f;
    }

    cVector3d fwave = wave->getForceFeedback(xpos,ypos,totalTime);

    cVector3d fcentering = -300.0f * newPosition;
    fcentering(2) = 0;

    // rocks
    bool isRocktriggered = false;
    QListIterator<Rock*> ritr(rock);
    while(ritr.hasNext()){
        Rock* r = ritr.next();
        if(r->triggered){
            isRocktriggered = true;
        }
        cVector3d frock = r->getForceFeedback(xpos,ypos,totalTime,xpositionUpdated,ypositionUpdated);
        f.add(frock);
    }

    // whirpools
    bool iswhirpooltriggered = false;
    QListIterator<whirPool*> witr(whirpool);
    while(witr.hasNext()){
        whirPool* w = witr.next();
        if(w->triggered){
            iswhirpooltriggered = true;
        }
        cVector3d fpool = w->poolForce(xpos,ypos);
        f.add(fpool);
    }

    // iecbergs
    QListIterator <iceBerg*> iitr(iceberg);
    while(iitr.hasNext()){
        iceBerg* ice = iitr.next();
        cVector3d fice = ice->iceForce(xpos,ypos);
        f.add(fice);
    }

    // currents
    bool inCurrentEntrance = false;
    QListIterator <Current*> citr(current);
    while(citr.hasNext()){
        Current* cur = citr.next();
        cVector3d fcur = cur->getForceFeedback(xpos,ypos);
        f.add(fcur);
        if(cur->inArea1 || cur->inArea2){
            inCurrentEntrance = true;
            if(buttonClicked){
                cur->transferTriggered(xpos,ypos);
                blockedByCurrent = true;
                triggeredCurrent = cur;
            }
        }
    }

    if(isRocktriggered || iswhirpooltriggered){
        speedScale = 0.2;
    }else{
        if(inCurrentEntrance){
            speedScale = 1.5;
        }else{
            f.add(fwave);
            f.add(fcentering);
            speedScale = 1.0;
        }
    }

    return f;
}

void GameMap::setTotalTime(double t){
    totalTime = t;
}

GameMap::GameMap(){
    int ainit = 10;
    double finit = 1;
    wave = new Wave(ainit,finit);
    rock << new Rock(5,25,50,5);
    iceberg << new iceBerg(25,50,10);
    whirpool << new whirPool(50,50,5);
    whirpool << new whirPool(50,75,5);
    whirpool << new whirPool(75,50,5);
    current << new Current(25,25,80,80,5);
}

bool GameMap::willBeBlocked(double x,double y){
    bool blocked = false;
    QListIterator<iceBerg*> itr(iceberg);
    while(itr.hasNext()){
        iceBerg* i = itr.next();
        if(i->willBeBlocked(x,y))
        {
            blocked = true;
            break;
        }
    }
    return blocked;
}

void GameMap::setXspeed(double pos){
    if(pos<=xthreshold){
        xspeed = 0;
        xinc = 0;
    }else{
        xspeed = speedScale*(pos-xthreshold)/xstep;
        xinc = xspeed/base;
    }
}

void GameMap::setYspeed(double pos){
    if(pos<=ythreshold){
        yspeed = 0;
        yinc = 0;
    }else{
        yspeed = speedScale*(pos-ythreshold)/ystep;
        yinc = yspeed/base;
    }
}

void GameMap::updateCurrentx(double x){
    if(x>0){
        currentx += xinc;
        if(willBeBlocked(currentx,currenty)) currentx-=xinc;
        currentx = currentx>=xmax?xmax:currentx;
    }
    if(x<0){
        currentx -= xinc;
        if(willBeBlocked(currentx,currenty)) currentx+=xinc;
        currentx = currentx<=0?0:currentx;
    }
}

void GameMap::updateXpos(double x){
    double xabs = cAbs(x);
    if(xabs>xthreshold){
        setXspeed(xabs);
        xpositionUpdated = true;
        updateCurrentx(x);
    }else{
       xpositionUpdated = false;
    }
}

void GameMap::updateCurrenty(double y){
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

void GameMap::updateYpos(double y){
    double yabs = cAbs(y);
    if(yabs>ythreshold){
        setYspeed(yabs);
        ypositionUpdated = true;
        updateCurrenty(y);
    }
    else ypositionUpdated = false;
}

