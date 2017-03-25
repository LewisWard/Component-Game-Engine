// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 26/10/2016
#pragma once
#include "InputManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "glm\gtx\rotate_vector.hpp"
#include <algorithm>

namespace GE
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  Every object in that exists in the world is one of these
	//----------------------------------------------------------------------------------------------------------------------
	class GameObject
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		GameObject();
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Destructor
		//----------------------------------------------------------------------------------------------------------------------
		virtual ~GameObject();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  update 
		/// prama		float delta time
		//----------------------------------------------------------------------------------------------------------------------
		void update(float dt);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  draw 
		//----------------------------------------------------------------------------------------------------------------------
		void draw();

		void drawMapped();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get a attached component as a std::shared_ptr
		/// prama		ComponentType type
		/// \return shared<T> returns NULL if no component of that type attached
		//----------------------------------------------------------------------------------------------------------------------
		template <class T>
		shared<T> getComponentShared(ComponentType type)
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				if (type == m_components.at(i).get()->m_type)
				{
					return std::dynamic_pointer_cast<T>(m_components.at(i));
				}
			}

			// it failed
			return NULL;
		}


		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get a attached component as a std::shared_ptr
		/// \prama	ComponentType type
		/// \return shared<T> returns NULL if no component of that type attached
		//----------------------------------------------------------------------------------------------------------------------
		template <class T>
		shared<T> getMappedComponent(ComponentType type)
		{
			// make sure this component is attached
			try
			{
				shared<Component> sPtr = m_components2.at(type);
				return std::dynamic_pointer_cast<T>(sPtr);
			}
			catch (const std::out_of_range& error)
			{
				std::cerr << "Out of range error: " << error.what() << ". GameObject.h:" << __LINE__ << '\n';
			}

			// it failed
			return NULL;
		}

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get a attached component as a pointer
		/// prama		ComponentType type
		/// \return T* returns NULL if no component of that type attached
		//----------------------------------------------------------------------------------------------------------------------
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


		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  add a new component
		/// \return shared<T> newly created component
		//----------------------------------------------------------------------------------------------------------------------
		template <class T>
		shared<T> addComponent()
		{
			shared<T> component(new T());

			m_components.push_back(component);
			component->m_parent = this;

			return component;
		}


		template <class T>
		shared<T> addMappedComponent(GE::ComponentType type)
		{
			shared<T> component(new T());

			component->m_parent = this;
			m_components2.insert(std::pair<GE::ComponentType, shared<GE::Component>>(type, component));

			return component;
		}

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  remove component
		/// \return ComponentType type
		//----------------------------------------------------------------------------------------------------------------------
		void removeComponent(ComponentType type);


		void removeMappedComponent(ComponentType type);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  when deleted
		//----------------------------------------------------------------------------------------------------------------------
		void onDelete();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get all attached components
		/// \return std::vector<shared<Component>>
		//----------------------------------------------------------------------------------------------------------------------
		std::vector<shared<Component>> getComponents() { return m_components;  }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set if this gameobject will have a child gameobject (can have more then one)
		/// prama		shared<GE::GameObject>
		//----------------------------------------------------------------------------------------------------------------------
		void setChild(shared<GE::GameObject> GameObject);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  does it have childern GameObjects
		/// \return bool true if so
		//----------------------------------------------------------------------------------------------------------------------
		bool hasChildern() { return m_childern.size() >= 1 ? 1 : 0;  }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief if this GameObject has a parent
		/// prama GameObject
		/// \note need to also set the parent to this object as a child!
		//----------------------------------------------------------------------------------------------------------------------
		void setParent(GameObject Go);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  no longer has a parent
		//----------------------------------------------------------------------------------------------------------------------
		void unsetParent();
		
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  does it have parent GameObject
		/// \return bool true if so
		//----------------------------------------------------------------------------------------------------------------------
		inline bool hasParent() { return m_hasParent; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set input
		/// prama		shared<GE::Input::InputManager>
		//----------------------------------------------------------------------------------------------------------------------
		void setInput(shared<GE::Input::InputManager> input) { m_input = input; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  has the user selected this GameObject
		/// \return bool
		//----------------------------------------------------------------------------------------------------------------------
		inline bool isSelected() { return m_isSelected; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set this GameObject as the currently selected GameObject
		//----------------------------------------------------------------------------------------------------------------------
		inline void setSelected() { m_isSelected = true; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  unset this GameObject as the currently selected GameObject
		//----------------------------------------------------------------------------------------------------------------------
		inline void unselected() { m_isSelected = false; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  has this GameObject collided with another GameObject
		/// \return bool
		//----------------------------------------------------------------------------------------------------------------------
		inline bool hasCollided() { return m_hasCollided; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set this GameObject has collided with another GameObject
		/// prama  bool
		//----------------------------------------------------------------------------------------------------------------------
		inline void hasCollided(bool collided) { m_hasCollided = collided; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  translate
		/// prama		glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		void translate(glm::vec3& translate);

		void translateMapped(glm::vec3& translate);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  scale
		/// prama		glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		void scale(glm::vec3& scale);

		void scaleMapped(glm::vec3& scale);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  rotate
		/// prama		glm::vec3
		//----------------------------------------------------------------------------------------------------------------------
		void rotate(glm::vec3& rotate);

		void rotateMapped(glm::vec3& rotate);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief set if this is active, if not it is not updated, drawn or able to be selected
		/// prama  bool
		//----------------------------------------------------------------------------------------------------------------------
		inline void isActive(bool state) { m_active = state; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  is this active, if not it is not updated, drawn or able to be selected
		/// \return bool
		//----------------------------------------------------------------------------------------------------------------------
		inline bool isActive() { return m_active; }

	private:
		std::unordered_map<ComponentType, shared<GE::Component>> m_components2;
		std::vector<shared<Component>> m_components;
		std::vector<shared<GameObject>> m_childern;
		weak<GE::Input::InputManager> m_input;
		weak<GameObject> m_parent;
		bool m_isSelected;
		bool m_hasCollided;
		bool m_hasParent;
		bool m_active;
	};
};
