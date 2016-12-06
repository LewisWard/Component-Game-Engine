// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 30/10/2016
#include "GameObject.h"

namespace GE
{
	GameObject::GameObject()
	{
		m_hasParent = false;
		m_isSelected = false;
		addComponent<Transform>();
	}

	GameObject::~GameObject()
	{

	}

	void GameObject::update(float dt)
	{
		glm::mat4 model;
		shared<GE::Input::InputManager> input(m_input);

		Transform* trs = getComponent<GE::Transform>(GE::kTransform);
		GE::BoxCollider* boxCollider = getComponent<GE::BoxCollider>(GE::kBoxCollider);
		GE::SphereCollider* sphereCollider = getComponent<GE::SphereCollider>(GE::kSphereCollider);

		//m_components[i]->onUpdate(dt);

		if (trs != NULL)
		{
			model = trs->createTransform();

			if (boxCollider != NULL)
			{
				boxCollider->recomputeBounds(trs->getPosition());
			}

			if (sphereCollider != NULL)
			{
				sphereCollider->setCenter(trs->getPosition());
			}
		}
	}

	void GameObject::draw()
	{
		glm::mat4 model;

		for (size_t i = 0; i < m_components.size(); i++)
		{
			if (kTransform == m_components.at(i).get()->m_type)
			{
				Transform* trs = dynamic_cast<Transform*>(m_components.at(i).get());
				model = trs->createTransform();
			}

			if (kMeshRenderer == m_components.at(i).get()->m_type)
			{
				MeshRenderer* renderer = dynamic_cast<MeshRenderer*>(m_components.at(i).get());
				glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 25.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				glm::mat4 projection = glm::perspective(45.0f, renderer->m_screenRes.x / renderer->m_screenRes.y, 0.1f, 100.0f);
				renderer->setMVPUniforms(model, view, projection);
				m_components[i]->onDraw();
			}

			if (kBoxCollider == m_components.at(i).get()->m_type)
			{
				BoxCollider* collider = dynamic_cast<BoxCollider*>(m_components.at(i).get());
				glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 25.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				glm::mat4 projection = glm::perspective(45.0f, collider->m_screenRes.x / collider->m_screenRes.y, 0.1f, 100.0f);
				collider->setMVPUniforms(model, view, projection);
				m_components[i]->onDraw();
			}
		}
	}

	void GameObject::removeComponent(ComponentType type)
	{
		for (size_t i = 0; i < m_components.size(); i++)
		{
			if (type == m_components.at(i).get()->m_type && type != kTransform)
			{
				m_components.erase(m_components.begin() + i);
			}
		}
	}

	void GameObject::onDelete()
	{
		m_components[0].reset();
		m_components.clear();
	}

	void GameObject::setParent(GameObject Go)
	{
		m_parent = mkShare<GameObject>(Go);
		m_hasParent = true;
	}

	void GameObject::unsetParent()
	{
		m_parent.reset();
		m_hasParent = false;
	}
};
