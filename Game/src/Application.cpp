// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#include "Application.h"
#include <string>

Application::Application()
{
	Configurations config;
	config.readINIFile(ENGINEASSETS"game.ini");
	std::string assetPath(ENGINEASSETS);

	m_input = mkShare<GE::Input::InputManager>();

	m_scrennSize.x = RES_LOW_X;
	m_scrennSize.y = RES_LOW_Y;
	onResize((int)m_scrennSize.x, (int)m_scrennSize.y);
	glViewport(0, 0, (int)m_scrennSize.x, (int)m_scrennSize.y);
	windowRename(std::string(config.data.windowTitle).c_str());


	m_texture = mkShare<GEC::Texture>(std::string(assetPath + config.data.texturePaths[0]).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
	m_sphereObject = mkShare<GEC::ObjObject>(std::string(assetPath + config.data.modelPaths[0]).c_str());
	m_cubeObject = mkShare<GEC::ObjObject>(std::string(assetPath + config.data.modelPaths[1]).c_str());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);

	m_camera = mkShare<GE::Camera>(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1.0f), m_scrennSize, 45.0f, 0.1f, 100.0f);

	GE::Shader vertexShader(std::string(assetPath + config.data.shaderPaths[0]).c_str(), kVertexShader);
	GE::Shader pixelShader(std::string(assetPath + config.data.shaderPaths[1]).c_str(), kPixelShader);
	m_shaderProgram = mkShare<GE::Program>(vertexShader, pixelShader);

	GE::Shader vertexShader2(std::string(assetPath + "shaders/collisionWireframe.vrt").c_str(), kVertexShader);
	GE::Shader pixelShader2(std::string(assetPath + "shaders/collisionWireframe.pix").c_str(), kPixelShader);
	m_shaderProgramCollision = mkShare<GE::Program>(vertexShader2, pixelShader2);

	m_gameObjects.push_back(mkShare<GE::GameObject>());
	m_gameObjects.push_back(mkShare<GE::GameObject>());
	m_gameObjects.push_back(mkShare<GE::GameObject>());
	m_gameObjects.push_back(mkShare<GE::GameObject>());
	m_gameObjects.push_back(mkShare<GE::GameObject>());

	GE::Transform* transform;
	GE::MeshRenderer* meshRenderer;
	GE::BoxCollider* boxCollider;
	GE::SphereCollider* sphereCollider;

	// CUBE
	transform = m_gameObjects.at(0)->getComponent<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f));
	transform->setPosition(glm::vec3(-5.0f, -2.0f, -21.0f));
	m_gameObjects.at(0)->addComponent<GE::MeshRenderer>();
	meshRenderer = m_gameObjects.at(0)->getComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_cubeObject);
	meshRenderer->setTexture(m_texture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_camera);
	m_gameObjects.at(0)->addComponent<GE::BoxCollider>();
	boxCollider = m_gameObjects.at(0)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->boundToObject(m_cubeObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	m_gameObjects.at(0)->setChild(m_gameObjects.at(1));

	// SPHERE
	transform = m_gameObjects.at(1)->getComponent<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f));
	transform->setPosition(glm::vec3(-8.0f, -3.0f, -20.0f));
	m_gameObjects.at(1)->addComponent<GE::MeshRenderer>();
	meshRenderer = m_gameObjects.at(1)->getComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_sphereObject);
	meshRenderer->setTexture(m_texture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_camera);
	m_gameObjects.at(1)->addComponent<GE::SphereCollider>();
	sphereCollider = m_gameObjects.at(1)->getComponent<GE::SphereCollider>(GE::kSphereCollider);
	sphereCollider->boundToObject(m_sphereObject);
	sphereCollider->setCenter(transform->getPosition());
	sphereCollider->setRadius(transform->getScale().x);

	// CUBE
	transform = m_gameObjects.at(2)->getComponent<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f));
	transform->setPosition(glm::vec3(3.0f, 0.0f, -20.0f));
	m_gameObjects.at(2)->addComponent<GE::MeshRenderer>();
	meshRenderer = m_gameObjects.at(2)->getComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_cubeObject);
	meshRenderer->setTexture(m_texture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_camera);
	m_gameObjects.at(2)->addComponent<GE::BoxCollider>();
	boxCollider = m_gameObjects.at(2)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->boundToObject(m_cubeObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);
	m_gameObjects.at(2)->setChild(m_gameObjects.at(3));
	
	// SPHERE
	transform = m_gameObjects.at(3)->getComponent<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f));
	transform->setPosition(glm::vec3(4.5f, 4.50f, -20.0f));
	m_gameObjects.at(3)->addComponent<GE::MeshRenderer>();
	meshRenderer = m_gameObjects.at(3)->getComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_sphereObject);
	meshRenderer->setTexture(m_texture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_camera);
	m_gameObjects.at(3)->addComponent<GE::SphereCollider>();
	sphereCollider = m_gameObjects.at(3)->getComponent<GE::SphereCollider>(GE::kSphereCollider);
	sphereCollider->boundToObject(m_sphereObject);
	sphereCollider->setCenter(transform->getPosition());
	sphereCollider->setRadius(transform->getScale().x);

	// SPHERE
	transform = m_gameObjects.at(4)->getComponent<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(1.0f));
	transform->setPosition(glm::vec3(0.0f, 0.0f, -20.0f));
	m_gameObjects.at(4)->addComponent<GE::MeshRenderer>();
	meshRenderer = m_gameObjects.at(4)->getComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_sphereObject);
	meshRenderer->setTexture(m_texture);
	meshRenderer->setProgram(m_shaderProgram);
	meshRenderer->setMainCamera(m_camera);
	m_gameObjects.at(4)->addComponent<GE::BoxCollider>();
	boxCollider = m_gameObjects.at(4)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->boundToObject(m_sphereObject);
	boxCollider->recomputeBounds(transform->getPosition());
	boxCollider->setScreenRes(m_scrennSize);

	
	m_gameObjects.at(0)->setSelected();

	m_screenMouse = mkShare<GE::Input::MouseConverter>(m_camera->getProjection(), m_camera->getView(), m_scrennSize);
}

Application::~Application()
{
	std::cout << "Application deleted\n";
}

void Application::update(float& dt)
{
	static float refreshDT = 0.0f;
	refreshDT += dt;

	GE::SphereCollider* sphereColliderA = m_gameObjects.at(0)->getComponent<GE::SphereCollider>(GE::kSphereCollider);;
	GE::SphereCollider* sphereColliderB = m_gameObjects.at(1)->getComponent<GE::SphereCollider>(GE::kSphereCollider);;

	// update input
	m_input->update();

	// cap how often you can change selection - make input update more accurate
	if (refreshDT >= 0.05f)
	{
		// select the next object 
		if (m_input->getKeyDown("action"))
		{
			for (size_t i = 0; i < m_gameObjects.size(); ++i)
			{
				if (m_gameObjects.at(i)->isSelected())
				{
					m_gameObjects.at(i)->unselected();

					// cycle back to the start if at the end of the vector
					if (i < m_gameObjects.size() - 1)
						m_gameObjects.at(i + 1)->setSelected();
					else
						m_gameObjects.at(0)->setSelected();

					printf("selected %d \n", i);
					break;
				}
			}
		}
		refreshDT = 0.0f;
	}

	// update GameObjects
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		if (m_gameObjects.at(i)->isActive())
		{
			if (m_gameObjects.at(i)->isSelected())
			{
				if (m_input->getKeyHeld("movementVert") == MULTI_KEY_HIGHER)
				{
					// get the current gameobject components
					GE::Transform* transform = m_gameObjects.at(i)->getComponent<GE::Transform>(GE::kTransform);
					GE::BoxCollider* boxCollider = m_gameObjects.at(i)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
					GE::SphereCollider* sphereCollider = m_gameObjects.at(i)->getComponent<GE::SphereCollider>(GE::kSphereCollider);

					// set movement speed
					glm::vec3 movement = glm::vec3(0, 2.0f, 0) * dt;
					bool collision = false;

					// loop over all gameojects in the scene
					for (size_t object = 0; object < m_gameObjects.size(); ++object)
					{
						// make sure we don't test this object vs itself (I think this wouldn't make a difference but just in case)
						// also make sure we have not just collided with a previous gameobject, if we did other objects not intersection will reset
						// the value to false so the collision isn't detected!
						if (object != i && !collision)
						{
							m_gameObjects.at(object)->hasCollided(collision);

							// get the components of the object we are going to test
							GE::Transform* objectTransform = m_gameObjects.at(object)->getComponent<GE::Transform>(GE::kTransform);
							GE::BoxCollider* objectBoxCollider = m_gameObjects.at(object)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
							GE::SphereCollider* objectSphereCollider = m_gameObjects.at(object)->getComponent<GE::SphereCollider>(GE::kSphereCollider);


							// AABB vs AABB test
							if (boxCollider != NULL && objectBoxCollider != NULL)
							{
								collision = boxCollider->collision(*objectBoxCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "AABB vs AABB - Result: " << collision << std::endl;
							}

							// Sphere vs AABB test
							// AABB's can only test vs Sphere so we need to work out which box collider is valid
							if (boxCollider != NULL && objectSphereCollider != NULL)
							{
								collision = boxCollider->collision(*objectSphereCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "Sphere vs AABB - Result: " << collision << std::endl;
							}
							else if (sphereCollider != NULL && objectBoxCollider != NULL)
							{
								collision = objectBoxCollider->collision(*sphereCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "Sphere vs AABB - Result: " << collision << std::endl;
							}

							// Sphere vs Sphere test
							if (sphereCollider != NULL && objectSphereCollider != NULL)
							{			
								collision = objectSphereCollider->collision(*sphereCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "Sphere vs Sphere - Result: " << collision << std::endl;
							}
						}
					}

					// update the position of the gameobject as no collision detected
					m_gameObjects.at(i)->translate(movement);

				}
				else if (m_input->getKeyHeld("movementVert") == MULTI_KEY_LOWER)
				{
					// get the current gameobject components
					GE::Transform* transform = m_gameObjects.at(i)->getComponent<GE::Transform>(GE::kTransform);
					GE::BoxCollider* boxCollider = m_gameObjects.at(i)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
					GE::SphereCollider* sphereCollider = m_gameObjects.at(i)->getComponent<GE::SphereCollider>(GE::kSphereCollider);

					// set movement speed
					glm::vec3 movement = glm::vec3(0, -2.0f, 0) * dt;
					bool collision = false;

					// loop over all gameojects in the scene
					for (size_t object = 0; object < m_gameObjects.size(); ++object)
					{
						// make sure we don't test this object vs itself (I think this wouldn't make a difference but just in case)
						// also make sure we have not just collided with a previous gameobject, if we did other objects not intersection will reset
						// the value to false so the collision isn't detected!
						if (object != i && !collision)
						{
							m_gameObjects.at(object)->hasCollided(collision);

							// get the components of the object we are going to test
							GE::Transform* objectTransform = m_gameObjects.at(object)->getComponent<GE::Transform>(GE::kTransform);
							GE::BoxCollider* objectBoxCollider = m_gameObjects.at(object)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
							GE::SphereCollider* objectSphereCollider = m_gameObjects.at(object)->getComponent<GE::SphereCollider>(GE::kSphereCollider);


							// AABB vs AABB test
							if (boxCollider != NULL && objectBoxCollider != NULL)
							{
								collision = boxCollider->collision(*objectBoxCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "AABB vs AABB - Result: " << collision << std::endl;
							}

							// Sphere vs AABB test
							// AABB's can only test vs Sphere so we need to work out which box collider is valid
							if (boxCollider != NULL && objectSphereCollider != NULL)
							{
								collision = boxCollider->collision(*objectSphereCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "Sphere vs AABB - Result: " << collision << std::endl;
							}
							else if (sphereCollider != NULL && objectBoxCollider != NULL)
							{
								collision = objectBoxCollider->collision(*sphereCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "Sphere vs AABB - Result: " << collision << std::endl;
							}

							// Sphere vs Sphere test
							if (sphereCollider != NULL && objectSphereCollider != NULL)
							{
								collision = objectSphereCollider->collision(*sphereCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "Sphere vs Sphere - Result: " << collision << std::endl;
							}
						}
					}

					// update the position of the gameobject as no collision detected
					m_gameObjects.at(i)->translate(movement);
				}
				else if (m_input->getKeyHeld("movementHoriz") == MULTI_KEY_HIGHER)
				{
					// get the current gameobject components
					GE::Transform* transform = m_gameObjects.at(i)->getComponent<GE::Transform>(GE::kTransform);
					GE::BoxCollider* boxCollider = m_gameObjects.at(i)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
					GE::SphereCollider* sphereCollider = m_gameObjects.at(i)->getComponent<GE::SphereCollider>(GE::kSphereCollider);

					// set movement speed
					glm::vec3 movement = glm::vec3(-2.0f, 0.0f, 0) * dt;
					bool collision = false;

					// loop over all gameojects in the scene
					for (size_t object = 0; object < m_gameObjects.size(); ++object)
					{
						// make sure we don't test this object vs itself (I think this wouldn't make a difference but just in case)
						// also make sure we have not just collided with a previous gameobject, if we did other objects not intersection will reset
						// the value to false so the collision isn't detected!
						if (object != i && !collision)
						{
							m_gameObjects.at(object)->hasCollided(collision);

							// get the components of the object we are going to test
							GE::Transform* objectTransform = m_gameObjects.at(object)->getComponent<GE::Transform>(GE::kTransform);
							GE::BoxCollider* objectBoxCollider = m_gameObjects.at(object)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
							GE::SphereCollider* objectSphereCollider = m_gameObjects.at(object)->getComponent<GE::SphereCollider>(GE::kSphereCollider);


							// AABB vs AABB test
							if (boxCollider != NULL && objectBoxCollider != NULL)
							{
								collision = boxCollider->collision(*objectBoxCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "AABB vs AABB - Result: " << collision << std::endl;
							}

							// Sphere vs AABB test
							// AABB's can only test vs Sphere so we need to work out which box collider is valid
							if (boxCollider != NULL && objectSphereCollider != NULL)
							{
								collision = boxCollider->collision(*objectSphereCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "Sphere vs AABB - Result: " << collision << std::endl;
							}
							else if (sphereCollider != NULL && objectBoxCollider != NULL)
							{
								collision = objectBoxCollider->collision(*sphereCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "Sphere vs AABB - Result: " << collision << std::endl;
							}

							// Sphere vs Sphere test
							if (sphereCollider != NULL && objectSphereCollider != NULL)
							{
								collision = objectSphereCollider->collision(*sphereCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "Sphere vs Sphere - Result: " << collision << std::endl;
							}
						}
					}

					// update the position of the gameobject as no collision detected
					m_gameObjects.at(i)->translate(movement);

				}
				else if (m_input->getKeyHeld("movementHoriz") == MULTI_KEY_LOWER)
				{
					// get the current gameobject components
					GE::Transform* transform = m_gameObjects.at(i)->getComponent<GE::Transform>(GE::kTransform);
					GE::BoxCollider* boxCollider = m_gameObjects.at(i)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
					GE::SphereCollider* sphereCollider = m_gameObjects.at(i)->getComponent<GE::SphereCollider>(GE::kSphereCollider);

					// set movement speed
					glm::vec3 movement = glm::vec3(2.0f, 0.0f, 0) * dt;
					bool collision = false;

					// loop over all gameojects in the scene
					for (size_t object = 0; object < m_gameObjects.size(); ++object)
					{

						// make sure we don't test this object vs itself (I think this wouldn't make a difference but just in case)
						if (object != i && !collision)
						{
							m_gameObjects.at(object)->hasCollided(collision);

							// get the components of the object we are going to test
							GE::Transform* objectTransform = m_gameObjects.at(object)->getComponent<GE::Transform>(GE::kTransform);
							GE::BoxCollider* objectBoxCollider = m_gameObjects.at(object)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
							GE::SphereCollider* objectSphereCollider = m_gameObjects.at(object)->getComponent<GE::SphereCollider>(GE::kSphereCollider);


							// AABB vs AABB test
							if (boxCollider != NULL && objectBoxCollider != NULL)
							{
								collision = boxCollider->collision(*objectBoxCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "AABB vs AABB - Result: " << collision << std::endl;
							}

							// Sphere vs AABB test
							// AABB's can only test vs Sphere so we need to work out which box collider is valid
							if (boxCollider != NULL && objectSphereCollider != NULL)
							{
								collision = boxCollider->collision(*objectSphereCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "Sphere vs AABB - Result: " << collision << std::endl;
							}
							else if (sphereCollider != NULL && objectBoxCollider != NULL)
							{
								collision = objectBoxCollider->collision(*sphereCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "Sphere vs AABB - Result: " << collision << std::endl;
							}

							// Sphere vs Sphere test
							if (sphereCollider != NULL && objectSphereCollider != NULL)
							{
								collision = objectSphereCollider->collision(*sphereCollider);
								m_gameObjects.at(i)->hasCollided(collision);
								std::cout << "Sphere vs Sphere - Result: " << collision << std::endl;
							}
						}
					}

					m_gameObjects.at(i)->translate(movement);
				}
			}


			// active gameobject general update (doesn't have to be selected

			m_gameObjects.at(i)->setInput(m_input);
			m_gameObjects.at(i)->update(dt);
		}
	}
}

void Application::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(28.0f / 255.0f, 28.0f / 255.0f, 28.0f / 255.0f, 1.0f);

	if (m_input->getMouseDown(GE::Input::kLeftButton))
	{
		GE::SphereCollider* sphereCollider;
		GE::BoxCollider* boxCollider;
		GE::Transform* transform;
		GE::Input::Mouse mousePos = m_input->getMousePosition();

		m_screenMouse->update(mousePos);
		glm::vec3 mouseRay = m_screenMouse->getRay();
		glm::vec3 cameraOrigin(m_camera->getPosition());

		for (size_t object = 0; object < m_gameObjects.size(); object++)
		{
			if (m_gameObjects.at(object)->isActive())
			{
				transform = m_gameObjects.at(object)->getComponent<GE::Transform>(GE::kTransform);
				boxCollider = m_gameObjects.at(object)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
				sphereCollider = m_gameObjects.at(object)->getComponent<GE::SphereCollider>(GE::kSphereCollider);

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
					float tmin = glm::max(glm::max(glm::min(minX, maxX), glm::min(minY, maxY)), glm::min(minZ, minZ));
					float tmax = glm::min(glm::min(glm::max(minX, maxX), glm::max(minY, maxY)), glm::max(minZ, minZ));

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
							for (size_t i = 0; i < m_gameObjects.size(); ++i)
								if (m_gameObjects.at(i)->isSelected())
								{
									m_gameObjects.at(i)->unselected();
									break;
								}

							m_gameObjects.at(object)->setSelected();
							printf("selected %d \n", object);
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
					glm::vec3 rayDirection(mouseRay - cameraOrigin);
					rayDirection = glm::normalize(rayDirection);

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
						for (size_t i = 0; i < m_gameObjects.size(); ++i)
							if (m_gameObjects.at(i)->isSelected())
							{
								m_gameObjects.at(i)->unselected();
								break;
							}

						m_gameObjects.at(object)->setSelected();
						printf("selected %d \n", object);
					}
				}
			}
		}
	}

	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		if (m_gameObjects.at(i)->isActive())
			m_gameObjects.at(i)->draw();
	}

	glutSwapBuffers();
}
