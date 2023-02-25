#pragma once

#include <Tigraf/Tigraf.h>

using namespace Tigraf;

namespace Drawgon
{
	class Scene
	{
	public:

		Scene() {}
		Scene(const std::filesystem::path& filepath) {}
		Scene(const std::filesystem::path& fileDir, const char* filename) {}

		~Scene() {}

		void onLoad();
		void onUpdate();
		void onDraw();
		bool onEvent(Event& e);

		Ref<Texture2D> getColors() { return m_SceneFramebuffer->getColorTexture(0); }			//TODO: Maybe make it default to 0 implicitly
		Ref<Texture2D> getDepth() { return m_SceneFramebuffer->getDepthStencilTexture(); }

		/**
			Sets index of an cubemap texture which will be used
			\param textureCubeSlot is the slot which will shader sample cubemap from
		*/
		void setSkyboxIndex(TextureCubeSlot textureCubeSlot);
		const int getSkyboxIndex() { return m_SkyboxIndex; }

	protected:

		Ref<Framebuffer> m_SceneFramebuffer = nullptr;

		Ref<EditorCamera> m_SceneCamera = nullptr;

		
		Ref<Mesh> m_SceneSkybox = nullptr;
		int m_SkyboxIndex = TEXTURE_CUBE_0;

		Ref<Mesh> m_SceneGrid = nullptr;


	private:

		EVENT(onResize);
		//TODO: Key, Button, Focus... events

	};
}