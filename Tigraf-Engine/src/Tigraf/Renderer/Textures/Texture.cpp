#include "PCH.h"
#include "Texture.h"

#include "OpenGLTexture.h"

namespace Tigraf
{
	Ref<Texture2D> Texture2D::create(const char* filePath)
	{
		return createRef<OpenGLTexture2D>(filePath);
	}

	Ref<TextureCube> TextureCube::create(const char* filePath)
	{
		return createRef<OpenGLTextureCube>(filePath);
	}
}