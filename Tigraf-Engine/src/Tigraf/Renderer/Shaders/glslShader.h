#pragma once
#include "Shader.h"

#include <glad/glad.h>
#include <filesystem>

namespace Tigraf
{
	class glslShader : public Shader
	{
	public:
		glslShader(std::filesystem::path path);
		virtual ~glslShader();

		void bind();

	protected:
		GLuint m_ShaderID = 0;

	};
}
