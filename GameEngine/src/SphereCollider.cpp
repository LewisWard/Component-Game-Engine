/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#include "SphereCollider.h"

namespace GE
{
	SphereCollider::SphereCollider()
	{
		m_type = kSphereCollider;
	}

	SphereCollider::SphereCollider(glm::vec3 center, float radius)
	{
		m_type = kSphereCollider;
		m_center = center;
		m_radius = radius;
	}

	SphereCollider::~SphereCollider() {}

	void SphereCollider::boundToObject(shared<GEC::ObjObject> obj)
	{
		glm::vec2 X, Y, Z;
		obj->getVertexRange(X, Y, Z);
		m_center = glm::vec3(X.x - X.y, Y.x - Y.y, Z.x - Z.y);
		m_radius = m_center.x - X.x;
	}

	bool SphereCollider::collision(SphereCollider& other)
	{
		// compute the distance between the two spheres
		glm::vec3 distanceDelta(m_center - other.getCenter());
		float distance = glm::sqrt((distanceDelta.x * distanceDelta.x) + (distanceDelta.y * distanceDelta.y) + (distanceDelta.z * distanceDelta.z));

		float radii = m_radius + other.getRadius();

		if (distance < radii)
			return true;

		return false;
	}
};
