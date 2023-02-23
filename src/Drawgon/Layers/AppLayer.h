#pragma once

#include <Tigraf/Tigraf.h>

//#define DRAWGON_DIST

#ifdef DRAWGON_DIST

	#define GUI_INIT()

	#define DECLARE_ON_GUI_RENDER
	#define DEFINE_ON_GUI_RENDER()
	#define ON_GUI_RENDER()

#else

	//ImGui
	#include <imgui.h>
	
	//Platform Backend
	#include <backends/imgui_impl_sdl3.h>

	//Renderer backends
	#include <backends/imgui_impl_opengl3.h>
	//TODO: Add more!

	#define GUI_INIT()																	\
		ImGui::CreateContext();															\
		ImGui::StyleColorsDark();														\
		ImGui_ImplOpenGL3_Init();														\
		ImGui_ImplSDL3_InitForOpenGL													\
		(																				\
			(SDL_Window*)Application::s_Instance->getWindow()->getNativeHandle(), 		\
			Application::s_Instance->getWindow()->getNativeContext()					\
		);																				\
		Application::s_Instance->getWindow()->setNativeEventCallback					\
		(																				\
			[](void* e)																	\
			{																			\
				ImGui_ImplSDL3_ProcessEvent(e);											\
				return false;															\
			}																			\
		)

	#define DECLARE_ON_GUI_RENDER					\
		private:									\
			void onGuiRender();		

	#define DEFINE_ON_GUI_RENDER(func_body)			\
		void AppLayer::onGuiRender() func_body

	#define ON_GUI_RENDER()							\
		onGuiRender()

#endif

namespace Tigraf
{
	class AppLayer : public Layer
	{
		DECLARE_LAYER
		DECLARE_ON_GUI_RENDER

	public:
		AppLayer() {}
		~AppLayer() {}

	private:
		EVENT(onResize);

		Ref<Camera> m_EditorCamera = nullptr;
		Ref<Framebuffer> m_Framebuffer = nullptr;

		Ref<TextureCube> m_CubemapTexture = nullptr;

		Ref<Mesh> m_FloorMesh = nullptr;
		Ref<Mesh> m_CubemapMesh = nullptr;
		Ref<Mesh> m_FramebufferFrameMesh = nullptr;
	};
}