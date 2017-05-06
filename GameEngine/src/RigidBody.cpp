/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
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
