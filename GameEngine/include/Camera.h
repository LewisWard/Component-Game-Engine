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
#include "glm\gtc\matrix_transform.hpp"
#include "ObjObject.h"

namespace GE
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief A camera
	//----------------------------------------------------------------------------------------------------------------------
	class Camera
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief Constructor
		/// prama		glm::vec3 position (eye)
		/// prama		glm::vec3 facing (point to look at/towards)
		/// prama		glm::vec2 screen size
		/// prama		float Field of View
		/// prama		float near plane
		/// prama		float far plane
		//----------------------------------------------------------------------------------------------------------------------
		Camera(glm::vec3 position, glm::vec3 facing, glm::vec2 screen, float FoV, float nearPlane, float farPlane);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Desstructor
		//----------------------------------------------------------------------------------------------------------------------
		~Camera();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get projection matrix
		/// \return glm::mat4 
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::mat4 getProjection() { return m_projection; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get view matrix
		/// \return glm::mat4 
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::mat4 getView() { return m_view; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get camera position (origin)
		/// \return glm::vec3 
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::vec3 getPosition() { return m_position;  }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get camera facing
		/// \return glm::vec3 
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::vec3 getFacing() { return m_facing; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get the screen size
		/// \return glm::vec2
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::vec2 getScreenSize() { return m_screenSize; }

	private:
		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::vec3 m_position;
		glm::vec3 m_up;
		glm::vec3 m_facing;
		glm::vec2 m_screenSize;
	};
};


