// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 25/10/2016
#include "Program.h"

namespace GE
{
	Program::Program()
	{
		// create the program
		m_program = glCreateProgram();

		// display error if failed
		if (!m_program)
		{
			std::cout << "Failed to create program" << std::endl;
		}
	}

	Program::Program(Shader& shaderOne, Shader& shaderTwo)
	{
		m_program = glCreateProgram();

		// make sure program was created
		if (m_program)
		{
			// attach the shaders
			glAttachShader(m_program, shaderOne.getShader());
			glAttachShader(m_program, shaderTwo.getShader());
			getGLError("Program:AttachShader");

			// link the program
			glLinkProgram(m_program);
			getGLError("Program:LinkProgram");

			// check that the link was ok
			int32_t status = GL_FALSE;
			glGetProgramiv(m_program, GL_LINK_STATUS, &status);
			getGLError("Program:CheckLink");

			// display error is link failed
			if (status == GL_FALSE)
			{
				int32_t length;
				char errorBuffer[256];
				glGetProgramInfoLog(m_program, 256, &length, errorBuffer);
				getGLError("Program:Failed");
				std::printf("Failed to create program: \n%s", errorBuffer);
				glDeleteProgram(m_program);
				m_program = 0;
			}
		}

	}

	Program::~Program()
	{
		glDeleteProgram(m_program);
		m_program = 0;
	}

}; /// end of namespace
