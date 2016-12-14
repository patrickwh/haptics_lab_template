#ifndef WATERGAME_H
#define WATERGAME_H

#include "Assignment.h"
#include "chai3d.h"
#include "gamemap.h"

class WaterGame : public Assignment
{
private:
    // A 3D cursor for the haptic device
    cShapeSphere* m_cursor;

    // Material properties used to render the color of the cursors
    cMaterialPtr m_matCursorButtonON;
    cMaterialPtr m_matCursorButtonOFF;
    void removeAllCurrentObject();
    void addAllCurrentObject();
    void updateBonuspoints();
    void initialBonuspoints();

public:

    virtual std::string getName() const { return " Water Game"; }


    virtual void initialize(cWorld* world, cCamera* camera);
    virtual void updateGraphics();
    virtual void updateHaptics(cGenericHapticDevice* hapticDevice, double timeStep, double totalTime);

    // my methods and attributes

    GameMap* map;
    WaterGame();

    double totallen = 0.0765*2;
    double xstep = 0;
    int halfmax = 0;

    //**************************************************************************************
    cMesh* object3;

    // a haptic device handler
    cHapticDeviceHandler* handler;

    // a pointer to the current haptic device
    cGenericHapticDevicePtr hapticDevice;

    // a virtual tool representing the haptic device in the scene
    cToolCursor* tool;
    cShapeSphere* boat;
    cMaterialPtr boatc;
    cMaterialPtr boatc2;
    cWorld* world;

    QList<cShapeSphere*> curObjList;
    QList<cShapeSphere*> bonusObjList;
    //**************************************************************************************

};

WaterGame::WaterGame(){
    map = new GameMap();
    xstep = totallen/map->xmax;
    halfmax = map->xmax/2.0;
}

void WaterGame::initialize(cWorld* world, cCamera* camera)
{
    this->world = world;
    //Change the background
    world->setBackgroundColor(0.2f, 0, 0.31f);

    boatc = cMaterialPtr(new cMaterial());
    boatc->m_ambient.set(0.5, 0.2, 0.0);
    boatc->m_diffuse.set(1.0, 0.5, 0.0);
    boatc->m_specular.set(1.0, 1.0, 1.0);
    boatc2 = cMaterialPtr(new cMaterial());
    boatc2->m_ambient.set(0.5, 0.0, 0.5);
    boatc2->m_diffuse.set(1.0, 0.5, 0.0);
    boatc2->m_specular.set(1.0, 1.0, 1.0);

    // *************************** ADD OBJECTS INTO THE WORLD******************************
    // iceberg object
    QListIterator <iceBerg*> iitr(map->iceberg);
    while(iitr.hasNext()){
        iceBerg* ice = iitr.next();
        double icesr = xstep*ice->radius;
        double x = xstep*(ice->xpos-halfmax);
        double y = xstep*(ice->ypos-halfmax);
        cShapeSphere* icebergsp = new cShapeSphere(icesr);
        icebergsp->setLocalPos(0.0,y,x);
        world->addChild(icebergsp);
    } 
    // bonus object
    initialBonuspoints();

    // exit object
    QListIterator <Exit*> eitr(map->exit);
    while(eitr.hasNext()){
        Exit* exit = eitr.next();
        double er = xstep*exit->radius;
        double x = xstep*(exit->xpos-halfmax);
        double y = xstep*(exit->ypos-halfmax);
        cShapeSphere* exitsp = new cShapeSphere(er);
        exitsp->setLocalPos(0.0,y,x);
        world->addChild(exitsp);
        if(exit->TYPE_FAKE_TRANSFER_TO_START==-1){
                  exitsp->m_material->setYellowGold();
              }
    }
    // current object
    QListIterator <Current*> citr(map->current);
    while(citr.hasNext()){
        Current* current = citr.next();
        double currentr = current->entranceRadius*xstep;
        cShapeSphere* currentsp1 = new cShapeSphere(currentr);
        double x1 = xstep*(current->x1-halfmax);
        double y1 = xstep*(current->y1-halfmax);
        cMaterialPtr entrancec = cMaterialPtr(new cMaterial());
        entrancec->m_ambient.set(0.2, 0.7, 0.2);
        entrancec->m_diffuse.set(1.0, 0.5, 0.0);
        entrancec->m_specular.set(1.0, 1.0, 1.0);
        currentsp1->m_material = entrancec;
        currentsp1->setLocalPos(0.0,y1,x1);
        //world->addChild(currentsp1);
        cShapeSphere* currentsp2 = new cShapeSphere(currentr);
        double x2 = xstep*(current->x2-halfmax);
        double y2 = xstep*(current->y2-halfmax);
        currentsp2->m_material = entrancec;
        currentsp2->setLocalPos(0.0,y2,x2);
        //world->addChild(currentsp2);
        curObjList<<currentsp1;
        curObjList<<currentsp2;
    }
    // rock object
    QListIterator <Rock*> ritr(map->rock);
    while(ritr.hasNext()){
        Rock* r = ritr.next();
        double xsz = 0.0;
        double ysz = xstep*r->width;
        double zsz = xstep*r->height;
        cShapeBox* rockbx = new cShapeBox(xsz,ysz,zsz);
        double x = xstep*(r->xpos-halfmax+r->height/2.0);
        double y = xstep*(r->ypos-halfmax+r->width/2.0);
        rockbx->setLocalPos(0.0,y,x);
        world->addChild(rockbx);
    }
    // whirpool object
    QListIterator <whirPool*> witr(map->whirpool);
    while(witr.hasNext()){
        whirPool* w = witr.next();
        double whirpoolr = xstep*w->radius;
        double x = xstep*(w->xpos-halfmax);
        double y = xstep*(w->ypos-halfmax);
        cShapeSphere* whirpoolsp = new cShapeSphere(whirpoolr);

        whirpoolsp->m_material->m_ambient.set(0.1, 0.1, 0.6, 0.5);
        whirpoolsp->m_material->m_diffuse.set(0.3, 0.3, 0.9, 0.5);
        whirpoolsp->m_material->m_specular.set(1.0, 1.0, 1.0, 0.5);
        whirpoolsp->m_material->setWhite();
        whirpoolsp->setTransparencyLevel(0.1);
        whirpoolsp->setLocalPos(0.0,y,x);
       //        whirpoolsp->m_material = whirpoolc;
        world->addChild(whirpoolsp);
    }
    // boat object
    boat = new cShapeSphere(0.002);
    double x = xstep*(map->currentx-halfmax);
    double y = xstep*(map->currenty-halfmax);
    boat->setLocalPos(0.0,y,x);

//    boat->m_material->setColorf(1,0,0,10);
    boat->m_material->setGreenLime();
    boat->setTransparencyLevel(1);

//    boat->m_material = boatc;
    world->addChild(boat);

}

void WaterGame::updateGraphics()
{

}

void WaterGame::initialBonuspoints(){
    QListIterator<cShapeSphere*> boitr(bonusObjList);
    while(boitr.hasNext()){
        cShapeSphere* bpsp = boitr.next();
        world->removeChild(bpsp);
        delete bpsp;
    }
    bonusObjList.clear();
    QListIterator <BonusPoint*> bitr(map->bonus);
    while(bitr.hasNext()){
        BonusPoint* bp = bitr.next();
        double br = 0.001;
        double x = xstep*(bp->xpos-halfmax);
        double y = xstep*(bp->ypos-halfmax);
        cShapeSphere* bpsp = new cShapeSphere(br);
        bpsp->setLocalPos(0.0,y,x);
        world->addChild(bpsp);
        bonusObjList<<bpsp;
    }
}

void WaterGame::removeAllCurrentObject(){
    QListIterator<cShapeSphere*> coitr(curObjList);
    while(coitr.hasNext()){
        cShapeSphere* co = coitr.next();
        world->removeChild(co);
    }
}

void WaterGame::addAllCurrentObject(){
    QListIterator<cShapeSphere*> coitr(curObjList);
    while(coitr.hasNext()){
        cShapeSphere* co = coitr.next();
        world->addChild(co);
    }
}

void WaterGame::updateBonuspoints(){
    int updateFrequency = 15;
    QListIterator<BonusPoint*> bitr(map->bonus);
    QList<int> deleteList;
    int id = 0;
    while(bitr.hasNext()){
        BonusPoint* bp = bitr.next();
        if(bp->valid == false){
            cShapeSphere* bpsp = bonusObjList[id];
            world->removeChild(bpsp);
            bonusObjList.removeOne(bpsp);
            deleteList<<id;
            delete bpsp;
        }else{
            int choise = rand()%(1000*updateFrequency);
            if(choise == 0){
                double newx = rand()%int(map->xmax);
                double newy = rand()%int(map->xmax);
                bp->xpos = newx;
                bp->ypos = newy;
                double x = xstep*(bp->xpos-halfmax);
                double y = xstep*(bp->ypos-halfmax);
                bonusObjList[id]->setLocalPos(0.0,y,x);
            }
        }
        id++;
    }
    QListIterator<int> itr(deleteList);
    while(itr.hasNext()){
        map->bonus.removeAt(itr.next());
    }
}


void WaterGame::updateHaptics(cGenericHapticDevice* hapticDevice, double timeStep, double totalTime)
{
    cVector3d newPosition;
    hapticDevice->getPosition(newPosition);

    double x = -newPosition(0);
    double y = newPosition(1);

    if(!map->blockedByCurrent){
        map->updateXpos(x);
        map->updateYpos(y);
    }

    if(map->gameOver){
        delete map;
        map = new GameMap();
        initialBonuspoints();
    }

    map->setTotalTime(totalTime);

    updateBonuspoints();

    bool bs;
    hapticDevice->getUserSwitch(0, bs);
    bool bs2;
    hapticDevice->getUserSwitch(1, bs2);

    if(bs2)
    {
        boat->m_material = boatc2;
        addAllCurrentObject();
    }else{
        boat->m_material = boatc2;
        removeAllCurrentObject();
    }
    double bloodLevl = map->bloodMax/5.0;
    double bloodGreen = map->bloodMax-bloodLevl;
    double bloodBlue = map->bloodMax-2*bloodLevl;
    double bloodYellow = map->bloodMax-3*bloodLevl;
    double bloodOrange = map->bloodMax-4*bloodLevl;
    double bloodRed = map->bloodMax-5*bloodLevl;
    if (map->blood>=bloodGreen){
        boat->m_material->setColorf(0,1,0);
    }else if (map->blood<bloodGreen&&map->blood>=bloodBlue){
        boat->m_material->setColorf(0,0,1);
    }else if (map->blood<bloodBlue&&map->blood>=bloodYellow){
        boat->m_material->setColorf(1,1,0);
    }else if (map->blood<bloodYellow&&map->blood>=bloodOrange){
        boat->m_material->setColorf(1,0.5,0);
    }else{
        boat->m_material->setColorf(1,0,0);
    }

    cVector3d f = map->getForceFeedback(newPosition,bs);
    hapticDevice->setForce(f);

    double xx = xstep*(map->currentx-halfmax);
    double yy = xstep*(map->currenty-halfmax);
    boat->setLocalPos(0.0,yy,xx);
}
#endif
