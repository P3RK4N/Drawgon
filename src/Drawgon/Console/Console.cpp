#include "Console.h"

namespace Drawgon
{

#ifndef DRAWGON_EXPORT

	//Make it resize when there is free real estate
	void Console::onGuiRender()
	{
		if(!m_Visible) return;

		ImGui::Begin("Console", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		{
			m_ConsoleSink->drawToConsole();
		}
		ImGui::End();
	}

#endif

}