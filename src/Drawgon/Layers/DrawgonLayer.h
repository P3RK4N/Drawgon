#pragma once

//#define DRAWGON_EXPORT //TODO: Put at precompile state

#include <Tigraf/Tigraf.h>

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

	public:
		DrawgonLayer() {}			//TODO: Make this accesible only to startup class. UPDATE: Why?
		~DrawgonLayer() {}

	private:

		Ref<Scene> m_CurrentScene = nullptr;

		Ref<Mesh> m_FramebufferFrameMesh = nullptr;
		Ref<TextureCube> m_CubemapTexture = nullptr;
	};
}