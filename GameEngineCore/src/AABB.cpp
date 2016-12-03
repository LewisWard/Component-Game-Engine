// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 08/11/2016
#include "AABB.h"

namespace GEC
{
	bool AABB::contains(glm::vec3 point)
	{
		return (point.x > min.x && point.x < max.x && point.y > min.y && point.y < max.y && point.z > min.z && point.z < max.z);
	}

	bool AABB::intersects(AABB aabb)
	{
		return min.x <= aabb.max.x && max.x >= aabb.min.x &&
					 min.y <= aabb.max.y && max.y >= aabb.min.y &&
					 min.z <= aabb.max.z && max.z >= aabb.min.z;
	}
}