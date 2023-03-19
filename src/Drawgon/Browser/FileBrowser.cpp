#ifndef DRAWGON_EXPORT

#include "FileBrowser.h"

#include "Drawgon/Layers/DrawgonLayer.h"

#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

namespace Drawgon
{
	const int FileBrowser::s_FilenameWidth = 12;

	FileBrowser::FileBrowser()
	{
		m_FolderTexture = Texture2D::create("textures\\gui\\folder.png");
		m_FileTexture = Texture2D::create("textures\\gui\\file.png");
	}

	bool FileBrowser::onEvent(Event& ev)
	{
		static const auto& onFileDrop = [this](void* eventData) { m_ExternalPayloadPath = ((FileData*)eventData)->filePath; return true; };
		static const auto& onKeyPress = [this](void* eventData)
		{
			KeyData kd = *(KeyData*)eventData;
			return false;	//TODO: on enter or delete, manipulate active file
		};

		DISPATCH(EVENT_TYPE::FILE_DROP, ev, onFileDrop);
		DISPATCH(EVENT_TYPE::KEY_PRESS, ev, onKeyPress);
		return false;
	}

	void FileBrowser::onGuiRender()
	{
		TIGRAF_ASSERT(!m_CurrentDirectory.empty(), "Current path not set!");
		TIGRAF_ASSERT(!m_RootDirectory.empty(), "Root path not set!");

		const std::string& relPath = fs::relative("." / m_CurrentDirectory, m_RootDirectory).string();

		ImGui::Begin("File System", nullptr, 0);
		{
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
				for(int i = 0; i < entries.size(); i++)
				{
					ImGui::TableNextColumn();

					ImGui::PushID(i);

					const std::string& entryName = entries[i].path().filename().string();
					const std::string& shortEntryName = entryName.size() > s_FilenameWidth ? entryName.substr(0, s_FilenameWidth) + "..." : entryName;
					
					ImGui::BeginGroup(); //File entry
					{
						auto imgPosX = (ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - m_ImageWidth - ImGui::GetScrollX() - 2 * ImGui::GetStyle().ItemSpacing.x);
						if(imgPosX > ImGui::GetCursorPosX()) ImGui::SetCursorPosX(imgPosX);

						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
						if(entries[i].is_directory())	ImGui::ImageButton((void*)*(uint32_t*)m_FolderTexture->getNativeTextureID(), { m_ImageWidth,m_ImageWidth }, { 0, 1 }, { 1, 0 });
						else						ImGui::ImageButton((void*)*(uint32_t*)m_FileTexture->getNativeTextureID(), { m_ImageWidth,m_ImageWidth }, { 0, 1 }, { 1, 0 });
						ImGui::PopStyleColor(3);

						auto textPosX = (ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - ImGui::CalcTextSize(shortEntryName.c_str()).x - ImGui::GetScrollX() - 2 * ImGui::GetStyle().ItemSpacing.x);
						if(textPosX > ImGui::GetCursorPosX()) ImGui::SetCursorPosX(textPosX);

						ImGui::Text("%s", shortEntryName.c_str());
					}
					ImGui::EndGroup(); //File entry

					if(ImGui::IsItemClicked()) m_ActiveEntry = entries[i];
					if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsItemClicked() && m_ActiveEntry == entries[i]) m_ActiveEntry = {};
					if(m_ActiveEntry == entries[i]) ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, 0x40'C0'80'40);

					if(ImGui::IsItemHovered()) 
					{
						if(m_ActiveEntry != entries[i])
						{
							if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))	ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, 0x60120F0FF);
							else												ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, 0x3060C0FF);
						}

						if(ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) openItem(entries[i]);
					}


					if(ImGui::IsItemClicked(ImGuiMouseButton_Right)) ImGui::OpenPopup("Options");
					if(ImGui::BeginPopup("Options"))
					{
						if(ImGui::MenuItem("Delete"));
						if(ImGui::IsItemClicked()) ImGui::OpenPopup(entryName.c_str());

						centerNextPopup(300, 150);
						if(ImGui::BeginPopupModal(entryName.c_str()))
						{
							ImGui::SetCursorPosX((300 - ImGui::CalcTextSize("Are you sure?").x) / 2);
							ImGui::Text("Are you sure?");

							auto heightStart = (ImGui::GetWindowHeight() + ImGui::GetCursorPos().y) / 2.0f - 20;
							auto lWidthStart = ImGui::GetWindowWidth() / 3.0f - 40;
							auto rWidthStart = ImGui::GetWindowWidth() * 0.666667f - 40;

							ImGui::SetCursorPos({ lWidthStart, heightStart });
							if(ImGui::Button("Yes", { 80, 40 }))
							{
								deleteItem(entries[i]);
								ImGui::ClosePopupToLevel(0, true);
							}
							ImGui::SameLine();
							ImGui::SetCursorPosX(rWidthStart);
							if(ImGui::Button("No", { 80, 40 })) ImGui::ClosePopupToLevel(0, true);

							ImGui::EndPopup();
						}

						ImGui::EndPopup();
					}
					
					ImGui::PopID();
				}

				m_ColumnWidth = ImGui::GetColumnWidth();
				ImGui::EndTable();
			}

			if(!m_ExternalPayloadPath.empty() && m_ExternalPayloadPath.parent_path() != m_CurrentDirectory)
			{
				const auto& sourceName = m_ExternalPayloadPath.filename();
				fs::copy(m_ExternalPayloadPath, m_CurrentDirectory / sourceName);
				TRACE("{} copied here!", m_ExternalPayloadPath);
				m_ExternalPayloadPath.clear();
			}
		}
		ImGui::End();
	}

	void FileBrowser::openItem(const fs::directory_entry& entry)
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

	void FileBrowser::deleteItem(const fs::directory_entry& entry)
	{
		TRACE("Removing: {}", entry.path());
		TIGRAF_ASSERT(fs::remove(entry.path()), "Could not remove item")
	}

} //Namespace Drawgon

#endif