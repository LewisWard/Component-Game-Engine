// Author  : Lewis Ward (i7212443)
// Program : 3D Render Engine
// Date    : 7/11/2015
#pragma once
#include <iostream>
#include "glm\vec2.hpp"
#include "glm\vec3.hpp"
#include "glm\vec4.hpp"

namespace GE
{
	void consoleLog(const char* msg);
	void consoleLog(const char* msg, glm::vec2 v);
	void consoleLog(const char* msg, glm::vec3 v);
	void consoleLog(const char* msg, glm::vec4 v);
};
