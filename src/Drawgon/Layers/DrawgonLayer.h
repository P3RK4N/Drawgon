#pragma once
#include <Tigraf/Tigraf.h>

//#define DRAWGON_EXPORT //TODO: Put at precompile state

#ifndef DRAWGON_EXPORT

#include "nfd.h"

#endif

#include "Drawgon/GUI/GUI_DrawgonDefines.h"
#include "Drawgon/Project/Project.h"
#include "Drawgon/Scene/Scene.h"

using namespace Tigraf;

namespace Drawgon	
{
	class DrawgonLayer : public Layer
	{
		TIGRAF_DECLARE_LAYER
		DRAWGON_DECLARE_ON_GUI_RENDER
		DRAWGON_DECLARE_RELOAD_GUI
		
		DRAWGON_DECLARE_CONSOLE
		DRAWGON_DECLARE_FILE_BROWSER

	public:
		DrawgonLayer() {}			//TODO: Make this accesible only to startup class. UPDATE: Why?
		~DrawgonLayer() {}

	public:
		static DrawgonLayer* s_DrawgonLayer;

	private:
		Project m_Project			= {};
		Ref<Scene> m_CurrentScene	= nullptr;

		//Ref<Mesh> m_FramebufferFrameMesh = nullptr;

	private:
		//TODO: Move nfd to project?
		void loadProjectFromDisk();
		//TODO: loadProjectFromDisk2 -> binary exported data
		void createProjectOnDisk();
	};
}