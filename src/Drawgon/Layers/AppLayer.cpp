#include "AppLayer.h"


namespace Drawgon
{
	struct PerFrameData
	{
		glm::mat4 CameraViewProjection{};
		glm::vec3 CameraWorldPosition{};
		float TotalTime;
		float FrameTime;
		uint32_t SkyboxSlot;
	} frameData{};

	struct PerModelData
	{
		glm::mat4 M{};
		glm::mat4 MVP{};
	} modelData{};

	void AppLayer::init()
	{
		ON_GUI_INIT();

		//FRAMEBUFFER FRAME
		glm::mat4 transform =  glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));
		m_FramebufferFrameMesh = MeshPrimitives::Plane(transform);
		m_FramebufferFrameMesh->setShader(Shader::create("shaders\\FramebufferShader.glsl"));

		//FLOOR
		transform = glm::scale(glm::vec3(1000.0f, 1000.0f, 1000.0f)) * glm::mat4(1.0f);
		m_FloorMesh = MeshPrimitives::Plane(transform);
		m_FloorMesh->setShader(Shader::create("shaders\\GridShader.glsl"));

		//CUBE
		m_CubemapMesh = MeshPrimitives::Cube(transform);
		m_CubemapMesh->setShader(Shader::create("shaders\\CubemapShader.glsl"));

		//EDITOR_CAMERA
		auto&[x, y] = Application::s_Instance->getWindow()->getSize();
		m_EditorCamera = createRef<EditorCamera>(1.0f * x / y, 0.1f, 1000.0f);

		//TEXTURES
		m_CubemapTexture = TextureCube::create("textures\\cubemaps\\skybox\\skybox", "jpg");
		SetTextureHandle(m_CubemapTexture, TextureCubeSlot::TEXTURE_CUBE_0);

		//FRAMEBUFFER
		auto&[width, height] = Application::s_Instance->getWindow()->getSize();
		m_Framebuffer = Framebuffer::create(width, height);
		m_Framebuffer->attachColorTexture(TextureFormat::RGBA8);
		m_Framebuffer->attachDepthStencilTexture(TextureFormat::DEPTH24STENCIL8);
		m_Framebuffer->invalidate();
		SetTextureHandle(m_Framebuffer->getColorTexture(0), Texture2DSlot::TEXTURE_2D_0);

	}

	void AppLayer::onUpdate(const TimeStep& ts)
	{
		m_EditorCamera->onUpdate(ts);

		auto&[w, h] = Application::s_Instance->getWindow()->getSize();
		if(w != m_Framebuffer->getWidth() || h != m_Framebuffer->getHeight())
		{
			m_Framebuffer->resize(w, h);
			SetTextureHandle(m_Framebuffer->getColorTexture(0), Texture2DSlot::TEXTURE_2D_0);
		}

		frameData.CameraWorldPosition = m_EditorCamera->getPosition();
		frameData.CameraViewProjection = m_EditorCamera->getViewProjection();
		frameData.TotalTime = ts.m_TotalTime;
		frameData.FrameTime = ts.m_FrameTime;
		frameData.SkyboxSlot = 0;
		UpdatePerFrameBuffer(&frameData, 0, sizeof(PerFrameData));
	}

	void AppLayer::onDraw()
	{
		//ON_GUI_RENDER();

		m_Framebuffer->bind();
		{
			m_CubemapMesh->drawTrianglesIndexed();
			m_FloorMesh->drawTrianglesIndexed();
		}
		m_Framebuffer->unbind();

		m_FramebufferFrameMesh->drawTrianglesIndexed();
	}

	void AppLayer::shutdown()
	{
		ON_GUI_SHUTDOWN();
	}

	bool AppLayer::onEvent(Event& event)
	{
		DISPATCH(EVENT_TYPE::RESIZE, event, onResize);
		return false;
	}

	bool AppLayer::onResize(void* eventData)
	{
		ResizeData* data = (ResizeData*)eventData; 

		m_EditorCamera->setAspectRatio(1.0f * data->width / data->height);
		m_EditorCamera->recalculateViewProjection();

		return false;
	}

	static bool showDemo = true;

	DEFINE_ON_GUI_RENDER
	(
		GUI_RENDER_BEGIN();

		ImGui::ShowDemoWindow(&showDemo);

		GUI_RENDER_END();
	)
}