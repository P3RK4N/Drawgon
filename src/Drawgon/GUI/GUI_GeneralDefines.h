#pragma once

#ifdef DRAWGON_EXPORT
	
	#define DECLARE_ON_GUI_RENDER
	#define DEFINE_ON_GUI_RENDER()
	#define ON_GUI_RENDER()

#else

	#include <imgui.h>

	#define DECLARE_ON_GUI_RENDER														\
		private:																		\
			void onGuiRender();

	#define ON_GUI_RENDER(classInstance)												\
		classInstance->onGuiRender()

#endif