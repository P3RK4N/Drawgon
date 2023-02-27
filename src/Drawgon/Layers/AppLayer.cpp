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


		//TEXTURES
		m_CubemapTexture = TextureCube::create("textures\\cubemaps\\skybox\\skybox", "jpg");
		SetTextureHandle(m_CubemapTexture, TextureCubeSlot::TEXTURE_CUBE_0);

		m_CurrentScene = createRef<Scene>();
		SetTextureHandle(m_CurrentScene->getColors(), Texture2DSlot::TEXTURE_2D_0);
	}

	void AppLayer::onUpdate(const TimeStep& ts)
	{
		m_CurrentScene->onUpdate(ts);
	}

	void AppLayer::onDraw()
	{
		ON_GUI_RENDER(this);

		m_CurrentScene->onDraw();
		//m_FramebufferFrameMesh->drawTrianglesIndexed();
	}

	void AppLayer::shutdown()
	{
		ON_GUI_SHUTDOWN();
	}

	bool AppLayer::onEvent(Event& event)
	{
		if(m_CurrentScene->onEvent(event)) return true;

		return false;
	}

	static bool showDemo = true;

#ifndef DRAWGON_EXPORT

	void AppLayer::onGuiRender()
	{
		GUI_RENDER_BEGIN();

		ImGui::ShowDemoWindow(&showDemo);

		ON_GUI_RENDER(m_CurrentScene);

		GUI_RENDER_END();
	}

#endif

}