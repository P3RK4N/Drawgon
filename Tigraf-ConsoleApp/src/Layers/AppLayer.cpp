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

	struct TextureVertex
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
		std::vector<TextureVertex> cubemapVertices;
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

		//FRAMEBUFFER FRAME
		std::vector<TextureVertex> frameVertices =
		{
			{{ -0.5f, -0.5f, 0 }, { 0.0f, 0.0f }},
			{{ 0.5f, -0.5f, 0 }, { 1.0f, 0.0f }},
			{{ -0.5f, 0.5f, 0 }, { 0.0f, 1.0f }},
			{{ 0.5f, 0.5f, 0 }, { 1.0f, 1.0f }}
		};
		std::vector<uint32_t> frameIndices =
		{
			0,2,1, 2,3,1
		};

		m_FramebufferFrame = VertexBuffer::create(frameVertices.size(), sizeof(frameVertices[0]), frameVertices.data(), 0);
		Ref<IndexBuffer> framebufferIB = IndexBuffer::create(frameIndices, 0);
		
		m_FramebufferFrame->setIndexBuffer(framebufferIB);
		m_FramebufferFrame->pushVertexAttribute(VertexAttributeType::FLOAT3);
		m_FramebufferFrame->pushVertexAttribute(VertexAttributeType::FLOAT2);

		m_FramebufferShader = createRef<glslShader>("resources\\shaders\\framebuffer.glsl");
		
		//EDITOR_CAMERA
		auto[x, y] = Application::s_Instance->getWindow()->getSize();
		m_EditorCamera = createRef<EditorCamera>(1.0f * x / y, 0.1f, 300.0f);

		//TEXTURES
		m_GigachadTexture = Texture2D::create("resources\\textures\\Gigachad.png");
		m_CubemapTexture = TextureCube::create("resources\\textures\\cubemaps\\skybox\\skybox", "jpg");

		//FRAMEBUFFER
		auto [width, height] = Application::s_Instance->getWindow()->getSize();
		m_Framebuffer = Framebuffer::create(width, height);
		m_Framebuffer->attachColorTexture(TextureFormat::RGBA);
		m_Framebuffer->attachDepthStencilTexture(TextureFormat::DepthStencil);
		m_Framebuffer->invalidate();

		//GLOBAL UNIFORM BUFFER
		SET_TEXTURE_HANDLE(m_CubemapTexture->getTextureHandle(), TEXTURE_CUBE_0);
		SET_TEXTURE_HANDLE(m_Framebuffer->getColorTexture(0)->getTextureHandle(), TEXTURE_2D_0);
		SET_TEXTURE_HANDLE(m_GigachadTexture->getTextureHandle(), TEXTURE_2D_1);
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
		m_Framebuffer->bind();

		m_CubeShader->setMat4(m_EditorCamera->getViewProjection() * m_CubeTransform, "MVP");
		m_CubeShader->bind();
		Renderer::s_RendererAPI->draw(m_Cube);

		m_FloorShader->setMat4(m_EditorCamera->getViewProjection(), "VP");
		m_FloorShader->setMat4(m_FloorTransform, "M");
		m_FloorShader->bind();
		Renderer::s_RendererAPI->drawIndexed(m_Floor);

		m_Framebuffer->unbind();

		m_CubeShader->setMat4(m_EditorCamera->getViewProjection() * m_CubeTransform, "MVP");
		m_CubeShader->bind();
		Renderer::s_RendererAPI->draw(m_Cube);

		m_FloorShader->setMat4(m_EditorCamera->getViewProjection(), "VP");
		m_FloorShader->setMat4(m_FloorTransform, "M");
		m_FloorShader->bind();
		Renderer::s_RendererAPI->drawIndexed(m_Floor);

		m_FramebufferShader->bind();
		Renderer::s_RendererAPI->drawIndexed(m_FramebufferFrame);
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

		if(data->width && data->height)
		{
			m_EditorCamera->setAspectRatio(1.0f * data->width / data->height);
			m_EditorCamera->recalculateViewProjection();
		}

		return false; 
	}
}