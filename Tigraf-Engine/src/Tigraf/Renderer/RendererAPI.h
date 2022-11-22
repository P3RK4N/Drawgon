#pragma once
#include "glm/glm.hpp"

#include "Buffers/Buffer.h"

namespace Tigraf
{
	class RendererAPI
	{
	public:
		virtual ~RendererAPI() {}

		virtual void init() = 0;

		virtual void clear() = 0;
		virtual void setClearColor(const glm::vec4& color) = 0;

		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void draw(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void drawIndexed(const Ref<VertexBuffer>& vertexBuffer) = 0;

	private:

	};
}