// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#include "RigidBody.h"

namespace GE
{
	RigidBody::RigidBody()
	{
		m_type = kRigidBody;
	}

	void RigidBody::createRigidBody(shared<GE::CollisionShape> collisionShape, glm::vec3 position, float mass)
	{
		{
			btVector3 origin(position.x, position.y, position.z);
			btVector3 localInertia(0, 0, 0);
			m_mass = (btScalar)mass;
			bool m_isDynamic = (m_mass != 0.0f); // is static only if mass is zero

			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(origin);

			if (m_isDynamic)
				collisionShape->getShape()->calculateLocalInertia(m_mass, localInertia);

			m_motionState = mkShare<btDefaultMotionState>(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo(m_mass, m_motionState.get(), collisionShape->getShape().get(), localInertia);
			m_body = mkShare<btRigidBody>(rigidBodyInfo);
		}
	}
};
