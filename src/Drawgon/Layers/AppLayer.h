#pragma once

//#define DRAWGON_DIST

#include <Tigraf/Tigraf.h>

#include "Drawgon/GUI/GUI.h"
#include "Drawgon/Scene.h"

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