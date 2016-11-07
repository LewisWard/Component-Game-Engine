// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#pragma once

#define ENGINEASSETS "../EngineAssets/"

#ifdef _WIN32
#include <Windows.h>
#endif
#define GLEW_STATIC
#include "glew.h"
#include "GL\glut.h"
#include "gl/freeglut_ext.h"
#include "glFunctions.h"
#include "soil/SOIL.h"
#include <iostream>
#include <memory>
#define shared std::shared_ptr
#define mkShare std::make_shared
#define weak std::weak_ptr
static int windowOldWidth = 0;
static int windowOldHeight = 0;
static bool windowUpdated = false;

//----------------------------------------------------------------------------------------------------------------------
/// \brief  freeglut initialisation
/// \return bool true if glut initialisation was susscessful
//----------------------------------------------------------------------------------------------------------------------
bool initGlut(int& argc, char** argv);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  glew initialisation
/// \return GLenum true if glew initialisation was susscessful
//----------------------------------------------------------------------------------------------------------------------
GLenum initGlew();

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Delta Time 
//----------------------------------------------------------------------------------------------------------------------
void initTimerDT(); ///< initialisation
float updateTimerDT(); ///< update, return delta time

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Uses the current Delta Time to compute the current Frames Per Second (FPS)
/// \parma	float delta time
/// \return	FPS
//----------------------------------------------------------------------------------------------------------------------
float currentFPS(float& dt);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  When a key is pressed down
/// \parma  unsigned char key
/// \parma  int
/// \parma  int
//----------------------------------------------------------------------------------------------------------------------
void keyboardOnPress(unsigned char key, int, int);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  When a key is pressed released
/// \parma  unsigned char key
/// \parma  int
/// \parma  int
//---------------------------------------------------------------------------------------------------------------------
void keyboardOnRelease(unsigned char key, int, int);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  When a special key is pressed
/// \parma  int key
/// \parma  int
/// \parma  int
//---------------------------------------------------------------------------------------------------------------------
void keyboardSpecialKeys(int key, int, int);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Has the key been pressed
/// \parma  short key
//----------------------------------------------------------------------------------------------------------------------
bool isKeyPressed(short key);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Toggle full screen mode
/// \parma  bool
//----------------------------------------------------------------------------------------------------------------------
void toggleFullScreen(const bool& s);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Handles mouse input
/// \parma  int (GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
/// \parma  int (GLUT_DOWN, GLUT_UP)
/// \parma  int mouse X position (from upper left)
/// \parma  int mouse Y position (from upper left)
//----------------------------------------------------------------------------------------------------------------------
void mouseInput(int button, int state, int x, int y);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  is a mouse key pressed
/// \parma  short (GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
/// \return bool
//----------------------------------------------------------------------------------------------------------------------
bool isMouseKeyPressed(short key);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  gets the mouse position
/// \parma  int X
/// \parma  int Y
//----------------------------------------------------------------------------------------------------------------------
void mousePosition(int& x, int& y);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  gets the mouse position when a mouse button was clicked and moving
/// \parma  int X
/// \parma  int Y
//----------------------------------------------------------------------------------------------------------------------
void mouseMotion(int x, int y);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  gets the mouse position when a mouse is just moving
/// \parma  int X
/// \parma  int Y
//----------------------------------------------------------------------------------------------------------------------
void mousePassiveMotion(int x, int y);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Is the window in full screen mode
/// \return bool true is in fullscreen
//----------------------------------------------------------------------------------------------------------------------
bool isFullScreen();

//----------------------------------------------------------------------------------------------------------------------
/// \brief  What to resize the screen to
/// \parma  int width
/// \parma  int height
//----------------------------------------------------------------------------------------------------------------------
void onResize(int width, int height);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  get the screen size
/// \parma  int width
/// \parma  int height
//----------------------------------------------------------------------------------------------------------------------
void getSize(int& newWidth, int& newHeight);

inline void windowRename(const char* name) { glutSetWindowTitle(name); }

//----------------------------------------------------------------------------------------------------------------------
/// \brief  delete/free memory
//----------------------------------------------------------------------------------------------------------------------
void cleanup();

//----------------------------------------------------------------------------------------------------------------------
/// \brief  MAIN ENETRY POINT! called from main(), calls glut functions.
//----------------------------------------------------------------------------------------------------------------------
int run(int argc, char* argv[]);


