#pragma once

#ifdef DRAWGON_EXPORT
	
	#define DRAWGON_DECLARE_ON_GUI_RENDER
	#define DRAWGON_ON_GUI_RENDER()

#else

	#include <imgui.h>
	#include <imgui_internal.h>

	#define DRAWGON_DECLARE_ON_GUI_RENDER					\
		private:											\
			void onGuiRender();

	#define DRAWGON_ON_GUI_RENDER(classInstance)			\
		classInstance->onGuiRender()

	#define DRAWGON_DECLARE_DOCKSPACE_ID					\
		public:												\
			static ImGuiID s_DockspaceID;

#endif