// Author  : Lewis Ward (i7212443)
// Program : 3D Renderer
// Date    : 09/10/2016
#include "Application.h"
#include "glm\gtc\matrix_transform.hpp"
#include <string>

Application::Application()
{
	m_scrennSize.x = RES_LOW_X;
	m_scrennSize.y = RES_LOW_Y;
	onResize((int)m_scrennSize.x, (int)m_scrennSize.y);
	glViewport(0, 0, (int)m_scrennSize.x, (int)m_scrennSize.y);
	windowRename("Game Engine - Lewis Ward (i7212443)");

	m_texture = std::make_shared<GEC::Texture>(ENGINEASSETS"textures/wood.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
	m_sphereObject = std::make_shared<GEC::ObjObject>(ENGINEASSETS"models/sphere.obj", "models/");
	m_planeObject = std::make_shared<GEC::ObjObject>(ENGINEASSETS"models/plane.obj", "models/");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);

	GE::Shader vertexShader(ENGINEASSETS"shaders/shader.vrt", kVertexShader);
	GE::Shader pixelShader(ENGINEASSETS"shaders/shader.pix", kPixelShader);
	m_shaderProgram = std::make_shared<GE::Program>(vertexShader, pixelShader);
}

Application::~Application()
{
	std::cout << "Application deleted\n";
}

void Application::update(float& dt)
{

}

void Application::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(28.0f / 255.0f, 28.0f / 255.0f, 28.0f / 255.0f, 1.0f);

	
	glm::mat4 model(8.0f);
	model[3][3] = 1.0f;
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 5.0f, 25.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection = glm::perspective(45.0f, m_scrennSize.x / m_scrennSize.y, 0.1f, 100.0f);

	// draw start
	m_shaderProgram->bind();
	m_texture->bind(1);
	const float* offset = 0;

	// plane
	m_shaderProgram->uniform1i("texture", 1);
	m_shaderProgram->uniformMatrix4("modelMatrix", 1, model);
	m_shaderProgram->uniformMatrix4("viewMatrix", 1, view);
	m_shaderProgram->uniformMatrix4("projectionlMatrix", 1 , projection);
	glBindBuffer(GL_ARRAY_BUFFER, m_planeObject->getVertexBuffer()->getVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_planeObject->getVertexBuffer()->getIBO());
	offset = 0;
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexNormalUV), offset);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 3);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 6);
	glEnableVertexAttribArray(2);
	glDrawElements(GL_TRIANGLES, (GLsizei)m_planeObject->getIndicesCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// sphere
	model = glm::mat4(1.0f);
	m_shaderProgram->uniformMatrix4("modelMatrix", 1, model);
	glBindBuffer(GL_ARRAY_BUFFER, m_sphereObject->getVertexBuffer()->getVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_sphereObject->getVertexBuffer()->getIBO());
	offset = 0;
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexNormalUV), offset);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 3);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 6);
	glEnableVertexAttribArray(2);
	glDrawElements(GL_TRIANGLES, (GLsizei)m_sphereObject->getIndicesCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_texture->unbind();
	m_shaderProgram->unbind();
	// draw end
	


	glutSwapBuffers();
}
