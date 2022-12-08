#pragma once
#include "Tigraf/Core/Application.h"
#include "Tigraf/Renderer/Camera/EditorCamera.h"
#include "Tigraf/Renderer/Textures/Texture.h"
#include "Tigraf/Renderer/Framebuffers/Framebuffer.h"

namespace Tigraf
{
	class AppLayer : public Layer
	{
		DECLARE_LAYER

	public:
		AppLayer() {}
		~AppLayer() {}

	protected:
		EVENT(onResize);

	private:
		Ref<VertexBuffer> m_Floor = nullptr;
		Ref<glslShader> m_FloorShader = nullptr;
		glm::mat4 m_FloorTransform{};

		Ref<VertexBuffer> m_Cube = nullptr;
		Ref<glslShader> m_CubeShader = nullptr;
		glm::mat4 m_CubeTransform{};

		Ref<Camera> m_EditorCamera = nullptr;

		Ref<Texture2D> m_GigachadTexture = nullptr;
		Ref<TextureCube> m_CubemapTexture = nullptr;

		Ref<Framebuffer> m_Framebuffer = nullptr;
		Ref<VertexBuffer> m_FramebufferFrame = nullptr;
		Ref<glslShader> m_FramebufferShader = nullptr;
	};
}