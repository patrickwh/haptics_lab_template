#ifndef WATERGAME_H
#define WATERGAME_H

//#include <QList>
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
    void setXspeed(double pos);
    void setYspeed(double pos);

public:

    virtual std::string getName() const { return " Water Game"; }


    virtual void initialize(cWorld* world, cCamera* camera);
    virtual void updateGraphics();
    virtual void updateHaptics(cGenericHapticDevice* hapticDevice, double timeStep, double totalTime);

    // my methods and attributes

    GameMap map;
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
    //**************************************************************************************

};

WaterGame::WaterGame(){
    map = GameMap();
    xstep = totallen/map.xmax;
    halfmax = map.xmax/2;
}

void WaterGame::initialize(cWorld* world, cCamera* camera)
{
    //Change the background
    world->setBackgroundColor(0.2f, 0, 0.31f);


    // *************************** ADD OBJECTS INTO THE WORLD******************************
    // iceberg object
    QListIterator <iceBerg*> iitr(map.iceberg);
    while(iitr.hasNext()){
        iceBerg* ice = iitr.next();
        double icesr = xstep*ice->radius;
        double x = xstep*(ice->xpos-halfmax);
        double y = xstep*(ice->ypos-halfmax);
        cShapeSphere* icebergsp = new cShapeSphere(icesr);
        icebergsp->setLocalPos(0.0,y,x);
        world->addChild(icebergsp);
    }
    // current object
    QListIterator <Current*> citr(map.current);
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
        world->addChild(currentsp1);
        cShapeSphere* currentsp2 = new cShapeSphere(currentr);
        double x2 = xstep*(current->x2-halfmax);
        double y2 = xstep*(current->y2-halfmax);
        currentsp2->m_material = entrancec;
        currentsp2->setLocalPos(0.0,y2,x2);
        world->addChild(currentsp2);
    }
    // rock object
    QListIterator <Rock*> ritr(map.rock);
    while(ritr.hasNext()){
        Rock* r = ritr.next();
        double xsz = 0.0001;
        double ysz = xstep*r->width;
        double zsz = xstep*r->height;
        cShapeBox* rockbx = new cShapeBox(xsz,ysz,zsz);
        double x = xstep*(r->xpos-halfmax+r->height/2);
        double y = xstep*(r->ypos-halfmax+r->width/2);
        rockbx->setLocalPos(0.0,y,x);
        world->addChild(rockbx);
    }
    // whirpool object
    QListIterator <whirPool*> witr(map.whirpool);
    while(witr.hasNext()){
        whirPool* w = witr.next();
        double whirpoolr = xstep*w->radius;
        double x = xstep*(w->xpos-halfmax);
        double y = xstep*(w->ypos-halfmax);
        cMaterialPtr whirpoolc = cMaterialPtr(new cMaterial());
        whirpoolc->m_ambient.set(0.5, 0.2, 0.0);
        whirpoolc->m_diffuse.set(1.0, 0.5, 0.0);
        whirpoolc->m_specular.set(1.0, 1.0, 1.0);
        cShapeSphere* whirpoolsp = new cShapeSphere(whirpoolr);
        whirpoolsp->setLocalPos(0.0,y,x);
        whirpoolsp->m_material = whirpoolc;
        world->addChild(whirpoolsp);
    }
    // boat object
    boat = new cShapeSphere(0.002);
    double x = xstep*(map.currentx-halfmax);
    double y = xstep*(map.currenty-halfmax);
    boat->setLocalPos(0.0,y,x);
    cMaterialPtr boatc = cMaterialPtr(new cMaterial());
    boatc->m_ambient.set(0.5, 0.2, 0.0);
    boatc->m_diffuse.set(1.0, 0.5, 0.0);
    boatc->m_specular.set(1.0, 1.0, 1.0);
    boat->m_material = boatc;
    world->addChild(boat);
//**************************************************************************************
//    //--------------------------------------------------------------------------
//    // HAPTIC DEVICES / TOOLS
//    //--------------------------------------------------------------------------

//    // create a haptic device handler
//    handler = new cHapticDeviceHandler();

//    // get access to the first available haptic device
//    handler->getDevice(hapticDevice, 0);

//    // retrieve information about the current haptic device
//    cHapticDeviceInfo hapticDeviceInfo = hapticDevice->getSpecifications();

//    // create a 3D tool and add it to the world
//    tool = new cToolCursor(world);
//    camera->addChild(tool);

//    // position tool in respect to camera
//    tool->setLocalPos(-1.0, 0.0, 0.0);

//    // connect the haptic device to the tool
//    tool->setHapticDevice(hapticDevice);

//    // set radius of tool
//    double toolRadius = 0.01;

//    // define a radius for the tool
//    tool->setRadius(toolRadius);

//    // map the physical workspace of the haptic device to a larger virtual workspace.
//    tool->setWorkspaceRadius(1.0);

//    // start the haptic tool
//    tool->start();

//    double workspaceScaleFactor = tool->getWorkspaceScaleFactor();

//    // properties

//    double maxStiffness = hapticDeviceInfo.m_maxLinearStiffness / workspaceScaleFactor;

//    // create a mesh
//       object3 = new cMesh();

//       // create plane
//       cCreatePlane(object3, 0.3, 0.3);

//       // create collision detector
//       object3->createAABBCollisionDetector(toolRadius);

//       // add object to world
//       world->addChild(object3);

//       // set the position of the object
//       object3->setLocalPos(-0.2, 0.2, 0.0);

//       // set graphic properties
//       object3->m_texture = cTexture2d::create();
//       bool fileload = object3->m_texture->loadFromFile("images.jpg");
//       if (!fileload)
//       {
//           #if defined(_MSVC)
//           fileload = object3->m_texture->loadFromFile("../../../bin/resources/images/blackstone.jpg");
//           #endif
//       }
//       if (!fileload)
//       {
//           std::cout << "Error - Texture image failed to load correctly." << std::endl;
//           // close();
//       }

//       // enable texture mapping
//       object3->setUseTexture(true);
//       object3->m_material->setWhite();

//       // create normal map from texture data
//       cNormalMapPtr normalMap3 = cNormalMap::create();
//       normalMap3->createMap(object3->m_texture);
//       object3->m_normalMap = normalMap3;
//       normalMap3->setTextureUnit(GL_TEXTURE0_ARB);

//       // set haptic properties
//       object3->m_material->setStiffness(0.7 * maxStiffness);
//       object3->m_material->setStaticFriction(0.4);
//       object3->m_material->setDynamicFriction(0.3);
//       object3->m_material->setTextureLevel(0.5);
//       object3->m_material->setHapticTriangleSides(true, false);
//**************************************************************************************

}

void WaterGame::updateGraphics()
{

}



void WaterGame::updateHaptics(cGenericHapticDevice* hapticDevice, double timeStep, double totalTime)
{
    cVector3d newPosition;
    hapticDevice->getPosition(newPosition);

    double x = -newPosition(0);
    double y = newPosition(1);

    map.updateXpos(x);
    map.updateYpos(y);

    map.setTotalTime(totalTime);

    bool buttonStatus;
    hapticDevice->getUserSwitch(0, buttonStatus);

    cVector3d f = map.getForceFeedback(newPosition,buttonStatus);
    hapticDevice->setForce(f);

    double xx = xstep*(map.currentx-halfmax);
    double yy = xstep*(map.currenty-halfmax);
    boat->setLocalPos(0.0,yy,xx);
}
#endif
