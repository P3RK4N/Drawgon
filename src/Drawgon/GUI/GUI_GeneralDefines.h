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

	//TODO: Maybe remove, maybe make everything static
	#define DRAWGON_DECLARE_DOCKSPACE_ID					\
		public:												\
			static ImGuiID s_DockspaceID;

	#define DRAWGON_WINDOW_VISIBILITY(defaultVisibility)			\
		private:													\
			bool m_Visible = defaultVisibility;						\
		private:													\
			void setVisible(bool visible) { m_Visible = visible; }	\
			bool isVisible() { return m_Visible; }	

#endif