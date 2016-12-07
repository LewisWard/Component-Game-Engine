// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 26/10/2016
#pragma once
#include "Program.h"
#include "Camera.h"
#include "Log.h"
#include "AABB.h"
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
		kBoxCollider,
		kSphereCollider,
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

		inline void translate(glm::vec3& p) { m_position += p; }

		glm::mat4 createTransform();

	private:
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_rotation;
	};

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		void onDraw();

		void MeshRenderer::Draw();

		void setTexture(shared<GEC::Texture>& texture) { m_texture = texture; }

		void setMesh(shared<GEC::ObjObject>& mesh) { m_mesh = mesh; }

		void setProgram(shared<GE::Program>& program) { m_shaderProgram = program; }

		inline void setScreenRes(glm::vec2 screen) { m_screenRes = screen; }

		void setMainCamera(shared<GE::Camera> mainCamera) { m_mainCamera = mainCamera; }

		void setMVPUniforms(glm::mat4 M);

	public:
		weak<GE::Program> m_shaderProgram;
		weak<GE::Camera> m_mainCamera;
		weak<GEC::Texture> m_texture;
		weak<GEC::ObjObject> m_mesh;
		glm::vec2 m_screenRes;
		bool m_usingVertexBuffer;
	};

	class SphereCollider : public Component
	{
	public:

		SphereCollider();

		SphereCollider(glm::vec3 center, glm::vec3 radius);

		~SphereCollider();

		void boundToObject(shared<GEC::ObjObject> obj);

		inline float getRadius() { return m_radius; }

		inline glm::vec3 getCenter() { return m_center; }

		inline void setRadius(float r) { m_radius = r; }

		inline void setCenter(glm::vec3 c) { m_center = c; }

		bool collision(SphereCollider& other);

	private:
		glm::vec3 m_center;
		float m_radius;
	};

	class BoxCollider : public Component
	{
	friend class AABB;
	public:

		BoxCollider();

		BoxCollider(glm::vec3 center, glm::vec3 size);

		~BoxCollider();

		void onDraw();

		void boundToObject(shared<GEC::ObjObject> obj);

		void setMin(glm::vec3 min) { m_boundingBox.min = min; m_boundingBox.center = ((m_boundingBox.max - m_boundingBox.min) / 2.0f) + m_boundingBox.min; };

		void setMax(glm::vec3 max) { m_boundingBox.max = max; m_boundingBox.center = ((m_boundingBox.max - m_boundingBox.min) / 2.0f) + m_boundingBox.min; };

		inline glm::vec3 getMin() { return m_boundingBox.min; }
							
		inline glm::vec3 getMax() { return m_boundingBox.max; }

		inline glm::vec3 getCenter() { return m_boundingBox.center; }

		bool collision(BoxCollider other);

		bool collision(GE::SphereCollider sphere);

		inline void setScreenRes(glm::vec2 screen) { m_screenRes = screen; }

		void setMVPUniforms(glm::mat4 M, glm::mat4 V, glm::mat4 P);

		
		void recomputeBounds(glm::vec3& newPosition);
		

	public:
		GEC::AABB m_boundingBox;
		glm::vec2 m_screenRes;

	private:

		void makeVertexBuffer();

		shared<GEC::VertexBuffer> m_vertexBuffer;
		shared<GE::Program> m_shaderProgram;
		int m_indexCount;
	};

};

