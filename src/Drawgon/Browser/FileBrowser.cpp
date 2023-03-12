#ifndef DRAWGON_EXPORT

#include "FileBrowser.h"

#include "Drawgon/Layers/DrawgonLayer.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace Drawgon
{
	FileBrowser::FileBrowser()
	{
		m_FolderTexture = Texture2D::create("textures\\gui\\folder.png");

		glm::u8vec3 col = { 80U, 100U, 180U };
		m_FileTexture = Texture2D::create(TextureFormat::RGB8, 1, 1, &col);
	}


	void FileBrowser::onGuiRender()
	{
		ImGui::Begin("File System", nullptr, 0);
		{
			if(m_CurrentDirectory.empty()) 
				m_CurrentDirectory = DrawgonLayer::s_DrawgonLayer->m_Project.m_ProjectSettings.Directory;

			for(const auto& entry : fs::directory_iterator(m_CurrentDirectory))
			{
				if(entry.path().filename() == ".drawgon") continue;
				else if(entry.is_directory())
				{
					ImGui::ImageButton((void*)*(uint32_t*)m_FolderTexture->getNativeTextureID(), ImVec2(50U, 50U), ImVec2(0, 1), ImVec2(1, 0));
				}
				else
				{
					ImGui::ImageButton((void*)*(uint32_t*)m_FileTexture->getNativeTextureID(), ImVec2(50U, 50U), ImVec2(0, 1), ImVec2(1, 0));
				}
			}
		}
		ImGui::End();
	}
}

#endif