#pragma once

#include "Core/Common.h"
#include "Vertex.h"
#include <d3d11.h>
#include <stdint.h>
#include <vector>

namespace Craft
{
	class CRAFT_API StaticMesh
	{
	public:
		StaticMesh();
		virtual ~StaticMesh();

		void Initialize(
			const void* vertices,
			uint32_t vertexCount,
			uint32_t stride,
			const void* indices,
			uint32_t indexCount);

		void UpdateVertexBuffer(const std::vector<Vertex>& vertices); // @test

		virtual void Bind();

		inline ID3D11Buffer* GetVertexBuffer() const { return vertexBuffer; }
		inline ID3D11Buffer* GetIndexBuffer() const { return indexBuffer; }
		inline uint32_t GetIndexCount() const { return indexCount; }
		inline uint32_t GetStride() const { return stride; }

		inline std::vector<Vertex> GetVertices() const { return vertices; } // @test

	protected:
		ID3D11Buffer* vertexBuffer = nullptr;
		ID3D11Buffer* indexBuffer = nullptr;
		uint32_t indexCount = 0;
		uint32_t stride = 0;

		std::vector<Vertex> vertices; // @test
	};
}