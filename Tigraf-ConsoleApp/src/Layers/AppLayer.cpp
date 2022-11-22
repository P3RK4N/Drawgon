#include "AppLayer.h"

namespace Tigraf
{
	struct ColoredVertex
	{
		glm::vec3 pos{ 0,0,0 };
		glm::vec3 col{ 0,0,0 };
	};

	void AppLayer::init()
	{
		std::vector<ColoredVertex> triangleVertices;
		triangleVertices.push_back({{ 0.0f, 1.0f, 1.0f} , {1.0f, 0.0f, 0.0f} });
		triangleVertices.push_back({{ -1.0f, 0.0f, 0.0f} , {0.0f, 1.0f, 0.0f} });
		triangleVertices.push_back({{ 1.0f, -1.0f, 0.0f} , {0.0f, 0.0f, 1.0f} });
		std::vector<uint32_t> triangleIndices;
		triangleIndices.push_back(0);
		triangleIndices.push_back(2);
		triangleIndices.push_back(1);


		m_Triangle = VertexBuffer::create(triangleVertices.size(), sizeof(triangleVertices[0]), triangleVertices.data(), GL_DYNAMIC_STORAGE_BIT);
		Ref<IndexBuffer> indexBuffer = IndexBuffer::create(triangleIndices, GL_DYNAMIC_STORAGE_BIT);

		m_Triangle->pushVertexAttribute(VertexAttributeType::FLOAT3);
		m_Triangle->pushVertexAttribute(VertexAttributeType::FLOAT3);
		m_Triangle->setIndexBuffer(indexBuffer);

		m_Shader = createRef<glslShader>("resources\\shaders\\basic.glsl");
		m_Shader->bind();
	}

	void AppLayer::onUpdate(TimeStep ts)
	{
	
	}

	void AppLayer::onDraw()
	{
		Renderer::s_RendererAPI->drawIndexed(m_Triangle);
	}

	void AppLayer::shutdown()
	{
	
	}

	void AppLayer::onEvent(Event& event)
	{
	
	}
}