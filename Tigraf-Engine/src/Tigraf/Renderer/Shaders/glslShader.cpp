#include "PCH.h"
#include "glslShader.h"

namespace Tigraf
{
	const static std::unordered_map<std::string, GLuint> NameToShaderType
	{
		{"VertexShader", GL_VERTEX_SHADER},
		{"PixelShader", GL_FRAGMENT_SHADER},
		{"GeometryShader", GL_GEOMETRY_SHADER}
	};

#define GET_SHADER_TYPE(ShaderText) NameToShaderType[ShaderText.substr(0, ShaderText.size()-1)]

	glslShader::glslShader(std::filesystem::path path)
	{
		std::ifstream shaderFile(path);
		TIGRAF_ASSERT(shaderFile.is_open(), "Shader file could not be opened!");

		m_ShaderID = glCreateProgram();

		auto attachShader = [&](const std::string& shaderName, const GLchar* shaderSrc)
		{
			GLuint shader = glCreateShader(NameToShaderType.at(shaderName));

			glShaderSource(shader, 1, &shaderSrc, NULL);
			glCompileShader(shader);

			int  success;
			char infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if(!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				CORE_ERROR(std::format("{} - {}", shader, infoLog));
			}
			glAttachShader(m_ShaderID, shader);
		};

		std::string currentShaderName = "";
		std::stringstream shaderSS;

		std::string line;
		while(std::getline(shaderFile, line))
		{
			if(line[0] == '$')
			{
				if(!currentShaderName.empty()) attachShader(currentShaderName, shaderSS.str().c_str());

				shaderSS = std::stringstream{};
				currentShaderName = line.substr(1, line.length() - 1);
			}
			else shaderSS << line << '\n';
		}
		
		if(!currentShaderName.empty()) attachShader(currentShaderName, shaderSS.str().c_str());

		glLinkProgram(m_ShaderID);
	}

	glslShader::~glslShader()
	{
		glDeleteProgram(m_ShaderID);
	}

	void glslShader::bind()
	{
		glUseProgram(m_ShaderID);
	}
}