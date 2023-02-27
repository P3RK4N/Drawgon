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
		DECLARE_LAYER
		DECLARE_ON_GUI_RENDER

	public:
		AppLayer() {}
		~AppLayer() {}

	private:

		Ref<Scene> m_CurrentScene = nullptr;

		Ref<Mesh> m_FramebufferFrameMesh = nullptr;
		Ref<TextureCube> m_CubemapTexture = nullptr;
	};
}