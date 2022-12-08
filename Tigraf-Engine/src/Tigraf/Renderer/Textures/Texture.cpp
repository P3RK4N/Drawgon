#include "PCH.h"
#include "Texture.h"

#include "OpenGLTexture.h"

namespace Tigraf
{
	Ref<Texture2D> Texture2D::create(const char* filePath)
	{
		return createRef<OpenGLTexture2D>(filePath);
	}

	Ref<Texture2D> Texture2D::create(TextureFormat textureFormat, uint32_t width, uint32_t height, const void* data)
	{
		return createRef<OpenGLTexture2D>(textureFormat, width, height, data);
	}

	Ref<TextureCube> TextureCube::create(const char* baseFilePath, const char* fileFormat)
	{
		return createRef<OpenGLTextureCube>(baseFilePath, fileFormat);
	}

	const std::string TextureCube::s_CubeSides[6] =
	{
		"right",
		"left",
		"top",
		"bottom",
		"front",
		"back"
	};
}