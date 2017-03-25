// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 25/10/2016
#include "Shaders.h"

namespace GE
{
	void getGLError(const char* file)
	{
		// get OpenGL error and print it to console
		switch (glGetError())
		{
		case GL_NO_ERROR: break;
		case GL_INVALID_ENUM: std::cout << file << " GL_INVALID_ENUM\n"; break;
		case GL_INVALID_VALUE: std::cout << file << " GL_INVALID_VALUE\n"; break;
		case GL_INVALID_OPERATION: std::cout << file << " GL_INVALID_OPERATION\n"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: std::cout << file << " GL_INVALID_FRAMEBUFFER_OPERATION\n"; break;
		case GL_OUT_OF_MEMORY: std::cout << file << " GL_OUT_OF_MEMORY\n"; break;
		case GL_STACK_UNDERFLOW: std::cout << file << " GL_STACK_UNDERFLOW\n"; break;
		case GL_STACK_OVERFLOW: std::cout << file << " GL_STACK_OVERFLOW\n"; break;
		}
	}

	Shader::Shader(const char* source, kShaderType type)
	{
		// load binary or text file
		// read in the source
		m_source = loadShader(source);

		// make sure something was returned
		if (m_source)
		{
			// create the shader type and it's source
			m_shader = glCreateShader(type);
			getGLError("Shader:CreateShader");
			glShaderSource(m_shader, 1, &m_source, NULL);
			getGLError("Shader:ShaderSource");

			// compile shader
			glCompileShader(m_shader);
			int32_t status = 0;
			glGetShaderiv(m_shader, GL_COMPILE_STATUS, &status);
			getGLError("Shader:CompileShader");

			// check it compiled ok
			int32_t length = 0;
			char errorBuffer[256];
			glGetShaderInfoLog(m_shader, 256, &length, errorBuffer);
			getGLError("Shader:CheckShader");

			// if failed to compile
			if (length)
			{
				// delete the shader print message
				glDeleteShader(m_shader);
				getGLError("Shader:Failed");
				m_shader = 0;
				std::printf("failed to create shader %s", errorBuffer);
			}
		}
		else
		{
			std::cout << "failed to create shader: couldn't find shader" << std::endl;
		}
	}


	Shader::~Shader()
	{
		glDeleteShader(m_shader);
		delete[] m_source;
		m_shader = 0;
	}

	char* Shader::loadShader(const char* filename)
	{
		// open the file
		std::FILE* fp = std::fopen(filename, "rb");

		// make sure file is ok
		if (fp)
		{
			// seek to the end of the file
			if (!std::fseek(fp, 0, SEEK_END))
			{
				// get the file size
				size_t size = std::ftell(fp);

				if (size)
				{
					// go to the start of the file
					if (!std::fseek(fp, 0, SEEK_SET))
					{
						// allocate memory for file content
						char* content = new char[size + 1];
						// read in file content
						std::fread(content, size, 1, fp);
						// terminate at the end of file ('\n')
						content[size] = 0;
						// close the file
						std::fclose(fp);
						return content;
					}
				}
			}
			// close the file if it failed somewhere
			std::fclose(fp);
		}
		return 0;
	}

}; /// end of namespace
