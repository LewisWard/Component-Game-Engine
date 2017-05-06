/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#include "..\include\Log.h"

void GE::consoleLog(const char * msg)
{
	std::cout << msg << std::endl;
}

void GE::consoleLog(const char* msg, int i)
{
	std::cout << msg << " " << i << std::endl;
}

void GE::consoleLog(const char* msg, float f)
{
	std::cout << msg << " " << f << std::endl;
}

void GE::consoleLog(const char* msg, const char* c)
{
	std::cout << msg << " " << c << std::endl;
}

void GE::consoleLog(const char * msg, glm::vec2 v)
{
	std::cout << msg << " " << v.x << " " << v.y << std::endl;
}

void GE::consoleLog(const char * msg, glm::vec3 v)
{
	std::cout << msg << " " << v.x << " " << v.y << " " << v.z << std::endl;
}

void GE::consoleLog(const char * msg, glm::vec4 v)
{
	std::cout << msg << " " << v.x << " " << v.y << " " << v.z << " " << v.w << std::endl;
}

void GE::consoleLog(const char* msg, btVector3 v)
{
	std::cout << msg << " " << v.getX() << " " << v.getY() << " " << v.getZ() << std::endl;
}

