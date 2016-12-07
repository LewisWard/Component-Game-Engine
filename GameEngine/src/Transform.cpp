// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 07/12/2016
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
		m = glm::scale(m, m_scale);
		m = glm::rotate(m, m_rotation.x, glm::vec3(1, 0, 0));
		m = glm::rotate(m, m_rotation.y, glm::vec3(0, 1, 0));
		m = glm::rotate(m, m_rotation.z, glm::vec3(0, 0, 1));
		m = glm::translate(m, m_position);
		m[3][3] = 1.0f;
		return m;
	}
};
