#pragma once
#include <string>
#include <vector>

//Settings which persist on export
struct DrawgonSettings
{
	std::string StartingScene;
	std::vector<std::string> Scenes;
	//TODO: Add More
};


//Settings which dont persist on export
#ifndef DRAWGON_EXPORT

	struct EditorSettings
	{
		bool ConsoleEnabled;
		bool SceneEnabled;
		bool SceneHierarchyEnabled;
		bool ObjectPropertiesEnabled;
		bool FileBrowserEnabled;

		std::string CurrentScene;
		//TODO: Add More
	};

	//This is done automatically via imgui :)
	//struct GUISettings
	//{

	//};

#endif