#include "Console.h"

namespace Drawgon
{

#ifndef DRAWGON_EXPORT

	void Console::onGuiRender()
	{
		if(!m_Visible) return;

		ImGui::Begin("Console");
		{
			m_ConsoleSink->drawToConsole();
		}
		ImGui::End();
	}

#endif

}