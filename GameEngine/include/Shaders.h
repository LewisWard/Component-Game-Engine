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
#include "Window.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief  all the different types of shader (OpenGL)
//----------------------------------------------------------------------------------------------------------------------
enum kShaderType
{
	kVertexShader = GL_VERTEX_SHADER,
	kPixelShader = GL_FRAGMENT_SHADER, ///< in OpenGL terms this is the Fragment Shader
	kGeometryShader = GL_GEOMETRY_SHADER,
	kTessellationControllShader = GL_TESS_CONTROL_SHADER,
	kTessellationEvaluationShader = GL_TESS_EVALUATION_SHADER,
	kComputeShader = GL_COMPUTE_SHADER,
};

namespace GE
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  gets OpenGL error
	/// prama		tag to print with error message
	//----------------------------------------------------------------------------------------------------------------------
	void getGLError(const char* tag);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  a single shader
	//----------------------------------------------------------------------------------------------------------------------
	class Shader
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  constructor
		/// prama		char* soure filename
		/// prama		kShaderType shader type
		//----------------------------------------------------------------------------------------------------------------------
		Shader(const char* source, kShaderType type);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  destructor
		//----------------------------------------------------------------------------------------------------------------------
		~Shader();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  a single shader
		/// \return  uint32_t ID
		//----------------------------------------------------------------------------------------------------------------------
		inline uint32_t getShader() { return m_shader; }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  a single shader from file
		/// prama		char* soure filename
		/// \return	char* soure if successful, 0 if not
		//----------------------------------------------------------------------------------------------------------------------
		char* loadShader(const char* filename);
	
	private:
		char* m_source; ///< shader source
		uint32_t m_shader; ///< shader location 
	};
}; /// end of namespace
