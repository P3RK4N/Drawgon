#include "PCH.h"
#include "OpenGLBuffer.h"

namespace Tigraf
{
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
		glDeleteBuffers(1, &m_VertexBufferID);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(GLuint vertexCount, GLuint vertexSize, void* data, GLuint flags)
	{
		m_VertexSize = vertexSize;
		m_VertexCount = vertexCount;

		//Creating vertex buffer and assigning immutable storage to it
		glCreateBuffers(1, &m_VertexBufferID);
		glNamedBufferStorage(m_VertexBufferID, vertexSize*vertexCount, data, flags);

		//Creating vertex array and binding buffer to index 0
		glCreateVertexArrays(1, &m_VertexArrayID);
		glVertexArrayVertexBuffer(m_VertexArrayID, 0, m_VertexBufferID, 0, vertexSize);
	}

	void OpenGLVertexBuffer::pushVertexAttribute(VertexAttributeType type)
	{
		glEnableVertexArrayAttrib(m_VertexArrayID, m_AttributeCount);

		GLuint attributeSize = OpenGLVertexAttributeTypeSize(type);
		GLenum attributeElementType = OpenGLVertexAttributeType(type);
		GLuint attributeElementCount = OpenGLVertexAttributeTypeCount(type);
	
		//Adding attribute to vertex array
		if(isINT(type))			glVertexArrayAttribIFormat(m_VertexArrayID, m_AttributeCount, attributeElementCount, attributeElementType, m_AttributeOffset);
		else if(isFLOAT(type))	glVertexArrayAttribFormat(m_VertexArrayID, m_AttributeCount, attributeElementCount, attributeElementType, false, m_AttributeOffset);
		else if(isDOUBLE(type)) glVertexArrayAttribLFormat(m_VertexArrayID, m_AttributeCount, attributeElementCount, attributeElementType, m_AttributeOffset);

		//Binding attribute to first vertex buffer
		glVertexArrayAttribBinding(m_VertexArrayID, m_AttributeCount, 0);

		m_AttributeOffset += attributeSize; 
		m_AttributeCount += 1;

	}

	void OpenGLVertexBuffer::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glVertexArrayElementBuffer(m_VertexArrayID, reinterpret_cast<OpenGLIndexBuffer*>(indexBuffer.get())->getIndexBufferID());
		m_IndexBuffer = indexBuffer;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<GLuint>& indices, GLuint flags)
	{
		m_IndicesCount = indices.size();
		glCreateBuffers(1, &m_IndexBufferID);
		glNamedBufferStorage(m_IndexBufferID, m_IndicesCount * sizeof(indices[0]), indices.data(), flags);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_IndexBufferID);
	}

}