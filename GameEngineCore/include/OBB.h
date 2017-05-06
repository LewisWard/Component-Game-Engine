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
#include "AABB.h"
#include "glm\matrix.hpp"
#include "glm\gtx\rotate_vector.hpp"

namespace GEC
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  Object Bounding Box
	/// \note implementation is not complete, avoid using for the moment.
	//----------------------------------------------------------------------------------------------------------------------
	class OBB
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		OBB() : center(0.0f), size(1.0f), extents(size * 0.5f), min(center - extents), max(center + extents)
		{
			min = glm::vec3(center - extents);
			max = glm::vec3(center + extents);

			m_objectBounds[0] = glm::vec3(min.x, min.y, min.z);
			m_objectBounds[1] = glm::vec3(max.x, min.y, min.z);
			m_objectBounds[2] = glm::vec3(min.x, max.y, min.z);
			m_objectBounds[3] = glm::vec3(max.x, max.y, min.z);
			m_objectBounds[4] = glm::vec3(min.x, min.y, max.z);
			m_objectBounds[5] = glm::vec3(max.x, min.y, max.z);
			m_objectBounds[6] = glm::vec3(min.x, max.y, max.z);
			m_objectBounds[7] = glm::vec3(max.x, max.y, max.z);
		}

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		/// prama		glm::vec3 center
		/// prama		glm::vec3 size
		//----------------------------------------------------------------------------------------------------------------------
		OBB(glm::vec3 center, glm::vec3 size) : center(center), size(size), extents(size * 0.5f)
		{
			min = glm::vec3(center - extents);
			max = glm::vec3(center + extents);

			m_objectBounds[0] = glm::vec3(min.x, min.y, min.z);
			m_objectBounds[1] = glm::vec3(max.x, min.y, min.z);
			m_objectBounds[2] = glm::vec3(min.x, max.y, min.z);
			m_objectBounds[3] = glm::vec3(max.x, max.y, min.z);
			m_objectBounds[4] = glm::vec3(min.x, min.y, max.z);
			m_objectBounds[5] = glm::vec3(max.x, min.y, max.z);
			m_objectBounds[6] = glm::vec3(min.x, max.y, max.z);
			m_objectBounds[7] = glm::vec3(max.x, max.y, max.z);

			glm::mat3 worldSpace(1.0f);

			// object to world space
			for (int i = 0; i < 8; i++)
				m_objectBounds[i] = worldSpace * m_objectBounds[i];
		}

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Desstructor
		//----------------------------------------------------------------------------------------------------------------------
		~OBB() { };

		void rotate(glm::vec3 rotation)
		{
			// object to world space
			for (int i = 0; i < 8; i++)
			{
				m_objectBounds[i] = glm::rotateX(m_objectBounds[i], rotation.x);
				m_objectBounds[i] = glm::rotateY(m_objectBounds[i], rotation.y);
				m_objectBounds[i] = glm::rotateZ(m_objectBounds[i], rotation.z);
			}
		}

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  is a point inside this AABB
		/// prama		glm::vec3 point
		/// \return	bool
		//----------------------------------------------------------------------------------------------------------------------
		bool contains(glm::vec3 point)
		{
			return (point.x > min.x && point.x < max.x && point.y > min.y && point.y < max.y && point.z > min.z && point.z < max.z);
		}

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  does this AABB intersect another AABB
		/// prama		glm::vec3 point
		/// \return	bool
		//----------------------------------------------------------------------------------------------------------------------
		bool intersects(const AABB& const aabb)
		{
			return min.x <= aabb.max.x && max.x >= aabb.min.x &&
				min.y <= aabb.max.y && max.y >= aabb.min.y &&
				min.z <= aabb.max.z && max.z >= aabb.min.z;
		}

	public:
		glm::vec3 m_objectBounds[8];
		glm::vec3 min;
		glm::vec3 max;
		glm::vec3 center;
		glm::vec3 size;
		glm::vec3 extents;
	};
};
