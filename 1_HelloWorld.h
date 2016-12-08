#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include "Assignment.h"

#include "chai3d.h"

class HelloWorld : public Assignment
{
private:
    // A 3D cursor for the haptic device
    cShapeSphere* m_cursor;

    // A line to display velocity of the haptic interface
    cShapeLine* m_velocityVector;

    // Material properties used to render the color of the cursors
    cMaterialPtr m_matCursorButtonON;
    cMaterialPtr m_matCursorButtonOFF;

	// A label used to demonstrate debug output
    cLabel* m_debugLabel;

public:
    virtual std::string getName() const { return "1: Hello World"; }

	virtual void initialize(cWorld* world, cCamera* camera);

	virtual void updateGraphics();
	virtual void updateHaptics(cGenericHapticDevice* hapticDevice, double timeStep, double totalTime);
};

void HelloWorld::initialize(cWorld* world, cCamera* camera)
{
	//Change the background
    world->setBackgroundColor(0.0f, 1.0f, 0.0f);

	// Create a cursor with its radius set
	m_cursor = new cShapeSphere(0.01);
	// Add cursor to the world
	world->addChild(m_cursor);

	// Create a small line to illustrate velocity
    m_velocityVector = new cShapeLine(cVector3d(0, 0, 0), cVector3d(0, 0, 0));
	// Add line to the world
    world->addChild(m_velocityVector);

	// Here we define the material properties of the cursor when the
	// user button of the device end-effector is engaged (ON) or released (OFF)

	// A light orange material color
    m_matCursorButtonOFF = cMaterialPtr(new cMaterial());
    m_matCursorButtonOFF->m_ambient.set(0.5, 0.2, 0.0);
    m_matCursorButtonOFF->m_diffuse.set(1.0, 0.5, 0.0);
    m_matCursorButtonOFF->m_specular.set(1.0, 1.0, 1.0);

	// A blue material color
    m_matCursorButtonON = cMaterialPtr(new cMaterial());
    m_matCursorButtonON->m_ambient.set(0.1, 0.1, 0.4);
    m_matCursorButtonON->m_diffuse.set(0.3, 0.3, 0.8);
    m_matCursorButtonON->m_specular.set(1.0, 1.0, 1.0);

	// Apply the 'off' material to the cursor
    m_cursor->m_material = m_matCursorButtonOFF;

    // Create a font
    cFont *font = NEW_CFONTCALIBRI20();

	// Create a label used to show how debug output can be handled
    m_debugLabel = new cLabel(font);

	// Labels need to be added to the camera instead of the world
    camera->m_frontLayer->addChild(m_debugLabel);
}

void HelloWorld::updateGraphics()
{
	std::stringstream ss;

    ss << "You can add debug output like this: " << m_cursor->getLocalPos().length() * 1000.0
		<< " mm (Distance from center)";

    m_debugLabel->setString(ss.str());

	// Position the label
    m_debugLabel->setLocalPos(30, 150, 0);
}

void HelloWorld::updateHaptics(cGenericHapticDevice* hapticDevice, double timeStep, double totalTime)
{
	//Read the current position of the haptic device
	cVector3d newPosition;
	hapticDevice->getPosition(newPosition);

	// Update position and orientation of cursor
    m_cursor->setLocalPos(newPosition);

	// Read linear velocity from device
	cVector3d linearVelocity;
	hapticDevice->getLinearVelocity(linearVelocity);

	// Update the line showing velocity
    m_velocityVector->m_pointA = newPosition;
    m_velocityVector->m_pointB = newPosition + linearVelocity;

	// Read user button status
	bool buttonStatus;
	hapticDevice->getUserSwitch(0, buttonStatus);

	// Adjust the color of the cursor according to the status of
	// the user switch (ON = TRUE / OFF = FALSE)
    m_cursor->m_material = buttonStatus ? m_matCursorButtonON : m_matCursorButtonOFF;

	cVector3d force(0, 0, 0);

	//Pull towards center
    force = -300.0f * newPosition;

	//Set a force to the haptic device
	hapticDevice->setForce(force);
}

#endif

