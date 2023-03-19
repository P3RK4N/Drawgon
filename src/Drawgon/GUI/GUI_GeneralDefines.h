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

namespace Drawgon
{
	static void centerNextPopup(float width, float height)
	{
		auto [cx,cy] = ImGui::GetMainViewport()->GetCenter();
		ImVec2 pos = { cx - width / 2.0f, cy - height / 2.0f };
		ImGui::SetNextWindowPos(pos);
		ImGui::SetNextWindowSize({ width, height });
	}

	//TODO: Add some prebuilt gui elements. (centered yes-no Popups...)
}

#endif