#include "StaticMesh.h"
#include "GraphicsContext.h"
#include "Core/Common.h"

namespace Craft
{
	SubMesh::SubMesh()
	{
	}

	SubMesh::SubMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) : stride(Vertex::Stride())
	{
		this->vertices.assign(vertices.begin(), vertices.end());
		this->indices.assign(indices.begin(), indices.end());

		auto& device = GraphicsContext::Get().GetDevice();

		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth = stride * (uint32_t)vertices.size();
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = this->vertices.data();

		ThrowIfFailed(device.CreateBuffer(
			&vertexBufferDesc,
			&vertexData,
			&vertexBuffer
		), L"Failed to create vertex buffer.");

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(uint32_t) * (uint32_t)indices.size();
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = { };
		indexData.pSysMem = this->indices.data();

		indexBuffer = nullptr;
		ThrowIfFailed(device.CreateBuffer(
			&indexBufferDesc,
			&indexData,
			&indexBuffer
		), L"Failed to create index buffer.");
	}

	SubMesh::~SubMesh()
	{
	}

	void SubMesh::Bind()
	{
	}

	/* SubMesh */

	StaticMesh::StaticMesh()
	{
	}

	StaticMesh::~StaticMesh()
	{
		SafeRelease(vertexBuffer);
		SafeRelease(indexBuffer);
	}

	void StaticMesh::Initialize(
		const void* vertices, uint32_t vertexCount, uint32_t stride,
		const void* indices, uint32_t indexCount)
	{
		// @test
		this->vertices.reserve(vertexCount);
		Vertex* vertexArray = (Vertex*)(vertices);
		for (uint32_t i = 0; i < vertexCount; ++i)
		{
			this->vertices.emplace_back(vertexArray[i]);
		}
	}

	void StaticMesh::UpdateVertexBuffer(const std::vector<Vertex>& vertices)
	{
		if (!vertexBuffer || vertices.empty())
			return;

		auto& context = GraphicsContext::Get().GetDeviceContext();
		context.UpdateSubresource(vertexBuffer, 0, nullptr, vertices.data(), 0, 0);
	}

	void StaticMesh::Bind()
	{
		auto& context = GraphicsContext::Get().GetDeviceContext();

		uint32_t offset = 0;
		context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		context.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}