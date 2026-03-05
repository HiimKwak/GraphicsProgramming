#include "StaticMesh.h"
#include "GraphicsContext.h"
#include "Core/Common.h"
#include "Graphics/GraphicsContext.h"

namespace Craft
{
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
		auto& device = GraphicsContext::Get().GetDevice();

		this->stride = stride;
		this->indexCount = indexCount;

		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth = stride * vertexCount;
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = vertices;

		vertexBuffer = nullptr;
		HRESULT result = device.CreateBuffer(
			&vertexBufferDesc,
			&vertexData,
			&vertexBuffer
		);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(uint32_t) * indexCount;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = { };
		indexData.pSysMem = indices;

		indexBuffer = nullptr;
		result = device.CreateBuffer(
			&indexBufferDesc,
			&indexData,
			&indexBuffer
		);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}
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