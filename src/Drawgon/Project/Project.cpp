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
		p.m_ProjectPath = projectPath;
		p.m_ProjectName = node["ProjectName"].as<std::string>();

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

	const std::filesystem::path Project::s_ProjectFilePathRel = std::filesystem::path(".drawgon") / std::filesystem::path("drawgon.proj");
	const std::filesystem::path Project::s_ProjectScenesPathRel = std::filesystem::path(".drawgon") / std::filesystem::path("scenes");
}