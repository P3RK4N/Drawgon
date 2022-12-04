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

	struct CubeMapVertex
	{
		glm::vec3 pos{ 0, 0, 0 };
		glm::vec2 uv{ 0, 0 };
	};

	struct TextureBufferElement
	{
		uint64_t textureHandle = 0;
		uint64_t padding = 0;
	};

	void AppLayer::init()
	{
		//FLOOR
		std::vector<Vertex> floorVertices;
		floorVertices.push_back({{ -1000, 0, -1000 }});
		floorVertices.push_back({{ 1000, 0, -1000 }});
		floorVertices.push_back({{ -1000, 0, 1000 }});
		floorVertices.push_back({{ 1000, 0, 1000 }});
		std::vector<uint32_t> floorIndices = { 0,2,1, 2,3,1 };

		m_Floor = VertexBuffer::create(floorVertices.size(), sizeof(floorVertices[0]), floorVertices.data(), GL_DYNAMIC_STORAGE_BIT);
		Ref<IndexBuffer> floorIB = IndexBuffer::create(floorIndices, GL_DYNAMIC_STORAGE_BIT);

		m_Floor->pushVertexAttribute(VertexAttributeType::FLOAT3);
		m_Floor->setIndexBuffer(floorIB);

		m_FloorShader = createRef<glslShader>("resources\\shaders\\floor.glsl");

		//CUBE
		std::vector<CubeMapVertex> cubemapVertices;
		cubemapVertices.push_back({ { -100,-100,-100  }	, { 0.0f,	1.0f/3.0f }	});		//0		
		cubemapVertices.push_back({ { -100, 100, -100 }	, { 0.0f,	2.0f/3.0f }	});		//2		
		cubemapVertices.push_back({ { -100,-100,  100 }	, { 0.25f,	1.0f/3.0f }	});		//1		

		cubemapVertices.push_back({ { -100, 100, -100 }	, { 0.0f,	2.0f/3.0f }	});		//2		
		cubemapVertices.push_back({ { -100, 100,  100 }	, { 0.25f,	2.0f/3.0f }	});		//3		
		cubemapVertices.push_back({ { -100,-100,  100 }	, { 0.25f,	1.0f/3.0f }	});		//1		

		cubemapVertices.push_back({ { -100,-100,  100 }	, { 0.25f,	1.0f/3.0f }	});		//1		
		cubemapVertices.push_back({ { -100, 100,  100 }	, { 0.25f,	2.0f/3.0f }	});		//3		
		cubemapVertices.push_back({ {  100, -100, 100 }	, { 0.5f,	1.0f/3.0f }	});		//5		

		cubemapVertices.push_back({ { -100, 100,  100 }	, { 0.25f,	2.0f/3.0f }	});		//3		
		cubemapVertices.push_back({ {  100,	100,  100 }	, { 0.5f,	2.0f/3.0f }	});		//7
		cubemapVertices.push_back({ {  100, -100, 100 }	, { 0.5f,	1.0f/3.0f }	});		//5		

		cubemapVertices.push_back({ { -100,-100,-100  }	, { 0.25f,	0.0f }	});			//0		
		cubemapVertices.push_back({ { -100,-100,  100 }	, { 0.25f,	1.0f/3.0f }	});		//1
		cubemapVertices.push_back({ {  100, -100,-100 }	, { 0.5f,	0.0f }	});			//4		

		cubemapVertices.push_back({ { -100,-100,  100 }	, { 0.25f,	1.0f/3.0f }	});		//1
		cubemapVertices.push_back({ {  100, -100, 100 }	, { 0.5f,	1.0f/3.0f }	});		//5		
		cubemapVertices.push_back({ {  100, -100,-100 }	, { 0.5f,	0.0f }	});			//4		

		cubemapVertices.push_back({ { -100, 100,  100 }	, { 0.25f,	2.0f/3.0f }	});		//3		
		cubemapVertices.push_back({ { -100, 100, -100 }	, { 0.25f,	1.0f }	});			//2		
		cubemapVertices.push_back({ {  100,	100,  100 }	, { 0.5f,	2.0f/3.0f }	});		//7

		cubemapVertices.push_back({ { -100, 100, -100 }	, { 0.25f,	1.0f }	});			//2		
		cubemapVertices.push_back({ {  100,	100, -100 }	, { 0.5f,	1.0f }	});			//6		
		cubemapVertices.push_back({ {  100,	100,  100 }	, { 0.5f,	2.0f/3.0f }	});		//7

		cubemapVertices.push_back({ {  100, -100, 100 }	, { 0.5f,	1.0f/3.0f }	});		//5		
		cubemapVertices.push_back({ {  100,	100,  100 }	, { 0.5f,	2.0f/3.0f }	});		//7
		cubemapVertices.push_back({ {  100, -100,-100 }	, { 0.75f,	1.0f/3.0f }	});		//4		

		cubemapVertices.push_back({ {  100,	100,  100 }	, { 0.5f,	2.0f/3.0f }	});		//7
		cubemapVertices.push_back({ {  100,	100, -100 }	, { 0.75f,	2.0f/3.0f }	});		//6		
		cubemapVertices.push_back({ {  100, -100,-100 }	, { 0.75f,	1.0f/3.0f }	});		//4		

		cubemapVertices.push_back({ {  100, -100,-100 }	, { 0.75f,	1.0f/3.0f }	});		//4		
		cubemapVertices.push_back({ {  100,	100, -100 }	, { 0.75f,	2.0f/3.0f }	});		//6	
		cubemapVertices.push_back({ { -100,-100,-100  }	, { 1.00f,	1.0f/3.0f }	});		//0		

		cubemapVertices.push_back({ {  100,	100, -100 }	, { 0.75f,	2.0f/3.0f }	});		//6	
		cubemapVertices.push_back({ { -100, 100, -100 }	, { 1.00f,	2.0f/3.0f }	});		//2		
		cubemapVertices.push_back({ { -100,-100,-100  }	, { 1.00f,	1.0f/3.0f }	});		//0		


		m_Cube = VertexBuffer::create(cubemapVertices.size(), sizeof(cubemapVertices[0]), cubemapVertices.data(), 0);

		m_Cube->pushVertexAttribute(VertexAttributeType::FLOAT3);
		m_Cube->pushVertexAttribute(VertexAttributeType::FLOAT2);

		m_CubeShader = createRef<glslShader>("resources\\shaders\\cubemap.glsl");

		//EDITOR_CAMERA
		auto[x, y] = Application::s_Instance->getWindow()->getSize();
		m_EditorCamera = createRef<EditorCamera>(1.0f * x / y, 0.1f, 300.0f);

		//TEXTURES
		m_GigachadTexture = Texture2D::create("resources\\textures\\Gigachad.png");
		m_CubemapTexture = Texture2D::create("resources\\textures\\cubemap.png");

		//UNIFORM BUFFER
		TextureBufferElement bufferElements[] =
		{
			{ m_CubemapTexture->getTextureHandle(), 0 },
			{ m_GigachadTexture->getTextureHandle(), 0 }
		};
		m_TextureBuffer = UniformBuffer::create(&bufferElements, sizeof(bufferElements), GL_DYNAMIC_STORAGE_BIT);
		m_TextureBuffer->bind(0);
	}

	void AppLayer::onUpdate(const TimeStep& ts)
	{
		m_EditorCamera->onUpdate(ts);

		glm::vec3 camPos = m_EditorCamera->getPosition();
		m_CubeTransform = glm::translate(camPos);

		camPos.y = 0.0f;
		m_FloorTransform = glm::translate(camPos);
	}

	void AppLayer::onDraw()
	{
		m_FloorShader->setMat4(m_EditorCamera->getViewProjection(), "VP");
		m_FloorShader->setMat4(m_FloorTransform, "M");
		m_FloorShader->bind();
		Renderer::s_RendererAPI->drawIndexed(m_Floor);

		m_CubeShader->setMat4(m_EditorCamera->getViewProjection() * m_CubeTransform, "MVP");
		m_CubeShader->bind();
		Renderer::s_RendererAPI->draw(m_Cube);
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