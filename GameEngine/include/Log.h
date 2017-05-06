/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#pragma once
#include <iostream>
#include "glm\vec2.hpp"
#include "glm\vec3.hpp"
#include "glm\vec4.hpp"
#include "bullet3\LinearMath\btVector3.h"

namespace GE
{
	void consoleLog(const char* msg);
	void consoleLog(const char* msg, int i);
	void consoleLog(const char* msg, float f);
	void consoleLog(const char* msg, const char* c);
	void consoleLog(const char* msg, glm::vec2 v);
	void consoleLog(const char* msg, glm::vec3 v);
	void consoleLog(const char* msg, glm::vec4 v);
	void consoleLog(const char* msg, btVector3 v);
};
