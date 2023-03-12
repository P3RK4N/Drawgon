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

	private:
		std::filesystem::path m_CurrentDirectory = {};

		Ref<Texture2D> m_FolderTexture = nullptr;
		Ref<Texture2D> m_FileTexture = nullptr;
		//Ref<Texture2D> m_PNGTexture = nullptr;
	};
}

#endif