#include "PCH.h"
#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Tigraf
{
	GLuint textureFormatToOpenGL(TextureFormat textureType)
	{
		switch(textureType)
		{
		case TextureFormat::R:
			return GL_RED;
		case TextureFormat::RG:
			return GL_RG;
		case TextureFormat::RGB:
			return GL_RGB;
		case TextureFormat::RGBA:
			return GL_RGBA;
		case TextureFormat::RI:
			return GL_RED_INTEGER;
		case TextureFormat::DepthStencil:
			return GL_DEPTH_STENCIL;
		}

		TIGRAF_ASSERT(0, "Invalid Texture Format");
	}

	GLuint OpenGLDataFormatToInternal(GLuint dataFormat)
	{
		switch(dataFormat)
		{
		case GL_RED:
			return GL_R8;
		case GL_RG:
			return GL_RG8;
		case GL_RGB:
			return GL_RGB8;
		case GL_RGBA:
			return GL_RGBA8;
		case GL_RED_INTEGER:
			return GL_R32I;
		case GL_DEPTH_STENCIL:
			return GL_DEPTH24_STENCIL8;
		}

		TIGRAF_ASSERT(0, "Invalid Data Format");
	}

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

	OpenGLTexture2D::OpenGLTexture2D(TextureFormat textureFormat, uint32_t width, uint32_t height, const void* textureData)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		GLenum internalFormat, dataFormat;
		dataFormat = textureFormatToOpenGL(textureFormat);
		internalFormat = OpenGLDataFormatToInternal(dataFormat);

		m_Width = width;
		m_Height = height;
		m_TextureFormat = textureFormat;

		glTextureStorage2D(m_TextureID, 1, internalFormat, width, height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if(textureData) glTextureSubImage2D(m_TextureID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, textureData);

		m_TextureHandle = glad_glGetTextureHandleARB(m_TextureID);

		//TODO(P3RK4N): Remove
		glMakeTextureHandleResidentARB(m_TextureHandle);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}


	OpenGLTextureCube::OpenGLTextureCube(const char* baseFilePath, const char* fileFormat)
	{
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_TextureID);

		GLenum internalFormat = 0;
		GLenum dataFormat = 0;
		int channels;
		stbi_set_flip_vertically_on_load(0);
		for(int i = 0; i < 6; i++)
		{
			std::string facePath = baseFilePath + std::string("_") + TextureCube::s_CubeSides[i] + std::string(".") + fileFormat;
			uint8_t* data = stbi_load(facePath.c_str(), &m_Width, &m_Height, &channels, 0);

			if(!internalFormat)
			{
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
			}

			glTextureSubImage3D(m_TextureID, 0, 0, 0, i, m_Width, m_Height, 1, dataFormat, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		};

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		m_TextureHandle = glad_glGetTextureHandleARB(m_TextureID);
	
		//TODO(P3RK4N): Remove
		glMakeTextureHandleResidentARB(m_TextureHandle);
	}

	OpenGLTextureCube::~OpenGLTextureCube()
	{
		glDeleteTextures(1, &m_TextureID);
	}
}
