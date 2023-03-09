#pragma once
#include <Tigraf/Core/Assert.h>

#include <string>
#include <filesystem>

#define DRAWGON_DECLARE_PROJECT \
	private:					\
		Project m_Project{};

namespace Drawgon
{
	class Project
	{
	public:
		Project() = default;

		void saveProject();

		const std::string& getName() { return m_ProjectName; }
		const std::filesystem::path& getPath() { return m_ProjectPath; }
		bool exists() { return !m_ProjectName.empty(); }

	public:
		static bool isProject(const std::filesystem::path& projectPath);
		static Project loadProject(const std::filesystem::path& projectPath);
		static Project createProject(const std::string& projectName, const std::filesystem::path& projectPath);

		static const std::filesystem::path s_ProjectFilePathRel;
		static const std::filesystem::path s_ProjectScenesPathRel;

	private:
		//TODO: Remove redundant "Project" prefix
		std::filesystem::path m_ProjectPath{};
		std::string m_ProjectName{};
	};
}