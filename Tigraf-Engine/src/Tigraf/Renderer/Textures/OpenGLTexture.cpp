#include "PCH.h"
#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Tigraf
{
	OpenGLTexture2D::OpenGLTexture2D(const char* filePath)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		int channels;

		stbi_set_flip_vertically_on_load(1);
		uint8_t* data = stbi_load(filePath, &m_Width, &m_Height, &channels, 0);

		GLenum internalFormat, dataFormat;

		if(channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
			m_TextureFormat = TextureFormat::RGB;
		}
		else
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
			m_TextureFormat = TextureFormat::RGBA;
		}

		glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

		m_TextureHandle = glad_glGetTextureHandleARB(m_TextureID);
	
		//TODO(P3RK4N): Remove
		glMakeTextureHandleResidentARB(m_TextureHandle);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	OpenGLTextureCube::OpenGLTextureCube(const char* filePath)
	{
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_TextureID);

		int channels;

		stbi_set_flip_vertically_on_load(1);
		uint8_t* data = stbi_load(filePath, &m_Width, &m_Height, &channels, 0);

		GLenum internalFormat, dataFormat;

		if(channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		else
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}

		glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

		m_TextureHandle = glad_glGetTextureHandleARB(m_TextureID);
	
		//TODO(P3RK4N): Remove
		glMakeTextureHandleResidentARB(m_TextureHandle);
	}

	OpenGLTextureCube::~OpenGLTextureCube()
	{
	}
}
