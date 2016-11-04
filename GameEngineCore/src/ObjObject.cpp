// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 10/10/2016
#include "ObjObject.h"
#include "tiny_obj_loader.h"

GEC::ObjObject::ObjObject(const char* objFilename, const char* mtlRootDir)
{

	std::string inputfile = objFilename;
	std::vector<tinyobj::shape> shapes;
	std::vector<tinyobj::material> materials;

	std::string err;
	tinyobj::LoadObj(shapes, materials, err, inputfile.c_str(), mtlRootDir, true);

	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << std::endl <<  err << std::endl;
	}

	// store the first objects name
	m_objectName = shapes[0].name.c_str();

	// need to extract from the tiny_obj_loader formats to this Engines own formats
	m_indices.resize(shapes[0].mesh.indices.size());
	m_vertices.resize(shapes[0].mesh.positions.size() / 3);


	for (size_t i = 0; i < m_indices.size(); ++i)
		m_indices[i] = shapes[0].mesh.indices[i];

	size_t x = 0;
	for (size_t i = 0; i < shapes[0].mesh.positions.size(); i+=3)
	{
		m_vertices[x].v.x = shapes[0].mesh.positions[i];
		m_vertices[x].v.y = shapes[0].mesh.positions[i + 1];
		m_vertices[x].v.z = shapes[0].mesh.positions[i + 2];
		m_vertices[x].n.x = shapes[0].mesh.normals[i];
		m_vertices[x].n.y = shapes[0].mesh.normals[i + 1];
		m_vertices[x].n.z = shapes[0].mesh.normals[i + 2];
		x++;
	}
	
	x = 0;
	for (size_t i = 0; i < shapes[0].mesh.texcoords.size(); i += 2)
	{
		m_vertices[x].u.x = shapes[0].mesh.texcoords[i];
		m_vertices[x].u.y = shapes[0].mesh.texcoords[i + 1];
		x++;
	}

	m_linkedTexture = 0;

	// create vertex and index buffers
	m_vertexBuffer = new VertexBuffer(m_vertices, m_indices);
}

GEC::ObjObject::~ObjObject()
{
	delete m_vertexBuffer;
	m_vertexBuffer = 0;
	m_linkedTexture = 0;
	m_vertices.clear();
	m_indices.clear();
}
