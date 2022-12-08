#pragma once
#include "RendererAPI.h"
#include "Buffers/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Tigraf
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual ~OpenGLRendererAPI() override {}

		virtual void init() override;

		virtual void clear() override;
		virtual void setClearColor(const glm::vec4& color) override;

		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void draw(const Ref<VertexBuffer>& vertexBuffer);
		virtual void drawIndexed(const Ref<VertexBuffer>& vertexBuffer);

	private:
		void initGlobalUniformBuffers();
	};
}