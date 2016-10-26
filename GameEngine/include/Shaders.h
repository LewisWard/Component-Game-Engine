// Author  : Lewis Ward (i7212443)
// Program : 3D Render Engine
// Date    : 21/09/2015
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
	/// \parma	tag to print with error message
	//----------------------------------------------------------------------------------------------------------------------
	void getGLError(const char* tag);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  a single shader
	//----------------------------------------------------------------------------------------------------------------------
	class Shader
	{
	public:
		Shader(const char* source, kShaderType type);
		~Shader();

		inline uint32_t getShader() { return m_shader; }

		char* loadShader(const char* filename);
	
	private:
		char* m_source; ///< shader source
		uint32_t m_shader; ///< shader location 

	};

}; /// end of namespace
