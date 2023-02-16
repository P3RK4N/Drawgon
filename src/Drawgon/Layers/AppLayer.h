#pragma once

#include <Tigraf/Tigraf.h>

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
		Ref<Camera> m_EditorCamera = nullptr;
		Ref<Framebuffer> m_Framebuffer = nullptr;

		Ref<TextureCube> m_CubemapTexture = nullptr;

		Ref<Mesh> m_FloorMesh = nullptr;
		Ref<Mesh> m_CubemapMesh = nullptr;
		Ref<Mesh> m_FramebufferFrameMesh = nullptr;
	};
}