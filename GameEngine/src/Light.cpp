// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 31/03/2016
#include "Light.h"

namespace GE
{
	Light::Light()
	{
		m_type = kLight;
		m_position = glm::vec3(0, 0, 0);
		m_colour = glm::vec3(1, 1, 1);
		m_intensity = 1.0f;
	}

	Light::~Light()
	{

	}
};