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

	/*
	BoxCollider::BoxCollider()
	{
		m_type = kBoxCollider;
		makeVertexBuffer();
	}

	BoxCollider::BoxCollider(glm::vec3 min, glm::vec3 max)
	{
		m_type = kBoxCollider;
		m_boundingBox = GEC::AABB(min, max);
		makeVertexBuffer();
	}
	*/
	BoxCollider::~BoxCollider()
	{
	}
};
