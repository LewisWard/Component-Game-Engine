// Author  : Lewis Ward (i7212443)
// Program : 3D Renderer
// Date    : 09/10/2016
#include "Window.h"


bool initGlut(int & argc, char ** argv)
{
	glutInit(&argc, argv);

	// initialisation susscessful
	return true;
}

GLenum initGlew()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if(GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	return err;
}

// gobal variables for dt
uint64_t g_startCount = 0, g_lastCount = 0, g_newTime = 0;
float g_CPS;

void initTimerDT()
{
	// get the current performance-counter frequency
	QueryPerformanceFrequency((LARGE_INTEGER*)&g_startCount);
	// compute Count Per Seconds (CPS)
	g_CPS = 1.0f / g_startCount;

	// setup previous time
	QueryPerformanceCounter((LARGE_INTEGER*)&g_lastCount);
}

float updateTimerDT()
{
	// get the current frequency
	QueryPerformanceCounter((LARGE_INTEGER*)&g_newTime);
	// compute the DT
	float dt = (g_newTime - g_lastCount) * g_CPS;
	// update last time value with new
	g_lastCount = g_newTime;
	// return dt
	return dt;
}

// this will be decleared within the main.cpp for the app (i.e. Demo)
extern void init();
extern void update(float dt);
extern void draw3D();

void refresh()
{
	// update dt
	float dtTemp = updateTimerDT();

	// update
	update(dtTemp);

	// tell glut to redraw the screen
	glutPostRedisplay();
}

float currentFPS(float& dt)
{
	// 1000/60 = 16.666666666666666666666666666667ms (ms per frame)
	// get to number of ms based on dt
	float milliseconds = dt * 1000.0f;

	// check it is not zero (stops divion by zero)
	if (std::abs(milliseconds) < 0.00000f)
		milliseconds = 0.00001f;

	// convert from ms to FPS
	return (1000.0f / milliseconds);
}

static bool g_keys[512] = { false }; ///< Keyboard keys pressed
static bool g_mouseKeys[3] = { false }; ///< Mouse keys pressed (left, middle, right)
static int mousePositionX = 0;
static int mousePositionY = 0;

void mouseInput(int button, int state, int x, int y)
{
	g_mouseKeys[button] = !state;
	mousePositionX = x;
	mousePositionY = y;
}

bool isMouseKeyPressed(short key)
{
	return g_mouseKeys[key];
}

void mousePosition(int& x, int& y)
{
	x = mousePositionX;
	y = mousePositionY;
}

void mouseMotion(int x, int y)
{
	mousePositionX = x;
	mousePositionY = y;
}

void mousePassiveMotion(int x, int y)
{
	mousePositionX = x;
	mousePositionY = y;
}

void keyboardOnPress(unsigned char key, int, int)
{
	// if the escape key is pressed close the program
	if (key == 27)
		exit(0);

	g_keys[key] = true;
}

void keyboardOnRelease(unsigned char key, int, int)
{
	g_keys[key] = false;
}

void keyboardSpecialKeys(int key, int, int)
{
	// don't have much use for any of the keys now but for more details see:
	// https://www.opengl.org/resources/libraries/glut/spec3/node54.html
	switch (key)
	{
		case GLUT_KEY_F1: break;
		case GLUT_KEY_F2: break;
		case GLUT_KEY_F3: break;
		case GLUT_KEY_F4: break;
		case GLUT_KEY_F5: break;
		case GLUT_KEY_F6: break;
		case GLUT_KEY_F7: break;
		case GLUT_KEY_F8: break;
		case GLUT_KEY_F9: break;
		case GLUT_KEY_F10: break;
		case GLUT_KEY_F11: break;
		case GLUT_KEY_F12: break;
		case GLUT_KEY_LEFT: break;
		case GLUT_KEY_RIGHT: break;
		case GLUT_KEY_UP: break;
		case GLUT_KEY_DOWN: break;
		case GLUT_KEY_PAGE_UP: break;
		case GLUT_KEY_PAGE_DOWN: break;
		case GLUT_KEY_HOME: break;
		case GLUT_KEY_END: break;
		case GLUT_KEY_INSERT: break;
	}
}

bool isKeyPressed(short key)
{
	return g_keys[key];
}

static bool g_isFullscreen = false;

void toggleFullScreen(const bool& s)
{
	if (s != g_isFullscreen)
	{
		glutFullScreenToggle();
		g_isFullscreen = s;
	}
}

bool isFullScreen()
{
	return g_isFullscreen;
}

void onResize(int width, int height)
{
	windowUpdated = false;

	if (windowOldWidth != width)
	{
		windowOldWidth = width;
		windowUpdated = true;
	}

	if (windowOldHeight != height)
	{
		windowOldHeight = height;
		windowUpdated = true;
	}

	if (windowUpdated)
		glutReshapeWindow(width, height);
}

void getSize(int& newWidth, int& newHeight) 
{ 
	newWidth = windowOldWidth;
	newHeight = windowOldHeight;
}

int run()
{
	// setup glut and window
	char* argv[] = { "GameEngine.exe", 0 };
	int argc = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("GameEngineWindow");
	initGlew();
	glutMouseFunc(mouseInput);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutKeyboardFunc(keyboardOnPress);
	glutKeyboardUpFunc(keyboardOnRelease);
	glutSpecialFunc(keyboardSpecialKeys);
	glutReshapeFunc(onResize);
	glutDisplayFunc(draw3D);	
	glutIdleFunc(refresh);

	// init delta time and user assests
	init();
	initTimerDT();
	
	// when the window is closed, quit the loop and continue to run the program (i.e. cleanup)
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutMainLoop();

	// clean up
	cleanup();

	return 0;
}
