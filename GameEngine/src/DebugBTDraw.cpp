/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#pragma once
#include "DebugBTDraw.h"

namespace GE
{
	DebugBTDraw::DebugBTDraw() : m_debugMode(0)
	{
		std::string assetPath(ENGINEASSETS);
		GE::Shader vertexShader(std::string(assetPath + "shaders/collisionWireframe.vrt").c_str(), kVertexShader);
		GE::Shader pixelShader(std::string(assetPath + "shaders/collisionWireframe.pix").c_str(), kPixelShader);
		m_shaderProgram = mkShare<GE::Program>(vertexShader, pixelShader);
	}

	DebugBTDraw::~DebugBTDraw()
	{
	}

	void DebugBTDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
	{
		std::cout << "Implement drawLine\n";
	}

	void DebugBTDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		//drawLine(from, to, color, color);
		std::vector<vertexNormalUV> vertices;
		std::vector<int> indices;

		vertexNormalUV tmp;
		tmp.n = glm::vec3(1.0f);
		tmp.u = glm::vec2(0.0f);
		tmp.v = glm::vec3(from.getX(), from.getY(), from.getZ());
		vertices.push_back(tmp);
		tmp.v = glm::vec3(to.getX(), to.getY(), to.getZ());
		vertices.push_back(tmp);

		indices.push_back(0);
		indices.push_back(1);

		makeVertexBuffer(vertices, indices);
		draw();
	}

	void DebugBTDraw::drawSphere(const btVector3& p, btScalar radius, const btVector3& color)
	{
		std::cout << "Implement drawSphere\n";
	}

	void DebugBTDraw::drawBox(const btVector3& bbMin, const btVector3& bbMax, const btVector3& color)
	{
		glm::vec3 center(glm::vec3(bbMax.getX(), bbMax.getY(), bbMax.getZ()) - glm::abs(glm::vec3(bbMin.getX(), bbMin.getY(), bbMin.getZ())));
		center /= 2;
		glm::vec3 size(glm::vec3(bbMax.getX(), bbMax.getY(), bbMax.getZ()) - glm::vec3(bbMin.getX(), bbMin.getY(), bbMin.getZ()));
		GEC::AABB boundingBox(center, size);

		std::vector<vertexNormalUV> vertices;
		std::vector<int> indices;

		vertexNormalUV tmp;
		tmp.n = glm::vec3(1.0f);
		tmp.u = glm::vec2(0.0f);
		tmp.v = boundingBox.max;
		vertices.push_back(tmp);
		tmp.v = boundingBox.max;
		tmp.v.y -= boundingBox.size.y;
		vertices.push_back(tmp);
		tmp.v = boundingBox.max;
		tmp.v.x -= boundingBox.size.x;
		tmp.v.y -= boundingBox.size.y;
		vertices.push_back(tmp);
		tmp.v = boundingBox.max;
		tmp.v.x -= boundingBox.size.x;
		vertices.push_back(tmp);

		tmp.v = boundingBox.min;
		vertices.push_back(tmp);
		tmp.v = boundingBox.min;
		tmp.v.y += boundingBox.size.y;
		vertices.push_back(tmp);
		tmp.v = boundingBox.min;
		tmp.v.x += boundingBox.size.x;
		tmp.v.y += boundingBox.size.y;
		vertices.push_back(tmp);
		tmp.v = boundingBox.min;
		tmp.v.x += boundingBox.size.x;
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

		makeVertexBuffer(vertices, indices);
		draw();
	}

	void DebugBTDraw::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
	{
		std::cout << "Implement drawContactPoint\n";
	}

	void DebugBTDraw::reportErrorWarning(const char* warningString)
	{
		std::cout << warningString << std::endl;
	}

	void DebugBTDraw::draw3dText(const btVector3& location, const char* textString)
	{
		std::cout << "Implement unsupported\n";
	}

	void DebugBTDraw::setDebugMode(int debugMode)
	{
		m_debugMode = debugMode;
	}

	int DebugBTDraw::getDebugMode() const
	{
		return m_debugMode;
	}

	void DebugBTDraw::makeVertexBuffer(std::vector<vertexNormalUV> vertices, std::vector<int> indices)
	{
		m_indexCount = (int)indices.size();
		m_vertexBuffer = mkShare<GEC::VertexBuffer>(vertices, indices);
	}

	void DebugBTDraw::setDebugCamera(shared<GE::Camera> camera)
	{
		m_debugCamera = camera;
	}

	void DebugBTDraw::draw()
	{
		m_shaderProgram->bind();
		m_shaderProgram->uniform3f("wireframeColour", 128.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f);
		m_shaderProgram->uniformMatrix4("modelMatrix", 1, glm::mat4(1.0f));
		m_shaderProgram->uniformMatrix4("viewMatrix", 1, m_debugCamera->getView());
		m_shaderProgram->uniformMatrix4("projectionlMatrix", 1, m_debugCamera->getProjection());
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
};
