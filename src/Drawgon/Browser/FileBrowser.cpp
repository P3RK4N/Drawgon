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

			std::vector<fs::directory_entry> entries;

			for(const auto& entry : fs::directory_iterator(m_CurrentDirectory))
				if(entry.path().filename() != ".drawgon") entries.emplace_back(entry);

			const auto& [x, y] = ImGui::GetContentRegionAvail();
			constexpr int FILE_WIDTH = 80;
			int width = x / (FILE_WIDTH + ImGui::GetStyle().FramePadding.x + ImGui::GetStyle().ItemSpacing.x);

			if(ImGui::BeginTable("File Browser", width, ImGuiTableFlags_SizingFixedSame))
			{
				ImGui::TableSetupColumn("File Browser", 0, 55);
				//for(const auto& entry : entries)
				for(int i = 0; i < 29; i++)
				{
					ImGui::TableNextColumn();
					
					ImGui::BeginGroup();
						ImGui::ImageButton("Button", 0, { FILE_WIDTH,FILE_WIDTH });
						if(ImGui::IsItemHovered()) ImGui::TextColored({ 0.3, 0.7, 0.2, 1.0 }, "Ivan %d", i);
						else ImGui::Text("Ivan %d", i);
					ImGui::EndGroup();
				}

				ImGui::EndTable();
			}

		}
		ImGui::End();
	}
}

#endif