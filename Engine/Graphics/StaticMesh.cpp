#include "StaticMesh.h"
#include "GraphicsContext.h"
#include "Core/Common.h"

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

		// 서브 리소스 데이터 설정 (실제 데이터 할당).
		D3D11_SUBRESOURCE_DATA indexData = { };
		indexData.pSysMem = indices;

		// 인덱스 버퍼 생성.
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
}