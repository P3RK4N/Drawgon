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
		RGBA
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

	public:
		static Ref<Texture2D> create(const char* filePath);

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
		static Ref<TextureCube> create(const char* filePath);

	protected:
		//Of each side
		int m_Width = 0;
		int m_Height = 0;
	};
}