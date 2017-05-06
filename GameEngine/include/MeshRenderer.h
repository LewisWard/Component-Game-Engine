/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#pragma once
#include "Components.h"

namespace GE
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Renders a mesh
	//----------------------------------------------------------------------------------------------------------------------
	class MeshRenderer : public Component
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		MeshRenderer();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Destructor
		//----------------------------------------------------------------------------------------------------------------------
		~MeshRenderer();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  draws mesh using attached texture, shaders etc.
		//----------------------------------------------------------------------------------------------------------------------
		void onDraw();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  draws mesh, doesn't use textures etc.
		//----------------------------------------------------------------------------------------------------------------------
		void Draw();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  attach a texture
		/// prama shared<GEC::Texture> 
		//----------------------------------------------------------------------------------------------------------------------
		void setTexture(shared<GEC::Texture>& texture) { m_texture = texture; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief attach the mesh to render
		/// prama shared<GEC::ObjObject> 
		//----------------------------------------------------------------------------------------------------------------------
		void setMesh(shared<GEC::ObjObject>& mesh) { m_mesh = mesh; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  attach a shader program
		/// prama shared<GEC::Program> 
		//----------------------------------------------------------------------------------------------------------------------
		void setProgram(shared<GE::Program>& program) { m_shaderProgram = program; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set the screen size
		/// prama glm::vec2 
		//----------------------------------------------------------------------------------------------------------------------
		inline void setScreenRes(glm::vec2 screen) { m_screenRes = screen; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set the camera to use
		/// prama shared<GE::Camera>
		//----------------------------------------------------------------------------------------------------------------------
		void setMainCamera(shared<GE::Camera> mainCamera) { m_mainCamera = mainCamera; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  sets up the model, view and projection matrices for the shader uniforms
		/// prama glm::mat4 model
		//----------------------------------------------------------------------------------------------------------------------
		void setMVPUniforms(glm::mat4 M);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief set highlighting colour if a object is selected
		/// prama glm::vec3 colour
		/// prama bool if the object is selected or not
		//----------------------------------------------------------------------------------------------------------------------
		void setColourOnSelection(glm::vec3 colour, bool collision);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief set highlighting colour if a object has collided with another object
		/// prama glm::vec3 colour
		/// prama bool if a collision was detection
		//----------------------------------------------------------------------------------------------------------------------
		void setColourOnCollision(glm::vec3 colour, bool selected);

	public:
		weak<GE::Program> m_shaderProgram;
		weak<GE::Camera> m_mainCamera;
		weak<GEC::Texture> m_texture;
		weak<GEC::ObjObject> m_mesh;
		glm::vec2 m_screenRes;
		bool m_usingVertexBuffer;
	};
};
