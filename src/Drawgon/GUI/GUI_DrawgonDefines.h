#pragma once


#ifdef DRAWGON_EXPORT //DRAWGON GUI MACROS

	#define DRAWGON_ON_GUI_INIT()
	#define DRAWGON_ON_GUI_INIT_CUSTOM(filePath)
	#define DRAWGON_ON_GUI_SHUTDOWN()

	#define DRAWGON_GUI_RENDER_BEGIN()
	#define DRAWGON_GUI_RENDER_END()
	
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
			ImGuiIO& io = ImGui::GetIO();																				\
			ImGui::LoadIniSettingsFromDisk(filePath);																	\
			io.IniFilename = filePath;																					\
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
		ImGui::DockSpaceOverViewport(nullptr, flags);

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
			void reloadGUI();										

#endif //DRAWGON GUI MACROS


#ifdef DRAWGON_EXPORT //WINDOW MACROS

	#define DRAWGON_DECLARE_CONSOLE
	#define DRAWGON_ON_CONSOLE_INIT()

	#define DRAWGON_DECLARE_FILE_BROWSER
	#define DRAWGON_ON_FILE_BROWSER_INIT()

#else

	#include "Drawgon/Console/Console.h"
	#include "Drawgon/Browser/FileBrowser.h"

	#define DRAWGON_DECLARE_CONSOLE										\
		friend class Console;											\
		public:															\
			Ref<Console> m_Console = nullptr;

	#define DRAWGON_ON_CONSOLE_INIT()									\
		m_Console = createRef<Console>();

	#define DRAWGON_DECLARE_FILE_BROWSER								\
		friend class FileBrowser;										\
		private:														\
			Ref<FileBrowser> m_FileBrowser = nullptr;

	#define DRAWGON_ON_FILE_BROWSER_INIT()								\
		m_FileBrowser = createRef<FileBrowser>();

#endif //WINDOW MACROS
