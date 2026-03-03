#include "Renderer.h"
#include "Core/Common.h"
#include "GraphicsContext.h"
#include <d3dcompiler.h>
#include "Core/Common.h"

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

		// 셰이더 컴파일
		// (_In_ LPCWSTR pFileName,
		// _In_reads_opt_(_Inexpressible_(pDefines->Name != NULL)) CONST D3D_SHADER_MACRO* pDefines,
		// _In_opt_ ID3DInclude* pInclude,
		// _In_ LPCSTR pEntrypoint,
		// _In_ LPCSTR pTarget,
		// _In_ UINT Flags1,
		// _In_ UINT Flags2,
		// _Out_ ID3DBlob** ppCode,
		// _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorMsgs

		ID3DBlob* vertexShaderObject = nullptr; // 컴파일된 Object 코드 저장
		result = D3DCompileFromFile(
			L"HLSLShader/DefaultVS.hlsl",
			nullptr,
			nullptr,
			"main",
			"vs_5_0",
			0,
			0,
			&vertexShaderObject,
			nullptr
		);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		// 셰이더 객체 생성
		ID3D11VertexShader* vertexShader = nullptr;
		device.CreateVertexShader(
			vertexShaderObject->GetBufferPointer(),
			vertexShaderObject->GetBufferSize(),
			nullptr,
			&vertexShader

		);

		// 셰이더 컴파일
		// (_In_ LPCWSTR pFileName,
		// _In_reads_opt_(_Inexpressible_(pDefines->Name != NULL)) CONST D3D_SHADER_MACRO* pDefines,
		// _In_opt_ ID3DInclude* pInclude,
		// _In_ LPCSTR pEntrypoint,
		// _In_ LPCSTR pTarget,
		// _In_ UINT Flags1,
		// _In_ UINT Flags2,
		// _Out_ ID3DBlob** ppCode,
		// _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorMsgs

		ID3DBlob* pixelShaderObject = nullptr; // 컴파일된 Object 코드 저장
		result = D3DCompileFromFile(
			L"HLSLShader/DefaultPS.hlsl",
			nullptr,
			nullptr,
			"main",
			"ps_5_0",
			0,
			0,
			&pixelShaderObject,
			nullptr
		);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		// 셰이더 객체 생성
		ID3D11PixelShader* pixelShader = nullptr;
		device.CreatePixelShader(
			pixelShaderObject->GetBufferPointer(),
			pixelShaderObject->GetBufferSize(),
			nullptr,
			&pixelShader

		);

		// 입력 레이아웃 생성

		// LPCSTR SemanticName;
		// UINT SemanticIndex;
		// DXGI_FORMAT Format;
		// UINT InputSlot;
		// UINT AlignedByteOffset;
		// D3D11_INPUT_CLASSIFICATION InputSlotClass;
		// UINT InstanceDataStepRate;
		D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		// _In_reads_(NumElements)  const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
		// _In_range_(0, D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT)  UINT NumElements,
		// _In_reads_(BytecodeLength)  const void* pShaderBytecodeWithInputSignature,
		// _In_  SIZE_T BytecodeLength,
		// _COM_Outptr_opt_  ID3D11InputLayout** ppInputLayout) = 0;
		ID3D11InputLayout* inputLayout = nullptr; // 입력 레아이웃 : 정점 세이더
		result = device.CreateInputLayout(
			inputDesc, _countof(inputDesc), vertexShaderObject->GetBufferPointer(), vertexShaderObject->GetBufferSize(), &inputLayout
		);

		RenderCommand command = { };
		command.vertexBuffer = vertexBuffer;
		command.indexBuffer = indexBuffer;
		command.indexCount = _countof(indices);
		command.vertexShader = vertexShader;
		command.pixelShader = pixelShader;
		command.inputLayout = inputLayout;

		renderQueue.emplace_back(command);

		SafeRelease(vertexShaderObject);
		SafeRelease(pixelShaderObject);
	}

	void Renderer::DrawScene()
	{
		// 바인딩: 셰이더 각 단계에 필요한 정보 전달 + 설정
		// state 설정
		auto& context = GraphicsContext::Get().GetDeviceContext();

		RenderCommand& command = renderQueue[0];

		uint32_t stride = sizeof(float) * 3; // 정점 배열에서 데이터 한 블럭의 너비(byte 너비)
		uint32_t offset = 0;
		context.IASetVertexBuffers(0, 1, &command.vertexBuffer, &stride, &offset);
		context.IASetIndexBuffer(command.indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		context.IASetInputLayout(command.inputLayout);
		context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 점 3개씩 잘라 읽고 삼각형을 만들어주는 모드
		// 셰이더 설정
		context.VSSetShader(command.vertexShader, nullptr, 0);
		context.PSSetShader(command.pixelShader, nullptr, 0);
		// draw 콜
		context.DrawIndexed(command.indexCount, 0, 0);
	}
}