// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 25/10/2016
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
	// this function is based on the function I wrote for PGAG assignment 2 in Level I
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
		/// \brief  a single shader
		/// prama		char* soure filename
		/// \return	char* soure if successful, 0 if not
		//----------------------------------------------------------------------------------------------------------------------
		char* loadShader(const char* filename);
	
	private:
		char* m_source; ///< shader source
		uint32_t m_shader; ///< shader location 
	};
}; /// end of namespace
