#pragma once
#include "Tigraf/Core/Application.h"

namespace Tigraf
{
	class AppLayer : public Layer
	{
		DECLARE_LAYER

	public:
		AppLayer() {}
		~AppLayer() {}

			
	private:
		Ref<VertexBuffer> m_Triangle = nullptr;
		Ref<glslShader> m_Shader = nullptr;
	};
}