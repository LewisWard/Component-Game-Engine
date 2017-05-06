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
