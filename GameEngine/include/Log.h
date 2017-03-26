// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 26/10/2016
#pragma once
#include <iostream>
#include "glm\vec2.hpp"
#include "glm\vec3.hpp"
#include "glm\vec4.hpp"
#include "bullet3\LinearMath\btVector3.h"

namespace GE
{
	void consoleLog(const char* msg);
	void consoleLog(const char* msg, glm::vec2 v);
	void consoleLog(const char* msg, glm::vec3 v);
	void consoleLog(const char* msg, glm::vec4 v);
	void consoleLog(const char* msg, btVector3 v);
};
