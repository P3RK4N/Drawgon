#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace Drawgon
{
	//Settings which persist on export
	struct ProjectSettings
	{
		std::string Name						= {};
		std::filesystem::path Directory			= {};
		std::string StartingScene				= {};
		std::vector<std::string> Scenes			= {};
		//TODO: Add More
	};

	//Settings which dont persist on export
	#ifndef DRAWGON_EXPORT

		struct EditorSettings
		{
			bool ConsoleEnabled				= true;
			bool SceneEnabled				= true;
			bool SceneHierarchyEnabled		= false;
			bool ObjectPropertiesEnabled	= false;
			bool FileBrowserEnabled			= false;

			std::string CurrentScene		= {};
			//TODO: Add More
		};

	#endif
}