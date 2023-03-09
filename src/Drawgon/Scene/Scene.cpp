#include "Scene.h"

#include "Drawgon/Layers/DrawgonLayer.h"

namespace Drawgon
{
	Scene::Scene()
	{
		auto& [x, y] = Application::s_Instance->getWindow()->getSize();

		m_SceneFramebuffer = Framebuffer::create(x, y);
		m_SceneFramebuffer->attachColorTexture(TextureFormat::RGBA8);
		m_SceneFramebuffer->attachDepthStencilTexture(TextureFormat::DEPTH24STENCIL8);
		m_SceneFramebuffer->invalidate();

		m_SceneData.m_PerFrameData.FrameTime = 0.0f;
		m_SceneData.m_PerFrameData.TotalTime = 0.0f;
		m_SceneData.m_PerFrameData.CameraViewProjection = m_SceneCamera->getViewProjection();
		m_SceneData.m_PerFrameData.CameraWorldPosition = m_SceneCamera->getPosition();
		m_SceneData.m_PerFrameData.SkyboxIndex = 0;

		m_SceneData.m_PerModelData.M = {};
		m_SceneData.m_PerModelData.MVP = {};

		auto transform = glm::scale(glm::vec3(1000.0f, 1000.0f, 1000.0f)) * glm::mat4(1.0f);
		
		m_SceneSkybox = MeshPrimitives::Cube(transform);
		m_SceneGrid = MeshPrimitives::Plane(transform);

		m_SceneSkybox->setShader(Shader::create("shaders\\CubemapShader.glsl"));
		m_SceneGrid->setShader(Shader::create("shaders\\GridShader.glsl"));
	}

	Scene::Scene(const std::filesystem::path& filepath)
	{
		//TODO: Implement
	}

	Scene::Scene(const std::filesystem::path& fileDir, const char* filename)
	{
		//TODO: Implement
	}

	void Scene::onUpdate(const TimeStep& ts)
	{
		DRAWGON_UPDATE_SCENE_CAMERA(ts);

		m_SceneData.m_PerFrameData.CameraViewProjection = m_SceneCamera->getViewProjection();
		m_SceneData.m_PerFrameData.CameraWorldPosition = m_SceneCamera->getPosition();
		m_SceneData.m_PerFrameData.FrameTime = ts;
		m_SceneData.m_PerFrameData.TotalTime += ts;
		UpdatePerFrameBuffer(&m_SceneData.m_PerFrameData, 0, sizeof(SceneData::PerFrameData));
	}

	void Scene::onDraw()
	{
		m_SceneFramebuffer->bind();
		{
			m_SceneSkybox->drawTrianglesIndexed();
			//TODO: Draw From Entity registry
			m_SceneGrid->drawTrianglesIndexed();
		}
		m_SceneFramebuffer->unbind();
	}

	bool Scene::onEvent(Event& e)
	{

		return false;
	}

	void Scene::onPlay()
	{

	}

	void Scene::onPause()
	{

	}

	void Scene::onStop()
	{

	}

	void Scene::setSkyboxIndex(uint16_t skyboxIndex)
	{
		TIGRAF_ASSERT(skyboxIndex >= TEXTURE_CUBE_COUNT, "Invalid skybox index!");
		m_SceneData.m_PerFrameData.SkyboxIndex = skyboxIndex;
	}

#ifndef DRAWGON_EXPORT

	ImGuiID Scene::s_DockspaceID = 0;

	void Scene::onGuiRender()
	{
		if(!m_Visible) return;			//TODO: This variable needs persistence

		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0.0f,0.0f});
		ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::PopStyleVar(2);

			//Resizing framebuffer ################################
			auto [texX,texY] = this->getColors()->getSize();
			auto [winX, winY] = ImGui::GetContentRegionAvail();	//TODO: Make sure imgui viewports work while main window is minimized
			
			if(!ImGui::IsMouseDown(ImGuiMouseButton_Left) && winX != 0.0f && winY != 0.0f && (texX != winX || texY != winY) || ImGui::GetFrameCount() == 2) //Window is somehow different on a frame before 2
			{
				m_SceneFramebuffer->resize(winX, winY);
				m_SceneCamera->setAspectRatio(winX / winY);
				m_SceneCamera->recalculateViewProjection();
				TRACE("Scene Resize");
			}
			//#####################################################
		
			//Enabling SceneCamera movement #######################
			if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
			{
				m_SceneCamera->setInteractable(true);
			}
			else if(ImGui::IsMouseReleased(ImGuiMouseButton_Left))
			{
				m_SceneCamera->setInteractable(false);
			}
			//#####################################################

			ImGui::Image
			(
				(void*)*(uint32_t*)this->getColors()->getNativeTextureID(),
				ImVec2(winX, winY),
				ImVec2(0,1),
				ImVec2(1,0)
			);
		
		ImGui::End();
  	}

#endif

}