#include "..\include\Log.h"

void GE::consoleLog(const char * msg)
{
	std::cout << msg << std::endl;
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
