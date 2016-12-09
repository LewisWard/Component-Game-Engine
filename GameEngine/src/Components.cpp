// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 26/10/2016
#include "Components.h"

namespace GE
{
	Component::Component()
	{
		m_parent = nullptr;
	}

	Component::~Component()
	{
	}

	void Component::onLoad()
	{

	}

	void Component::onUpdate(float dt)
	{

	}

	void Component::onDraw()
	{

	}

	void Component::onDelete()
	{
		m_parent = nullptr;
	}
};
