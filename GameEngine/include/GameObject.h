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

		void update(float dt);

		void draw();

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

			// it failed
			return NULL;
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

			// it failed
			return NULL;
		}

		template <class T>
		shared<T> addComponent()
		{
			shared<T> component(new T());

			m_components.push_back(component);
			component->m_parent = this;

			return component;
		}

		void removeComponent(ComponentType type);

		void onDelete();

		std::vector<shared<Component>> getComponents() { return m_components;  }

		void setChild(shared<GE::GameObject> GameObject)
		{
			m_childern.push_back(GameObject);
		}

		bool hasChildern() { return m_childern.size();  }

		void setParent(GameObject Go);

		void unsetParent();
		
		inline bool hasParent() { return m_hasParent; }

		void setInput(shared<GE::Input::InputManager> input) { m_input = input; }

		inline bool isSelected() { return m_isSelected; }

		inline void setSelected() { m_isSelected = true; }

		inline void unselected() { m_isSelected = false; }

		void translate(glm::vec3& translate) 
		{ 
			// get the transform and update it
			GE::Transform* transform = getComponent<GE::Transform>(GE::kTransform);
			transform->translate(translate);

			// if there are childern update them too
			size_t childCount = m_childern.size();
			if (childCount)
				for (size_t i = 0; i < childCount; i++)
					m_childern.at(i)->translate(translate);
		}

		void scale(glm::vec3& scale)
		{
			// get the transform and update it
			GE::Transform* transform = getComponent<GE::Transform>(GE::kTransform);
			transform->setScale(scale);

			// if there are childern update them too
			size_t childCount = m_childern.size();
			if (childCount)
				for (size_t i = 0; i < childCount; i++)
					m_childern.at(i)->scale(scale);
		}

		void rotate(glm::vec3& rotate)
		{
			// get the transform and update it
			GE::Transform* transform = getComponent<GE::Transform>(GE::kTransform);
			transform->setRotation(rotate);

			// if there are childern update them too
			size_t childCount = m_childern.size();
			if (childCount)
				for (size_t i = 0; i < childCount; i++)
					m_childern.at(i)->rotate(rotate);
		}

	private:
		std::vector<shared<Component>> m_components;
		std::vector<shared<GameObject>> m_childern;
		weak<GE::Input::InputManager> m_input;
		weak<GameObject> m_parent;
		bool m_isSelected;
		bool m_hasParent;
	};
};
