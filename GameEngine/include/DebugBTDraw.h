// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#pragma once
#include "Window.h"
#include "Program.h"
#include "VertexBuffer.h"
#include "AABB.h"
#include "Camera.h"

namespace GE
{
	class DebugBTDraw : public btIDebugDraw
	{
	public:
		DebugBTDraw();
		virtual ~DebugBTDraw();
		virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);
		virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
		virtual void drawSphere(const btVector3& p, btScalar radius, const btVector3& color);
		virtual void drawBox(const btVector3& bbMin, const btVector3& bbMax, const btVector3& color);
		virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
		virtual void reportErrorWarning(const char* warningString);
		virtual void draw3dText(const btVector3& location, const char* textString);
		virtual void setDebugMode(int debugMode);
		virtual int getDebugMode() const;

		void setDebugCamera(shared<GE::Camera> camera);

	private:
		int m_debugMode;

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  makes a vertex buffer for the AABB
		//----------------------------------------------------------------------------------------------------------------------
		void makeVertexBuffer(std::vector<vertexNormalUV> vertices, std::vector<int> indices);
		void draw();

		shared<GE::Camera> m_debugCamera;
		shared<GEC::VertexBuffer> m_vertexBuffer;
		shared<GE::Program> m_shaderProgram;
		int m_indexCount;

	};
};
