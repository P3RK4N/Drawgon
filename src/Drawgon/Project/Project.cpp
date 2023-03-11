#include "Project.h"

#include <yaml-cpp/yaml.h>

#include <fstream>

#ifdef TIGRAF_WINDOWS
	#include <Windows.h>
#endif

namespace fs = std::filesystem;

namespace Drawgon
{
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

		p.m_ProjectSettings.Name					= node["ProjectSettings"]["Name"].as<std::string>();
		p.m_ProjectSettings.Directory				= node["ProjectSettings"]["Directory"].as<std::string>();
		p.m_ProjectSettings.StartingScene			= node["ProjectSettings"]["StartingScene"].as<std::string>();
		p.m_ProjectSettings.Scenes					= node["ProjectSettings"]["Scenes"].as<std::vector<std::string>>();

		p.m_EditorSettings.ConsoleEnabled			= node["EditorSettings"]["ConsoleEnabled"].as<bool>();
		p.m_EditorSettings.SceneEnabled				= node["EditorSettings"]["SceneEnabled"].as<bool>();
		p.m_EditorSettings.SceneHierarchyEnabled	= node["EditorSettings"]["SceneHierarchyEnabled"].as<bool>();
		p.m_EditorSettings.ObjectPropertiesEnabled	= node["EditorSettings"]["ObjectPropertiesEnabled"].as<bool>();
		p.m_EditorSettings.FileBrowserEnabled		= node["EditorSettings"]["FileBrowserEnabled"].as<bool>();
		p.m_EditorSettings.CurrentScene				= node["EditorSettings"]["CurrentScene"].as<std::string>();

		return p;
	}

	Project Project::createProject(const std::string& projectName, const std::filesystem::path& projectPath)
	{
		TIGRAF_ASSERT(!isProject(projectPath), "Project already exists here!");

		Project p;
		p.m_ProjectSettings.Name = projectName;
		p.m_ProjectSettings.Directory = projectPath;

		YAML::Emitter out;

		out << YAML::BeginMap;
		{
			out << YAML::Key << "ProjectSettings" << YAML::Value << YAML::BeginMap;
			{
				out << YAML::Key << "Name" << YAML::Value << p.m_ProjectSettings.Name;
				out << YAML::Key << "Directory" << YAML::Value << p.m_ProjectSettings.Directory.string();
				out << YAML::Key << "StartingScene" << YAML::Value << p.m_ProjectSettings.StartingScene;
				out << YAML::Key << "Scenes" << YAML::Value << p.m_ProjectSettings.Scenes;
			}
			out << YAML::EndMap;

			out << YAML::Key << "EditorSettings" << YAML::Value << YAML::BeginMap;
			{
				out << YAML::Key << "ConsoleEnabled" << YAML::Value << p.m_EditorSettings.ConsoleEnabled;
				out << YAML::Key << "SceneEnabled" << YAML::Value << p.m_EditorSettings.SceneEnabled;
				out << YAML::Key << "SceneHierarchyEnabled" << YAML::Value << p.m_EditorSettings.SceneHierarchyEnabled;
				out << YAML::Key << "ObjectPropertiesEnabled" << YAML::Value << p.m_EditorSettings.ObjectPropertiesEnabled;
				out << YAML::Key << "FileBrowserEnabled" << YAML::Value << p.m_EditorSettings.FileBrowserEnabled;
				out << YAML::Key << "CurrentScene" << YAML::Value << p.m_EditorSettings.CurrentScene;
			}
			out << YAML::EndMap;
		}
		out << YAML::EndMap;

		const auto& fullPath = projectPath / s_ProjectFilePathRel;
		std::filesystem::create_directories(fullPath.parent_path());
		
#ifdef TIGRAF_WINDOWS
		SetFileAttributesW(fullPath.parent_path().c_str(), FILE_ATTRIBUTE_HIDDEN);
#endif

		std::ofstream fout(fullPath, std::ios::out | std::ios::trunc);

		TIGRAF_ASSERT(fout.is_open(), "Project could not be created!");

		fout << out.c_str();
		fout.close();

		return p;
	}

	void Project::save()
	{
		TIGRAF_ASSERT(exists(), "Cannot save empty project!");

		YAML::Emitter out;

		out << YAML::BeginMap;
		{
			out << YAML::Key << "ProjectSettings" << YAML::Value << YAML::BeginMap;
			{
				out << YAML::Key << "Name" << YAML::Value << m_ProjectSettings.Name;
				out << YAML::Key << "Directory" << YAML::Value << m_ProjectSettings.Directory.string();
				out << YAML::Key << "StartingScene" << YAML::Value << m_ProjectSettings.StartingScene;
				out << YAML::Key << "Scenes" << YAML::Value << m_ProjectSettings.Scenes;
			}
			out << YAML::EndMap;

			out << YAML::Key << "EditorSettings" << YAML::Value << YAML::BeginMap;
			{
				out << YAML::Key << "ConsoleEnabled" << YAML::Value << m_EditorSettings.ConsoleEnabled;
				out << YAML::Key << "SceneEnabled" << YAML::Value << m_EditorSettings.SceneEnabled;
				out << YAML::Key << "SceneHierarchyEnabled" << YAML::Value << m_EditorSettings.SceneHierarchyEnabled;
				out << YAML::Key << "ObjectPropertiesEnabled" << YAML::Value << m_EditorSettings.ObjectPropertiesEnabled;
				out << YAML::Key << "FileBrowserEnabled" << YAML::Value << m_EditorSettings.FileBrowserEnabled;
				out << YAML::Key << "CurrentScene" << YAML::Value << m_EditorSettings.CurrentScene;
			}
			out << YAML::EndMap;
		}
		out << YAML::EndMap;

		const auto& fullPath = m_ProjectSettings.Directory / s_ProjectFilePathRel;

		std::ofstream fout(fullPath, std::ios::out | std::ios::trunc);
		fout << out.c_str();
		fout.close();

		TRACE("Project {} saved successfuly!", m_ProjectSettings.Name);
	}

	const std::filesystem::path Project::s_ProjectFilePathRel = std::filesystem::path(".drawgon") / std::filesystem::path("drawgon.proj");
	const std::filesystem::path Project::s_ProjectScenesPathRel = std::filesystem::path(".drawgon") / std::filesystem::path("scenes");
	const std::filesystem::path Project::s_ProjectGUILayoutPathRel = std::filesystem::path(".drawgon") / std::filesystem::path("imgui.ini");
}