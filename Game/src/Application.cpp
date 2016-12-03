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
	m_planeObject = mkShare<GEC::ObjObject>(std::string(assetPath + config.data.modelPaths[1]).c_str());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);

	GE::Shader vertexShader(std::string(assetPath + config.data.shaderPaths[0]).c_str(), kVertexShader);
	GE::Shader pixelShader(std::string(assetPath + config.data.shaderPaths[1]).c_str(), kPixelShader);
	m_shaderProgram = mkShare<GE::Program>(vertexShader, pixelShader);

	GE::Shader vertexShader2(std::string(assetPath + "shaders/collisionWireframe.vrt").c_str(), kVertexShader);
	GE::Shader pixelShader2(std::string(assetPath + "shaders/collisionWireframe.pix").c_str(), kPixelShader);
	m_shaderProgramCollision = mkShare<GE::Program>(vertexShader2, pixelShader2);

	m_gameObjects.push_back(mkShare<GE::GameObject>());
	m_gameObjects.push_back(mkShare<GE::GameObject>());

	GE::Transform* transform;
	GE::MeshRenderer* meshRenderer;
	GE::BoxCollider* boxCollider;

	transform = m_gameObjects.at(0)->getComponent<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(8.0f));
	m_gameObjects.at(0)->addComponent<GE::MeshRenderer>();
	meshRenderer = m_gameObjects.at(0)->getComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_planeObject);
	meshRenderer->setTexture(m_texture);
	meshRenderer->setProgram(m_shaderProgram);
	m_gameObjects.at(0)->addComponent<GE::BoxCollider>();
	boxCollider = m_gameObjects.at(0)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->boundToObject(m_planeObject);
	boxCollider->setScreenRes(m_scrennSize);

	transform = m_gameObjects.at(1)->getComponent<GE::Transform>(GE::kTransform);
	transform->setScale(glm::vec3(2.0f));
	transform->setPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	m_gameObjects.at(1)->addComponent<GE::MeshRenderer>();
	meshRenderer = m_gameObjects.at(1)->getComponent<GE::MeshRenderer>(GE::kMeshRenderer);
	meshRenderer->setScreenRes(m_scrennSize);
	meshRenderer->setMesh(m_sphereObject);
	meshRenderer->setTexture(m_texture);
	meshRenderer->setProgram(m_shaderProgram);
	m_gameObjects.at(1)->addComponent<GE::BoxCollider>();
	boxCollider = m_gameObjects.at(1)->getComponent<GE::BoxCollider>(GE::kBoxCollider);
	boxCollider->boundToObject(m_sphereObject);
	boxCollider->setScreenRes(m_scrennSize);

	m_gameObjects.at(1)->setSelected();
}

Application::~Application()
{
	std::cout << "Application deleted\n";
}

void Application::update(float& dt)
{
	// update input
	m_input->update();

	// select the next object 
	if (m_input->getKeyDown("action"))
	{
		int index = -1;
		for (size_t i = 0; i < m_gameObjects.size(); ++i)
		{
			if (m_gameObjects.at(i)->isSelected())
			{
				m_gameObjects.at(i)->unselected();

				// cycle back to the start if at the end of the vector
				if(i < m_gameObjects.size() - 1)
					m_gameObjects.at(i + 1)->setSelected();
				else
					m_gameObjects.at(0)->setSelected();

				printf("selected %d \n", i);
				break;
			}
		}
	}

	// update GameObjects
	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		if (m_gameObjects.at(i)->isSelected())
		{
			if (m_input->getKeyDown("movementVert"))
			{
				GE::Transform* transform = m_gameObjects.at(i)->getComponent<GE::Transform>(GE::kTransform);
				transform->translate(glm::vec3(0, 1.0f, 0) * dt);
			}
		}

		m_gameObjects.at(i)->setInput(m_input);
		m_gameObjects.at(i)->update(dt);
	}
}

void Application::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(28.0f / 255.0f, 28.0f / 255.0f, 28.0f / 255.0f, 1.0f);

#if RELEASEINBUILD 1
	GE::BoxCollider* boxCollider;
	GE::Transform* transform;

	transform = m_gameObjects.at(1)->getComponent<GE::Transform>(GE::kTransform);
	boxCollider = m_gameObjects.at(1)->getComponent<GE::BoxCollider>(GE::kBoxCollider);

	glm::mat4 model(transform->createTransform());
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 15.0f, 55.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection = glm::perspective(45.0f, m_scrennSize.x / m_scrennSize.y, 0.1f, 100.0f);
	GE::Input::Mouse mousePos = m_input->getMousePosition();


	float x = (2.0f * mousePos.x) / m_scrennSize.x - 1.0f;
	float y = 1.0f - (2.0f * mousePos.y) / m_scrennSize.y;
	float z = 1.0f;
	glm::vec3 ray_nds(x, y, z);
	glm::vec4 ray_clip(ray_nds.x, ray_nds.y, -1.0f, 1.0f);
	glm::vec4 ray_eye = glm::inverse(projection) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
	glm::vec3 ray_wor = (glm::inverse(model) * ray_eye);
	ray_wor = glm::normalize(ray_wor);
	//std::cout << ray_clip.x << " " << ray_clip.y << " " << ray_clip.z << std::endl;

	if (m_input->getMouseDown(GE::Input::kLeftButton))
	{
		std::cout << ray_wor.x << " " << ray_wor.y << " " << ray_wor.z << std::endl;

		if (boxCollider->m_boundingBox.contains(ray_wor))
			printf("HIT!\n");
	}

#endif

	for (size_t i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects.at(i)->draw();
	}

	glutSwapBuffers();
}
