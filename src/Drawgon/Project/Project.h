#pragma once
#include "Drawgon/Project/Settings.h"

#include <Tigraf/Core/Assert.h>

#include <string>
#include <vector>
#include <filesystem>

//TODO: Project in export will be opened without file dialog. It will be opened from relative addressing. DO IT
namespace Drawgon
{
	class Project
	{
	public:
		Project() = default;

		const std::string&				getName()							{ return  m_ProjectSettings.Name; }
		const void						setName(const std::string& name)	{ m_ProjectSettings.Name = name; }
		const std::filesystem::path&	getDirectory()						{ return m_ProjectSettings.Directory; }
		const std::filesystem::path		getGUILayoutFilePath()				{ return m_ProjectSettings.Directory / Project::s_ProjectGUILayoutPathRel; }
		const bool						exists()							{ return !m_ProjectSettings.Name.empty(); }

		ProjectSettings m_ProjectSettings	= {};
		EditorSettings	m_EditorSettings	= {};

		void save();

	public:
		static bool		isProject		(const std::filesystem::path& projectPath);
		static Project	loadProject		(const std::filesystem::path& projectPath);
		static Project	createProject	(const std::string& projectName, const std::filesystem::path& projectPath);

		static const std::filesystem::path s_ProjectFilePathRel;
		static const std::filesystem::path s_ProjectScenesPathRel;
		static const std::filesystem::path s_ProjectGUILayoutPathRel;

	};
}