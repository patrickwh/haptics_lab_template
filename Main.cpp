//===========================================================================
/*

	CS277 - Experimental Haptics
	Winter 2010, Stanford University


	You may use this program as a boilerplate for starting your homework
	assignments.  Use CMake (www.cmake.org) on the CMakeLists.txt file to
	generate project files for the development tool of your choice.  The
	CHAI3D library directory (chai3d-2.1.0) should be installed as a sibling
	directory to the one containing this project.


	These files are meant to be helpful should you encounter difficulties
	setting up a working CHAI3D project.  However, you are not required to
	use them for your homework -- you may start from anywhere you'd like.


	\author    Francois Conti & Sonny Chan
	\date      January 2010
	*/
//===========================================================================
// This define is needed for some gcc5 reason
// http://stackoverflow.com/questions/33394934/converting-std-cxx11string-to-stdstring
#define _GLIBCXX_USE_CXX11_ABI 0

//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

//---------------------------------------------------------------------------
#include "chai3d.h"

#include "GL/glut.h"
#include "Assignment.h"

#include "1_HelloWorld.h"
#include "2_ReadDevicePosition.h"
#include "3_BasicForceEffects.h"
#include "4_HapticWall.h"
#include "5_MagneticEffect.h"
#include "6_HapticSphere.h"
#include "watergame.h"
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
// DECLARED CONSTANTS
//---------------------------------------------------------------------------
// Initial size (width/height) in pixels of the display window
const int WINDOW_SIZE_W = 600;
const int WINDOW_SIZE_H = 600;


// Mouse menu options (right button)
const int OPTION_FULLSCREEN = 1;
const int OPTION_WINDOWDISPLAY = 2;


// Maximum number of haptic devices supported in this demo
const int MAX_DEVICES = 8;



//---------------------------------------------------------------------------
// DECLARED VARIABLES
//---------------------------------------------------------------------------
// A list of all available assignments
std::vector<Assignment*> assignments;
volatile size_t currentAssignment = 0;


// A world that contains all objects of the virtual environment
cWorld* world = 0;


// A camera that renders the world in a window display
cCamera* camera;


// A light source to illuminate the objects in the virtual scene
cDirectionalLight *light;


// Width and height of the current window display
int displayW = WINDOW_SIZE_W;
int displayH = WINDOW_SIZE_H;


// A haptic device handler
cHapticDeviceHandler* handler;


// A pointer to the first haptic device detected on this computer
cGenericHapticDevicePtr hapticDevice = 0;


// Labels to show haptic device position, update rate and assignment text
cLabel* positionLabel = 0;
cLabel* rateLabel = 0;
cLabel* assignmentLabel = 0;
double assignmentLabelWidth;
double rateEstimate = 0;


// A clock measuring the total time
cPrecisionClock clockTotal;


// Status of the main simulation haptics loop
bool simulationRunning = false;


// Has exited haptics simulation thread
bool simulationFinished = false;


//---------------------------------------------------------------------------
// DECLARED FUNCTIONS
//---------------------------------------------------------------------------
// Callback when the window display is resized
void resizeWindow(int w, int h);

// Callback when a keyboard key is pressed
void keySelect(unsigned char key, int, int);

// Callback when the right mouse button is pressed to select a menu item
void menuSelect(int value);

// Function called before exiting the application
void close(void);

// Main graphics callback
void updateGraphics(void);

// callback of GLUT timer
void graphicsTimer(int);

// Main haptics loop
void updateHaptics(void);

// Reset the scene with a new scene according to 'assignmentId'
void reset(size_t assignmentId);
//===========================================================================

/*
	This application illustrates the use of the haptic device handler
	"cHapticDevicehandler" to access haptic devices connected to the computer.


	In this example the application opens an OpenGL window and displays a
	3D cursor for the first device found. If the operator presses the device
	user button, the color of the cursor changes accordingly.

	In the main haptics loop function  "updateHaptics()" , the position and
	user switch status of the device are retrieved at each simulation iteration.
	This information is then used to update the position and color of the
	cursor. A force is then commanded to the haptic device to attract the
	end-effector towards the device origin.
*/
//===========================================================================



int main(int argc, char* argv[])
{

	//-----------------------------------------------------------------------
	// INITIALIZATION
	//-----------------------------------------------------------------------
	std::cout << std::endl;
	std::cout << "Based on:" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "CS277 - Experimental Haptics" << std::endl;
	std::cout << "Homework Boilerplate Application" << std::endl;
	std::cout << "January 2010, Stanford University" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << std::endl << std::endl;

	//-----------------------------------------------------------------------
	// ASSIGNMENTS
	//-----------------------------------------------------------------------

	// Load the available assignment scenes
	assignments.push_back(new HelloWorld());
	assignments.push_back(new ReadDevicePosition());
	assignments.push_back(new BasicForceEffects());
	assignments.push_back(new HapticWall());
	assignments.push_back(new MagneticEffect());
	assignments.push_back(new HapticSphere());
    assignments.push_back(new WaterGame());

	//-----------------------------------------------------------------------
	// HAPTIC DEVICES / TOOLS
	//-----------------------------------------------------------------------

    // Create a haptic device handler
    handler = new cHapticDeviceHandler();

	// Read the number of haptic devices currently connected to the computer
    int numHapticDevices = handler->getNumDevices();

    // If there is at least one haptic device detected...
	if (numHapticDevices)
	{

		// Get a handle to the first haptic device
		handler->getDevice(hapticDevice);

		// Open connection to haptic device
		hapticDevice->open();

        // Calbrate if needed
        hapticDevice->calibrate();

		// Retrieve information about the current haptic device
		cHapticDeviceInfo info = hapticDevice->getSpecifications();
	}

	//-----------------------------------------------------------------------
	// OPEN GL - WINDOW DISPLAY
	//-----------------------------------------------------------------------

	// Initialize GLUT
	glutInit(&argc, argv);

	// Retrieve the resolution of the computer display and estimate the position
	// of the GLUT window so that it is located at the center of the screen
	int screenW = glutGet(GLUT_SCREEN_WIDTH);
	int screenH = glutGet(GLUT_SCREEN_HEIGHT);
	int windowPosX = (screenW - WINDOW_SIZE_W) / 2;
	int windowPosY = (screenH - WINDOW_SIZE_H) / 2;


	// Initialize the OpenGL GLUT window
	glutInitWindowPosition(windowPosX, windowPosY);
    glutInitWindowSize(WINDOW_SIZE_W, WINDOW_SIZE_H);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(updateGraphics);
	glutKeyboardFunc(keySelect);
	glutReshapeFunc(resizeWindow);
    glutSetWindowTitle("DT2140,multimodal interaction and interfaces,lab4");
    glewInit();


	// Create a mouse menu (right button)
	glutCreateMenu(menuSelect);
	glutAddMenuEntry("full screen", OPTION_FULLSCREEN);
	glutAddMenuEntry("window display", OPTION_WINDOWDISPLAY);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    //-----------------------------------------------------------------------
	// START SIMULATION
	//-----------------------------------------------------------------------
	// Initialize the world with assignment 0
	reset(0);

	// Simulation in now running
	simulationRunning = true;

    // Create a thread which starts the main haptics rendering loop
    cThread* hapticsThread = new cThread();
    hapticsThread->start(updateHaptics, CTHREAD_PRIORITY_HAPTICS);

	// Start the main graphics rendering loop
    glutTimerFunc(50, graphicsTimer, 0);
	glutMainLoop();

	// Close everything
	close();

	// Exit
	return (0);
}
//---------------------------------------------------------------------------



void graphicsTimer(int)
{
    if (simulationRunning)
    {
        glutPostRedisplay();
    }
    glutTimerFunc(50, graphicsTimer, 0);
}


void reset(size_t assignmentId)
{
	// Deactivate the old scene
	assignments[currentAssignment]->setInitialized(false);
	currentAssignment = assignmentId;

	// Delete the old world and create a new one
    delete world;
	world = new cWorld();
	world->setBackgroundColor(0.0, 0.0, 0.0);

	// Create a camera and insert it into the virtual world
	camera = new cCamera(world);
	world->addChild(camera);

	// Position and oriente the camera
	camera->set(cVector3d(0.2, 0.0, 0.0),    // camera position (eye)
                cVector3d(0.0, 0.0, 0.0),    // lookat position (target)
                cVector3d(0.0, 0.0, 1.0));   // direction of the "up" vector


	// Set the near and far clipping planes of the camera
	// anything in front/behind these clipping planes will not be rendered
	camera->setClippingPlanes(0.01, 10.0);

	// Create a light source and attach it to the camera
    light = new cDirectionalLight(world);
	camera->addChild(light);                   // attach light to camera
	light->setEnabled(true);                   // enable light source
    light->setLocalPos(cVector3d(2.0, 0.5, 1.0));  // position the light source
	light->setDir(cVector3d(-2.0, 0.5, 1.0));  // define the direction of the light beam

	// Create a label that shows the haptic loop update rate
    cFont *font = NEW_CFONTCALIBRI20();
    rateLabel = new cLabel(font);
    camera->m_frontLayer->addChild(rateLabel);

    // Create a label that shows the current position of the device
    positionLabel = new cLabel(font);
    positionLabel->setLocalPos(8, 8, 0);
    camera->m_frontLayer->addChild(positionLabel);

    // Create a label that shows the current assignment name
    assignmentLabel = new cLabel(font);
    camera->m_frontLayer->addChild(assignmentLabel);

	// Initialize the current assignment
    assignments[currentAssignment]->initialize(world, camera);

	// Update the assignment label
    assignmentLabel->setString(assignments[currentAssignment]->getName());

	// Precalculate width to make it centered
    assignmentLabelWidth = assignmentLabel->m_font->getStringWidth(assignmentLabel->getString());
    assignments[currentAssignment]->setInitialized(true);


	// Restart the clock measuring total time elapsed
	clockTotal.start(true);
}
//---------------------------------------------------------------------------


void resizeWindow(int w, int h)
{
	// Update the size of the viewport
	displayW = w;
	displayH = h;
	glViewport(0, 0, displayW, displayH);
}


//---------------------------------------------------------------------------
void keySelect(unsigned char key, int, int)
{
	// Escape key
	if ((key == 27) || (key == 'x'))
	{
		// Close everything
		close();

		// Exit application
		exit(0);
	}

    // Key 1 - 9 corresponding to an existing assignment
	if (key >= '1' && key < '1' + assignments.size())
	{
		// Change assignment
		reset(key - '1');
	}
}
//---------------------------------------------------------------------------


void menuSelect(int value)
{
	switch (value)
	{
        // Enable full screen display
        case OPTION_FULLSCREEN:
		glutFullScreen();
		break;

        // Reshape window to original size
        case OPTION_WINDOWDISPLAY:
		glutReshapeWindow(WINDOW_SIZE_W, WINDOW_SIZE_H);
		break;
	}
}


//---------------------------------------------------------------------------

void close(void)
{
	// Stop the simulation
	simulationRunning = false;

    // Wait for graphics and haptics loops to terminate
	while (!simulationFinished) { cSleepMs(100); }

	// Close the haptic devices
	if (hapticDevice)
	{
		hapticDevice->close();
	}
}

//---------------------------------------------------------------------------

void updateGraphics(void)
{

	// Update the label showing the position of the haptic device
	if (hapticDevice)
	{
		cVector3d position;
		hapticDevice->getPosition(position);
		position = position * 1000.0; // Convert to mm

		char buffer[128];

        sprintf(buffer, "Device position: (%.2lf, %.2lf, %.2lf) mm", position.x(), position.y(), position.z());

		//Set the text to the label
        positionLabel->setString(buffer);
	}

	if (assignments[currentAssignment]->isInitialized())
		assignments[currentAssignment]->updateGraphics();


	// Update the label with the haptic refresh rate
	char buffer[128];
	sprintf(buffer, "Haptic rate: %.0lf Hz", rateEstimate);
    rateLabel->setString(buffer);
    rateLabel->setLocalPos(displayW - 120, 8, 0);

    assignmentLabel->setLocalPos(0.5 * (displayW - assignmentLabelWidth), displayH - 20, 0);

	// Render world
	camera->renderView(displayW, displayH);

	// Swap buffers
	glutSwapBuffers();

	// Check for any OpenGL errors
	GLenum err;
	err = glGetError();
	if (err != GL_NO_ERROR) printf("Error:  %s\n", gluErrorString(err));

	// Inform the GLUT window to call updateGraphics again (next frame)
	if (simulationRunning)
	{
		glutPostRedisplay();
	}
}

//---------------------------------------------------------------------------


void updateHaptics(void)
{
	// A clock to estimate the haptic simulation loop update rate
	cPrecisionClock pclock;
	pclock.setTimeoutPeriodSeconds(1.0);
	pclock.start(true);
	int counter = 0;
	cPrecisionClock frameClock;
	frameClock.start(true);

	// Main haptic simulation loop
	while (simulationRunning)
	{
		if (!hapticDevice)
			continue;

		// Total time elapsed since the current assignment started
		double totalTime = clockTotal.getCurrentTimeSeconds();

		// Time elapsed since the previous haptic frame
		double timeStep = frameClock.getCurrentTimeSeconds();
		frameClock.start(true);

		// Update assignment
		if (assignments[currentAssignment]->isInitialized())
            assignments[currentAssignment]->updateHaptics(hapticDevice.get(), timeStep, totalTime);

		// Estimate the refresh rate
		++counter;
		if (pclock.timeoutOccurred()) {
			pclock.stop();
			rateEstimate = counter;
			counter = 0;
			pclock.start(true);
		}
	}

	// Exit haptics thread
	simulationFinished = true;
}

//---------------------------------------------------------------------------
