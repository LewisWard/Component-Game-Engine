/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#include "ObjObject.h"

GEC::ObjObject::ObjObject(const char* objFilename)
{
	ObjParser object;
	object.load(objFilename);

	model objModel = object.getModel();

	m_vertices.resize(objModel.mesh.positions.size());
	m_indices.resize(objModel.mesh.indices.size());

	for (size_t i = 0; i < m_indices.size(); ++i)
		m_indices[i] = objModel.mesh.indices[i];

	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		m_vertices[i].v = objModel.mesh.positions[i];
		m_vertices[i].n = objModel.mesh.normals[i];
	}

	for (size_t i = 0; i < objModel.mesh.textureUVs.size(); i++)
	{
		m_vertices[i].u = objModel.mesh.textureUVs[i];
	}

	m_linkedTexture = 0;

	// create vertex and index buffers
	m_vertexBuffer = mkShare<GEC::VertexBuffer>(m_vertices);
}

GEC::ObjObject::~ObjObject()
{
	m_vertexBuffer = 0;
	m_linkedTexture = 0;
	m_vertices.clear();
	m_indices.clear();
}

void GEC::ObjObject::getVertexRange(glm::vec2& X, glm::vec2& Y, glm::vec2& Z)
{
	std::vector<vertexNormalUV>::iterator result, resultmax;
	result = std::min_element(m_vertices.begin(), m_vertices.end(), vertexCompareX);
	resultmax = std::max_element(m_vertices.begin(), m_vertices.end(), vertexCompareX);
	X.x = result->v.x;
	X.y = resultmax->v.x;

	result = std::min_element(m_vertices.begin(), m_vertices.end(), vertexCompareY);
	resultmax = std::max_element(m_vertices.begin(), m_vertices.end(), vertexCompareY);
	Y.x = result->v.y;
	Y.y = resultmax->v.y;

	result = std::min_element(m_vertices.begin(), m_vertices.end(), vertexCompareZ);
	resultmax = std::max_element(m_vertices.begin(), m_vertices.end(), vertexCompareZ);
	Z.x = result->v.z;
	Z.y = resultmax->v.z;
}
