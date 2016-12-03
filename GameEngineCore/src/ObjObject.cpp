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
