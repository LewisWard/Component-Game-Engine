// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 06/12/2016
#pragma once
#include "glm\gtc\matrix_transform.hpp"
#include "ObjObject.h"

namespace GE
{
	class Camera
	{
	public:
		Camera(glm::vec3 position, glm::vec3 facing, glm::vec2 screen, float FoV, float nearPlane, float farPlane);

		~Camera();

		inline glm::mat4 getProjection() { return m_projection; }

		inline glm::mat4 getView() { return m_view; }

		inline glm::vec3 getPosition() { return m_position;  }

		inline glm::vec3 getFacing() { return m_facing; }

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


