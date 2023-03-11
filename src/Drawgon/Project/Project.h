#pragma once
#include <Tigraf/Core/Assert.h>

#include <string>
#include <vector>
#include <filesystem>

#define DRAWGON_DECLARE_PROJECT \
	private:					\
		Project m_Project{};	\
		void loadProjectFD();	\
		void createProjectFD();	

namespace Drawgon
{
	class Project
	{
	public:
		Project() = default;

		void saveProject();

		const std::string& getName() { return m_Name; }
		const void setName(const std::string& name) { m_Name = name; }
		const std::filesystem::path& getPath() { return m_Path; }
		const std::filesystem::path getGUILayoutFilePath() { return m_Path / Project::s_ProjectGUILayoutPathRel; }
		bool exists() { return !m_Name.empty(); }

		void save();

	public:
		static bool isProject(const std::filesystem::path& projectPath);
		static Project loadProject(const std::filesystem::path& projectPath);
		static Project createProject(const std::string& projectName, const std::filesystem::path& projectPath);

		static const std::filesystem::path s_ProjectFilePathRel;
		static const std::filesystem::path s_ProjectScenesPathRel;
		static const std::filesystem::path s_ProjectGUILayoutPathRel;

	private:
		std::filesystem::path m_Path{};
		std::string m_Name{};

		std::vector<std::string> m_Scenes{};
		std::string m_CurrentScene{};
		std::string m_StartScene{};
	};
}