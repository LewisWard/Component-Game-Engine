// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#include "Defines.h"
#include "GameObject.h"
#include "Configurations.h"

class Application
{
public:
	Application();
	~Application();

	void update(float& dt);

	void draw();

private:
	std::vector<shared<GE::GameObject>> m_gameObjects;
	shared<GEC::Texture> m_texture;
	shared<GEC::ObjObject> m_planeObject;
	shared<GEC::ObjObject> m_sphereObject;
	shared<GE::Program> m_shaderProgram;
	glm::vec2 m_scrennSize;
};
