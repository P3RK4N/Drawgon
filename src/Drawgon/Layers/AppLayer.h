#pragma once

//#define DRAWGON_EXPORT //TODO: Put at precompile state

#include <Tigraf/Tigraf.h>

#include "Drawgon/GUI/GUI_LayerDefines.h"
#include "Drawgon/Scene/Scene.h"

using namespace Tigraf;

namespace Drawgon	
{
	class AppLayer : public Layer
	{
		TIGRAF_DECLARE_LAYER
		DRAWGON_DECLARE_ON_GUI_RENDER
		DRAWGON_DECLARE_DOCKSPACE_ID

	public:
		AppLayer() {}			//TODO: Make this accesible only to startup class
		~AppLayer() {}

	private:

		Ref<Scene> m_CurrentScene = nullptr;

		Ref<Mesh> m_FramebufferFrameMesh = nullptr;
		Ref<TextureCube> m_CubemapTexture = nullptr;
	};
}