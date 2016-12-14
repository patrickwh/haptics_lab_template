#include "gamemap.h"



cVector3d GameMap::getForceFeedback(cVector3d newPosition,bool buttonClicked){

    int xpos = currentx;
    int ypos = currenty;

    cVector3d f(0,0,0);

    cVector3d fcentering = -300.0f * newPosition;
    fcentering(2) = 0;

    // bonus points
    QListIterator<BonusPoint*> bitr(bonus);
    while(bitr.hasNext()){
        BonusPoint* bp = bitr.next();
        bp->updateState(xpos,ypos);
        if(bp->triggered && bp->valid){

            blood += bp->ammount;
            if(blood>bloodMax){
                blood =bloodMax;
            }
            bp->valid = false;
            bp->triggered = false;
        }
    }

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

    // exits
    QListIterator<Exit*> eitr(exit);
    while(eitr.hasNext()){
        Exit* e = eitr.next();
        e->updateState(xpos,ypos);
        if(e->state == Exit::STATE_BACK_TO_START){
            currentx = xstart;
            currenty = ystart;
            e->state = Exit::STATE_GAME_UNGOING;
        }
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
        }else f.add(fcentering);
    }

    cVector3d fwave = wave->getForceFeedback(xpos,ypos,totalTime);

    // rocks
    bool isRocktriggered = false;
    QListIterator<Rock*> ritr(rock);
    while(ritr.hasNext()){
        Rock* r = ritr.next();
        if(r->triggered){
            isRocktriggered = true;
            blood -= r->damage;
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
            blood -= w-> damage;
        }
        cVector3d fpool = w->poolForce(xpos,ypos,totalTime);
        f.add(fpool);
    }

    // iecbergs
    QListIterator <iceBerg*> iitr(iceberg);
    while(iitr.hasNext()){
        iceBerg* ice = iitr.next();
        if(ice->triggered){
            blood -= ice -> damage;
        }
        cVector3d fice = ice->iceForce(xpos,ypos,totalTime);
        f.add(fice);
    }

    if(isRocktriggered || iswhirpooltriggered){
        speedScale = 0.2;
    }else{
        if(inCurrentEntrance){
            speedScale = 1.5;
        }else{
            f.add(fwave);
            speedScale = 1.0;
        }
    }

    std::cout<<"blood: "<<blood<<std::endl;

    return f;
}

void GameMap::setTotalTime(double t){
    totalTime = t;
}

GameMap::GameMap(){
    int ainit = 10;
    double finit = 1;
    wave = new Wave(ainit,finit);
    rock << new Rock(72.5,-5,125,5);
    rock << new Rock(25.5,-5,125,5);

    rock << new Rock(45,53.5,1.5,1); //1
    rock << new Rock(45.5,54,1,4.5); //2
    rock << new Rock(53.5,54,1,1.5); //3
    rock << new Rock(54,49.5,4.5,1); //4
    rock << new Rock(54,45,1.5,1); //5
    rock << new Rock(49.5,45,1,4.5); //6
    rock << new Rock(45,45,1,1.5); //7
    rock << new Rock(45,46,4.5,1); //8

    rock << new Rock(35,66,5,35); //9

    iceberg << new iceBerg(75,25,5);
    iceberg << new iceBerg(75,50,5);
    iceberg << new iceBerg(75,75,5);
    iceberg << new iceBerg(27.5,25,5);
    iceberg << new iceBerg(27.5,50,5);
    iceberg << new iceBerg(27.5,75,5);
    // up part
    whirpool<< new whirPool(88,10,6);
    whirpool<< new whirPool(88,35,6);
    whirpool<< new whirPool(88,64,6);
    whirpool<< new whirPool(88,94,6);
    // down part
    whirpool<< new whirPool(12,10,6);
    whirpool<< new whirPool(12,35,6);
    whirpool<< new whirPool(12,64,6);
    whirpool<< new whirPool(12,94,6);
    // Middle part
    whirpool<< new whirPool(50,84,8);


    current << new Current(62.5,25,80,80,5);

    exit<< new Exit(50.0,0.0,Exit::TYPE_FAKE_TRANSFER_TO_START);
    exit<< new Exit(50.0,100.0,Exit::TYPE_FAKE_TRANSFER_TO_START);
    exit<< new Exit(0.0,50.0,Exit::TYPE_REAL);
    exit<< new Exit(100.0,50.0,Exit::TYPE_REAL);

    generateRandomBouns(10);
}

bool GameMap::willBeBlocked(double x,double y){
    if(blockedByCurrent) return false;
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

void GameMap::generateRandomBouns(int num){
    srand(time(NULL));
    for(int i=0;i<num;i++){
        double x = double (rand()%int(xmax));
        double y = double (rand()%int(xmax));
        double a = rand()%50+100;
        BonusPoint* bp = new BonusPoint(x,y,a);
        bonus<<bp;
    }
}
