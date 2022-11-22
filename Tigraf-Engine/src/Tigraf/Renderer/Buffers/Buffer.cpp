#include "PCH.h"
#include "Buffer.h"

#include "OpenGLBuffer.h"

namespace Tigraf
{
	Ref<VertexBuffer> VertexBuffer::create(uint32_t vertexCount, uint32_t vertexSize, void* data, uint32_t flags)
	{
		return createRef<OpenGLVertexBuffer>(vertexCount, vertexSize, data, flags);
	}

	Ref<IndexBuffer> IndexBuffer::create(const std::vector<uint32_t>& indices, uint32_t flags)
	{
		return createRef<OpenGLIndexBuffer>(indices, flags);
	}

}