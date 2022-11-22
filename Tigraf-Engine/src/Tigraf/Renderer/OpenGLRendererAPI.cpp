#include "PCH.h"
#include "OpenGLRendererAPI.h"

namespace Tigraf
{
	void OpenGLRendererAPI::init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

		glClearColor(0.2f, 0.6f, 0.8f, 1.0f);
	}

	void OpenGLRendererAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLRendererAPI::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::draw(const Ref<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(reinterpret_cast<OpenGLVertexBuffer*>(vertexBuffer.get())->getVertexArrayID());
		glDrawArrays(GL_TRIANGLES, 0, vertexBuffer->getVertexCount());
	}

	void OpenGLRendererAPI::drawIndexed(const Ref<VertexBuffer>& vertexBuffer)
	{

		glBindVertexArray(reinterpret_cast<OpenGLVertexBuffer*>(vertexBuffer.get())->getVertexArrayID());

		TIGRAF_ASSERT(vertexBuffer->getIndexBuffer() != nullptr, "Index Buffer must be set before drawing indexed!");

		glDrawElements(GL_TRIANGLES, vertexBuffer->getIndexBuffer()->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}
}