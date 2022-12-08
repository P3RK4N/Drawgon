#pragma once
#include "Tigraf/Core/Core.h"

namespace Tigraf
{
	enum class TextureFormat : int
	{
		None,

		R,
		RG,
		RGB,
		RGBA,

		RI,
		DepthStencil
	};

	class Texture
	{
	public:
		virtual ~Texture() {}

		uint64_t getTextureHandle() { return m_TextureHandle; }

	protected:
		uint64_t m_TextureHandle = 0;
	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() {}

		TextureFormat getTextureFormat() { return m_TextureFormat; }

	public:
		static Ref<Texture2D> create(const char* filePath);
		static Ref<Texture2D> create(TextureFormat textureFormat, uint32_t width, uint32_t height, const void* textureData);

	protected:
		int m_Width = 0;
		int m_Height = 0;
		TextureFormat m_TextureFormat = TextureFormat::None;
	};

	class TextureCube : public Texture
	{
	public:
		virtual ~TextureCube() {}

	public:
		/**
		* Creates Cubemap from 6 textures
		* 
		* @param baseFilePath contains directory path and file name (ex. folder1/workshop_front.jpg will be "folder1/workshop")
		* @param fileFormat is the format of picture (ex. workshop_front.jpg will be "jpg")
		* @return newly created cubemap texture pointer
		*/
		static Ref<TextureCube> create(const char* baseFilePath, const char* fileFormat);

		static const std::string s_CubeSides[6];

	protected:
		//Of each side
		int m_Width = 0;
		int m_Height = 0;
		TextureFormat m_TextureFormat = TextureFormat::None;
	};
}

