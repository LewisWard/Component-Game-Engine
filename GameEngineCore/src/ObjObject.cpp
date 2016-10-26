// Author  : Lewis Ward (i7212443)
// Program : 3D Renderer
// Date    : 10/10/2016
#include "ObjObject.h"
#include "tiny_obj_loader.h"

gl::ObjObject::ObjObject(const char* objFilename, const char* mtlRootDir)
{

	std::string inputfile = objFilename;
	std::vector<tinyobj::shape> shapes;
	std::vector<tinyobj::material> materials;

	std::string err;
	tinyobj::LoadObj(shapes, materials, err, inputfile.c_str(), mtlRootDir, true);

	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << std::endl <<  err << std::endl;
	}

#ifdef _DEBUG
	#if IMPORT_DEBUG
	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	std::cout << "# of materials : " << materials.size() << std::endl;

	for (size_t i = 0; i < shapes.size(); i++) {
		printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
		printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
		printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
		assert((shapes[i].mesh.indices.size() % 3) == 0);
		for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
			printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, shapes[i].mesh.indices[3 * f + 0], shapes[i].mesh.indices[3 * f + 1], shapes[i].mesh.indices[3 * f + 2], shapes[i].mesh.material_ids[f]);
		}

		printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
		assert((shapes[i].mesh.positions.size() % 3) == 0);
		for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
			printf("  v[%ld] = (%f, %f, %f)\n", v,
				shapes[i].mesh.positions[3 * v + 0],
				shapes[i].mesh.positions[3 * v + 1],
				shapes[i].mesh.positions[3 * v + 2]);
		}
	}

	for (size_t i = 0; i < materials.size(); i++) {
		printf("material[%ld].name = %s\n", i, materials[i].name.c_str());
		printf("  material.Ka = (%f, %f ,%f)\n", materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]);
		printf("  material.Kd = (%f, %f ,%f)\n", materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]);
		printf("  material.Ks = (%f, %f ,%f)\n", materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]);
		printf("  material.Tr = (%f, %f ,%f)\n", materials[i].transmittance[0], materials[i].transmittance[1], materials[i].transmittance[2]);
		printf("  material.Ke = (%f, %f ,%f)\n", materials[i].emission[0], materials[i].emission[1], materials[i].emission[2]);
		printf("  material.Ns = %f\n", materials[i].shininess);
		printf("  material.Ni = %f\n", materials[i].ior);
		printf("  material.dissolve = %f\n", materials[i].dissolve);
		printf("  material.illum = %d\n", materials[i].illum);
		printf("  material.map_Ka = %s\n", materials[i].ambient_texname.c_str());
		printf("  material.map_Kd = %s\n", materials[i].diffuse_texname.c_str());
		printf("  material.map_Ks = %s\n", materials[i].specular_texname.c_str());
		printf("  material.map_Ns = %s\n", materials[i].specular_highlight_texname.c_str());
		std::map<std::string, std::string>::const_iterator it(materials[i].unknown_parameter.begin());
		std::map<std::string, std::string>::const_iterator itEnd(materials[i].unknown_parameter.end());
		for (; it != itEnd; it++) {
			printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
		}
		printf("\n");
	}
	#endif
#endif

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

#ifdef _DEBUG
	#if IMPORT_DEBUG
	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		std::cout << i << " " << m_vertices[i].v.x << " " << m_vertices[i].v.y << " " << m_vertices[i].v.z << " ";
		std::cout << m_vertices[i].n.x << " " << m_vertices[i].n.y << " " << m_vertices[i].n.z << " ";
		std::cout << m_vertices[i].u.x << " " << m_vertices[i].u.y << std::endl;
	}

	for (size_t i = 0; i < m_indices.size(); i++)
		std::cout << m_indices[i] << std::endl;
	#endif
#endif

	m_linkedTexture = 0;

	// create vertex and index buffers
	m_vertexBuffer = new VertexBuffer(m_vertices, m_indices);
}

gl::ObjObject::~ObjObject()
{
	delete m_vertexBuffer;
	m_vertexBuffer = 0;
	m_linkedTexture = 0;
	m_vertices.clear();
	m_indices.clear();
}
