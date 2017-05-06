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
#include "Components.h"

namespace GE
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Sphere collision detection
	//----------------------------------------------------------------------------------------------------------------------
	class SphereCollider : public Component
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		SphereCollider();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		/// prama glm::vec3 center
		/// prama float radius
		//----------------------------------------------------------------------------------------------------------------------
		SphereCollider(glm::vec3 center, float radius);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Destructor
		//----------------------------------------------------------------------------------------------------------------------
		~SphereCollider();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  create the boundary based on the object
		/// prama shared<GEC::ObjObject>
		//----------------------------------------------------------------------------------------------------------------------
		void boundToObject(shared<GEC::ObjObject> obj);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get radius
		/// \return float
		//----------------------------------------------------------------------------------------------------------------------
		inline float getRadius() { return m_radius; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get center
		/// \return glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::vec3 getCenter() { return m_center; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set radius
		/// prama float
		//----------------------------------------------------------------------------------------------------------------------
		inline void setRadius(float r) { m_radius = r; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set center
		/// prama glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		inline void setCenter(glm::vec3 c) { m_center = c; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  check if a collision has occurred between another GE::SphereCollider
		/// prama GE::SphereCollider
		//----------------------------------------------------------------------------------------------------------------------
		bool collision(SphereCollider& other);

	private:
		glm::vec3 m_center;
		float m_radius;
	};
};
