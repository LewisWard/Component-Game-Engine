// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 07/12/2016
#include "SphereCollider.h"

namespace GE
{
	SphereCollider::SphereCollider()
	{
		m_type = kSphereCollider;
	}

	SphereCollider::SphereCollider(glm::vec3 center, glm::vec3 radius)
	{
		m_type = kSphereCollider;
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
