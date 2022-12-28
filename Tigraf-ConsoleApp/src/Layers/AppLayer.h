#pragma once
#include "Tigraf/Core/Application.h"
#include "Tigraf/Renderer/Camera/EditorCamera.h"
#include "Tigraf/Renderer/Textures/Texture.h"
#include "Tigraf/Renderer/Framebuffers/Framebuffer.h"
#include "Tigraf/Renderer/Mesh/Mesh.h"
#include "Tigraf/Renderer/Mesh/MeshPrimitives.h"

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
		Ref<Framebuffer> m_Framebuffer = nullptr;
		Ref<Camera> m_EditorCamera = nullptr;

		Ref<Texture2D> m_GigachadTexture = nullptr;
		Ref<TextureCube> m_CubemapTexture = nullptr;

		Ref<Mesh> m_FloorMesh = nullptr;
		Ref<Mesh> m_CubemapMesh = nullptr;
		Ref<Mesh> m_FramebufferFrameMesh = nullptr;

		Ref<Mesh> m_Plane2DMesh = nullptr;

		Ref<RWBuffer> m_RWBuffer = nullptr;
		Ref<RWTexture2D> m_RWTexture = nullptr;
		Ref<UniformBuffer> m_ImageBuffer = nullptr;
		Ref<Shader> m_ComputeShader = nullptr;
	};
}