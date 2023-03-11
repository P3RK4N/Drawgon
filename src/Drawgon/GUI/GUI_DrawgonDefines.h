#pragma once


#ifdef DRAWGON_EXPORT //DRAWGON GUI MACROS

	#define DRAWGON_ON_GUI_INIT()
	#define DRAWGON_ON_GUI_INIT_CUSTOM(filePath)
	#define DRAWGON_ON_GUI_SHUTDOWN()

	#define DRAWGON_GUI_RENDER_BEGIN()
	#define DRAWGON_GUI_RENDER_END()
	
	#define DRAWGON_DECLARE_MAIN_DOCKSPACE_ID
	#define DRAWGON_DECLARE_RELOAD_GUI

#else

	#include <Drawgon/GUI/GUI_GeneralDefines.h>

	//Platform Backend
	#include <backends/imgui_impl_sdl3.h>

	//Renderer backends
	#include <backends/imgui_impl_opengl3.h>
	//TODO: Add more!

	#define DRAWGON_ON_GUI_INIT() DRAWGON_ON_GUI_INIT_CUSTOM("imgui.ini")

	#define DRAWGON_ON_GUI_INIT_CUSTOM(filePath)																		\
		{																												\
			IMGUI_CHECKVERSION();																						\
			ImGui::CreateContext();																						\
			ImGui::LoadIniSettingsFromDisk(filePath);																	\
			ImGuiIO& io = ImGui::GetIO(); (void)io;																		\
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;														\
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;															\
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;															\
			io.ConfigWindowsMoveFromTitleBarOnly = true;																\
			ImGui::StyleColorsDark();																					\
			ImGui_ImplSDL3_InitForOpenGL																				\
			(																											\
				(SDL_Window*)Application::s_Instance->getWindow()->getNativeHandle(), 									\
				Application::s_Instance->getWindow()->getNativeContext()												\
			);																											\
			ImGui_ImplOpenGL3_Init("#version 460");																		\
			Application::s_Instance->getWindow()->setNativeEventCallback												\
			(																											\
				[](void* e)																								\
				{																										\
					ImGui_ImplSDL3_ProcessEvent((SDL_Event*)e);															\
					ImGuiIO& io = ImGui::GetIO();																		\
					return io.WantCaptureMouse;																			\
				}																										\
			);																											\
		}

	#define DRAWGON_GUI_RENDER_BEGIN()																				\
		ImGui_ImplOpenGL3_NewFrame();																				\
        ImGui_ImplSDL3_NewFrame();																					\
        ImGui::NewFrame();																							\
		ImGuiDockNodeFlags flags = ImGuiDockNodeFlags_PassthruCentralNode;											\
		DrawgonLayer::s_DockspaceID = ImGui::DockSpaceOverViewport(nullptr, flags);

	#define DRAWGON_GUI_RENDER_END()																					\
		{																												\
			ImGuiIO& io = ImGui::GetIO();																				\
			auto&[x,y] = Application::s_Instance->getWindow()->getSize();												\
			io.DisplaySize = ImVec2((float)x, (float)y);																\
			ImGui::Render();																							\
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());														\
			if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)														\
			{																											\
				ImGui::UpdatePlatformWindows();																			\
				ImGui::RenderPlatformWindowsDefault();																	\
				Application::s_Instance->getWindow()->makeCurrent();													\
			}																											\
		}

	#define DRAWGON_ON_GUI_SHUTDOWN()																				\
		ImGui_ImplOpenGL3_Shutdown();																				\
		ImGui_ImplSDL3_Shutdown();																					\
		ImGui::DestroyContext();					

	#define DRAWGON_DECLARE_RELOAD_GUI																					\
		private:																										\
			bool m_ShouldReloadGUI = false;																				\
			std::filesystem::path m_GUIFilePath = "imgui.ini";															\
			void reloadGUI();

#endif //DRAWGON GUI MACROS


#ifdef DRAWGON_EXPORT //CONSOLE WINDOW MACROS

	#define DRAWGON_CONSOLE

#else

	#include "Drawgon/Console/Console.h"

	#define DRAWGON_CONSOLE									\
		public:												\
			Ref<Console> m_Console = createRef<Console>();

#endif //CONSOLE WINDOW MACROS

#ifdef DRAWGON_EXPORT //MAIN MENU BAR MACROS

	#define DRAWGON_WINDOW_CHECKBOX(window)

#else

	#define	DRAWGON_WINDOW_CHECKBOX(window, name)				\
		{														\
				bool visible = window->isVisible();				\
				ImGui::Checkbox(name, &visible);				\
				window->setVisible(visible);					\
		}

#endif //MAIN MENU BAR MACROS

#ifdef DRAWGON_EXPORT //CURRENT SCENE MACROS

	//TODO: Needs precompiled version
	//#define  DRAWGON_STARTING_SCENE 
	//This takes the value from precompiled macro 
	#define DRAWGON_CURRENT_SCENE DRAWGON_STARTING_SCENE

#else

	#define DRAWGON_CURRENT_SCENE nullptr

#endif //CURRENT SCENE MACROS
