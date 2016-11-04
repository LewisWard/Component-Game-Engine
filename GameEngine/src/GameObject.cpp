// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 30/10/2016
#include "GameObject.h"

namespace GE
{
	GameObject::GameObject()
	{
		m_hasParent = false;
		addComponent<Transform>();
	}

	GameObject::~GameObject()
	{

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
};
