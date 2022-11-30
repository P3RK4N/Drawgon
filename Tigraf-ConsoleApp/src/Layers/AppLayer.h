#pragma once
#include "Tigraf/Core/Application.h"
#include "Tigraf/Renderer/Camera/EditorCamera.h"

namespace Tigraf
{
	class AppLayer : public Layer
	{
		DECLARE_LAYER

	public:
		AppLayer() {}
		~AppLayer() {}

	protected:
		EVENT(onResize);

	private:
		Ref<VertexBuffer> m_Triangle = nullptr;
		Ref<glslShader> m_TriangleShader = nullptr;

		Ref<VertexBuffer> m_Floor = nullptr;
		Ref<glslShader> m_FloorShader = nullptr;
		glm::mat4 m_FloorTransform{};

		Ref<Camera> m_EditorCamera = nullptr;
	};
}