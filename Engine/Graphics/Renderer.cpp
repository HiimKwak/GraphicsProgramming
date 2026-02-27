#include "Renderer.h"
#include "Core/Common.h"
#include "GraphicsContext.h"
#include <d3dcompiler.h>

namespace Craft
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
		auto& command = renderQueue[0];
		SafeRelease(command.vertexBuffer);
		SafeRelease(command.indexBuffer);
		SafeRelease(command.inputLayout);
		SafeRelease(command.vertexShader);
		SafeRelease(command.pixelShader);
	}

	void Renderer::Initialize()
	{
		auto& device = GraphicsContext::Get().GetDevice();

		float vertices[] = {
			0.0f, 0.5f, 0.1f,
			0.5f, -0.5f, 0.1f,
			-0.5f, -0.5f, 0.1f // 왼손 좌표계
		};

		// UINT ByteWidth;
		// D3D11_USAGE Usage;
		// UINT BindFlags;
		// UINT CPUAccessFlags;
		// UINT MiscFlags;
		// UINT StructureByteStride;
		D3D11_BUFFER_DESC vertexBufferDesc{};
		vertexBufferDesc.ByteWidth = sizeof(float) * _countof(vertices);
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// const void* pSysMem;
		// UINT SysMemPitch;
		// UINT SysMemSlicePitch;
		D3D11_SUBRESOURCE_DATA vertexData = {}; // 서브 리소스 데이터 설정(실제 데이터 할당)
		vertexData.pSysMem = vertices;

		ID3D11Buffer* vertexBuffer = nullptr;
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

		uint32_t indices[] = { 0,1,2 }; // 삼각형 조합 시 정점 순서 지정

		D3D11_BUFFER_DESC indexBufferDesc{};
		indexBufferDesc.ByteWidth = sizeof(uint32_t) * _countof(indices);
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		// const void* pSysMem;
		// UINT SysMemPitch;
		// UINT SysMemSlicePitch;
		D3D11_SUBRESOURCE_DATA indexData = {}; // 서브 리소스 데이터 설정(실제 데이터 할당)
		indexData.pSysMem = indices;

		ID3D11Buffer* indexBuffer = nullptr;
		HRESULT result = device.CreateBuffer(
			&indexBufferDesc,
			&indexData,
			&indexBuffer
		);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		RenderCommand command = { };
		command.vertexBuffer = vertexBuffer;
		command.indexBuffer = indexBuffer;
		command.indexCount = _countof(indices);
	}

	void Renderer::DrawScene()
	{
	}
}