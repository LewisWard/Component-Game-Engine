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
	/// \brief Stores a Bullet btCollisionShape
	//----------------------------------------------------------------------------------------------------------------------
	class CollisionShape : public Component
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		CollisionShape();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Desstructor
		//----------------------------------------------------------------------------------------------------------------------
		~CollisionShape() { }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  creates a collision shape
		/// \parma  bullet collision shape (i.e. btBoxShape, btSphereShape, btCapsuleShape)
		//----------------------------------------------------------------------------------------------------------------------
		template <class T>
		void createShape(T shape)
		{
			m_collisionShape = mkShare<T>(shape);
		}

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get the btCollisionShape
		/// \return	glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		inline shared<btCollisionShape> getShape() { return m_collisionShape; }

	private:
		shared<btCollisionShape> m_collisionShape;
	};
};

