#pragma once
#include <Tigraf/Tigraf.h>

//#define DRAWGON_EXPORT //TODO: Put at precompile state

#ifndef DRAWGON_EXPORT

#include "nfd.h"
#include "Drawgon/Project/Project.h"

#endif

#include "Drawgon/GUI/GUI_DrawgonDefines.h"
#include "Drawgon/Scene/Scene.h"

using namespace Tigraf;

namespace Drawgon	
{
	class DrawgonLayer : public Layer
	{
		TIGRAF_DECLARE_LAYER
		DRAWGON_DECLARE_ON_GUI_RENDER
		DRAWGON_DECLARE_DOCKSPACE_ID
		DRAWGON_CONSOLE
		DRAWGON_DECLARE_PROJECT

	public:
		DrawgonLayer() {}			//TODO: Make this accesible only to startup class. UPDATE: Why?
		~DrawgonLayer() {}

	private:

		Ref<Scene> m_CurrentScene = nullptr;

		Ref<Mesh> m_FramebufferFrameMesh = nullptr;
		Ref<TextureCube> m_CubemapTexture = nullptr;
	};
}