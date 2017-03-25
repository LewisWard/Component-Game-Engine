// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#include "Application.h"
#include <string>

Application::Application()
{
	m_config.readINIFile(ENGINEASSETS"game.ini");
	std::string assetPath(ENGINEASSETS);

	m_input = mkShare<GE::Input::InputManager>();

	m_scrennSize.x = RES_LOW_X;
	m_scrennSize.y = RES_LOW_Y;
	onResize((int)m_scrennSize.x, (int)m_scrennSize.y);
	glViewport(0, 0, (int)m_scrennSize.x, (int)m_scrennSize.y);
	windowRename(std::string(m_config.data.windowTitle).c_str());


	// ------------------- BULLET SETUP  ------------------- //

	// collision configuration contains default setup for memory, collision setup
	collisionConfiguration = new btDefaultCollisionConfiguration();

	// the default collision dispatcher
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	// a general purpose broadphase
	overlappingPairCache = new btDbvtBroadphase();

	// the default constraint solver
	solver = new btSequentialImpulseConstraintSolver;

	// provide a high level interface that manages the physics objects and implements the update of all objects each frame
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -10, 0));


	// ------------------- BULLET SET    ------------------- //



	m_texture = mkShare<GEC::Texture>(std::string(assetPath + m_config.data.texturePaths[0]).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
	m_paddleTexture = mkShare<GEC::Texture>(std::string(assetPath + m_config.data.texturePaths[1]).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
	m_sphereObject = mkShare<GEC::ObjObject>(std::string(assetPath + m_config.data.modelPaths[0]).c_str());
	m_paddleObject = mkShare<GEC::ObjObject>(std::string(assetPath + m_config.data.modelPaths[1]).c_str());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);

	m_camera = mkShare<GE::Camera>(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1.0f), m_scrennSize, 45.0f, 0.1f, 100.0f);

	GE::Shader vertexShader(std::string(assetPath + m_config.data.shaderPaths[0]).c_str(), kVertexShader);
	GE::Shader pixelShader(std::string(assetPath + m_config.data.shaderPaths[1]).c_str(), kPixelShader);
	m_shaderProgram = mkShare<GE::Program>(vertexShader, pixelShader);

	GE::Shader vertexShader2(std::string(assetPath + "shaders/collisionWireframe.vrt.bin").c_str(), kVertexShader);
	GE::Shader pixelShader2(std::string(assetPath + "shaders/collisionWireframe.pix.bin").c_str(), kPixelShader);
	m_shaderProgramCollision = mkShare<GE::Program>(vertexShader2, pixelShader2);

	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("player1Paddle"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("player2Paddle"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("ball"), mkShare<GE::GameObject>()));

	shared<GE::Transform> transform;
	shared<GE::MeshRenderer> meshRenderer;
	shared<GE::BoxCollider> boxCollider;
	shared<GE::SphereCollider> sphereCollider;
	shared<GE::CollisionShape> collisionShape;

	// player1Paddle
	transform = m_gameObjects.at("player1Paddle")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	transform->setPosition(glm::vec3(0.0f, -5.0f, -20.0f));
	transform->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	m_gameObjects.at("player1Paddle")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("player1Paddle")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_paddleObject);
	meshRenderer->setTexture(m_paddleTexture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_camera);
	m_gameObjects.at("player1Paddle")->addComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider = m_gameObjects.at("player1Paddle")->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->boundToObject(m_paddleObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	m_gameObjects.at("player1Paddle")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("player1Paddle")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape->createShape(btBoxShape(btVector3(btScalar(transform->getScale().x), btScalar(transform->getScale().y), btScalar(transform->getScale().z))));

	// player2Paddle
	transform = m_gameObjects.at("player2Paddle")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	transform->setPosition(glm::vec3(0.0f, -5.0f, -60.0f));
	transform->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	m_gameObjects.at("player2Paddle")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("player2Paddle")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_paddleObject);
	meshRenderer->setTexture(m_paddleTexture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_camera);
	m_gameObjects.at("player2Paddle")->addComponent<GE::SphereCollider>(GE::kSphereCollider);
	sphereCollider = m_gameObjects.at("player2Paddle")->getComponentShared<GE::SphereCollider>(GE::kSphereCollider);
	sphereCollider->boundToObject(m_paddleObject);
	sphereCollider->setCenter(transform->getPosition());
	sphereCollider->setRadius(transform->getScale().x);

	// ball
	transform = m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f));
	transform->setPosition(glm::vec3(0.0f, 5.0f, -20.0f));
	m_gameObjects.at("ball")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("ball")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_sphereObject);
	meshRenderer->setTexture(m_texture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_camera);
	m_gameObjects.at("ball")->addComponent<GE::SphereCollider>(GE::kSphereCollider);
	sphereCollider = m_gameObjects.at("ball")->getComponentShared<GE::SphereCollider>(GE::kSphereCollider);
	sphereCollider->boundToObject(m_sphereObject);
	sphereCollider->setCenter(transform->getPosition());
	sphereCollider->setRadius(transform->getScale().x);


	// ------------------- BULLET GAMEOBJECTS CONFIG ------------------- //
	{
		transform = m_gameObjects.at("player1Paddle")->getComponentShared<GE::Transform>(GE::kTransform);
		shared<btCollisionShape> paddleShape = m_gameObjects.at("player1Paddle")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape)->getShape();
		//btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(transform->getScale().x), btScalar(transform->getScale().y), btScalar(transform->getScale().z)));
		collisionShapes.push_back(paddleShape.get());

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z));

		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			paddleShape->calculateLocalInertia(mass, localInertia);

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, paddleShape.get(), localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);


		// paddle2
		transform = m_gameObjects.at("player2Paddle")->getComponentShared<GE::Transform>(GE::kTransform);
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z));
		btDefaultMotionState* myMotionStateTwo= new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbTwoInfo(mass, myMotionStateTwo, paddleShape.get(), localInertia);
		body = new btRigidBody(rbTwoInfo);

		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);
	}


	{
		//create a dynamic rigidbody
		transform = m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform);
		btCollisionShape* colShape = new btSphereShape(btScalar(transform->getScale().x));
		collisionShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar	mass(1.f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

		startTransform.setOrigin(btVector3(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z));

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		dynamicsWorld->addRigidBody(body);
	}
	// ------------------- BULLET GAMEOBJECTS CONFIGED ------------------- //


	m_screenMouse = mkShare<GE::Input::MouseConverter>(m_camera->getProjection(), m_camera->getView(), m_scrennSize);

	// which level to start on
	m_activeLevel = 0;
}

Application::~Application()
{
	//remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	// collision shapes are deleted in the CollisionShape component

	delete dynamicsWorld;
	delete solver;
	delete overlappingPairCache;
	delete dispatcher;
	delete collisionConfiguration;
	collisionShapes.clear();
	m_gameObjects.clear();
	std::cout << "Application deleted\n";
}

void Application::update(float& dt)
{
	static float refreshDT = 0.0f;
	refreshDT += dt;

	// update input
	m_input->update();

	// cap how often you can change selection - make input update more accurate
	if (refreshDT >= 0.05f)
	{

		refreshDT = 0.0f;
	}

	if (m_input->getKeyHeld("action"))
	{

	}

	///-----stepsimulation_start-----
	{
		dynamicsWorld->stepSimulation(1.f / 60.f, 10);

		//print positions of all objects
		for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			if (body && body->getMotionState())
			{
				body->getMotionState()->getWorldTransform(trans);

			}
			else
			{
				trans = obj->getWorldTransform();
			}
		}
	}


		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[2];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);

		}
		else
		{
			trans = obj->getWorldTransform();
		}


		shared<GE::Transform> objectTransform = m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform);
		btVector3 origin = trans.getOrigin();
		glm::vec3 glmOrigin(origin.getX(), origin.getY(), origin.getZ());
		objectTransform->setPosition(glmOrigin);
		m_gameObjects.at("ball")->setInput(m_input);
		m_gameObjects.at("ball")->update(dt);
}

void Application::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(28.0f / 255.0f, 28.0f / 255.0f, 28.0f / 255.0f, 1.0f);

	if (m_input->getMouseDown(GE::Input::kLeftButton))
	{
		shared<GE::SphereCollider> sphereCollider;
		shared<GE::BoxCollider> boxCollider;
		shared<GE::Transform> transform;
		GE::Input::Mouse mousePos = m_input->getMousePosition();

		m_screenMouse->update(mousePos);
		glm::vec3 mouseRay = m_screenMouse->getRay();
		glm::vec3 cameraOrigin(m_camera->getPosition());

		for (std::unordered_map<std::string, shared<GE::GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
		{
			if (it->second->isActive())
			{
				transform = it->second->getComponentShared<GE::Transform>(GE::kTransform);
				boxCollider = it->second->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
				sphereCollider = it->second->getComponentShared<GE::SphereCollider>(GE::kSphereCollider);

				// based on: http://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms [accessed 06/12/2016]
				// the direction of the ray firing from the camera to the clicked position
				glm::vec3 rayDirection(mouseRay - cameraOrigin);
				rayDirection = glm::normalize(rayDirection);

				// test ray vs AABB otherwise vs Sphere
				if (boxCollider != NULL)
				{
					glm::vec3 min(boxCollider->m_boundingBox.min);
					glm::vec3 max(boxCollider->m_boundingBox.max);

					// computer where the ray intersects with each plane
					float minX = (min.x - cameraOrigin.x) / rayDirection.x;
					float maxX = (max.x - cameraOrigin.x) / rayDirection.x;
					float minY = (min.y - cameraOrigin.y) / rayDirection.y;
					float maxY = (max.y - cameraOrigin.y) / rayDirection.y;
					float minZ = (min.z - cameraOrigin.z) / rayDirection.z;
					float maxZ = (max.z - cameraOrigin.z) / rayDirection.z;
					bool objectHit = true;

					// find the greatest t value
					float tmin = glm::max(glm::max(glm::min(minX, maxX), glm::min(minY, maxY)), glm::min(minZ, maxZ));
					float tmax = glm::min(glm::min(glm::max(minX, maxX), glm::max(minY, maxY)), glm::max(minZ, maxZ));

					// if any ray < 0 there was an intersection but behind the camera
					if (tmax < 0)
						objectHit = false;

					// ray didn't intersect
					if (tmin > tmax)
						objectHit = false;

					if (objectHit)
					{
						// now an object has been hit, need to do something
						if (objectHit)
						{
							// find the currently selected object and change it to another object
							for (std::unordered_map<std::string, shared<GE::GameObject>>::iterator its = m_gameObjects.begin(); its != m_gameObjects.end(); its++)
								if (its->second->isSelected())
								{
									its->second->unselected();
									break;
								}

							it->second->setSelected();
							printf("selected %s \n", it->first);
						}
					}

				}
				else if (sphereCollider != NULL)
				{
					// based on: https://capnramses.github.io//opengl/raycasting.html [accessed 06/12/2016]
					bool objectHit = false;
					float sphereRadius = sphereCollider->getRadius();
					glm::vec3 sphereCenter(sphereCollider->getCenter());

					// the direction of the ray firing from the camera to the clicked position
					//glm::vec3 rayDirection(mouseRay - cameraOrigin);
					//rayDirection = glm::normalize(rayDirection);

					// t is the distance from the ray origin to a point on the surface of the sphere (center + radius)
					float t = glm::distance(glm::abs(sphereCenter + sphereRadius), cameraOrigin);
					glm::vec3 pointOnSphere = glm::abs(cameraOrigin + rayDirection * t - sphereCenter) - sphereRadius;

					float B = glm::dot(rayDirection, cameraOrigin - sphereCenter);
					float C = glm::dot((cameraOrigin - sphereCenter), (cameraOrigin - sphereCenter)) - (sphereRadius * sphereRadius);

					float result = (B*B) - C;
					float detA = 0.0f;
					float detB = 0.0f;

					if (result == 0.0f)
					{
						detA = -B - glm::sqrt(result);
						objectHit = true;
					}

					if (result > 0.0f)
					{
						detA = -B - glm::sqrt(result);
						detB = -B + glm::sqrt(result);
						objectHit = true;
					}

					// now an object has been hit, need to do something
					if (objectHit)
					{
						// find the currently selected object and change it to another object
						for (std::unordered_map<std::string, shared<GE::GameObject>>::iterator its = m_gameObjects.begin(); its != m_gameObjects.end(); its++)
							if (its->second->isSelected())
							{
								its->second->unselected();
								break;
							}

						it->second->setSelected();
						printf("selected %s \n", it->first);
					}
				}
			}
		}
	}

	for (std::unordered_map<std::string, shared<GE::GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if (it->second->isActive())
			it->second->draw();
	}

	glutSwapBuffers();
}
