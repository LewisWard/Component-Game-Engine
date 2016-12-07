// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#include "Defines.h"
#include "GameObject.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief the application/game build using the Game Engine
//----------------------------------------------------------------------------------------------------------------------
class Application
{
public:
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  Constructor
	//----------------------------------------------------------------------------------------------------------------------
	Application();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  Destructor
	//----------------------------------------------------------------------------------------------------------------------
	~Application();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  update the applcation
	/// prama		float delta time
	//----------------------------------------------------------------------------------------------------------------------
	void update(float& dt);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  draw GameObjects
	//----------------------------------------------------------------------------------------------------------------------
	void draw();

private:
	std::vector<shared<GE::GameObject>> m_gameObjects;
	shared<GEC::Texture> m_texture;
	shared<GEC::ObjObject> m_cubeObject;
	shared<GEC::ObjObject> m_sphereObject;
	shared<GE::Program> m_shaderProgram;
	shared<GE::Program> m_shaderProgramCollision;
	shared<GE::Input::InputManager> m_input;
	shared<GE::Input::MouseConverter> m_screenMouse;
	shared<GE::Camera> m_camera;
	Configurations m_config;
	glm::vec2 m_scrennSize;
	int m_activeLevel;
};
