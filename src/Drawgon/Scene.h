#pragma once
#include "Drawgon/SceneData.h"

#include <Tigraf/Tigraf.h>

using namespace Tigraf;

namespace Drawgon
{
	class Scene
	{
	public:

		Scene();
		Scene(const std::filesystem::path& filepath);
		Scene(const std::filesystem::path& fileDir, const char* filename);

		~Scene() {}

		void onUpdate(const TimeStep& ts);
		void onDraw();
		bool onEvent(Event& e);

		void onPlay();
		void onPause();
		void onStop();

		Ref<Texture2D> getColors() { return m_SceneFramebuffer->getColorTexture(0); }			//TODO: Maybe make it default to 0 implicitly
		Ref<Texture2D> getDepth() { return m_SceneFramebuffer->getDepthStencilTexture(); }

		/**
			Sets index of an cubemap texture which will be used
			@param skyboxIndex is the index which will shader sample cubemap from. Default range is [0-19]
		*/
		void setSkyboxIndex(uint16_t skyboxIndex);
		const int getSkyboxIndex() { return m_SceneData.m_PerFrameData.SkyboxIndex; }

	protected:

		Ref<Framebuffer> m_SceneFramebuffer = nullptr;
		Ref<EditorCamera> m_SceneCamera = nullptr;

		SceneData m_SceneData{};

		Ref<Mesh> m_SceneSkybox = nullptr;
		Ref<Mesh> m_SceneGrid = nullptr;

	private:

		EVENT(onResize);
		//TODO: Key, Button, Focus... events

	};
}