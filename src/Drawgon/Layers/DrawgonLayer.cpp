#include "DrawgonLayer.h"

namespace Drawgon
{
	void DrawgonLayer::init()
	{
		DRAWGON_ON_GUI_INIT();

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

	void DrawgonLayer::onUpdate(const TimeStep& ts)
	{
		m_CurrentScene->onUpdate(ts);
	}

	void DrawgonLayer::onDraw()
	{
		DRAWGON_ON_GUI_RENDER(this);

		m_CurrentScene->onDraw();
		//m_FramebufferFrameMesh->drawTrianglesIndexed();
	}

	void DrawgonLayer::shutdown()
	{
		DRAWGON_ON_GUI_SHUTDOWN();
	}

	bool DrawgonLayer::onEvent(Event& event)
	{
		if(m_CurrentScene->onEvent(event)) return true;

		return false;
	}

	static bool showDemo = true;

#ifndef DRAWGON_EXPORT

	static bool Renaming = false;
	static char RenameBuffer[128] = "";

	ImGuiID DrawgonLayer::s_DockspaceID = 0;

	void DrawgonLayer::loadProjectFD()
	{
		std::string currentDirectory = std::filesystem::current_path().string();
		const char* currentDirectory_chr = currentDirectory.c_str();
					
		char* projectDirectory_chr = new char[256];
		auto res = NFD_PickFolder(currentDirectory_chr, (nfdchar_t**)&projectDirectory_chr);

		TIGRAF_ASSERT(res != NFD_ERROR, "Error while creating New Project!");

		if(res == NFD_OKAY)
		{
			std::string projectDirectory{ projectDirectory_chr };

			//Loading project
			m_Project = Project::loadProject(projectDirectory);

			//Switching GUI state to saved state of loaded project
			m_GUIFilePath = m_Project.getGUILayoutFilePath().string().c_str();
			m_ShouldReloadGUI = true;

			TRACE("Project {} Loaded at: {}", m_Project.getName(), projectDirectory);
		}
		else TRACE("Project loading cancelled!");

		delete[] projectDirectory_chr;
	}

	void DrawgonLayer::createProjectFD()
	{
		std::string currentDirectory = std::filesystem::current_path().string();
		const char* currentDirectory_chr = currentDirectory.c_str();
					
		char* projectDirectory_chr = new char[256];
		auto res = NFD_PickFolder(currentDirectory_chr, (nfdchar_t**)&projectDirectory_chr);

		TIGRAF_ASSERT(res != NFD_ERROR, "Error while creating New Project!");

		if(res == NFD_OKAY)
		{
			std::string projectDirectory{ projectDirectory_chr };

			//Creating project instance
			m_Project = Project::createProject("New Project", projectDirectory);

			//Switching GUI state to saved state of loaded project
			m_GUIFilePath = m_Project.getGUILayoutFilePath().string().c_str();
			m_ShouldReloadGUI = true;

			//Copying default gui settings
			const auto& defaultGuiSrc = Application::s_Instance->getWorkingDirectory() / "settings" / "default.ini";
			const auto& defaultGuiDst = m_Project.getGUILayoutFilePath();
			TIGRAF_ASSERT(std::filesystem::copy_file(defaultGuiSrc, defaultGuiDst), "Error while creating New Project!");

			TRACE("Project created at: {}", projectDirectory);
		}
		else TRACE("Project creation cancelled!");

		delete[] projectDirectory_chr;
	}

	void DrawgonLayer::reloadGUI()
	{
		DRAWGON_ON_GUI_SHUTDOWN();
		DRAWGON_ON_GUI_INIT_CUSTOM(m_GUIFilePath.string().c_str());
	}

	void DrawgonLayer::onGuiRender()
	{
		if(m_Project.getName().empty())
		{
			//TODO: Force creation/loading of project
			return;
		}

		if(m_ShouldReloadGUI)
		{
			m_ShouldReloadGUI = false;
			reloadGUI();
		}

		DRAWGON_GUI_RENDER_BEGIN();

		ImGui::BeginMainMenuBar();
		{
			if(ImGui::BeginMenu("Application"))
			{
				if(ImGui::MenuItem("Exit"))
				{
					Application::s_Instance->exit();
				}

				ImGui::EndMenu();
			}

			if(ImGui::BeginMenu("Project"))
			{
				//Project settings
				if(!m_Project.getName().empty()) 
				{
					if(ImGui::BeginMenu(m_Project.getName().c_str()))
					{
						if(ImGui::MenuItem("Rename"))
						{
							Renaming = true;
						}

						if(ImGui::MenuItem("Save"))
						{
							m_Project.save();
						}

						ImGui::EndMenu();
					}
				}
				else
				{
					ImGui::TextDisabled("Empty");
				}

				ImGui::Separator();


				//Loading project
				if(ImGui::MenuItem("Load..."))
				{
					loadProjectFD();
				}

				//TODO: Maybe open a project creation window
				if(ImGui::MenuItem("Create..."))
				{
					createProjectFD();
				}

				ImGui::EndMenu();
			}

			if(ImGui::BeginMenu("View"))
			{
				DRAWGON_WINDOW_CHECKBOX(m_CurrentScene, "Scene");
				DRAWGON_WINDOW_CHECKBOX(m_Console, "Console");

				ImGui::EndMenu();
			}
		}

		ImGui::EndMainMenuBar();

		if(Renaming) ImGui::OpenPopup("Rename Project", ImGuiPopupFlags_NoOpenOverExistingPopup);

		if(ImGui::BeginPopup("Rename Project"))
		{
			if(ImGui::InputText("New Project Name", RenameBuffer, 128, ImGuiInputTextFlags_EnterReturnsTrue))
			{
				if(RenameBuffer[0])
				{
					m_Project.setName(RenameBuffer);
					TRACE("Renamed project to {}", RenameBuffer);
				}
				else
				{
					WARN("Cannot rename project to empty name!");
				}
				Renaming = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::ShowDemoWindow(&showDemo);

		DRAWGON_ON_GUI_RENDER(m_CurrentScene);
		DRAWGON_ON_GUI_RENDER(m_Console);

		DRAWGON_GUI_RENDER_END();
	}

#endif

}