// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 10/10/2016
#include "ObjParser.h"

namespace GEC
{
	// based upon: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/ [accessed 21/11/2016]
	bool ObjParser::load(const char* filename)
	{
		FILE* file = fopen(filename, "r");
		if (file == NULL) 
		{
			std::cout << "Cannot open: " << filename << std::endl;
			return false;
		}

		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec3> temp_normals;
		std::vector<glm::vec2> temp_uvs;
		std::vector<uint32_t> vertices;
		std::vector<uint32_t> uvs;
		std::vector<uint32_t> normals;
		std::vector<int> indices;

		while (1) 
		{
			char line[128];

			// read in a line at a time until the end of file
			int res = fscanf(file, "%s", line);
			if (res == EOF)
				break; 

			// read in vertex data
			if (strcmp(line, "v") == 0)
			{
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(line, "vt") == 0)  // read in vertex texture (uv) data
			{
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(line, "vn") == 0)  // read in vertex normal data
			{
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(line, "f") == 0) // read in face (index) data
			{
				uint32_t vertexIndices[3], uvIndices[3], normalIndices[3];

				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndices[0], &uvIndices[0], &normalIndices[0], &vertexIndices[1], &uvIndices[1], &normalIndices[1], &vertexIndices[2], &uvIndices[2], &normalIndices[2]);
				if (matches != 9) 
				{
					std::cout << "Cannot read data in " << filename << ". Make sure normals and uv's are exported and faces are triangulated!\n";
					return false;
				}

				vertices.push_back(vertexIndices[0]);
				vertices.push_back(vertexIndices[1]);
				vertices.push_back(vertexIndices[2]);
				uvs.push_back(uvIndices[0]);
				uvs.push_back(uvIndices[1]);
				uvs.push_back(uvIndices[2]);
				normals.push_back(normalIndices[0]);
				normals.push_back(normalIndices[1]);
				normals.push_back(normalIndices[2]);

				indices.push_back(vertexIndices[0] - 1);
				indices.push_back(vertexIndices[1] - 1);
				indices.push_back(vertexIndices[2] - 1);

			}
			else if (strcmp(line, "o") == 0) // read in the object name
			{
				char name[128];
				fscanf(file, "%s", name);
				m_model.name = name;
			}
		}

		// copy data into model
		for (uint32_t i = 0; i < vertices.size(); i++)
			m_model.mesh.positions.push_back(temp_vertices[vertices[i] - 1]);

		for (uint32_t i = 0; i < normals.size(); i++)
			m_model.mesh.normals.push_back(temp_normals[normals[i] - 1]);

		for (uint32_t i = 0; i < uvs.size(); i++)
			m_model.mesh.textureUVs.push_back(temp_uvs[uvs[i] - 1]);

		m_model.mesh.indices = indices;

		return true;
	}
};
