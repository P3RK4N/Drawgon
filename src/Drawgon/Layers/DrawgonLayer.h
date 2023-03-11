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
		
		DRAWGON_CONSOLE

	public:
		DrawgonLayer() {}			//TODO: Make this accesible only to startup class. UPDATE: Why?
		~DrawgonLayer() {}

	private:
		Project m_Project			= {};
		Ref<Scene> m_CurrentScene	= DRAWGON_CURRENT_SCENE;

		//Ref<Mesh> m_FramebufferFrameMesh = nullptr;

	private:
		void loadProjectFromDisk();
		//TODO: loadProjectFromDisk2 -> binary exported data
		void createProjectOnDisk();
	};
}