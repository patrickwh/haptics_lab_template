#ifndef HAPTICSPHERE_H
#define HAPTICSPHERE_H

#include "Assignment.h"

#include "chai3d.h"

class HapticSphere : public Assignment
{
private:
    // A 3D cursor for the haptic device
    cShapeSphere* m_cursor;

    // Material properties used to render the color of the cursors
    cMaterialPtr m_matCursorButtonON;
    cMaterialPtr m_matCursorButtonOFF;

public:
    virtual std::string getName() const { return "6: Haptic Sphere"; }

	virtual void initialize(cWorld* world, cCamera* camera);
	virtual void updateGraphics();
	virtual void updateHaptics(cGenericHapticDevice* hapticDevice, double timeStep, double totalTime);
};

void HapticSphere::initialize(cWorld* world, cCamera* camera)
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

void HapticSphere::updateGraphics()
{

}

void HapticSphere::updateHaptics(cGenericHapticDevice* hapticDevice, double timeStep, double totalTime)
{
	//Read the current position of the haptic device
	cVector3d newPosition;
    hapticDevice->getPosition(newPosition);

    double x = newPosition.x();
    double y = newPosition.y();
    double z = newPosition.z();
    double dis = sqrt(x*x+y*y+z*z);

    std::cout << "1"<<dis << std::endl;

    // double dis = newPosition.length();
    double r = 0.04;

    cVector3d pos(x,y,z);
    cVector3d pos2(x,y,z);
    cVector3d force(0, 0, 0);

    if(dis < r){
        pos.normalize();
        pos.mul(r);
        m_cursor->setLocalPos(pos);
        std::cout << "2"<<dis << std::endl;
        pos2.normalize();
        pos2.mul(2000*(r-dis));
        hapticDevice->setForce(pos2);
    }else{
        m_cursor->setLocalPos(pos);
        hapticDevice->setForce(force);
    }


}
#endif

