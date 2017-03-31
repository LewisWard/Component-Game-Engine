// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 31/03/2016
#pragma once
#include "Components.h"

namespace GE
{
	class Light : public Component
	{
	public:
		Light();

		~Light();


		inline void setPosition(glm::vec3 position) { m_position = position; }

		inline void setColour(glm::vec3 colour) { m_colour = colour; }

		inline void setIntensity(float intensity) { m_intensity = intensity; }

		inline glm::vec3 getPosition() { return m_position; }
								
		inline glm::vec3 getColour() { return m_colour; }
								
		inline float getIntensity() { return m_intensity; }

	private:
		glm::vec3 m_position;
		glm::vec3 m_colour;
		float m_intensity;
	};
}
