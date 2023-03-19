#pragma once

#ifndef DRAWGON_EXPORT

#include "Drawgon/GUI/GUI_GeneralDefines.h"

#include <Tigraf/Tigraf.h>

using namespace Tigraf;

namespace Drawgon
{
	//TODO: Add c++ scripting support and cmakelists generator
	class FileBrowser
	{
		friend class DrawgonLayer;

		DRAWGON_DECLARE_ON_GUI_RENDER

	public:
		FileBrowser();

		void setRootDirectory(const std::filesystem::path& rootDir) { m_CurrentDirectory = m_RootDirectory = rootDir; }
		void setExternalPayloadPath(const char* filePath) { m_ExternalPayloadPath = filePath; }

		bool onEvent(Event& ev);

	private:
		//TODO: Serialize?
		std::filesystem::path m_CurrentDirectory = {};
		std::filesystem::path m_RootDirectory = {};

		Ref<Texture2D> m_FolderTexture = nullptr;
		Ref<Texture2D> m_FileTexture = nullptr;
		//Ref<Texture2D> m_PNGTexture = nullptr;

		float m_ImageWidth = 80.0f;
		float m_ColumnWidth = 80.0f;

		std::filesystem::path m_ExternalPayloadPath = {};
		std::filesystem::directory_entry m_ActiveEntry = {};

	private:
		void openItem(const std::filesystem::directory_entry& entry);
		void deleteItem(const std::filesystem::directory_entry& entry);

		void deletePrompt() {} //TODO: Implement
	private:
		static const int s_FilenameWidth;
	};
}

#endif