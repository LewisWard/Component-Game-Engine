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
#include "Texture.h"
#include "ObjParser.h"
#include <algorithm>

namespace GEC
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  loads a obj file
	//----------------------------------------------------------------------------------------------------------------------
	class ObjObject
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		/// prama		char* filename
		//----------------------------------------------------------------------------------------------------------------------
		ObjObject(const char* objFilename);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Destructor 
		//----------------------------------------------------------------------------------------------------------------------
		~ObjObject();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  gets the model matrix
		/// \return	math::Mat4 
		//----------------------------------------------------------------------------------------------------------------------
		inline glm::mat4 getMatrix() { return m_modelMatrix; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  sets the model matrix
		/// prama	math::Mat4 
		//----------------------------------------------------------------------------------------------------------------------
		inline void setMatrix(glm::mat4& matrix) { m_modelMatrix = matrix; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  gets the Vertex Buffer
		/// \return	gl::VertexBuffer*
		//----------------------------------------------------------------------------------------------------------------------
		inline shared<VertexBuffer> getVertexBuffer() { return m_vertexBuffer; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  gets the number of indices the object has
		/// \return	int
		//----------------------------------------------------------------------------------------------------------------------
		inline size_t getIndicesCount() { return m_indices.size(); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  gets the texture
		/// \return gl::Texture*
		//----------------------------------------------------------------------------------------------------------------------
		inline shared<Texture>getLinkedTexture() { return m_linkedTexture; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  sets the texture
		/// prama  gl::Texture*
		//----------------------------------------------------------------------------------------------------------------------
		inline void setLinkedTexture(shared<Texture> texture) { m_linkedTexture = texture; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  sets the position of the vertices that are the greatest distance away from the center of the model
		/// prama  glm::vec2 X axis
		/// prama  glm::vec2 Y axis
		/// prama  glm::vec2 Z axis
		//----------------------------------------------------------------------------------------------------------------------
		void getVertexRange(glm::vec2& X, glm::vec2& Y, glm::vec2& Z);


	private:
		std::vector<vertexNormalUV> m_vertices; ///< store the vertices
		std::vector<int> m_indices; ///< store the indices
		glm::mat4 m_modelMatrix; ///< model matrix
		shared<VertexBuffer> m_vertexBuffer; ///< Vertex Buffer (VBO/IBO)
		shared<Texture> m_linkedTexture; ///< points to the texture that should be bound
		const char* m_objectName; ///< objects name

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief finds the two vertices on the X axis at that are the greatest distance any from the origin (local space)
		/// prama  vertexNormalUV a
		/// prama  vertexNormalUV b
		/// \return  bool
		//----------------------------------------------------------------------------------------------------------------------
		static bool vertexCompareX(vertexNormalUV a, vertexNormalUV b) { return (a.v.x < b.v.x); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief finds the two vertices on the Y axis at that are the greatest distance any from the origin (local space)
		/// prama  vertexNormalUV a
		/// prama  vertexNormalUV b
		/// \return  bool
		//----------------------------------------------------------------------------------------------------------------------
		static bool vertexCompareY(vertexNormalUV a, vertexNormalUV b) { return (a.v.y < b.v.y); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief finds the two vertices on the Z axis at that are the greatest distance any from the origin (local space)
		/// prama  vertexNormalUV a
		/// prama  vertexNormalUV b
		/// \return  bool
		//----------------------------------------------------------------------------------------------------------------------
		static bool vertexCompareZ(vertexNormalUV a, vertexNormalUV b) { return (a.v.z < b.v.z); }
	};
}; ///< end of namespace

