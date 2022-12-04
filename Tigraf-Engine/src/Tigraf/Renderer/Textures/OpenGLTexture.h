#pragma once
#include "Texture.h"

#include <glad/glad.h>

namespace Tigraf
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const char* filePath);
		virtual ~OpenGLTexture2D();

	protected:
		GLuint m_TextureID = 0;
	};

	class OpenGLTextureCube : public TextureCube
	{
	public:
		OpenGLTextureCube(const char* filePath);
		virtual ~OpenGLTextureCube();

	protected:
		GLuint m_TextureID = 0;

	};
}
