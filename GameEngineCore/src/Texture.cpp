// Author  : Lewis Ward (i7212443)
// Program : 3D Render Engine
// Date    : 29/01/2016
#include "Texture.h"

namespace gl
{
	Texture::Texture(const char* filename, int channel, uint32_t textureID, uint32_t flags)
	{
		m_count = 1;
		m_id = SOIL_load_OGL_texture(filename, channel, textureID, flags);

		if (!m_id)
		{
			printf("SOIL loading error: '%s'\n", SOIL_last_result());
		}
	}

	Texture::Texture(int number, GLenum type, const textureDesc& desc, const GLvoid* data)
	{
		m_count = number;
		glGenTextures(m_count, &m_id);
		glBindTexture(type, m_id);
		glTexImage2D(type, desc.level, desc.internalFormat, desc.width, desc.height, desc.border, desc.format, desc.type, data);
		glTexParameteri(type, desc.paramNameA, desc.texParamA);
		glTexParameteri(type, desc.paramNameB, desc.texParamB);
		glBindTexture(type, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(m_count, &m_id);
	}

	void Texture::bind(const int& slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::parameteri(const GLenum& target, const GLenum& paramName, const int32_t & param)
	{
		glTexParameteri(target, paramName, param);
	}

}; ///< end of namespace