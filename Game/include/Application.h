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
	std::unordered_map<std::string, shared<GE::GameObject>> m_gameObjects;
	shared<GEC::Texture> m_texture;
	shared<GEC::Texture> m_paddleTexture;
	shared<GEC::ObjObject> m_paddleObject;
	shared<GEC::ObjObject> m_sphereObject;
	shared<GE::Program> m_shaderProgram;
	shared<GE::Program> m_shaderProgramCollision;
	shared<GE::Input::InputManager> m_input;
	shared<GE::Input::MouseConverter> m_screenMouse;
	shared<GE::Camera> m_camera;
	Configurations m_config;
	glm::vec2 m_scrennSize;
	int m_activeLevel;


	btDiscreteDynamicsWorld* dynamicsWorld;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;


	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  returns the number of overlapping objects using the collision dispatcher
	/// \return int number of overlapping objects pairs (i.e. 2 objects equals 1 pair)
	//----------------------------------------------------------------------------------------------------------------------
	int overlappingObjectsPairsCount()
	{
		return dynamicsWorld->getDispatcher()->getNumManifolds();
	}

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  returns the number of overlapping objects using the collision dispatcher
	/// \param  std::string empty string (key) to fill
	/// \param  std::string empty string (key) to fill
	/// \param  int pair ID
	/// \return int number of overlapping objects pairs (i.e. 2 objects equals 1 pair)
	//----------------------------------------------------------------------------------------------------------------------
	void getOverlappingGameObjects(std::string& keyA, std::string& keyB, int pairNumber)
	{
		// get the two objects that have collided
		btPersistentManifold* manifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(pairNumber);
		const btCollisionObject* const objectA = manifold->getBody0();
		const btCollisionObject* const objectB = manifold->getBody1();
		manifold->refreshContactPoints(objectA->getWorldTransform(), objectB->getWorldTransform());

		// find which GameObject these two objects are
		for (std::unordered_map<std::string, shared<GE::GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
		{
			if (it->second->isActive())
			{
				shared<GE::Transform> transform = it->second->getComponentShared<GE::Transform>(GE::kTransform);
				glm::vec3 originA(objectA->getWorldTransform().getOrigin().getX(), objectA->getWorldTransform().getOrigin().getY(), objectA->getWorldTransform().getOrigin().getZ());
				if (originA == transform->getPosition())
				{
					keyA = it->first;
				}

				glm::vec3 originB(objectB->getWorldTransform().getOrigin().getX(), objectB->getWorldTransform().getOrigin().getY(), objectB->getWorldTransform().getOrigin().getZ());
				if (originB == transform->getPosition())
				{
					keyB = it->first;
				}
			}
		}
	}
};
