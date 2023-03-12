#ifndef DRAWGON_EXPORT

#include "Console.h"

namespace Drawgon
{

	//Make it resize when there is free real estate
	void Console::onGuiRender()
	{
		ImGui::Begin("Console", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		{
			m_ConsoleSink->drawToConsole();
		}
		ImGui::End();
	}
}

#endif