// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 06/12/2016
#include "Camera.h"

namespace GE
{
	Camera::Camera(glm::vec3 position, glm::vec3 facing, glm::vec2 screen, float FoV, float nearPlane, float farPlane) : m_position(position), m_facing(facing), m_screenSize(screen)
	{
		m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_view = glm::lookAt(m_position, m_facing, m_up);
		m_projection = glm::perspective(FoV, m_screenSize.x / m_screenSize.y, nearPlane, farPlane);
	}

	Camera::~Camera()
	{

	}
};
