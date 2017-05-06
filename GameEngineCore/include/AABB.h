/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#pragma once
#include <cmath>
#include "glm\vec3.hpp"

namespace GEC
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  Axis-Aligned Bounding Box
	//----------------------------------------------------------------------------------------------------------------------
	class AABB
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		AABB() : center(0.0f), size(1.0f), extents(size * 0.5f), min(center - extents), max(center + extents)
		{
			min = glm::vec3(center - extents);
			max = glm::vec3(center + extents);
		}

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		/// prama		glm::vec3 center
		/// prama		glm::vec3 size
		//----------------------------------------------------------------------------------------------------------------------
		AABB(glm::vec3 center, glm::vec3 size) : center(center), size(size), extents(size * 0.5f) 
		{
			min = glm::vec3(center - extents);
			max = glm::vec3(center + extents);
		}
		
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Desstructor
		//----------------------------------------------------------------------------------------------------------------------
		~AABB() { };

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  is a point inside this AABB
		/// prama		glm::vec3 point
		/// \return	bool
		//----------------------------------------------------------------------------------------------------------------------
		bool contains(glm::vec3 point);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  does this AABB intersect another AABB
		/// prama		glm::vec3 point
		/// \return	bool
		//----------------------------------------------------------------------------------------------------------------------
		bool intersects(const AABB& const aabb);

	public:
		glm::vec3 min;
		glm::vec3 max;
		glm::vec3 center;
		glm::vec3 size;
		glm::vec3 extents;
	};
};
