/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
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
