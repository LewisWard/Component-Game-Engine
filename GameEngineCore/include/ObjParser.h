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
#include <map>
#include <algorithm>
#include <sstream>
#include "Texture.h"
#include "VertexBuffer.h"

namespace GEC
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief what a mesh contains
	//----------------------------------------------------------------------------------------------------------------------
	struct mesh
	{
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> textureUVs;
		std::vector<int> indices;
		std::vector<int> materialID;
	};

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief a model
	//----------------------------------------------------------------------------------------------------------------------
	struct model
	{
		std::string name;
		std::string material;
		mesh mesh;
	};

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Reads and extracts .obj data and store it in a model structure
	//----------------------------------------------------------------------------------------------------------------------
	class ObjParser
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		ObjParser();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Destructor
		//----------------------------------------------------------------------------------------------------------------------
		~ObjParser();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  loads a .obj file
		/// prama	char* filename
		//----------------------------------------------------------------------------------------------------------------------
		bool load(const char* filename);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  gets the model data
		/// \return GEC::model
		//----------------------------------------------------------------------------------------------------------------------
		inline model getModel() { return m_model; }

	private:
		model m_model; ///< the model data
	};
};
