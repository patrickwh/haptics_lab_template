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

    virtual std::string getName() const { return "7: Water Game"; }


    virtual void initialize(cWorld* world, cCamera* camera);
    virtual void updateGraphics();
    virtual void updateHaptics(cGenericHapticDevice* hapticDevice, double timeStep, double totalTime);

    // my methods and

    GameMap map;
    WaterGame();

};

WaterGame::WaterGame(){
    map = GameMap();
}

void WaterGame::initialize(cWorld* world, cCamera* camera)
{
    //Change the background
    world->setBackgroundColor(0.2f, 0, 0.31f);

    // Create a cursor with its radius set
    m_cursor = new cShapeSphere(0.01);
    // Add cursor to the world
    world->addChild(m_cursor);

    double radius = 0.04;
    cShapeSphere* ball = new cShapeSphere(radius);
    world->addChild(ball);

    // Here we define the material properties of the cursor when the
    // user button of the device end-effector is engaged (ON) or released (OFF)

    // A light orange material color
    m_matCursorButtonOFF = cMaterialPtr(new cMaterial());
    m_matCursorButtonOFF->m_ambient.set(0.5, 0.2, 0.0);
    m_matCursorButtonOFF->m_diffuse.set(1.0, 0.5, 0.0);
    m_matCursorButtonOFF->m_specular.set(1.0, 1.0, 1.0);

    // A blue material color
    // A light orange material color
    m_matCursorButtonON = cMaterialPtr(new cMaterial());
    m_matCursorButtonON->m_ambient.set(0.1, 0.1, 0.4);
    m_matCursorButtonON->m_diffuse.set(0.3, 0.3, 0.8);
    m_matCursorButtonON->m_specular.set(1.0, 1.0, 1.0);

    // Apply the 'off' material to the cursor
    m_cursor->m_material = m_matCursorButtonOFF;
}

void WaterGame::updateGraphics()
{

}



void WaterGame::updateHaptics(cGenericHapticDevice* hapticDevice, double timeStep, double totalTime)
{
    cVector3d newPosition;
    hapticDevice->getPosition(newPosition);
    cVector3d centerForce = -300.0f * newPosition;
    // no center force on z axis
    centerForce(2) = 0;

    double x = -newPosition(0);
    double y = newPosition(1);

    map.updateXpos(x);
    map.updateYpos(y);

    std::cout<<"pos: "<<map.currentx<<" "<<map.currenty<<" ; ";

    map.setTotalTime(totalTime);
    cVector3d f = map.getForceFeedback(map.currentx,map.currenty);
    f.add(centerForce);
    hapticDevice->setForce(f);
}
#endif
