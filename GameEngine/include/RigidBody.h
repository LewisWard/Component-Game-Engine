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
#include "CollisionShape.h"

namespace GE
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Stores the data for a Bullet btRigidBody
	//----------------------------------------------------------------------------------------------------------------------
	class RigidBody : public Component 
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		RigidBody();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Destructor
		//----------------------------------------------------------------------------------------------------------------------
		~RigidBody() { }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Creates a btRigidBody
		/// \parma  shared<GE::CollisionShape>
		/// \parma  glm::vec3 position
		/// \parma  float mass
		//----------------------------------------------------------------------------------------------------------------------
		void createRigidBody(shared<GE::CollisionShape> collisionShape, glm::vec3 position, float mass);


		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Gets the RigidBody's world transform from the motion state
		/// \parma  btTransform
		//----------------------------------------------------------------------------------------------------------------------
		void getBodyWorldTransform(btTransform& transform)
		{
			if (m_body && m_body->getMotionState())
			{
				m_body->getMotionState()->getWorldTransform(transform);
			}
		}

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Get the RigidBody
		/// \return shared<btRigidBody>
		//----------------------------------------------------------------------------------------------------------------------
		inline shared<btRigidBody> getRigidBody() { return m_body; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Get the RigidBody's motion state
		/// \return shared<btDefaultMotionState>
		//----------------------------------------------------------------------------------------------------------------------
		inline shared<btDefaultMotionState> getMotionState() { return m_motionState; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Get the RigidBody's local inertia
		/// \return btVector3
		//----------------------------------------------------------------------------------------------------------------------
		inline btVector3 getLocalInertia() { return m_localInertia; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Get the RigidBody's mass
		/// \return btScalar
		//----------------------------------------------------------------------------------------------------------------------
		inline btScalar getMass() { return m_mass; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Get if the RigidBody is dynamic
		/// \return bool, true if dynamic
		//----------------------------------------------------------------------------------------------------------------------
		inline bool isDynamic() { return m_isDynamic; }

	private:
		shared<btRigidBody> m_body;
		shared<btDefaultMotionState> m_motionState;
		btVector3 m_localInertia;
		btScalar m_mass;
		bool m_isDynamic;
	};
};
