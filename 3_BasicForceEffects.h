#ifndef BASICFORCEEFFECTS_H
#define BASICFORCEEFFECTS_H

#include "Assignment.h"

#include "chai3d.h"

class BasicForceEffects : public Assignment
{
private:
    // A 3D cursor for the haptic device
    cShapeSphere* m_cursor;

    // Material properties used to render the color of the cursors
    cMaterialPtr m_matCursorButtonON;
    cMaterialPtr m_matCursorButtonOFF;

public:
    virtual std::string getName() const { return "3: Basic Force Effects"; }

	virtual void initialize(cWorld* world, cCamera* camera);
	virtual void updateGraphics();
	virtual void updateHaptics(cGenericHapticDevice* hapticDevice, double timeStep, double totalTime);
};

void BasicForceEffects::initialize(cWorld* world, cCamera* camera)
{
	//Change the background
	world->setBackgroundColor(0.2f, 0, 0);

	// Create a cursor with its radius set
	m_cursor = new cShapeSphere(0.01);
	// Add cursor to the world
	world->addChild(m_cursor);

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

void BasicForceEffects::updateGraphics()
{

}

void BasicForceEffects::updateHaptics(cGenericHapticDevice* hapticDevice, double timeStep, double totalTime)
{
	//Read the current position of the haptic device
	cVector3d newPosition;
	hapticDevice->getPosition(newPosition);

	// Update position and orientation of cursor
    m_cursor->setLocalPos(newPosition);

	// Read user button status
	bool buttonStatus;
	hapticDevice->getUserSwitch(0, buttonStatus);

	// Adjust the color of the cursor according to the status of
	// the user switch (ON = TRUE / OFF = FALSE)
	m_cursor->m_material = buttonStatus ? m_matCursorButtonON : m_matCursorButtonOFF;

	cVector3d force(0, 0, 0);

	//TODO: Add an interesting force here



    double t = totalTime;
    double A = 10;
    double f = 100;
    force = cVector3d(0,0,A*cSinRad(f*t));


	//Set a force to the haptic device
	hapticDevice->setForce(force);
}

#endif

