/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#include "BoxCollider.h"

namespace GE
{
	BoxCollider::BoxCollider()
	{
		m_type = kBoxCollider;
		m_axisAligned = true;
		m_boundingBox = GEC::AABB(glm::vec3(0.0f), glm::vec3(1.0f));
		makeVertexBuffer();
		std::string assetPath(ENGINEASSETS);
		GE::Shader vertexShader(std::string(assetPath + "shaders/collisionWireframe.vrt").c_str(), kVertexShader);
		GE::Shader pixelShader(std::string(assetPath + "shaders/collisionWireframe.pix").c_str(), kPixelShader);
		m_shaderProgram = mkShare<GE::Program>(vertexShader, pixelShader);
		m_enableDraw = false;
		m_scale = glm::vec3(1.0f);
	}

	BoxCollider::BoxCollider(glm::vec3 center, glm::vec3 size)
	{
		m_type = kBoxCollider;
		m_axisAligned = true;
		m_boundingBox = GEC::AABB(center, size);
		makeVertexBuffer();
		std::string assetPath(ENGINEASSETS);
		GE::Shader vertexShader(std::string(assetPath + "shaders/collisionWireframe.vrt").c_str(), kVertexShader);
		GE::Shader pixelShader(std::string(assetPath + "shaders/collisionWireframe.pix").c_str(), kPixelShader);
		m_shaderProgram = mkShare<GE::Program>(vertexShader, pixelShader);
		m_enableDraw = false;
		m_scale = glm::vec3(1.0f);
	}

	BoxCollider::~BoxCollider()
	{
	}

	void BoxCollider::onDraw()
	{
		if (m_enableDraw)
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
	}

	void BoxCollider::boundToObject(shared<GEC::ObjObject> obj)
	{
		if (m_axisAligned)
		{
			glm::vec2 X, Y, Z;
			obj->getVertexRange(X, Y, Z);
			m_boundingBox = GEC::AABB(glm::vec3(0.0f), glm::vec3((X.y - X.x) * m_scale.x, (Y.y - Y.x) * m_scale.y, (Z.y - Z.x) * m_scale.z));
			makeVertexBuffer();
		}
		else
		{
			glm::vec2 X, Y, Z;
			obj->getVertexRange(X, Y, Z);
			m_objectBoundedBox = GEC::OBB(glm::vec3(0.0f), glm::vec3((X.y - X.x) * m_scale.x, (Y.y - Y.x) * m_scale.y, (Z.y - Z.x) * m_scale.z));
			makeVertexBuffer();
		}
	}

	bool BoxCollider::collision(BoxCollider other)
	{
		if(m_axisAligned)
			return m_boundingBox.intersects(other.m_boundingBox);
		else
			return m_objectBoundedBox.intersects(other.m_boundingBox);
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

	void BoxCollider::recomputeBounds(const glm::vec3& newPosition)
	{
		if (m_axisAligned)
			m_boundingBox = GEC::AABB(newPosition, m_boundingBox.size);
		else
			m_objectBoundedBox = GEC::OBB(newPosition, m_objectBoundedBox.size);
	}

	void BoxCollider::makeVertexBuffer()
	{
		std::vector<vertexNormalUV> vertices;
		std::vector<int> indices;
		vertexNormalUV tmp;
		tmp.n = glm::vec3(1.0f);
		tmp.u = glm::vec2(0.0f);

		if (m_axisAligned)
		{
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
		}
		else
		{
			tmp.v = m_objectBoundedBox.m_objectBounds[0];
			vertices.push_back(tmp);
			tmp.v = m_objectBoundedBox.m_objectBounds[1];
			vertices.push_back(tmp);
			tmp.v = m_objectBoundedBox.m_objectBounds[3];
			vertices.push_back(tmp);
			tmp.v = m_objectBoundedBox.m_objectBounds[2];
			vertices.push_back(tmp);

			tmp.v = m_objectBoundedBox.m_objectBounds[4];
			vertices.push_back(tmp);
			tmp.v = m_objectBoundedBox.m_objectBounds[5];
			vertices.push_back(tmp);
			tmp.v = m_objectBoundedBox.m_objectBounds[7];
			vertices.push_back(tmp);
			tmp.v = m_objectBoundedBox.m_objectBounds[6];
			vertices.push_back(tmp);

			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(1);
			indices.push_back(2);
			indices.push_back(2);
			indices.push_back(3);
			indices.push_back(3);
			indices.push_back(0);

			indices.push_back(4);
			indices.push_back(5);
			indices.push_back(5);
			indices.push_back(6);
			indices.push_back(6);
			indices.push_back(7);
			indices.push_back(7);
			indices.push_back(4);

			indices.push_back(0);
			indices.push_back(4);
			indices.push_back(7);
			indices.push_back(3);
			indices.push_back(1);
			indices.push_back(5);
			indices.push_back(2);
			indices.push_back(6);
		}

		m_indexCount = (int)indices.size();
		m_vertexBuffer = mkShare<GEC::VertexBuffer>(vertices, indices);
	}
};
