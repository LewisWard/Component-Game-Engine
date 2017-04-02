// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 20/03/2017
#include "Application.h"
#include <string>

Application::Application()
{
	m_config.readINIFile(ENGINEASSETS"game.ini");
	std::string assetPath(ENGINEASSETS);

	m_input = mkShare<GE::Input::InputManager>();

	// create the window
	m_scrennSize.x = RES_MEDIUM_X;
	m_scrennSize.y = RES_MEDIUM_Y;
	onResize((int)m_scrennSize.x, (int)m_scrennSize.y);
	m_scrennSize.x /= 2.0f;
	glViewport(0, 0, (int)m_scrennSize.x, (int)m_scrennSize.y);
	windowRename(std::string(m_config.data.windowTitle).c_str());

	// ------------------- BULLET SETUP  ------------------- //
	m_collisionConfiguration = mkShare<btDefaultCollisionConfiguration>(); // collision configuration contains default setup for memory, collision setup
	m_dispatcher = mkShare<btCollisionDispatcher>(m_collisionConfiguration.get()); // the default collision dispatcher
	m_overlappingPairCache = mkShare<btDbvtBroadphase>(); // a general purpose broadphase
	m_solver = mkShare<btSequentialImpulseConstraintSolver>(); // the default constraint solver

	// provide a high level interface that manages the physics objects and implements the update of all objects each frame
	m_dynamicsWorld = mkShare<btDiscreteDynamicsWorld>(m_dispatcher.get(), m_overlappingPairCache.get(), m_solver.get(), m_collisionConfiguration.get());
	m_dynamicsWorld->setGravity(btVector3(0, 0, 0));
	m_dynamicsWorld->setDebugDrawer(&m_debugDraw);

	// ------------------- BULLET SET    ------------------- //

	// load assets
	m_texture = mkShare<GEC::Texture>(std::string(assetPath + m_config.data.texturePaths[0]).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
	m_paddleTexture = mkShare<GEC::Texture>(std::string(assetPath + m_config.data.texturePaths[1]).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
	m_wallTexture = mkShare<GEC::Texture>(std::string(assetPath + m_config.data.texturePaths[2]).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
	m_ballTexture = mkShare<GEC::Texture>(std::string(assetPath + m_config.data.texturePaths[3]).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
	m_sphereObject = mkShare<GEC::ObjObject>(std::string(assetPath + m_config.data.modelPaths[0]).c_str());
	m_paddleObject = mkShare<GEC::ObjObject>(std::string(assetPath + m_config.data.modelPaths[1]).c_str());
	m_wallObject = mkShare<GEC::ObjObject>(std::string(assetPath + m_config.data.modelPaths[2]).c_str());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);

	// set the cameras, load the shaders and create teh GameObjects
	m_cameraPlayer1 = mkShare<GE::Camera>(glm::vec3(0, 16, 0), glm::vec3(0, 16, -45.0f), m_scrennSize, 45.0f, 0.1f, 400.0f);
	m_cameraPlayer2 = mkShare<GE::Camera>(glm::vec3(0, 16, -136.0f), glm::vec3(0, 16, -50.0f), m_scrennSize, 45.0f, 0.1f, 400.0f);
	m_debugDraw.setDebugCamera(m_cameraPlayer1);

	GE::Shader vertexShader(std::string(assetPath + m_config.data.shaderPaths[0]).c_str(), kVertexShader);
	GE::Shader pixelShader(std::string(assetPath + m_config.data.shaderPaths[1]).c_str(), kPixelShader);
	m_shaderProgram = mkShare<GE::Program>(vertexShader, pixelShader);

	GE::Shader vertexShader2(std::string(assetPath + "shaders/collisionWireframe.vrt").c_str(), kVertexShader);
	GE::Shader pixelShader2(std::string(assetPath + "shaders/collisionWireframe.pix").c_str(), kPixelShader);
	m_shaderProgramCollision = mkShare<GE::Program>(vertexShader2, pixelShader2);

	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("player1Paddle"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("player2Paddle"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("ball"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("wallBottom"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("wallLeft"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("wallTop"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("wallRight"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("player1Goal"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("player2Goal"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("light0"), mkShare<GE::GameObject>()));
	m_gameObjects.insert(std::pair<std::string, shared<GE::GameObject>>(std::string("light1"), mkShare<GE::GameObject>()));

	// init creates the transform for each GameObject
	for (std::unordered_map<std::string, shared<GE::GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
		it->second->init();

	shared<GE::Transform> transform;
	shared<GE::MeshRenderer> meshRenderer;
	shared<GE::BoxCollider> boxCollider;
	shared<GE::SphereCollider> sphereCollider;
	shared<GE::CollisionShape> collisionShape;
	shared<GE::RigidBody> rigidBody;
	shared<GE::Light> light;

	//  walls
	transform = m_gameObjects.at("wallBottom")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(20.0f, 20.0f, 40.0f));
	transform->setPosition(glm::vec3(0.0f, 0.0f, -68.0f));
	transform->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	m_gameObjects.at("wallBottom")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("wallBottom")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_wallObject);
	meshRenderer->setTexture(m_wallTexture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_cameraPlayer1);
	m_gameObjects.at("wallBottom")->addComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider = m_gameObjects.at("wallBottom")->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->setScale(transform->getScale());
	boxCollider->boundToObject(m_wallObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	glm::vec3 aabbSize = glm::vec3(boxCollider->m_boundingBox.extents);
	m_gameObjects.at("wallBottom")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("wallBottom")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape->createShape(btBoxShape(btVector3(btScalar(aabbSize.x), btScalar(aabbSize.y), btScalar(aabbSize.z))));
	m_gameObjects.at("wallBottom")->addComponent<GE::RigidBody>(GE::kRigidBody);
	rigidBody = m_gameObjects.at("wallBottom")->getComponentShared<GE::RigidBody>(GE::kRigidBody);
	rigidBody->createRigidBody(collisionShape, transform->getPosition(), 0.0f);
#if BULLET_DRAW_ALL == 0
	rigidBody->getRigidBody()->setCollisionFlags(rigidBody->getRigidBody()->getCollisionFlags() | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
#endif

	transform = m_gameObjects.at("wallLeft")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(16.0f, 20.0f, 40.0f));
	transform->setPosition(glm::vec3(-14.0f, 15.0f, -68.0f));
	transform->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));
	m_gameObjects.at("wallLeft")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("wallLeft")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_wallObject);
	meshRenderer->setTexture(m_wallTexture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_cameraPlayer1);
	m_gameObjects.at("wallLeft")->addComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider = m_gameObjects.at("wallLeft")->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->setScale(transform->getScale());
	boxCollider->boundToObject(m_wallObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	aabbSize = glm::vec3(boxCollider->m_boundingBox.extents);
	m_gameObjects.at("wallLeft")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("wallLeft")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape->createShape(btBoxShape(btVector3(btScalar(aabbSize.y), btScalar(aabbSize.x), btScalar(aabbSize.z)))); // could use a OBB and recalulate entents but as its a 90 degree rotation on 1 axis, just swap x and y
	m_gameObjects.at("wallLeft")->addComponent<GE::RigidBody>(GE::kRigidBody);
	rigidBody = m_gameObjects.at("wallLeft")->getComponentShared<GE::RigidBody>(GE::kRigidBody);
	rigidBody->createRigidBody(collisionShape, transform->getPosition(), 0.0f);
#if BULLET_DRAW_ALL == 0
	rigidBody->getRigidBody()->setCollisionFlags(rigidBody->getRigidBody()->getCollisionFlags() | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
#endif

	transform = m_gameObjects.at("wallTop")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(20.0f, 20.0f, 40.0f));
	transform->setPosition(glm::vec3(0.0f, 32.0f, -68.0f));
	transform->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	m_gameObjects.at("wallTop")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("wallTop")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_wallObject);
	meshRenderer->setTexture(m_wallTexture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_cameraPlayer1);
	m_gameObjects.at("wallTop")->addComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider = m_gameObjects.at("wallTop")->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->setScale(transform->getScale());
	boxCollider->boundToObject(m_wallObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	aabbSize = glm::vec3(boxCollider->m_boundingBox.extents);
	m_gameObjects.at("wallTop")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("wallTop")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape->createShape(btBoxShape(btVector3(btScalar(aabbSize.x), btScalar(aabbSize.y), btScalar(aabbSize.z))));
	m_gameObjects.at("wallTop")->addComponent<GE::RigidBody>(GE::kRigidBody);
	rigidBody = m_gameObjects.at("wallTop")->getComponentShared<GE::RigidBody>(GE::kRigidBody);
	rigidBody->createRigidBody(collisionShape, transform->getPosition(), 0.0f);
#if BULLET_DRAW_ALL == 0
	rigidBody->getRigidBody()->setCollisionFlags(rigidBody->getRigidBody()->getCollisionFlags() | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
#endif

	transform = m_gameObjects.at("wallRight")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(16.0f, 20.0f, 40.0f));
	transform->setPosition(glm::vec3(14.f, 15.f, -68.0f));
	transform->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));
	m_gameObjects.at("wallRight")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("wallRight")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_wallObject);
	meshRenderer->setTexture(m_wallTexture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_cameraPlayer1);
	m_gameObjects.at("wallRight")->addComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider = m_gameObjects.at("wallRight")->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->setScale(transform->getScale());
	boxCollider->boundToObject(m_wallObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	aabbSize = glm::vec3(boxCollider->m_boundingBox.extents);
	m_gameObjects.at("wallRight")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("wallRight")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape->createShape(btBoxShape(btVector3(btScalar(aabbSize.y), btScalar(aabbSize.x), btScalar(aabbSize.z))));
	m_gameObjects.at("wallRight")->addComponent<GE::RigidBody>(GE::kRigidBody);
	rigidBody = m_gameObjects.at("wallRight")->getComponentShared<GE::RigidBody>(GE::kRigidBody);
	rigidBody->createRigidBody(collisionShape, transform->getPosition(), 0.0f);
#if BULLET_DRAW_ALL == 0
	rigidBody->getRigidBody()->setCollisionFlags(rigidBody->getRigidBody()->getCollisionFlags() | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
#endif

	// ball
	transform = m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f));
	transform->setPosition(glm::vec3(-2.0f, 10.0f, -55.0f));
	m_gameObjects.at("ball")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("ball")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_sphereObject);
	meshRenderer->setTexture(m_ballTexture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_cameraPlayer1);
	m_gameObjects.at("ball")->addComponent<GE::SphereCollider>(GE::kSphereCollider);
	sphereCollider = m_gameObjects.at("ball")->getComponentShared<GE::SphereCollider>(GE::kSphereCollider);
	sphereCollider->boundToObject(m_sphereObject);
	sphereCollider->setCenter(transform->getPosition());
	sphereCollider->setRadius(transform->getScale().x);
	m_gameObjects.at("ball")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("ball")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape->createShape(btSphereShape(btScalar(transform->getScale().x)));
	m_gameObjects.at("ball")->addComponent<GE::RigidBody>(GE::kRigidBody);
	rigidBody = m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody);
	rigidBody->createRigidBody(collisionShape, transform->getPosition(), 1.0f);
	rigidBody->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);

	// player1Paddle
	transform = m_gameObjects.at("player1Paddle")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	transform->setPosition(glm::vec3(0.0f, 10.0f, -32.0f));
	transform->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	m_gameObjects.at("player1Paddle")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("player1Paddle")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_paddleObject);
	meshRenderer->setTexture(m_paddleTexture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_cameraPlayer1);
	m_gameObjects.at("player1Paddle")->addComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider = m_gameObjects.at("player1Paddle")->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->boundToObject(m_paddleObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	m_gameObjects.at("player1Paddle")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("player1Paddle")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	aabbSize = glm::vec3(boxCollider->m_boundingBox.extents);
	collisionShape->createShape(btBoxShape(btVector3(btScalar(aabbSize.x), btScalar(aabbSize.y), btScalar(aabbSize.z))));
	m_gameObjects.at("player1Paddle")->addComponent<GE::RigidBody>(GE::kRigidBody);
	rigidBody = m_gameObjects.at("player1Paddle")->getComponentShared<GE::RigidBody>(GE::kRigidBody);
	rigidBody->createRigidBody(collisionShape, transform->getPosition(), 1.0f);
	rigidBody->getRigidBody()->setAngularFactor(btVector3(0, 0, 0));
	rigidBody->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);

	// player2Paddle
	transform = m_gameObjects.at("player2Paddle")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	transform->setPosition(glm::vec3(0.0f, 10.0f, -104.0f));
	transform->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	m_gameObjects.at("player2Paddle")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("player2Paddle")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_paddleObject);
	meshRenderer->setTexture(m_paddleTexture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_cameraPlayer1);
	m_gameObjects.at("player2Paddle")->addComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider = m_gameObjects.at("player2Paddle")->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->boundToObject(m_paddleObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	aabbSize = glm::vec3(boxCollider->m_boundingBox.extents);
	m_gameObjects.at("player2Paddle")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("player2Paddle")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape->createShape(btBoxShape(btVector3(btScalar(aabbSize.x), btScalar(aabbSize.y), btScalar(aabbSize.z))));
	m_gameObjects.at("player2Paddle")->addComponent<GE::RigidBody>(GE::kRigidBody);
	rigidBody = m_gameObjects.at("player2Paddle")->getComponentShared<GE::RigidBody>(GE::kRigidBody);
	rigidBody->createRigidBody(collisionShape, transform->getPosition(), 1.0f);
	rigidBody->getRigidBody()->setAngularFactor(btVector3(0, 0, 0));
	rigidBody->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);

	// goals
	transform = m_gameObjects.at("player1Goal")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(20.0f, 20.0f, 16.0f));
	transform->setPosition(glm::vec3(0.f, 16.0f, -28.f));
	transform->setRotation(glm::vec3(90.0f, 0.0f, 0.0f));
	m_gameObjects.at("player1Goal")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("player1Goal")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_wallObject);
	meshRenderer->setTexture(m_texture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_cameraPlayer1);
	m_gameObjects.at("player1Goal")->addComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider = m_gameObjects.at("player1Goal")->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->setScale(transform->getScale());
	boxCollider->boundToObject(m_wallObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	aabbSize = glm::vec3(boxCollider->m_boundingBox.extents);
	m_gameObjects.at("player1Goal")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("player1Goal")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape->createShape(btBoxShape(btVector3(btScalar(aabbSize.x), btScalar(aabbSize.z), btScalar(aabbSize.y))));
	m_gameObjects.at("player1Goal")->addComponent<GE::RigidBody>(GE::kRigidBody);
	rigidBody = m_gameObjects.at("player1Goal")->getComponentShared<GE::RigidBody>(GE::kRigidBody);
	rigidBody->createRigidBody(collisionShape, transform->getPosition(), 0.0f);
	rigidBody->getRigidBody()->setCollisionFlags(rigidBody->getRigidBody()->getCollisionFlags() | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	transform = m_gameObjects.at("player2Goal")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(20.0f, 20.0f, 16.0f));
	transform->setPosition(glm::vec3(0.f, 16.0f, -108.f));
	transform->setRotation(glm::vec3(90.0f, 0.0f, 0.0f));
	m_gameObjects.at("player2Goal")->addComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer = m_gameObjects.at("player2Goal")->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_wallObject);
	meshRenderer->setTexture(m_texture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_cameraPlayer1);
	m_gameObjects.at("player2Goal")->addComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider = m_gameObjects.at("player2Goal")->getComponentShared<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->setScale(transform->getScale());
	boxCollider->boundToObject(m_wallObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	aabbSize = glm::vec3(boxCollider->m_boundingBox.extents);
	m_gameObjects.at("player2Goal")->addComponent<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape = m_gameObjects.at("player2Goal")->getComponentShared<GE::CollisionShape>(GE::kCollisionShape);
	collisionShape->createShape(btBoxShape(btVector3(btScalar(aabbSize.x), btScalar(aabbSize.z), btScalar(aabbSize.y))));
	m_gameObjects.at("player2Goal")->addComponent<GE::RigidBody>(GE::kRigidBody);
	rigidBody = m_gameObjects.at("player2Goal")->getComponentShared<GE::RigidBody>(GE::kRigidBody);
	rigidBody->createRigidBody(collisionShape, transform->getPosition(), 0.0f);
	rigidBody->getRigidBody()->setCollisionFlags(rigidBody->getRigidBody()->getCollisionFlags() | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	transform = m_gameObjects.at("light0")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setPosition(glm::vec3(0, 15, -21));
	m_gameObjects.at("light0")->addComponent<GE::Light>(GE::kLight);
	light = m_gameObjects.at("light0")->getComponentShared<GE::Light>(GE::kLight);
	light->setPosition(transform->getPosition());
	m_gameObjects.at("light0")->isActive(false); // this game objects is a light and not a mesh object, so we dont want to "draw" it

	transform = m_gameObjects.at("light1")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setPosition(glm::vec3(0, 15, -129));
	m_gameObjects.at("light1")->addComponent<GE::Light>(GE::kLight);
	light = m_gameObjects.at("light1")->getComponentShared<GE::Light>(GE::kLight);
	light->setPosition(transform->getPosition());
	m_gameObjects.at("light1")->isActive(false); // this game objects is a light and not a mesh object, so we dont want to "draw" it


	// ------------------- BULLET GAMEOBJECTS CONFIG ------------------- //
	// add rigidBody's to dynamics world
	// paddles
	m_dynamicsWorld->addRigidBody(m_gameObjects.at("player1Paddle")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get());
	m_dynamicsWorld->addRigidBody(m_gameObjects.at("player2Paddle")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get());

	// ball
	m_ballMaxSpeed = 300.0f;
	m_startingVelocity = btVector3(1, 0, 8);
	m_velocityDirection = m_startingVelocity;
	m_ballSpeed = btVector3(1, 1, 1);
	m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get()->setFriction(0.0f);
	m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody()->setLinearVelocity(m_velocityDirection);
	m_dynamicsWorld->addRigidBody(m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get());

	// walls
	m_gameObjects.at("wallBottom")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get()->setFriction(0.0f);
	m_gameObjects.at("wallLeft")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get()->setFriction(0.0f);
	m_gameObjects.at("wallTop")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get()->setFriction(0.0f);
	m_gameObjects.at("wallRight")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get()->setFriction(0.0f);
	m_dynamicsWorld->addRigidBody(m_gameObjects.at("wallBottom")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get());
	m_dynamicsWorld->addRigidBody(m_gameObjects.at("wallLeft")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get());
	m_dynamicsWorld->addRigidBody(m_gameObjects.at("wallTop")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get());
	m_dynamicsWorld->addRigidBody(m_gameObjects.at("wallRight")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get());

	// goals
	m_dynamicsWorld->addRigidBody(m_gameObjects.at("player1Goal")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get());
	m_dynamicsWorld->addRigidBody(m_gameObjects.at("player2Goal")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody().get());

	// ------------------- BULLET GAMEOBJECTS CONFIGED ------------------- //

	// which level to start on
	m_activeLevel = 0;
	m_player1Score = 0;
	m_player2Score = 0;
	m_paddleSpeed = 7.5f;
	m_checker = false;

	m_timer = mkShare<GEC::Timer>();
	m_timer->stop();

	// print to console
	instructions();
}

Application::~Application()
{
	// the order which these shared_ptr's are delete is important
	m_dynamicsWorld.reset();
	m_solver.reset();
	m_overlappingPairCache.reset();
	m_dispatcher.reset();
	m_collisionConfiguration.reset();
	m_gameObjects.clear();
	std::cout << "Application deleted\n";
}

void Application::update(float& dt)
{
	btTransform updateTransform;
	std::string collisionKeyA;
	std::string collisionKeyB;

	//------------------ input update start ------------------ //
	// update input
	m_input->update();
	prcoessInput();

	//------------------ input update end ------------------ //


	//------------------ bullet step start ------------------ //
	m_dynamicsWorld->stepSimulation(1.f / 30.f, 10);
	
	int overlaps = overlappingObjectsPairsCount();
	bool player1Scored = false;
	bool player2Scored = false;
	
	// handle overlapping objects, if there are any
	for (int i = 0; i < overlaps; i++)
	{
		// get a pair of overlapping objects
		btVector3  collisionNormal = getOverlappingGameObjects(collisionKeyA, collisionKeyB, i);
		
		// if both keys are no empty, perform collision response logic
		if (!collisionKeyA.empty() && !collisionKeyB.empty())
		{	
			if (collisionKeyA == "ball" && !m_checker || collisionKeyB == "ball" && !m_checker)
			{
				// goals
				if (collisionKeyA == "player1Goal" && !m_checker || collisionKeyB == "player1Goal" && !m_checker)
				{
					m_checker = true;
					m_player2Score++;
					m_velocityDirection = m_startingVelocity;
					std::cout << "Player 2 Scores, their current score: " << m_player2Score << std::endl;
				
					shared<GE::Transform> transform = m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform);
					transform->setPosition(glm::vec3(-2.0f, 10.0f, -55.0f));
					shared<GE::RigidBody> rigidBody = m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody);
				
					// reseting ball position based on: http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?t=6252 [accessed 30/3/2017]
					btTransform reset = rigidBody->getRigidBody()->getCenterOfMassTransform();
					reset.setOrigin(btVector3(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z));
					rigidBody->getRigidBody()->setCenterOfMassTransform(reset);
					m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody()->setLinearVelocity(m_startingVelocity); // moves towards player 1
					m_ballSpeed = btVector3(1, 1, 1);
					player2Scored = true;
				}
				
				if (collisionKeyA == "player2Goal" && !m_checker || collisionKeyB == "player2Goal" && !m_checker)
				{
					m_checker = true;
					m_player1Score++;
					m_velocityDirection = m_startingVelocity;
					std::cout << "Player 1 Scores, their current score: " << m_player1Score << std::endl;
				
					shared<GE::Transform> transform = m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform);
					transform->setPosition(glm::vec3(-2.0f, 10.0f, -55.0f));
					shared<GE::RigidBody> rigidBody = m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody);
				
					// reseting ball position based on: http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?t=6252 [accessed 30/3/2017]
					btTransform reset = rigidBody->getRigidBody()->getCenterOfMassTransform();
					reset.setOrigin(btVector3(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z));
					rigidBody->getRigidBody()->setCenterOfMassTransform(reset);
					btVector3 resetVelocity(m_startingVelocity);
					resetVelocity.setZ(-resetVelocity.getZ());
					m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody()->setLinearVelocity(resetVelocity); // moves towards player 2
					m_ballSpeed = btVector3(1, 1, 1);
					player1Scored = true;
				}

				// walls
				if (collisionNormal != btVector3(0, 0, 0))
				{
					btVector3 linVelocity = m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody()->getLinearVelocity();
	
					// walls
					if (collisionKeyA.find("wall") != std::string::npos || collisionKeyB.find("wall") != std::string::npos)
					{
						// reflection equation: https://www.gamedev.net/topic/615766-angle-of-reflection/ [accessed 30/03/2017]
						btVector3 direction = m_velocityDirection;
						btVector3 reflection = -2 * (direction.dot(collisionNormal)) * collisionNormal + direction;		
						m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody()->setLinearVelocity(reflection);
						m_velocityDirection = reflection;
						m_checker = true;
					}

					//paddles
					if (collisionKeyA.find("Paddle") != std::string::npos || collisionKeyB.find("Paddle") != std::string::npos)
					{
						// reflection equation: https://www.gamedev.net/topic/615766-angle-of-reflection/ [accessed 30/03/2017]
						btVector3 direction = m_velocityDirection;
						btVector3 reflection = -2 * (direction.dot(collisionNormal)) * collisionNormal + direction;
						m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody()->setLinearVelocity(reflection);
						m_velocityDirection = reflection;
						m_checker = true;
					}
				}

				// increases the speed of the ball every time the ball hits a wall or paddle
				if (m_checker)
				{
					float ballMag = glm::length(m_velocityDirection.dot(m_velocityDirection));
					if (ballMag <= m_ballMaxSpeed)
					{
						btVector3 tmp = m_ballSpeed;
						m_ballSpeed.setX(tmp.getX() + 1.0f * dt);
						m_ballSpeed.setY(tmp.getY() + 1.0f * dt);
						m_ballSpeed.setZ(tmp.getZ() + 1.0f * dt);
						m_velocityDirection *= m_ballSpeed;
					}
				}
			}
			else
				m_checker = false;
		}
	}
	//------------------ bullet step end ------------------ //

	// update Transform Component with changes from Bullet Engine for both paddles
	glm::vec3 glmOrigin;
	btTransform bttransform;

	m_gameObjects.at("player1Paddle")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getBodyWorldTransform(bttransform);
	glmOrigin = glm::vec3(bttransform.getOrigin().getX(), bttransform.getOrigin().getY(), bttransform.getOrigin().getZ());
	m_gameObjects.at("player1Paddle")->getComponentShared<GE::Transform>(GE::kTransform)->setPosition(glmOrigin);
	m_gameObjects.at("player2Paddle")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getBodyWorldTransform(bttransform);
	glmOrigin = glm::vec3(bttransform.getOrigin().getX(), bttransform.getOrigin().getY(), bttransform.getOrigin().getZ());
	m_gameObjects.at("player2Paddle")->getComponentShared<GE::Transform>(GE::kTransform)->setPosition(glmOrigin);

	// update Transform Component with changes from Bullet Engine for the ball
	m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getBodyWorldTransform(updateTransform);
	btVector3 origin = updateTransform.getOrigin();
	btVector3 rotation = updateTransform.getRotation().getAxis();

	// if no object collided
	if (overlaps == 0)
		m_checker = false;

	// changes the light by the a players goal to red, if a goal was scored vs them
	if (player1Scored)
	{
		m_timer->start();
		m_gameObjects.at("light1")->getComponentShared<GE::Light>(GE::kLight)->setColour(glm::vec3(1, 0, 0));
	}
	else if (player2Scored)
	{
		m_timer->start();
		m_gameObjects.at("light0")->getComponentShared<GE::Light>(GE::kLight)->setColour(glm::vec3(1, 0, 0));
	}

	// 1 second after the time started (or as close to it as possible) change the lights back to default colour
	if (m_timer->checkElapsedTimeMS() >= 1000.0f)
	{
		m_timer->reset();
		m_gameObjects.at("light0")->getComponentShared<GE::Light>(GE::kLight)->setColour(glm::vec3(1, 1, 1));
		m_gameObjects.at("light1")->getComponentShared<GE::Light>(GE::kLight)->setColour(glm::vec3(1, 1, 1));
	}

	// update ball position adn rotation
	glm::vec3 glmRotation = m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform)->getRotation();
	glmRotation.x += m_velocityDirection.getZ();
	glmRotation.y += m_velocityDirection.getY();
	glmRotation.z += m_velocityDirection.getX();
	glmOrigin = glm::vec3(origin.getX(), origin.getY(), origin.getZ());
	m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform)->setPosition(glmOrigin);
	m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform)->setRotation(glmRotation);

	// update the ball position on this frame as the last frame position
	m_pfPosition = btVector3(glmOrigin.x, glmOrigin.y, glmOrigin.z);
}

void Application::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(28.0f / 255.0f, 28.0f / 255.0f, 28.0f / 255.0f, 1.0f);

	// player 1 viewport
	glViewport(0, 0, (int)m_scrennSize.x, (int)m_scrennSize.y);

	// draw all GameObjects
	for (std::unordered_map<std::string, shared<GE::GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		// don't want goal visable so disable it
		if (it->first == "player1Goal")
			it->second->isActive(false);

		// set uniforms and draw
		if (it->second->isActive())
		{
			shared<GE::MeshRenderer> renderer = it->second->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
			shared<GE::Light> light0 = m_gameObjects.at("light0")->getComponentShared<GE::Light>(GE::kLight);
			shared<GE::Light> light1 = m_gameObjects.at("light1")->getComponentShared<GE::Light>(GE::kLight);
			renderer->setMainCamera(m_cameraPlayer1);
			renderer->m_shaderProgram.lock()->bind();
			renderer->m_shaderProgram.lock()->uniform3f("lights[0].position", light0->getPosition());
			renderer->m_shaderProgram.lock()->uniform3f("lights[1].position", light1->getPosition());
			renderer->m_shaderProgram.lock()->uniform3f("lights[0].colour", light0->getColour());
			renderer->m_shaderProgram.lock()->uniform3f("lights[1].colour", light1->getColour());
			renderer->m_shaderProgram.lock()->uniform1f("lights[0].intensity", light0->getIntensity());
			renderer->m_shaderProgram.lock()->uniform1f("lights[1].intensity", light1->getIntensity());


			if (it->first.find("wall") == 0)
				renderer->m_shaderProgram.lock()->uniform1f("uvTileScale", 2);
			else
				renderer->m_shaderProgram.lock()->uniform1f("uvTileScale", 1);
			renderer->m_shaderProgram.lock()->unbind();
			it->second->draw();
		}

		// re-enable
		if (it->first == "player1Goal")
			it->second->isActive(true);
	}


#if BULLET_DEBUG_DRAW == 1
	m_dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawAabb);
	m_debugDraw.setDebugCamera(m_cameraPlayer1);
	m_dynamicsWorld->debugDrawWorld();
#endif

	// player 2 viewport
	glViewport((int)m_scrennSize.x, 0, (int)m_scrennSize.x, (int)m_scrennSize.y);

	for (std::unordered_map<std::string, shared<GE::GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		// don't want goal visable so disable it
		if (it->first == "player2Goal")
			it->second->isActive(false);

		// set uniforms and draw
		if (it->second->isActive())
		{
			shared<GE::MeshRenderer> renderer = it->second->getComponentShared<GE::MeshRenderer>(GE::kMeshRenderer);
			shared<GE::Light> light0 = m_gameObjects.at("light0")->getComponentShared<GE::Light>(GE::kLight);
			shared<GE::Light> light1 = m_gameObjects.at("light1")->getComponentShared<GE::Light>(GE::kLight);
			renderer->setMainCamera(m_cameraPlayer2);
			renderer->m_shaderProgram.lock()->bind();
			renderer->m_shaderProgram.lock()->uniform3f("lights[0].position", light0->getPosition());
			renderer->m_shaderProgram.lock()->uniform3f("lights[1].position", light1->getPosition());
			renderer->m_shaderProgram.lock()->uniform3f("lights[0].colour", light0->getColour());
			renderer->m_shaderProgram.lock()->uniform3f("lights[1].colour", light1->getColour());
			renderer->m_shaderProgram.lock()->uniform1f("lights[0].intensity", light0->getIntensity());
			renderer->m_shaderProgram.lock()->uniform1f("lights[1].intensity", light1->getIntensity());

			if (it->first.find("wall") == 0)
				renderer->m_shaderProgram.lock()->uniform1f("uvTileScale", 2);
			else
				renderer->m_shaderProgram.lock()->uniform1f("uvTileScale", 1);
			renderer->m_shaderProgram.lock()->unbind();
			it->second->draw();
		}

		// re-enable
		if (it->first == "player2Goal")
			it->second->isActive(true);
	}

#if BULLET_DEBUG_DRAW == 1
	m_dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawAabb);
	m_debugDraw.setDebugCamera(m_cameraPlayer2);
	m_dynamicsWorld->debugDrawWorld();
#endif

	glutSwapBuffers();
}

// based upon: http://hamelot.io/programming/using-bullet-only-for-collision-detection/ [accessed 25/03/2017].
btVector3 Application::getOverlappingGameObjects(std::string& keyA, std::string& keyB, int pairNumber)
{
	// get the two objects that have collided
	btPersistentManifold* manifold = m_dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(pairNumber);
	const btCollisionObject* const objectA = manifold->getBody0();
	const btCollisionObject* const objectB = manifold->getBody1();
	btVector3 normalAtCollision(0, 0, 0);
	int contacts = manifold->getNumContacts();

	// for each contact point between the objects
	for (int j = 0; j < contacts; j++) 
	{
		btManifoldPoint& pt = manifold->getContactPoint(j);
		normalAtCollision = pt.m_normalWorldOnB;
	}

	// find which GameObject these two objects are
	for (std::unordered_map<std::string, shared<GE::GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		// gameObject is active else breaks once both keys are found
		if (it->second->isActive() && keyA.empty() || keyB.empty())
		{
			shared<GE::RigidBody> rbBody = it->second->getComponentShared<GE::RigidBody>(GE::kRigidBody);

			if (rbBody != NULL)
			{
				btTransform bttransform = rbBody->getRigidBody()->getWorldTransform();
				btVector3 oA = objectA->getWorldTransform().getOrigin();
				btVector3 oB = objectB->getWorldTransform().getOrigin();

				// which key matches this transform
				if (oA == bttransform.getOrigin())
					keyA = it->first;

				if (oB == bttransform.getOrigin())
					keyB = it->first;
			}
		}
		else
			break;
	}

	return normalAtCollision;
}

void Application::prcoessInput()
{
	bool movementAlright = false;

	// apply velocity to the the paddle
	shared<btRigidBody> paddle1 = m_gameObjects.at("player1Paddle")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody();
	if (m_input->getKeyHeld("movementVert") == MULTI_KEY_HIGHER)
	{
		// don't keep updating velocity if it's the same
		if (paddle1->getLinearVelocity().getY() == 0.0f)
		{
			paddle1->setLinearVelocity(btVector3(0, m_paddleSpeed, 0));
			movementAlright = true;
		}
	}
	// apply velocity to the the paddle
	if (m_input->getKeyHeld("movementVert") == MULTI_KEY_LOWER)
	{
		// don't keep updating velocity if it's the same
		if (paddle1->getLinearVelocity().getY() == 0.0f)
		{
			paddle1->setLinearVelocity(btVector3(0, -m_paddleSpeed, 0));
			movementAlright = true;
		}
	}
	// apply velocity to the the paddle
	if (m_input->getKeyHeld("movementVert") == MULTI_KEY_NONE)
	{
		// don't keep updating velocity if it's the same
		if (paddle1->getLinearVelocity().getY() != 0.0f)
			paddle1->setLinearVelocity(btVector3(0, 0, 0));
	}


	if (m_input->getKeyHeld("movementHoriz") == MULTI_KEY_HIGHER)
	{
		// don't keep updating velocity if it's the same
		if (paddle1->getLinearVelocity().getX() == 0.0f)
			if (movementAlright)
				paddle1->setLinearVelocity(btVector3(-m_paddleSpeed, paddle1->getLinearVelocity().getY(), 0));
			else
				paddle1->setLinearVelocity(btVector3(-m_paddleSpeed, 0, 0));
	}
	// apply velocity to the the paddle
	if (m_input->getKeyHeld("movementHoriz") == MULTI_KEY_LOWER)
	{
		// don't keep updating velocity if it's the same
		if (paddle1->getLinearVelocity().getX() == 0.0f)
			if (movementAlright)
				paddle1->setLinearVelocity(btVector3(m_paddleSpeed, paddle1->getLinearVelocity().getY(), 0));
			else
				paddle1->setLinearVelocity(btVector3(m_paddleSpeed, 0, 0));
	}
	// apply velocity to the the paddle
	if (m_input->getKeyHeld("movementHoriz") == MULTI_KEY_NONE)
	{
		// don't keep updating velocity if it's the same
		if (movementAlright)
			paddle1->setLinearVelocity(btVector3(0, paddle1->getLinearVelocity().getY(), 0));
		else
			if (paddle1->getLinearVelocity().getX() != 0.0f)
				paddle1->setLinearVelocity(btVector3(0, 0, 0));
	}

	movementAlright = false;
	shared<btRigidBody> paddle2 = m_gameObjects.at("player2Paddle")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody();
	if (m_input->getKeyHeld("movementVert2") == MULTI_KEY_HIGHER)
	{
		// don't keep updating velocity if it's the same
		if (paddle2->getLinearVelocity().getY() == 0.0f)
		{
			paddle2->setLinearVelocity(btVector3(0, m_paddleSpeed, 0));
			movementAlright = true;
		}
	}
	// apply velocity to the the paddle
	if (m_input->getKeyHeld("movementVert2") == MULTI_KEY_LOWER)
	{
		// don't keep updating velocity if it's the same
		if (paddle2->getLinearVelocity().getY() == 0.0f)
		{
			paddle2->setLinearVelocity(btVector3(0, -m_paddleSpeed, 0));
			movementAlright = true;
		}
	}
	// apply velocity to the the paddle
	if (m_input->getKeyHeld("movementVert2") == MULTI_KEY_NONE)
	{
		// don't keep updating velocity if it's the same
		if (paddle2->getLinearVelocity().getY() != 0.0f)
			paddle2->setLinearVelocity(btVector3(0, 0, 0));
	}

	if (m_input->getKeyHeld("movementHoriz2") == MULTI_KEY_HIGHER)
	{
		// don't keep updating velocity if it's the same
		if (paddle2->getLinearVelocity().getX() == 0.0f)
			if (movementAlright)
				paddle2->setLinearVelocity(btVector3(m_paddleSpeed, paddle2->getLinearVelocity().getY(), 0));
			else
				paddle2->setLinearVelocity(btVector3(m_paddleSpeed, 0, 0));
	}
	// apply velocity to the the paddle
	if (m_input->getKeyHeld("movementHoriz2") == MULTI_KEY_LOWER)
	{
		// don't keep updating velocity if it's the same
		if (paddle2->getLinearVelocity().getX() == 0.0f)
			if (movementAlright)
				paddle2->setLinearVelocity(btVector3(-m_paddleSpeed, paddle2->getLinearVelocity().getY(), 0));
			else
				paddle2->setLinearVelocity(btVector3(-m_paddleSpeed, 0, 0));
	}
	// apply velocity to the the paddle
	if (m_input->getKeyHeld("movementHoriz2") == MULTI_KEY_NONE)
	{
		// don't keep updating velocity if it's the same
		if (movementAlright)
			paddle2->setLinearVelocity(btVector3(0, paddle2->getLinearVelocity().getY(), 0));
		else
			if (paddle2->getLinearVelocity().getX() != 0.0f)
				paddle2->setLinearVelocity(btVector3(0, 0, 0));
	}

	if (m_input->getKeyDown("action"))
		ballReset();
}

void Application::ballReset()
{
	m_velocityDirection = m_startingVelocity;

	shared<GE::Transform> transform = m_gameObjects.at("ball")->getComponentShared<GE::Transform>(GE::kTransform);
	transform->setPosition(glm::vec3(-2.0f, 10.0f, -55.0f));
	shared<GE::RigidBody> rigidBody = m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody);

	btTransform reset = rigidBody->getRigidBody()->getCenterOfMassTransform();
	reset.setOrigin(btVector3(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z));
	rigidBody->getRigidBody()->setCenterOfMassTransform(reset);
	m_gameObjects.at("ball")->getComponentShared<GE::RigidBody>(GE::kRigidBody)->getRigidBody()->setLinearVelocity(m_startingVelocity); // moves towards player 1
	m_ballSpeed = btVector3(1, 1, 1);
}

void Application::instructions()
{
	// get all of the key we want
	GE::Input::Key p1MoveV = m_input->getKeyFromName("movementVert");
	GE::Input::Key p1MoveH = m_input->getKeyFromName("movementHoriz");
	GE::Input::Key p2MoveV = m_input->getKeyFromName("movementVert2");
	GE::Input::Key p2MoveH = m_input->getKeyFromName("movementHoriz2");
	GE::Input::Key reset = m_input->getKeyFromName("action");
	GE::Input::Key quit = m_input->getKeyFromName("quit");
	int quitKey = quit.keyBinding == ESC ? 27 : quit.keyBinding;

	// for multikeys extract the two values from them
	short p1MoveVLower, p1MoveVHigher;
	short p1MoveHLower, p1MoveHHigher;
	short p2MoveVLower, p2MoveVHigher;
	short p2MoveHLower, p2MoveHHigher;
	m_input->useMultiKey(p1MoveV, p1MoveVLower, p1MoveVHigher);
	m_input->useMultiKey(p1MoveH, p1MoveHLower, p1MoveHHigher);
	m_input->useMultiKey(p2MoveV, p2MoveVLower, p2MoveVHigher);
	m_input->useMultiKey(p2MoveH, p2MoveHLower, p2MoveHHigher);

	GE::consoleLog("--------INSTRUCTIONS--------");
	GE::consoleLog("Player 1 on the left, Player 2 on the right.\nMove your paddle to stop the ball of hitting your goal.\nScore points from scoring.");
	GE::consoleLog("--------CONTROLS--------");
	std::cout << "Player1 vertical movement: " << (char)p1MoveVLower << "/" << (char)p1MoveVHigher << std::endl;
	std::cout << "Player1 horizontal movement: " << (char)p1MoveHLower << "/" << (char)p1MoveHHigher << std::endl;
	std::cout << "Player2 vertical movement: " << (char)p2MoveVLower << "/" << (char)p2MoveVHigher << std::endl;
	std::cout << "Player2 horizontal movement: " << (char)p2MoveHLower << "/" << (char)p2MoveHHigher << std::endl;
	std::cout << "Ball reset: " << (char)reset.keyBinding << std::endl;
	quit.keyBinding == ESC ? GE::consoleLog("Quit game: ESC") : std::cout << "Ball reset: " << (char)quit.keyBinding << std::endl;
	GE::consoleLog("--------------------------------");
}

