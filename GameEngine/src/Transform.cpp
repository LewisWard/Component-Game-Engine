/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#include "Transform.h"

namespace GE
{
	Transform::Transform()
	{
		m_type = kTransform;
		m_position = glm::vec3(0.0f);
		m_scale = glm::vec3(1.0f);
		m_rotation = glm::vec3(0.0f);
	}

	Transform::Transform(const Transform & t)
	{
		m_position = t.m_position;
		m_scale = t.m_scale;
		m_rotation = t.m_rotation;
	}

	Transform::~Transform()
	{

	}

	glm::mat4 Transform::createTransform()
	{
		glm::mat4 m;
		m = glm::translate(m, m_position);
		m = glm::rotate(m, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
		m = glm::rotate(m, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
		m = glm::rotate(m, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
		m = glm::scale(m, m_scale);
		m[3][3] = 1.0f;
		return m;
	}
};
