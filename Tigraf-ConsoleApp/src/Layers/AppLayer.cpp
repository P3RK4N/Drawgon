#include "AppLayer.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace Tigraf
{
	struct ColoredVertex
	{
		glm::vec3 pos{ 0,0,0 };
		glm::vec3 col{ 0,0,0 };
	};

	struct Vertex
	{
		glm::vec3 pos{ 0, 0, 0 };
	};

	void AppLayer::init()
	{
		//TRIANGLE
		std::vector<ColoredVertex> triangleVertices;
		triangleVertices.push_back({{ 0.0f, 1.0f, 1.0f} , {1.0f, 0.0f, 0.0f} });
		triangleVertices.push_back({{ -1.0f, 0.0f, 0.0f} , {0.0f, 1.0f, 0.0f} });
		triangleVertices.push_back({{ 1.0f, -1.0f, 0.0f} , {0.0f, 0.0f, 1.0f} });
		std::vector<uint32_t> triangleIndices;
		triangleIndices.push_back(0);
		triangleIndices.push_back(2);
		triangleIndices.push_back(1);

		m_Triangle = VertexBuffer::create(triangleVertices.size(), sizeof(triangleVertices[0]), triangleVertices.data(), GL_DYNAMIC_STORAGE_BIT);
		Ref<IndexBuffer> triangleIB = IndexBuffer::create(triangleIndices, GL_DYNAMIC_STORAGE_BIT);
		m_Triangle->pushVertexAttribute(VertexAttributeType::FLOAT3);
		m_Triangle->pushVertexAttribute(VertexAttributeType::FLOAT3);
		m_Triangle->setIndexBuffer(triangleIB);

		m_TriangleShader = createRef<glslShader>("resources\\shaders\\basic.glsl");

		//FLOOR
		std::vector<Vertex> floorVertices;
		floorVertices.push_back({{ -1000, 0, -1000 }});
		floorVertices.push_back({{ 1000, 0, -1000 }});
		floorVertices.push_back({{ -1000, 0, 1000 }});
		floorVertices.push_back({{ 1000, 0, 1000 }});
		std::vector<uint32_t> floorIndices;
		floorIndices.emplace_back(0);
		floorIndices.emplace_back(2);
		floorIndices.emplace_back(1);
		floorIndices.emplace_back(2);
		floorIndices.emplace_back(3);
		floorIndices.emplace_back(1);

		m_Floor = VertexBuffer::create(floorVertices.size(), sizeof(floorVertices[0]), floorVertices.data(), GL_DYNAMIC_STORAGE_BIT);
		Ref<IndexBuffer> floorIB = IndexBuffer::create(floorIndices, GL_DYNAMIC_STORAGE_BIT);

		m_Floor->pushVertexAttribute(VertexAttributeType::FLOAT3);
		m_Floor->setIndexBuffer(floorIB);

		m_FloorShader = createRef<glslShader>("resources\\shaders\\floor.glsl");

		//EDITOR_CAMERA
		auto[x, y] = Application::s_Instance->getWindow()->getSize();
		m_EditorCamera = createRef<EditorCamera>(1.0f * x / y, 0.1f, 200.0f);
	}

	void AppLayer::onUpdate(const TimeStep& ts)
	{
		m_EditorCamera->onUpdate(ts);

		glm::vec3 camPos = m_EditorCamera->getPosition();
		camPos.y = 0.0f;
		m_FloorTransform = glm::translate(camPos);
	}

	void AppLayer::onDraw()
	{
		m_TriangleShader->setMat4(m_EditorCamera->getViewProjection(), "VP");
		m_FloorShader->setMat4(m_EditorCamera->getViewProjection(), "VP");
		m_FloorShader->setMat4(m_FloorTransform, "M");

		m_TriangleShader->bind();
		Renderer::s_RendererAPI->drawIndexed(m_Triangle);

		m_FloorShader->bind();
		Renderer::s_RendererAPI->drawIndexed(m_Floor);
	}

	void AppLayer::shutdown()
	{
	
	}

	bool AppLayer::onEvent(Event& event)
	{
		DISPATCH(EVENT_TYPE::RESIZE, event, onResize);
	}

	bool AppLayer::onResize(void* eventData)
	{
		ResizeData* data = (ResizeData*)eventData; 

		m_EditorCamera->setAspectRatio(1.0f * data->width / data->height);
		m_EditorCamera->recalculateViewProjection();

		return false; 
	}
}