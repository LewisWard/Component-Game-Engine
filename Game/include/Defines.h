/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
/**
* \mainpage Game Engine Documentation
*
* \section Game Engine by Lewis Ward
*
* \subsection Introduction
* A 3D component based Game Engine written in C++, using OpenGL with Bullet Physics integration. 
* 
* \subsection  Installation
* If on Windows and have Visual Studio 2015 installed, run: bin/BUILD_VS_x64.bat
*
* CMake will generate a VS2015 Project then open GameEngine.sln. Otherwise, run CMake from within the bin directory (i.e. cmake ../)
* 
* \subsection Copyright
* Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the author be held liable for any damages arising from the use of this software.
* Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
* subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
* 2. This notice may not be removed or altered from any source distribution.
* 
* Included and used libraries include within the Engine are works of their respected owners, if they came with a license file it can be found with the directory the library is in.
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
