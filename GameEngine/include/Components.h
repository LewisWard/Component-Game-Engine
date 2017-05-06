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
#include "Program.h"
#include "Camera.h"
#include "Log.h"
#include "AABB.h"
#include <vector>
#include <memory>

namespace GE
{
	// forward declear, see GameObject.h
	class GameObject;

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Type of components
	//----------------------------------------------------------------------------------------------------------------------
	enum ComponentType
	{
		kTransform,
		kMeshRenderer,
		kBoxCollider,
		kSphereCollider,
		kCollisionShape,
		kRigidBody,
		kLight
	};

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Component base class, GE::GameObjects can have many components attached to them
	//----------------------------------------------------------------------------------------------------------------------
	class Component
	{
	friend class GameObject;

	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		Component();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Destructor
		//----------------------------------------------------------------------------------------------------------------------
		virtual ~Component();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  When the component is loaded first time
		//----------------------------------------------------------------------------------------------------------------------
		virtual void onLoad();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Update
		/// prama		float delta time
		//----------------------------------------------------------------------------------------------------------------------
		virtual void onUpdate(float dt);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Draw
		//----------------------------------------------------------------------------------------------------------------------
		virtual void onDraw();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  When deleted
		//----------------------------------------------------------------------------------------------------------------------
		virtual void onDelete();

	protected:
		shared<GameObject> m_parent; ///< the gameobject this is attached to
		ComponentType m_type; ///< the type of component this is
	};
};
