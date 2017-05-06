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
#include <vector>

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Vertex with just position and normal
//----------------------------------------------------------------------------------------------------------------------
struct vertexNormal
{
	glm::vec3 v; ///< Vertex
	glm::vec3 n; ///< Normal
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Vertex with just position and UV
//----------------------------------------------------------------------------------------------------------------------
struct vertexUV
{
	glm::vec3 v; ///< Vertex
	glm::vec2 u; ///< Texture coordinates (UV)
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Vertex with just position, normal and UV
//----------------------------------------------------------------------------------------------------------------------
struct vertexNormalUV
{
	glm::vec3 v; ///< Vertex
	glm::vec3 n; ///< Normal
	glm::vec2 u; ///< Texture coordinates (UV)
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Vertex with position, normal, bi-normal, tagent and UV
//----------------------------------------------------------------------------------------------------------------------
struct vertex
{
	glm::vec3 v; ///< Vertex
	glm::vec3 n; ///< Normal
	glm::vec3 b; ///< Bi-Normal
	glm::vec3 t; ///< Tangent
	glm::vec2 u; ///< Texture coordinates (UV)
};

namespace GEC
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  Vertex Buffer - Vertex/Normal/UV
	//----------------------------------------------------------------------------------------------------------------------
	class VertexBuffer
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		/// prama	std::vector vertexNormalUV vertices
		/// prama	std::vector int indices
		//----------------------------------------------------------------------------------------------------------------------
		VertexBuffer(const std::vector<vertexNormalUV>& vertices, const std::vector<int>& indices);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		/// prama	std::vector vertexNormalUV vertices
		//----------------------------------------------------------------------------------------------------------------------
		VertexBuffer(const std::vector<vertexNormalUV>& vertices);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Destructor
		//----------------------------------------------------------------------------------------------------------------------
		~VertexBuffer();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get the VBO id
		/// \return uint32_t 
		//----------------------------------------------------------------------------------------------------------------------
		inline uint32_t getVBO() { return m_vbo; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get the IBO id
		/// \return uint32_t 
		//----------------------------------------------------------------------------------------------------------------------
		inline uint32_t getIBO() { return m_ibo; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  gets if the data is being index
		/// \return bool true if it is 
		//----------------------------------------------------------------------------------------------------------------------
		inline bool isIndexed() { return m_usingIndexed; }

	private:
		uint32_t m_vbo; ///< Vertex Buffer Object
		uint32_t m_ibo; ///< Index Buffer Object
		bool m_usingIndexed; ///< is GL_ELEMENT_ARRAY_BUFFER/glDrawElements to be used or not, true if so.
	};
}; ///< end of namespace
