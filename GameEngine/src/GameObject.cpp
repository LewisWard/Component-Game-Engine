// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 30/10/2016
#include "GameObject.h"

namespace GE
{
	GameObject::GameObject()
	{
		m_active = true;
		m_hasParent = false;
		m_isSelected = false;
		m_hasCollided = false;
		addComponent<Transform>();
	}

	GameObject::~GameObject()
	{

	}

	void GameObject::update(float dt)
	{
		glm::mat4 model;
		shared<GE::Input::InputManager> input(m_input);

		shared<GE::Transform> trs = getComponentShared<GE::Transform>(GE::kTransform);
		shared<GE::BoxCollider> boxCollider = getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
		shared<GE::SphereCollider> sphereCollider = getComponentShared<GE::SphereCollider>(GE::kSphereCollider);

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
		// transform and meshrenderer components provide these for other components to use
		// TODO: improved checking on component order, so we don't access a NULL ptr
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

		for (size_t i = 0; i < m_components.size(); i++)
		{
			if (kTransform == m_components.at(i).get()->m_type)
			{
				shared<GE::Transform> trs = getComponentShared<GE::Transform>(kTransform);
				model = trs->createTransform();
			}

			if (kMeshRenderer == m_components.at(i).get()->m_type)
			{
				shared<GE::MeshRenderer> renderer = getComponentShared<GE::MeshRenderer>(kMeshRenderer);
				shared<GE::Camera> camera(renderer->m_mainCamera);
				view = camera->getView();
				projection = camera->getProjection();
				renderer->setMVPUniforms(model);
				
				// if this gameobject is selected, apply a highlight colour
				renderer->setColourOnSelection(glm::vec3(64.0f, 64.0f, 64.0f), m_isSelected);
				renderer->setColourOnCollision(glm::vec3(128.0f, 0.0f, 0.0f), m_hasCollided);

				m_components[i]->onDraw();
			}

			if (kBoxCollider == m_components.at(i).get()->m_type)
			{
				shared<GE::BoxCollider> collider = getComponentShared<GE::BoxCollider>(kBoxCollider);
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

	void GameObject::setChild(shared<GE::GameObject> GameObject)
	{
		m_childern.push_back(GameObject);
		m_childern.at(m_childern.size() - 1)->setParent(*this);
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

	void GameObject::translate(glm::vec3& translate)
	{
		// get the transform and update it
		shared<GE::Transform> transform = getComponentShared<GE::Transform>(GE::kTransform);
		transform->translate(translate);

		// if there are childern update them too
		size_t childCount = m_childern.size();
		if (childCount)
			for (size_t i = 0; i < childCount; i++)
				m_childern.at(i)->translate(translate);
	}

	void GameObject::scale(glm::vec3& scale)
	{
		// get the transform and update it
		shared<GE::Transform> transform = getComponentShared<GE::Transform>(GE::kTransform);
		transform->setScale(scale);

		// if there are childern update them too
		size_t childCount = m_childern.size();
		if (childCount)
			for (size_t i = 0; i < childCount; i++)
				m_childern.at(i)->scale(scale);
	}

	void GameObject::rotate(glm::vec3& rotate)
	{
		// get the transform and update it
		shared<GE::Transform> transform = getComponentShared<GE::Transform>(GE::kTransform);
		transform->setRotation(rotate);

		// if there are childern update them too
		size_t childCount = m_childern.size();
		if (childCount)
			for (size_t i = 0; i < childCount; i++)
				m_childern.at(i)->rotate(rotate);
	}
};
