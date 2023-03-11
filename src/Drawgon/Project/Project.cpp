#include "Project.h"

#include <yaml-cpp/yaml.h>

#include <fstream>

#ifdef TIGRAF_WINDOWS
#include <Windows.h>
#endif

namespace fs = std::filesystem;

namespace Drawgon
{
	void Project::saveProject()
	{
	}
	bool Project::isProject(const std::filesystem::path& projectPath)
	{
		return std::filesystem::exists(projectPath / Project::s_ProjectFilePathRel);
	}

	Project Project::loadProject(const std::filesystem::path& projectPath)
	{
		TIGRAF_ASSERT(isProject(projectPath), "This path does not contain Drawgon project!");

		std::ifstream drawgonProj(projectPath / Project::s_ProjectFilePathRel);
		YAML::Node node = YAML::Load(drawgonProj);
		drawgonProj.close();

		Project p;
		p.m_Path = projectPath;
		p.m_Name = node["ProjectName"].as<std::string>();

		return p;
	}

	Project Project::createProject(const std::string& projectName, const std::filesystem::path& projectPath)
	{
		TIGRAF_ASSERT(!isProject(projectPath), "Project already exists here!");

		YAML::Emitter out;

		out << YAML::BeginMap;
		{
			out << YAML::Key << "ProjectName" << YAML::Value << projectName;
		}
		out << YAML::EndMap;

		const auto& fullPath = projectPath/s_ProjectFilePathRel;
		std::filesystem::create_directories(fullPath.parent_path());
		
#ifdef TIGRAF_WINDOWS
		SetFileAttributesW(fullPath.parent_path().c_str(), FILE_ATTRIBUTE_HIDDEN);
#endif

		std::ofstream fout(fullPath, std::ios::out | std::ios::trunc);

		TIGRAF_ASSERT(fout.is_open(), "Project could not be created!");

		fout << out.c_str();
		fout.close();

		return loadProject(projectPath);
	}

	void Project::save()
	{
		TIGRAF_ASSERT(!m_Name.empty(), "Cannot save empty project!");

		YAML::Emitter out;

		out << YAML::BeginMap;
		{
			out << YAML::Key << "ProjectName" << YAML::Value << m_Name;
		}
		out << YAML::EndMap;

		const auto& fullPath = m_Path / s_ProjectFilePathRel;

		std::ofstream fout(fullPath, std::ios::out | std::ios::trunc);
		fout << out.c_str();
		fout.close();

		TRACE("Project {} saved successfuly!", m_Name);
	}

	const std::filesystem::path Project::s_ProjectFilePathRel = std::filesystem::path(".drawgon") / std::filesystem::path("drawgon.proj");
	const std::filesystem::path Project::s_ProjectScenesPathRel = std::filesystem::path(".drawgon") / std::filesystem::path("scenes");
	const std::filesystem::path Project::s_ProjectGUILayoutPathRel = std::filesystem::path(".drawgon") / std::filesystem::path("imgui.ini");
}