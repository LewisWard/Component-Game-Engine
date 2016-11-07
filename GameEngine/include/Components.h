// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 26/10/2016
#pragma once
#include "glm\gtc\matrix_transform.hpp"
#include "ObjObject.h"
#include "Program.h"
#include "Log.h"
#include <vector>
#include <memory>

namespace GE
{
	// forward declear, see GameObject.h
	class GameObject;

	enum ComponentType
	{
		kTransform,
		kMeshRenderer,
		kMeshCollider
	};

	class Component
	{
	friend class GameObject;

	public:
		Component();
		virtual ~Component();

		virtual void onLoad();
		virtual void onUpdate(float dt);
		virtual void onDraw();
		virtual void onDelete();

	protected:
		GameObject* m_parent;
		ComponentType m_type;
	};

	class Transform : public Component
	{
	public:
		Transform();
		Transform(const Transform& t);
		~Transform();

		inline glm::vec3 getPosition() { return m_position;  }

		inline glm::vec3 getScale() { return m_scale; }

		inline glm::vec3 getRotation() { return m_rotation; }

		inline void setPosition(glm::vec3& p) { m_position = p; }

		inline void setScale(glm::vec3& s) { m_scale = s; }

		inline void setRotation(glm::vec3& r) { m_rotation = r; }

		glm::mat4 createTransform()
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

	private:
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_rotation;
	};

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		MeshRenderer(const MeshRenderer& m);
		~MeshRenderer();

		void onDraw();

		void setTexture(shared<GEC::Texture>& texture) { m_texture = texture; }

		void setMesh(shared<GEC::ObjObject>& mesh) { m_mesh = mesh; }

		void setProgram(shared<GE::Program>& program) { m_shaderProgram = program; }

		inline void setScreenRes(glm::vec2 screen) { m_screenRes = screen; }

		void setMVPUniforms(glm::mat4 M, glm::mat4 V, glm::mat4 P)
		{
			shared<GE::Program> program(m_shaderProgram);
			program->bind();
			program->uniformMatrix4("modelMatrix", 1, M);
			program->uniformMatrix4("viewMatrix", 1, V);
			program->uniformMatrix4("projectionlMatrix", 1, P);
			program->unbind();
		}

	public:
		weak<GEC::Texture> m_texture;
		weak<GEC::ObjObject> m_mesh;
		weak<GE::Program> m_shaderProgram;
		glm::vec2 m_screenRes;
	};
};

