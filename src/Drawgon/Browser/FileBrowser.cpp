#ifndef DRAWGON_EXPORT

#include "FileBrowser.h"

#include "Drawgon/Layers/DrawgonLayer.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace Drawgon
{
	const int FileBrowser::s_FilenameWidth = 12;

	FileBrowser::FileBrowser()
	{
		m_FolderTexture = Texture2D::create("textures\\gui\\folder.png");
		m_FileTexture = Texture2D::create("textures\\gui\\file.png");
	}

	void FileBrowser::onGuiRender()
	{
		ImGui::Begin("File System", nullptr, 0);
		{
			if(m_CurrentDirectory.empty()) 
				m_RootDirectory = m_CurrentDirectory = DrawgonLayer::s_DrawgonLayer->m_Project.m_ProjectSettings.Directory;

			const std::string& relPath = fs::relative("." / m_CurrentDirectory, m_RootDirectory).string();

			if(relPath != ".")
			{
				if(ImGui::Button("<-")) m_CurrentDirectory = m_CurrentDirectory.parent_path();
				ImGui::SameLine();
				ImGui::Text("%s", relPath.c_str());
			}

			std::vector<fs::directory_entry> entries;

			for(const auto& entry : fs::directory_iterator(m_CurrentDirectory))
				if(entry.path().filename() != ".drawgon") entries.emplace_back(entry);

			const auto& [x, y] = ImGui::GetContentRegionAvail();
			int width = std::max(int(x / (m_ColumnWidth + ImGui::GetStyle().FramePadding.x + ImGui::GetStyle().ItemSpacing.x)), 1);

			//TODO: Create class FileBrowserEntry
			if(entries.size() && ImGui::BeginTable("File Browser", width, ImGuiTableFlags_SizingFixedSame))
			{
				ImGui::TableSetupColumn("File Browser");

				for(const auto& entry : entries)
				{
					const std::string& entryName = entry.path().filename().string();
					const std::string& shortEntryName = entryName.size() > s_FilenameWidth ? entryName.substr(0, s_FilenameWidth) + "..." : entryName;

					ImGui::TableNextColumn();

					ImGui::BeginGroup();

						auto imgPosX = (ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - m_ImageWidth - ImGui::GetScrollX() - 2 * ImGui::GetStyle().ItemSpacing.x);
						if(imgPosX > ImGui::GetCursorPosX()) ImGui::SetCursorPosX(imgPosX);

						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 0.5f));
						if(entry.is_directory())	ImGui::ImageButton((void*)*(uint32_t*)m_FolderTexture->getNativeTextureID(), { m_ImageWidth,m_ImageWidth }, { 0, 1 }, { 1, 0 });
						else						ImGui::ImageButton((void*)*(uint32_t*)m_FileTexture->getNativeTextureID(), { m_ImageWidth,m_ImageWidth }, { 0, 1 }, { 1, 0 });
						ImGui::PopStyleColor(3);

						auto textPosX = (ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - ImGui::CalcTextSize(shortEntryName.c_str()).x - ImGui::GetScrollX() - 2 * ImGui::GetStyle().ItemSpacing.x);
						if(textPosX > ImGui::GetCursorPosX()) ImGui::SetCursorPosX(textPosX);


						if(ImGui::IsItemHovered()) 
						{
							ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, 0x80'00'00'FF);
							ImGui::TextColored({ 0.3, 0.7, 0.2, 1.0 }, "%s", shortEntryName.c_str());
							if(ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								if(entry.is_directory()) m_CurrentDirectory = entry.path();
								else 
								{
									std::string command;
#ifdef TIGRAF_LINUX
									command = "xdg-open \'" + entry.path().string() + "\'";
#elif defined(TIGRAF_MACOS)
									command = "open \'" + entry.path().string() + "\'";
#elif defined(TIGRAF_WINDOWS)
									command = "start \"\" \"" + entry.path().string() + "\"";
#else
									TIGRAF_ASSERT(0, "OS not supported!");
#endif
									std::system(command.c_str());
								}
							}
						}
						else ImGui::Text("%s", shortEntryName.c_str());

					ImGui::EndGroup();
				}

				m_ColumnWidth = ImGui::GetColumnWidth();
				ImGui::EndTable();
			}

			if(ImGui::BeginDragDropTarget())
			{
				if(const auto pl = ImGui::AcceptDragDropPayload("", ImGuiDragDropFlags_SourceExtern))
				{
					TRACE("Payload prihvacen");
				}

				ImGui::EndDragDropTarget();
			}
		}
		ImGui::End();
	}
}

#endif