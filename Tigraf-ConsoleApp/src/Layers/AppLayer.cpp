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
	};

	struct PerModelData
	{
		glm::mat4 M{};
		glm::mat4 MVP{};
	};

	PerFrameData frameData{};
	PerModelData modelData{};

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

		//EDITOR_CAMERA
		auto[x, y] = Application::s_Instance->getWindow()->getSize();
		m_EditorCamera = createRef<EditorCamera>(1.0f * x / y, 0.1f, 300.0f);

		//TEXTURES
		m_GigachadTexture = Texture2D::create("resources\\textures\\Gigachad.png");
		SET_TEXTURE_HANDLE(m_GigachadTexture->getTextureHandle(), TEXTURE_2D_1);
		m_CubemapTexture = TextureCube::create("resources\\textures\\cubemaps\\skybox\\skybox", "jpg");
		SET_TEXTURE_HANDLE(m_CubemapTexture->getTextureHandle(), TEXTURE_CUBE_0);

		//FRAMEBUFFER
		auto [width, height] = Application::s_Instance->getWindow()->getSize();
		m_Framebuffer = Framebuffer::create(width, height);
		m_Framebuffer->attachColorTexture(TextureFormat::RGBA);
		m_Framebuffer->attachDepthStencilTexture(TextureFormat::DepthStencil);
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
	}

	void AppLayer::onDraw()
	{
		frameData.CameraWorldPosition = m_EditorCamera->getPosition();
		frameData.CameraViewProjection = m_EditorCamera->getViewProjection();
		UPDATE_PER_FRAME_BUFFER(frameData, sizeof(PerFrameData), 0);

		m_Framebuffer->bind();
		{
			m_CubemapMesh->drawIndexed();
			m_FloorMesh->drawIndexed();
		}
		m_Framebuffer->unbind();

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