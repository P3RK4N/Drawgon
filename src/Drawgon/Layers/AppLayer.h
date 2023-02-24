#pragma once

#include <Tigraf/Tigraf.h>

//#define DRAWGON_DIST

#ifdef DRAWGON_DIST

	#define ON_GUI_INIT()
	#define ON_GUI_SHUTDOWN()

	#define DECLARE_ON_GUI_RENDER
	#define DEFINE_ON_GUI_RENDER()
	#define ON_GUI_RENDER()
	#define GUI_RENDER_BEGIN()
	#define GUI_RENDER_END()

#else

	//ImGui
	#include <imgui.h>
	
	//#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

	//Platform Backend
	#include <backends/imgui_impl_sdl3.h>

	//Renderer backends
	#include <backends/imgui_impl_opengl3.h>
	//TODO: Add more!

	#define ON_GUI_INIT()																\
		IMGUI_CHECKVERSION();															\
		ImGui::CreateContext();															\
		ImGuiIO& io = ImGui::GetIO(); (void)io;											\
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;							\
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;								\
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;								\
		ImGui::StyleColorsDark();														\
		ImGui_ImplSDL3_InitForOpenGL													\
		(																				\
			(SDL_Window*)Application::s_Instance->getWindow()->getNativeHandle(), 		\
			Application::s_Instance->getWindow()->getNativeContext()					\
		);																				\
		ImGui_ImplOpenGL3_Init("#version 460");											\
		Application::s_Instance->getWindow()->setNativeEventCallback					\
		(																				\
			[](void* e)																	\
			{																			\
				ImGui_ImplSDL3_ProcessEvent((SDL_Event*)e);								\
				return false;															\
			}																			\
		)

	#define DECLARE_ON_GUI_RENDER														\
		private:																		\
			void onGuiRender();		

	#define DEFINE_ON_GUI_RENDER(func_body)												\
		void AppLayer::onGuiRender() { func_body }

	#define ON_GUI_RENDER()																\
		onGuiRender()

	#define GUI_RENDER_BEGIN()															\
		ImGui_ImplOpenGL3_NewFrame();													\
        ImGui_ImplSDL3_NewFrame();														\
        ImGui::NewFrame();

	#define GUI_RENDER_END()															\
		ImGuiIO& io = ImGui::GetIO();													\
		auto&[x,y] = Application::s_Instance->getWindow()->getSize();					\
		io.DisplaySize = ImVec2((float)x, (float)y);									\
		ImGui::Render();																\
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());							\
		if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)							\
		{																				\
			ImGui::UpdatePlatformWindows();												\
			ImGui::RenderPlatformWindowsDefault();										\
			Application::s_Instance->getWindow()->makeCurrent();						\
		}
		

	#define ON_GUI_SHUTDOWN()															\
		ImGui_ImplOpenGL3_Shutdown();													\
		ImGui_ImplSDL3_Shutdown();														\
		ImGui::DestroyContext();					

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