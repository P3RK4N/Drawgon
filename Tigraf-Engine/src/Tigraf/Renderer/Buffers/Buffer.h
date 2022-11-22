#pragma once
#include <cstdint>

namespace Tigraf
{
#define isINT(VertexAttributeType)		(uint32_t)VertexAttributeType < 10U
#define isFLOAT(VertexAttributeType)	(uint32_t)VertexAttributeType < 20U && (uint32_t)VertexAttributeType >= 10
#define isDOUBLE(VertexAttributeType)	(uint32_t)VertexAttributeType >= 20U

	enum class VertexAttributeType : uint16_t
	{
		INT = 0,
		INT2 = 1,
		INT3 = 2,
		INT4 = 3,

		FLOAT = 10,
		FLOAT2 = 11,
		FLOAT3 = 12,
		FLOAT4 = 13,

		FLOAT3X3 = 14,
		FLOAT4X4 = 15,
	};

	class IndexBuffer;

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void pushVertexAttribute(VertexAttributeType type) = 0;

		const Ref<IndexBuffer>& getIndexBuffer() { return m_IndexBuffer; }
		virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
		
		const uint32_t getVertexSize() const { return m_VertexSize; }
		const uint32_t getVertexCount() const { return m_VertexCount; }

	public:
		static Ref<VertexBuffer> create(uint32_t vertexCount, uint32_t vertexSize, void* data, uint32_t flags);

	protected:
		uint32_t m_VertexSize = 0;
		uint32_t m_VertexCount = 0;

		Ref<IndexBuffer> m_IndexBuffer = nullptr;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		const uint32_t getIndicesCount() const { return m_IndicesCount; }

	public:
		static Ref<IndexBuffer> create(const std::vector<uint32_t>& indices, uint32_t flags);

	protected:
		uint32_t m_IndicesCount = 0;
	};

	//class ConstantBuffer
	//{
	//
	//};
}