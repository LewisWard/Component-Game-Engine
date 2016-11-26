// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 10/10/2016
#pragma once
#include <map>
#include <algorithm>
#include <sstream>
#include "Texture.h"
#include "VertexBuffer.h"

namespace GEC
{
	struct mesh
	{
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> textureUVs;
		std::vector<int> indices;
		std::vector<int> materialID;
	};

	struct model
	{
		std::string name;
		std::string material;
		mesh mesh;
	};

	class ObjParser
	{
	public:
		ObjParser() { }
		~ObjParser() { }

		bool load(const char* filename);

		inline model getModel() { return m_model; }

	private:
		model m_model;
	};
};
