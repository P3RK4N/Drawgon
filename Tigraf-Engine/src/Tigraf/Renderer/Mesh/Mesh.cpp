#include "PCH.h"
#include "Mesh.h"

#include "Tigraf/Renderer/Renderer.h"
#include "Tigraf/Renderer/Shaders/Shader.h"

namespace Tigraf
{
	Mesh::Mesh(Ref<VertexBuffer> vertexBuffer, Ref<IndexBuffer> indexBuffer, Ref<Shader> shader)
		: m_Shader(shader), m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer) 
	{
		if(m_IndexBuffer) m_VertexBuffer->setIndexBuffer(m_IndexBuffer);
	}

	void Mesh::draw()
	{
		TIGRAF_ASSERT(m_Shader, "Shader not attached!");
	
		m_Shader->use();
		Renderer::s_RendererAPI->draw(m_VertexBuffer);
	}

	void Mesh::drawIndexed()
	{
		TIGRAF_ASSERT(m_IndexBuffer, "Index buffer not attached!");
		TIGRAF_ASSERT(m_Shader, "Shader not attached!");

		m_Shader->use();
		Renderer::s_RendererAPI->drawIndexed(m_VertexBuffer);
	}
}