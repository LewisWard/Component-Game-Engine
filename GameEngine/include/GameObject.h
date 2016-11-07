// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 26/10/2016
#pragma once
#include "InputManager.h"
#include "Components.h"
#include <algorithm>

namespace GE
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		void update(float dt)
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				m_components[i]->onUpdate(dt);
			}
		}

		void draw()
		{
			// get the order of attached components
			std::vector<shared<Component>> pair;
			while (pair.size() != m_components.size())
			{
				for (size_t i = 0; i < m_components.size(); i++)
				{
					if (kTransform == m_components.at(i).get()->m_type && pair.empty())
					{
						pair.push_back(m_components[i]);
					}

					if (kMeshRenderer == m_components.at(i).get()->m_type && !pair.empty())
					{
						pair.push_back(m_components[i]);
					}
				}
			}
			m_components = pair;

			glm::mat4 model;
			// as this GameObject might not have all types of component we still need to check which type is where, but now it is an
			// ordered list. Just skip the ones this GameObject doesn't have
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
					glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 5.0f, 25.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					glm::mat4 projection = glm::perspective(45.0f, renderer->m_screenRes.x / renderer->m_screenRes.y, 0.1f, 100.0f);
					renderer->setMVPUniforms(model, view, projection);
					m_components[i]->onDraw();
				}
			}
		}

		template <class T>
		T* getComponent(ComponentType type)
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				if (type == m_components.at(i).get()->m_type)
				{
					return dynamic_cast<T*>(m_components.at(i).get());
				}
			}

			// it failed, we always have a Transform component so we return that one
			return dynamic_cast<T*>(m_components.at(0).get());
		}

		template <class T>
		const T* getComponentRead(ComponentType type)
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				if (type == m_components.at(i).get()->m_type)
				{
					return dynamic_cast<T*>(m_components.at(i).get());
				}
			}

			// it failed, we always have a Transform component so we return that one
			return dynamic_cast<T*>(m_components.at(0).get());
		}

		template <class T>
		weak<T> addComponent()
		{
			shared<T> component(new T());

			m_components.push_back(component);
			component->m_parent = this;

			return component;
		}

		void removeComponent(ComponentType type);

		void onDelete();

		std::vector<shared<Component>> getComponents() { return m_components;  }

		void setParent(GameObject Go) 
		{ 
			m_parent = mkShare<GameObject>(Go); 
			m_hasParent = true;
		}

		void unsetParent()
		{
			m_parent.reset();
			m_hasParent = false;
		}
		
		inline bool hasParent() { return m_hasParent; }

	private:
		std::vector<shared<Component>> m_components;
		std::vector<shared<GameObject>> m_childern;
		weak<GameObject> m_parent;
		bool m_hasParent;
	};
};
