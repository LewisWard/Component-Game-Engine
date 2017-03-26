// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 25/03/2016
#pragma once
#include "CollisionShape.h"

namespace GE
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Stores the data for a Bullet btRigidBody
	//----------------------------------------------------------------------------------------------------------------------
	class RidigBody : public Component 
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		RidigBody();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Destructor
		//----------------------------------------------------------------------------------------------------------------------
		~RidigBody() { }

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


		shared<btRigidBody> getRigidBody() { return m_body; }

		shared<btDefaultMotionState> getMotionState() { return m_motionState; }

		btVector3 getLocalInertia() { return m_localInertia; }

		btScalar getMass() { return m_mass; }

		bool isDynamic() { return m_isDynamic; }

	private:
		shared<btRigidBody> m_body;
		shared<btDefaultMotionState> m_motionState;
		btVector3 m_localInertia;
		btScalar m_mass;
		bool m_isDynamic;
	};
};
