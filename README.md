# Game Engine by Lewis Ward 
## Introduction

A 3D component based Game Engine written in C++, using OpenGL with Bullet Physics integration. 

##  Installation

If on Windows and have Visual Studio 2015 and CMake installed, run: bin/BUILD_VS_x64.bat

CMake will generate a VS2015 Project then open GameEngine.sln. Otherwise, run CMake from within the bin directory (i.e. cmake ../)

If using Visual Studio, make sure that the "Game" Project rather then "ALL_BUILD" is set as the start up project. Then build and run.

Binaries output:

*bin/Debug/Game.exe
*bin/Release/Game.exe

When the game is running a console will also be open, see the console for more information such as controls.


## Copyright

Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.

Used libraries include within the Game Engine are works of their respected owners, if they came with a license file it can be found with the directory the library is in.

* Freeglut: http://freeglut.sourceforge.net/
* SOIL: http://www.lonesock.net/soil.html
* Bullet: http://bulletphysics.org/wordpress/
* GLM: http://glm.g-truc.net/0.9.8/index.html
