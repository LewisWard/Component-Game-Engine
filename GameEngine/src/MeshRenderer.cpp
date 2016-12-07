// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 07/12/2016
#include "MeshRenderer.h"

namespace GE
{
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
		}
		texture->unbind();
		program->unbind();
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
};
