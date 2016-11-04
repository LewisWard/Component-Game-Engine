// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 29/01/2016
#pragma once
#include "soil\SOIL.h"
#include "Window.h"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>

namespace GEC
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Texture Descriptor
	//----------------------------------------------------------------------------------------------------------------------
	struct textureDesc
	{
		int level = 0;
		int internalFormat;
		int width;
		int height;
		int border = 0;
		int texParamA = GL_LINEAR; ///< for glTexParameteri (i.e. GL_NEAREST or GL_LINEAR for GL_TEXTURE_MIN_FILTER or GL_TEXTURE_WRAP_S)
		int texParamB = GL_LINEAR; ///< for glTexParameteri (i.e. GL_NEAREST or GL_LINEAR for GL_TEXTURE_MAX_FILTER or GL_TEXTURE_WRAP_T)
		GLenum format;
		GLenum type = GL_UNSIGNED_BYTE; ///< i.e. GL_UNSIGNED_BYTE
		GLenum paramNameA = GL_TEXTURE_MIN_FILTER; ///< for glTexParameteri (i.e. GL_TEXTURE_MIN_FILTER or GL_TEXTURE_WRAP_S)
		GLenum paramNameB = GL_TEXTURE_MAG_FILTER; ///< for glTexParameteri (i.e. GL_TEXTURE_MAG_FILTER or GL_TEXTURE_WRAP_T)
	};

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Single standard texture, uses functions from the SOIL library. See SOIL.h for enum's
	//----------------------------------------------------------------------------------------------------------------------
	class Texture
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief Constructor, will create a glTexture.
		/// \parma char* filename
		/// \parma int  channels. SOIL_LOAD_AUTO | SOIL_LOAD_L | SOIL_LOAD_LA | SOIL_LOAD_RGB | SOIL_LOAD_RGBA
		/// \parma uint32_t texture ID, SOIL_CREATE_NEW_ID to make a new texture or pass ID to replace with new texture
		/// \parma uint32_t SOIL flags. SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | 
		///								SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | 
		///								SOIL_FLAG_DDS_LOAD_DIRECT
		//----------------------------------------------------------------------------------------------------------------------
		Texture(const char* filename, int channel, uint32_t textureID, uint32_t flags);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief Constructor, will create a glTexture.
		/// \parma int number of textures
		/// \parma GLenum type (i.e. GL_TEXTURE_2D)
		/// \parma textureDesc	Texture Descriptor
		/// \parma GLvoid* data
		//----------------------------------------------------------------------------------------------------------------------
		Texture(int number, GLenum type, const textureDesc& descriptor, const GLvoid* data);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief Single standard texture, uses functions from the SOIL library. See SOIL.h for enum's
		//----------------------------------------------------------------------------------------------------------------------
		~Texture();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief Binds this texture to a slot
		/// \parma int slot
		//----------------------------------------------------------------------------------------------------------------------
		void bind(const int& slot);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief Unbinds this texture
		//----------------------------------------------------------------------------------------------------------------------
		void unbind();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief Sets a texture parameter
		/// \parma GLenum target
		/// \parma GLenum param name
		/// \parma int32_t param
		//----------------------------------------------------------------------------------------------------------------------
		void parameteri(const GLenum& target, const GLenum& paramName, const int32_t& param);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Single standard texture, uses functions from the SOIL library. See SOIL.h for enum's
		/// \return uint32_t ID, if zero texture is not valid (i.e. failed to create)
		//----------------------------------------------------------------------------------------------------------------------
		inline uint32_t getID() { return m_id; }

	private:
		uint32_t m_id; ///< handle to the id
		int m_count; ///< the number of texture objects
	};


}; ///< end of namespace
