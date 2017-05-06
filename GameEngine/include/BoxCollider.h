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
#include "SphereCollider.h"
#include "OBB.h"

namespace GE
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Box (AABB) collision detection
	//----------------------------------------------------------------------------------------------------------------------
	class BoxCollider : public Component
	{
		friend class AABB;
	public:

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		BoxCollider();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		/// prama glm::vec3 center
		/// prama glm::vec3 radius
		//----------------------------------------------------------------------------------------------------------------------
		BoxCollider(glm::vec3 center, glm::vec3 size);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Destructor
		//----------------------------------------------------------------------------------------------------------------------
		~BoxCollider();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  draw the AABB around the attached object - useful for testing
		//----------------------------------------------------------------------------------------------------------------------
		void onDraw();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  create the boundary based on the object
		/// prama shared<GEC::ObjObject>
		//----------------------------------------------------------------------------------------------------------------------
		void boundToObject(shared<GEC::ObjObject> obj);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set min
		/// prama glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		void setMin(glm::vec3 min) { m_boundingBox.min = min; m_boundingBox.center = ((m_boundingBox.max - m_boundingBox.min) / 2.0f) + m_boundingBox.min; };

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set max
		/// prama glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		void setMax(glm::vec3 max) { m_boundingBox.max = max; m_boundingBox.center = ((m_boundingBox.max - m_boundingBox.min) / 2.0f) + m_boundingBox.min; };

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get min
		/// prama glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::vec3 getMin() { return m_boundingBox.min; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief get max
		/// prama glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::vec3 getMax() { return m_boundingBox.max; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief get center
		/// prama glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::vec3 getCenter() { return m_boundingBox.center; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  check if a collision has occurred between another GE::BoxCollider
		/// prama GE::BoxCollider
		//----------------------------------------------------------------------------------------------------------------------
		bool collision(BoxCollider other);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  check if a collision has occurred between a GE::SphereCollider
		/// prama GE::SphereCollider
		//----------------------------------------------------------------------------------------------------------------------
		bool collision(GE::SphereCollider sphere);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set radius
		/// prama float
		//----------------------------------------------------------------------------------------------------------------------
		inline void setScreenRes(glm::vec2 screen) { m_screenRes = screen; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set radius
		/// prama float
		//----------------------------------------------------------------------------------------------------------------------
		void setMVPUniforms(glm::mat4 M, glm::mat4 V, glm::mat4 P);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  recompute bounds after AABB has been moved
		/// prama glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		void recomputeBounds(const glm::vec3& newPosition);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  recompute bounds after AABB has been moved
		/// prama glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		void recomputeBounds(const glm::vec3& newPosition, const glm::vec3& newRotation)
		{
			if (!m_axisAligned)
			{
				glm::vec2 X, Y, Z;
				m_objectBoundedBox.rotate(newRotation);
				vertexRange(X, Y, Z);
				m_objectBoundedBox.size = glm::vec3((X.y - X.x), (Y.y - Y.x), (Z.y - Z.x));
				m_objectBoundedBox.extents = m_objectBoundedBox.size / 2.0f;
				makeVertexBuffer();
			}
		}

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief debug draw on or off
		/// prama bool
		//----------------------------------------------------------------------------------------------------------------------
		inline void toggleDraw(bool draw) { m_enableDraw = draw; }

		inline void setScale(glm::vec3 scale) { m_scale = scale; }

		inline glm::vec3 getScale() { return m_scale; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief AABB or OBB. If setting to OBB will generate from existing AABB
		/// prama bool, true for AABB and false for OBB
		//----------------------------------------------------------------------------------------------------------------------
		void toggleAxisAligned(bool aligned) 
		{
			m_axisAligned = aligned; 
			if (!m_axisAligned)
				toOBB();
		}


		void toOBB()
		{
			m_axisAligned = false;
			m_objectBoundedBox = GEC::OBB(m_boundingBox.center, m_boundingBox.size);
		}

	public:
		GEC::OBB m_objectBoundedBox;
		GEC::AABB m_boundingBox;
		glm::vec2 m_screenRes;

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  makes a vertex buffer for the AABB
		//----------------------------------------------------------------------------------------------------------------------
		void makeVertexBuffer();

		shared<GEC::VertexBuffer> m_vertexBuffer;
		shared<GE::Program> m_shaderProgram;
		glm::vec3 m_scale;
		int m_indexCount;
		bool m_enableDraw;
		bool m_axisAligned;


		void vertexRange(glm::vec2& X, glm::vec2& Y, glm::vec2& Z)
		{
			std::vector<glm::vec3> points;
			for (int i = 0; i < 8; i++)
				points.push_back(m_objectBoundedBox.m_objectBounds[i]);

			std::vector<glm::vec3>::iterator result, resultmax;
			result = std::min_element(points.begin(), points.end(), vec3CompareX);
			resultmax = std::max_element(points.begin(), points.end(), vec3CompareX);
			X.x = result->x;
			X.y = resultmax->x;

			result = std::min_element(points.begin(), points.end(), vec3CompareY);
			resultmax = std::max_element(points.begin(), points.end(), vec3CompareY);
			Y.x = result->y;
			Y.y = resultmax->y;

			result = std::min_element(points.begin(), points.end(), vec3CompareZ);
			resultmax = std::max_element(points.begin(), points.end(), vec3CompareZ);
			Z.x = result->z;
			Z.y = resultmax->z;

		}

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief finds the two vertices on the X axis at that are the greatest distance any from the origin (local space)
		/// prama  glm::vec3 a
		/// prama  glm::vec3 b
		/// \return  bool
		//----------------------------------------------------------------------------------------------------------------------
		static bool vec3CompareX(glm::vec3 a, glm::vec3 b) { return (a.x < b.x); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief finds the two vertices on the Y axis at that are the greatest distance any from the origin (local space)
		/// prama  glm::vec3 a
		/// prama  glm::vec3 b
		/// \return  bool
		//----------------------------------------------------------------------------------------------------------------------
		static bool vec3CompareY(glm::vec3 a, glm::vec3 b) { return (a.y < b.y); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief finds the two vertices on the Z axis at that are the greatest distance any from the origin (local space)
		/// prama  glm::vec3 a
		/// prama  glm::vec3 b
		/// \return  bool
		//----------------------------------------------------------------------------------------------------------------------
		static bool vec3CompareZ(glm::vec3 a, glm::vec3 b) { return (a.z < b.z); }
	};
};



