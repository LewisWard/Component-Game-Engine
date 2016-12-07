// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 10/10/2016
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
		/// \parma	char* filename
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
		/// \parma	math::Mat4 
		//----------------------------------------------------------------------------------------------------------------------
		inline void setMatrix(glm::mat4& matrix) { m_modelMatrix = matrix; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  gets the Vertex Buffer
		/// \return	gl::VertexBuffer*
		//----------------------------------------------------------------------------------------------------------------------
		inline VertexBuffer* getVertexBuffer() { return m_vertexBuffer; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  gets the number of indices the object has
		/// \return	int
		//----------------------------------------------------------------------------------------------------------------------
		inline size_t getIndicesCount() { return m_indices.size(); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  gets the texture
		/// \return gl::Texture*
		//----------------------------------------------------------------------------------------------------------------------
		inline Texture* getLinkedTexture() { return m_linkedTexture; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  sets the texture
		/// \parma  gl::Texture*
		//----------------------------------------------------------------------------------------------------------------------
		inline void setLinkedTexture(Texture* texture) { m_linkedTexture = texture; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  sets the position of the vertices that are the greatest distance away from the center of the model
		/// \parma  glm::vec2 X axis
		/// \parma  glm::vec2 Y axis
		/// \parma  glm::vec2 Z axis
		//----------------------------------------------------------------------------------------------------------------------
		void getVertexRange(glm::vec2& X, glm::vec2& Y, glm::vec2& Z);


	private:
		const char* m_objectName; ///< objects name
		std::vector<vertexNormalUV> m_vertices; ///< store the vertices
		std::vector<int> m_indices; ///< store the indices
		glm::mat4 m_modelMatrix; ///< model matrix
		VertexBuffer* m_vertexBuffer; ///< Vertex Buffer (VBO/IBO)
		Texture* m_linkedTexture; ///< points to the texture that should be bound

		static bool vertexCompareX(vertexNormalUV a, vertexNormalUV b) { return (a.v.x < b.v.x); }

		static bool vertexCompareY(vertexNormalUV a, vertexNormalUV b) { return (a.v.y < b.v.y); }

		static bool vertexCompareZ(vertexNormalUV a, vertexNormalUV b) { return (a.v.z < b.v.z); }
	};
}; ///< end of namespace

