#include "AppLayer.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tigraf
{
	struct PerFrameData
	{
		glm::mat4 CameraViewProjection{};
		glm::vec3 CameraWorldPosition{};
		float TotalTime;
	} frameData{};

	struct PerModelData
	{
		glm::mat4 M{};
		glm::mat4 MVP{};
	} modelData{};

	void AppLayer::init()
	{
		//FRAMEBUFFER FRAME
		glm::mat4 transform =  glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));
		m_FramebufferFrameMesh = MeshPrimitives::Plane(transform);
		m_FramebufferFrameMesh->setShader(Shader::create("resources\\shaders\\FramebufferShader.glsl"));

		//FLOOR
		transform = glm::scale(glm::vec3(100.0f, 100.0f, 100.0f)) * glm::mat4(1.0f);
		m_FloorMesh = MeshPrimitives::Plane(transform);
		m_FloorMesh->setShader(Shader::create("resources\\shaders\\GridShader.glsl"));

		//CUBE
		m_CubemapMesh = MeshPrimitives::Cube(transform);
		m_CubemapMesh->setShader(Shader::create("resources\\shaders\\CubemapShader.glsl"));

		//Plane2D
		m_Plane2DMesh = MeshPrimitives::Plane2D();
		m_Plane2DMesh->setShader(Shader::create("resources\\shaders\\GUI_Shader.glsl"));

		//EDITOR_CAMERA
		auto[x, y] = Application::s_Instance->getWindow()->getSize();
		m_EditorCamera = createRef<EditorCamera>(1.0f * x / y, 0.1f, 300.0f);

		//TEXTURES
		m_GigachadTexture = Texture2D::create("resources\\textures\\Gigachad.png");
		SET_TEXTURE_HANDLE(m_GigachadTexture->getTextureHandle(), TEXTURE_2D_1);
		m_CubemapTexture = TextureCube::create("resources\\textures\\cubemaps\\skybox\\skybox", "jpg");
		SET_TEXTURE_HANDLE(m_CubemapTexture->getTextureHandle(), TEXTURE_CUBE_0);

		//RWBUFFER
		glm::vec4 Color = { 1.0f, 0.2f, 0.2f, 1.0f };

		m_RWBuffer = RWBuffer::create(nullptr, sizeof(glm::vec4), GL_DYNAMIC_STORAGE_BIT);
		m_RWBuffer->bind(RW_BUFFER_0);
		m_RWBuffer->updateBuffer(&Color, 16, 0);

		//RWTEXTURE
		struct COLOR
		{
			uint8_t r, g, b, a;
		};

		std::vector<COLOR> colorBuffer;
		colorBuffer.reserve(100 * 100);
		for(int i = 0; i < 100*100; i++)
		{
			colorBuffer.emplace_back(0xFF,0xF0,0,0xFF);
		}

		m_RWTexture = RWTexture2D::create(TextureFormat::RGBA8, 100, 100, colorBuffer.data());
		struct Handle
		{
			uint64_t handle;
			uint64_t padding;
		} handle{ m_RWTexture->getTextureHandle(), 0 };
		m_ImageBuffer = UniformBuffer::create(&handle, sizeof(handle), 0);
		m_ImageBuffer->bind(UNIFORM_BUFFER_3);

		m_ComputeShader = Shader::create("resources\\shaders\\ComputeShader.glsl");

		//FRAMEBUFFER
		auto [width, height] = Application::s_Instance->getWindow()->getSize();
		m_Framebuffer = Framebuffer::create(width, height);
		m_Framebuffer->attachColorTexture(TextureFormat::RGBA8);
		m_Framebuffer->attachDepthStencilTexture(TextureFormat::DEPTH24STENCIL8);
		m_Framebuffer->invalidate();
		SET_TEXTURE_HANDLE(m_Framebuffer->getColorTexture(0)->getTextureHandle(), TEXTURE_2D_0);
	}

	void AppLayer::onUpdate(const TimeStep& ts)
	{
		m_EditorCamera->onUpdate(ts);

		auto [w, h] = Application::s_Instance->getWindow()->getSize();
		if(w != m_Framebuffer->getWidth() || h != m_Framebuffer->getHeight())
		{
			m_Framebuffer->resize(w, h);
			SET_TEXTURE_HANDLE(m_Framebuffer->getColorTexture(0)->getTextureHandle(), TEXTURE_2D_0);
		}

		m_ComputeShader->dispatch(16, 16, 1);
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		frameData.CameraWorldPosition = m_EditorCamera->getPosition();
		frameData.CameraViewProjection = m_EditorCamera->getViewProjection();
		frameData.TotalTime = ts.m_TotalTime;
		UPDATE_PER_FRAME_BUFFER(frameData, sizeof(PerFrameData), 0);
	}

	void AppLayer::onDraw()
	{
		m_Framebuffer->bind();
		{
			m_CubemapMesh->drawIndexed();
			m_FloorMesh->drawIndexed();
		}
		m_Framebuffer->unbind();

		
		m_Plane2DMesh->drawIndexed();
		m_FramebufferFrameMesh->drawIndexed();
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