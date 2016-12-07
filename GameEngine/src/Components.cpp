// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 26/10/2016
#include "Components.h"

namespace GE
{
	Component::Component()
	{

	}

	Component::~Component()
	{
	}

	void Component::onLoad()
	{

	}

	void Component::onUpdate(float dt)
	{

	}

	void Component::onDraw()
	{

	}

	void Component::onDelete()
	{
		m_parent = nullptr;
	}

	Transform::Transform()
	{
		m_type = kTransform;
		m_position = glm::vec3(0.0f);
		m_scale = glm::vec3(1.0f);
		m_rotation = glm::vec3(0.0f);
	}

	Transform::Transform(const Transform & t)
	{
		m_position = t.m_position;
		m_scale = t.m_scale;
		m_rotation = t.m_rotation;
	}

	Transform::~Transform()
	{

	}

	glm::mat4 Transform::createTransform()
	{
		glm::mat4 m;
		m = glm::scale(m, m_scale);
		m = glm::translate(m, m_position);
		m = glm::rotate(m, m_rotation.x, glm::vec3(1, 0, 0));
		m = glm::rotate(m, m_rotation.y, glm::vec3(0, 1, 0));
		m = glm::rotate(m, m_rotation.z, glm::vec3(0, 0, 1));
		m[3][3] = 1.0f;
		return m;
	}

	MeshRenderer::MeshRenderer()
	{
		m_type = kMeshRenderer;
		m_usingVertexBuffer = false;
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::onDraw()
	{
		shared<GE::Program> program(m_shaderProgram);
		shared<GEC::ObjObject> mesh(m_mesh);
		shared<GEC::Texture> texture(m_texture);
		program->bind();
		texture->bind(1);
		program->uniform1i("texture", 1);

		if (!mesh->getVertexBuffer()->isIndexed())
		{
			const float* offset = 0;
			glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer()->getVBO());
			glBindVertexArray(mesh->getVertexBuffer()->getIBO());
			glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexNormalUV), offset);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 3);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 6);
			glEnableVertexAttribArray(2);
			glDrawArrays(GL_TRIANGLES, 0, mesh->getIndicesCount());
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
#if _DEBUG
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
#endif
		}
		else
		{
			const float* offset = 0;
			glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer()->getVBO());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getVertexBuffer()->getIBO());
			glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexNormalUV), offset);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 3);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 6);
			glEnableVertexAttribArray(2);
			glDrawElements(GL_TRIANGLES, (GLsizei)mesh->getIndicesCount(), GL_UNSIGNED_INT, 0);
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
#if _DEBUG
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
		texture->unbind();
		program->unbind();
		}
	}

	void MeshRenderer::Draw()
	{
		shared<GEC::ObjObject> mesh(m_mesh);

		if (!mesh->getVertexBuffer()->isIndexed())
		{
			const float* offset = 0;
			glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer()->getVBO());
			glBindVertexArray(mesh->getVertexBuffer()->getIBO());
			glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexNormalUV), offset);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 3);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 6);
			glEnableVertexAttribArray(2);
			glDrawArrays(GL_TRIANGLES, 0, mesh->getIndicesCount());
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
#if _DEBUG
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
#endif
		}
		else
		{
			const float* offset = 0;
			glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer()->getVBO());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getVertexBuffer()->getIBO());
			glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexNormalUV), offset);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 3);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 6);
			glEnableVertexAttribArray(2);
			glDrawElements(GL_TRIANGLES, (GLsizei)mesh->getIndicesCount(), GL_UNSIGNED_INT, 0);
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
#if _DEBUG
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
		}
	}

	void MeshRenderer::setMVPUniforms(glm::mat4 M)
	{
		shared<GE::Camera> camera(m_mainCamera);
		glm::mat4 V = camera->getView();
		glm::mat4 P = camera->getProjection();
		shared<GE::Program> program(m_shaderProgram);
		program->bind();
		program->uniformMatrix4("modelMatrix", 1, M);
		program->uniformMatrix4("viewMatrix", 1, V);
		program->uniformMatrix4("projectionlMatrix", 1, P);
		program->unbind();
	}

	void MeshRenderer::setColourOnCollision(glm::vec3 colour, bool collision)
	{
		shared<GE::Program> program(m_shaderProgram);
		program->bind();

		if (collision)
			program->uniform3f("collisionColour", colour.x / 255.0f, colour.y / 255.0f, colour.z / 255.0f);
		else
			program->uniform3f("collisionColour", 0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f);

		program->unbind();
	}

	void MeshRenderer::setColourOnSelection(glm::vec3 colour, bool selected)
	{
		shared<GE::Program> program(m_shaderProgram);
		program->bind();

		if (selected)
			program->uniform3f("selectedColour", colour.x / 255.0f, colour.y / 255.0f, colour.z / 255.0f);
		else
			program->uniform3f("selectedColour", 0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f);
		
		program->unbind();
	}

	SphereCollider::SphereCollider()
	{
		m_type = kSphereCollider;

	}

	SphereCollider::SphereCollider(glm::vec3 center, glm::vec3 radius)
	{
		m_type = kSphereCollider;

	}

	SphereCollider::~SphereCollider() {}

	void SphereCollider::boundToObject(shared<GEC::ObjObject> obj)
	{
		glm::vec2 X, Y, Z;
		obj->getVertexRange(X, Y, Z);
		m_center = glm::vec3(X.x - X.y, Y.x - Y.y, Z.x - Z.y);
		m_radius = m_center.x - X.x;
	}

	bool SphereCollider::collision(SphereCollider& other)
	{
		// compute the distance between the two spheres
		glm::vec3 distanceDelta(m_center - other.getCenter());
		float distance = glm::sqrt((distanceDelta.x * distanceDelta.x) + (distanceDelta.y * distanceDelta.y) + (distanceDelta.z * distanceDelta.z));

		float radii = m_radius + other.getRadius();

		if (distance < radii)
			return true;

		return false;
	}

	
	BoxCollider::BoxCollider()
	{
		m_type = kBoxCollider;
		m_boundingBox = GEC::AABB(glm::vec3(0.0f), glm::vec3(1.0f));
		makeVertexBuffer();
		std::string assetPath(ENGINEASSETS);
		GE::Shader vertexShader(std::string(assetPath + "shaders/collisionWireframe.vrt").c_str(), kVertexShader);
		GE::Shader pixelShader(std::string(assetPath + "shaders/collisionWireframe.pix").c_str(), kPixelShader);
		m_shaderProgram = mkShare<GE::Program>(vertexShader, pixelShader);
	}

	BoxCollider::BoxCollider(glm::vec3 center, glm::vec3 size)
	{
		m_type = kBoxCollider;
		m_boundingBox = GEC::AABB(center, size);
		makeVertexBuffer();
		std::string assetPath(ENGINEASSETS);
		GE::Shader vertexShader(std::string(assetPath + "shaders/collisionWireframe.vrt").c_str(), kVertexShader);
		GE::Shader pixelShader(std::string(assetPath + "shaders/collisionWireframe.pix").c_str(), kPixelShader);
		m_shaderProgram = mkShare<GE::Program>(vertexShader, pixelShader);
	}
	
	BoxCollider::~BoxCollider()
	{
	}

	void BoxCollider::onDraw()
	{
		m_shaderProgram->bind();
		m_shaderProgram->uniform3f("wireframeColour", 128.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f);
		const float* offset = 0;
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer->getVBO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexBuffer->getIBO());
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexNormalUV), offset);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 3);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 6);
		glEnableVertexAttribArray(2);
		glDrawElements(GL_LINES, (GLsizei)m_indexCount, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		m_shaderProgram->unbind();
	}

	void BoxCollider::boundToObject(shared<GEC::ObjObject> obj)
	{
		glm::vec2 X, Y, Z;
		obj->getVertexRange(X, Y, Z);
		m_boundingBox = GEC::AABB(glm::vec3(0.0f), glm::vec3((X.y - X.x), (Y.y - Y.x), (Z.y - Z.x)));
		makeVertexBuffer();
	}

	bool BoxCollider::collision(BoxCollider other)
	{
		return m_boundingBox.intersects(other.m_boundingBox);
	}

	bool BoxCollider::collision(GE::SphereCollider sphere)
	{
		glm::vec3 sphereCenter(sphere.getCenter());
		float x = glm::max(m_boundingBox.min.x, glm::min(sphereCenter.x, m_boundingBox.max.x));
		float y = glm::max(m_boundingBox.min.y, glm::min(sphereCenter.y, m_boundingBox.max.y));
		float z = glm::max(m_boundingBox.min.z, glm::min(sphereCenter.z, m_boundingBox.max.z));

		float distance = glm::sqrt((x - sphereCenter.x) * (x - sphereCenter.x) +
			(y - sphereCenter.y) * (y - sphereCenter.y) +
			(z - sphereCenter.z) * (z - sphereCenter.z));

		return distance < sphere.getRadius();
	}

	void BoxCollider::setMVPUniforms(glm::mat4 M, glm::mat4 V, glm::mat4 P)
	{
		shared<GE::Program> program(m_shaderProgram);
		program->bind();
		program->uniformMatrix4("modelMatrix", 1, M);
		program->uniformMatrix4("viewMatrix", 1, V);
		program->uniformMatrix4("projectionlMatrix", 1, P);
		program->unbind();
	}

	void BoxCollider::recomputeBounds(glm::vec3& newPosition)
	{
		m_boundingBox = GEC::AABB(newPosition, m_boundingBox.size);
	}

	void BoxCollider::makeVertexBuffer()
	{
		std::vector<vertexNormalUV> vertices;
		std::vector<int> indices;

		vertexNormalUV tmp;
		tmp.n = glm::vec3(1.0f);
		tmp.u = glm::vec2(0.0f);
		tmp.v = m_boundingBox.max;
		vertices.push_back(tmp);
		tmp.v = m_boundingBox.max;
		tmp.v.y -= m_boundingBox.size.y;
		vertices.push_back(tmp);
		tmp.v = m_boundingBox.max;
		tmp.v.x -= m_boundingBox.size.x;
		tmp.v.y -= m_boundingBox.size.y;
		vertices.push_back(tmp);
		tmp.v = m_boundingBox.max;
		tmp.v.x -= m_boundingBox.size.x;
		vertices.push_back(tmp);

		tmp.v = m_boundingBox.min;
		vertices.push_back(tmp);
		tmp.v = m_boundingBox.min;
		tmp.v.y += m_boundingBox.size.y;
		vertices.push_back(tmp);
		tmp.v = m_boundingBox.min;
		tmp.v.x += m_boundingBox.size.x;
		tmp.v.y += m_boundingBox.size.y;
		vertices.push_back(tmp);
		tmp.v = m_boundingBox.min;
		tmp.v.x += m_boundingBox.size.x;
		vertices.push_back(tmp);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(3);
		indices.push_back(0);

		indices.push_back(2);
		indices.push_back(4);
		indices.push_back(4);
		indices.push_back(5);
		indices.push_back(5);
		indices.push_back(3);

		indices.push_back(4);
		indices.push_back(7);
		indices.push_back(7);
		indices.push_back(6);
		indices.push_back(6);
		indices.push_back(5);

		indices.push_back(7);
		indices.push_back(1);
		indices.push_back(6);
		indices.push_back(0);

		m_indexCount = indices.size();
		m_vertexBuffer = mkShare<GEC::VertexBuffer>(vertices, indices);
	}
};
