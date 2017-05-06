/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#include "AABB.h"

namespace GEC
{
	bool AABB::contains(glm::vec3 point)
	{
		return (point.x > min.x && point.x < max.x && point.y > min.y && point.y < max.y && point.z > min.z && point.z < max.z);
	}

	bool AABB::intersects(const AABB& const aabb)
	{
		return min.x <= aabb.max.x && max.x >= aabb.min.x &&
					 min.y <= aabb.max.y && max.y >= aabb.min.y &&
					 min.z <= aabb.max.z && max.z >= aabb.min.z;
	}
};
