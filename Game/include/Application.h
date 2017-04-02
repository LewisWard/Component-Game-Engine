// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 20/03/2017
#include "Defines.h"
#include "GameObject.h"
#include "DebugBTDraw.h"
#include "Timer.h"

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
	std::unordered_map<std::string, shared<GE::GameObject>> m_gameObjects;
	shared<btDiscreteDynamicsWorld> m_dynamicsWorld;
	shared<btDefaultCollisionConfiguration> m_collisionConfiguration;
	shared<btCollisionDispatcher> m_dispatcher;
	shared<btBroadphaseInterface> m_overlappingPairCache;
	shared<btSequentialImpulseConstraintSolver> m_solver;
	shared<GEC::Texture> m_texture;
	shared<GEC::Texture> m_paddleTexture;
	shared<GEC::Texture> m_wallTexture;
	shared<GEC::Texture> m_ballTexture;
	shared<GEC::ObjObject> m_paddleObject;
	shared<GEC::ObjObject> m_sphereObject;
	shared<GEC::ObjObject> m_wallObject;
	shared<GE::Program> m_shaderProgram;
	shared<GE::Program> m_shaderProgramCollision;
	shared<GE::Input::InputManager> m_input;
	shared<GE::Camera> m_cameraPlayer1;
	shared<GE::Camera> m_cameraPlayer2;
	Configurations m_config;
	shared<GEC::Timer> m_timer;
	btVector3 m_startingVelocity;
	btVector3 m_velocityDirection;
	btVector3 m_pfPosition;
	btVector3 m_ballSpeed;
	glm::vec2 m_scrennSize;
	float m_ballMaxSpeed;
	float m_paddleSpeed;
	int m_activeLevel;
	int m_player1Score;
	int m_player2Score;
	bool m_checker;

	GE::DebugBTDraw m_debugDraw;

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  returns the number of overlapping objects using the collision dispatcher
	/// \return int number of overlapping objects pairs (i.e. 2 objects equals 1 pair)
	//----------------------------------------------------------------------------------------------------------------------
	int overlappingObjectsPairsCount()
	{
		return m_dynamicsWorld->getDispatcher()->getNumManifolds();
	}

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  returns the number of overlapping objects using the collision dispatcher
	/// \param  std::string empty string (key) to fill
	/// \param  std::string empty string (key) to fill
	/// \param  int pair ID
	/// \return btVector3 normal at collision point of oebject B, int number of overlapping objects pairs (i.e. 2 objects equals 1 pair)
	//----------------------------------------------------------------------------------------------------------------------
	btVector3 getOverlappingGameObjects(std::string& keyA, std::string& keyB, int pairNumber);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  processes user input
	//----------------------------------------------------------------------------------------------------------------------
	void prcoessInput();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  resets the ball
	//----------------------------------------------------------------------------------------------------------------------
	void ballReset();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  prints instructions to console
	//----------------------------------------------------------------------------------------------------------------------
	void instructions();
};
