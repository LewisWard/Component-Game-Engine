// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 08/11/2016
#pragma once
#include <cmath>
#include "glm\vec3.hpp"

namespace GEC
{
	class AABB
	{
	public:
		AABB() : center(0.0f), size(1.0f), extents(size * 0.5f), min(center - extents), max(center + extents)
		{
			min = glm::vec3(center - extents);
			max = glm::vec3(center + extents);
		}

		AABB(glm::vec3 center, glm::vec3 size) : center(center), size(size), extents(size * 0.5f) 
		{
			min = glm::vec3(center - extents);
			max = glm::vec3(center + extents);
		}

		~AABB() { };

		bool contains(glm::vec3 point);

		bool intersects(AABB aabb);

	public:
		glm::vec3 min;
		glm::vec3 max;
		glm::vec3 center;
		glm::vec3 size;
		glm::vec3 extents;
	};
};
