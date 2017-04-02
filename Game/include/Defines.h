// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 20/03/2017

/**
* \mainpage Game Engine Documentation
*
* \section Game Engine by Lewis Ward (i7212443)
*
* \subsection Introduction
* A 3D component based Game Engine written in C++. All classes that have not untouched from the first assignment have a comment marked 
* at the top of their file to indicate if a class is new or modified from the first assignment or not.
* 
* \subsection  Installation
* To load the engine project open GameEngine.sln.
*
* To run a build, they are found in:
*
* bin/Release/x64/Game.exe
*
* bin/Debug/x64/Game.exe
* 
* 
* \subsection Copyright
* Allow included and used libraries include within the Engine are works of their respected owners, if they came with a license file it can be found with the directory the library is in.
*
* Freeglut: http://freeglut.sourceforge.net/
*
* SOIL: http://www.lonesock.net/soil.html
*
* Bullet: http://bulletphysics.org/wordpress/
*
* GLM: http://glm.g-truc.net/0.9.8/index.html
*
*/

#pragma once
#define RELEASEINBUILD 0
#define TEXTURE_LOW 512
#define TEXTURE_MEDIUM 1024
#define TEXTURE_HIGH 2048
#define RES_LOW_X 1280
#define RES_LOW_Y 720
#define RES_MEDIUM_X 1600
#define RES_MEDIUM_Y 900
#define RES_HIGH_X 1920
#define RES_HIGH_Y 1080
#define RES_SUPER_X 2560
#define RES_SUPER_Y 1440
#define SHOW_MOUSE 1
#define MULTI_KEY_HIGHER 1
#define MULTI_KEY_LOWER -1
#define MULTI_KEY_NONE 0
#define BULLET_DEBUG_DRAW 0
#define BULLET_DRAW_ALL 0
