// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 10/10/2016
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
	m_vertexBuffer = new VertexBuffer(m_vertices);

}

GEC::ObjObject::~ObjObject()
{
	delete m_vertexBuffer;
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
